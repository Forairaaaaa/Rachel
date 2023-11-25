/**
 * @file progress_window.h
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
    /**
     * @brief Render a progress window on the screen, 渲染一个带进度条的页面 
     * 
     * @param title Title label on top of the window 
     * @param progress 0~100
     * @param lightMode 
     */
    void ProgressWindow(std::string title, uint8_t progress, bool lightMode = false);
}
