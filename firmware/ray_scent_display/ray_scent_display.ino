/**
 * @file ray_scent_display.ino
 * @brief RĀY OS - Day 3 (05/10/2026): Zero-Gravity Olfactory Particle Simulation
 * 
 * Standalone Arduino IDE Sketch for 1.28" GC9A01 Round LCD + ESP32-S3
 * 
 * Hardware:
 * - Seeed Studio XIAO ESP32-S3 (or any ESP32-S3 dev board)
 * - 1.28" Round GC9A01 SPI Display (240x240)
 * 
 * Libraries Required:
 * - TFT_eSPI (configured for GC9A01 driver)
 */

#include <TFT_eSPI.h>

TFT_eSPI tft = TFT_eSPI();

#define SCREEN_WIDTH 240
#define SCREEN_HEIGHT 240
#define CENTER_X 120
#define CENTER_Y 120
#define RADIUS 114 // Kept slightly under 120 to preserve boundary margin

const int NUM_PARTICLES = 25; // Süzülecek koku molekülü sayısı

struct Particle {
  float x, y;
  float prevX, prevY;
  float vx, vy;
  int size;
  uint16_t color;
};

Particle particles[NUM_PARTICLES];

// Koku Profilleri (Scent Palette Presets)
const uint16_t COLOR_AMBIENT[] = { TFT_CYAN, 0x07FF, 0x5DDF };       // Nötr/Ferah
const uint16_t COLOR_COFFEE[]  = { 0xFD20, 0xFEA0, 0xD400, 0x9A60 }; // Kahve/Kavrulmuş
const uint16_t COLOR_CITRUS[]  = { TFT_GREEN, TFT_YELLOW, 0xFDA0 };  // Narenciye/Limon

void setup() {
  Serial.begin(115200);
  tft.init();
  tft.setRotation(0);
  tft.fillScreen(TFT_BLACK); // Derin uzay / Siber arka plan

  // Siber dairesel sınır halkası (Glass Sphere Rim)
  tft.drawCircle(CENTER_X, CENTER_Y, RADIUS + 1, 0x2104);

  // Partikülleri merkezden başlat ve rastgele hızlar ver
  for (int i = 0; i < NUM_PARTICLES; i++) {
    particles[i].x = CENTER_X + random(-20, 20);
    particles[i].y = CENTER_Y + random(-20, 20);
    particles[i].prevX = particles[i].x;
    particles[i].prevY = particles[i].y;
    
    // Anti-gravity süzülme hızı
    particles[i].vx = (random(-100, 100) / 50.0);
    particles[i].vy = (random(-100, 100) / 50.0);
    particles[i].size = random(2, 6);
    particles[i].color = COLOR_AMBIENT[random(0, 3)];
  }
}

void loop() {
  // BME688'den gelen VOC değerine göre hız çarpanı simülasyonu
  float speedMultiplier = 1.0; 

  for (int i = 0; i < NUM_PARTICLES; i++) {
    // 1. Önceki partikülü temizle (Differential Erase - Titremesiz 60FPS)
    tft.fillCircle((int)particles[i].prevX, (int)particles[i].prevY, particles[i].size, TFT_BLACK);

    // 2. Pozisyonu güncelle
    particles[i].x += (particles[i].vx * speedMultiplier);
    particles[i].y += (particles[i].vy * speedMultiplier);

    // 3. Yuvarlak ekran sınır çarpışma testi (Daire denklemi)
    float dx = particles[i].x - CENTER_X;
    float dy = particles[i].y - CENTER_Y;
    float distance = sqrt(dx * dx + dy * dy);

    if (distance + particles[i].size >= RADIUS) {
      if (distance < 0.001f) distance = 0.001f;

      // Yüzey normal vektörü
      float nx = dx / distance;
      float ny = dy / distance;
      
      // Hız vektörünü yansıt (Reflection / Sekme)
      float dotProduct = particles[i].vx * nx + particles[i].vy * ny;
      particles[i].vx -= 2 * dotProduct * nx;
      particles[i].vy -= 2 * dotProduct * ny;
      
      // Sınırın dışına kaçmasını engellemek için içeri çek
      particles[i].x = CENTER_X + nx * (RADIUS - particles[i].size);
      particles[i].y = CENTER_Y + ny * (RADIUS - particles[i].size);
    }

    // 4. Partikülü çiz
    tft.fillCircle((int)particles[i].x, (int)particles[i].y, particles[i].size, particles[i].color);

    // Sonraki karede silmek için konumu kaydet
    particles[i].prevX = particles[i].x;
    particles[i].prevY = particles[i].y;
  }

  delay(16); // ~60 FPS akıcılığı için
}
