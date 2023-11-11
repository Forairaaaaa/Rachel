/**
 * @file rcb_align_right.cpp
 * @author Forairaaaaa
 * @brief 
 * @version 0.1
 * @date 2023-11-11
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#include "render_callbacks.h"
#include "../../../../../assets/theme/theme.h"
#include "../../../../../../hal/hal.h"


using namespace SYSTEM::UI;


void SelectMenuRenderCb_AlignRight::renderCallback(
    const std::vector<SMOOTH_MENU::Item_t*>& menuItemList,
    const SMOOTH_MENU::RenderAttribute_t& selector,
    const SMOOTH_MENU::RenderAttribute_t& camera
)
{
    // Clear 
    HAL::GetCanvas()->fillScreen(THEME_COLOR_DARK);

    // Render items 
    HAL::GetCanvas()->setTextColor(THEME_COLOR_LIGHT, THEME_COLOR_DARK);
    HAL::GetCanvas()->setTextSize(1);
    HAL::GetCanvas()->setTextDatum(textdatum_t::top_right);
    for (int i = 0; i < menuItemList.size(); i++)
    {
        HAL::GetCanvas()->drawString(
            menuItemList[i]->tag.c_str(), 
            menuItemList[i]->x + camera.width - 20, 
            menuItemList[i]->y - camera.y
        );
    }

    // Render selector 
    HAL::GetCanvas()->setColor(TFT_WHITE);
    HAL::GetCanvas()->fillSmoothRoundRectInDifference(
        selector.x + camera.width - selector.width - 20,
        selector.y - camera.y + (menuItemList[selector.targetItem]->height - selector.height) / 2,
        selector.width,
        selector.height,
        6
    );
}
