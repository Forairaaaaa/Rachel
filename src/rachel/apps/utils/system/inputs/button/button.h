/**
 * @file button.h
 * @author Forairaaaaa
 * @brief Base on https://github.com/madleech/Button, thanks to madleech
 * @version 0.1
 * @date 2023-11-18
 * 
 * @copyright Copyright (c) 2023
 * 
 */

/*
	Button - a small library for Arduino to handle button debouncing
	
	MIT licensed.
*/

#ifndef Button_h
#define Button_h
#include "../../../hal/hal.h"


namespace SYSTEM::INPUTS
{
    /**
     * @brief Simple but supper useful button class 
     * 
     */
    class Button
    {
    public:
        Button(GAMEPAD::GamePadButton_t button, uint16_t debounce_ms = 50) :
            _button(button),
            _delay(debounce_ms),
            _state(false),
            _ignore_until(0),
            _has_changed(false)
            {}
        bool read();
        bool toggled();
        bool pressed();
        bool released();
        bool has_changed();
        
        const static bool PRESSED = true;
        const static bool RELEASED = false;
    
    private:
        GAMEPAD::GamePadButton_t _button;
        uint16_t _delay;
        bool     _state;
        uint32_t _ignore_until;
        bool     _has_changed;
    };
}

#endif
