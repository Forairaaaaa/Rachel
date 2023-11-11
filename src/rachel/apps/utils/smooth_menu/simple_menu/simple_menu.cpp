/**
 * @file simple_menu.cpp
 * @author Forairaaaaa
 * @brief 
 * @version 0.1
 * @date 2023-11-10
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#include "simple_menu.h"


namespace SMOOTH_MENU 
{
    Simple_Menu::Simple_Menu(int cameraWidth, int cameraHeight)
    {
        // Create menu 
        _menu = new Menu_t;

        // Create selector 
        _selector = new Selector_t;
        _selector->setMenu(_menu);

        // Create camera 
        _camera = new Camrea_t;
        _camera->setMenu(_menu);
        _camera->setSize(cameraWidth, cameraHeight);

        _render_callback = nullptr;
        _first_open = true;
        _first_item = 0;
    }


    Simple_Menu::~Simple_Menu()
    {
        delete _menu;
        delete _selector;
        delete _camera;
    }


    void Simple_Menu::setMenuLoopMode(bool loopMode)
    {
        _selector->setMenuLoopMode(loopMode);
        _camera->setMenuLoopMode(loopMode);
    }


    void Simple_Menu::update(uint32_t currentTime, bool renderAtOnce)
    {
        /* Return if empty menu */
        if (!_menu->getItemNum())
            return;

        /* Move the selector to the first item */
        if (_first_open) 
        {
            _first_open = false;

            // Set first item
            _selector->reset(currentTime);
            _selector->goToItem(_first_item);
            _camera->goToItem(_first_item);

            _selector->update(0);
        }

        _menu->update(currentTime);
        _selector->update(currentTime, false);
        _camera->update(currentTime, false);


        // If render at once 
        if (renderAtOnce)
            render();
    }


    void Simple_Menu::render()
    {
        if (_render_callback == nullptr)
            return;

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
