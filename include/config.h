/**
 * Configuration Header for ESP32 Timelapse Camera
 * 
 * This file contains all user-configurable settings.
 * Edit these values to customize your timelapse camera behavior.
 * 
 * Author: Raushan Kumar
 * License: MIT
 */

#ifndef CONFIG_H
#define CONFIG_H

// ============================================================================
// TIMELAPSE SETTINGS
// ============================================================================

/**
 * Capture interval in milliseconds
 * 
 * Examples:
 * - 1000 = 1 second
 * - 5000 = 5 seconds (fast timelapses)
 * - 10000 = 10 seconds (default, good for testing)
 * - 30000 = 30 seconds
 * - 60000 = 1 minute
 * - 300000 = 5 minutes (plant growth)
 * - 900000 = 15 minutes
 * - 1800000 = 30 minutes (construction)
 * - 3600000 = 1 hour (very slow changes)
 */
#define CAPTURE_INTERVAL_MS 10000

/**
 * JPEG image quality
 * 
 * Range: 0-63
 * - 0-10: Best quality (200-300KB per image)
 * - 10-20: High quality (100-200KB per image) - Recommended
 * - 20-40: Medium quality (50-100KB per image)
 * - 40-63: Low quality (20-50KB per image)
 * 
 * Lower number = Better quality but larger files
 */
#define IMAGE_QUALITY 10

/**
 * Image resolution / frame size
 * 
 * Available options (with PSRAM):
 * - FRAMESIZE_QQVGA  (160x120)   - Testing only
 * - FRAMESIZE_QCIF   (176x144)   - Testing only
 * - FRAMESIZE_HQVGA  (240x176)   - Very low res
 * - FRAMESIZE_QVGA   (320x240)   - Low res
 * - FRAMESIZE_CIF    (400x296)   - Low res
 * - FRAMESIZE_VGA    (640x480)   - Standard
 * - FRAMESIZE_SVGA   (800x600)   - Good for web
 * - FRAMESIZE_XGA    (1024x768)  - HD ready
 * - FRAMESIZE_SXGA   (1280x1024) - High quality
 * - FRAMESIZE_UXGA   (1600x1200) - Recommended for timelapse
 * - FRAMESIZE_QXGA   (2048x1536) - Maximum (requires PSRAM)
 * 
 * Without PSRAM: Maximum FRAMESIZE_SVGA recommended
 */
#define FRAME_SIZE FRAMESIZE_UXGA

// ============================================================================
// HARDWARE PIN DEFINITIONS (ESP32-CAM AI-THINKER)
// ============================================================================

/**
 * Camera pins for AI-THINKER ESP32-CAM board
 * Do not change unless using different board variant
 */
#define PWDN_GPIO_NUM     32
#define RESET_GPIO_NUM    -1
#define XCLK_GPIO_NUM      0
#define SIOD_GPIO_NUM     26
#define SIOC_GPIO_NUM     27
#define Y9_GPIO_NUM       35
#define Y8_GPIO_NUM       34
#define Y7_GPIO_NUM       39
#define Y6_GPIO_NUM       36
#define Y5_GPIO_NUM       21
#define Y4_GPIO_NUM       19
#define Y3_GPIO_NUM       18
#define Y2_GPIO_NUM        5
#define VSYNC_GPIO_NUM    25
#define HREF_GPIO_NUM     23
#define PCLK_GPIO_NUM     22

/**
 * LED pin (built-in flash LED)
 */
#define LED_PIN 4

// ============================================================================
// ADVANCED CAMERA SETTINGS
// ============================================================================

/**
 * Camera sensor settings
 * Adjust these for different lighting conditions
 */

// Brightness: -2 to 2 (0 = default)
#define CAM_BRIGHTNESS 0

// Contrast: -2 to 2 (0 = default)
#define CAM_CONTRAST 0

// Saturation: -2 to 2 (0 = default)
#define CAM_SATURATION 0

// Auto Exposure Level: -2 to 2 (0 = default)
#define CAM_AE_LEVEL 0

// Manual Exposure Value: 0 to 1200 (300 = default)
// Only used if auto exposure is disabled
#define CAM_AEC_VALUE 300

// Horizontal Mirror: 0 = off, 1 = on
#define CAM_HMIRROR 0

// Vertical Flip: 0 = off, 1 = on
#define CAM_VFLIP 0

// ============================================================================
// SD CARD SETTINGS
// ============================================================================

/**
 * SD card mount point and directory
 */
#define SD_MOUNT_POINT "/sdcard"
#define TIMELAPSE_DIR "/timelapse"

/**
 * Filename pattern
 * Images will be named: IMG_00001.jpg, IMG_00002.jpg, etc.
 */
#define FILENAME_PREFIX "IMG_"
#define FILENAME_SUFFIX ".jpg"
#define FILENAME_DIGITS 5

// ============================================================================
// SYSTEM SETTINGS
// ============================================================================

/**
 * Serial communication baud rate
 */
#define SERIAL_BAUD 115200

/**
 * Enable/disable debug output
 * 1 = enabled, 0 = disabled
 */
#define DEBUG_ENABLED 1

/**
 * LED blink patterns for status indication
 */
#define LED_BLINK_CAMERA_OK 2      // 2 blinks = camera initialized
#define LED_BLINK_SD_OK 3          // 3 blinks = SD card initialized
#define LED_BLINK_SD_WARN 5        // 5 blinks = SD card warning
#define LED_BLINK_ERROR 10         // 10 blinks = error

/**
 * LED blink duration in milliseconds
 */
#define LED_BLINK_DURATION 100

// ============================================================================
// FEATURE FLAGS
// ============================================================================

/**
 * Enable/disable brownout detector
 * 0 = disabled (recommended for stability)
 * 1 = enabled
 */
#define ENABLE_BROWNOUT_DETECTOR 0

/**
 * Enable/disable automatic white balance
 * 1 = enabled (recommended)
 * 0 = disabled
 */
#define ENABLE_AWB 1

/**
 * Enable/disable automatic exposure control
 * 1 = enabled (recommended)
 * 0 = disabled (use manual AEC_VALUE)
 */
#define ENABLE_AEC 1

/**
 * Enable/disable automatic gain control
 * 1 = enabled (recommended)
 * 0 = disabled
 */
#define ENABLE_AGC 1

// ============================================================================
// PRESETS
// ============================================================================

/**
 * Uncomment ONE preset below to use predefined settings
 * Or leave all commented to use custom settings above
 */

// PRESET: Fast Test (5 seconds, low resolution)
// #define PRESET_FAST_TEST

// PRESET: Plant Growth (5 minutes, high quality)
// #define PRESET_PLANT_GROWTH

// PRESET: Construction (30 minutes, high quality)
// #define PRESET_CONSTRUCTION

// PRESET: Cloud Motion (10 seconds, high quality)
// #define PRESET_CLOUD_MOTION

// PRESET: Sunset (15 seconds, maximum quality)
// #define PRESET_SUNSET

// Apply preset configurations
#ifdef PRESET_FAST_TEST
    #ifdef CAPTURE_INTERVAL_MS
        #undef CAPTURE_INTERVAL_MS
    #endif
    #ifdef FRAME_SIZE
        #undef FRAME_SIZE
    #endif
    #ifdef IMAGE_QUALITY
        #undef IMAGE_QUALITY
    #endif
    #define CAPTURE_INTERVAL_MS 5000
    #define FRAME_SIZE FRAMESIZE_SVGA
    #define IMAGE_QUALITY 12
#endif

#ifdef PRESET_PLANT_GROWTH
    #ifdef CAPTURE_INTERVAL_MS
        #undef CAPTURE_INTERVAL_MS
    #endif
    #ifdef IMAGE_QUALITY
        #undef IMAGE_QUALITY
    #endif
    #define CAPTURE_INTERVAL_MS 300000  // 5 minutes
    #define IMAGE_QUALITY 10
#endif

#ifdef PRESET_CONSTRUCTION
    #ifdef CAPTURE_INTERVAL_MS
        #undef CAPTURE_INTERVAL_MS
    #endif
    #ifdef IMAGE_QUALITY
        #undef IMAGE_QUALITY
    #endif
    #define CAPTURE_INTERVAL_MS 1800000  // 30 minutes
    #define IMAGE_QUALITY 10
#endif

#ifdef PRESET_CLOUD_MOTION
    #ifdef CAPTURE_INTERVAL_MS
        #undef CAPTURE_INTERVAL_MS
    #endif
    #ifdef IMAGE_QUALITY
        #undef IMAGE_QUALITY
    #endif
    #define CAPTURE_INTERVAL_MS 10000  // 10 seconds
    #define IMAGE_QUALITY 10
#endif

#ifdef PRESET_SUNSET
    #ifdef CAPTURE_INTERVAL_MS
        #undef CAPTURE_INTERVAL_MS
    #endif
    #ifdef IMAGE_QUALITY
        #undef IMAGE_QUALITY
    #endif
    #define CAPTURE_INTERVAL_MS 15000  // 15 seconds
    #define IMAGE_QUALITY 8  // Higher quality
#endif

#endif // CONFIG_H
