# Smart Energy Meter with IoT Dashboard

## Overview
A simulated smart energy meter built on ESP32 that monitors
voltage, current, power, and energy consumption in real time.
Readings are displayed on a 16x2 LCD and streamed live to a
Blynk IoT dashboard over WiFi. Fully simulated using Wokwi —
no hardware required.

## Features
- Voltage monitoring: 180V to 240V range
- Current monitoring: 0A to 10A range
- Real-time power calculation in Watts
- Energy accumulation over time in kWh
- LED alert when voltage exceeds 240V or current exceeds 9A
- Live IoT dashboard via Blynk cloud
- No hardware needed — runs entirely on Wokwi simulator

## Components Used
| Component          | Purpose                        |
|--------------------|--------------------------------|
| ESP32 DevKit V1    | Microcontroller with WiFi      |
| Potentiometer x2   | Simulate voltage/current input |
| LCD 16x2 with I2C  | Display readings locally       |
| LED + 220 ohm      | Overvoltage/current alert      |

## Wokwi Simulation Link
[Click here to run the simulation]- https://wokwi.com/projects/466341805526035457

## Circuit
![Circuit Diagram](circuit/circuit_screenshot.png)

## Simulation Output
![LCD Display](simulation/lcd_working.png)
![Serial Monitor](simulation/serial_monitor.png)

## How It Works
1. Two potentiometers simulate voltage (180-240V) and current (0-10A) sensors
2. ESP32 reads both via ADC pins 34 and 35
3. Power is calculated as P = V x I
4. Energy accumulates every second using time delta formula
5. All values display on LCD and send to Blynk dashboard
6. LED turns ON if voltage > 240V or current > 9A

## Pin Connections
| Signal        | ESP32 Pin |
|---------------|-----------|
| Voltage ADC   | GPIO 34   |
| Current ADC   | GPIO 35   |
| LCD SDA       | GPIO 21   |
| LCD SCL       | GPIO 22   |
| Alert LED     | GPIO 2    |

## Skills Demonstrated
- ESP32 ADC reading and analog signal mapping
- I2C communication protocol for LCD
- Real-time energy accumulation algorithm
- IoT cloud integration using Blynk
- Embedded C++ programming
- Circuit simulation using Wokwi

## Author
Name: Anurag              
Degree: B.Sc(H) Electronics, 3rd Year
