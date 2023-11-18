/**
 * @file select_menu.cpp
 * @author Forairaaaaa
 * @brief 
 * @version 0.1
 * @date 2023-11-10
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#include "select_menu.h"
#include "../../../../../hal/hal.h"
#include "components/render_callbacks.h"


using namespace SYSTEM::UI;


void SelectMenu::_create_menu(std::vector<std::string>& itemList)
{
    // Create menu 
    _data.menu = new SMOOTH_MENU::Simple_Menu(HAL::GetCanvas()->width(), HAL::GetCanvas()->height());    

    // Push items into menu 
    int text_width = 12;
    int text_height = 24;
    for (int i = 0; i < itemList.size(); i++) 
    {
        _data.menu->getMenu()->addItem(
            itemList[i].c_str(),
            10,
            10 + (text_height + 5) * i,
            text_width * itemList[i].size(),
            text_height
        );
    }

    // Set render callback 
    if (_config.items_alignment == ALIGN_LEFT)
        _data.render_cb = new SelectMenuRenderCb_AlignLeft;
    else if (_config.items_alignment == ALIGN_CENTER)
        _data.render_cb = new SelectMenuRenderCb_AlignCenter;
    else if (_config.items_alignment == ALIGN_RIGHT)
        _data.render_cb = new SelectMenuRenderCb_AlignRight;
    else
        _data.render_cb = new SelectMenuRenderCb_AlignLeft;

    _data.menu->setRenderCallback(_data.render_cb);
}


void SelectMenu::_destroy_menu()
{
    delete _data.menu;
    delete _data.render_cb;
}


void SelectMenu::_load_config()
{
    // Load font 
    HAL::LoadLauncherFont24();

    // Configs 
    _data.menu->setFirstItem(_config.first_item);
    _data.menu->setMenuLoopMode(_config.selector_can_go_loop);
    {
        auto cfg = _data.menu->getMenu()->config();
        cfg.animPath_open = _config.menu_open_anim_path;
        cfg.animTime_open = _config.menu_open_anim_time;
        _data.menu->getMenu()->config(cfg);
    }
    {
        auto cfg = _data.menu->getSelector()->config();
        cfg.animPath_y = _config.selector_anim_path;
        cfg.animTime_y = _config.selector_anim_time;
        _data.menu->getSelector()->config(cfg);
    }
    {
        auto cfg = _data.menu->getCamera()->config();
        cfg.animPath_y = _config.camera_anim_path;
        cfg.animTime_y = _config.camera_anim_time;
        _data.menu->getCamera()->config(cfg);
    }
}


int SelectMenu::waitResult(std::vector<std::string>& itemList)
{
    _create_menu(itemList);
    _load_config();

    while (1)
    {
        if ((HAL::Millis() - _data.menu_update_count) > _config.menu_update_interval)
        {
            // Update navigation 
            if (HAL::GetButton(GAMEPAD::BTN_UP) || HAL::GetButton(GAMEPAD::BTN_LEFT))
            {
                if (!_data.menu_wait_button_released)
                {
                    _data.menu->goLast();
                    _data.menu_wait_button_released = true;
                }
            }
            else if (HAL::GetButton(GAMEPAD::BTN_DOWN) || HAL::GetButton(GAMEPAD::BTN_RIGHT))
            {
                if (!_data.menu_wait_button_released)
                {
                    _data.menu->goNext();
                    _data.menu_wait_button_released = true;
                }
            }

            // If select 
            else if (HAL::GetButton(GAMEPAD::BTN_A) || HAL::GetButton(GAMEPAD::BTN_LEFT_STICK))
            {
                _data.menu->getSelector()->pressed();
                // Wait release 
                while (HAL::GetButton(GAMEPAD::BTN_A) || HAL::GetButton(GAMEPAD::BTN_LEFT_STICK))
                {
                    _data.menu->update(HAL::Millis());
                    HAL::CanvasUpdate();
                }
                _data.menu->getSelector()->released();

                // Wait anim finish 
                while (!_data.menu->getSelector()->isAnimFinished())
                {
                    _data.menu->update(HAL::Millis());
                    HAL::CanvasUpdate();
                }

                // If not title 
                if (_data.menu->getSelector()->getTargetItem() != 0)
                {
                    int selected_index = _data.menu->getSelector()->getTargetItem();
                    _destroy_menu();
                    return selected_index;
                }
            }

            // Unlock if no button is pressing 
            else
            {
                _data.menu_wait_button_released = false;
            }

            // Render and push frame  
            _data.menu->update(HAL::Millis());
            HAL::CanvasUpdate();

            _data.menu_update_count = HAL::Millis();
        }
        else 
        {
            HAL::Delay(5);
        }
    }
}

