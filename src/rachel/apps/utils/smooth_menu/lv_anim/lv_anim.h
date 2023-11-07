/**
 * @file lv_anim.h
 * @author Forairaaaaa
 * @brief Wrap of lvgl anim path part: https://github.com/lvgl/lvgl
 * @version 0.1
 * @date 2023-06-09
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#pragma once
#include <stdint.h>


namespace LVGL {

    /* --------------------------------------------- C API --------------------------------------------- */

    /** Describes an animation*/
    typedef struct _lv_anim_t {

        int32_t start_value;            /**< Start value*/
        int32_t end_value;              /**< End value*/
        int32_t time;                   /**< Animation time in ms*/
        int32_t act_time;               /**< Current time in animation. Set to negative to make delay.*/

    } lv_anim_t;


    /** Get the current value during an animation*/
    typedef int32_t (*lv_anim_path_cb_t)(const struct _lv_anim_t *);


    int32_t lv_anim_path_linear(const lv_anim_t * a);
    int32_t lv_anim_path_ease_in(const lv_anim_t * a);
    int32_t lv_anim_path_ease_out(const lv_anim_t * a);
    int32_t lv_anim_path_ease_in_out(const lv_anim_t * a);
    int32_t lv_anim_path_overshoot(const lv_anim_t * a);
    int32_t lv_anim_path_bounce(const lv_anim_t * a);
    int32_t lv_anim_path_step(const lv_anim_t * a);


    /* --------------------------------------------- Wrap --------------------------------------------- */

    enum LV_ANIM_PATH_t {
        linear = 0,
        ease_in,
        ease_out,
        ease_in_out,
        overshoot,
        bounce,
        step
    };


    class Anim_Path {
        private:
            LV_ANIM_PATH_t _anim_path;
            lv_anim_path_cb_t _path_cb;
            lv_anim_t _anim_t;
            int32_t _time_offset;

        public:
            Anim_Path()
            {
                /* Set default */
                _anim_path = ease_out;
                _path_cb = lv_anim_path_ease_out;
                _anim_t.start_value = 0;
                _anim_t.end_value = 0;
                _anim_t.time = 0;
                _anim_t.act_time = 0;
            }


            /* Set value */
            inline void setStartValue(int32_t startValue) { _anim_t.start_value = startValue; }
            inline void setEndValue(int32_t endValue) { _anim_t.end_value = endValue; }
            inline void setTime(int32_t time) { _anim_t.time = time; }
            inline void setPath(LV_ANIM_PATH_t path)
            {
                switch (path) {
                    case linear:
                        _path_cb = lv_anim_path_linear;
                        break;
                    case ease_in:
                        _path_cb = lv_anim_path_ease_in;
                        break;
                    case ease_out:
                        _path_cb = lv_anim_path_ease_out;
                        break;
                    case ease_in_out:
                        _path_cb = lv_anim_path_ease_in_out;
                        break;
                    case overshoot:
                        _path_cb = lv_anim_path_overshoot;
                        break;
                    case bounce:
                        _path_cb = lv_anim_path_bounce;
                        break;
                    case step:
                        _path_cb = lv_anim_path_step;
                        break;
                    default:
                        _path_cb = lv_anim_path_ease_out;
                        break;
                }
            }
            inline lv_anim_t* getAnimValue() { return &_anim_t; }


            inline void setAnim(LV_ANIM_PATH_t path, int32_t startValue, int32_t endValue, int32_t time)
            {
                setPath(path);
                setStartValue(startValue);
                setEndValue(endValue);
                setTime(time);
            }


            inline void setValue(int32_t startValue, int32_t endValue, int32_t time)
            {
                setAnim(_anim_path, startValue, endValue, time);
            }


            /* Reset anim time */
            inline void resetTime(int32_t currentTime) { _time_offset = currentTime; }


            /* Get path value by current time */
            inline int32_t getValue(int32_t currentTime)
            {
                _anim_t.act_time = currentTime - _time_offset;
                return _path_cb(&_anim_t);
            }


            inline bool isFinished(int32_t currentTime)
            {
                if ((currentTime - _time_offset) > _anim_t.time) {
                    return true;
                }
                else {
                    return false;
                }
            }

            
    };

}
