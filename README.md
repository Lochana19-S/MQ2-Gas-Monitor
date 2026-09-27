# MQ-2 Gas Monitoring and Safety System

## Overview

This project is an ESP32-based intelligent gas monitoring and safety system designed to detect gas concentration in real time using an MQ-2 gas sensor.

The system provides visual monitoring through an OLED display and uses a servo motor, relay-controlled exhaust fan, and LED indicators to respond to different gas-level conditions.

## Features

- Real-time gas-level monitoring using the MQ-2 gas sensor
- OLED display for gas readings and system status
- Three-level gas status indication:
  - SAFE
  - DANGER
  - CRITICAL
- Servo motor control based on gas level
- Automatic exhaust fan control using a relay
- Green, yellow, and red LED indicators
- Serial Monitor output for real-time system information

## Hardware Components

- ESP32 Development Board
- MQ-2 Gas Sensor
- 0.96-inch OLED Display
- Servo Motor
- Relay Module
- Exhaust Fan
- Green LED
- Yellow LED
- Red LED
- Connecting Wires
- Breadboard
- Power Supply

## Pin Configuration

| Component   | ESP32 Pin |
| ----------- | --------- |
| MQ-2 Sensor | GPIO 34   |
| Servo Motor | GPIO 13   |
| Relay       | GPIO 27   |
| Green LED   | GPIO 25   |
| Yellow LED  | GPIO 26   |
| Red LED     | GPIO 33   |
| OLED SDA    | GPIO 21   |
| OLED SCL    | GPIO 22   |

## Gas-Level Conditions

| Gas Sensor Reading | Status   | Servo Angle | Exhaust Fan | LED Indicator |
| ------------------ | -------- | ----------- | ----------- | ------------- |
| Below 2500         | SAFE     | 0°          | OFF         | Green         |
| 2500–2999          | DANGER   | 90°         | ON          | Yellow        |
| 3000–4095          | CRITICAL | 180°        | ON          | Red           |

## Working Principle

1. The MQ-2 sensor continuously measures the gas level.
2. The ESP32 reads the sensor's analog value.
3. The measured value is compared with predefined safety thresholds.
4. The system determines whether the condition is SAFE, DANGER, or CRITICAL.
5. The corresponding LED is activated.
6. The servo motor changes its position according to the detected gas level.
7. The relay automatically controls the exhaust fan.
8. The OLED displays the current gas reading, status, servo angle, and fan state.
9. The same information is also displayed through the Serial Monitor.

## Software Requirements

- Arduino IDE
- ESP32 Board Package
- Adafruit GFX Library
- Adafruit SSD1306 Library
- ESP32Servo Library

## How to Run

1. Install Arduino IDE.
2. Install the ESP32 board package.
3. Install the required libraries.
4. Connect the ESP32 to the computer.
5. Open `MQ2-Gas-Monitor.ino`.
6. Select the correct ESP32 board and COM port.
7. Upload the program.
8. Open the Serial Monitor at **115200 baud**.
9. Observe the gas readings and system response.

## Project Objective

The objective of this project is to develop a real-time gas monitoring and safety system that can detect increasing gas levels and automatically activate appropriate safety mechanisms.

## Technologies Used

- ESP32
- Embedded C/C++
- Arduino IDE
- MQ-2 Gas Sensor
- OLED Display
- Servo Motor
- Relay Module
