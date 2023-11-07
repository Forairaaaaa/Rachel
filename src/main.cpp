/**
 * @file main.cpp
 * @author Forairaaaaa
 * @brief 
 * @version 0.1
 * @date 2023-11-07
 * 
 * @copyright Copyright (c) 2023
 * 
 */
// Include befor Arduino.h to avoid compile error 
#include <mooncake.h>
#include <Arduino.h>


using namespace MOONCAKE;
Mooncake mooncake;


// A app class to override life cycle methods 
class AppExample : public APP_BASE
{
private:
        uint32_t count;
public:
    void onCreate() override
    {
        spdlog::info("{} onCreate", getAppName());
        count = millis();
    }

    void onResume() override
    {
        spdlog::info("{} onResume", getAppName());
    }

    void onRunning() override
    {
        if (millis() - count > 1000)
        {
            spdlog::info("{} onRunning", getAppName());
            count = millis();
        }
    }
};


// A app packer to store static resource and memory management 
class AppExample_packer : public APP_PACKER_BASE
{
    public:
    std::string getAppName() override { return "AppExample"; }
    void * newApp() override { return new AppExample; }
    void deleteApp(void *app) override { delete (AppExample*)app; }
};


void setup()
{
    delay(3000);
    
    // Init framework 
    mooncake.init();

    // Install app with app packer 
    mooncake.installApp(new AppExample_packer);

    // We can get a list of installed apps from app register 
    auto installed_apps_list = mooncake.getAppRegister().getInstalledAppList();
    spdlog::info("first installed app's name is {}", installed_apps_list[0]->getAppName());

    // Now let create and start an app with the installed app packer
    mooncake.createAndStartApp(installed_apps_list[0]);
}


void loop()
{
    // Keep dispatcher running 
    mooncake.update();
}
