#include "Adafruit_TLC5947.h"

// How many boards do you have chained?
#define NUM_TLC5974 1

#define data   4
#define clock   5
#define latch   6
#define oe  -1  // set to -1 to not use the enable pin (its optional)
#define BRIGHTNESS 3000
#define LEDS 11

#define DOT 0
#define DAT 1
#define UNIT 200

uint8_t leds[] = {4,5,7,8,9,10,11,12,13,15,16};

Adafruit_TLC5947 tlc = Adafruit_TLC5947(NUM_TLC5974, clock, data, latch);

void setup() {
	Serial.begin(9600);
	
	Serial.println("[xmas lights]");
	tlc.begin();
	if (oe >= 0) {
		pinMode(oe, OUTPUT);
		digitalWrite(oe, LOW);
	}
	uint8_t x;
	for(x = 0; x < LEDS; x++) {
		Serial.println(leds[x]);
		tlc.setPWM(leds[x], BRIGHTNESS);
		tlc.write();
		delay(20);
	}
	delay(1000);
}

void loop() {
	/*
	pwm(4);
	randomLights(10);
	sequantial(10);
	flashAll(4);
	*/
	morse('g');
	morse('o');
	morse('d');
	delay(UNIT*7);
	morse('j');
	morse('u');
	morse('l');
	delay(UNIT*7);
}

void randomLights(uint8_t loops) {
	Serial.println("[random loop]");
	uint8_t x, l, led;
	for(x = 0; x < loops; x++) {
		led = random(0, LEDS);
		for(l = 0; l < LEDS; l++) {
			if(l == led) {
				tlc.setPWM(leds[l], BRIGHTNESS);
			}
			else {
				tlc.setPWM(leds[l], 0);
			}
			tlc.write();
			delay(20);
		}
	}
}

void sequantial(uint8_t loops) {
	Serial.println("[sequantial loop]");
	uint8_t x,l;
	int d = 50;
	for(l = 0; l < loops; l++) {
		for(x = 0; x < LEDS; x++) {
			tlc.setPWM(leds[x], BRIGHTNESS);
			tlc.write();
			delay(d);
		}
		for(x = 0; x < LEDS; x++) {
			tlc.setPWM(leds[x], 0);
			tlc.write();
			delay(d);
		}
	}
}

void pwm(uint8_t loops) {
	Serial.println("[PWM loop]");
	uint8_t x,l;
	int b, d = 50;
	for(l = 0; l < loops; l++) {
		for(b = 0; b < 4000; b += 100) {
			for(x = 0; x < LEDS; x++) {
				tlc.setPWM(leds[x], b);
			}
			tlc.write();
			delay(d);
		}
		for(b = 4000; b > 0; b -= 100) {
			for(x = 0; x < LEDS; x++) {
				tlc.setPWM(leds[x], b);
			}
			tlc.write();
			delay(d);
		}

	}
}

void flashAll(uint8_t loops) {
	Serial.println("[Flashy flashy!]");
	uint8_t l, x;
	int d = 300;
	for(l = 0; l < loops; l++) {
		for(x = 0; x < LEDS; x++) {
			tlc.setPWM(leds[x], BRIGHTNESS);
		}
		tlc.write();
		delay(d);
		for(x = 0; x < LEDS; x++) {
			tlc.setPWM(leds[x], 0);
		}
		tlc.write();
		delay(d);
	}
}

void morse (char letter) {
	Serial.print("Morse: ");
	Serial.println(letter);
	switch (letter) {
		case 'a':
		dashBlink(DOT);
		dashBlink(DAT);
		break;
		case 'b':
		dashBlink(DAT);
		dashBlink(DOT);
		dashBlink(DOT);
		dashBlink(DOT);
		break;
		case 'c':
		dashBlink(DAT);
		dashBlink(DOT);
		dashBlink(DAT);
		dashBlink(DOT);
		break;
		case 'd':
		dashBlink(DAT);
		dashBlink(DOT);
		dashBlink(DOT);
		break;
		case 'e':
		dashBlink(DOT);
		break;
		case 'f':
		dashBlink(DOT);
		dashBlink(DOT);
		dashBlink(DAT);
		dashBlink(DOT);
		break;
		case 'g':
		dashBlink(DAT);
		dashBlink(DAT);
		dashBlink(DOT);
		break;
		case 'h':
		dashBlink(DOT);
		dashBlink(DOT);
		dashBlink(DOT);
		dashBlink(DOT);
		break;
		case 'i':
		dashBlink(DOT);
		dashBlink(DOT);
		break;
		case 'j':
		dashBlink(DOT);
		dashBlink(DAT);
		dashBlink(DAT);
		dashBlink(DAT);
		break;
		case 'k':
		dashBlink(DAT);
		dashBlink(DOT);
		dashBlink(DAT);
		break;
		case 'l':
		dashBlink(DOT);
		dashBlink(DAT);
		dashBlink(DOT);
		dashBlink(DOT);
		break;
		case 'm':
		dashBlink(DAT);
		dashBlink(DAT);
		break;
		case 'n':
		dashBlink(DAT);
		dashBlink(DOT);
		break;
		case 'o':
		dashBlink(DAT);
		dashBlink(DAT);
		dashBlink(DAT);
		break;
		case 'p':
		dashBlink(DOT);
		dashBlink(DAT);
		dashBlink(DAT);
		dashBlink(DOT);
		break;
		case 'q':
		dashBlink(DAT);
		dashBlink(DAT);
		dashBlink(DOT);
		dashBlink(DAT);
		break;
		case 'r':
		break;
		case 's':
		break;
		case 't':
		break;
		case 'u':
		break;
		case 'v':
		break;
		case 'w':
		break;
		case 'x':
		break;
		case 'y':
		break;
		case 'z':
		break;
	}
	delay(UNIT*3);
}

void dashBlink (uint8_t type) {
	int dot = UNIT, dat = UNIT*3;
	switch (type) {
		case 0:
		blink(dot);
		break;
		case 1:
		blink(dat);
		break;
	}

}

void blink (int duration) {
	uint8_t l, x;
	for(x = 0; x < LEDS; x++) {
		tlc.setPWM(leds[x], BRIGHTNESS);
	}
	tlc.write();
	delay(duration);
	for(x = 0; x < LEDS; x++) {
		tlc.setPWM(leds[x], 0);
	}
	tlc.write();
	delay(UNIT);
}


