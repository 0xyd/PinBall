#include <VL53L0X.h>
#include <Wire.h>

VL53L0X sensor_A;  // 宣告VL53L0X類型物件
VL53L0X sensor_B;
// VL53L0X sensor_C;

#define XSHUT_A 8
#define XSHUT_B 7
// #define XSHUT_C 10

#define THRESHOLD 0 // Test Value
// #define THRESHOLD 40 

void setup() {
  Serial.begin(57600);
  Wire.begin();  // 啟動I2C通訊
  Wire.setClock(400000);

  pinMode(XSHUT_A, OUTPUT);
  pinMode(XSHUT_B, OUTPUT);
  // pinMode(XSHUT_C, OUTPUT);

  sensor_A.setTimeout(500);  // 設定感測器超時時間
  // 若無法初始化感測器（如：硬體沒有接好），則顯示錯誤訊息。
  digitalWrite(XSHUT_A, LOW);
  digitalWrite(XSHUT_B, LOW);
  // digitalWrite(XSHUT_C, LOW);

  digitalWrite(XSHUT_A, HIGH);
  if (!sensor_A.init()) {
    Serial.println("Failed to detect and initialize sensor A!");
    // while (1) {}
  } 
  else {
    Serial.println("Detected sensor A!");
    sensor_A.setAddress(0);
    // sensor_A.setAddress(42);
  }

  digitalWrite(XSHUT_B, HIGH);
  if (!sensor_B.init()) {
    Serial.println("Failed to detect and initialize sensor B!");
    // while (1) {}
  } 
  else {
    Serial.println("Detected sensor B!");
    sensor_B.setAddress(1);
    // sensor_B.setAddress(43);
  }

  // digitalWrite(XSHUT_C, HIGH);
  // if (!sensor_C.init()) {
  //   Serial.println("Failed to detect and initialize sensor B!");
  //   // while (1) {}
  // } 
  // else {
  //   Serial.println("Detected sensor C!");
  //   sensor_C.setAddress(2);
  //   // sensor_B.setAddress(43);
  // }
}

void loop() {
  // Serial.println("Test");
  // // 在序列埠監控視窗顯示測距值
  uint16_t t1 = sensor_A.readRangeSingleMillimeters();
  uint16_t t2 = sensor_B.readRangeSingleMillimeters();
  // uint16_t t3 = sensor_C.readRangeSingleMillimeters();

  if (t1 >= THRESHOLD) {
    Serial.print("Detected by sensor A\t");
    Serial.println(t1);
  }

  if (t2 >= THRESHOLD) {
    Serial.print("Detected by sensor B\t");
    Serial.println(t2);
  }

  // if (t3 >= THRESHOLD) {
  //   Serial.print("Detected by sensor C\t");
  //   Serial.println(t3);
  // }

  // Serial.print(sensor.readRangeSingleMillimeters());
  // // 若發生超時（感測器沒有回應），則顯示“TIMEOUT”。
  if (sensor_A.timeoutOccurred()) { Serial.print("Sensor A TIMEOUT"); }
  if (sensor_B.timeoutOccurred()) { Serial.print("Sensor B TIMEOUT"); }
  // if (sensor_C.timeoutOccurred()) { Serial.print("Sensor C TIMEOUT"); }
  delay(100);
  Serial.println();
}