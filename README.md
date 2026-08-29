# 🌟 RĀY — AI-Powered Pocket Olfactory Scanner & Synthesizer

<p align="center">
  <b>Capture the world's scents. Synthesize on the go.</b><br>
  An open-hardware cyber-pocket companion that digitizes aromas and creates custom scent notes in real-time.
</p>

<p align="center">
  <img src="https://img.shields.io/badge/Status-Day%201%20Alpha-blue?style=for-the-badge" alt="Status">
  <img src="https://img.shields.io/badge/Hardware-ESP32--S3-green?style=for-the-badge" alt="Hardware">
  <img src="https://img.shields.io/badge/Sensors-BME688%20MOX%20AI-orange?style=for-the-badge" alt="Sensors">
  <img src="https://img.shields.io/badge/License-Apache--2.0-blue?style=for-the-badge" alt="License">
</p>

---

## 🧭 What is RĀY?

**RĀY** is a palm-sized, interactive cyber-companion equipped with an **AI electronic nose (e-Nose)**, a circular OLED/LCD expressive face, and a micro-dispensing piezo mist system. 

It allows creators, designers, and everyday users to:
1. **Sniff & Digitize:** Capture VOC (Volatile Organic Compounds) profiles of flowers, coffee, perfumes, or ambient environments.
2. **AI Classification:** Process olfactory signatures on-device using TinyML (ESP32-S3 Edge AI).
3. **Micro-Synthesize:** Dispense matched scent notes via interchangeable piezo-actuated pods.

---

## 🛠️ System Architecture

[ Ambient Air ]
│
▼
┌─────────────────────────┐
│   BME688 MOX AI Sensor  │ ──► Gas Resistance / VOCs / Temp / Humidity
└─────────────────────────┘
│
▼
┌─────────────────────────┐
│   Xiao ESP32-S3 MCU     │ ◄──► TinyML Classifier (Edge Impulse)
└─────────────────────────┘
│
┌────┴────────────────────────┐
▼                             ▼
┌─────────────────────────┐   ┌─────────────────────────┐
│  1.28" Round LCD (Face) │   │  Micro Piezo Mist Core  │
│  Live Molecule & Avatar │   │  Instant Scent Release  │
└─────────────────────────┘   └─────────────────────────┘


---

## 📂 Repository Structure

- `/firmware`: Embedded C++ code for ESP32-S3, sensor drivers, and round LCD animations.
- `/hardware`: 3D CAD files (Fusion 360 / STEP / STL) for the transparent cyber-chassis and PCB schematics.
- `/ml-model`: Scent training data logs (CSV) and exported Edge Impulse TinyML models.
- `/mobile-app`: Companion app for digital scent vault and community sharing.

---

## 🚀 14-Day Build-In-Public Roadmap

- [x] **Day 1:** Project Vision, Architecture, and Open Source Launch (`RĀY`).
- [ ] **Day 2:** Sensor wiring (BME688 + ESP32) & First VOC baseline log.
- [ ] **Day 3:** Circular LCD Eye Animation & Live Scent Waveform.
- [ ] **Day 4:** 3D Star Chassis CAD modeling & Ergonomics.
- [ ] **Day 5:** First Resin Print & Chassis Assembly.
- [ ] **Day 6:** TinyML Coffee vs. Citrus differentiation test.
- [ ] **Day 7:** Piezo Micro-Dispenser Integration.

---

## 🤝 Contributing

RĀY is built in public! Contributions, issues, and feature ideas are welcome.
1. Fork the Project
2. Create your Feature Branch (`git checkout -b feature/AmazingScent`)
3. Commit your Changes (`git commit -m 'Add some AmazingScent'`)
4. Push to the Branch (`git push origin feature/AmazingScent`)
5. Open a Pull Request

---

<p align="center">
  Maintained by <a href="https://github.com/MitraZahiri">Mitra Zahiri</a> • Built in Public
</p>