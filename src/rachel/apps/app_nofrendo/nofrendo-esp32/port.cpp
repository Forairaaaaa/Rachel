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
 * @brief Roms
 * 
 */
/* ------------------------------------------------------------------ */
// #include "../roms/rom_smb.h"
// #include "../roms/rom_contra.h"
// #include "../roms/rom_tetris.h"
// #include "../roms/rom_zelda.h"

// extern "C" char* nofendo_get_rom()
// {
//     char* rom = (char*)rom_smb;

//     SelectMenu menu;
//     std::vector<std::string> item_list = {
//         "[ROMS]",
//         "Super Mario Bros",
//         "Contra",
//         "Zelda",
//         "Tetris"
//     };
//     auto selected_item = menu.waitResult(item_list);

//     if (selected_item == 1)
//         rom = (char*)rom_smb;
//     else if (selected_item == 2)
//         rom = (char*)rom_contra;
//     else if (selected_item == 3)
//         rom = (char*)rom_zelda;
//     else if (selected_item == 4)
//         rom = (char*)rom_tetris;

//     return rom;
// }


extern "C" char* nofendo_get_rom()
{
    char* rom = nullptr;

    // Ls rom dir 
    // TODO 

    // Create menu
    // TODO

    // Allocate buffer
    // TODO

    // Copy rom
    // TODO

    return rom;
}
/* ------------------------------------------------------------------ */
