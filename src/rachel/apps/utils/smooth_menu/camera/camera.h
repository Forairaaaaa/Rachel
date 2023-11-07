/**
 * @file camera.h
 * @author Forairaaaaa
 * @brief 
 * @version 0.1
 * @date 2023-06-10
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#pragma once
#include "../lv_anim/lv_anim.h"
#include "../selector/selector.h"


namespace SMOOTH_MENU {


    class Camrea_t : public Selector_t {
        private:
            int _width;
            int _height;


        public:
            Camrea_t() :
                _width(0),
                _height(0)
                { }
            ~Camrea_t() = default;


            inline void setSize(int width, int height) { _width = width; _height = height; }


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
             * @brief Get render attribute for rendering
             * 
             * @return const RenderAttribute_t& 
             */
            const RenderAttribute_t& getRenderAttribute();

    };



}
