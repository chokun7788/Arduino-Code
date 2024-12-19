#include <DHT.h>

#define SOUND_SENSOR_PIN A0
#define DHT_PIN 2
#define ISD1820_PIN_1 5
#define ISD1820_PIN_2 6

#define SOUND_THRESHOLD 30
#define TEMP_THRESHOLD 28.0

bool systemActive = false;

DHT dht(DHT_PIN, DHT11);

void setup() {
  pinMode(SOUND_SENSOR_PIN, INPUT);
  pinMode(ISD1820_PIN_1, OUTPUT);
  pinMode(ISD1820_PIN_2, OUTPUT);
  digitalWrite(ISD1820_PIN_1, LOW);
  digitalWrite(ISD1820_PIN_2, LOW);

  Serial.begin(9600);
  dht.begin();
  Serial.println("Smart Temperature Detector Ready!");
}

void loop() {
  int soundValue = analogRead(SOUND_SENSOR_PIN);
  if (soundValue > SOUND_THRESHOLD && !systemActive) {
    systemActive = true;
    Serial.println("Clap detected! Starting temperature check...");

    float temperature = dht.readTemperature();

    if (temperature > TEMP_THRESHOLD) {
      Serial.println("Temperature is HIGH!");
      playISD1820(ISD1820_PIN_1);
    } else {
      Serial.println("Temperature is NORMAL.");
      playISD1820(ISD1820_PIN_2);
    }

    delay(5000);
    systemActive = false;
  }
}

void playISD1820(int pin) {
  digitalWrite(pin, HIGH);
  delay(5000);
  digitalWrite(pin, LOW);
}
