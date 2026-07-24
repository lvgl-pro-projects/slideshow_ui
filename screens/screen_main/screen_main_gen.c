/**
 * @file screen_main_gen.c
 * @brief Template source file for LVGL objects
 */

/*********************
 *      INCLUDES
 *********************/

#include "screen_main_gen.h"
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

lv_obj_t * screen_main_create(void)
{
    LV_TRACE_OBJ_CREATE("begin");


    lv_obj_t * the_root = NULL;

    #if SLIDESHOW_UI_CHECK_COMPILE_TARGET(SLIDESHOW_UI_TARGET_ALL)
    if (slideshow_ui_check_target(SLIDESHOW_UI_TARGET_ALL)) {
        lv_obj_t * lv_obj_0 = lv_obj_create(NULL);
        lv_obj_set_name_static(lv_obj_0, "screen_main_#");
        lv_obj_set_style_bg_color(lv_obj_0, lv_color_hex(0x000000), 0);

        lv_obj_t * lv_image_0 = lv_image_create(lv_obj_0);
        lv_image_bind_src(lv_image_0, &subject_image);

        lv_obj_t * controls_0 = controls_create(lv_obj_0);
        lv_obj_set_align(controls_0, LV_ALIGN_BOTTOM_MID);
        lv_obj_set_y(controls_0, -50);
        lv_obj_bind_flag_if_eq(controls_0, &subject_controls, LV_OBJ_FLAG_HIDDEN, 0);

        lv_obj_t * settings_0 = settings_create(lv_obj_0);
        lv_obj_set_align(settings_0, LV_ALIGN_CENTER);
        lv_obj_bind_flag_if_eq(settings_0, &subject_settings, LV_OBJ_FLAG_HIDDEN, 0);

        lv_obj_add_subject_toggle_event(lv_obj_0, &subject_controls, LV_EVENT_CLICKED);
        lv_obj_add_subject_set_int_event(lv_obj_0, &subject_settings, LV_EVENT_CLICKED, 0);

        the_root = lv_obj_0;
    }
    #endif

    LV_TRACE_OBJ_CREATE("finished");

    return the_root;
}

/**********************
 *   STATIC FUNCTIONS
 **********************/

