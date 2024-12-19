#include <Wire.h>
#include <LiquidCrystal_I2C.h>

#define TRIG_PIN 2
#define ECHO_PIN 3
#define JOYSTICK_SW_PIN 4
LiquidCrystal_I2C lcd(0x27, 16, 2);
bool measuring = false;
float distance = 0.0;

float measureDistance() {
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);
  long duration = pulseIn(ECHO_PIN, HIGH);
  float distance = (duration * 0.034) / 2.0;
  return distance;
}

void setup() {
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  pinMode(JOYSTICK_SW_PIN, INPUT_PULLUP);

  lcd.init();
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("Digital Ruler");
  lcd.setCursor(0, 1);
  lcd.print("Press to Start");
  delay(2000);
  lcd.clear();

  Serial.begin(9600);
}

void loop() {
  if (digitalRead(JOYSTICK_SW_PIN) == LOW) {
    measuring = !measuring;
    delay(500);
    if(measuring){
      Serial.println("Start.");
    } else {
      Serial.println("Stop");
    }
  }
  if (measuring) {
    distance = measureDistance();
    lcd.setCursor(0, 0);
    lcd.print("Distance: ");
    lcd.setCursor(10, 0);
    lcd.print("      ");
    lcd.setCursor(10, 0);
    lcd.print(distance, 2);
    lcd.print(" cm");
    Serial.print("Distance: ");
    Serial.print(distance, 2);
    Serial.println(" cm");
  } else {
    lcd.setCursor(0, 0);
    lcd.print("Press to Start ");
    lcd.setCursor(0, 1);
    lcd.print("                ");
  }
  delay(200);
}
