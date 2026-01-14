@echo off
REM ============================================================================
REM Timelapse Video Creator Script (Windows)
REM ============================================================================
REM This script helps you create timelapse videos from captured images
REM using FFmpeg.
REM
REM Usage:
REM   create_timelapse.bat <input_folder> [output_file] [fps]
REM
REM Example:
REM   create_timelapse.bat C:\timelapse my_timelapse.mp4 30
REM
REM Prerequisites:
REM   - FFmpeg must be installed and in PATH
REM   - Images should be in sequence (IMG_00001.jpg, IMG_00002.jpg, etc.)
REM ============================================================================

setlocal enabledelayedexpansion

REM Default values
set DEFAULT_FPS=30
set DEFAULT_OUTPUT=timelapse.mp4
set DEFAULT_QUALITY=20

REM Colors (limited support in Windows CMD)
echo ========================================
echo   ESP32 Timelapse Video Creator
echo ========================================
echo.

REM Check if FFmpeg is installed
where ffmpeg >nul 2>nul
if %errorlevel% neq 0 (
    echo [ERROR] FFmpeg is not installed or not in PATH!
    echo.
    echo Please install FFmpeg:
    echo   Download from: https://ffmpeg.org/download.html
    echo   Add to system PATH
    echo.
    pause
    exit /b 1
)

echo [SUCCESS] FFmpeg found
echo.

REM Check arguments
if "%~1"=="" (
    echo [ERROR] Missing input folder argument
    echo.
    echo Usage: %~nx0 ^<input_folder^> [output_file] [fps]
    echo.
    echo Arguments:
    echo   input_folder   Path to folder containing timelapse images
    echo   output_file    Output video filename ^(default: timelapse.mp4^)
    echo   fps            Frames per second ^(default: 30^)
    echo.
    echo Examples:
    echo   %~nx0 C:\timelapse
    echo   %~nx0 C:\timelapse my_video.mp4
    echo   %~nx0 C:\timelapse sunset.mp4 60
    echo.
    pause
    exit /b 1
)

REM Parse arguments
set INPUT_FOLDER=%~1
set OUTPUT_FILE=%~2
set FPS=%~3

REM Set defaults if not provided
if "%OUTPUT_FILE%"=="" set OUTPUT_FILE=%DEFAULT_OUTPUT%
if "%FPS%"=="" set FPS=%DEFAULT_FPS%

REM Validate input folder
if not exist "%INPUT_FOLDER%" (
    echo [ERROR] Input folder does not exist: %INPUT_FOLDER%
    pause
    exit /b 1
)

REM Check for timelapse subdirectory
if exist "%INPUT_FOLDER%\timelapse" (
    echo [INFO] Found \timelapse subdirectory, using that
    set INPUT_FOLDER=%INPUT_FOLDER%\timelapse
)

REM Count images
set IMAGE_COUNT=0
for %%f in ("%INPUT_FOLDER%\IMG_*.jpg" "%INPUT_FOLDER%\IMG_*.JPG") do (
    set /a IMAGE_COUNT+=1
)

if %IMAGE_COUNT%==0 (
    echo [ERROR] No JPG images found in %INPUT_FOLDER%
    pause
    exit /b 1
)

echo [SUCCESS] Found %IMAGE_COUNT% images
echo.

REM Display settings
echo [INFO] Creating timelapse video...
echo [INFO] Input: %INPUT_FOLDER%
echo [INFO] Output: %OUTPUT_FILE%
echo [INFO] FPS: %FPS%
echo [INFO] Quality: CRF %DEFAULT_QUALITY% ^(lower = better^)
echo.

REM Calculate estimated duration
set /a DURATION=%IMAGE_COUNT% / %FPS%
echo [INFO] Estimated video duration: %DURATION% seconds
echo.

REM Create video with FFmpeg
echo [INFO] Processing ^(this may take a while^)...
echo.

ffmpeg -y -framerate %FPS% -pattern_type glob -i "%INPUT_FOLDER%\IMG_*.jpg" -c:v libx264 -pix_fmt yuv420p -crf %DEFAULT_QUALITY% -movflags +faststart "%OUTPUT_FILE%"

if %errorlevel% equ 0 (
    echo.
    echo [SUCCESS] Video created successfully!
    echo [INFO] Output file: %OUTPUT_FILE%
    
    REM Get file size
    for %%A in ("%OUTPUT_FILE%") do (
        set FILE_SIZE=%%~zA
        set /a FILE_SIZE_MB=!FILE_SIZE! / 1048576
        echo [INFO] File size: !FILE_SIZE_MB! MB
    )
    
    echo.
    echo ========================================
    echo [SUCCESS] All done!
    echo ========================================
) else (
    echo.
    echo [ERROR] Failed to create video
    pause
    exit /b 1
)

echo.
pause
