#include <FastLED.h>
#include <stdint.h>

#define LED_PIN     5
#define NUM_LEDS    60

CRGB g_leds[NUM_LEDS];
static uint64_t g_lightning_event = 0;

enum LedState {
        IDLE,
        TEST
};
static LedState g_led_state = IDLE;

void setup() {
        FastLED.addLeds<WS2812, LED_PIN, GRB>(g_leds, NUM_LEDS);
        Serial.begin(115200);

        randomSeed(analogRead(0));
        g_lightning_event = millis();
        g_lightning_event += random(1000, 10000);
}

bool is_lightning_event(void) {
        if (millis() > g_lightning_event) {
                g_lightning_event = millis() + random(100, 10000);
                return true;
        } else {
                // do nothing, check next loop
                return false;
        }
}

void lightning(void) {
        for (int i = 0; i <= NUM_LEDS; i++) {
                g_leds[i] = CRGB::White;
        }
}

void rain(void) {
        for (int i = 0; i <= NUM_LEDS; i++) {
                uint8_t blue_random = random(0, 255);
                g_leds[i] = CRGB(0, 0, blue_random);
        }
}

void testing(void) {
        static unsigned int led_pos = 1;

        led_pos++;
        g_leds[(led_pos - 2) % NUM_LEDS] = CRGB(0, 32, 0);
        g_leds[(led_pos - 1) % NUM_LEDS] = CRGB(0, 128, 0);
        g_leds[led_pos % NUM_LEDS] = CRGB(0, 255, 0);
        g_leds[(led_pos + 1) % NUM_LEDS] = CRGB(0, 128, 0);
}

void handle_serial(void) {
        String command = Serial.readStringUntil('\n');
        command.trim();

        if (command == "IDLE") {
                g_led_state = IDLE;
                Serial.println("state: " + command);
        } else if (command == "TEST") {
                g_led_state = TEST;
                Serial.println("state: " + command);
        } else {
                Serial.println("unknown command: " + command);
        }
}

void loop() {
        if (Serial.available() > 0) {
                handle_serial();
        }

        switch (g_led_state) {
        case IDLE:
                if (is_lightning_event()) {
                        lightning();
                } else {
                        rain();
                }
                break;

        case TEST:
                testing();
                break;
        }

        FastLED.show();
        delay(100);  
}

