/**
 * @file slideshow_ui_gen.h
 */

#ifndef SLIDESHOW_UI_GEN_H
#define SLIDESHOW_UI_GEN_H

#ifndef UI_SUBJECT_STRING_LENGTH
#define UI_SUBJECT_STRING_LENGTH 256
#endif

#ifdef __cplusplus
extern "C" {
#endif

/*********************
 *      INCLUDES
 *********************/

#ifdef LV_LVGL_H_INCLUDE_SIMPLE
    #include "lvgl.h"
    #include "lvgl_private.h"
#else
    #include "lvgl/lvgl.h"
    #include "lvgl/lvgl_private.h"
#endif

#if defined(LV_USE_XML) && LV_USE_XML
    #include "lv_xml/lv_xml.h"
#endif



/* Prototypes for target functions, needed by responsive const definitions */

void slideshow_ui_set_target(uint32_t target);
uint32_t slideshow_ui_get_target(void);
bool slideshow_ui_check_target(uint32_t target);

/*********************
 *      DEFINES
 *********************/

#define SLIDESHOW_UI_TARGET_UNDEFINED  (0 << 1)
#define SLIDESHOW_UI_TARGET_TARGET1    (1 << 1)
#define SLIDESHOW_UI_TARGET_ALL        0x0FFFFFFF

/* By default compile for all targets, allowing to switch to any targets at runtime */
#ifndef SLIDESHOW_UI_COMPILE_TARGET
#define SLIDESHOW_UI_COMPILE_TARGET SLIDESHOW_UI_TARGET_ALL
#endif

#define SLIDESHOW_UI_CHECK_COMPILE_TARGET(target) (SLIDESHOW_UI_COMPILE_TARGET & (target) ? 1 : 0)

#ifndef LV_XML_EVAL_STRING_BUF_SIZE
    #define LV_XML_EVAL_STRING_BUF_SIZE 256
#endif

/**********************
 *      TYPEDEFS
 **********************/

/**********************
 * GLOBAL VARIABLES
 **********************/

/*-------------------
 * Permanent screens
 *------------------*/

/*----------------
 * Global styles
 *----------------*/

/*----------------
 * Fonts
 *----------------*/




/*----------------
 * Images
 *----------------*/

/* Targets: any */
extern const void * icon_shuffle;
extern const void * icon_next;
extern const void * icon_settings;
extern const void * landscape_1;
extern const void * landscape_2;
extern const void * landscape_3;
extern const void * landscape_4;
extern const void * landscape_5;

/*----------------
 * Subjects
 *----------------*/

extern lv_subject_t subject_brightness;
extern lv_subject_t subject_autoplay;
extern lv_subject_t subject_shuffle;
extern lv_subject_t subject_interval;
extern lv_subject_t subject_image;
extern lv_subject_t subject_controls;
extern lv_subject_t subject_settings;

/**********************
 * GLOBAL PROTOTYPES
 **********************/

/*----------------
 * Event Callbacks
 *----------------*/

void on_next_cb(lv_event_t * e);

/**
 * Initialize the component library
 */

void slideshow_ui_init_gen(const char * asset_path);

/**********************
 *      MACROS
 **********************/

/**********************
 *   POST INCLUDES
 **********************/

/*Include all the widgets, components and screens of this library*/
#include "components/button/button_gen.h"
#include "components/controls/controls_gen.h"
#include "components/list_item/list_item_gen.h"
#include "components/settings/settings_gen.h"
#include "screens/screen_main/screen_main_gen.h"

#ifdef __cplusplus
} /*extern "C"*/
#endif

#endif /*SLIDESHOW_UI_GEN_H*/