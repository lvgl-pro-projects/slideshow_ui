# Slideshow UI

A minimal image slideshow UI built with LVGL, featuring simple playback controls and configurable settings.

## Features
- Image slideshow display
- Auto-play support
- Shuffle mode
- Adjustable interval timing
- Brightness control

Designed for embedded devices using LVGL with a focus on simplicity and performance.

## Screenshots

| Image | Controls | Settings |
| ------ | ------- | ------- |
| ![Preview](screenshots/preview.png?raw=true "preview") | ![Controls](screenshots/controls.png?raw=true "controls") | ![Settings](screenshots/settings.png?raw=true "settings") |

## Try it Online

You can preview and interact with the UI directly in your browser via the LVGL online viewer:

https://viewer.lvgl.io/?repo=https://github.com/lvgl-pro-projects/slideshow_ui

## Integration

Follow these steps to integrate the slideshow UI into your project:

1. Initialize the UI

Call the UI init function:

```c
slideshow_ui_init("");
```

2. Provide Images (Required for custom sources)

Override the weak callback to control how images are loaded:

```c
void slideshow_ui_next_triggered_cb(bool shuffle)
{
    // Decide next image based on shuffle flag
    // Load image from memory, filesystem, etc.

    void * next_image = ...;

    slideshow_ui_subject_set_image(next_image);
}
```
shuffle: indicates if shuffle mode is enabled in the ui
next_image can be:
- lv_image_dsc_t *
- file path (if using filesystem)

### ⚠️ Default Behavior

If `slideshow_ui_next_triggered_cb` is not implemented, the UI will fall back to 5 built-in test images for demonstration purposes.

This is useful for:
- quick preview
- testing UI behavior without integration

For real use cases, you should override the callback to supply your own images.

3. Set Initial Image

After initialization, set a default or previously saved image:

```c
slideshow_ui_subject_set_image((void *)&image_dsc);
```

4. Handle Settings Changes (Optional)

You can override subject change callbacks to react to UI updates:

```c
void slideshow_ui_subject_brightness_change(int32_t value)
{
    // Apply brightness to your display driver
}
```
See [`subjects.h`](custom/subjects.h)

5. Configure Defaults / Restore State

You can configure subjects at startup:
```c
slideshow_ui_subject_set_brightness(200);
slideshow_ui_subject_set_autoplay(1);
slideshow_ui_subject_set_interval(2);
```
Or restore values from saved settings.

### Note
- The UI does not manage image storage — you control the source
