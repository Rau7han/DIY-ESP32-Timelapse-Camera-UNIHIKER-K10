# Quick Start Guide

## 🎯 Getting Started in 5 Minutes

### Step 1: Hardware Setup
1. Connect the OV2640 camera module to your UNIHIKER K10 board
2. Insert a formatted microSD card (FAT32)
3. Connect the K10 to your computer via USB-C

### Step 2: Software Setup
```bash
# Install Arduino IDE if you haven't already
# Add ESP32 board support URL in Preferences:
https://raw.githubusercontent.com/espressif/arduino-esp32/gh-pages/package_esp32_index.json

# Install required libraries:
- UNIHIKER_K10
- TFT_eSPI
```

### Step 3: Upload Firmware
1. Open `K10_TimeLapse_Camera/K10_TimeLapse_Camera.ino`
2. Select board: **Tools → Board → ESP32S3 Dev Module**
3. Select your COM port
4. Click **Upload**

### Step 4: Use the Camera

#### Live Stream Mode 🎥
1. Power on → Select "Live Stream"
2. Press **B** to start streaming
3. Hold **A+B** to exit

#### Time-Lapse Mode 📸
1. Power on → Select "Time-Lapse"
2. Choose resolution (recommended: VGA for balanced quality/speed)
3. Set interval:
   - **Hours**: Press **A** to increment, **B** to confirm
   - **Minutes**: Press **A** to increment, **B** to confirm
   - **Seconds**: Press **A** to increment, **B** to confirm
4. Review settings and press **B** to start
5. Hold **A+B** to stop recording

## 📊 Example Time-Lapse Sessions

### Quick Test (Every 5 seconds)
- **Interval**: 00:00:05
- **Resolution**: VGA (640x480)
- **Duration**: 5 minutes
- **Result**: 60 images (~30 MB)

### Plant Growth (Every 30 minutes)
- **Interval**: 00:30:00
- **Resolution**: HD (1280x720)
- **Duration**: 24 hours
- **Result**: 48 images (~100 MB)

### Sky/Clouds (Every 10 seconds)
- **Interval**: 00:00:10
- **Resolution**: SVGA (800x600)
- **Duration**: 1 hour
- **Result**: 360 images (~180 MB)

### Construction/Workshop (Every 5 minutes)
- **Interval**: 00:05:00
- **Resolution**: SXGA (1280x1024)
- **Duration**: 8 hours
- **Result**: 96 images (~200 MB)

## 🎬 Creating a Video from Your Time-Lapse

Use **FFmpeg** to convert your images to video:

```bash
# Navigate to your SD card folder
cd /path/to/sd/card

# Create MP4 video at 30fps
ffmpeg -framerate 30 -pattern_type glob -i 'img*.jpg' \
       -c:v libx264 -pix_fmt yuv420p -crf 18 \
       output.mp4

# Or create a GIF
ffmpeg -framerate 10 -pattern_type glob -i 'img*.jpg' \
       -vf "scale=640:-1:flags=lanczos,split[s0][s1];[s0]palettegen[p];[s1][p]paletteuse" \
       output.gif
```

## 💡 Tips & Tricks

1. **Battery Life**: Use a power bank for extended outdoor sessions
2. **Stability**: Use a tripod or stable mount to prevent camera shake
3. **Lighting**: Avoid direct sunlight on the lens; use shade or diffuser
4. **SD Card**: Use Class 10 or higher for best performance
5. **File Management**: The camera auto-numbers files, so you can run multiple sessions
6. **Quality vs Size**: 
   - VGA: Best balance for most projects
   - HD/SXGA: Use for important projects where quality matters
   - QVGA: Use for very long sessions to save space

## ⚠️ Common Issues

**Camera shows "Camera init failed"**
- Check camera cable connections
- Power cycle the device
- Ensure camera module is compatible (OV2640)

**"SD Card NOT FOUND!"**
- Reinsert SD card
- Format as FAT32
- Check card isn't locked (write-protect switch)

**Images are blurry**
- Ensure camera is stable and not moving
- Check lens is clean
- Avoid very low light conditions

**Device freezes**
- Power cycle
- Check SD card has enough space
- Try lower resolution

## 🔋 Power Consumption Estimates

- **Live Stream Mode**: ~200mA (high)
- **Time-Lapse Recording**: ~150mA during capture, ~50mA idle
- **Idle/Menu**: ~30mA

**Battery recommendations**:
- 1000mAh power bank: ~4-6 hours time-lapse
- 5000mAh power bank: ~20-30 hours time-lapse
- 10000mAh power bank: ~40-60 hours time-lapse

---

**Happy time-lapsing! 📸✨**
