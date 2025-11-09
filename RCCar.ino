#include "BluetoothSerial.h"

BluetoothSerial SerialBT;

// Motor driver pins
#define IN1 19
#define IN2 18
#define IN3 2
#define IN4 4
#define ENA 22   // Enable pin for Motor A
#define ENB 23  // Enable pin for Motor B

void setup() {
  Serial.begin(115200);
  SerialBT.begin("SanthoshCar"); // Bluetooth device name
  Serial.println("Bluetooth started! Pair your device.");

  // Motor pins
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);

  // Enable pins
  pinMode(ENA, OUTPUT);
  pinMode(ENB, OUTPUT);

  // Turn on motors
  digitalWrite(ENA, HIGH);
  digitalWrite(ENB, HIGH);
}

void loop() {
  if (SerialBT.available()) {
    char value = SerialBT.read();
    Serial.println(value);

    if (value == 'F') forward();
    else if (value == 'B') backward();
    else if (value == 'L') left();
    else if (value == 'R') right();
    else Stop();
  }
}

// Motor control functions
void forward() {
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
  Serial.println("Forward");
}

void backward() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
  Serial.println("Backward");
}

void left() {
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
  Serial.println("Left");
}

void right() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
  Serial.println("Right");
}

void Stop() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
  Serial.println("Stop");
}
