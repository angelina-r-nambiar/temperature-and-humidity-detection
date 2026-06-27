#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
#include <SimpleDHT.h>

// --- CONFIGURATION ---
int pinDHT11 = 2;         // Data pin connected to Digital 2
SimpleDHT11 dht11(pinDHT11);

// LCD Address - Try 0x27 or 0x3F
LiquidCrystal_I2C lcd(0x27, 16, 2); 

// RGB LED Pins
const int redPin = 9;
const int greenPin = 10;
const int bluePin = 11;

void setup() {
  lcd.init();
  lcd.backlight();
  
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);

  lcd.setCursor(0, 0);
  lcd.print("System Booting...");
  delay(1500);
  lcd.clear();
}

void loop() {
  // SimpleDHT variables
  byte temperature = 0;
  byte humidity = 0;
  int err = SimpleDHTErrSuccess;

  // Reading the sensor
  if ((err = dht11.read(&temperature, &humidity, NULL)) != SimpleDHTErrSuccess) {
    lcd.setCursor(0, 0);
    lcd.print("Read Error...");
    delay(1000);
    return;
  }

  // Displaying on LCD
  lcd.setCursor(0, 0);
  lcd.print("Temp: ");
  lcd.print((int)temperature);
  lcd.print(" C   "); // Spaces clear old digits

  lcd.setCursor(0, 1);
  lcd.print("Humid: ");
  lcd.print((int)humidity);
  lcd.print(" %   ");

  // --- RGB LED COLOR LOGIC ---
  if (temperature < 27) {
    updateLED(0, 0, 255);   // Blue (Cool)
  } 
  else if (temperature >= 27 && temperature <= 31) {
    updateLED(0, 255, 0);   // Green (Comfort)
  } 
  else {
    updateLED(255, 0, 0);   // Red (Hot!)
  }

  delay(2000); // 2-second update interval
}

void updateLED(int r, int g, int b) {
  analogWrite(redPin, r);
  analogWrite(greenPin, g);
  analogWrite(bluePin, b);
}