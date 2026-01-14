# Wiring Guide for ESP32 Timelapse Camera

This guide provides detailed wiring instructions for connecting your ESP32-CAM board.

## ESP32-CAM Pinout Reference

```
                    ESP32-CAM (AI-THINKER)
                    =====================
                    
        ┌─────────────────────────────────────┐
        │                                     │
        │   ┌──────────┐     ┌──────────┐    │
        │   │ OV2640   │     │  SD Card │    │
        │   │  Camera  │     │   Slot   │    │
        │   └──────────┘     └──────────┘    │
        │                                     │
        │ ┌────┐  ┌────┐  ┌────┐  ┌────┐    │
        │ │3V3 │  │ 5V │  │GND │  │U0R │    │
        │ └────┘  └────┘  └────┘  └────┘    │
        │                                     │
        │ ┌────┐  ┌────┐  ┌────┐  ┌────┐    │
        │ │U0T │  │GP0 │  │GP2 │  │GP4 │    │
        │ └────┘  └────┘  └────┘  └────┘    │
        │                                     │
        │ ┌────┐  ┌────┐  ┌────┐  ┌────┐    │
        │ │G12 │  │G13 │  │G14 │  │G15 │    │
        │ └────┘  └────┘  └────┘  └────┘    │
        │                                     │
        │            [ RESET ]                │
        └─────────────────────────────────────┘

        Legend:
        3V3  = 3.3V Output
        5V   = 5V Input
        GND  = Ground
        U0R  = UART RX (GPIO 3)
        U0T  = UART TX (GPIO 1)
        GP0  = GPIO 0
        GP2  = GPIO 2
        GP4  = GPIO 4 (Flash LED)
        G12-15 = GPIO 12-15
```

## Connection Diagrams

### 1. Programming Mode (One-time firmware upload)

Connect FTDI or USB-to-Serial adapter:

```
    FTDI/USB-Serial          ESP32-CAM
    ===============          =========
    
    VCC (5V)    ────────────  5V
    GND         ────────────  GND
    TX          ────────────  U0R (RX)
    RX          ────────────  U0T (TX)
    
    [For Programming]
    GND         ────────────  GPIO 0
    
```

**Important Steps**:
1. Connect GPIO 0 to GND **before** powering on
2. Power on the board
3. Upload firmware
4. Disconnect GPIO 0 from GND
5. Press reset button

### 2. Normal Operation Mode

For standalone operation after programming:

```
    Power Supply            ESP32-CAM
    ============            =========
    
    5V          ────────────  5V
    GND         ────────────  GND
    
```

**Power Requirements**:
- Voltage: 5V DC
- Current: Minimum 500mA, recommended 1-2A
- Use quality power supply to avoid brownouts

### 3. With UNIHIKER K10 Display (Optional)

#### Serial Connection:

```
    UNIHIKER K10            ESP32-CAM
    ============            =========
    
    TX (GPIO)   ────────────  U0R (RX)
    RX (GPIO)   ────────────  U0T (TX)
    GND         ────────────  GND
    
    [Separate Power]
    5V Supply   ────────────  5V (ESP32-CAM)
    5V Supply   ────────────  5V (UNIHIKER)
```

**Notes**:
- UNIHIKER K10 can control camera and display status
- Requires firmware modifications for communication protocol
- Both devices can share ground but use separate power

## Component Connections

### Camera Module (OV2640)

✅ **Pre-connected on ESP32-CAM board**
- No additional wiring needed
- Ribbon cable should be firmly seated
- Camera should face forward (lens through hole)

### SD Card

✅ **Built-in slot on ESP32-CAM**
- Insert microSD card into slot on back
- Card should click into place
- Ensure card is formatted as FAT32
- Contacts should be facing the PCB

### Flash LED

✅ **Built-in on GPIO 4**
- White LED on front of board
- Used for status indication in firmware
- Can also be used as camera flash

## Additional Components

### Recommended: Power Stabilization Capacitor

Add a large capacitor for stable power:

```
    Power Supply
         |
         ├── (+) ────────  5V (ESP32-CAM)
         |
         ├── Capacitor (100-470µF, 16V+)
         |
         └── (-) ────────  GND (ESP32-CAM)
```

**Benefits**:
- Prevents brownout resets
- Stabilizes camera operation
- Reduces noise in images

### Optional: External Reset Button

Add a reset button for easy resets:

```
    [Push Button]
         |
         ├── One side ────  RST (RESET pin)
         |
         └── Other side ──  GND
```

### Optional: External Status LED

Add an external LED for better visibility:

```
    GPIO 2  ────────  [220Ω Resistor]  ────  LED (+)
                                              LED (-) ──── GND
```

**Modify firmware to use GPIO 2 instead of GPIO 4 if needed**

## Power Supply Options

### Option 1: USB Power Bank

```
    [USB Power Bank]
         |
         └─ Micro USB Cable ─┐
                             |
                          [USB to ]
                          [5V/GND ]  ───── ESP32-CAM
                          [Adapter ]
```

**Pros**:
- Portable
- Good for outdoor timelapses
- Built-in battery

**Cons**:
- May auto-shutoff with low current draw
- Limited capacity

### Option 2: Wall Adapter

```
    [Wall Adapter]
    [5V 2A      ]
         |
         └─ DC Jack ───── ESP32-CAM (5V/GND)
```

**Pros**:
- Continuous power
- Stable voltage
- Best for long-duration timelapses

**Cons**:
- Not portable
- Requires AC outlet

### Option 3: Battery Pack with Voltage Regulator

```
    [Battery Pack]  ──┐
    [7-12V        ]   |
                      └─ [LM7805 Regulator] ─── ESP32-CAM
                         [or Buck Converter]
```

**Pros**:
- Long runtime
- Portable
- Can use rechargeable batteries

**Cons**:
- Requires voltage regulation
- More complex setup

## Common Wiring Mistakes

### ❌ Don't Do This:

1. **Swapping TX/RX**
   - TX → TX, RX → RX ❌
   - Correct: TX → RX, RX → TX ✅

2. **Wrong Voltage**
   - Using 3.3V for VCC ❌
   - Correct: Use 5V for VCC ✅

3. **Weak Power Supply**
   - Using 200mA USB hub port ❌
   - Correct: Use 500mA+ power supply ✅

4. **No GPIO 0 Ground (during programming)**
   - Not connecting GPIO 0 to GND ❌
   - Correct: Connect GPIO 0 to GND before powering on ✅

5. **Leaving GPIO 0 Grounded (during operation)**
   - GPIO 0 to GND in normal mode ❌
   - Correct: Disconnect GPIO 0 after programming ✅

## Troubleshooting Wiring Issues

### Camera Not Working
- Check camera ribbon cable is fully inserted
- Ensure camera is not blocked by case
- Verify power supply is stable (5V, 500mA+)

### Cannot Upload Firmware
- Verify GPIO 0 is connected to GND during programming
- Check TX/RX are not swapped
- Ensure correct COM port is selected
- Try lower baud rate (115200 instead of 921600)

### Random Resets
- Add stabilization capacitor
- Use better power supply
- Shorten USB cable
- Check for loose connections

### SD Card Not Detected
- Ensure SD card is fully inserted
- Check card is formatted as FAT32
- Try different SD card
- Clean SD card contacts

## Safety Notes

⚠️ **Important Safety Information**:

1. **Never connect/disconnect components while powered**
   - Always disconnect power before wiring changes
   - Can damage components or cause shorts

2. **Check polarity carefully**
   - Wrong polarity can destroy board
   - Double-check before powering on

3. **Use appropriate wire gauge**
   - Thin wires can overheat
   - Use 22-26 AWG for connections

4. **Avoid shorts**
   - Keep wires organized
   - Use heat shrink or electrical tape
   - Check for stray wire strands

5. **Static protection**
   - Touch grounded metal before handling
   - Use ESD wrist strap if available
   - Work on non-static surface

## Testing Your Wiring

### Step-by-step verification:

1. **Visual Inspection**
   - ✓ All connections match diagram
   - ✓ No exposed wire causing shorts
   - ✓ Secure connections

2. **Multimeter Test** (power off)
   - ✓ Continuity on power/ground lines
   - ✓ No shorts between 5V and GND
   - ✓ Correct voltage on power supply (5V ±0.25V)

3. **First Power On**
   - ✓ LED should light up briefly
   - ✓ No smoke or burning smell
   - ✓ Board not getting hot

4. **Serial Communication**
   - ✓ Serial monitor shows output at 115200 baud
   - ✓ Boot messages appear
   - ✓ No continuous resets

## Reference Images

For actual photos of wiring setups, see:
- `/docs/images/wiring_photo1.jpg` (if available)
- `/docs/images/wiring_photo2.jpg` (if available)

Or search online for "ESP32-CAM wiring" for visual references.

## Need Help?

If you're having wiring issues:
1. Double-check this guide
2. Verify power supply specifications
3. Test with minimal setup first
4. Post photos of your wiring in Issues
5. Include serial monitor output

---

**Remember**: Take your time with wiring. A few minutes of careful checking can prevent hours of troubleshooting!
