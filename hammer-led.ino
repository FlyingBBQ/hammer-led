#include <FastLED.h>
#include <stdint.h>

#define LED_PIN     5
#define NUM_LEDS    60

CRGB leds[NUM_LEDS];
static uint64_t lightning_event = 0;

void setup() {
  FastLED.addLeds<WS2812, LED_PIN, GRB>(leds, NUM_LEDS);
  randomSeed(analogRead(0));
  lightning_event = millis();
  lightning_event += random(1000, 10000);
}

bool is_lightning_event(void) {
  if (millis() > lightning_event) {
    lightning_event = millis() + random(100, 10000);
    return true;
  } else {
    // do nothing, check next loop
    return false;
  }
}

void lightning(void) {
  for (int i = 0; i <= NUM_LEDS; i++) {
    leds[i] = CRGB::White;
  }
}

void rain(void) {
  for (int i = 0; i <= NUM_LEDS; i++) {
    uint8_t blue_random = random(0, 255);
    leds[i] = CRGB(0, 0, blue_random);
  }
}

void loop() {
  if (is_lightning_event()) {
    lightning();
  } else {
    rain();
  }
  FastLED.show();
  delay(100);  
}

