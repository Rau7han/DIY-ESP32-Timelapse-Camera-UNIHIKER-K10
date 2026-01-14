# ESP32 Timelapse Camera Configuration

This file documents the configuration options available in the firmware.
To change settings, edit the `src/main.cpp` file and modify the `#define` values.

## Timelapse Settings

### CAPTURE_INTERVAL_MS
- **Description**: Time between captures in milliseconds
- **Default**: 10000 (10 seconds)
- **Examples**:
  - 5000 = 5 seconds
  - 30000 = 30 seconds
  - 60000 = 1 minute
  - 300000 = 5 minutes
  - 3600000 = 1 hour

### IMAGE_QUALITY
- **Description**: JPEG compression quality
- **Default**: 10
- **Range**: 0-63
  - 0 = Best quality (largest file size)
  - 10 = High quality (recommended)
  - 20 = Medium quality
  - 63 = Lowest quality (smallest file size)

### FRAME_SIZE
- **Description**: Image resolution
- **Default**: FRAMESIZE_UXGA (1600x1200)
- **Available Options**:
  - FRAMESIZE_QQVGA (160x120)
  - FRAMESIZE_QCIF (176x144)
  - FRAMESIZE_HQVGA (240x176)
  - FRAMESIZE_QVGA (320x240)
  - FRAMESIZE_CIF (400x296)
  - FRAMESIZE_VGA (640x480)
  - FRAMESIZE_SVGA (800x600)
  - FRAMESIZE_XGA (1024x768)
  - FRAMESIZE_SXGA (1280x1024)
  - FRAMESIZE_UXGA (1600x1200) - **Recommended for timelapse**
  - FRAMESIZE_QXGA (2048x1536) - **Requires PSRAM**

## Hardware Pin Configuration

Pin definitions are set for the AI-THINKER ESP32-CAM board. If you're using a different ESP32-CAM variant, you may need to adjust these pins.

### Camera Pins (OV2640)
- PWDN: GPIO 32
- RESET: Not connected (-1)
- XCLK: GPIO 0
- SIOD (SDA): GPIO 26
- SIOC (SCL): GPIO 27
- Y9: GPIO 35
- Y8: GPIO 34
- Y7: GPIO 39
- Y6: GPIO 36
- Y5: GPIO 21
- Y4: GPIO 19
- Y3: GPIO 18
- Y2: GPIO 5
- VSYNC: GPIO 25
- HREF: GPIO 23
- PCLK: GPIO 22

### LED Pin
- Flash LED: GPIO 4

## Advanced Camera Settings

The firmware includes advanced camera sensor settings that can be adjusted in the `initCamera()` function:

- **Brightness**: -2 to 2 (default: 0)
- **Contrast**: -2 to 2 (default: 0)
- **Saturation**: -2 to 2 (default: 0)
- **White Balance**: Enabled by default
- **Auto Exposure**: Enabled by default
- **Auto Gain**: Enabled by default
- **Mirror/Flip**: Disabled by default

## SD Card Settings

The firmware uses 1-bit SD_MMC mode for better compatibility. Images are saved to the `/timelapse/` directory with the naming format `IMG_XXXXX.jpg`.

## Performance Notes

- **With PSRAM**: Higher resolution images (up to QXGA) with better quality
- **Without PSRAM**: Limited to SVGA resolution to prevent memory issues
- **Recommended SD Card**: Class 10 or UHS-1 for fast write speeds
- **SD Card Format**: FAT32 (most compatible)

## Power Considerations

The ESP32-CAM draws approximately:
- 180-250mA during capture (with LED on)
- 80-120mA in idle/waiting mode
- Use a stable 5V power supply with at least 500mA capacity
- Consider adding a capacitor (100-470µF) near the power pins for stability

## Troubleshooting

If you experience issues:
1. Brownout detector is disabled in the code (helps with power issues)
2. LED blinks indicate status:
   - 2 blinks: Camera initialized successfully
   - 3 blinks: SD card initialized successfully
   - 5 blinks: SD card initialization failed (warning)
   - 10 blinks: Camera initialization failed (error)
3. Check Serial Monitor at 115200 baud for detailed logs
