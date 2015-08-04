#define PIN_LED 13
#define PIN_RESET 12
#define PIN_COMM 9

#define RESET_TIMEOUT_MS 240000     // 4 minutes


// the setup routine runs once when you press reset:
void setup() {
  digitalWrite(PIN_RESET, HIGH);
  delay(200);
  // initialize the digital pin as an output.
  pinMode(PIN_LED, OUTPUT);
  digitalWrite(PIN_LED, HIGH);

  pinMode(PIN_RESET, OUTPUT);
  pinMode(PIN_COMM, INPUT);

  Serial.begin(9600);//initialize Serial Port
  Serial.println("setup complete");
}

int tmpVal;
int lastVal;
unsigned long lastUpdate = 0;

void doReset() {
  Serial.println("resetting");
  digitalWrite(PIN_RESET, LOW);
  delay(200);
  digitalWrite(PIN_RESET, HIGH);
  Serial.println("end");
  delay(5000);
}

void loop() {
  delay(1000);
  tmpVal = digitalRead(PIN_COMM);

  if (tmpVal!=lastVal) {
    Serial.println("Received ping");
    Serial.println(tmpVal);
    lastVal = tmpVal;
    lastUpdate = millis();
  } else {
    if (millis()-lastUpdate >= RESET_TIMEOUT_MS) {
      doReset();
      lastUpdate = millis();
    } else {
      Serial.print("No change, time to reset: ");
      Serial.println(RESET_TIMEOUT_MS - (millis()-lastUpdate));
    }
  }
  
}
