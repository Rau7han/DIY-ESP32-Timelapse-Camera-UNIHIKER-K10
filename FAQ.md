# Frequently Asked Questions (FAQ)

Common questions and answers about the ESP32 Timelapse Camera project.

## General Questions

### Q: What is this project?
**A:** This is a DIY timelapse camera built using an ESP32-CAM board. It automatically captures images at configurable intervals and saves them to an SD card. You can then create timelapse videos from these images.

### Q: How much does it cost to build?
**A:** Basic setup costs around $25-40 USD:
- ESP32-CAM board: $10-15
- MicroSD card: $5-10
- USB programmer: $5-8
- Power supply: $5-10
- Optional UNIHIKER K10 display: $50-80

### Q: Do I need programming experience?
**A:** No! The firmware is ready to use. Just upload it to your ESP32-CAM following the Quick Start Guide. If you want to customize settings, basic editing skills are helpful.

### Q: Can I use a different ESP32 board?
**A:** This firmware is specifically designed for ESP32-CAM boards with the OV2640 camera module. Other ESP32 boards without a camera won't work. Different ESP32-CAM variants may need pin adjustments.

## Hardware Questions

### Q: Which ESP32-CAM board should I buy?
**A:** The AI-THINKER ESP32-CAM is the most common and well-supported. The pin definitions in this project are configured for that board.

### Q: What size SD card do I need?
**A:** Minimum 4GB, but 16GB-32GB is recommended. A Class 10 or UHS-1 card provides better performance. Must be formatted as FAT32.

### Q: Can I power it with batteries?
**A:** Yes! You can use:
- USB power bank (test for auto-shutoff issues)
- Battery pack with 5V regulator
- Li-ion batteries with boost converter
Expect 180-250mA current draw during capture, 80-120mA idle.

### Q: Do I need the UNIHIKER K10?
**A:** No, it's optional. The ESP32-CAM works standalone. The UNIHIKER K10 can be used for display and control features (requires additional firmware development).

### Q: Can I use a different camera module?
**A:** The firmware is designed for the OV2640 that comes with ESP32-CAM. Other cameras would require significant code changes.

## Software Questions

### Q: Should I use PlatformIO or Arduino IDE?
**A:** PlatformIO is recommended because it handles library dependencies automatically. However, Arduino IDE works fine too with manual library installation.

### Q: Can I change the capture interval?
**A:** Yes! Edit `CAPTURE_INTERVAL_MS` in `src/main.cpp` or use one of the presets in `include/config.h`. Examples:
- 5000 = 5 seconds
- 60000 = 1 minute
- 300000 = 5 minutes
- 3600000 = 1 hour

### Q: How do I upload the firmware?
**A:** See the Quick Start Guide. Basically:
1. Connect USB programmer to ESP32-CAM
2. Connect GPIO 0 to GND
3. Upload firmware using PlatformIO or Arduino IDE
4. Disconnect GPIO 0 from GND
5. Reset the board

### Q: The code won't compile. What's wrong?
**A:** Common issues:
- Wrong board selected (should be ESP32-CAM or AI Thinker ESP32-CAM)
- Missing libraries (install esp32-camera and SD)
- Incorrect ESP32 board support version
- Check that you have ESP32 Arduino core 2.0.0 or later

## Operation Questions

### Q: How do I know if it's working?
**A:** Watch the LED:
- 2 blinks = Camera initialized successfully
- 3 blinks = SD card initialized successfully
- Then LED blinks briefly each time it captures

You can also check the serial monitor at 115200 baud for detailed logs.

### Q: Where are the images saved?
**A:** Images are saved to the SD card in the `/timelapse/` directory with sequential names: `IMG_00001.jpg`, `IMG_00002.jpg`, etc.

### Q: How long can it record?
**A:** Depends on:
- SD card size
- Image quality/resolution
- Capture interval

Example: 16GB card with UXGA quality (250KB per image) = ~65,000 images
At 10-second intervals, that's about 7.5 days of continuous recording.

### Q: Can I access images without removing the SD card?
**A:** Not with the current firmware. You need to power off and remove the SD card. Future versions may add WiFi file transfer.

### Q: How do I stop recording?
**A:** Simply disconnect power. Images are saved immediately after capture, so no data loss.

## Image Quality Questions

### Q: My images are too dark/bright. How do I fix this?
**A:** Adjust camera settings in the code:
- Change `CAM_BRIGHTNESS` (-2 to 2)
- Change `CAM_AE_LEVEL` for auto-exposure (-2 to 2)
- Modify exposure value `CAM_AEC_VALUE` (0-1200)

### Q: What's the best resolution for timelapses?
**A:** FRAMESIZE_UXGA (1600x1200) is recommended for high-quality timelapses. It provides good detail without massive file sizes.

### Q: How do I improve image quality?
**A:**
- Lower `IMAGE_QUALITY` number (try 8 instead of 10)
- Use higher resolution (UXGA or QXGA)
- Ensure good lighting
- Keep camera stable
- Clean camera lens

### Q: Images are blurry. What's wrong?
**A:**
- Camera might be moving/vibrating
- Lens might be dirty or have protective film
- Focus might be off (OV2640 has fixed focus)
- Check camera is securely mounted

## Video Creation Questions

### Q: How do I create a video from the images?
**A:** Use FFmpeg with the provided scripts:
- Linux/Mac: `./examples/create_timelapse.sh /path/to/timelapse`
- Windows: `examples\create_timelapse.bat C:\timelapse`

Or use FFmpeg directly:
```bash
ffmpeg -framerate 30 -pattern_type glob -i 'IMG_*.jpg' \
  -c:v libx264 -pix_fmt yuv420p -crf 20 timelapse.mp4
```

### Q: What frame rate should I use?
**A:**
- 24 fps: Cinematic look
- 30 fps: Standard, smooth (recommended)
- 60 fps: Very smooth, professional

### Q: The video is too fast/slow. How do I change it?
**A:** Adjust the frame rate (fps) in FFmpeg:
- Lower fps = slower video (more visible detail)
- Higher fps = faster video (more time compression)

### Q: I don't have FFmpeg. What are my options?
**A:**
- Install FFmpeg (free): https://ffmpeg.org/
- Use online tools like Kapwing or Clideo
- Use Windows Movie Maker or iMovie
- Use video editing software (Adobe Premiere, DaVinci Resolve, etc.)

## Troubleshooting Questions

### Q: Camera won't initialize (10 LED blinks). Help!
**A:**
- Check camera ribbon cable is firmly connected
- Ensure camera module is properly seated
- Use a better power supply (5V 1-2A)
- Add 470µF capacitor between 5V and GND
- Try resetting the board

### Q: SD card not detected (5 LED blinks). Help!
**A:**
- Format SD card as FAT32
- Try a different SD card (some are incompatible)
- Ensure card is fully inserted (should click)
- Check card isn't write-protected
- Use Class 10 or UHS-1 card
- Clean SD card contacts

### Q: Board keeps resetting randomly. Why?
**A:** Power issues:
- Use higher current power supply (2A recommended)
- Add 470µF capacitor near power pins
- Use shorter/better USB cable
- Check for loose connections
- Avoid cheap cables with high resistance

### Q: I can upload firmware but nothing happens. Help!
**A:**
- Did you disconnect GPIO 0 from GND after upload?
- Press the Reset button after upload
- Check power LED is on
- Open serial monitor to see boot messages
- Verify SD card is inserted

### Q: Images are saving but with wrong timestamps. Help!
**A:** The ESP32 doesn't have a real-time clock. Images are numbered sequentially, not timestamped. If you need timestamps, you'd need to add an RTC module or use WiFi to get time from NTP server.

## Advanced Questions

### Q: Can I add WiFi connectivity?
**A:** Yes! The ESP32 supports WiFi. You could modify the firmware to:
- Upload images to cloud storage
- Provide web interface for control
- Stream live preview
- Download images over WiFi
This requires additional programming.

### Q: Can I trigger capture manually with a button?
**A:** Yes! Add a button connected to a GPIO pin and modify the firmware to check button state in the loop. Capture when button is pressed.

### Q: Can I add motion detection?
**A:** Yes! You could implement motion detection by:
- Comparing consecutive frames
- Only saving when significant changes detected
- This requires additional coding and may impact performance

### Q: How do I add a battery monitor?
**A:** Connect battery voltage to an ADC pin (through voltage divider if >3.3V) and read voltage in code. Display/log the battery level.

### Q: Can I use this underwater?
**A:** The ESP32-CAM is not waterproof. You'd need a waterproof enclosure. Ensure it has good seals and consider condensation issues.

### Q: Can I capture at higher resolution than UXGA?
**A:** The OV2640 camera supports up to QXGA (2048x1536), but this requires PSRAM. Not all ESP32-CAM boards have PSRAM. Check your board specifications.

## Project Questions

### Q: Can I contribute to this project?
**A:** Yes! Contributions are welcome. Fork the repository, make changes, and submit a pull request. Or report bugs and suggest features in Issues.

### Q: Is this project open source?
**A:** Yes! Licensed under MIT License. You're free to use, modify, and distribute it.

### Q: Can I use this commercially?
**A:** Yes, the MIT License allows commercial use. Attribution is appreciated but not required.

### Q: Where can I get help?
**A:**
1. Read this FAQ
2. Check the README.md
3. Review QUICKSTART.md and WIRING.md
4. Search existing GitHub Issues
5. Open a new Issue with details

### Q: Can I share my timelapse videos?
**A:** Absolutely! We'd love to see what you create. Share on social media and tag the project!

## Tips and Best Practices

### Q: What are some tips for better timelapses?
**A:**
- Secure camera firmly to avoid vibration
- Point camera at well-lit subjects
- Test settings with short intervals first
- Keep extra SD cards ready
- Use wall power for long captures
- Clean camera lens before starting
- Check first few images before leaving camera
- Consider weather protection for outdoor use

### Q: How do I calculate how many images I'll capture?
**A:** 
```
Total Images = (Duration in seconds) / (Interval in seconds)

Example: 24-hour timelapse with 10-second interval
= (24 × 60 × 60) / 10
= 86,400 / 10
= 8,640 images
```

### Q: How do I estimate SD card space needed?
**A:**
```
Space Needed = (Number of Images) × (Size per Image)

Example: 10,000 images at UXGA quality (250KB each)
= 10,000 × 250KB
= 2,500,000 KB
= ~2.4 GB
```

Add 20% buffer: ~3 GB recommended

## Still Have Questions?

If your question isn't answered here:
1. Check the full [README.md](README.md)
2. Review [CONFIGURATION.md](CONFIGURATION.md) for settings
3. See [WIRING.md](WIRING.md) for connections
4. Read [QUICKSTART.md](QUICKSTART.md) for setup
5. Browse [GitHub Issues](https://github.com/Rau7han/DIY-ESP32-Timelapse-Camera-UNIHIKER-K10/issues)
6. Ask a new question by opening an Issue

---

**Happy Timelapsing! 📸**
