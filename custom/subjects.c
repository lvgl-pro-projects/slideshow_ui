
/**
 * @file subjects.c
 * generated from globals.xml. DO NOT EDIT MANUALLY.
 */

/*********************
 *      INCLUDES
 *********************/
                 
#include "subjects.h"
#include "../slideshow_ui.h" 

/**********************
 *  STATIC PROTOTYPES
 **********************/

static void int_subject_observer_cb(lv_observer_t * observer, lv_subject_t * subject);

/**********************
 *  INIT 
 **********************/

void slideshow_ui_subjects_init(void)
{
    /* Re-initialize non-supported subjects in the Editor */
    lv_subject_deinit(&subject_image);
    lv_subject_init_pointer(&subject_image, NULL);

    /* Attach observers for change notifications */
    lv_subject_add_observer(&subject_brightness, int_subject_observer_cb, slideshow_ui_subject_brightness_change);
    lv_subject_add_observer(&subject_autoplay, int_subject_observer_cb, slideshow_ui_subject_autoplay_change);
    lv_subject_add_observer(&subject_shuffle, int_subject_observer_cb, slideshow_ui_subject_shuffle_change);
    lv_subject_add_observer(&subject_interval, int_subject_observer_cb, slideshow_ui_subject_interval_change);

}

/**********************
 * SET FUNCTIONS
 **********************/

void slideshow_ui_subject_set_brightness(int32_t value)
{
    lv_lock();
    lv_subject_set_int(&subject_brightness, value);
    lv_unlock();
}

void slideshow_ui_subject_set_autoplay(int32_t value)
{
    lv_lock();
    lv_subject_set_int(&subject_autoplay, value);
    lv_unlock();
}

void slideshow_ui_subject_set_shuffle(int32_t value)
{
    lv_lock();
    lv_subject_set_int(&subject_shuffle, value);
    lv_unlock();
}

void slideshow_ui_subject_set_interval(int32_t value)
{
    lv_lock();
    lv_subject_set_int(&subject_interval, value);
    lv_unlock();
}

void slideshow_ui_subject_set_image(void * value)
{
    lv_lock();
    lv_subject_set_pointer(&subject_image, value);
    lv_unlock();
}

/**********************
 * GET FUNCTIONS
 **********************/

int32_t slideshow_ui_subject_get_brightness(void)
{
    return lv_subject_get_int(&subject_brightness);
}

int32_t slideshow_ui_subject_get_autoplay(void)
{
    return lv_subject_get_int(&subject_autoplay);
}

int32_t slideshow_ui_subject_get_shuffle(void)
{
    return lv_subject_get_int(&subject_shuffle);
}

int32_t slideshow_ui_subject_get_interval(void)
{
    return lv_subject_get_int(&subject_interval);
}

void * slideshow_ui_subject_get_image(void)
{
    return lv_subject_get_pointer(&subject_image);
}

/**********************
 * WEAK FUNCTIONS
 **********************/

void __attribute__((weak)) slideshow_ui_subject_brightness_change(int32_t value)
{
    LV_LOG_USER("Subject brightness changed %d", value);
}

void __attribute__((weak)) slideshow_ui_subject_autoplay_change(int32_t value)
{
    LV_LOG_USER("Subject autoplay changed %d", value);
}

void __attribute__((weak)) slideshow_ui_subject_shuffle_change(int32_t value)
{
    LV_LOG_USER("Subject shuffle changed %d", value);
}

void __attribute__((weak)) slideshow_ui_subject_interval_change(int32_t value)
{
    LV_LOG_USER("Subject interval changed %d", value);
}

/**********************
 * STATIC FUNCTIONS
 **********************/

static void int_subject_observer_cb(lv_observer_t * observer, lv_subject_t * subject)
{
    int32_t value = lv_subject_get_int(subject);
    void (*fn)(int32_t) = lv_observer_get_user_data(observer);
    if(fn) fn(value);
}
