cmake_minimum_required(VERSION 3.16)
project(lvgl_web C)

if(NOT EMSCRIPTEN)
  message(FATAL_ERROR "Configure this target with Emscripten: emcmake cmake -S web-editor -B build-web")
endif()

set(UI_DIR "${CMAKE_CURRENT_SOURCE_DIR}/.." CACHE PATH "Folder with the exported UI")
set(PROJECT_XML "${UI_DIR}/project.xml")

set(_lvgl_version_default "v9.5.0")
if(EXISTS "${PROJECT_XML}")
  file(READ "${PROJECT_XML}" _project_xml_for_version)
  string(REGEX MATCH "<project[^>]*lvgl_version=\"([^\"]+)\"" _ "${_project_xml_for_version}")
  set(_project_lvgl_version "${CMAKE_MATCH_1}")
  if(_project_lvgl_version)
    if(_project_lvgl_version MATCHES "^v")
      set(_lvgl_version_default "${_project_lvgl_version}")
    else()
      set(_lvgl_version_default "v${_project_lvgl_version}")
    endif()
  endif()
endif()
set(LVGL_VERSION "${_lvgl_version_default}" CACHE STRING "LVGL version (git tag or branch)")
message(STATUS "Using LVGL ${LVGL_VERSION}")

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(EXECUTABLE_OUTPUT_PATH "${CMAKE_BINARY_DIR}/bin")
set(WEB_PREVIEW_OUTPUT_PATH "${UI_DIR}/preview-bin/web")
set(WEB_ASSETS_DIR
    "${CMAKE_CURRENT_SOURCE_DIR}/assets"
    CACHE PATH
    "Optional folder with web preview assets")
option(WEB_SINGLE_HTML
       "Build one self-contained index.html instead of separate HTML, JS and assets"
       OFF)
option(WEB_LVGL_MEMORY_MONITOR
       "Use LVGL's built-in allocator and expose LVGL heap diagnostics to the web page"
       OFF)
option(WEB_ENABLE_KEY_OVERLAY
       "Enable optional key overlay, hardware frame image and clickable hardware controls"
       OFF)
set(WEB_HARDWARE_FRAME_IMAGE_FILE
    "${WEB_ASSETS_DIR}/hardware_frame.png"
    CACHE FILEPATH
    "Hardware frame image to embed when WEB_SINGLE_HTML is enabled")
unset(WEB_KEY_OVERLAY_CONFIG_FILE CACHE)
set(WEB_KEY_OVERLAY_CONFIG_FILE "${WEB_ASSETS_DIR}/key_overlay.json")

include(FetchContent)
if(POLICY CMP0169)
  cmake_policy(SET CMP0169 OLD)
endif()
FetchContent_Declare(
  lvgl
  GIT_REPOSITORY https://github.com/lvgl/lvgl.git
  GIT_TAG ${LVGL_VERSION}
  GIT_SHALLOW TRUE)

FetchContent_GetProperties(lvgl)
if(NOT lvgl_POPULATED)
  message(STATUS "Fetching LVGL ${LVGL_VERSION}. It might take a few minutes ...")
  FetchContent_Populate(lvgl)
endif()

find_package(Python3 REQUIRED COMPONENTS Interpreter)

set(LV_CONF_DEFAULTS "${CMAKE_CURRENT_SOURCE_DIR}/lv_conf_emscripten.defaults")
set(LV_CONF_EFFECTIVE_DEFAULTS "${LV_CONF_DEFAULTS}")
if(WEB_LVGL_MEMORY_MONITOR)
  file(READ "${LV_CONF_DEFAULTS}" _lv_conf_defaults_text)
  string(REGEX REPLACE
         "(^|\n)[ \t]*LV_USE_STDLIB_MALLOC[ \t]+[^\n]*"
         "\\1LV_USE_STDLIB_MALLOC    LV_STDLIB_BUILTIN"
         _lv_conf_defaults_text
         "${_lv_conf_defaults_text}")
  string(REGEX REPLACE
         "(^|\n)[ \t]*LV_USE_SYSMON[ \t]+[^\n]*"
         "\\1LV_USE_SYSMON           1"
         _lv_conf_defaults_text
         "${_lv_conf_defaults_text}")
  if(NOT _lv_conf_defaults_text MATCHES "(^|\n)[ \t]*LV_USE_SYSMON[ \t]+")
    string(APPEND _lv_conf_defaults_text "\nLV_USE_SYSMON           1")
  endif()
  string(REGEX REPLACE
         "(^|\n)[ \t]*LV_USE_MEM_MONITOR[ \t]+[^\n]*"
         "\\1LV_USE_MEM_MONITOR      1"
         _lv_conf_defaults_text
         "${_lv_conf_defaults_text}")
  if(NOT _lv_conf_defaults_text MATCHES "(^|\n)[ \t]*LV_USE_MEM_MONITOR[ \t]+")
    string(APPEND _lv_conf_defaults_text "\nLV_USE_MEM_MONITOR      1")
  endif()
  set(LV_CONF_EFFECTIVE_DEFAULTS "${CMAKE_BINARY_DIR}/lv_conf_emscripten.memory.defaults")
  file(WRITE "${LV_CONF_EFFECTIVE_DEFAULTS}" "${_lv_conf_defaults_text}\n")
endif()
set(LV_CONF_PATH "${CMAKE_BINARY_DIR}/lv_conf.h")
set(LV_CONF_TMP "${CMAKE_BINARY_DIR}/lv_conf.h.in")
execute_process(
  COMMAND ${Python3_EXECUTABLE}
          "${lvgl_SOURCE_DIR}/scripts/generate_lv_conf.py"
          --template "${lvgl_SOURCE_DIR}/lv_conf_template.h"
          --defaults "${LV_CONF_EFFECTIVE_DEFAULTS}"
          --config   "${LV_CONF_TMP}"
  RESULT_VARIABLE _conf_result
  OUTPUT_VARIABLE _conf_output
  ERROR_VARIABLE  _conf_output)
if(NOT _conf_result EQUAL 0)
  message(FATAL_ERROR "Failed to generate lv_conf.h:\n${_conf_output}")
endif()
execute_process(COMMAND ${CMAKE_COMMAND} -E copy_if_different
                "${LV_CONF_TMP}" "${LV_CONF_PATH}")
message(STATUS "Generated ${LV_CONF_PATH} from ${LV_CONF_EFFECTIVE_DEFAULTS}")

set_property(DIRECTORY APPEND PROPERTY CMAKE_CONFIGURE_DEPENDS
             "${LV_CONF_DEFAULTS}")

set(LV_BUILD_CONF_PATH "${LV_CONF_PATH}" CACHE PATH "" FORCE)

set(CONFIG_LV_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
set(CONFIG_LV_BUILD_DEMOS OFF CACHE BOOL "" FORCE)
set(CONFIG_LV_USE_THORVG_INTERNAL OFF CACHE BOOL "" FORCE)

add_compile_options("-sUSE_SDL=2")
add_subdirectory(${lvgl_SOURCE_DIR} ${lvgl_BINARY_DIR})

add_subdirectory(${UI_DIR} ${CMAKE_BINARY_DIR}/ui)
target_compile_definitions(lib-ui PUBLIC 
  LV_LVGL_H_INCLUDE_SIMPLE 
  LV_SIM_BUILD)

file(READ "${PROJECT_XML}" _project_xml)
string(REGEX MATCH "<project[^>]*name=\"([^\"]+)\"" _ "${_project_xml}")
set(UI_NAME "${CMAKE_MATCH_1}")
if(NOT UI_NAME)
  get_filename_component(UI_NAME "${UI_DIR}" ABSOLUTE)
  get_filename_component(UI_NAME "${UI_NAME}" NAME)
  message(STATUS "No project name in ${UI_DIR}/project.xml; using folder name \"${UI_NAME}\"")
endif()
string(REGEX MATCH "<display[^>]*width=\"([0-9]+)\"[^>]*height=\"([0-9]+)\"" _ "${_project_xml}")
set(UI_WIDTH "${CMAKE_MATCH_1}")
set(UI_HEIGHT "${CMAKE_MATCH_2}")
if(NOT UI_WIDTH OR NOT UI_HEIGHT)
  set(UI_WIDTH 800)
  set(UI_HEIGHT 480)
endif()

if(WEB_ENABLE_KEY_OVERLAY AND EXISTS "${WEB_KEY_OVERLAY_CONFIG_FILE}")
  file(READ "${WEB_KEY_OVERLAY_CONFIG_FILE}" WEB_KEY_OVERLAY_CONFIG)
  set(WEB_KEY_OVERLAY_DEPENDS "${WEB_KEY_OVERLAY_CONFIG_FILE}")
else()
  set(WEB_KEY_OVERLAY_CONFIG "{\"enabled\":false}")
  set(WEB_KEY_OVERLAY_DEPENDS "")
endif()
if(WEB_ENABLE_KEY_OVERLAY)
  set(WEB_ENABLE_KEY_OVERLAY_JS "true")
else()
  set(WEB_ENABLE_KEY_OVERLAY_JS "false")
endif()

if(WEB_ENABLE_KEY_OVERLAY AND EXISTS "${WEB_ASSETS_DIR}")
  file(GLOB WEB_ASSET_FILES CONFIGURE_DEPENDS "${WEB_ASSETS_DIR}/*")
else()
  set(WEB_ASSET_FILES "")
endif()

if(WEB_SINGLE_HTML)
  set(WEB_SINGLE_HTML_JS "true")
  set(WEB_RUNTIME_SCRIPT "{{{ SCRIPT }}}")
  if(WEB_ENABLE_KEY_OVERLAY AND EXISTS "${WEB_HARDWARE_FRAME_IMAGE_FILE}")
    execute_process(
      COMMAND ${Python3_EXECUTABLE} -c
              "import base64,sys;sys.stdout.write(base64.b64encode(open(sys.argv[1],'rb').read()).decode())"
              "${WEB_HARDWARE_FRAME_IMAGE_FILE}"
      OUTPUT_VARIABLE _web_hardware_frame_base64
      ERROR_VARIABLE _web_hardware_frame_error
      RESULT_VARIABLE _web_hardware_frame_result)
    if(NOT _web_hardware_frame_result EQUAL 0)
      message(FATAL_ERROR "Failed to embed ${WEB_HARDWARE_FRAME_IMAGE_FILE}:\n${_web_hardware_frame_error}")
    endif()
    set(WEB_HARDWARE_FRAME_IMAGE_SRC "data:image/png;base64,${_web_hardware_frame_base64}")
    set_property(DIRECTORY APPEND PROPERTY CMAKE_CONFIGURE_DEPENDS
                 "${WEB_HARDWARE_FRAME_IMAGE_FILE}")
  else()
    set(WEB_HARDWARE_FRAME_IMAGE_SRC "")
    message(STATUS "No ${WEB_HARDWARE_FRAME_IMAGE_FILE}; single HTML build has no embedded frame image")
  endif()
else()
  set(WEB_SINGLE_HTML_JS "false")
  set(WEB_RUNTIME_SCRIPT "<script src=\"index.js\"></script>")
  set(WEB_HARDWARE_FRAME_IMAGE_SRC "")
endif()

set_property(DIRECTORY APPEND PROPERTY CMAKE_CONFIGURE_DEPENDS
             "${CMAKE_CURRENT_SOURCE_DIR}/index.html.in"
             ${WEB_KEY_OVERLAY_DEPENDS}
             ${WEB_ASSET_FILES})

add_executable(index main.c)
target_link_libraries(index PRIVATE lib-ui lvgl)
target_compile_definitions(index PRIVATE
  LVGL_PRO_WEB_BUILD
  UI_HEADER="${UI_NAME}.h"
  UI_INIT=${UI_NAME}_init
  UI_WIDTH=${UI_WIDTH}
  UI_HEIGHT=${UI_HEIGHT})

configure_file(
  "${CMAKE_CURRENT_SOURCE_DIR}/index.html.in"
  "${CMAKE_BINARY_DIR}/index.html"
  @ONLY)

if(WEB_SINGLE_HTML)
  set_target_properties(index PROPERTIES
    OUTPUT_NAME "index"
    SUFFIX ".html")
else()
  set_target_properties(index PROPERTIES SUFFIX ".js")
endif()
set_target_properties(index PROPERTIES
  LINK_DEPENDS "${CMAKE_BINARY_DIR}/index.html;${WEB_KEY_OVERLAY_DEPENDS};${WEB_ASSET_FILES}")
target_link_options(index PRIVATE
  "-sUSE_SDL=2"
  "-sSINGLE_FILE=1"
  "-sALLOW_MEMORY_GROWTH=1"
  "-sINITIAL_MEMORY=67108864")
if(WEB_SINGLE_HTML)
  target_link_options(index PRIVATE "--shell-file" "${CMAKE_BINARY_DIR}/index.html")
endif()

if(WEB_SINGLE_HTML)
  add_custom_command(TARGET index POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E make_directory "${WEB_PREVIEW_OUTPUT_PATH}"
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
            "$<TARGET_FILE:index>"
            "${WEB_PREVIEW_OUTPUT_PATH}/index.html"
    COMMAND ${CMAKE_COMMAND} -E rm -f
            "${EXECUTABLE_OUTPUT_PATH}/index.js"
            "${EXECUTABLE_OUTPUT_PATH}/key_overlay.json"
            "${EXECUTABLE_OUTPUT_PATH}/hardware_frame.png"
            "${EXECUTABLE_OUTPUT_PATH}/fbd_hardware_frame.png"
    COMMAND ${CMAKE_COMMAND} -E rm -f
            "${WEB_PREVIEW_OUTPUT_PATH}/index.js"
            "${WEB_PREVIEW_OUTPUT_PATH}/key_overlay.json"
            "${WEB_PREVIEW_OUTPUT_PATH}/hardware_frame.png"
            "${WEB_PREVIEW_OUTPUT_PATH}/fbd_hardware_frame.png")
elseif(WEB_ENABLE_KEY_OVERLAY AND EXISTS "${WEB_ASSETS_DIR}")
  add_custom_command(TARGET index POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E make_directory "${WEB_PREVIEW_OUTPUT_PATH}"
    COMMAND ${CMAKE_COMMAND} -E copy_directory
            "${WEB_ASSETS_DIR}"
            "${EXECUTABLE_OUTPUT_PATH}"
    COMMAND ${CMAKE_COMMAND} -E copy_directory
            "${WEB_ASSETS_DIR}"
            "${WEB_PREVIEW_OUTPUT_PATH}"
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
            "${CMAKE_BINARY_DIR}/index.html"
            "${EXECUTABLE_OUTPUT_PATH}/index.html"
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
            "${CMAKE_BINARY_DIR}/index.html"
            "${WEB_PREVIEW_OUTPUT_PATH}/index.html"
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
            "$<TARGET_FILE:index>"
            "${WEB_PREVIEW_OUTPUT_PATH}/index.js")
else()
  add_custom_command(TARGET index POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E make_directory "${WEB_PREVIEW_OUTPUT_PATH}"
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
            "${CMAKE_BINARY_DIR}/index.html"
            "${EXECUTABLE_OUTPUT_PATH}/index.html"
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
            "${CMAKE_BINARY_DIR}/index.html"
            "${WEB_PREVIEW_OUTPUT_PATH}/index.html"
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
            "$<TARGET_FILE:index>"
            "${WEB_PREVIEW_OUTPUT_PATH}/index.js"
    COMMAND ${CMAKE_COMMAND} -E rm -f
            "${EXECUTABLE_OUTPUT_PATH}/key_overlay.json"
            "${EXECUTABLE_OUTPUT_PATH}/hardware_frame.png"
            "${EXECUTABLE_OUTPUT_PATH}/fbd_hardware_frame.png"
    COMMAND ${CMAKE_COMMAND} -E rm -f
            "${WEB_PREVIEW_OUTPUT_PATH}/key_overlay.json"
            "${WEB_PREVIEW_OUTPUT_PATH}/hardware_frame.png"
            "${WEB_PREVIEW_OUTPUT_PATH}/fbd_hardware_frame.png")
endif()

find_program(HOST_CC NAMES cc clang gcc PATHS /usr/bin /bin /usr/local/bin NO_DEFAULT_PATH)
if(NOT HOST_CC)
  message(FATAL_ERROR "Could not find a host C compiler for the web launch marker")
endif()

add_custom_command(OUTPUT "${EXECUTABLE_OUTPUT_PATH}/web_build_done"
  COMMAND ${CMAKE_COMMAND} -E make_directory "${EXECUTABLE_OUTPUT_PATH}"
  COMMAND "${HOST_CC}" "${CMAKE_CURRENT_SOURCE_DIR}/build_done.c" -o "${EXECUTABLE_OUTPUT_PATH}/web_build_done"
  DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/build_done.c"
  VERBATIM)
add_custom_target(web_build_done ALL
  DEPENDS "${EXECUTABLE_OUTPUT_PATH}/web_build_done")
add_dependencies(index web_build_done)

add_custom_target(run
  COMMAND ${CMAKE_COMMAND} -E echo "Serve ${EXECUTABLE_OUTPUT_PATH}/index.html with: python3 -m http.server 8000 -d ${EXECUTABLE_OUTPUT_PATH}"
  DEPENDS index)
