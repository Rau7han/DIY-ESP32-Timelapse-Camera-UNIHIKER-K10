# Changelog

All notable changes to this project will be documented in this file.

The format is based on [Keep a Changelog](https://keepachangelog.com/en/1.0.0/),
and this project adheres to [Semantic Versioning](https://semver.org/spec/v2.0.0.html).

## [1.0.0] - 2026-01-14

### Added
- Initial release of ESP32 Timelapse Camera firmware
- Complete PlatformIO project structure
- Camera capture functionality with OV2640 support
- SD card storage with automatic directory creation
- Configurable timelapse intervals
- LED status indicators for system feedback
- Serial monitoring with detailed debug output
- Support for multiple image resolutions (QQVGA to QXGA)
- Advanced camera sensor settings (brightness, contrast, exposure, etc.)
- PSRAM detection and optimization
- Brownout detector handling
- Comprehensive README documentation
- Quick Start Guide for beginners
- Detailed wiring guide (WIRING.md)
- Configuration guide (CONFIGURATION.md)
- Video creation helper scripts (bash and Windows batch)
- Example commands and Python script for video creation
- Configuration header file with presets
- .gitignore for build artifacts

### Features
- ✅ Automatic timelapse capture at configurable intervals
- ✅ High-quality image capture up to 1600x1200 (UXGA)
- ✅ Sequential image naming (IMG_00001.jpg, IMG_00002.jpg, etc.)
- ✅ SD card support with FAT32 compatibility
- ✅ Visual LED feedback for status indication
- ✅ Robust error handling for camera and SD card failures
- ✅ Serial output for monitoring and debugging
- ✅ Support for AI-THINKER ESP32-CAM board
- ✅ Optional UNIHIKER K10 integration support

### Documentation
- Complete hardware requirements list with cost estimates
- Detailed wiring diagrams for programming and operation modes
- Step-by-step installation instructions for PlatformIO and Arduino IDE
- Configuration options with examples
- Troubleshooting guide for common issues
- FFmpeg video creation guide with multiple examples
- Expected file sizes and performance metrics

### Examples
- Linux/Mac bash script for automated video creation
- Windows batch script for automated video creation
- FFmpeg command examples for various scenarios
- Python script example for video creation
- Configuration presets (fast test, plant growth, construction, etc.)

### Hardware Support
- ESP32-CAM (AI-THINKER model)
- OV2640 camera module
- SD/SDHC cards (FAT32)
- Optional UNIHIKER K10 display integration

### Software Support
- PlatformIO (recommended)
- Arduino IDE (alternative)
- ESP32 Arduino framework
- SD_MMC library
- ESP32 Camera library

## [Unreleased]

### Planned Features
- [ ] WiFi connectivity for remote monitoring
- [ ] Web interface for configuration
- [ ] UNIHIKER K10 display integration firmware
- [ ] Live preview mode
- [ ] Battery level monitoring
- [ ] Multiple capture modes (burst, HDR)
- [ ] Motion detection triggering
- [ ] Time-based scheduling
- [ ] GPS tagging (with external module)
- [ ] Cloud storage upload support
- [ ] Mobile app integration
- [ ] Power saving modes
- [ ] Real-time clock integration
- [ ] Temperature/humidity sensor integration

### Known Issues
- None reported yet

### Compatibility Notes
- Tested with ESP32-CAM AI-THINKER board
- Compatible with PlatformIO and Arduino IDE
- Requires PSRAM for resolutions above SVGA
- SD card must be FAT32 formatted
- Some USB power banks may auto-shutoff with low current draw

## Version History

### Version 1.0.0 (2026-01-14)
- Initial public release
- Complete basic functionality
- Comprehensive documentation
- Example scripts and guides

---

**Legend:**
- `Added` - New features
- `Changed` - Changes in existing functionality
- `Deprecated` - Soon-to-be removed features
- `Removed` - Removed features
- `Fixed` - Bug fixes
- `Security` - Security improvements

**Contributing:**
Found a bug or have a feature request? Please [open an issue](https://github.com/Rau7han/DIY-ESP32-Timelapse-Camera-UNIHIKER-K10/issues)!
