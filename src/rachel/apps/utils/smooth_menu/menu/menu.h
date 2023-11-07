/**
 * @file menu.h
 * @author Forairaaaaa
 * @brief 
 * @version 0.1
 * @date 2023-06-09
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#pragma once
#include <iostream>
#include <vector>
#include <string>
#include "../lv_anim/lv_anim.h"


namespace SMOOTH_MENU {


    struct Item_t {
        public:
            /* Attributes */
            std::string tag;
            void* userData = nullptr;
            int id = 0;
            
            int x = 0;
            int y = 0;
            int width = 0;
            int height = 0;


        /* For menu used */
        public:
            inline bool isMenu() { return _is_menu; }
            virtual void open() { }
            virtual void close() { }
            int x_target = 0;
            int y_target = 0;
        protected:
            bool _is_menu = false;
            bool _is_opened = false;
            
    };


    struct MenuRenderCallback_t {
        virtual void renderCallback(const Item_t* item) { }
    };


    namespace MENU {

        struct Config_t {
            LVGL::LV_ANIM_PATH_t animPath_open = LVGL::ease_out;
            int32_t animTime_open = 400;
        };

        struct AnimContainer_t {
            LVGL::Anim_Path open;
            uint32_t currentTime = 0;
            bool isFinished = false;
        };

    }


    class Menu_t : public Item_t {
        private:
            std::vector<Item_t*> _item_list;
            MenuRenderCallback_t* _render_callback;

            MENU::Config_t _cfg;
            MENU::AnimContainer_t _anim_cntr;


        public:
            Menu_t();
            ~Menu_t() = default;


            inline void config(MENU::Config_t cfg) { _cfg = cfg; }
            inline MENU::Config_t config(void) { return _cfg; }


            inline void setTag(std::string tag) { this->tag = tag; }
            inline void setPostion(int x, int y) { this->x = x; this->y = y; }


            /**
             * @brief Get the Item List
             * 
             * @return std::vector<Item_t*> 
             */
            inline const std::vector<Item_t*>& getItemList() { return _item_list; }


            /**
             * @brief Add item into item list
             * 
             * @param tag 
             * @param x 
             * @param y 
             * @param width 
             * @param height 
             * @param userData 
             * @return int 
             */
            int addItem(std::string tag, int x, int y, int width, int height, void* userData = nullptr);


            /**
             * @brief Add item into item list
             * 
             * @param item 
             * @return int Item ID
             */
            int addItem(Item_t* item);


            /**
             * @brief Add item into menu vertically, automatically append Y
             * 
             * @param tag 
             * @param width 
             * @param height 
             * @param userData 
             * @return int 
             */
            int addItemVertically(std::string tag, int width, int height, int x = 0, void* userData = nullptr);


            /**
             * @brief Add item into menu horizontally, automatically append X
             * 
             * @param tag 
             * @param y 
             * @param width 
             * @param height 
             * @param userData 
             * @return ine 
             */
            int addItemHorizontally(std::string tag, int width, int height, int y = 0, void* userData = nullptr);


            /**
             * @brief Get the number of item in the menu
             * 
             * @return size_t 
             */
            inline size_t getItemNum() { return _item_list.size(); }


            /**
             * @brief Remove all items in menu
             * 
             */
            void clearAllItem();


            /**
             * @brief Set the Render Callback function, for your graphics lib
             * 
             * @param callback 
             */
            inline void setRenderCallback(MenuRenderCallback_t* callback) { _render_callback = callback; }


            /**
             * @brief Render menu at once
             * 
             */
            void render();


            /**
             * @brief Update menu anim
             * 
             * @param currentTime 
             */
            void update(uint32_t currentTime);



            void open();


            void close();



    };








}

