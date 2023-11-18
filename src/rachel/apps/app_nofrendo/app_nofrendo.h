/**
 * @file app_nofrendo.h
 * @author Forairaaaaa
 * @brief 
 * @version 0.1
 * @date 2023-11-04
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#include <mooncake.h>
#include "assets/icon_app_nofrendo.hpp"


namespace MOONCAKE::APPS
{
    /**
    * @brief Nofrendo 
    *
    */
    class AppNofrendo : public APP_BASE
    {
    public:
        void onCreate() override;
        void onResume() override;
        void onRunning() override;
        void onDestroy() override;
    };

    class AppNofrendo_Packer : public APP_PACKER_BASE
    {
        std::string getAppName() override { return "Nofrendo"; }
        void* getAppIcon() override { return (void*)image_data_icon_app_nofrendo; }
        void* newApp() override { return new AppNofrendo; }
        void deleteApp(void *app) override { delete (AppNofrendo*)app; }
    };
}