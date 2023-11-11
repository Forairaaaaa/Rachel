/**
 * @file render_callbacks.h
 * @author Forairaaaaa
 * @brief 
 * @version 0.1
 * @date 2023-11-10
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#pragma once
#include "../../../../smooth_menu/simple_menu/simple_menu.h"


namespace SYSTEM::UI
{
    class SelectMenuRenderCb_AlignLeft : public SMOOTH_MENU::SimpleMenuCallback_t
    {
    public:
        void renderCallback(
            const std::vector<SMOOTH_MENU::Item_t*>& menuItemList,
            const SMOOTH_MENU::RenderAttribute_t& selector,
            const SMOOTH_MENU::RenderAttribute_t& camera
        ) override;
    };

    class SelectMenuRenderCb_AlignCenter : public SMOOTH_MENU::SimpleMenuCallback_t
    {
    public:
        void renderCallback(
            const std::vector<SMOOTH_MENU::Item_t*>& menuItemList,
            const SMOOTH_MENU::RenderAttribute_t& selector,
            const SMOOTH_MENU::RenderAttribute_t& camera
        ) override;
    };

    class SelectMenuRenderCb_AlignRight : public SMOOTH_MENU::SimpleMenuCallback_t
    {
    public:
        void renderCallback(
            const std::vector<SMOOTH_MENU::Item_t*>& menuItemList,
            const SMOOTH_MENU::RenderAttribute_t& selector,
            const SMOOTH_MENU::RenderAttribute_t& camera
        ) override;
    };
}