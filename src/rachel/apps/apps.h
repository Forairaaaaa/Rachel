/**
 * @file apps.h
 * @author Forairaaaaa
 * @brief 
 * @version 0.1
 * @date 2023-11-04
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#pragma once
#include "launcher/launcher.h"
#include "app_template/app_template.h"
#include "app_settings/app_settings.h"
#include "app_gamepad/app_gamepad.h"
#include "app_screencast/app_screencast.h"
#include "app_music/app_music.h"
#include "app_genshin/app_genshin.h"
#include "app_gbemulator/app_gbemulator.h"
#include "app_raylibgames/app_raylibgames.h"
/* Header files locator(Don't remove) */


void rachel_app_install_callback(MOONCAKE::Mooncake* mooncake)
{
    mooncake->installApp(new MOONCAKE::APPS::AppSettings_Packer);
    mooncake->installApp(new MOONCAKE::APPS::AppGamepad_Packer);
    mooncake->installApp(new MOONCAKE::APPS::AppScreencast_Packer);
    mooncake->installApp(new MOONCAKE::APPS::AppRaylibgames_Packer);
    mooncake->installApp(new MOONCAKE::APPS::AppGbemulator_Packer);
    mooncake->installApp(new MOONCAKE::APPS::AppMusic_Packer);
    mooncake->installApp(new MOONCAKE::APPS::AppGenshin_Packer);
    /* Install app locator(Don't remove) */
}
