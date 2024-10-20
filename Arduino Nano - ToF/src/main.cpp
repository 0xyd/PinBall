#include <VL53L0X.h>
#include <Wire.h>

VL53L0X sensor;  // 宣告VL53L0X類型物件

void setup() {
  Serial.begin(57600);
  Wire.begin();  // 啟動I2C通訊
  Wire.setClock(400000);
  sensor.setTimeout(500);  // 設定感測器超時時間
  // 若無法初始化感測器（如：硬體沒有接好），則顯示錯誤訊息。
  if (!sensor.init()) {
    Serial.println("Failed to detect and initialize sensor!");
    // while (1) {}
  } 
  else {
    Serial.println("Detected!");
  }
}

void loop() {
  // Serial.println("Test");
  // // 在序列埠監控視窗顯示測距值
  uint16_t t = sensor.readRangeSingleMillimeters();

  if (t >= 40) {
    Serial.print("Detected\t");
    Serial.println(t);
  }

  // Serial.print(sensor.readRangeSingleMillimeters());
  // // 若發生超時（感測器沒有回應），則顯示“TIMEOUT”。
  if (sensor.timeoutOccurred()) { Serial.print(" TIMEOUT"); }
  delay(10);
  Serial.println();
}