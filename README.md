# ESP32 Wireless Air Mouse (Battery powered)

This project turns an ESP32 + MPU6050 into a Bluetooth Low Energy (BLE) air mouse.

# Features
- Gyroscope-based cursor control
- Smooth movement filtering
- Left & Right click buttons
- Scroll support 
- Wireless
- Rechargeable and portable

# Components Used
- ESP32 Dev Board
- MPU6050 
- Push buttons (4x)
- PCB
- lithium ion cell
- li-ion battery charging module

# How it Works
The MPU6050 reads hand motion. ESP32 converts gyro data into mouse movements using BLE HID protocol.

# Code
Main code is inside `src/esp32_air_mouse.ino`

# Setup
1. Install ESP32 board in Arduino IDE
2. Install libraries:
   - Adafruit MPU6050
   - Adafruit Sensor h
   - BleMouse
3. Upload code to ESP32
4. Pair with Bluetooth device

## 📌 Notes
- Keep MPU6050 stable during calibration
- Use proper smoothing for better cursor control
