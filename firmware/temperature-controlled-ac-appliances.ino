#include <Wire.h> 
#include <LiquidCrystal_I2C.h> 
 
LiquidCrystal_I2C lcd(0x27, 16, 2); 
 
const int sensorPin = A0; 
const int relayPin = 8; 
 
void setup() { 
  pinMode(relayPin, OUTPUT); 
 
  // Active LOW Relay 
  digitalWrite(relayPin, HIGH);   // Fan OFF 
 
  lcd.init(); 
  lcd.backlight(); 
 
  lcd.setCursor(0,0); 
  lcd.print("Temp Controller"); 
  delay(2000); 
  lcd.clear(); 
} 
 
void loop() { 
 
  int adcValue = analogRead(sensorPin); 
 
  float voltage = adcValue * (5.0 / 1023.0); 
 
  // LM35 Temperature + Calibration 
  float temperature = (voltage * 100.0) - 5.8; 
 
  lcd.setCursor(0,0); 
  lcd.print("Temp:"); 
  lcd.print(temperature,1); 
  lcd.write(223); 
  lcd.print("C  "); 
 
  if(temperature >= 30.0) 
  { 
    digitalWrite(relayPin, LOW);   // Fan ON 
    lcd.setCursor(0,1); 
    lcd.print("Fan: ON "); 
  } 
  else 

  { 
    digitalWrite(relayPin, HIGH);  // Fan OFF 
    lcd.setCursor(0,1); 
    lcd.print("Fan: OFF"); 
  } 
 
  delay(1000); 
}