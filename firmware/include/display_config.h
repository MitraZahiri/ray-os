#pragma once

#include <Arduino.h>

/**
 * @file display_config.h
 * @brief Hardware pinout and display geometry for 1.28" Round GC9A01 LCD on ESP32-S3
 * 
 * Target Board: Seeed Studio XIAO ESP32-S3 / ESP32-S3 DevKitC-1
 * Display: 1.28-inch GC9A01 SPI Round TFT LCD (240x240)
 */

// Display Physical Dimensions
#define SCREEN_WIDTH       240
#define SCREEN_HEIGHT      240
#define CENTER_X           120
#define CENTER_Y           120
#define BOUNDARY_RADIUS    114   // Keep 6px buffer from mechanical circular bezel

// Simulation Parameters
#define MAX_PARTICLES       32
#define DEFAULT_PARTICLES   24
#define TARGET_FRAME_MS     16    // ~60 FPS target

// Rendering Mode
// Set to true to erase only particle footprints (ultra-fast, no SPI screen tear)
// Set to false for full screen refresh
#define USE_DIRTY_RECT_ERASE true

// Recommended Pinout for Seeed XIAO ESP32-S3:
// TFT_MOSI  -> GPIO 9  (D10)
// TFT_SCLK  -> GPIO 7  (D8)
// TFT_CS    -> GPIO 2  (D1)
// TFT_DC    -> GPIO 3  (D2)
// TFT_RST   -> GPIO 4  (D3)
// TFT_BL    -> GPIO 1  (D0 / Backlight PWM, optional)
