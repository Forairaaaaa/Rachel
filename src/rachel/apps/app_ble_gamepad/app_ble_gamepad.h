/**
 * @file app_ble_gamepad.h
 * @author Forairaaaaa
 * @brief 
 * @version 0.1
 * @date 2023-11-19
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#include <mooncake.h>
#include "assets/icon_app_ble_gamepad.hpp"


namespace MOONCAKE::APPS
{
    /**
    * @brief Ble_controller 
    *
    */
    class AppBle_gamepad : public APP_BASE
    {
    public:
        void onCreate() override;
        void onResume() override;
        void onRunning() override;
        void onDestroy() override;
    };

    class AppBle_gamepad_Packer : public APP_PACKER_BASE
    {
        std::string getAppName() override { return "Ble Gamepad"; }
        void* getAppIcon() override { return (void*)image_data_icon_app_ble_gamepad; }
        void* newApp() override { return new AppBle_gamepad; }
        void deleteApp(void *app) override { delete (AppBle_gamepad*)app; }
    };
}