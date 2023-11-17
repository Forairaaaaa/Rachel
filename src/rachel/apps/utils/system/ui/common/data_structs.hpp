/**
 * @file data_structs.hpp
 * @author Forairaaaaa
 * @brief 
 * @version 0.1
 * @date 2023-11-17
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#pragma once
#include <iostream>


namespace SYSTEM::UI
{
    struct BasicShape_t
    {
        int x;
        int y;
        int width;
        int height;
        
        BasicShape_t(int x = 0, int y = 0, int width = 0, int height = 0)
        {
            this->x = x;
            this->y = y;
            this->width = width;
            this->height = height;
        }
    };
}
