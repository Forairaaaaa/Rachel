/**
 * @file launcher.h
 * @author Forairaaaaa
 * @brief 
 * @version 0.1
 * @date 2023-11-04
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#pragma once
#include <cstdint>
#include <mooncake.h>
#include <string>
#include "../utils/smooth_menu/simple_menu/simple_menu.h"


namespace MOONCAKE
{
    namespace APPS
    {
        /**
        * @brief Launcher
        *
        */
        class Launcher : public APP_BASE
        {
        private:
            struct Data_t
            {
                // Clock
                std::string clock;
                uint32_t clock_update_count = 0;
                const uint32_t clock_update_interval = 1000;

                // Menu
                SMOOTH_MENU::Simple_Menu* menu = nullptr;
                SMOOTH_MENU::SimpleMenuCallback_t* menu_render_cb = nullptr;
                uint32_t menu_update_count = 0;
                const uint32_t menu_update_interval = 10;
                // const uint32_t menu_update_interval = 0;
                bool menu_wait_button_released = false;

                // App open and close anim 
                LVGL::Anim_Path app_anim;
            };
            Data_t _data;
            void _update_clock(bool updateNow = false);
            void _create_menu();
            void _update_menu();
            void _destroy_menu();
            void _play_app_anim(bool open);

        public:
            void onCreate() override;
            void onResume() override;
            void onRunning() override;
            void onRunningBG() override;
            void onPause() override;
            void onDestroy() override;
        };

        class Launcher_Packer : public APP_PACKER_BASE
        {
            std::string getAppName() override { return "Launcher"; }
            void* newApp() override { return new Launcher; }
            void deleteApp(void *app) override { delete (Launcher*)app; }
        };
    }
}
