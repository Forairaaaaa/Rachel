/**
 * @file raylib.cpp
 * @author Forairaaaaa
 * @brief 
 * @version 0.1
 * @date 2023-11-13
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#include "raylib.h"


void InitWindow(int w, int h, const char* title)
{
    HAL::LoadLauncherFont24();
}


void SetTargetFPS(int fps) {}


bool WindowShouldClose()
{
    return HAL::GetButton(GAMEPAD::BTN_SELECT);
}


void CloseWindow() {}


int GetScreenWidth()
{
    return HAL::GetCanvas()->width();
}


void BeginDrawing() {}


void EndDrawing()
{
    HAL::CanvasUpdate();
}


void ClearBackground(uint32_t color)
{
    HAL::GetCanvas()->fillScreen(color);
}


void DrawRectangle(int x, int y, int w, int h, uint32_t color)
{
    HAL::GetCanvas()->fillRect(x, y, w, h, color);
}


void DrawCircleV(Vector2 center, float r, uint32_t color)
{
    HAL::GetCanvas()->fillSmoothCircle(center.x, center.y, r, color);
}


#include <random>
std::random_device rd;
std::mt19937 gen(rd());
int GetRandomValue(int min, int max)
{
    std::uniform_int_distribution<> dist(min, max);
    return dist(gen);
}




// Check collision between circle and rectangle
// NOTE: Reviewed version to take into account corner limit case
bool CheckCollisionCircleRec(Vector2 center, float radius, Rectangle rec)
{
    bool collision = false;

    int recCenterX = (int)(rec.x + rec.width/2.0f);
    int recCenterY = (int)(rec.y + rec.height/2.0f);

    float dx = fabsf(center.x - (float)recCenterX);
    float dy = fabsf(center.y - (float)recCenterY);

    if (dx > (rec.width/2.0f + radius)) { return false; }
    if (dy > (rec.height/2.0f + radius)) { return false; }

    if (dx <= (rec.width/2.0f)) { return true; }
    if (dy <= (rec.height/2.0f)) { return true; }

    float cornerDistanceSq = (dx - rec.width/2.0f)*(dx - rec.width/2.0f) +
                             (dy - rec.height/2.0f)*(dy - rec.height/2.0f);

    collision = (cornerDistanceSq <= (radius*radius));

    return collision;
}

