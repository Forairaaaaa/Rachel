/**
 * @file menu.cpp
 * @author Forairaaaaa
 * @brief 
 * @version 0.1
 * @date 2023-06-09
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#include "menu.h"


namespace SMOOTH_MENU {


    Menu_t::Menu_t()
    {
        _render_callback = nullptr;
        _is_menu = true;

        {
            MENU::AnimContainer_t default_anim_cntr;
            MENU::Config_t default_cfg;
            _anim_cntr = default_anim_cntr;
            _cfg = default_cfg;
        }
    }


    int Menu_t::addItem(Item_t* item)
    {
        /* If null pointer */
        if (item == nullptr) {
            return -1;
        }

        /* Get ID */
        item->id = _item_list.size();

        /* Push into list */
        _item_list.push_back(item);

        return item->id;
    }


    int Menu_t::addItem(std::string tag, int x, int y, int width, int height, void* userData)
    {
        Item_t* new_item = new Item_t;

        new_item->tag = tag;
        new_item->x = x + this->x;
        new_item->y = y + this->y;
        new_item->width = width;
        new_item->height = height;
        new_item->userData = userData;

        new_item->x_target = x;
        new_item->y_target = y;
        
        return addItem(new_item);
    }


    int Menu_t::addItemVertically(std::string tag, int width, int height, int x, void* userData)
    {
        int y;
        if (_item_list.size() == 0) {
            y = 0;
        }
        else {
            y = _item_list[_item_list.size() - 1]->y + _item_list[_item_list.size() - 1]->height - this->y;
        }

        return addItem(tag, x, y, width, height, userData);
    }


    int Menu_t::addItemHorizontally(std::string tag, int width, int height, int y, void* userData)
    {
        int x;
        if (_item_list.size() == 0) {
            x = 0;
        }
        else {
            x = _item_list[_item_list.size() - 1]->x + _item_list[_item_list.size() - 1]->width - this->x;
        }

        return addItem(tag, x, y, width, height, userData);
    }


    void Menu_t::clearAllItem()
    {
        /* Free list */
        std::vector<Item_t*>().swap(_item_list);
    }


    void Menu_t::render()
    {
        if (_render_callback == nullptr) {
            return;
        }

        /* Iterate item list */
        for (int i = 0; i < _item_list.size(); i++) {
            _render_callback->renderCallback(_item_list[i]);
        }
    }


    void Menu_t::update(uint32_t currentTime)
    {
        if (!_is_opened) {
            _is_opened = true;
            _anim_cntr.open.resetTime(currentTime);
        }


        if (_anim_cntr.open.isFinished(currentTime)) {
            return;
        }


        /* Iterate item list */
        for (int i = 0; i < _item_list.size(); i++) {
            _anim_cntr.open.setAnim(_cfg.animPath_open, 0, _item_list[i]->x_target, _cfg.animTime_open);
            _item_list[i]->x = _anim_cntr.open.getValue(_anim_cntr.currentTime);
            _anim_cntr.open.setAnim(_cfg.animPath_open, 0, _item_list[i]->y_target, _cfg.animTime_open);
            _item_list[i]->y = _anim_cntr.open.getValue(_anim_cntr.currentTime);
        }


        /* Update current time */
        _anim_cntr.currentTime = currentTime;
    }


    void Menu_t::open()
    {


    }


    void Menu_t::close()
    {

    }


}
