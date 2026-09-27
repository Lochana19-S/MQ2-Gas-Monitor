#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <ESP32Servo.h>

// =====================================================
// OLED
// =====================================================

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64

#define OLED_RESET -1
#define OLED_ADDRESS 0x3C

// =====================================================
// PIN DEFINITIONS
// =====================================================

// MQ-2
#define MQ2_PIN 34

// Servo
#define SERVO_PIN 13

// Relay Channel 1
#define RELAY_PIN 27

// LEDs
#define GREEN_LED 25
#define YELLOW_LED 26
#define RED_LED 33

// =====================================================
// OBJECTS
// =====================================================

Adafruit_SSD1306 display(
  SCREEN_WIDTH,
  SCREEN_HEIGHT,
  &Wire,
  OLED_RESET
);

Servo gasServo;

// =====================================================
// RELAY CONFIGURATION
// =====================================================

// Most relay modules are ACTIVE LOW.
// If your relay works opposite, change to false.
#define RELAY_ACTIVE_LOW true

// =====================================================
// FAN CONTROL
// =====================================================

void setFan(bool state) {

  if (RELAY_ACTIVE_LOW) {

    if (state) {
      digitalWrite(RELAY_PIN, LOW);
    }
    else {
      digitalWrite(RELAY_PIN, HIGH);
    }

  }
  else {

    if (state) {
      digitalWrite(RELAY_PIN, HIGH);
    }
    else {
      digitalWrite(RELAY_PIN, LOW);
    }
  }
}

// =====================================================
// LED CONTROL
// =====================================================

void setLEDs(bool green, bool yellow, bool red) {

  digitalWrite(
    GREEN_LED,
    green ? HIGH : LOW
  );

  digitalWrite(
    YELLOW_LED,
    yellow ? HIGH : LOW
  );

  digitalWrite(
    RED_LED,
    red ? HIGH : LOW
  );
}

// =====================================================
// SETUP
// =====================================================

void setup() {

  Serial.begin(115200);

  // ---------------------------------------------------
  // MQ-2
  // ---------------------------------------------------

  analogReadResolution(12);

  analogSetPinAttenuation(
    MQ2_PIN,
    ADC_11db
  );

  // ---------------------------------------------------
  // LEDs
  // ---------------------------------------------------

  pinMode(GREEN_LED, OUTPUT);
  pinMode(YELLOW_LED, OUTPUT);
  pinMode(RED_LED, OUTPUT);

  // Start SAFE
  setLEDs(true, false, false);

  // ---------------------------------------------------
  // RELAY
  // ---------------------------------------------------

  pinMode(RELAY_PIN, OUTPUT);

  // Fan OFF initially
  setFan(false);

  // ---------------------------------------------------
  // OLED
  // ---------------------------------------------------

  Wire.begin(21, 22);

  if (!display.begin(
        SSD1306_SWITCHCAPVCC,
        OLED_ADDRESS
      )) {

    Serial.println("OLED NOT FOUND!");

    while (1);
  }

  // ---------------------------------------------------
  // SERVO
  // ---------------------------------------------------

  gasServo.setPeriodHertz(50);

  gasServo.attach(
    SERVO_PIN,
    500,
    2400
  );

  // Start SAFE position
  gasServo.write(0);

  // ---------------------------------------------------
  // STARTUP SCREEN
  // ---------------------------------------------------

  display.clearDisplay();

  display.setTextColor(SSD1306_WHITE);

  display.setTextSize(2);

  display.setCursor(25, 5);

  display.println("MQ-2");

  display.setTextSize(1);

  display.setCursor(15, 35);

  display.println("GAS MONITOR");

  display.display();

  delay(2000);

  Serial.println();
  Serial.println("==============================");
  Serial.println("       MQ-2 GAS MONITOR");
  Serial.println("==============================");
  Serial.println("SAFE     : 0 - 1999");
  Serial.println("DANGER   : 2000 - 2999");
  Serial.println("CRITICAL : 3000 - 4095");
  Serial.println("==============================");
}

// =====================================================
// LOOP
// =====================================================

void loop() {

  // ---------------------------------------------------
  // READ MQ-2
  // ---------------------------------------------------

  int raw = analogRead(MQ2_PIN);

  String status;

  int servoAngle;

  bool fanState;


  // ===================================================
  // SAFE
  // ===================================================

  if (raw < 2500) {

    status = "SAFE";

    servoAngle = 0;

    fanState = false;

    setLEDs(
      true,
      false,
      false
    );
  }


  // ===================================================
  // DANGER
  // ===================================================

  else if (raw < 3000) {

    status = "DANGER";

    servoAngle = 90;

    fanState = true;

    setLEDs(
      false,
      true,
      false
    );
  }


  // ===================================================
  // CRITICAL
  // ===================================================

  else {

    status = "CRITICAL";

    servoAngle = 180;

    fanState = true;

    setLEDs(
      false,
      false,
      true
    );
  }


  // ---------------------------------------------------
  // SERVO
  // ---------------------------------------------------

  gasServo.write(servoAngle);


  // ---------------------------------------------------
  // FAN
  // ---------------------------------------------------

  setFan(fanState);


  // ---------------------------------------------------
  // SERIAL MONITOR
  // ---------------------------------------------------

  Serial.print("MQ-2 RAW: ");
  Serial.print(raw);

  Serial.print(" | STATUS: ");
  Serial.print(status);

  Serial.print(" | SERVO: ");
  Serial.print(servoAngle);

  Serial.print(" deg");

  Serial.print(" | FAN: ");

  if (fanState) {
    Serial.println("ON");
  }
  else {
    Serial.println("OFF");
  }


  // ---------------------------------------------------
  // OLED
  // ---------------------------------------------------

  display.clearDisplay();

  display.setTextColor(SSD1306_WHITE);

  display.setTextSize(1);

  display.setCursor(0, 0);

  display.println("MQ-2 GAS MONITOR");

  display.drawLine(
    0,
    11,
    127,
    11,
    SSD1306_WHITE
  );

  display.setCursor(0, 19);

  display.print("RAW: ");

  display.println(raw);


  display.setCursor(0, 31);

  display.print("STATUS: ");

  display.println(status);


  display.setCursor(0, 43);

  display.print("SERVO: ");

  display.print(servoAngle);

  display.println(" deg");


  display.setCursor(0, 55);

  display.print("FAN: ");

  if (fanState) {
    display.println("ON");
  }
  else {
    display.println("OFF");
  }

  display.display();

  delay(1000);
}
