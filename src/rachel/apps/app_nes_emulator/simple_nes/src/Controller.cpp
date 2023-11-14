#include "../include/Controller.h"

namespace sn
{
    Controller::Controller() :
        m_keyStates(0),
        m_keyBindings(TotalButtons)
    {
//         m_keyBindings[A] = sf::Keyboard::J;
//         m_keyBindings[B] = sf::Keyboard::K;
//         m_keyBindings[Select] = sf::Keyboard::RShift;
//         m_keyBindings[Start] = sf::Keyboard::Return;
//         m_keyBindings[Up] = sf::Keyboard::W;
//         m_keyBindings[Down] = sf::Keyboard::S;
//         m_keyBindings[Left] = sf::Keyboard::A;
//         m_keyBindings[Right] = sf::Keyboard::D;

        m_keyBindings[A]        = GAMEPAD::BTN_A;
        m_keyBindings[B]        = GAMEPAD::BTN_B;
        m_keyBindings[Select]   = GAMEPAD::BTN_SELECT;
        m_keyBindings[Start]    = GAMEPAD::BTN_START;
        m_keyBindings[Up]       = GAMEPAD::BTN_UP;
        m_keyBindings[Down]     = GAMEPAD::BTN_DOWN;
        m_keyBindings[Left]     = GAMEPAD::BTN_LEFT;
        m_keyBindings[Right]    = GAMEPAD::BTN_RIGHT;
    }

    // void Controller::setKeyBindings(const std::vector<sf::Keyboard::Key>& keys)
    // {
    //     m_keyBindings = keys;
    // }

    void Controller::strobe(Byte b)
    {
        m_strobe = (b & 1);
        if (!m_strobe)
        {
            m_keyStates = 0;
            int shift = 0;
            for (int button = A; button < TotalButtons; ++button)
            {
                // m_keyStates |= (sf::Keyboard::isKeyPressed(m_keyBindings[static_cast<Buttons>(button)]) << shift);
                m_keyStates |= (HAL::GetButton(m_keyBindings[static_cast<Buttons>(button)]) << shift);
                ++shift;
            }
        }
    }

    Byte Controller::read()
    {
        Byte ret;
        if (m_strobe)
        {
            // ret = sf::Keyboard::isKeyPressed(m_keyBindings[A]);
            ret = HAL::GetButton(GAMEPAD::BTN_A);
        }
        else
        {
            ret = (m_keyStates & 1);
            m_keyStates >>= 1;
        }
        return ret | 0x40;
    }

}