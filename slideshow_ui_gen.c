/**
 * @file slideshow_ui_gen.c
 */

/*********************
 *      INCLUDES
 *********************/

#include "slideshow_ui_gen.h"

#if LV_USE_XML
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

/**********************
 *  STATIC VARIABLES
 **********************/

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

const void * icon_shuffle;
extern const void * icon_shuffle_data;
const void * icon_next;
extern const void * icon_next_data;
const void * icon_settings;
extern const void * icon_settings_data;
const void * landscape_1;
extern const void * landscape_1_data;
const void * landscape_2;
extern const void * landscape_2_data;
const void * landscape_3;
extern const void * landscape_3_data;
const void * landscape_4;
extern const void * landscape_4_data;
const void * landscape_5;
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
    char buf[256];


    /*----------------
     * Fonts
     *----------------*/


    /*----------------
     * Images
     *----------------*/
    icon_shuffle = &icon_shuffle_data;
    icon_next = &icon_next_data;
    icon_settings = &icon_settings_data;
    landscape_1 = &landscape_1_data;
    landscape_2 = &landscape_2_data;
    landscape_3 = &landscape_3_data;
    landscape_4 = &landscape_4_data;
    landscape_5 = &landscape_5_data;

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

#if LV_USE_XML
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
#if LV_USE_XML && !defined(LV_EDITOR_PREVIEW)
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

#if LV_USE_XML == 0
    /*--------------------
     *  Permanent screens
     *-------------------*/
    /* If XML is enabled it's assumed that the permanent screens are created
     * manaully from XML using lv_xml_create() */
#endif
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