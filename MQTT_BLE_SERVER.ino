#include <WiFi.h>
#include <PubSubClient.h>

#include <BLEDevice.h>
#include <BLEUtils.h>
#include <BLEScan.h>
#include <BLEServer.h>
#include <BLEAdvertisedDevice.h>

WiFiClient espClient;
PubSubClient client(espClient);

const char* ssid = "panoulu";   // Replace with your WiFi network SSID
const char* password = "q1ghost567";   // Replace with your WiFi network password
const char* mqtt_server = "16.170.238.248";  // Replace with your MQTT server address
const char* mqtt_topic = "ble_project_2";  // Replace with the topic you want to subscribe to


int scanTime = 5; //In seconds
BLEScan* pBLEScan;
#define SERVICE_UUID        "99af3e71-7ba2-422c-927d-0affd948b6c5"
#define CHARACTERISTIC_UUID "7505f90d-77eb-465e-8378-06a229f7781d"
BLECharacteristic *pCharacteristic;




// class MyAdvertisedDeviceCallbacks: public BLEAdvertisedDeviceCallbacks {
//     void onResult(BLEAdvertisedDevice advertisedDevice) {
//       Serial.printf("Advertised Device: %s \n", advertisedDevice.toString().c_str());
//     }
// };


void setup() {
  
  Serial.begin(115200);
  WiFi.begin(ssid);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());

  client.setServer(mqtt_server, 1886);
  while (!client.connected()) {
    Serial.print("Attempting to connect to MQTT server...");
    if (client.connect("ESP32Client")) {
      Serial.println("Connected to MQTT server");
      client.subscribe(mqtt_topic);
    } else {
      Serial.print("Failed to connect. Retry in 5 seconds.");
      delay(5000);
    }
  }
  client.setCallback(onMessageReceived);
  BLEDevice::init("XIAO_ESP32S3");
  BLEServer *pServer = BLEDevice::createServer();
  BLEService *pService = pServer->createService(SERVICE_UUID);
  pCharacteristic = pService->createCharacteristic(
                                         CHARACTERISTIC_UUID,
                                         BLECharacteristic::PROPERTY_READ |
                                         BLECharacteristic::PROPERTY_WRITE
                                       );
  pCharacteristic->setValue("Hello world");
  pService->start();
  BLEAdvertising *pAdvertising = BLEDevice::getAdvertising();
  pAdvertising->addServiceUUID(SERVICE_UUID);
  pAdvertising->setScanResponse(true);
  pAdvertising->setMinPreferred(0x06);  // functions that help with iPhone connections issue
  pAdvertising->setMinPreferred(0x12);
  BLEDevice::startAdvertising();
  
}

void loop() {
  client.loop();
  // BLEScanResults* foundDevices = pBLEScan->start(scanTime, false);
  // Serial.print("Devices found: ");
  // Serial.println(foundDevices.getCount());
  // Serial.println("Scan done!");
  // pBLEScan->clearResults();
  delay(1000);
}

void onMessageReceived(const char* topic, byte* payload, unsigned int length) {
  Serial.print("Received message on topic: ");
  // Serial.println(topic);
  String message = "";
  for (int i = 0; i < length; i++) {
    message += (char)payload[i];
  }
  Serial.println(message);
  pCharacteristic->setValue(message);
}
