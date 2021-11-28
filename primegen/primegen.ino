
#include "pitches.h"

#define TFT_DC    9
#define TFT_RST   8 
#define SCR_WD   240
#define SCR_HT   240   // 320 - to allow access to full 240x320 frame buffer
#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Arduino_ST7789_Fast.h>
Arduino_ST7789 lcd = Arduino_ST7789(TFT_DC, TFT_RST);

byte ledPin[] = {2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12};
int n = 2048;
unsigned long i = 2;
int lastState = 0;
int state = 0;

void setup() {
  pinMode(LED_BUILTIN, OUTPUT);
//  for (int i = 0; i < 11; i++) {
//    pinMode(ledPin[i], OUTPUT);
//  }
  pinMode(2, INPUT_PULLUP);
  Serial.begin(9600);
  Serial.println("Starting");
  lcd.init(SCR_WD, SCR_HT);
  lcd.setTextColor(BLACK);
  lcd.setTextSize(5);
  lcd.setCursor(24,110);
  lcd.fillScreen(WHITE);
  lcd.drawRect(0,0,240,240,GREEN);
}

//void displayBinary(int num) {
//  for (int i = 0 ; i < 11; i++) {
//    byte state = bitRead(num, i);
//    digitalWrite(ledPin[i], state);
//  }
//}

bool checkPrime(unsigned long num) {
  int result = 1;
  for (int i = 2; i <= sqrt(num); i++) {
    if (num % i == 0) {
      result = 0;
      break;
    }
    
  }
  return result;
}

void clearPin() {
  for (int i = 0 ; i < 11 ; i++) {
    digitalWrite(ledPin[i], LOW);
  }
}

// the loop function runs over and over again forever
void loop() {
  while (!checkPrime(i)) {
    i++;
  }
//  displayBinary(i);
lcd.setCursor(24,24);
  lcd.fillScreen(WHITE);
  lcd.drawRect(0,0,240,240,GREEN);
  
  lcd.println(i);
  Serial.println(i);
  
  while (1) {
    lastState = state;
    state = digitalRead(2);
    if (state == LOW && lastState == HIGH) {
//  delay(500);
      Serial.println("I");
      if (checkPrime(i)) i++;
      
      break;
    }
  }
  
}
