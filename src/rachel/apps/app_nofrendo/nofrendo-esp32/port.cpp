/**
 * @file port.cpp
 * @author Forairaaaaa
 * @brief 
 * @version 0.1
 * @date 2023-11-15
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#include "../../../hal/hal.h"
#include <cstdint>


/**
 * @brief Render 
 * 
 */
/* ------------------------------------------------------------------ */
/* Visible (NTSC) screen height */
#ifndef NES_VISIBLE_HEIGHT
#define  NES_VISIBLE_HEIGHT   224
#endif /* !NES_VISIBLE_HEIGHT */
#define  NES_SCREEN_WIDTH     256
#define  NES_SCREEN_HEIGHT    NES_VISIBLE_HEIGHT

extern uint16_t myPalette[];
static const int x_offset = -8;
static const int y_offset = 8;

extern "C" void nofendo_render_frame(const uint8_t* data[])
{
    for (int y = 0; y < NES_SCREEN_HEIGHT; y++)
    {
        // HAL::GetCanvas()->writeIndexedPixels((const uint8_t*)(bmp->line), myPalette, NES_SCREEN_WIDTH);
        for (int x = 0; x < NES_SCREEN_WIDTH; x++)
        {
            HAL::GetCanvas()->drawPixel(x + x_offset, y + y_offset, myPalette[data[y][x]]);
        }
    }
    HAL::CanvasUpdate();
}
/* ------------------------------------------------------------------ */


/**
 * @brief Buttons 
 * 
 */
/* ------------------------------------------------------------------ */
extern "C" uint8_t nofendo_get_btn_a()
{
    return HAL::GetButton(GAMEPAD::BTN_A);
}

extern "C" uint8_t nofendo_get_btn_b()
{
    return HAL::GetButton(GAMEPAD::BTN_B);
}

extern "C" uint8_t nofendo_get_btn_select()
{
    return HAL::GetButton(GAMEPAD::BTN_SELECT);
}

extern "C" uint8_t nofendo_get_btn_start()
{
    return HAL::GetButton(GAMEPAD::BTN_START);
}

extern "C" uint8_t nofendo_get_btn_right()
{
    return HAL::GetButton(GAMEPAD::BTN_RIGHT);
}

extern "C" uint8_t nofendo_get_btn_left()
{
    return HAL::GetButton(GAMEPAD::BTN_LEFT);
}

extern "C" uint8_t nofendo_get_btn_up()
{
    return HAL::GetButton(GAMEPAD::BTN_UP);
}

extern "C" uint8_t nofendo_get_btn_down()
{
    return HAL::GetButton(GAMEPAD::BTN_DOWN);
}

extern "C" uint8_t nofendo_get_btn_x()
{
    return HAL::GetButton(GAMEPAD::BTN_X);
}

extern "C" uint8_t nofendo_get_btn_y()
{
    return HAL::GetButton(GAMEPAD::BTN_Y);
}
/* ------------------------------------------------------------------ */

/**
 * @brief Pause menu
 * 
 */
/* ------------------------------------------------------------------ */
#include "../../../utils/system/ui/ui.h"

using namespace SYSTEM::UI;

extern "C" void nofendo_pause_menu()
{
    SelectMenu menu;
    std::vector<std::string> item_list = {
        "[PAUSE MENU]",
        "Continue",
        "Power Off",
        "Reboot"
    };
    auto selected_item = menu.waitResult(item_list);

    if (selected_item == 2)
        HAL::PowerOff();
    else if (selected_item == 3)
        HAL::Reboot();
}

/* ------------------------------------------------------------------ */


/**
 * @brief Get roms from sd card 
 * 
 */
/* ------------------------------------------------------------------ */
#ifdef ESP_PLATFORM
#include <Arduino.h>
#include <SD.h>
#include <esp_partition.h>


static char* _load_rom_2_ram(File& rom_file);
static char* _load_rom_2_flash(File& rom_file);


static const String _nes_rom_path = "/nes_roms";

extern "C" char* nofendo_get_rom()
{
    if (!HAL::CheckSdCard())
        HAL::PopFatalError("没SD卡啊朋友");
    printf("try loading roms from SD card in %s\n", _nes_rom_path.c_str());


    // Check path 
    if (!SD.exists(_nes_rom_path))
    {
        std::string msg = "ROM路径不存在\n  (";
        msg += _nes_rom_path.c_str();
        msg += ")";
        HAL::PopFatalError(msg);
    }

    // List rom dir 
    auto rom_directory = SD.open(_nes_rom_path);
    std::vector<std::string> rom_list = {"[NES ROMS]"};
    while (1)
    {
        File entry =  rom_directory.openNextFile();

        if (!entry)
            break;

        if (!entry.isDirectory())
        {
            rom_list.push_back(entry.name());
            printf("get file: %s size: %ld\n", entry.name(), entry.size());
        }
        
        entry.close();    
    }
    if (rom_list.size() == 1)
        HAL::PopFatalError("没游戏啊朋友");


    // Create select menu
    SelectMenu menu;
    auto selected_item = menu.waitResult(rom_list);


    // Try open 
    String rom_path = _nes_rom_path;
    rom_path += "/";
    rom_path += rom_list[selected_item].c_str();
    printf("try open %s\n", rom_path.c_str());
    auto rom_file = SD.open(rom_path, FILE_READ);


    // return _load_rom_2_ram(rom_file);
    return _load_rom_2_flash(rom_file);
}


static char* _load_rom_2_ram(File& rom_file)
{
    // Try allocate rom buffer
    printf("try alloc buffer size: %ld\n", rom_file.size());
    auto free_block = heap_caps_get_largest_free_block(MALLOC_CAP_DEFAULT);
    printf("free block: %ld\n", free_block);

    if (free_block < rom_file.size())
        HAL::PopFatalError("内存不够啊朋友");


    // Alloc buffer 
    char* rom_buffer = new char[rom_file.size()];

    // Copy rom
    rom_file.readBytes(rom_buffer, rom_file.size());
    rom_file.close();


    // Clear screen
    HAL::GetCanvas()->clear(TFT_BLACK);


    return rom_buffer;
}


#include "../../../assets/theme/theme.h"

#define MAX_ROM_SIZE (2*1024*1024)

// Refs: 
// https://github.com/espressif/esp32-nesemu/blob/master/main/main.c#L13
// https://github.com/Ryuzaki-MrL/Espeon/blob/master/espeon.cpp#L186
static char* _load_rom_2_flash(File& rom_file)
{
    // Get partition 
    const esp_partition_t* part = esp_partition_find_first(ESP_PARTITION_TYPE_ANY, ESP_PARTITION_SUBTYPE_ANY, "gamerom");
    if (!part)
        HAL::PopFatalError("没这分区啊朋友\n  (gamerom)");


    HAL::GetCanvas()->clear(THEME_COLOR_DARK);
    HAL::GetCanvas()->setTextScroll(true);
    HAL::GetCanvas()->setCursor(0, 0);
    HAL::GetCanvas()->printf("Erasing...\n");
    HAL::CanvasUpdate();


    // Erase 
    esp_err_t err;
    err = esp_partition_erase_range(part, 0, MAX_ROM_SIZE);
    if (err != ESP_OK)
        HAL::PopFatalError("格式分区失败");
	

    // Flash rom into partition 
    const size_t bufsize = 32 * 1024;
    size_t romsize = rom_file.size();
    uint8_t* rombuf = (uint8_t*)calloc(bufsize, 1);

    printf("start flashing:\n");
    HAL::GetCanvas()->printf("Flashing...\n");

    size_t offset = 0;
    while(rom_file.available()) 
    {
        rom_file.read(rombuf, bufsize);
        esp_partition_write(part, offset, (const void*)rombuf, bufsize);
        offset += bufsize;

        printf("%d%%\n", offset * 100 / romsize);
        HAL::GetCanvas()->printf("%d%%\n", offset * 100 / romsize);
        HAL::CanvasUpdate();
    }

    free(rombuf);
    rom_file.close();


    // Map into system 
    spi_flash_mmap_handle_t hrom;
    const uint8_t* romdata;
    // esp_err_t err;
    err = esp_partition_mmap(part, 0, MAX_ROM_SIZE, SPI_FLASH_MMAP_DATA, (const void**)&romdata, &hrom);
    if (err != ESP_OK)
        HAL::PopFatalError("映射失败");


    // Clear screen
    HAL::GetCanvas()->clear(TFT_BLACK);


    return (char*)romdata;
}
#else
extern "C" char* nofendo_get_rom() { return nullptr; }
#endif
/* ------------------------------------------------------------------ */

