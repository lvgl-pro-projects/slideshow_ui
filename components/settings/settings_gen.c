/**
 * @file settings_gen.c
 * @brief Template source file for LVGL objects
 */

/*********************
 *      INCLUDES
 *********************/

#include "settings_gen.h"
#include "../../slideshow_ui.h"

/*********************
 *      DEFINES
 *********************/

/**********************
 *      TYPEDEFS
 **********************/

/***********************
 *  STATIC VARIABLES
 **********************/

/***********************
 *  STATIC PROTOTYPES
 **********************/

/**********************
 *   GLOBAL FUNCTIONS
 **********************/

lv_obj_t * settings_create(lv_obj_t * parent)
{
    LV_TRACE_OBJ_CREATE("begin");

    static lv_style_t style_base;

    static bool style_inited = false;

    if (!style_inited) {
        /*Init all styles*/
        lv_style_init(&style_base);

        lv_style_set_width(&style_base, 350);
        lv_style_set_height(&style_base, 300);
        lv_style_set_bg_color(&style_base, lv_color_hex(0xffffff));
        lv_style_set_bg_opa(&style_base, 220);
        lv_style_set_radius(&style_base, 20);
        lv_style_set_layout(&style_base, LV_LAYOUT_FLEX);
        lv_style_set_flex_flow(&style_base, LV_FLEX_FLOW_COLUMN);
        lv_style_set_pad_all(&style_base, 20);

        style_inited = true;
    }


    lv_obj_t * the_root = NULL;

    #if SLIDESHOW_UI_CHECK_COMPILE_TARGET(SLIDESHOW_UI_TARGET_ALL)
    if (slideshow_ui_check_target(SLIDESHOW_UI_TARGET_ALL)) {
        lv_obj_t * lv_obj_0 = lv_obj_create(parent);
        lv_obj_set_name_static(lv_obj_0, "settings_#");

        lv_obj_remove_style_all(lv_obj_0);
        lv_obj_add_style(lv_obj_0, &style_base, 0);
        lv_obj_t * list_item_0 = list_item_create(lv_obj_0, "Brightness");
        lv_obj_set_style_pad_right(list_item_0, 15, 0);
        lv_obj_t * lv_slider_0 = lv_slider_create(list_item_0);
        lv_obj_set_width(lv_slider_0, 150);
        lv_slider_set_min_value(lv_slider_0, 1);
        lv_slider_set_max_value(lv_slider_0, 255);
        lv_slider_bind_value(lv_slider_0, &subject_brightness);

        lv_obj_t * list_item_1 = list_item_create(lv_obj_0, "Auto-Play");
        lv_obj_t * lv_switch_0 = lv_switch_create(list_item_1);
        lv_obj_bind_checked(lv_switch_0, &subject_autoplay);

        lv_obj_t * list_item_2 = list_item_create(lv_obj_0, "Shuffle");
        lv_obj_t * lv_switch_1 = lv_switch_create(list_item_2);
        lv_obj_bind_checked(lv_switch_1, &subject_shuffle);

        lv_obj_t * list_item_3 = list_item_create(lv_obj_0, "Interval");
        lv_obj_t * lv_dropdown_0 = lv_dropdown_create(list_item_3);
        lv_dropdown_set_options(lv_dropdown_0, "30 secs\n1 min\n5 min\n10 min\n20 min");
        lv_dropdown_bind_value(lv_dropdown_0, &subject_interval);

        the_root = lv_obj_0;
    }
    #endif

    LV_TRACE_OBJ_CREATE("finished");

    return the_root;
}

/**********************
 *   STATIC FUNCTIONS
 **********************/

