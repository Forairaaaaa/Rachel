/**
 * @file button.cpp
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

#include "button.h"
#include "../../../hal/hal.h"


using namespace SYSTEM::INPUTS;


// 
// public methods
// 

bool Button::read()
{
	// ignore pin changes until after this delay time
	if (_ignore_until > HAL::Millis())
	{
		// ignore any changes during this period
	}
	
	// pin has changed 
	else if (HAL::GetButton(_button) != _state)
	{
		_ignore_until = HAL::Millis() + _delay;
		_state = !_state;
		_has_changed = true;
	}
	
	return _state;
}


// has the button been toggled from on -> off, or vice versa
bool Button::toggled()
{
	read();
	return has_changed();
}


// mostly internal, tells you if a button has changed after calling the read() function
bool Button::has_changed()
{
	if (_has_changed)
	{
		_has_changed = false;
		return true;
	}
	return false;
}


// has the button gone from off -> on
bool Button::pressed()
{
	return (read() == PRESSED && has_changed());
}


// has the button gone from on -> off
bool Button::released()
{
	return (read() == RELEASED && has_changed());
}
