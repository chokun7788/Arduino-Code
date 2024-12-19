#include <Wire.h>
#include <LiquidCrystal_I2C.h>

#define JOY_X A0
#define JOY_Y A1
#define JOY_SX 2

LiquidCrystal_I2C lcd(0x27, 16, 2);

int score = 0;
int numround = 10;
unsigned long timeres = 1000;

void setup() {
  Wire.begin();
  pinMode(JOY_X, INPUT);
  pinMode(JOY_Y, INPUT);
  pinMode(JOY_SX, INPUT_PULLUP);

  lcd.begin(16, 2);
  lcd.backlight();

  Serial.begin(9600);
  lcd.setCursor(0, 0);
  lcd.print("Reaction Game");
  lcd.setCursor(0, 1);
  lcd.print("Press to Start");

  while (digitalRead(JOY_SX) == HIGH);
  lcd.clear();
}

void loop() {
  score = 0;

  for (int i = 0; i < numround; i++) {
    String targetDirection = generateDirection();
    lcd.setCursor(0, 0);
    lcd.print("Direction: ");
    lcd.print(targetDirection);

    unsigned long startTime = millis();
    bool correct = false;

    while (millis() - startTime < timeres) {
      if (checkDirection(targetDirection)) {
        correct = true;
        score++;
        break;
      }
    }

    lcd.setCursor(0, 1);
    if (correct) {
      lcd.print("Correct!     ");
    } else {
      lcd.print("Too Slow!    ");
    }

    delay(1000);
    lcd.clear();
  }

  lcd.setCursor(0, 0);
  lcd.print("Game Over!");
  lcd.setCursor(0, 1);
  lcd.print("Score: ");
  lcd.print(score);

  Serial.print("Game Over! Score: ");
  Serial.println(score);

  while (digitalRead(JOY_SX) == HIGH);
  lcd.clear();
}

String generateDirection() {
  int randNum = random(0, 4);
  switch (randNum) {
    case 0: return "UP";
    case 1: return "DOWN";
    case 2: return "LEFT";
    case 3: return "RIGHT";
  }
  return "";
}

bool checkDirection(String targetDirection) {
  int xVal = analogRead(JOY_X);
  int yVal = analogRead(JOY_Y);

  if (targetDirection == "UP" && yVal < 300) return true;
  if (targetDirection == "DOWN" && yVal > 700) return true;
  if (targetDirection == "LEFT" && xVal < 300) return true;
  if (targetDirection == "RIGHT" && xVal > 700) return true;

  return false;
}
