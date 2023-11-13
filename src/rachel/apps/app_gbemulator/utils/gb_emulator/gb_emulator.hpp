/**
 * @file gb_emulator.hpp
 * @author Forairaaaaa
 * @brief 
 * @version 0.1
 * @date 2023-11-13
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#pragma once
#include "timer.h"
#include "rom.h"
#include "mem.h"
#include "cpu.h"
#include "lcd.h"
#include "sdl.h"
#include "gbrom.h"
#include "../../../../hal/hal.h"


void gb_emulator_start()
{
    rom_init(gb_rom);
    sdl_init();
    gb_mem_init();
    cpu_init();
}


void gb_emulator_update()
{
    cpu_cycle();
    lcd_cycle();
    timer_cycle();
    lgfx::delayMicroseconds(1);
}
