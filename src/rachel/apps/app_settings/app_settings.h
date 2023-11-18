/**
 * @file app_settings.h
 * @author Forairaaaaa
 * @brief 
 * @version 0.1
 * @date 2023-11-04
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#include <mooncake.h>
#include "assets/icon_app_settings.hpp"
#include "../../utils/system/ui/ui.h"


namespace MOONCAKE::APPS
{
    /**
    * @brief Settings 
    *
    */
    class AppSettings : public APP_BASE
    {
    private:
        struct Data_t
        {
            bool is_config_changed = false;
            SYSTEM::UI::SelectMenu* select_menu = nullptr;
        };
        Data_t _data;
        void _page_index();
        void _page_power();
        void _page_sound();
        void _page_display();
        void _page_time();
        void _page_about();

    public:
        void onCreate() override;
        void onResume() override;
        void onRunning() override;
        void onDestroy() override;
    };

    class AppSettings_Packer : public APP_PACKER_BASE
    {
        std::string getAppName() override { return "Settings"; }
        void* getAppIcon() override { return (void*)image_data_icon_app_settings; }
        void* newApp() override { return new AppSettings; }
        void deleteApp(void *app) override { delete (AppSettings*)app; }
    };
}