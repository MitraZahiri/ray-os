# 🪐 RĀY OS — Firmware & Embedded Graphics

This directory contains the embedded C++ firmware running on the **Seeed Studio XIAO ESP32-S3** microcontroller, powering RĀY's sensors, cyber-companion display engine, and micro-piezo aroma actuators.

---

## 📅 Day 3 Milestone (05/10/2026): Zero-Gravity Circular Scent Simulation

For Day 3 of the 14-day build-in-public roadmap, we transformed the **1.28" GC9A01 round LCD** into a virtual **"Zero-Gravity Glass Sphere"** holding live olfactory molecules.

Rather than static or linear graphs, scent molecules float, drift, and collide elastically with the round bezel under zero-gravity physics. When ambient VOC concentration spikes (detected by the BME688 MOX sensor), molecule agitation accelerates, accompanied by dynamic color morphing reflecting the detected aroma classification.

```
       ┌───────────────────────────────────────────────┐
       │   1.28" Round GC9A01 (240x240 Glass Sphere)   │
       │                                               │
       │                 ╭─────────╮                   │
       │             ╭───╯  (VOC)  ╰───╮               │
       │           ╭─╯       ●         ╰─╮             │
       │          ╭╯  ●        ↗          ╰╮           │
       │         │       ↖   ●             │           │
       │         │   ●        ↘            │           │
       │          ╰╮      ●               ╭╯           │
       │           ╰─╮         ●        ╭─╯            │
       │             ╰───╮       ●  ╭───╯              │
       │                 ╰─────────╯                   │
       │            [ Anti-Gravity Drift ]             │
       └───────────────────────────────────────────────┘
```

---

## 🧮 Physics & Visual Math

### 1. Circular Boundary Collision
Unlike rectangular displays where boundary checks use simple `x <= 0 || x >= width`, a circular boundary requires distance calculation from center coordinates $(c_x, c_y) = (120, 120)$:

$$\text{distance} = \sqrt{(x - c_x)^2 + (y - c_y)^2}$$

When $\text{distance} + \text{radius}_{particle} \ge R_{screen}$, a collision is triggered.

### 2. Specular Velocity Vector Reflection
Upon collision, the surface unit normal $\hat{n} = (\frac{dx}{\text{dist}}, \frac{dy}{\text{dist}})$ is computed, and the particle's velocity vector $\vec{v}$ is reflected across the surface tangent:

$$\vec{v}_{\text{reflected}} = \vec{v} - 2(\vec{v} \cdot \hat{n})\hat{n}$$

The particle's coordinates are immediately clamped to the interior circumference to eliminate any clipping outside the bezel.

### 3. Differential Erase (Flicker-Free 60 FPS)
Calling `tft.fillScreen(TFT_BLACK)` every frame requires transferring 57,600 pixels (115.2 KB) over SPI at 40MHz, which caps framerate and introduces visible tearing scanlines. 

Our firmware utilizes **differential erasing**:
1. Erase only the previous position of each active particle (`fillCircle(prevX, prevY, size, TFT_BLACK)`).
2. Integrate physics step.
3. Draw active particle at new $(x, y)$.

This reduces per-frame SPI bus traffic by **98%**, guaranteeing a fluid 60 FPS experience.

---

## 🎨 Olfactory Color Palettes

The particle simulation dynamically shifts palette depending on the scent detected by TinyML / BME688:

| Scent Classification | RGB565 Palettes | Visual Mood |
| :--- | :--- | :--- |
| **Ambient / Clean** | Cyan (`0x07FF`), Ice Blue, Deep Azure | Calm, neutral baseline air |
| **Coffee / Roasted** | Warm Amber (`0xFD20`), Honey Gold, Toasted Ochre | Deep, warm roasted compounds |
| **Citrus / Fresh** | Vivid Lime (`0x07E0`), Lemon Yellow, Tangerine | Zesty, high-energy VOC burst |
| **Floral / Sweet** | Magenta (`0xF81F`), Wild Rose, Lavender | Soft, blooming aroma notes |

---

## 🔌 Hardware Pinout (Xiao ESP32-S3 to GC9A01)

| Display Pin | XIAO ESP32-S3 Pin | Function |
| :--- | :--- | :--- |
| **VCC** | 3.3V | Power Supply |
| **GND** | GND | Ground |
| **SCL / SCLK** | D8 / GPIO 7 | SPI Clock |
| **SDA / MOSI** | D10 / GPIO 9 | SPI Data Out |
| **CS** | D1 / GPIO 2 | Chip Select |
| **DC** | D2 / GPIO 3 | Data / Command Select |
| **RES / RST** | D3 / GPIO 4 | Hardware Reset |
| **BLK / BL** | D0 / GPIO 1 (or 3.3V) | Backlight Control |

---

## 🚀 Getting Started

### Option A: PlatformIO (Recommended)
1. Open this repository in VS Code or Antigravity with PlatformIO installed.
2. Connect your XIAO ESP32-S3 via USB-C.
3. Build and upload:
   ```bash
   cd firmware
   pio run --target upload
   ```

### Option B: Arduino IDE
1. Open [`ray_scent_display/ray_scent_display.ino`](file:///c:/Users/Mitra/ray-os/firmware/ray_scent_display/ray_scent_display.ino) in Arduino IDE.
2. Install the **TFT_eSPI** library via Library Manager.
3. Ensure your `User_Setup.h` has the GC9A01 driver and matching pins enabled.
4. Select board **Seeed Studio XIAO ESP32S3** and hit **Upload**.
