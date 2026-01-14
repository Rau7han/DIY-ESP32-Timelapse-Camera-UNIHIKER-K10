#!/bin/bash

# ============================================================================
# Timelapse Video Creator Script
# ============================================================================
# This script helps you create timelapse videos from captured images
# using FFmpeg.
#
# Usage:
#   ./create_timelapse.sh <input_folder> [output_file] [fps]
#
# Example:
#   ./create_timelapse.sh /path/to/timelapse my_timelapse.mp4 30
#
# Prerequisites:
#   - FFmpeg must be installed
#   - Images should be in sequence (IMG_00001.jpg, IMG_00002.jpg, etc.)
# ============================================================================

set -e  # Exit on error

# Colors for output
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
BLUE='\033[0;34m'
NC='\033[0m' # No Color

# Default values
DEFAULT_FPS=30
DEFAULT_OUTPUT="timelapse.mp4"
DEFAULT_QUALITY=20  # CRF value (lower = better quality)

# Function to print colored output
print_info() {
    echo -e "${BLUE}[INFO]${NC} $1"
}

print_success() {
    echo -e "${GREEN}[SUCCESS]${NC} $1"
}

print_warning() {
    echo -e "${YELLOW}[WARNING]${NC} $1"
}

print_error() {
    echo -e "${RED}[ERROR]${NC} $1"
}

# Function to check if FFmpeg is installed
check_ffmpeg() {
    if ! command -v ffmpeg &> /dev/null; then
        print_error "FFmpeg is not installed!"
        echo ""
        echo "Please install FFmpeg:"
        echo "  - Ubuntu/Debian: sudo apt install ffmpeg"
        echo "  - macOS: brew install ffmpeg"
        echo "  - Windows: Download from https://ffmpeg.org/download.html"
        echo ""
        exit 1
    fi
    print_success "FFmpeg found: $(ffmpeg -version | head -n1)"
}

# Function to display usage
usage() {
    echo "Usage: $0 <input_folder> [output_file] [fps]"
    echo ""
    echo "Arguments:"
    echo "  input_folder   Path to folder containing timelapse images"
    echo "  output_file    Output video filename (default: timelapse.mp4)"
    echo "  fps            Frames per second (default: 30)"
    echo ""
    echo "Examples:"
    echo "  $0 ./timelapse"
    echo "  $0 ./timelapse my_video.mp4"
    echo "  $0 ./timelapse sunset.mp4 60"
    echo ""
    exit 1
}

# Function to count images
count_images() {
    local folder="$1"
    local count=$(find "$folder" -maxdepth 1 -name "*.jpg" -o -name "*.JPG" | wc -l)
    echo "$count"
}

# Function to estimate video duration
estimate_duration() {
    local image_count=$1
    local fps=$2
    local duration=$(echo "scale=2; $image_count / $fps" | bc)
    echo "$duration"
}

# Function to create timelapse video
create_video() {
    local input_folder="$1"
    local output_file="$2"
    local fps="$3"
    
    print_info "Creating timelapse video..."
    print_info "Input: $input_folder"
    print_info "Output: $output_file"
    print_info "FPS: $fps"
    print_info "Quality: CRF $DEFAULT_QUALITY (lower = better)"
    echo ""
    
    # Check if input folder has subdirectory
    if [ -d "$input_folder/timelapse" ]; then
        print_warning "Found /timelapse subdirectory, using that instead"
        input_folder="$input_folder/timelapse"
    fi
    
    # Count images
    local image_count=$(count_images "$input_folder")
    
    if [ "$image_count" -eq 0 ]; then
        print_error "No JPG images found in $input_folder"
        exit 1
    fi
    
    print_success "Found $image_count images"
    
    # Estimate video duration
    local duration=$(estimate_duration "$image_count" "$fps")
    print_info "Estimated video duration: ${duration} seconds"
    echo ""
    
    # Create video with FFmpeg
    print_info "Processing (this may take a while)..."
    
    ffmpeg -y \
        -framerate "$fps" \
        -pattern_type glob \
        -i "$input_folder/IMG_*.jpg" \
        -c:v libx264 \
        -pix_fmt yuv420p \
        -crf "$DEFAULT_QUALITY" \
        -movflags +faststart \
        "$output_file"
    
    if [ $? -eq 0 ]; then
        echo ""
        print_success "Video created successfully!"
        print_info "Output file: $output_file"
        
        # Get output file size
        if [ -f "$output_file" ]; then
            local file_size=$(du -h "$output_file" | cut -f1)
            print_info "File size: $file_size"
        fi
    else
        echo ""
        print_error "Failed to create video"
        exit 1
    fi
}

# Main script
main() {
    echo "========================================"
    echo "  ESP32 Timelapse Video Creator"
    echo "========================================"
    echo ""
    
    # Check arguments
    if [ $# -lt 1 ]; then
        print_error "Missing input folder argument"
        echo ""
        usage
    fi
    
    INPUT_FOLDER="$1"
    OUTPUT_FILE="${2:-$DEFAULT_OUTPUT}"
    FPS="${3:-$DEFAULT_FPS}"
    
    # Validate input folder
    if [ ! -d "$INPUT_FOLDER" ]; then
        print_error "Input folder does not exist: $INPUT_FOLDER"
        exit 1
    fi
    
    # Check FFmpeg
    check_ffmpeg
    echo ""
    
    # Create video
    create_video "$INPUT_FOLDER" "$OUTPUT_FILE" "$FPS"
    
    echo ""
    echo "========================================"
    print_success "All done!"
    echo "========================================"
}

# Run main function
main "$@"
