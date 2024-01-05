#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
  #include <avr/power.h>
#endif

#define PIN_RING1 6
#define PIN_RING2 7
#define PIN_RING3 8

#define PIXELRING1 24
#define PIXELRING2 32
#define PIXELRING3 40

//Command Setup
#define triggerPin 9 //The pin for reading command information
int triggerState = 0;
int lastState = 1;
unsigned long duration;

//  The overall fire brightness
//  (this can affect both color levels and power consumption)
int brightness_Ring1 = 75;
int brightness_Ring2 = 60;
int brightness_Ring3 = 50;

int flicker1 = 0;
int flicker2 = 0;
int flicker3 = 0;

//  Uncomment one of these RGB (Red, Green, Blue) values to
//  set the base color of the flame.  The color will flickr
//  based on the initial base color
  
//  Yellow flame:
//int r = 226, g = 121, b = 35;

//  Orange flame:
//int r = 226, g = 121, b = 20;

//  Purple flame:
//  int r = 158, g = 8, b = 148;

//  Green flame:
//int r = 74, g = 150, b = 12;

//  Red flame:
//int red1 = 255, grn1 = 35, blu1 = 10;   // Ring 1 Center
//int red1 = 226, grn1 = 121, blu1 = 35;   // Ring 1 Center
//int red2 = 255, grn2 = 35, blu2 = 10;   // Ring 2 Middle
//int red3 = 255, grn3 = 35, blu3 = 10;   // Ring 3 Outer

int red1 = 226, grn1 = 35, blu1 = 10;   // Ring 1 Center
int red2 = 255, grn2 = 121, blu2 = 35;   // Ring 2 Middle
int red3 = 255, grn3 = 35, blu3 = 10;   // Ring 3 Outer

//int red1 = 255, grn1 = 121, blu1 = 35;   // Ring 1 Center
//int red2 = 255, grn2 = 121, blu2 = 35;   // Ring 2 Middle
//int red3 = 255, grn3 = 35, blu3 = 10;   // Ring 3 Outer

unsigned long previousMillisRing1 = 0;
unsigned long previousMillisRing2 = 0;
unsigned long previousMillisRing3 = 0;
unsigned long currentMillis = 0;

int delayRing1 = 0;
int delayRing2 = 0;
int delayRing3 = 0;

int goblack = 0;

// Parameter 1 = number of pixels in strip
// Parameter 2 = Arduino pin number (most are valid)
// Parameter 3 = pixel type flags, add together as needed:
//   NEO_KHZ800  800 KHz bitstream (most NeoPixel products w/WS2812 LEDs)
//   NEO_KHZ400  400 KHz (classic 'v1' (not v2) FLORA pixels, WS2811 drivers)
//   NEO_GRB     Pixels are wired for GRB bitstream (most NeoPixel products)
//   NEO_RGB     Pixels are wired for RGB bitstream (v1 FLORA pixels, not v2)
Adafruit_NeoPixel ring1 = Adafruit_NeoPixel(PIXELRING1, PIN_RING1, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel ring2 = Adafruit_NeoPixel(PIXELRING2, PIN_RING2, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel ring3 = Adafruit_NeoPixel(PIXELRING3, PIN_RING3, NEO_GRB + NEO_KHZ800);

// IMPORTANT: To reduce NeoPixel burnout risk, add 1000 uF capacitor across
// pixel power leads, add 300 - 500 Ohm resistor on first pixel's data input
// and minimize distance between Arduino and first pixel.  Avoid connecting
// on a live circuit...if you must, connect GND first.
// For the ultimate NeoPixel guide, check out:
// https://learn.adafruit.com/adafruit-neopixel-uberguide/overview

void setup() {
  Serial.begin(115200);
  
  //command information setup
  pinMode(triggerPin, INPUT_PULLUP);
  
  randomSeed(analogRead(0));
  ring1.begin();
  ring2.begin();
  ring3.begin();
  
  ring1.setBrightness(brightness_Ring1);
  ring2.setBrightness(brightness_Ring2);
  ring3.setBrightness(brightness_Ring3);
  
  ring1.show();
  ring2.show();
  ring3.show();
}

void loop() {
  currentMillis = millis();

  //triggerState = digitalRead(triggerPin);
  
  //if (triggerState != lastState){
    duration = pulseIn(triggerPin,HIGH);//Read the Pin if there has 
    if (duration < 1500){
      //if (triggerState){
      Serial.println(triggerState);
      lastState = 1;//triggerState;
    }
    else{
      lastState = 0;
    }
 // }
  
  if (!lastState){
      lightsOn();
      Serial.println("Lights On");
      }
    else{
      ring1.setBrightness(0);
      ring2.setBrightness(0);
      ring3.setBrightness(0);
      ring1.show();
      ring2.show();
      ring3.show();
      Serial.println("Lights Off");
    }
  }

void lightsOn(){
  if (currentMillis - previousMillisRing1 >= delayRing1) {
    previousMillisRing1 = currentMillis;
    //  Flicker, based on our initial RGB values
    for(int i=0; i < ring1.numPixels(); i++) {
      flicker1 = random(0,55);
      int r1 = red1-flicker1;
      int g1 = grn1-flicker1;
      int b1 = blu1-flicker1;
      if(g1<0) g1=0;
      if(r1<0) r1=0;
      if(b1<0) b1=0;
      ring1.setPixelColor(i,r1,g1,b1);
      //ring1.setBrightness(random(brightness_Ring1-50,brightness_Ring1));
      ring1.setBrightness(brightness_Ring1);
    }
    delayRing1 = random(10,113);
    goblack = random(1,8);
    if(goblack == 1){
      ring1.setBrightness(0);
    }
    ring1.show();
  }
  
  if (currentMillis - previousMillisRing2 >= delayRing2) {
    previousMillisRing2 = currentMillis;
    for(int j=0; j < ring2.numPixels(); j++) {
      flicker2 = random(0,55);
      int r2 = red2-flicker2;
      int g2 = grn2-flicker2;
      int b2 = blu2-flicker2;
      if(g2<0) g2=0;
      if(r2<0) r2=0;
      if(b2<0) b2=0;
      ring2.setPixelColor(j,r2,g2,b2);
      //ring2.setBrightness(random(brightness_Ring2-50,brightness_Ring2));
      ring2.setBrightness(brightness_Ring2);
    }
    delayRing2 = random(10,113);
    goblack = random(1,6);
    if(goblack == 1){
      ring2.setBrightness(0);
    }
    ring2.show();
  }

  if (currentMillis - previousMillisRing3 >= delayRing3) {
    previousMillisRing3 = currentMillis;
    for(int k=0; k < ring3.numPixels(); k++) {
      flicker3 = random(0,55);
      int r3 = red3-flicker3;
      int g3 = grn3-flicker3;
      int b3 = blu3-flicker3;
      if(g3<0) g3=0;
      if(r3<0) r3=0;
      if(b3<0) b3=0;
      ring3.setPixelColor(k,r3,g3,b3);
      ring3.setBrightness(brightness_Ring3);
    }
    delayRing3 = random(10,113);
    goblack = random(1,8);
    if(goblack == 1){
      ring3.setBrightness(0);
    }
    ring3.show();
  }
//void lightsOff(){
//  
//}
}
