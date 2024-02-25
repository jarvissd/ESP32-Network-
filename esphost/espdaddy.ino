#include <WiFi.h>

const char* ssid = "Đ.Vinh";
const char* password = "87654321";

WiFiServer server(80);
WiFiClient client1;
WiFiClient client2;

// Chân kết nối của đèn LED trên ESP32 host
#define led1 27
#define led2 26
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

  // Cấu hình chân số cho đèn LED
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  digitalWrite(led1, LOW);
  digitalWrite(led2, LOW); // Tắt đèn LED ban đầu

  // Bắt đầu lắng nghe trên cổng 80
  server.begin();
}

void loop() {
  // Chờ cho kết nối từ ESP32 con 1
  if (!client1.connected()) {
    client1 = server.available();
    if (client1) {
      Serial.println("Client 1 connected");
    }
  }
    delay(100);
  // Chờ cho kết nối từ ESP32 con 2
  if (!client2.connected()) {
    client2 = server.available();
    if (client2) {
      Serial.println("Client 2 connected");
    }
  }
  delay(200);
  // Đọc dữ liệu từ ESP32 con 1
  while ((client1.connected() && client1.available()) || (client2.connected() && client2.available())) 
 {
    String data1 = client1.readStringUntil('\n');
    String data2 = client2.readStringUntil('\n');
     
    Serial.println("Received from Client 1: " + data1);
    delay(100);
    Serial.println("Received from Client 2: " + data2);
    delay(100);
     
    if (data1.indexOf("Motion detected from 1") != -1 && data2.indexOf("Motion detected from 2") != -1) {
      
      digitalWrite(led1, HIGH);
      digitalWrite(led2, HIGH);
    }
     
       else if(data1.indexOf("Motion detected from 1") != -1 && data2.indexOf("No motion from 2") != -1)
     { 
      digitalWrite(led1, HIGH);
      digitalWrite(led2, LOW);
       
    }
     
    else if(data1.indexOf("No motion from 1") != -1 && data2.indexOf("Motion detected from 2") != -1)
     { 
      digitalWrite(led1, LOW);
       digitalWrite(led2, HIGH);
       
    }
     
    else 
      {digitalWrite(led1, LOW);
      digitalWrite(led2, LOW);
      }
    // Phản hồi lại Client 1 nếu cần
    //client1.println("Data received by the server");
    //client1.flush();
    //delay(100);
   // client2.println("Data received by the server");
    //client2.flush();
 }
 }
  
  


