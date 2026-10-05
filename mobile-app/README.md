# 📱 RĀY Scent Companion — Digital Scent Vault & BLE Telemetry

<p align="center">
  <b>Your personal digital olfactory journal and real-time scent synthesizer controller.</b><br>
  Syncs with RĀY (ESP32-S3) over Bluetooth Low Energy (BLE 5.0) to capture, catalog, and replay aroma profiles.
</p>

---

## 🌟 Key Features

1. **🫧 Live Zero-G Scent Visualizer Mirror:**
   - Real-time mirroring of the 1.28" GC9A01 round LCD's anti-gravity molecule animation.
   - Visualizes VOC particle agitation and color-coded TinyML classification on your smartphone screen.

2. **🗃️ Digital Scent Vault:**
   - Saves captured aromas with multidimensional metadata: BME688 MOX gas resistance curve, temperature, relative humidity, barometric pressure, GPS geotag, and user sensory notes.
   - Search and filter by scent category: *Coffee / Roasted*, *Citrus / Zesty*, *Floral / Sweet*, *Woody / Earthy*, *Ambient Air*.

3. **💨 Piezo Micro-Mist Dispenser Controller:**
   - Remote trigger for RĀY's micro-piezo ultrasonic aroma pods.
   - Customizable pulse duration (e.g., 50ms - 500ms bursts) and automated dispersal cycles.

4. **🌐 Scent Exchange & Community Sharing:**
   - Export and import digital scent signatures via the open `.scent` JSON standard.
   - Share scent logs with other researchers, perfumers, and cyber-companion owners.

---

## 📡 BLE 5.0 GATT Specification

RĀY advertises as `RAY-Companion-XXXX` using a custom 128-bit Primary GATT Service.

### Primary Service UUID: `7F3A0001-5C2B-4D1E-8B39-92E870F4E0A1`

| Characteristic Name | UUID | Properties | Format / Payload | Description |
| :--- | :--- | :--- | :--- | :--- |
| **Live Telemetry Stream** | `7F3A0002-...` | `READ`, `NOTIFY` | `uint32_t gas_res, int16_t temp, uint16_t hum` (10Hz) | Raw BME688 environmental sensor feed |
| **Classification Output** | `7F3A0003-...` | `READ`, `NOTIFY` | `uint8_t category_id, uint8_t confidence_pct` | Edge Impulse TinyML inference result |
| **Piezo Trigger Command** | `7F3A0004-...` | `WRITE` | `uint8_t pod_id, uint16_t duration_ms` | Fires ultrasonic mist actuator |
| **Display Sync & Theme** | `7F3A0005-...` | `READ`, `WRITE` | `uint8_t color_scheme, uint8_t particle_count` | Synchronizes mobile & round LCD visual styles |
| **Battery & Health** | `0x2A19` (Standard) | `READ`, `NOTIFY` | `uint8_t percentage` | LiPo battery fuel gauge |

---

## 🗂️ `.scent` Digital Aroma Schema (v1.0)

Every scent recorded in the Vault conforms to this open JSON schema:

```json
{
  "version": "1.0",
  "scent_id": "scent_20261005_ethiopian_roast",
  "name": "Ethiopian Yirgacheffe Roast #04",
  "category": "coffee_roasted",
  "timestamp": "2026-10-05T22:20:00Z",
  "location": {
    "latitude": 41.0082,
    "longitude": 28.9784,
    "environment": "Indoor Roastery"
  },
  "sensor_telemetry": {
    "baseline_resistance_ohms": 142500,
    "peak_resistance_ohms": 21300,
    "delta_ratio": 6.69,
    "temp_celsius": 24.3,
    "humidity_rh": 48.2,
    "pressure_hpa": 1013.2
  },
  "tinyml_inference": {
    "model": "ray-tinyml-v1.2",
    "predicted_label": "coffee",
    "confidence": 0.94
  },
  "piezo_recipe": {
    "recommended_pod": "roasted_notes_v2",
    "pulse_ms": 120
  }
}
```

---

## 🏗️ Architecture & Tech Stack

```
┌────────────────────────────────┐
│      RĀY Mobile App UI         │  Flutter / React Native (Cross-Platform)
├────────────────────────────────┤
│    Olfactory Particle Canvas   │  Skia / Custom Painter (60 FPS Visuals)
├────────────────────────────────┤
│       BLE State Manager        │  Reactive BLE Manager (flutter_blue_plus / BLE-PLX)
├────────────────────────────────┤
│       Local Scent Vault        │  SQLite / Isar NoSQL (Offline-first)
└────────────────────────────────┘
                ▲
                │ BLE 5.0 (GATT)
                ▼
┌────────────────────────────────┐
│     RĀY Hardware (ESP32-S3)    │  GC9A01 Round LCD + BME688 MOX Sensor
└────────────────────────────────┘
```

---

## 📱 Planned App Screens

1. **Dashboard (The Orb):** Interactive glowing sphere matching the GC9A01 LCD screen. Swipe up to sniff and classify.
2. **Vault Gallery:** Grid of saved scents with thumbnail VOC curves, dates, and aroma color tags.
3. **Synthesis Lab:** Tactile trigger button for the micro-piezo mist dispenser with slider for burst duration.
4. **Export & Share:** Instant QR-code and AirDrop/Nearby share for `.scent` profiles.

---

## 🛠️ Contributing to Mobile App

The mobile companion app repository scaffold is being built with clean architecture (UI Layer, Domain Logic, BLE Repository). PRs and community feedback are welcome!
