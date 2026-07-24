/**
 * @file slideshow_ui_gen.c
 */

/*********************
 *      INCLUDES
 *********************/

#include "slideshow_ui_gen.h"

#if defined(LV_USE_XML) && LV_USE_XML
#endif /* LV_USE_XML */

/*********************
 *      DEFINES
 *********************/

/**********************
 *      TYPEDEFS
 **********************/

/**********************
 *  STATIC PROTOTYPES
 **********************/

static void check_font(lv_font_t ** font, const char * name);

/**********************
 *  STATIC VARIABLES
 **********************/

static uint32_t slideshow_ui_target = SLIDESHOW_UI_TARGET_ALL;

/*----------------
 * Translations
 *----------------*/

/**********************
 *  GLOBAL VARIABLES
 **********************/

/*--------------------
 *  Permanent screens
 *-------------------*/

/*----------------
 * Fonts
 *----------------*/



/*----------------
 * Images
 *----------------*/

/* Targets: any */
const void * icon_shuffle = NULL;
extern const void * icon_shuffle_data;
const void * icon_next = NULL;
extern const void * icon_next_data;
const void * icon_settings = NULL;
extern const void * icon_settings_data;
const void * landscape_1 = NULL;
extern const void * landscape_1_data;
const void * landscape_2 = NULL;
extern const void * landscape_2_data;
const void * landscape_3 = NULL;
extern const void * landscape_3_data;
const void * landscape_4 = NULL;
extern const void * landscape_4_data;
const void * landscape_5 = NULL;
extern const void * landscape_5_data;

/*----------------
 * Global styles
 *----------------*/

/*----------------
 * Subjects
 *----------------*/

lv_subject_t subject_brightness;
lv_subject_t subject_autoplay;
lv_subject_t subject_shuffle;
lv_subject_t subject_interval;
lv_subject_t subject_image;
lv_subject_t subject_controls;
lv_subject_t subject_settings;

/**********************
 *      MACROS
 **********************/

/**********************
 *   GLOBAL FUNCTIONS
 **********************/

void slideshow_ui_init_gen(const char * asset_path)
{

    /*----------------
     * Fonts
     *----------------*/




    /*----------------
     * Images
     *----------------*/

    /* Targets: any */
    #if SLIDESHOW_UI_CHECK_COMPILE_TARGET(SLIDESHOW_UI_TARGET_ALL)
    if (slideshow_ui_check_target(SLIDESHOW_UI_TARGET_ALL)) {
        /* icon_shuffle */
        if (!icon_shuffle) {
            icon_shuffle = &icon_shuffle_data;
        }
        /* icon_next */
        if (!icon_next) {
            icon_next = &icon_next_data;
        }
        /* icon_settings */
        if (!icon_settings) {
            icon_settings = &icon_settings_data;
        }
        /* landscape_1 */
        if (!landscape_1) {
            landscape_1 = &landscape_1_data;
        }
        /* landscape_2 */
        if (!landscape_2) {
            landscape_2 = &landscape_2_data;
        }
        /* landscape_3 */
        if (!landscape_3) {
            landscape_3 = &landscape_3_data;
        }
        /* landscape_4 */
        if (!landscape_4) {
            landscape_4 = &landscape_4_data;
        }
        /* landscape_5 */
        if (!landscape_5) {
            landscape_5 = &landscape_5_data;
        }
    }
    #endif

    /*----------------
     * Global styles
     *----------------*/

    /*----------------
     * Subjects
     *----------------*/
    lv_subject_init_int(&subject_brightness, 200);
    lv_subject_set_min_value_int(&subject_brightness, 50);
    lv_subject_set_max_value_int(&subject_brightness, 255);
    lv_subject_init_int(&subject_autoplay, 1);
    lv_subject_set_min_value_int(&subject_autoplay, 0);
    lv_subject_set_max_value_int(&subject_autoplay, 1);
    lv_subject_init_int(&subject_shuffle, 0);
    lv_subject_set_min_value_int(&subject_shuffle, 0);
    lv_subject_set_max_value_int(&subject_shuffle, 1);
    lv_subject_init_int(&subject_interval, 0);
    lv_subject_set_min_value_int(&subject_interval, 0);
    lv_subject_set_max_value_int(&subject_interval, 4);
    lv_subject_init_int(&subject_image, 0);
    lv_subject_init_int(&subject_controls, 0);
    lv_subject_set_min_value_int(&subject_controls, 0);
    lv_subject_set_max_value_int(&subject_controls, 1);
    lv_subject_init_int(&subject_settings, 0);
    lv_subject_set_min_value_int(&subject_settings, 0);
    lv_subject_set_max_value_int(&subject_settings, 1);

    /*----------------
     * Translations
     *----------------*/

#if defined(LV_USE_XML) && LV_USE_XML
    /* Register widgets */


    /* Register fonts */

    /* Register subjects */
    lv_xml_register_subject(NULL, "subject_brightness", &subject_brightness);
    lv_xml_register_subject(NULL, "subject_autoplay", &subject_autoplay);
    lv_xml_register_subject(NULL, "subject_shuffle", &subject_shuffle);
    lv_xml_register_subject(NULL, "subject_interval", &subject_interval);
    lv_xml_register_subject(NULL, "subject_image", &subject_image);
    lv_xml_register_subject(NULL, "subject_controls", &subject_controls);
    lv_xml_register_subject(NULL, "subject_settings", &subject_settings);

    /* Register callbacks */
    lv_xml_register_event_cb(NULL, "on_next_cb", on_next_cb);
#endif

    /* Register all the global assets so that they won't be created again when globals.xml is parsed.
     * While running in the editor skip this step to update the preview when the XML changes */
#if defined(LV_USE_XML) && LV_USE_XML && !defined(LV_EDITOR_PREVIEW)
    /* Register images */
    lv_xml_register_image(NULL, "icon_shuffle", icon_shuffle);
    lv_xml_register_image(NULL, "icon_next", icon_next);
    lv_xml_register_image(NULL, "icon_settings", icon_settings);
    lv_xml_register_image(NULL, "landscape_1", landscape_1);
    lv_xml_register_image(NULL, "landscape_2", landscape_2);
    lv_xml_register_image(NULL, "landscape_3", landscape_3);
    lv_xml_register_image(NULL, "landscape_4", landscape_4);
    lv_xml_register_image(NULL, "landscape_5", landscape_5);
#endif

#if defined(LV_USE_XML) && LV_USE_XML == 0
    /*--------------------
     *  Permanent screens
     *-------------------*/
    /* If XML is enabled it's assumed that the permanent screens are created
     * manually from XML using lv_xml_create() */
#endif
}

void slideshow_ui_set_target(uint32_t target)
{
    slideshow_ui_target = target;
}

uint32_t slideshow_ui_get_target(void)
{
    return slideshow_ui_target;
}

bool slideshow_ui_check_target(uint32_t target)
{
    return (slideshow_ui_target & target) ? true : false;
}

/* Callbacks */
#if defined(LV_EDITOR_PREVIEW)
void __attribute__((weak)) on_next_cb(lv_event_t * e)
{
    LV_UNUSED(e);
    LV_LOG("on_next_cb was called\n");
}
#endif

/**********************
 *   STATIC FUNCTIONS
 **********************/

static void check_font(lv_font_t ** font, const char * name)
{
    if (!(*font)) {
        *font = (lv_font_t *)LV_FONT_DEFAULT;
        LV_LOG_WARN("font `%s` was not set. Using `LV_FONT_DEFAULT` instead", name);
    }
}