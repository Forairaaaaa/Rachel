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
    // for (int32_t i = 0; i < NES_SCREEN_HEIGHT; i++)
    // {
    //     HAL::GetCanvas()->writeIndexedPixels((uint8_t *)(data[i]), myPalette, NES_SCREEN_WIDTH);
    // }

    

    for (int y = 0; y < NES_SCREEN_HEIGHT; y++)
	{
		// HAL::GetCanvas()->writeIndexedPixels((const uint8_t*)(bmp->line), myPalette, NES_SCREEN_WIDTH);
		// gfx->writeIndexedPixels((uint8_t *)(data[i] + frame_x_offset), myPalette, frame_line_pixels);
		for (int x = 0; x < NES_SCREEN_WIDTH; x++)
		{
			HAL::GetCanvas()->drawPixel(x + x_offset, y + y_offset, myPalette[data[y][x]]);
		}
	}

	HAL::CanvasUpdate();
}


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
