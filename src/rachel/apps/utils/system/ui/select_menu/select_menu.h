/**
 * @file select_menu.h
 * @author Forairaaaaa
 * @brief 
 * @version 0.1
 * @date 2023-11-10
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#pragma once
#include "../../../smooth_menu/simple_menu/simple_menu.h"
#include <iostream>
#include <string>
#include <vector>


namespace SYSTEM::UI
{
    /**
     * @brief Select menu, 选择菜单 
     * 
     */
    class SelectMenu
    {
    public:
        enum ItemsAlignment_t
        {
            ALIGN_LEFT = 0,
            ALIGN_CENTER,
            ALIGN_RIGHT,
        };

        struct Config_t
        {
            int first_item = 1;
            uint32_t menu_update_interval = 10;

            LVGL::LV_ANIM_PATH_t menu_open_anim_path = LVGL::ease_out;
            int32_t menu_open_anim_time = 400;

            LVGL::LV_ANIM_PATH_t selector_anim_path = LVGL::ease_out;
            int32_t selector_anim_time = 100;
            bool selector_can_go_loop = true;

            LVGL::LV_ANIM_PATH_t camera_anim_path = LVGL::ease_out;
            int32_t camera_anim_time = 400;

            ItemsAlignment_t items_alignment = ALIGN_LEFT;
        };
        
    private:
        struct Data_t
        {
            SMOOTH_MENU::Simple_Menu* menu = nullptr;
            SMOOTH_MENU::SimpleMenuCallback_t* render_cb = nullptr;
            uint32_t menu_update_count = 0;
            bool menu_wait_button_released = false;
        };
        Data_t _data;
        Config_t _config;
        void _load_config();
        void _create_menu(std::vector<std::string>& itemList);
        void _destroy_menu();

    public:
        inline Config_t getConfig() { return _config; }
        inline void setConfig(Config_t cfg) { _config = cfg; }
        inline void setItemAlignment(ItemsAlignment_t alignment) { _config.items_alignment = alignment; }
        

        /**
         * @brief Render the menu and blocked untill item selected, 渲染一个菜单并等待选择 
         * 
         * @param itemList Items to be select, the first element will be "title", which will not be selected 
         * @return int selected item index 
         */
        int waitResult(std::vector<std::string>& itemList);
        inline int waitResult(std::vector<std::string>& itemList, ItemsAlignment_t alignment) { setItemAlignment(alignment); return waitResult(itemList); }
    };
}
