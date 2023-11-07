/**
 * @file camera.cpp
 * @author Forairaaaaa
 * @brief 
 * @version 0.1
 * @date 2023-06-10
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#include "camera.h"


namespace SMOOTH_MENU {


    void Camrea_t::update(uint32_t currentTime, bool renderAtOnce)
    {
        /* If target changed */
        if (_item_status.changed) {
            _item_status.changed = false;

            /* Keep target inside [x, x + width], [y, y + height] */
            
            /* Postion X */
            if (_current_menu->getItemList()[_item_status.target]->x < _anim_cntr.x.getValue(currentTime)) {
                /* Reset anim to target */
                _anim_cntr.x.setAnim(
                    _cfg.animPath_x,
                    _anim_cntr.x.getValue(currentTime),
                    _current_menu->getItemList()[_item_status.target]->x,
                    _cfg.animTime_x
                    );
                _anim_cntr.x.resetTime(currentTime);
            }
            else if ((_current_menu->getItemList()[_item_status.target]->x + _current_menu->getItemList()[_item_status.target]->width) > (_anim_cntr.x.getValue(currentTime) + _width)) {
                /* Reset anim to target */
                _anim_cntr.x.setAnim(
                    _cfg.animPath_x,
                    _anim_cntr.x.getValue(currentTime),
                    // _current_menu->getItemList()[_item_status.target]->x - _width + _current_menu->getItemList()[_item_status.target]->width,       // Align Right
                    _current_menu->getItemList()[_item_status.target]->x,       // Align Left
                    _cfg.animTime_x
                    );
                _anim_cntr.x.resetTime(currentTime);
            }


            /* Postion Y */
            if (_current_menu->getItemList()[_item_status.target]->y < _anim_cntr.y.getValue(currentTime)) {
                /* Reset anim to target */
                _anim_cntr.y.setAnim(
                    _cfg.animPath_y,
                    _anim_cntr.y.getValue(currentTime),
                    _current_menu->getItemList()[_item_status.target]->y,
                    _cfg.animTime_y
                    );
                _anim_cntr.y.resetTime(currentTime);
            }
            else if ((_current_menu->getItemList()[_item_status.target]->y + _current_menu->getItemList()[_item_status.target]->height) > (_anim_cntr.y.getValue(currentTime) + _height)) {
                /* Reset anim to target */
                _anim_cntr.y.setAnim(
                    _cfg.animPath_y,
                    _anim_cntr.y.getValue(currentTime),
                    _current_menu->getItemList()[_item_status.target]->y - _height + _current_menu->getItemList()[_item_status.target]->height,     // Align Down
                    _cfg.animTime_y
                    );
                _anim_cntr.y.resetTime(currentTime);
            }

        }

        /* Update current time */
        _anim_cntr.currentTime = currentTime;

        /* Render menu and selector */
        if (renderAtOnce) {
            render();
        }
    }


    void Camrea_t::render(bool renderMenu)
    {
        /* Render selector */
        if (_render_callback != nullptr) {
            _render_callback->renderCallback(
                _anim_cntr.x.getValue(_anim_cntr.currentTime),
                _anim_cntr.y.getValue(_anim_cntr.currentTime),
                _width,
                _height
            );
        }

        /* Render menu */
        if (renderMenu) {
            _current_menu->render();
        }
    }


    const RenderAttribute_t& Camrea_t::getRenderAttribute()
    {
        _render_attribute_buffer.x = _anim_cntr.x.getValue(_anim_cntr.currentTime);
        _render_attribute_buffer.y = _anim_cntr.y.getValue(_anim_cntr.currentTime);
        _render_attribute_buffer.width = _width;
        _render_attribute_buffer.height = _height;

        return _render_attribute_buffer;
    }


}

