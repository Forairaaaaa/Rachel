/**
 * @file app_ble_controller.h
 * @author Forairaaaaa
 * @brief 
 * @version 0.1
 * @date 2023-11-04
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#include <mooncake.h>
#include "assets/icon_app_ble_gamepad.h"


namespace MOONCAKE::APPS
{
    /**
    * @brief Ble_controller 
    *
    */
    class AppBle_controller : public APP_BASE
    {
    private:
        struct Data_t
        {
            unsigned long count = 0;
        };
        Data_t _data;

    public:
        void onCreate() override;
        void onResume() override;
        void onRunning() override;
        void onDestroy() override;
    };

    class AppBle_controller_Packer : public APP_PACKER_BASE
    {
        std::string getAppName() override { return "Ble Controller"; }
        void* getAppIcon() override { return (void*)image_data_icon_app_ble_gamepad; }
        void* newApp() override { return new AppBle_controller; }
        void deleteApp(void *app) override { delete (AppBle_controller*)app; }
    };
}