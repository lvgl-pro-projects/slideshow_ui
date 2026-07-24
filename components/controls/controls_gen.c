/**
 * @file controls_gen.c
 * @brief Template source file for LVGL objects
 */

/*********************
 *      INCLUDES
 *********************/

#include "controls_gen.h"
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

lv_obj_t * controls_create(lv_obj_t * parent)
{
    LV_TRACE_OBJ_CREATE("begin");

    static lv_style_t style_base;

    static bool style_inited = false;

    if (!style_inited) {
        /*Init all styles*/
        lv_style_init(&style_base);

        lv_style_set_width(&style_base, 350);
        lv_style_set_height(&style_base, LV_SIZE_CONTENT);
        lv_style_set_bg_color(&style_base, lv_color_hex(0xffffff));
        lv_style_set_bg_opa(&style_base, 120);
        lv_style_set_radius(&style_base, 20);
        lv_style_set_layout(&style_base, LV_LAYOUT_FLEX);
        lv_style_set_flex_main_place(&style_base, LV_FLEX_ALIGN_SPACE_AROUND);
        lv_style_set_pad_all(&style_base, 20);

        style_inited = true;
    }


    lv_obj_t * the_root = NULL;

    #if SLIDESHOW_UI_CHECK_COMPILE_TARGET(SLIDESHOW_UI_TARGET_ALL)
    if (slideshow_ui_check_target(SLIDESHOW_UI_TARGET_ALL)) {
        lv_obj_t * lv_obj_0 = lv_obj_create(parent);
        lv_obj_set_name_static(lv_obj_0, "controls_#");

        lv_obj_remove_style_all(lv_obj_0);
        lv_obj_add_style(lv_obj_0, &style_base, 0);
        lv_obj_t * button_0 = button_create(lv_obj_0, icon_settings);
        lv_obj_add_subject_set_int_event(button_0, &subject_controls, LV_EVENT_CLICKED, 0);
        lv_obj_add_subject_set_int_event(button_0, &subject_settings, LV_EVENT_CLICKED, 1);

        lv_obj_t * button_1 = button_create(lv_obj_0, icon_shuffle);
        lv_obj_bind_checked(button_1, &subject_shuffle);
        lv_obj_add_subject_toggle_event(button_1, &subject_shuffle, LV_EVENT_CLICKED);

        lv_obj_t * button_2 = button_create(lv_obj_0, icon_next);
        lv_obj_add_event_cb(button_2, on_next_cb, LV_EVENT_CLICKED, NULL);

        the_root = lv_obj_0;
    }
    #endif

    LV_TRACE_OBJ_CREATE("finished");

    return the_root;
}

/**********************
 *   STATIC FUNCTIONS
 **********************/

