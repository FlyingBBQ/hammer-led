#include <FastLED.h>
#include <stdint.h>

#define LED_PIN     5
#define NUM_LEDS    60

CRGB leds[NUM_LEDS];
static uint64_t lightning_event = 0;

int timer = 0;

void setup() {
  FastLED.addLeds<WS2812, LED_PIN, GRB>(leds, NUM_LEDS);
  randomSeed(analogRead(0));
  lightning_event = millis();
  lightning_event += random(1000, 10000);
}

//Function to create event
bool is_lightning_event(int ltimer){
  if (millis() > lightning_event) {
    lightning_event = millis() + random(100, 10000); //Event occurrence
    timer = 10; //Event length
    return true;
  }
  else if(ltimer != 0){
    timer--;
    return true;
  }
  else {
    // do nothing, check next loop
    return false;
  }
}

//Function to create image
void lightning(int ltimer) {
  if(ltimer %2 == 0)
  {
    for (int i = 0; i <= NUM_LEDS; i++) {
        leds[i] = CRGB::CRGB(10, 10, 10);
      }
  
  }
  else
  {
     for (int i = 0; i <= NUM_LEDS; i++) {
        leds[i] = CRGB::CRGB(0, 0, 0);
      }
  }

}

void rain(int ltimer) {
  for (int i = 0; i <= NUM_LEDS; i++) {
    uint8_t blue_random = random(0, 50);
    leds[i] = CRGB(0, 0, blue_random);
  }
}

void loop() {

//create image
if (is_lightning_event(timer)) {
  lightning(timer);
} else {
  rain(timer);
}

//show image
FastLED.show();
delay(100);  



}

