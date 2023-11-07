/**
 * @file lv_anim.cpp
 * @author Forairaaaaa
 * @brief Wrap of lvgl anim path part: https://github.com/lvgl/lvgl
 * @version 0.1
 * @date 2023-06-09
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#include "lv_anim.h"


#define LV_BEZIER_VAL_MAX 1024 /**< Max time in Bezier functions (not [0..1] to use integers)*/
#define LV_BEZIER_VAL_SHIFT 10 /**< log2(LV_BEZIER_VAL_MAX): used to normalize up scaled values*/

#define LV_ANIM_RESOLUTION 1024
#define LV_ANIM_RES_SHIFT 10


namespace LVGL {

    /**
     * Get the mapped of a number given an input and output range
     * @param x integer which mapped value should be calculated
     * @param min_in min input range
     * @param max_in max input range
     * @param min_out max output range
     * @param max_out max output range
     * @return the mapped number
     */
    int32_t lv_map(int32_t x, int32_t min_in, int32_t max_in, int32_t min_out, int32_t max_out)
    {
        if(max_in >= min_in && x >= max_in) return max_out;
        if(max_in >= min_in && x <= min_in) return min_out;

        if(max_in <= min_in && x <= max_in) return max_out;
        if(max_in <= min_in && x >= min_in) return min_out;

        /**
         * The equation should be:
         *   ((x - min_in) * delta_out) / delta in) + min_out
         * To avoid rounding error reorder the operations:
         *   (x - min_in) * (delta_out / delta_min) + min_out
         */

        int32_t delta_in = max_in - min_in;
        int32_t delta_out = max_out - min_out;

        return ((x - min_in) * delta_out) / delta_in + min_out;
    }


    /**
     * Calculate a value of a Cubic Bezier function.
     * @param t time in range of [0..LV_BEZIER_VAL_MAX]
     * @param u0 start values in range of [0..LV_BEZIER_VAL_MAX]
     * @param u1 control value 1 values in range of [0..LV_BEZIER_VAL_MAX]
     * @param u2 control value 2 in range of [0..LV_BEZIER_VAL_MAX]
     * @param u3 end values in range of [0..LV_BEZIER_VAL_MAX]
     * @return the value calculated from the given parameters in range of [0..LV_BEZIER_VAL_MAX]
     */
    uint32_t lv_bezier3(uint32_t t, uint32_t u0, uint32_t u1, uint32_t u2, uint32_t u3)
    {
        uint32_t t_rem  = 1024 - t;
        uint32_t t_rem2 = (t_rem * t_rem) >> 10;
        uint32_t t_rem3 = (t_rem2 * t_rem) >> 10;
        uint32_t t2     = (t * t) >> 10;
        uint32_t t3     = (t2 * t) >> 10;

        uint32_t v1 = (t_rem3 * u0) >> 10;
        uint32_t v2 = (3 * t_rem2 * t * u1) >> 20;
        uint32_t v3 = (3 * t_rem * t2 * u2) >> 20;
        uint32_t v4 = (t3 * u3) >> 10;

        return v1 + v2 + v3 + v4;
    }


    int32_t lv_anim_path_linear(const lv_anim_t * a)
    {
        /*Calculate the current step*/
        int32_t step = lv_map(a->act_time, 0, a->time, 0, LV_ANIM_RESOLUTION);

        /*Get the new value which will be proportional to `step`
        *and the `start` and `end` values*/
        int32_t new_value;
        new_value = step * (a->end_value - a->start_value);
        new_value = new_value >> LV_ANIM_RES_SHIFT;
        new_value += a->start_value;

        return new_value;
    }


    int32_t lv_anim_path_ease_in(const lv_anim_t * a)
    {
        /*Calculate the current step*/
        uint32_t t = lv_map(a->act_time, 0, a->time, 0, LV_BEZIER_VAL_MAX);
        int32_t step = lv_bezier3(t, 0, 50, 100, LV_BEZIER_VAL_MAX);

        int32_t new_value;
        new_value = step * (a->end_value - a->start_value);
        new_value = new_value >> LV_BEZIER_VAL_SHIFT;
        new_value += a->start_value;

        return new_value;
    }


    int32_t lv_anim_path_ease_out(const lv_anim_t * a)
    {
        /*Calculate the current step*/
        uint32_t t = lv_map(a->act_time, 0, a->time, 0, LV_BEZIER_VAL_MAX);
        int32_t step = lv_bezier3(t, 0, 900, 950, LV_BEZIER_VAL_MAX);

        int32_t new_value;
        new_value = step * (a->end_value - a->start_value);
        new_value = new_value >> LV_BEZIER_VAL_SHIFT;
        new_value += a->start_value;

        return new_value;
    }


    int32_t lv_anim_path_ease_in_out(const lv_anim_t * a)
    {
        /*Calculate the current step*/
        uint32_t t = lv_map(a->act_time, 0, a->time, 0, LV_BEZIER_VAL_MAX);
        int32_t step = lv_bezier3(t, 0, 50, 952, LV_BEZIER_VAL_MAX);

        int32_t new_value;
        new_value = step * (a->end_value - a->start_value);
        new_value = new_value >> LV_BEZIER_VAL_SHIFT;
        new_value += a->start_value;

        return new_value;
    }


    int32_t lv_anim_path_overshoot(const lv_anim_t * a)
    {
        /*Calculate the current step*/
        uint32_t t = lv_map(a->act_time, 0, a->time, 0, LV_BEZIER_VAL_MAX);
        int32_t step = lv_bezier3(t, 0, 1000, 1300, LV_BEZIER_VAL_MAX);

        int32_t new_value;
        new_value = step * (a->end_value - a->start_value);
        new_value = new_value >> LV_BEZIER_VAL_SHIFT;
        new_value += a->start_value;

        return new_value;
    }


    int32_t lv_anim_path_bounce(const lv_anim_t * a)
    {
        /*Calculate the current step*/
        int32_t t = lv_map(a->act_time, 0, a->time, 0, LV_BEZIER_VAL_MAX);
        int32_t diff = (a->end_value - a->start_value);

        /*3 bounces has 5 parts: 3 down and 2 up. One part is t / 5 long*/

        if(t < 408) {
            /*Go down*/
            t = (t * 2500) >> LV_BEZIER_VAL_SHIFT; /*[0..1024] range*/
        }
        else if(t >= 408 && t < 614) {
            /*First bounce back*/
            t -= 408;
            t    = t * 5; /*to [0..1024] range*/
            t    = LV_BEZIER_VAL_MAX - t;
            diff = diff / 20;
        }
        else if(t >= 614 && t < 819) {
            /*Fall back*/
            t -= 614;
            t    = t * 5; /*to [0..1024] range*/
            diff = diff / 20;
        }
        else if(t >= 819 && t < 921) {
            /*Second bounce back*/
            t -= 819;
            t    = t * 10; /*to [0..1024] range*/
            t    = LV_BEZIER_VAL_MAX - t;
            diff = diff / 40;
        }
        else if(t >= 921 && t <= LV_BEZIER_VAL_MAX) {
            /*Fall back*/
            t -= 921;
            t    = t * 10; /*to [0..1024] range*/
            diff = diff / 40;
        }

        if(t > LV_BEZIER_VAL_MAX) t = LV_BEZIER_VAL_MAX;
        if(t < 0) t = 0;
        int32_t step = lv_bezier3(t, LV_BEZIER_VAL_MAX, 800, 500, 0);

        int32_t new_value;
        new_value = step * diff;
        new_value = new_value >> LV_BEZIER_VAL_SHIFT;
        new_value = a->end_value - new_value;

        return new_value;
    }


    int32_t lv_anim_path_step(const lv_anim_t * a)
    {
        if(a->act_time >= a->time)
            return a->end_value;
        else
            return a->start_value;
    }


}
