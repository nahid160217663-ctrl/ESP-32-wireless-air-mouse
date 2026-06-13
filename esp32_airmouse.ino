#include <Wire.h>
#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>
#include <BleMouse.h>

Adafruit_MPU6050 mpu;
BleMouse bleMouse("ESP32 Gyro Mouse");

#define UP_BUTTON 1
#define DOWN_BUTTON 2
#define LEFT_BUTTON 4
#define RIGHT_BUTTON 3

float gx_offset = 0, gy_offset = 0, gz_offset = 0;

float smoothX = 0; float smoothY = 0;


void calibrateGyro() {
  sensors_event_t a, g, temp;

  Serial.println("Calibrating gyro...");
  delay(1000);
  
  for (int i = 0; i < 500; i++) {
    mpu.getEvent(&a, &g, &temp);
    gx_offset += g.gyro.x;
    gy_offset += g.gyro.y;
    gz_offset += g.gyro.z;
    delay(5);
  }

  gx_offset /= 500;
  gy_offset /= 500;
  gz_offset /= 500;

  
}

void setup() {
  Serial.begin(115200);
  Wire.begin();

  pinMode(LEFT_BUTTON, INPUT_PULLUP);
  pinMode(RIGHT_BUTTON,INPUT_PULLUP);
  pinMode(UP_BUTTON, INPUT_PULLUP);
  pinMode(DOWN_BUTTON,INPUT_PULLUP);


  if (!mpu.begin()) {
    Serial.println("MPU6050 not found!");
    while (1);
  }

  calibrateGyro();

  Serial.println("Starting BLE...");
  bleMouse.begin();
}

 void loop() {

  if (!bleMouse.isConnected()) {
    Serial.println("Waiting for Bluetooth...");
    delay(500);
    return;
  }

  sensors_event_t a, g, temp;
  mpu.getEvent(&a, &g, &temp);

 
  float gx = (g.gyro.x - gx_offset) * 57.2958;
  float gy = (g.gyro.y - gy_offset) * 57.2958;
  float gz = (g.gyro.z - gz_offset) * 57.2958;

 if (abs(gx) < 2.5) gx = 0;
 if (abs(gy) < 2.5) gy = 0;

  int moveX = -gz * 0.3;   
  int moveY = -gx * 0.3;   
  
  moveX = constrain(moveX, -60, 60);
  moveY = constrain(moveY, -60, 60);

  smoothX = 0.8*smoothX + 0.2*moveX;
  smoothY = 0.8*smoothY + 0.2*moveY;

  bleMouse.move(smoothX, smoothY);

 
  if (digitalRead(LEFT_BUTTON) == LOW) { bleMouse.click(MOUSE_LEFT);  delay(200); }

  if (digitalRead(RIGHT_BUTTON) == LOW) { bleMouse.click(MOUSE_RIGHT);  delay(200); }

  if (digitalRead(UP_BUTTON) == LOW) { bleMouse.move(0,0,1);    delay(100);  }
   
  if (digitalRead(DOWN_BUTTON) == LOW) { bleMouse.move(0,0,-1);    delay(100);  }

  delay(5);   }