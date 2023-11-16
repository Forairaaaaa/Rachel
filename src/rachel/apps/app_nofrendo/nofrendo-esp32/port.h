/**
 * @file port.h
 * @author Forairaaaaa
 * @brief 
 * @version 0.1
 * @date 2023-11-15
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#pragma once
#include <stdint.h>

void nofendo_render_frame(const uint8_t* data[]);
void nofendo_pause_menu();
uint8_t nofendo_get_btn_a();
uint8_t nofendo_get_btn_b();
uint8_t nofendo_get_btn_select();
uint8_t nofendo_get_btn_start();
uint8_t nofendo_get_btn_right();
uint8_t nofendo_get_btn_left();
uint8_t nofendo_get_btn_up();
uint8_t nofendo_get_btn_down();
uint8_t nofendo_get_btn_x();
uint8_t nofendo_get_btn_y();
char* nofendo_get_rom();
