#include <WiFi.h>

const char* ssid = "Đ.Vinh";
const char* password = "87654321";
const char* serverIP = "172.20.10.3";

WiFiClient client1;

// Chân kết nối của cảm biến chuyển động SR501
#define PIR_PIN 4

void setup() {
  Serial.begin(115200);
  delay(10);

  // Kết nối WiFi
  Serial.println();
  Serial.println("Connecting to WiFi...");
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  Serial.println("Connected to WiFi");

  // Cấu hình chân số cho cảm biến PIR
  pinMode(PIR_PIN, INPUT);
}

void loop() {
  // Kết nối đến máy chủ
  if (!client1.connected()) {
    Serial.println("Connecting to server...");
    if (client1.connect(serverIP, 80)) {
      Serial.println("Connected to server");
    } else {
      Serial.println("Connection to server failed");
      delay(2000);
      return;
    }
  }

  // Đọc trạng thái của cảm biến chuyển động
  int motionStatus = digitalRead(PIR_PIN);

  // Gửi trạng thái đến máy chủ
  if (motionStatus == HIGH) {
    client1.println("Motion detected from 1");
  } else {
    client1.println("No motion from 1");
  }
  client1.flush();

  // Đợi 2 giây trước khi gửi lại
  delay(2000);
}
