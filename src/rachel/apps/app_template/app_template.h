/**
 * @file app_template.h
 * @author Forairaaaaa
 * @brief 
 * @version 0.1
 * @date 2023-11-04
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#include <mooncake.h>
#include "../assets/icons/icons.h"


namespace MOONCAKE::APPS
{
    /**
    * @brief Template 
    *
    */
    class AppTemplate : public APP_BASE
    {
    private:
        struct Data_t
        {
            unsigned long count = 0;
        };
        Data_t _data;

    public:
        void onResume() override;
        void onRunning() override;
        void onDestroy() override;
    };

    class AppTemplate_Packer : public APP_PACKER_BASE
    {
        std::string getAppName() override { return "Template"; }
        void* getAppIcon() override { return (void*)image_data_icon_app_default; }
        void* newApp() override { return new AppTemplate; }
        void deleteApp(void *app) override { delete (AppTemplate*)app; }
    };
}