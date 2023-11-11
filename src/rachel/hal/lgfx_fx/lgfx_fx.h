/**
 * @file lgfx_fx.hpp
 * @author Forairaaaaa
 * @brief 
 * @version 0.1
 * @date 2023-11-11
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#pragma once
#include <LovyanGFX.hpp>


/**
 * @brief Add apis to fill shape layer in difference mode 
 * 
 */
class LGFX_SpriteFx : public LGFX_Sprite
{
public:
    LGFX_SpriteFx(LovyanGFX* parent) : 
        LGFX_Sprite(parent) 
        {}

    void drawFastHLineInDifference( int32_t x, int32_t y, int32_t w);
    void fillRectInDifference( int32_t x, int32_t y, int32_t w, int32_t h);
    void fillSmoothRoundRectInDifference(int32_t x, int32_t y, int32_t w, int32_t h, int32_t r);
    inline void fillSmoothCircleInDifference(int32_t x, int32_t y, int32_t r) { fillSmoothRoundRectInDifference(x-r, y-r, r*2+1, r*2+1, r); }
};
