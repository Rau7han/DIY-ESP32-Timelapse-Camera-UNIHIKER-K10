/**
 * ESP32 Timelapse Camera with UNIHIKER K10
 * 
 * This firmware captures images at configurable intervals and saves them to an SD card.
 * Compatible with ESP32-CAM modules with OV2640 camera sensor.
 * 
 * Features:
 * - Configurable capture intervals
 * - SD card storage
 * - Auto-incrementing filename
 * - LED status indicator
 * - Serial monitoring
 * 
 * Hardware Requirements:
 * - ESP32-CAM board
 * - OV2640 camera module
 * - MicroSD card (formatted as FAT32)
 * - UNIHIKER K10 (optional for display/control)
 * 
 * Author: Raushan Kumar
 * License: MIT
 */

#include <Arduino.h>
#include "esp_camera.h"
#include "FS.h"
#include "SD_MMC.h"
#include "soc/soc.h"
#include "soc/rtc_cntl_reg.h"
#include "driver/rtc_io.h"

// ============================================================================
// CONFIGURATION
// ============================================================================

// Timelapse Configuration
#define CAPTURE_INTERVAL_MS 10000  // Time between captures in milliseconds (10 seconds default)
#define IMAGE_QUALITY 10           // JPEG quality (0-63, lower means higher quality)
#define FRAME_SIZE FRAMESIZE_UXGA  // Image resolution (UXGA = 1600x1200)

// Pin Definitions for ESP32-CAM (AI-THINKER)
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

// LED Pin (built-in flash LED on GPIO 4)
#define LED_PIN 4

// ============================================================================
// GLOBAL VARIABLES
// ============================================================================

unsigned long lastCaptureTime = 0;
int imageCount = 0;
bool sdCardAvailable = false;

// ============================================================================
// FUNCTION DECLARATIONS
// ============================================================================

bool initCamera();
bool initSDCard();
void captureAndSaveImage();
String getNextFilename();
void blinkLED(int times, int delayMs);

// ============================================================================
// SETUP
// ============================================================================

void setup() {
  // Disable brownout detector
  WRITE_PERI_REG(RTC_CNTL_BROWN_OUT_REG, 0);
  
  // Initialize Serial
  Serial.begin(115200);
  Serial.setDebugOutput(true);
  Serial.println("\n\n======================================");
  Serial.println("ESP32 Timelapse Camera Starting...");
  Serial.println("======================================");
  
  // Initialize LED pin
  pinMode(LED_PIN, OUTPUT);
  digitalWrite(LED_PIN, LOW);
  
  // Initialize Camera
  Serial.println("\n[1/2] Initializing Camera...");
  if (!initCamera()) {
    Serial.println("ERROR: Camera initialization failed!");
    Serial.println("System halted. Please reset the device.");
    blinkLED(10, 200);  // Error indication
    while (1) { delay(1000); }
  }
  Serial.println("SUCCESS: Camera initialized");
  blinkLED(2, 100);
  
  // Initialize SD Card
  Serial.println("\n[2/2] Initializing SD Card...");
  if (!initSDCard()) {
    Serial.println("WARNING: SD Card initialization failed!");
    Serial.println("Images will not be saved.");
    sdCardAvailable = false;
    blinkLED(5, 100);  // Warning indication
  } else {
    Serial.println("SUCCESS: SD Card initialized");
    sdCardAvailable = true;
    blinkLED(3, 100);
  }
  
  // Print Configuration
  Serial.println("\n======================================");
  Serial.println("Configuration:");
  Serial.println("======================================");
  Serial.printf("Capture Interval: %lu ms (%.1f seconds)\n", CAPTURE_INTERVAL_MS, CAPTURE_INTERVAL_MS / 1000.0);
  Serial.printf("Image Quality: %d (0=best, 63=worst)\n", IMAGE_QUALITY);
  Serial.printf("Frame Size: %d\n", FRAME_SIZE);
  Serial.printf("SD Card Status: %s\n", sdCardAvailable ? "Available" : "Not Available");
  Serial.println("======================================\n");
  
  Serial.println("System Ready! Starting timelapse capture...\n");
  
  // Initialize capture time
  lastCaptureTime = millis();
}

// ============================================================================
// MAIN LOOP
// ============================================================================

void loop() {
  unsigned long currentTime = millis();
  
  // Check if it's time to capture
  if (currentTime - lastCaptureTime >= CAPTURE_INTERVAL_MS) {
    captureAndSaveImage();
    lastCaptureTime = currentTime;
  }
  
  // Small delay to prevent watchdog issues
  delay(10);
}

// ============================================================================
// CAMERA INITIALIZATION
// ============================================================================

bool initCamera() {
  camera_config_t config;
  config.ledc_channel = LEDC_CHANNEL_0;
  config.ledc_timer = LEDC_TIMER_0;
  config.pin_d0 = Y2_GPIO_NUM;
  config.pin_d1 = Y3_GPIO_NUM;
  config.pin_d2 = Y4_GPIO_NUM;
  config.pin_d3 = Y5_GPIO_NUM;
  config.pin_d4 = Y6_GPIO_NUM;
  config.pin_d5 = Y7_GPIO_NUM;
  config.pin_d6 = Y8_GPIO_NUM;
  config.pin_d7 = Y9_GPIO_NUM;
  config.pin_xclk = XCLK_GPIO_NUM;
  config.pin_pclk = PCLK_GPIO_NUM;
  config.pin_vsync = VSYNC_GPIO_NUM;
  config.pin_href = HREF_GPIO_NUM;
  config.pin_sscb_sda = SIOD_GPIO_NUM;
  config.pin_sscb_scl = SIOC_GPIO_NUM;
  config.pin_pwdn = PWDN_GPIO_NUM;
  config.pin_reset = RESET_GPIO_NUM;
  config.xclk_freq_hz = 20000000;
  config.pixel_format = PIXFORMAT_JPEG;
  
  // Initialize with high specs to pre-allocate larger buffers
  if (psramFound()) {
    config.frame_size = FRAME_SIZE;
    config.jpeg_quality = IMAGE_QUALITY;
    config.fb_count = 2;
    Serial.println("PSRAM found - using high quality settings");
  } else {
    config.frame_size = FRAMESIZE_SVGA;
    config.jpeg_quality = 12;
    config.fb_count = 1;
    Serial.println("PSRAM not found - using lower quality settings");
  }
  
  // Camera init
  esp_err_t err = esp_camera_init(&config);
  if (err != ESP_OK) {
    Serial.printf("Camera init failed with error 0x%x\n", err);
    return false;
  }
  
  // Additional sensor settings
  sensor_t *s = esp_camera_sensor_get();
  if (s != NULL) {
    // Adjust sensor settings for better image quality
    s->set_brightness(s, 0);     // -2 to 2
    s->set_contrast(s, 0);       // -2 to 2
    s->set_saturation(s, 0);     // -2 to 2
    s->set_special_effect(s, 0); // 0 to 6 (0 - No Effect)
    s->set_whitebal(s, 1);       // 0 = disable , 1 = enable
    s->set_awb_gain(s, 1);       // 0 = disable , 1 = enable
    s->set_wb_mode(s, 0);        // 0 to 4 - if awb_gain enabled
    s->set_exposure_ctrl(s, 1);  // 0 = disable , 1 = enable
    s->set_aec2(s, 0);           // 0 = disable , 1 = enable
    s->set_ae_level(s, 0);       // -2 to 2
    s->set_aec_value(s, 300);    // 0 to 1200
    s->set_gain_ctrl(s, 1);      // 0 = disable , 1 = enable
    s->set_agc_gain(s, 0);       // 0 to 30
    s->set_gainceiling(s, (gainceiling_t)0);  // 0 to 6
    s->set_bpc(s, 0);            // 0 = disable , 1 = enable
    s->set_wpc(s, 1);            // 0 = disable , 1 = enable
    s->set_raw_gma(s, 1);        // 0 = disable , 1 = enable
    s->set_lenc(s, 1);           // 0 = disable , 1 = enable
    s->set_hmirror(s, 0);        // 0 = disable , 1 = enable
    s->set_vflip(s, 0);          // 0 = disable , 1 = enable
    s->set_dcw(s, 1);            // 0 = disable , 1 = enable
    s->set_colorbar(s, 0);       // 0 = disable , 1 = enable
  }
  
  return true;
}

// ============================================================================
// SD CARD INITIALIZATION
// ============================================================================

bool initSDCard() {
  // Mount SD Card
  if (!SD_MMC.begin("/sdcard", true)) {  // true = 1-bit mode (more compatible)
    Serial.println("SD Card Mount Failed");
    return false;
  }
  
  uint8_t cardType = SD_MMC.cardType();
  if (cardType == CARD_NONE) {
    Serial.println("No SD Card attached");
    return false;
  }
  
  // Print SD Card info
  Serial.print("SD Card Type: ");
  if (cardType == CARD_MMC) {
    Serial.println("MMC");
  } else if (cardType == CARD_SD) {
    Serial.println("SDSC");
  } else if (cardType == CARD_SDHC) {
    Serial.println("SDHC");
  } else {
    Serial.println("UNKNOWN");
  }
  
  uint64_t cardSize = SD_MMC.cardSize() / (1024 * 1024);
  Serial.printf("SD Card Size: %lluMB\n", cardSize);
  Serial.printf("Total space: %lluMB\n", SD_MMC.totalBytes() / (1024 * 1024));
  Serial.printf("Used space: %lluMB\n", SD_MMC.usedBytes() / (1024 * 1024));
  
  // Create timelapse directory if it doesn't exist
  if (!SD_MMC.exists("/timelapse")) {
    if (SD_MMC.mkdir("/timelapse")) {
      Serial.println("Created /timelapse directory");
    } else {
      Serial.println("Failed to create /timelapse directory");
    }
  }
  
  return true;
}

// ============================================================================
// CAPTURE AND SAVE IMAGE
// ============================================================================

void captureAndSaveImage() {
  Serial.println("----------------------------------------");
  Serial.printf("Capturing image #%d...\n", imageCount + 1);
  
  // Turn on LED indicator
  digitalWrite(LED_PIN, HIGH);
  
  // Capture image
  camera_fb_t *fb = esp_camera_fb_get();
  if (!fb) {
    Serial.println("ERROR: Camera capture failed");
    digitalWrite(LED_PIN, LOW);
    return;
  }
  
  Serial.printf("Image captured: %d bytes\n", fb->len);
  
  // Save to SD Card if available
  if (sdCardAvailable) {
    String filename = getNextFilename();
    
    File file = SD_MMC.open(filename.c_str(), FILE_WRITE);
    if (!file) {
      Serial.printf("ERROR: Failed to open file: %s\n", filename.c_str());
    } else {
      file.write(fb->buf, fb->len);
      file.close();
      imageCount++;
      Serial.printf("SUCCESS: Saved as %s\n", filename.c_str());
    }
  } else {
    Serial.println("INFO: SD Card not available, image not saved");
  }
  
  // Return the frame buffer
  esp_camera_fb_return(fb);
  
  // Turn off LED indicator
  digitalWrite(LED_PIN, LOW);
  
  Serial.printf("Next capture in %lu seconds\n", CAPTURE_INTERVAL_MS / 1000);
  Serial.println("----------------------------------------\n");
}

// ============================================================================
// GET NEXT FILENAME
// ============================================================================

String getNextFilename() {
  // Format: /timelapse/IMG_XXXXX.jpg (e.g., IMG_00001.jpg)
  char filename[40];
  snprintf(filename, sizeof(filename), "/timelapse/IMG_%05d.jpg", imageCount);
  return String(filename);
}

// ============================================================================
// LED BLINK UTILITY
// ============================================================================

void blinkLED(int times, int delayMs) {
  for (int i = 0; i < times; i++) {
    digitalWrite(LED_PIN, HIGH);
    delay(delayMs);
    digitalWrite(LED_PIN, LOW);
    delay(delayMs);
  }
}
