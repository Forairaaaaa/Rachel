/**
 * @file menu.cpp
 * @author Forairaaaaa
 * @brief 
 * @version 0.1
 * @date 2023-11-05
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#include "../launcher.h"
#include "lgfx/v1/lgfx_fonts.hpp"
#include "menu_render_callback.hpp"
#include "spdlog/spdlog.h"


using namespace MOONCAKE::APPS;


void Launcher::_create_menu()
{
    spdlog::info("create menu");



    // Create menu and render callback 
    _data.menu = new SMOOTH_MENU::Simple_Menu;
    _data.menu_render_cb = new LauncherRenderCallBack;

    // Init and set render callback 
    _data.menu->init(HAL::GetCanvas()->width(), HAL::GetCanvas()->height());
    _data.menu->setRenderCallback(_data.menu_render_cb);



    // Set selector anim, in this launcher case, is the icon's moving anim (fixed selector)
    auto cfg_selector = _data.menu->getSelector()->config();
    cfg_selector.animPath_x = LVGL::ease_out;
    cfg_selector.animTime_x = 300;
    _data.menu->getSelector()->config(cfg_selector);
    
    // Set menu open anim 
    auto cfg_menu = _data.menu->getMenu()->config();
    cfg_menu.animPath_open = LVGL::ease_out;
    cfg_menu.animTime_open = 1000;
    _data.menu->getMenu()->config(cfg_menu);



    // Allow selector go loop 
    _data.menu->setMenuLoopMode(true);



    // Get installed app list
    spdlog::info("installed apps num: {}", mcAppGetFramework()->getAppRegister().getInstalledAppNum());
    int i = 0;
    for (const auto& app : mcAppGetFramework()->getAppRegister().getInstalledAppList())
    {
        // Pass the launcher 
        if (app->getAddr() == getAppPacker())
            continue;

        // spdlog::info("app: {} icon: {}", app->getAppName(), app->getAppIcon());
        spdlog::info("push app: {} into menu", app->getAppName());
        
        // Push items into menu, use icon pointer as the item user data
        _data.menu->getMenu()->addItem(
            app->getAppName(),
            THEME_APP_ICON_GAP + i * (THEME_APP_ICON_WIDTH + THEME_APP_ICON_GAP),
            THEME_APP_ICON_MARGIN_TOP,
            THEME_APP_ICON_WIDTH,
            THEME_APP_ICON_HEIGHT,
            app->getAppIcon()
        );
        i++;
    }



    // Setup some widget shit 
    // Pass clock string pointer for redner 
    ((LauncherRenderCallBack*)_data.menu_render_cb)->setClock(&_data.clock);

    // Setup anims
    ((LauncherRenderCallBack*)_data.menu_render_cb)->statusBarAnim.setAnim(LVGL::ease_out, 0, 24, 600);
    ((LauncherRenderCallBack*)_data.menu_render_cb)->statusBarAnim.resetTime(HAL::Millis() + 1000);

    ((LauncherRenderCallBack*)_data.menu_render_cb)->bottomPanelAnim.resetTime(HAL::Millis());
    ((LauncherRenderCallBack*)_data.menu_render_cb)->bottomPanelAnim.setAnim(LVGL::ease_out, 240, 158, 600);
}


void Launcher::_update_menu()
{
    if ((HAL::Millis() - _data.menu_update_count) > _data.menu_update_interval)
    {
        // Update navigation 
        // To last one 
        if (HAL::GetButton(GAMEPAD::BTN_LEFT))
        {
            if (!_data.menu_wait_button_released)
            {
                _data.menu->goLast();
                _data.menu_wait_button_released = true;
            }
        }


        // To next one 
        else if (HAL::GetButton(GAMEPAD::BTN_RIGHT))
        {
            if (!_data.menu_wait_button_released)
            {
                _data.menu->goNext();
                _data.menu_wait_button_released = true;
            }
        }


        // Open app 
        else if (HAL::GetButton(GAMEPAD::BTN_A))
        {
            auto selected_item = _data.menu->getSelector()->getTargetItem();
            // spdlog::info("select: {} try create", selected_item);

            
            // Skip launcher 
            selected_item++;
            // Get packer, apps are arranged by install order, so simply use index is ok  
            auto app_packer = mcAppGetFramework()->getInstalledAppList()[selected_item];
            // spdlog::info("try create app: {}", app_packer->getAppName());


            // Try create and start app 
            if (mcAppGetFramework()->createAndStartApp(app_packer))
            {
                spdlog::info("app: {} opened", app_packer->getAppName());
                closeApp();
            }
            else 
                spdlog::error("open app: {} failed", app_packer->getAppName());
        }


        // Unlock if no button is pressing 
        else
        {
            _data.menu_wait_button_released = false;
        }


        // Update menu
        _data.menu->update(HAL::Millis());

        // Push frame buffer 
        HAL::CanvasUpdate();

        _data.menu_update_count = HAL::Millis();
    }
}


void Launcher::_destroy_menu()
{
    spdlog::info("destroy menu");
    delete _data.menu;
    delete _data.menu_render_cb;
}

