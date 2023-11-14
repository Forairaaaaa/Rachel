/**
 * @file app_nes_emulator.h
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
#include "simple_nes/include/Emulator.h"


namespace MOONCAKE::APPS
{
    /**
    * @brief Nes_emulator 
    *
    */
    class AppNes_emulator : public APP_BASE
    {
    private:
        struct Data_t
        {
            sn::Emulator* emulator = nullptr;
        };
        Data_t _data;

    public:
        void onCreate() override;
        void onResume() override;
        void onRunning() override;
        void onDestroy() override;
    };

    class AppNes_emulator_Packer : public APP_PACKER_BASE
    {
        std::string getAppName() override { return "NES Emulator"; }
        void* getAppIcon() override { return (void*)image_data_icon_app_default; }
        void* newApp() override { return new AppNes_emulator; }
        void deleteApp(void *app) override { delete (AppNes_emulator*)app; }
    };
}