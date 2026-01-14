# DIY ESP32 Timelapse Camera with UNIHIKER K10

![License](https://img.shields.io/badge/license-MIT-blue.svg)
![Platform](https://img.shields.io/badge/platform-ESP32-green.svg)
![Language](https://img.shields.io/badge/language-C%2B%2B-orange.svg)

A DIY mini timelapse camera built with ESP32-CAM and UNIHIKER K10. Captures images at configurable intervals and saves them to an SD card. Perfect for creating timelapse videos of plants growing, construction projects, sunsets, or any long-duration events.

## 🌟 Features

- **Automatic Timelapse Capture**: Configurable intervals from seconds to hours
- **High-Quality Images**: Support for resolutions up to 1600x1200 (UXGA)
- **SD Card Storage**: Automatic saving with sequential numbering
- **LED Status Indicators**: Visual feedback for system status
- **Serial Monitoring**: Real-time logs and debugging information
- **Low Power Options**: Optimized for battery-powered operation
- **Easy Configuration**: Simple defines for all settings
- **Robust Error Handling**: Graceful handling of SD card and camera failures

## 📋 Table of Contents

- [Hardware Requirements](#hardware-requirements)
- [Wiring Diagram](#wiring-diagram)
- [Software Setup](#software-setup)
- [Installation](#installation)
- [Configuration](#configuration)
- [Usage](#usage)
- [Timelapse Video Creation](#timelapse-video-creation)
- [Troubleshooting](#troubleshooting)
- [Example Output](#example-output)
- [Contributing](#contributing)
- [License](#license)

## 🛠️ Hardware Requirements

### Essential Components

1. **ESP32-CAM Board** (AI-THINKER model recommended)
   - ESP32 microcontroller with built-in camera interface
   - OV2640 camera module
   - Built-in SD card slot
   - ~$10-15 USD

2. **MicroSD Card**
   - Minimum 4GB, recommended 16GB or higher
   - Class 10 or UHS-1 for fast write speeds
   - Must be formatted as FAT32
   - ~$5-10 USD

3. **USB-to-Serial Programmer** (FTDI or CP2102)
   - For uploading firmware to ESP32-CAM
   - 5V/3.3V compatible
   - ~$5-8 USD

4. **Power Supply**
   - 5V DC power supply with at least 500mA capacity
   - USB power bank or wall adapter
   - Stable power is crucial for camera operation
   - ~$5-10 USD

### Optional Components

5. **UNIHIKER K10** (optional, for advanced control and display)
   - Touchscreen display for camera control
   - Can show live preview and adjust settings
   - ~$50-80 USD

6. **Enclosure/Case**
   - 3D printed case or weatherproof housing
   - Protects hardware from elements
   - ~$5-20 USD

7. **Additional Hardware**
   - Jumper wires for connections
   - Breadboard for prototyping
   - 100-470µF capacitor for power stability
   - Push button for manual reset

**Total Cost (Basic Setup)**: ~$25-40 USD  
**Total Cost (With UNIHIKER)**: ~$75-120 USD

## 🔌 Wiring Diagram

### ESP32-CAM Basic Setup

The ESP32-CAM has everything built-in except the programmer. Here's how to connect it:

#### For Programming (One-time setup):

```
FTDI/USB-to-Serial → ESP32-CAM
━━━━━━━━━━━━━━━━━━━━━━━━━━━━
5V                → 5V
GND               → GND
TX                → U0R (RX)
RX                → U0T (TX)
```

**Important**: 
- Connect GPIO 0 to GND during programming (boot mode)
- Disconnect GPIO 0 from GND after upload for normal operation
- Some programmers may require DTR/RTS connections for auto-reset

#### For Operation:

```
Power Supply → ESP32-CAM
━━━━━━━━━━━━━━━━━━━━━━━━━
5V           → 5V
GND          → GND
```

#### ESP32-CAM Pin Reference (AI-THINKER Board):

```
┌─────────────────────────────────────┐
│  ESP32-CAM (AI-THINKER)             │
│                                     │
│  [Camera]    [SD Card Slot]        │
│                                     │
│  3.3V  5V  GND  U0T  U0R  GPIO16   │
│  GPIO0 GPIO2 GPIO4 GPIO12 GPIO13   │
│  GPIO14 GPIO15                      │
└─────────────────────────────────────┘

Camera Module (OV2640): Pre-connected
SD Card Slot: Built-in (MMC interface)
LED Flash: GPIO 4 (built-in)
```

### With UNIHIKER K10 (Optional Advanced Setup)

The UNIHIKER K10 can be connected via serial or WiFi for enhanced control:

```
UNIHIKER K10 → ESP32-CAM
━━━━━━━━━━━━━━━━━━━━━━━━━━
RX (GPIO)    → U0T (TX)
TX (GPIO)    → U0R (RX)
GND          → GND
```

Or use WiFi for wireless communication (requires additional firmware modifications).

## 💻 Software Setup

### Prerequisites

Install the following software on your computer:

1. **PlatformIO IDE** (recommended) or **Arduino IDE**
   - [PlatformIO Installation Guide](https://platformio.org/install)
   - OR [Arduino IDE Download](https://www.arduino.cc/en/software)

2. **Git** (for cloning the repository)
   - [Git Installation Guide](https://git-scm.com/downloads)

3. **USB Serial Drivers**
   - CH340/CP2102 drivers if not already installed
   - Usually auto-detected on modern systems

### Using PlatformIO (Recommended)

PlatformIO provides better dependency management and build system.

#### Installation Steps:

1. **Install PlatformIO**:
   - Install [Visual Studio Code](https://code.visualstudio.com/)
   - Install PlatformIO extension from VS Code marketplace
   - Or install PlatformIO Core CLI

2. **Clone Repository**:
   ```bash
   git clone https://github.com/Rau7han/DIY-ESP32-Timelapse-Camera-UNIHIKER-K10.git
   cd DIY-ESP32-Timelapse-Camera-UNIHIKER-K10
   ```

3. **Open Project**:
   - Open the project folder in VS Code with PlatformIO
   - PlatformIO will automatically detect `platformio.ini`

4. **Install Dependencies**:
   - PlatformIO will auto-download required libraries
   - No manual library installation needed!

### Using Arduino IDE (Alternative)

If you prefer Arduino IDE:

1. **Install ESP32 Board Support**:
   - Open Arduino IDE
   - Go to `File → Preferences`
   - Add to "Additional Board Manager URLs":
     ```
     https://raw.githubusercontent.com/espressif/arduino-esp32/gh-pages/package_esp32_index.json
     ```
   - Go to `Tools → Board → Board Manager`
   - Search for "esp32" and install "ESP32 by Espressif Systems"

2. **Install Required Libraries**:
   - Go to `Sketch → Include Library → Manage Libraries`
   - Install:
     - "SD" by Arduino
     - "ESP32 Camera" (may be built-in with ESP32 board support)

3. **Open Sketch**:
   - Copy `src/main.cpp` to `timelapse_camera/timelapse_camera.ino`
   - Open in Arduino IDE

4. **Configure Board**:
   - Select `Tools → Board → ESP32 Arduino → AI Thinker ESP32-CAM`
   - Select your COM port
   - Set upload speed to 115200 or 921600

## 📦 Installation

### Step 1: Prepare SD Card

1. Format SD card as FAT32
2. Ensure the SD card is empty or create a backup
3. Insert SD card into ESP32-CAM SD slot

### Step 2: Connect Hardware

1. Connect FTDI programmer to ESP32-CAM as shown in wiring diagram
2. Connect GPIO 0 to GND (for programming mode)
3. Connect 5V power supply

### Step 3: Upload Firmware

#### Using PlatformIO:

```bash
# From project directory
pio run --target upload

# Or use VS Code: Click "Upload" button in PlatformIO toolbar
```

#### Using Arduino IDE:

1. Open the sketch
2. Click "Upload" button
3. Wait for "Done uploading" message

### Step 4: Disconnect Programming Pins

1. Disconnect GPIO 0 from GND
2. Press reset button or power cycle the board

### Step 5: Verify Operation

1. Open Serial Monitor (115200 baud)
2. You should see initialization messages
3. LED should blink to indicate status
4. Camera will start capturing images automatically

## ⚙️ Configuration

### Basic Configuration

Edit the defines at the top of `src/main.cpp`:

```cpp
// Capture interval in milliseconds
#define CAPTURE_INTERVAL_MS 10000  // 10 seconds

// Image quality (0-63, lower = better quality)
#define IMAGE_QUALITY 10

// Resolution (see CONFIGURATION.md for all options)
#define FRAME_SIZE FRAMESIZE_UXGA  // 1600x1200
```

### Common Timelapse Intervals

| Scenario | Recommended Interval | Example |
|----------|---------------------|---------|
| Fast-moving clouds | 5-10 seconds | `5000` |
| Plant growth | 5-15 minutes | `300000` |
| Construction | 15-30 minutes | `900000` |
| Sunset/sunrise | 10-30 seconds | `20000` |
| Traffic flow | 1-5 seconds | `2000` |
| Long-term projects | 1-6 hours | `3600000` |

### Advanced Configuration

For detailed configuration options, see [CONFIGURATION.md](CONFIGURATION.md).

Options include:
- Image resolution settings
- Camera sensor adjustments (brightness, contrast, etc.)
- Pin configuration for different ESP32-CAM variants
- Power optimization settings

## 🎬 Usage

### Starting a Timelapse

1. **Power on the device**
   - Connect 5V power supply
   - Device will initialize (takes 3-5 seconds)

2. **Monitor Status via LED**
   - 2 blinks: Camera ready
   - 3 blinks: SD card ready
   - Continuous: Capturing images
   - 5 blinks: SD card error (check card)
   - 10 blinks: Camera error (check connections)

3. **Check Serial Output** (optional)
   - Connect USB serial adapter
   - Open Serial Monitor at 115200 baud
   - View real-time capture logs

### Stopping a Timelapse

1. Disconnect power when done
2. Remove SD card
3. Images are saved in `/timelapse/` folder
4. Files named: `IMG_00001.jpg`, `IMG_00002.jpg`, etc.

### Retrieving Images

1. Remove SD card from ESP32-CAM
2. Insert into computer via SD card reader
3. Navigate to `/timelapse/` folder
4. Copy all JPG files to computer

## 🎥 Timelapse Video Creation

### Using FFmpeg (Recommended)

FFmpeg is a powerful free tool for video creation.

#### Installation:
- **Windows**: Download from [ffmpeg.org](https://ffmpeg.org/download.html)
- **Mac**: `brew install ffmpeg`
- **Linux**: `sudo apt install ffmpeg`

#### Create Video:

```bash
# Navigate to folder with images
cd /path/to/timelapse/folder

# Create 30fps video
ffmpeg -framerate 30 -pattern_type glob -i 'IMG_*.jpg' -c:v libx264 -pix_fmt yuv420p -crf 20 timelapse.mp4

# Create 60fps video (smoother)
ffmpeg -framerate 60 -pattern_type glob -i 'IMG_*.jpg' -c:v libx264 -pix_fmt yuv420p -crf 20 timelapse_60fps.mp4

# Create with specific resolution
ffmpeg -framerate 30 -pattern_type glob -i 'IMG_*.jpg' -vf scale=1920:1080 -c:v libx264 -pix_fmt yuv420p -crf 20 timelapse_1080p.mp4
```

#### Parameters Explained:
- `-framerate 30`: Output video frame rate (24, 30, or 60 fps recommended)
- `-crf 20`: Quality (0=best, 51=worst, 20-23 recommended)
- `-pix_fmt yuv420p`: Compatibility with most players
- `scale=1920:1080`: Resize to specific resolution

### Using Online Tools

- **Free Online Video Makers**:
  - [Kapwing](https://www.kapwing.com/)
  - [Canva](https://www.canva.com/)
  - [Clideo](https://clideo.com/)

- **Upload your images in sequence**
- **Set frame rate** (24-60 fps)
- **Export as MP4**

### Using Windows Movie Maker / iMovie

1. Import image sequence
2. Set duration per image (0.033s for 30fps, 0.016s for 60fps)
3. Add transitions (optional)
4. Export as video

## 🐛 Troubleshooting

### Camera Won't Initialize

**Symptoms**: 10 rapid LED blinks, "Camera init failed" in serial output

**Solutions**:
1. Check camera ribbon cable connection
2. Ensure camera module is properly seated
3. Try different power supply (needs stable 5V, 500mA+)
4. Add 100µF capacitor between 5V and GND
5. Check if PSRAM is detected (for high-resolution modes)

### SD Card Not Detected

**Symptoms**: 5 LED blinks, "SD Card Mount Failed" in serial output

**Solutions**:
1. Ensure SD card is formatted as FAT32
2. Try a different SD card (some cards are incompatible)
3. Check SD card is fully inserted
4. Use Class 10 or UHS-1 card for better compatibility
5. Try reformatting the card
6. Clean SD card contacts

### Images Are Dark/Overexposed

**Solutions**:
1. Adjust camera exposure settings in code
2. Change `s->set_ae_level()` value (-2 to +2)
3. Modify `s->set_aec_value()` for manual exposure
4. Check lighting conditions

### Power Issues / Brownout Resets

**Symptoms**: Random resets, "Brownout detector triggered"

**Solutions**:
1. Use a higher-quality power supply (2A recommended)
2. Add large capacitor (470µF or 1000µF) near power pins
3. Keep USB cable short (< 1 meter)
4. Avoid cheap USB cables with high resistance
5. Use external 5V power supply instead of USB

### Images Not Saving

**Symptoms**: Capture logs appear but no files on SD card

**Solutions**:
1. Check SD card has free space
2. Ensure `/timelapse/` folder was created
3. Check SD card write-protect switch
4. Try formatting SD card fresh
5. Check file system isn't corrupted

### Out of Memory Errors

**Symptoms**: "Failed to allocate frame buffer"

**Solutions**:
1. Reduce `FRAME_SIZE` to lower resolution
2. Check if board has PSRAM (required for high resolutions)
3. Use SVGA or XGA instead of UXGA
4. Reduce `IMAGE_QUALITY` number (increases compression)

### Serial Monitor Shows Garbage

**Solutions**:
1. Set baud rate to 115200
2. Check TX/RX aren't swapped
3. Ensure ground connection is solid
4. Try different USB cable

## 📸 Example Output

### Sample Timelapse Projects

**Plant Growth Timelapse**
- Interval: 10 minutes
- Duration: 7 days
- Images: 1,008 frames
- Video: 33 seconds at 30fps

**Sunset Timelapse**
- Interval: 10 seconds
- Duration: 1 hour
- Images: 360 frames
- Video: 12 seconds at 30fps

**Construction Project**
- Interval: 30 minutes
- Duration: 30 days
- Images: 1,440 frames
- Video: 48 seconds at 30fps

### Expected File Sizes

| Resolution | Quality | Approx. File Size | 1000 Images |
|------------|---------|-------------------|-------------|
| UXGA (1600x1200) | High (10) | 200-300 KB | ~250 MB |
| SXGA (1280x1024) | High (10) | 150-200 KB | ~175 MB |
| XGA (1024x768) | High (10) | 80-120 KB | ~100 MB |
| SVGA (800x600) | High (10) | 40-80 KB | ~60 MB |

## 🤝 Contributing

Contributions are welcome! Here's how you can help:

1. **Report Bugs**: Open an issue with details
2. **Suggest Features**: Share your ideas
3. **Submit Pull Requests**: Improve code or documentation
4. **Share Your Timelapses**: Post examples and use cases

### Development Setup

```bash
# Fork the repository
git clone https://github.com/YOUR_USERNAME/DIY-ESP32-Timelapse-Camera-UNIHIKER-K10.git
cd DIY-ESP32-Timelapse-Camera-UNIHIKER-K10

# Create a feature branch
git checkout -b feature/your-feature-name

# Make changes and commit
git commit -am "Add your feature"

# Push and create pull request
git push origin feature/your-feature-name
```

## 📄 License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.

## 👤 Author

**Raushan Kumar**

- GitHub: [@Rau7han](https://github.com/Rau7han)

## 🙏 Acknowledgments

- ESP32 community for excellent libraries and support
- Espressif for ESP32 platform
- Arduino community for development tools
- UNIHIKER team for the K10 display module
- All contributors and users of this project

## 📚 Additional Resources

- [ESP32-CAM Documentation](https://docs.espressif.com/)
- [OV2640 Camera Datasheet](https://www.uctronics.com/download/OV2640DS.pdf)
- [PlatformIO Documentation](https://docs.platformio.org/)
- [FFmpeg Documentation](https://ffmpeg.org/documentation.html)
- [Timelapse Photography Guide](https://en.wikipedia.org/wiki/Time-lapse_photography)

---

**⭐ If you find this project helpful, please consider giving it a star!**

**🐛 Found a bug? Please open an issue.**

**💡 Have a suggestion? We'd love to hear it!**
