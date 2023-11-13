/**
 * @file app_raylibgames.h
 * @author Forairaaaaa
 * @brief 
 * @version 0.1
 * @date 2023-11-04
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#include <mooncake.h>
#include "assets/icon_app_raylib_games.h"


namespace MOONCAKE::APPS
{
    /**
    * @brief Raylibgames 
    *
    */
    class AppRaylibgames : public APP_BASE
    {
    public:
        void onCreate() override;
        void onResume() override;
        void onRunning() override;
        void onDestroy() override;
    };

    class AppRaylibgames_Packer : public APP_PACKER_BASE
    {
        std::string getAppName() override { return "Raylib Games"; }
        void* getAppIcon() override { return (void*)image_data_icon_app_raylib_games; }
        void* newApp() override { return new AppRaylibgames; }
        void deleteApp(void *app) override { delete (AppRaylibgames*)app; }
    };
}