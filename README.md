# UNIHIKER K10 Time-Lapse Camera 📷

A beautiful, modern time-lapse camera with an intuitive UI for the UNIHIKER K10 (ESP32-S3) board.

![Version](https://img.shields.io/badge/version-v3.0-blue)
![Platform](https://img.shields.io/badge/platform-ESP32--S3-green)
![License](https://img.shields.io/badge/license-MIT-yellow)

## ✨ Features

- **Live Stream Mode**: Preview camera feed on the display
- **Time-Lapse Recording**: Capture images at custom intervals to SD card
- **Selectable Resolution**: Choose from 5 quality presets (QVGA to SXGA)
- **Configurable Intervals**: Set hours, minutes, and seconds for capture timing
- **Beautiful UI**: Modern card-based interface with smooth animations
- **SD Card Support**: Automatic file numbering and storage management
- **Easy Controls**: Simple A+B button combo to exit from any screen
- **Real-time Stats**: Monitor captured images, elapsed time, and storage usage

## 🛠️ Hardware Requirements

- **UNIHIKER K10 Board** (ESP32-S3 based)
- **OV2640 Camera Module** (connected to K10's camera interface)
- **MicroSD Card** (for storing time-lapse images)
- **USB-C Cable** (for programming and power)

## 📋 Prerequisites

Before uploading the firmware, ensure you have:

1. **Arduino IDE** (version 1.8.19 or newer) or **Arduino CLI**
2. **ESP32 Board Support Package** installed
3. **Required Libraries**:
   - `UNIHIKER_K10` library (for K10 board support)
   - `TFT_eSPI` (for display)
   - `SD` (for SD card operations)
   - `esp_camera` (included with ESP32 package)

## 🚀 Installation

### 1. Install Arduino IDE & ESP32 Support

1. Download and install [Arduino IDE](https://www.arduino.cc/en/software)
2. Add ESP32 board manager URL:
   - Go to `File → Preferences`
   - Add to "Additional Board Manager URLs":
     ```
     https://raw.githubusercontent.com/espressif/arduino-esp32/gh-pages/package_esp32_index.json
     ```
3. Install ESP32 boards:
   - Go to `Tools → Board → Board Manager`
   - Search for "ESP32" and install "esp32 by Espressif Systems"

### 2. Install Required Libraries

Install these libraries via `Sketch → Include Library → Manage Libraries`:
- UNIHIKER_K10
- TFT_eSPI
- SD (usually pre-installed)

### 3. Upload the Firmware

1. Open `K10_TimeLapse_Camera.ino` in Arduino IDE
2. Select the board:
   - `Tools → Board → ESP32 Arduino → ESP32S3 Dev Module`
3. Configure the settings:
   - **USB CDC On Boot**: Enabled
   - **Flash Size**: 4MB (or as per your board)
   - **Partition Scheme**: Default 4MB with spiffs
   - **PSRAM**: QSPI PSRAM (if available)
4. Select the correct COM port:
   - `Tools → Port → [Your K10's COM port]`
5. Click **Upload** button

## 🎮 Usage

### Main Menu

Upon startup, you'll see a beautiful splash screen followed by the main menu with two options:

1. **Live Stream** - Preview camera feed on display (no recording)
2. **Time-Lapse** - Configure and start time-lapse recording

### Time-Lapse Mode

1. **Select Resolution**: Choose from 5 quality presets
   - QVGA (240x320) - Fast
   - VGA (640x480) - Good
   - SVGA (800x600) - Better
   - HD (1280x720) - HD
   - SXGA (1280x1024) - Best

2. **Set Interval**:
   - Hours: 0-24
   - Minutes: 0-59
   - Seconds: 0-59
   - Minimum interval: 1 second

3. **Confirm Settings**: Review your configuration
   - Resolution
   - Interval
   - SD Card status
   - Next file name

4. **Recording**: 
   - Real-time statistics displayed
   - Progress bar shows time until next capture
   - Hold A+B buttons to stop recording

### Button Controls

- **Button A**: Navigate/Increment
- **Button B**: Select/Confirm
- **A+B (Hold)**: Exit to menu (from any screen)

## 📁 File Structure

```
DIY-ESP32-Timelapse-Camera-UNIHIKER-K10/
├── K10_TimeLapse_Camera/
│   └── K10_TimeLapse_Camera.ino    # Main firmware file
├── README.md                        # This file
└── LICENSE                          # MIT License
```

## 💾 SD Card

- Images are saved as `img00001.jpg`, `img00002.jpg`, etc.
- The camera automatically scans for existing files and continues numbering
- Format your SD card as FAT32 for best compatibility
- Ensure you have enough space for your time-lapse session

## 🎨 UI Design

The application features a modern, card-based UI with:
- Smooth animations and transitions
- Color-coded information cards
- Real-time progress indicators
- Beautiful splash screen with author attribution
- Clear button indicators
- Status feedback for all operations

## 🔧 Troubleshooting

### Camera Init Failed
- Check camera module connections
- Ensure camera is properly seated in K10's connector
- Try power cycling the board

### SD Card Not Found
- Verify SD card is properly inserted
- Format card as FAT32
- Check if card is not write-protected
- Try a different SD card

### Compilation Errors
- Verify all libraries are installed
- Check ESP32 board package version
- Ensure correct board is selected in Tools menu

## 👨‍💻 Author

**Rau7han** - 2026

*Based on original work by DJS (11/1/2025)*

## 📄 License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.

## 🙏 Acknowledgments

- UNIHIKER K10 development team for the excellent hardware platform
- ESP32 community for extensive camera support
- TFT_eSPI library maintainers

## 🤝 Contributing

Contributions are welcome! Feel free to:
- Report bugs
- Suggest new features
- Submit pull requests
- Improve documentation

---

**Made with ❤️ for the maker community**
