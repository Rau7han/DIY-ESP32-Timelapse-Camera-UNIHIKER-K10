# Examples Directory

This directory contains helpful scripts and examples for working with your ESP32 Timelapse Camera.

## Scripts

### 1. create_timelapse.sh (Linux/Mac)

A bash script to easily create timelapse videos from your captured images.

**Usage:**
```bash
./create_timelapse.sh <input_folder> [output_file] [fps]
```

**Examples:**
```bash
# Basic usage (30fps, output: timelapse.mp4)
./create_timelapse.sh /path/to/images

# Custom output filename
./create_timelapse.sh /path/to/images sunset.mp4

# Custom FPS (60fps for smoother video)
./create_timelapse.sh /path/to/images sunset.mp4 60
```

**Prerequisites:**
- FFmpeg must be installed
- Install on Ubuntu/Debian: `sudo apt install ffmpeg`
- Install on macOS: `brew install ffmpeg`

### 2. create_timelapse.bat (Windows)

A Windows batch script to create timelapse videos.

**Usage:**
```cmd
create_timelapse.bat <input_folder> [output_file] [fps]
```

**Examples:**
```cmd
REM Basic usage
create_timelapse.bat C:\timelapse

REM Custom output
create_timelapse.bat C:\timelapse my_video.mp4

REM Custom FPS
create_timelapse.bat C:\timelapse sunset.mp4 60
```

**Prerequisites:**
- FFmpeg must be installed and in PATH
- Download from: https://ffmpeg.org/download.html

## Common FFmpeg Commands

### Create Standard Video (30fps)
```bash
ffmpeg -framerate 30 -pattern_type glob -i 'IMG_*.jpg' \
  -c:v libx264 -pix_fmt yuv420p -crf 20 output.mp4
```

### Create High-Quality Video (60fps)
```bash
ffmpeg -framerate 60 -pattern_type glob -i 'IMG_*.jpg' \
  -c:v libx264 -pix_fmt yuv420p -crf 18 output_hq.mp4
```

### Create 1080p Video (Scaled)
```bash
ffmpeg -framerate 30 -pattern_type glob -i 'IMG_*.jpg' \
  -vf scale=1920:1080 -c:v libx264 -pix_fmt yuv420p -crf 20 output_1080p.mp4
```

### Create 4K Video (Upscaled)
```bash
ffmpeg -framerate 30 -pattern_type glob -i 'IMG_*.jpg' \
  -vf scale=3840:2160 -c:v libx264 -pix_fmt yuv420p -crf 20 output_4k.mp4
```

### Create with Fade In/Out (requires filter)
```bash
ffmpeg -framerate 30 -pattern_type glob -i 'IMG_*.jpg' \
  -vf "fade=in:0:30,fade=out:870:30" \
  -c:v libx264 -pix_fmt yuv420p -crf 20 output_fade.mp4
```

## Frame Rate Guide

| FPS | Use Case | Appearance |
|-----|----------|------------|
| 24 | Cinematic look | Film-like, slightly choppy |
| 30 | Standard video | Smooth, good for most timelapses |
| 60 | Very smooth | Ultra-smooth, great for slow subjects |

## Quality Settings (CRF)

| CRF | Quality | File Size | Use Case |
|-----|---------|-----------|----------|
| 18 | Very High | Large | Archive/master copy |
| 20 | High | Medium | Recommended default |
| 23 | Good | Small | Web sharing |
| 28 | Fair | Very Small | Quick preview |

Lower CRF = Better quality but larger file size

## Video Resolution Guide

### Source Resolution (ESP32-CAM UXGA): 1600x1200

**Upscaling Options:**
- 1920x1080 (1080p) - Slight upscale
- 3840x2160 (4K) - Significant upscale (may look blurry)

**Downscaling Options:**
- 1280x720 (720p) - Good for web
- 854x480 (480p) - Fast rendering, small files

**Keep Original:**
- 1600x1200 (UXGA) - No scaling, best quality

## Troubleshooting

### "Command not found" error
- FFmpeg is not installed or not in PATH
- Install FFmpeg and add to system PATH

### "No matches" error
- Check image filenames match pattern (IMG_*.jpg)
- Ensure you're in the correct directory
- Use absolute paths

### Video is too fast/slow
- Adjust FPS parameter
- Lower FPS = slower video
- Higher FPS = faster video

### Poor video quality
- Lower CRF value (e.g., use 18 instead of 20)
- Use higher source resolution images
- Check image quality settings on ESP32

## Advanced Techniques

### Add Music to Timelapse

```bash
# Create video first, then add audio
ffmpeg -i timelapse.mp4 -i music.mp3 \
  -c:v copy -c:a aac -shortest output_with_music.mp4
```

### Create GIF from Timelapse

```bash
ffmpeg -i timelapse.mp4 \
  -vf "fps=10,scale=640:-1:flags=lanczos" \
  -c:v gif output.gif
```

### Create Thumbnail Image

```bash
ffmpeg -i timelapse.mp4 -ss 00:00:05 -vframes 1 thumbnail.jpg
```

### Concatenate Multiple Timelapses

```bash
# Create file list
echo "file 'timelapse1.mp4'" > list.txt
echo "file 'timelapse2.mp4'" >> list.txt

# Concatenate
ffmpeg -f concat -safe 0 -i list.txt -c copy output.mp4
```

## Python Script Example

If you prefer Python, here's a simple script:

```python
import subprocess
import os
from pathlib import Path

def create_timelapse(input_folder, output_file="timelapse.mp4", fps=30):
    """Create timelapse video from images"""
    
    # Check if FFmpeg is available
    try:
        subprocess.run(["ffmpeg", "-version"], 
                      capture_output=True, check=True)
    except FileNotFoundError:
        print("Error: FFmpeg not found")
        return False
    
    # Build FFmpeg command
    cmd = [
        "ffmpeg", "-y",
        "-framerate", str(fps),
        "-pattern_type", "glob",
        "-i", f"{input_folder}/IMG_*.jpg",
        "-c:v", "libx264",
        "-pix_fmt", "yuv420p",
        "-crf", "20",
        output_file
    ]
    
    # Run FFmpeg
    print(f"Creating timelapse video...")
    result = subprocess.run(cmd)
    
    if result.returncode == 0:
        print(f"Success! Video saved as {output_file}")
        return True
    else:
        print("Failed to create video")
        return False

# Usage
if __name__ == "__main__":
    create_timelapse("/path/to/timelapse", "my_video.mp4", 30)
```

Save this as `create_timelapse.py` and run with:
```bash
python create_timelapse.py
```

## Need Help?

- Check the main README.md for more information
- See FFmpeg documentation: https://ffmpeg.org/documentation.html
- Post questions in the Issues section

---

**Happy Timelapsing! 📸🎬**
