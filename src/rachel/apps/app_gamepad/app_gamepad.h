/**
 * @file app_gamepad.h
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
    * @brief Gamepad 
    *
    */
    class AppGamepad : public APP_BASE
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

    class AppGamepad_Packer : public APP_PACKER_BASE
    {
        std::string getAppName() override { return "Controller"; }
        void * getAppIcon() override { return (void*)image_data_icon_app_ble_gamepad; }
        void *newApp() override { return new AppGamepad; }
        void deleteApp(void *app) override { delete (AppGamepad*)app; }
    };
}