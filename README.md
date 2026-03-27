# 🚗 Smart Parking Assistant (Embedded C++)

## 📌 Project Overview
This project is an Embedded C++ implementation of a Smart Parking Assistant. It uses a microcontroller to read real-time data from an ultrasonic distance sensor and provides visual and auditory feedback to the driver based on proximity to an obstacle.

🔗 wokwi.com/projects/459684117753375745

## ⚙️ Hardware Components
* **Microcontroller:** Arduino Uno / ESP32
* **Sensor:** HC-SR04 Ultrasonic Distance Sensor
* **Display:** 16x2 LCD Display (I2C)
* **Actuators:** 3x LEDs (Green, Yellow, Red) and a Piezo Buzzer

## 🧠 System Logic
1. **Safe Zone (> 200 cm):** Green LED is ON. LCD displays "SAFE".
2. **Warning Zone (100 cm - 200 cm):** Yellow LED is ON. Buzzer beeps intermittently. LCD displays "WARNING".
3. **Danger Zone (< 100 cm):** Red LED is ON. Buzzer emits a continuous tone. LCD displays "STOP!".

## 🛠️ Tech Stack
* **C / C++**
* **Microcontroller Programming** (GPIO manipulation, timing, I2C communication)
* **Wokwi Simulator**
