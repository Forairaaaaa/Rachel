/**
 * @file simple_menu.cpp
 * @author Forairaaaaa
 * @brief 
 * @version 0.1
 * @date 2023-06-10
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#include "simple_menu.h"


namespace SMOOTH_MENU {


    void Simple_Menu::setMenuLoopMode(bool loopMode)
    {
        _selector->setMenuLoopMode(loopMode);
        _camera->setMenuLoopMode(loopMode);
    }


    void Simple_Menu::init(Menu_t* menu, Selector_t* selector, Camrea_t* camera)
    {
        /* Init menu */
        if (menu == nullptr) {
            _menu = new Menu_t;
        }
        else {
            _menu = menu;
        }

        /* Init selector */
        if (selector == nullptr) {
            _selector = new Selector_t;
        }
        else {
            _selector = selector;
        }
        _selector->setMenu(_menu);

        /* Init camera */
        if (camera == nullptr) {
            _camera = new Camrea_t;
        }
        else {
            _camera = camera;
        }
        _camera->setMenu(_menu);
    }


    void Simple_Menu::update(uint32_t currentTime, bool renderAtOnce)
    {
        /* Return if empty menu */
        if (!_menu->getItemNum()) {
            return;
        }

        /* Move the selector to the first item */
        if (_first_open) {
            _first_open = false;
            _selector->goToItem(1);
            _selector->update(0);
        }

        _menu->update(currentTime);
        _selector->update(currentTime, false);
        _camera->update(currentTime, false);


        /* Render simple menu */
        if (renderAtOnce) {
            render();
        }
    }


    void Simple_Menu::render()
    {
        if (_render_callback == nullptr) {
            return;
        }

        _render_callback->renderCallback(
            _menu->getItemList(),
            _selector->getRenderAttribute(),
            _camera->getRenderAttribute()
        );

    }


    void Simple_Menu::goLast()
    {
        _selector->goLast();
        _camera->goLast();
    }


    void Simple_Menu::goNext()
    {
        _selector->goNext();
        _camera->goNext();
    }


}
