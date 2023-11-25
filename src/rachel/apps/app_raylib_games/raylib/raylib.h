/**
 * @file raylib.h
 * @author Forairaaaaa
 * @brief Ref: https://www.raylib.com/cheatsheet/cheatsheet.html
 * @version 0.1
 * @date 2023-11-13
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#pragma once
#include "../../../hal/hal.h"
#include "../../assets/theme/theme.h"
#include "../../utils/system/ui/ui.h"
#include <cstdint>


// Vector2 type
typedef struct Vector2 {
    float x;
    float y;
} Vector2;


// Rectangle type
typedef struct Rectangle {
    float x;
    float y;
    float width;
    float height;
} Rectangle;


// Some Basic Colors
// NOTE: Custom raylib color palette for amazing visuals on WHITE background
#define LIGHTGRAY  0xC8C8C8   // Light Gray
#define GRAY       0x828282   // Gray
#define DARKGRAY   0x505050   // Dark Gray
#define YELLOW     0xFDF900   // Yellow
#define GOLD       0xFFCB00   // Gold
#define ORANGE     0xFFA100   // Orange
#define PINK       0xFF6DC2   // Pink
#define RED        0xE62937   // Red
#define MAROON     0xBE2137   // Maroon
#define GREEN      0x00E430   // Green
#define LIME       0x009E2F   // Lime
#define DARKGREEN  0x00752C   // Dark Green
#define SKYBLUE    0x66BFFF   // Sky Blue
#define BLUE       0x0079F1   // Blue
#define DARKBLUE   0x0052AC   // Dark Blue
#define PURPLE     0xC87AFF   // Purple
#define VIOLET     0x873CBE   // Violet
#define DARKPURPLE 0x701F7E   // Dark Purple
#define BEIGE      0xD3B083   // Beige
#define BROWN      0x7F6A4F   // Brown
#define DARKBROWN  0x4C3F2F   // Dark Brown

#define WHITE      0xFFFFFF   // White
#define BLACK      0x000000   // Black
// #define BLANK      0x   // Blank (Transparent)
#define MAGENTA    0xFF00FF   // Magenta
#define RAYWHITE   0xF5F5F5   // My own White (raylib logo)


void InitWindow(int w, int h, const char* title);
void SetTargetFPS(int fps);
bool WindowShouldClose();
void CloseWindow();
int GetScreenWidth();
bool CheckCollisionCircleRec(Vector2 center, float radius, Rectangle rec);
void BeginDrawing();
void EndDrawing();
void ClearBackground(uint32_t color);
void DrawRectangle(int x, int y, int w, int h, uint32_t color);
void DrawCircleV(Vector2 center, float r, uint32_t color);
void DrawLineV(Vector2 startPos, Vector2 endPos, uint32_t color);
void DrawLine(int startPosX, int startPosY, int endPosX, int endPosY, uint32_t color);
void DrawRectangleV(Vector2 position, Vector2 size, uint32_t color);
int GetRandomValue(int min, int max);
