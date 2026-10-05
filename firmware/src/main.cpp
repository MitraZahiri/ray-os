/**
 * @file main.cpp
 * @brief RĀY OS - Day 3 (05/10/2026): Zero-Gravity Olfactory Particle Simulation
 * 
 * Implements anti-gravity floating scent molecule physics on a 1.28" GC9A01 
 * round LCD display driven by ESP32-S3 and TFT_eSPI.
 * 
 * Features:
 * - Circular Boundary Collision Physics (2D Elastic Reflection)
 * - Dynamic Scent Profiles (Ambient Clean, Coffee Roast, Citrus Fresh, Floral)
 * - VOC Concentration Reactivity (Molecule agitation & velocity scaling)
 * - Differential Erase (High-FPS flicker-free SPI rendering)
 * 
 * Build in Public: 14-Day Cyber-Companion Sprint
 * Author: Mitra Zahiri / RĀY Project
 */

#include <Arduino.h>
#include <TFT_eSPI.h>
#include "display_config.h"

// Instantiate display driver
TFT_eSPI tft = TFT_eSPI();

// Scent Profiles & Color Palettes
enum ScentCategory {
  SCENT_AMBIENT,    // Neutral clean air: Cyan / Ice Blue
  SCENT_COFFEE,     // Roasted beans: Amber / Gold / Warm Ochre
  SCENT_CITRUS,     // Citrus zest: Lime Green / Lemon Yellow / Orange
  SCENT_FLORAL      // Floral bloom: Violet / Pink / Magenta
};

// Particle Structure
struct Particle {
  float x, y;          // Current position
  float prevX, prevY;  // Previous position for dirty-rect redraw
  float vx, vy;        // Velocity vectors (anti-gravity drift)
  int size;            // Radius in pixels
  uint16_t color;      // RGB565 color
  float speedFactor;   // Individual Brownian jitter multiplier
};

Particle particles[MAX_PARTICLES];
int activeParticleCount = DEFAULT_PARTICLES;

// Ambient Olfactory State
ScentCategory currentScent = SCENT_AMBIENT;
float vocIntensity = 1.0f; // Multiplier: 1.0 (baseline) to 3.5 (dense scent burst)
unsigned long lastProfileSwitch = 0;

// Color helper palettes (RGB565)
const uint16_t PALETTE_AMBIENT[] = { TFT_CYAN, 0x07FF, 0x5DDF, 0x7E1F };
const uint16_t PALETTE_COFFEE[]  = { 0xFD20, 0xFEA0, 0xD400, 0x9A60 };
const uint16_t PALETTE_CITRUS[]  = { 0x07E0, 0xFFE0, 0xFDA0, 0x87E0 };
const uint16_t PALETTE_FLORAL[]  = { 0xF81F, 0xD01F, 0xFA9A, 0xBC1F };

uint16_t getRandomPaletteColor(ScentCategory category) {
  int idx = random(0, 4);
  switch (category) {
    case SCENT_COFFEE: return PALETTE_COFFEE[idx];
    case SCENT_CITRUS: return PALETTE_CITRUS[idx];
    case SCENT_FLORAL: return PALETTE_FLORAL[idx];
    case SCENT_AMBIENT:
    default:           return PALETTE_AMBIENT[idx];
  }
}

void applyScentProfile(ScentCategory newCategory) {
  currentScent = newCategory;
  for (int i = 0; i < activeParticleCount; i++) {
    particles[i].color = getRandomPaletteColor(currentScent);
  }
}

void initParticles() {
  for (int i = 0; i < activeParticleCount; i++) {
    particles[i].x = CENTER_X + (random(-30, 30));
    particles[i].y = CENTER_Y + (random(-30, 30));
    particles[i].prevX = particles[i].x;
    particles[i].prevY = particles[i].y;
    
    // Initial zero-gravity drift velocity
    float angle = random(0, 360) * 0.0174533f;
    float initialSpeed = random(10, 25) / 10.0f;
    particles[i].vx = cos(angle) * initialSpeed;
    particles[i].vy = sin(angle) * initialSpeed;
    
    particles[i].size = random(2, 6);
    particles[i].speedFactor = random(8, 14) / 10.0f;
    particles[i].color = getRandomPaletteColor(currentScent);
  }
}

void setup() {
  Serial.begin(115200);
  delay(100);
  Serial.println("\n[RĀY OS] Initializing Zero-Gravity Scent Visualizer (Day 3)...");

  tft.init();
  tft.setRotation(0);
  tft.fillScreen(TFT_BLACK);

  // Subtle outer horizon indicator for round glass sphere look
  tft.drawCircle(CENTER_X, CENTER_Y, BOUNDARY_RADIUS + 1, 0x2104); // Dim cyber ring
  tft.drawCircle(CENTER_X, CENTER_Y, BOUNDARY_RADIUS + 2, 0x1082);

  randomSeed(esp_random());
  initParticles();

  Serial.println("[RĀY OS] GC9A01 Display Ready. Zero-G physics loop running.");
}

void loop() {
  // Demo: Cycle scent profiles every 7 seconds to showcase TinyML classification
  unsigned long now = millis();
  if (now - lastProfileSwitch > 7000) {
    lastProfileSwitch = now;
    int nextProfile = (currentScent + 1) % 4;
    applyScentProfile((ScentCategory)nextProfile);

    // Vary VOC intensity for demonstration
    vocIntensity = 1.0f + (random(0, 25) / 10.0f);
    
    Serial.printf("[RĀY Scent Engine] Switched to Profile ID %d (VOC Agitation: %.1fx)\n", 
                  nextProfile, vocIntensity);
  }

  // Physics & Render Pass
  for (int i = 0; i < activeParticleCount; i++) {
#if USE_DIRTY_RECT_ERASE
    // Step 1: Differential erase - remove previous particle footprint (Ultra-fast, 60fps)
    tft.fillCircle((int)particles[i].prevX, (int)particles[i].prevY, particles[i].size, TFT_BLACK);
#endif

    // Step 2: Integrate velocity with VOC agitation multiplier
    float effectiveVx = particles[i].vx * vocIntensity * particles[i].speedFactor;
    float effectiveVy = particles[i].vy * vocIntensity * particles[i].speedFactor;

    particles[i].x += effectiveVx;
    particles[i].y += effectiveVy;

    // Step 3: Circular boundary collision test (Glass Sphere Container)
    float dx = particles[i].x - CENTER_X;
    float dy = particles[i].y - CENTER_Y;
    float distance = sqrt(dx * dx + dy * dy);

    if (distance + particles[i].size >= BOUNDARY_RADIUS) {
      // Avoid division by zero
      if (distance < 0.001f) distance = 0.001f;

      // Surface normal unit vector
      float nx = dx / distance;
      float ny = dy / distance;

      // Specular velocity vector reflection (2D Elastic Boundary)
      float dotProduct = particles[i].vx * nx + particles[i].vy * ny;
      particles[i].vx -= 2.0f * dotProduct * nx;
      particles[i].vy -= 2.0f * dotProduct * ny;

      // Prevent boundary escape by clamping inside safe radius
      particles[i].x = CENTER_X + nx * (BOUNDARY_RADIUS - particles[i].size);
      particles[i].y = CENTER_Y + ny * (BOUNDARY_RADIUS - particles[i].size);

      // Add microscopic micro-turbulence after bounce for organic feel
      particles[i].vx += (random(-10, 10) / 100.0f);
      particles[i].vy += (random(-10, 10) / 100.0f);
    }

    // Step 4: Render active molecule
    tft.fillCircle((int)particles[i].x, (int)particles[i].y, particles[i].size, particles[i].color);

    // Save previous position for differential erase in the next frame
    particles[i].prevX = particles[i].x;
    particles[i].prevY = particles[i].y;
  }

#if !USE_DIRTY_RECT_ERASE
  // Full-frame redraw mode (Alternative fallback)
  delay(12);
  tft.fillScreen(TFT_BLACK);
#endif

  // Target smooth ~60 FPS
  delay(TARGET_FRAME_MS);
}
