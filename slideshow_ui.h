/**
 * @file slideshow_ui.h
 */

#ifndef SLIDESHOW_UI_H
#define SLIDESHOW_UI_H

#ifdef __cplusplus
extern "C" {
#endif

/*********************
 *      INCLUDES
 *********************/

#include "slideshow_ui_gen.h"

#include "custom/subjects.h"

/*********************
 *      DEFINES
 *********************/

/**********************
 *      TYPEDEFS
 **********************/

/**********************
 * GLOBAL VARIABLES
 **********************/

/**********************
 * GLOBAL PROTOTYPES
 **********************/

/**
 * Initialize the component library
 */
void slideshow_ui_init(const char * asset_path);


/**
 * Triggered by the timer in autoplay mode or on next button clicked
 * Update the image using slideshow_ui_subject_set_image(void * value);
 * @param shuffle whether shuffle mode is enabled
 */
void slideshow_ui_next_triggered_cb(bool shuffle);

/**********************
 *      MACROS
 **********************/

#ifdef __cplusplus
} /*extern "C"*/
#endif

#endif /*SLIDESHOW_UI_H*/