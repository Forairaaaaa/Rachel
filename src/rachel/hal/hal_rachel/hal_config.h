/**
 * @file hal_common_config.h
 * @author Forairaaaaa
 * @brief 
 * @version 0.1
 * @date 2023-11-07
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#pragma once

/**
 * @brief Pin configs 
 * 
 */
// LCD 
#define HAL_PIN_LCD_MOSI            40
#define HAL_PIN_LCD_MISO            -1
#define HAL_PIN_LCD_SCLK            41
#define HAL_PIN_LCD_DC              42
#define HAL_PIN_LCD_CS              44
#define HAL_PIN_LCD_RST             12
#define HAL_PIN_LCD_BUSY            -1
#define HAL_PIN_LCD_BL              11

// Power 
#define HAL_PIN_PWR_HOLD            10

// Gamepad 
#define HAL_PIN_GAMEPAD_LS          43
#define HAL_PIN_GAMEPAD_UP          2
#define HAL_PIN_GAMEPAD_DOWN        6
#define HAL_PIN_GAMEPAD_LEFT        3
#define HAL_PIN_GAMEPAD_RIGHT       5
#define HAL_PIN_GAMEPAD_START       9
#define HAL_PIN_GAMEPAD_SELECT      0
#define HAL_PIN_GAMEPAD_X           1
#define HAL_PIN_GAMEPAD_Y           8
#define HAL_PIN_GAMEPAD_A           4
#define HAL_PIN_GAMEPAD_B           7

// SD card  
#define HAL_PIN_SD_CS               15
#define HAL_PIN_SD_MOSI             40
#define HAL_PIN_SD_MISO             39
#define HAL_PIN_SD_CLK              41

// I2C 
#define HAL_PIN_I2C_SCL             13
#define HAL_PIN_I2C_SDA             14

// Buzzer 
#define HAL_PIN_BUZZ                46
