/**
 * @file selector.h
 * @author Forairaaaaa
 * @brief 
 * @version 0.1
 * @date 2023-06-09
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#pragma once
#include "../lv_anim/lv_anim.h"
#include "../menu/menu.h"


namespace SMOOTH_MENU {


    struct RenderAttribute_t {
        int x;
        int y;
        int width;
        int height;

        int targetItem;
    };


    struct SelectorRenderCallback_t {
        virtual void renderCallback(int x, int y, int width, int height) { }
    };


    namespace SELECTOR {


        struct Config_t {
            LVGL::LV_ANIM_PATH_t animPath_x = LVGL::ease_out;
            LVGL::LV_ANIM_PATH_t animPath_y = LVGL::ease_out;
            LVGL::LV_ANIM_PATH_t animPath_width = LVGL::overshoot;
            LVGL::LV_ANIM_PATH_t animPath_height = LVGL::ease_out;

            int32_t animTime_x = 100;
            int32_t animTime_y = 100;
            int32_t animTime_width = 400;
            int32_t animTime_height = 100;

            bool menuLoopMode = true;
        };


        struct AnimContainer_t {
            LVGL::Anim_Path x;
            LVGL::Anim_Path y;
            LVGL::Anim_Path width;
            LVGL::Anim_Path height;
            uint32_t currentTime = 0;
        };


        struct ItemStatus_t {
            int current = 0;
            int target = 0;
            bool changed = false;
        };


    };


    class Selector_t {
        protected:
            SELECTOR::Config_t _cfg;
            SELECTOR::AnimContainer_t _anim_cntr;
            SELECTOR::ItemStatus_t _item_status;

            Menu_t* _current_menu;
            SelectorRenderCallback_t* _render_callback;
            RenderAttribute_t _render_attribute_buffer;

            void _reset_anim_time();


        public:
            Selector_t();
            ~Selector_t() = default;


            inline void config(SELECTOR::Config_t cfg) { _cfg = cfg; }
            inline SELECTOR::Config_t config(void) { return _cfg; }


            inline unsigned int getCurrentItem() { return _item_status.current; }
            inline unsigned int getTargetItem() { return _item_status.target; }
            inline bool isTargetChanged() { return _item_status.changed; }
            inline Menu_t* getMenu() { return _current_menu; }
            inline SELECTOR::AnimContainer_t* getAnimCntr() { return &_anim_cntr; }
            inline void setMenuLoopMode(bool loopMode) { _cfg.menuLoopMode = loopMode; }


            /**
             * @brief Set menu that selector base on
             * 
             * @param menu 
             */
            void setMenu(Menu_t* menu);


            /**
             * @brief Go to item, 0 ~ (getItemNum() - 1)
             * 
             * @param targetItem 
             */
            void goToItem(int targetItem);


            /**
             * @brief Go to last one
             * 
             */
            void goLast();


            /**
             * @brief Go to next one
             * 
             */
            void goNext();


            /**
             * @brief Press
             * 
             */
            void pressed();


            /**
             * @brief Release
             * 
             */
            void released();


            /**
             * @brief Set the Render Callback function, for your graphics lib
             * 
             * @param callback 
             */
            inline void setRenderCallback(SelectorRenderCallback_t* callback) { _render_callback = callback; }


            /**
             * @brief Uptate anim value 
             * 
             * @param currentTime 
             * @param render 
             */
            void update(uint32_t currentTime, bool renderAtOnce = true);


            /**
             * @brief Render selector at once 
             * 
             * @param renderMenu 
             */
            void render(bool renderMenu = true);


            /**
             * @brief Check if anim is finished
             * 
             * @return true 
             * @return false 
             */
            bool isAnimFinished();


            /**
             * @brief Get render attribute for rendering
             * 
             * @return const RenderAttribute_t& 
             */
            const RenderAttribute_t& getRenderAttribute();



    };


}
