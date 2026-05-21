/**
 * @file slideshow_ui.c
 */

/*********************
 *      INCLUDES
 *********************/

#include "slideshow_ui.h"

/*********************
 *      DEFINES
 *********************/

/**********************
 *      TYPEDEFS
 **********************/

/**********************
 *  STATIC PROTOTYPES
 **********************/

static void autoplay_observer_cb(lv_observer_t * observer, lv_subject_t * subject);
static void controls_observer_cb(lv_observer_t * observer, lv_subject_t * subject);
static void interval_observer_cb(lv_observer_t * observer, lv_subject_t * subject);

static void image_next_timer_cb(lv_timer_t * timer);
static void inactivity_timer_cb(lv_timer_t * timer);

static void start_next_timer(void);

static uint32_t get_interval(void);

/**********************
 *  STATIC VARIABLES
 **********************/
static lv_timer_t * image_next_timer;
static lv_timer_t * inactivity_timer;

static const void * images[5];

static int img_pos = 0;

/**********************
 *      MACROS
 **********************/

/**********************
 *   GLOBAL FUNCTIONS
 **********************/

void slideshow_ui_init(const char * asset_path)
{
    slideshow_ui_init_gen(asset_path);

    /* Add your own custom code here if needed */

    slideshow_ui_subjects_init();

    const void * tmp[] = {
        landscape_1,
        landscape_2,
        landscape_3,
        landscape_4,
        landscape_5
    };

    lv_memcpy(images, tmp, sizeof(images));

    slideshow_ui_subject_set_image((void *)landscape_1);

    lv_subject_add_observer(&subject_controls, controls_observer_cb, NULL);
    lv_subject_add_observer(&subject_settings, controls_observer_cb, NULL);
    lv_subject_add_observer(&subject_autoplay, autoplay_observer_cb, NULL);
    lv_subject_add_observer(&subject_interval, interval_observer_cb, NULL);

#if !defined(LV_EDITOR_PREVIEW)
    lv_screen_load(screen_main_create());
#endif
}

void on_next_cb(lv_event_t * e)
{
    bool shuffle = lv_subject_get_int(&subject_shuffle);
    slideshow_ui_next_triggered_cb(shuffle);

    if (image_next_timer) {
        lv_timer_del(image_next_timer);
        image_next_timer = NULL;
    }
    start_next_timer();
}

void __attribute__((weak)) slideshow_ui_next_triggered_cb(bool shuffle)
{

    if (shuffle) {
        img_pos = lv_rand(0, 4);
    } else {
        img_pos++;
        if (img_pos > 4) {
            img_pos = 0;
        }
    }

    LV_LOG_USER("Next pos %d", img_pos);

    slideshow_ui_subject_set_image((void *)images[img_pos]);

}

/**********************
 *   STATIC FUNCTIONS
 **********************/

static void autoplay_observer_cb(lv_observer_t * observer, lv_subject_t * subject)
{
    bool autoplay = lv_subject_get_int(&subject_autoplay);

    int32_t interval = get_interval();

    if (autoplay) {
        start_next_timer();
    } else {
        if (image_next_timer) {
            lv_timer_del(image_next_timer);
            image_next_timer = NULL;
        }
    }
}

static void interval_observer_cb(lv_observer_t * observer, lv_subject_t * subject)
{
    bool autoplay = lv_subject_get_int(&subject_autoplay);

    if (autoplay) {
        if (image_next_timer) {
            lv_timer_del(image_next_timer);
            image_next_timer = NULL;
        }
        start_next_timer();
    }
}

static void controls_observer_cb(lv_observer_t * observer, lv_subject_t * subject)
{
    bool controls = lv_subject_get_int(&subject_controls);
    bool settings = lv_subject_get_int(&subject_settings);

    if (controls || settings) {
        if (inactivity_timer) {
            lv_timer_reset(inactivity_timer);
        } else {
            inactivity_timer = lv_timer_create(inactivity_timer_cb, 1000, NULL);
        }

        if (image_next_timer) {
            lv_timer_pause(image_next_timer);
        }
    } else {
        if (inactivity_timer) {
            lv_timer_del(inactivity_timer);
            inactivity_timer = NULL;
        }

        start_next_timer();
    }

}


static void image_next_timer_cb(lv_timer_t * timer)
{
    bool shuffle = lv_subject_get_int(&subject_shuffle);
    slideshow_ui_next_triggered_cb(shuffle);

    lv_timer_del(image_next_timer);
    image_next_timer = NULL;
    start_next_timer();
}

static void inactivity_timer_cb(lv_timer_t * timer)
{
    uint32_t inactive_time = lv_display_get_inactive_time(lv_display_get_default());
    
    if (inactive_time > 10000) {
        LV_LOG_WARN("Inactivity timeout, closing controls & settings panels");

        lv_timer_del(inactivity_timer);
        inactivity_timer = NULL;

        lv_subject_set_int(&subject_controls, false);
        lv_subject_set_int(&subject_settings, false);
        

        start_next_timer();
    }
}

static void start_next_timer(void)
{
    bool autoplay = lv_subject_get_int(&subject_autoplay);
    bool controls = lv_subject_get_int(&subject_controls);
    bool settings = lv_subject_get_int(&subject_settings);
    if (!autoplay || controls || settings) {
        LV_LOG_WARN("Not starting timer. autoplay: %d, controls: %d, settings: %d", autoplay, controls, settings);
        return;
    }
    int32_t interval = get_interval();

    if (image_next_timer) {
        lv_timer_del(image_next_timer);
        image_next_timer = NULL;
    }

    LV_LOG_USER("Starting next timer with interval %d ms", interval);

   image_next_timer = lv_timer_create(image_next_timer_cb, interval, NULL);
   lv_timer_set_repeat_count(image_next_timer, 1);
}

static uint32_t get_interval(void)
{
    int32_t interval = lv_subject_get_int(&subject_interval);

    //"30 secs\n1 min\n5 min\n10 min\n20 min"
    switch (interval) {
        case 0:
            return 30000;
        case 1:
            return 60000;
        case 2:
            return 300000;
        case 3:
            return 600000;
        case 4:
            return 1200000;
        default:
            return 5000;
    
    }
    return 5000;
}