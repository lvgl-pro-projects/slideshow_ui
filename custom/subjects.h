
/**
 * @file subjects.h
 * generated from globals.xml. DO NOT EDIT MANUALLY.
 */

#ifndef SUBJECTS_H
#define SUBJECTS_H


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

                 
/**********************
 * INIT
 **********************/

/**
 * Re-initialize subjects and attach observers.
 */
void slideshow_ui_subjects_init(void);


/**********************
 * SET FUNCTIONS
 **********************/

/**
 * Display brightness set function.
 * @param value    New value
 */
void slideshow_ui_subject_set_brightness(int32_t value);

/**
 * Slideshow auto-play set function.
 * @param value    New value
 */
void slideshow_ui_subject_set_autoplay(int32_t value);

/**
 * Slideshow shuffle mode set function.
 * @param value    New value
 */
void slideshow_ui_subject_set_shuffle(int32_t value);

/**
 * Slideshow image interval set function.
 * @param value    New value
 */
void slideshow_ui_subject_set_interval(int32_t value);

/**
 * Slideshow image source set function.
 * @param value    New value
 */
void slideshow_ui_subject_set_image(void * value);


/**********************
 * GET FUNCTIONS
 **********************/

/**
 * Display brightness get function.
 * @return         Current value
 */
int32_t slideshow_ui_subject_get_brightness(void);

/**
 * Slideshow auto-play get function.
 * @return         Current value
 */
int32_t slideshow_ui_subject_get_autoplay(void);

/**
 * Slideshow shuffle mode get function.
 * @return         Current value
 */
int32_t slideshow_ui_subject_get_shuffle(void);

/**
 * Slideshow image interval get function.
 * @return         Current value
 */
int32_t slideshow_ui_subject_get_interval(void);

/**
 * Slideshow image source get function.
 * @return         Current value
 */
void * slideshow_ui_subject_get_image(void);


/**********************
 * CHANGE FUNCTIONS
 **********************/

/**
 * Display brightness change callback.
 * @param value    Updated value
 */
void slideshow_ui_subject_brightness_change(int32_t value);

/**
 * Slideshow auto-play change callback.
 * @param value    Updated value
 */
void slideshow_ui_subject_autoplay_change(int32_t value);

/**
 * Slideshow shuffle mode change callback.
 * @param value    Updated value
 */
void slideshow_ui_subject_shuffle_change(int32_t value);

/**
 * Slideshow image interval change callback.
 * @param value    Updated value
 */
void slideshow_ui_subject_interval_change(int32_t value);


#ifdef __cplusplus
} /*extern "C"*/
#endif

#endif /*SUBJECTS_H*/
