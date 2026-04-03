// Pin Definitions
int moisturePin = A0;
int buzzer = 8;
int redLED = 9;
int greenLED = 10;
int relay = 6;

int moistureValue = 0;
int moisturePercent = 0;

void setup() {
  pinMode(buzzer, OUTPUT);
  pinMode(redLED, OUTPUT);
  pinMode(greenLED, OUTPUT);
  pinMode(relay, OUTPUT);

  digitalWrite(relay, HIGH);   // Pump OFF initially
  Serial.begin(9600);
}

void loop() {

  moistureValue = analogRead(moisturePin);
  moisturePercent = map(moistureValue, 1023, 0, 0, 100);

  String soilStatus = "";
  String pumpStatus = "";

  // SENSOR IN AIR
  if (moistureValue > 1000) {
    digitalWrite(redLED, LOW);
    digitalWrite(greenLED, LOW);
    digitalWrite(buzzer, LOW);
    digitalWrite(relay, HIGH);

    soilStatus = "IN_AIR";
    pumpStatus = "OFF";
  }
  // DRY SOIL
  else if (moistureValue > 600) {
    digitalWrite(redLED, HIGH);
    digitalWrite(greenLED, LOW);
    digitalWrite(buzzer, HIGH);
    digitalWrite(relay, LOW);

    soilStatus = "DRY";
    pumpStatus = "ON";
  }
  // WET SOIL
  else {
    digitalWrite(redLED, LOW);
    digitalWrite(greenLED, HIGH);
    digitalWrite(buzzer, LOW);
    digitalWrite(relay, HIGH);

    soilStatus = "WET";
    pumpStatus = "OFF";
  }

  // DATA FORMAT:
  // DATA:RAW,MOISTURE_PERCENT,SOIL_STATUS,PUMP_STATUS
  Serial.print("DATA:");
  Serial.print(moistureValue);
  Serial.print(",");
  Serial.print(moisturePercent);
  Serial.print(",");
  Serial.print(soilStatus);
  Serial.print(",");
  Serial.println(pumpStatus);

  delay(2000);
}
