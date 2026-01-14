# Quick Start Guide

Get your ESP32 Timelapse Camera up and running in 15 minutes!

## What You Need

- ✅ ESP32-CAM board (AI-THINKER)
- ✅ MicroSD card (4GB+, formatted as FAT32)
- ✅ USB-to-Serial programmer (FTDI or CP2102)
- ✅ 5V power supply or USB cable
- ✅ Computer with USB port
- ✅ Jumper wires (3-4 pieces)

## Step-by-Step Setup

### 1️⃣ Install Software (5 minutes)

**Choose ONE option:**

#### Option A: PlatformIO (Recommended)
1. Install [Visual Studio Code](https://code.visualstudio.com/)
2. Install PlatformIO extension in VS Code
3. Done! ✓

#### Option B: Arduino IDE
1. Download [Arduino IDE](https://www.arduino.cc/en/software)
2. Add ESP32 board support:
   - File → Preferences
   - Add URL: `https://raw.githubusercontent.com/espressif/arduino-esp32/gh-pages/package_esp32_index.json`
   - Tools → Board Manager → Install "esp32"
3. Done! ✓

### 2️⃣ Get the Code (2 minutes)

**Download this repository:**

```bash
git clone https://github.com/Rau7han/DIY-ESP32-Timelapse-Camera-UNIHIKER-K10.git
cd DIY-ESP32-Timelapse-Camera-UNIHIKER-K10
```

Or download ZIP from GitHub and extract.

### 3️⃣ Prepare Hardware (3 minutes)

1. **Insert SD card** into ESP32-CAM slot
2. **Connect programmer** to ESP32-CAM:
   ```
   Programmer → ESP32-CAM
   ━━━━━━━━━━━━━━━━━━━━━━
   5V  → 5V
   GND → GND
   TX  → U0R (RX)
   RX  → U0T (TX)
   ```
3. **Connect GPIO 0 to GND** (jumper wire) - IMPORTANT for uploading!
4. **Plug in USB** to computer

### 4️⃣ Upload Firmware (3 minutes)

#### With PlatformIO:
1. Open project folder in VS Code
2. Click "Upload" button (→ icon)
3. Wait for "SUCCESS"

#### With Arduino IDE:
1. Copy `src/main.cpp` content to new sketch
2. Select Board: "AI Thinker ESP32-CAM"
3. Select your COM Port
4. Click Upload (→ button)
5. Wait for "Done uploading"

### 5️⃣ Start Camera (2 minutes)

1. **Disconnect GPIO 0 from GND** - IMPORTANT!
2. **Press Reset** button on ESP32-CAM
3. **Watch LED blinks**:
   - 2 blinks = Camera OK ✓
   - 3 blinks = SD Card OK ✓
4. **Camera is now capturing!** 📸

## Verify It's Working

### Option 1: Check SD Card
1. Wait 1-2 minutes
2. Remove SD card (power off first!)
3. Check `/timelapse/` folder on SD card
4. You should see `IMG_00001.jpg`, `IMG_00002.jpg`, etc.

### Option 2: Serial Monitor
1. Keep USB connected
2. Open Serial Monitor (115200 baud)
3. You should see:
   ```
   Camera initialized
   SD Card initialized
   Capturing image #1...
   SUCCESS: Saved as /timelapse/IMG_00001.jpg
   Next capture in 10 seconds
   ```

## Default Settings

- **Capture Interval**: 10 seconds
- **Resolution**: 1600x1200 (UXGA)
- **Image Quality**: High (10)
- **Storage**: SD card at `/timelapse/`

## Change Settings (Optional)

Edit `src/main.cpp`, find these lines near the top:

```cpp
#define CAPTURE_INTERVAL_MS 10000  // Change this! (milliseconds)
#define IMAGE_QUALITY 10           // 0=best, 63=worst
#define FRAME_SIZE FRAMESIZE_UXGA  // Resolution
```

**Examples:**
- 5 seconds: `5000`
- 30 seconds: `30000`
- 1 minute: `60000`
- 5 minutes: `300000`
- 1 hour: `3600000`

After changing, upload firmware again!

## Create Your First Timelapse Video

### Easy Way (Using Our Scripts)

**Linux/Mac:**
```bash
cd examples
./create_timelapse.sh /path/to/timelapse my_video.mp4 30
```

**Windows:**
```cmd
cd examples
create_timelapse.bat E:\timelapse my_video.mp4 30
```

### Manual Way (FFmpeg)

```bash
ffmpeg -framerate 30 -pattern_type glob -i 'IMG_*.jpg' \
  -c:v libx264 -pix_fmt yuv420p -crf 20 timelapse.mp4
```

## Common Issues & Quick Fixes

### ❌ Can't Upload Firmware
- ☑️ Check GPIO 0 is connected to GND during upload
- ☑️ Verify TX→RX and RX→TX (not TX→TX)
- ☑️ Try pressing Reset while clicking Upload
- ☑️ Check correct COM port selected

### ❌ SD Card Not Working (5 blinks)
- ☑️ Format card as FAT32
- ☑️ Try different SD card
- ☑️ Push card in firmly until it clicks
- ☑️ Check card isn't write-protected

### ❌ Camera Not Working (10 blinks)
- ☑️ Check camera ribbon cable
- ☑️ Use better power supply (5V 1A minimum)
- ☑️ Press camera connector firmly into socket

### ❌ Nothing Happens
- ☑️ Did you disconnect GPIO 0 after upload?
- ☑️ Press Reset button
- ☑️ Check power LED is on

### ❌ Images Are Dark/Bright
- ☑️ Point camera at well-lit subject
- ☑️ Adjust exposure in code settings
- ☑️ Check camera lens isn't blocked

## Next Steps

✨ **Congratulations! Your camera is working!**

Now you can:
- 📦 Place it somewhere interesting
- 🌱 Capture plant growth
- 🌅 Record sunsets
- 🏗️ Document projects
- 🎬 Create amazing timelapse videos!

## Need More Help?

- 📖 Read the full [README.md](README.md)
- 🔌 Check [WIRING.md](WIRING.md) for detailed connections
- ⚙️ See [CONFIGURATION.md](CONFIGURATION.md) for all settings
- 🐛 Found a bug? [Open an issue](https://github.com/Rau7han/DIY-ESP32-Timelapse-Camera-UNIHIKER-K10/issues)

## Pro Tips

💡 **Power Tips:**
- Use a wall adapter for long timelapses (not battery)
- USB power banks may auto-shutoff - test first!
- Add a capacitor (100-470µF) for stability

💡 **SD Card Tips:**
- Use Class 10 or faster
- 16GB-32GB is ideal
- Format before each long timelapse
- Keep a spare SD card ready

💡 **Capture Tips:**
- Start with 10-second intervals for testing
- Longer intervals for slow subjects (plants, construction)
- Shorter intervals for fast subjects (clouds, traffic)
- Secure camera to avoid shaking

💡 **Video Tips:**
- 30fps is standard and looks good
- Lower fps for longer duration (more images)
- Use CRF 18-20 for good quality/size balance
- Test with a small batch first

---

**🎉 Happy Timelapsing!**

Share your creations and tag this project!
