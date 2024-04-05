#include <Arduino.h>
#include <WiFi.h>
#include <PubSubClient.h>
#include "DHT.h"

// WiFi credentials
const char* ssid = "xx";
const char* password = "xx";

// MQTT broker
const char* mqtt_server = "test.mosquitto.org";
const int mqtt_port = 1883;

// MQTT topics
const char* mqtt_publish_topic = "esp32/dht";

// WiFi client
WiFiClient espClient;

// MQTT client
PubSubClient client(espClient);

#define DHTPIN 2     // Pin where the DHT11 is connected
#define DHTTYPE DHT11   // DHT 11

// Initialize DHT sensor
DHT dht(DHTPIN, DHTTYPE);

// Variables to hold sensor readings
float temp = 0;
float hum = 0;

// Task handles
TaskHandle_t wifiTaskHandle = NULL;
TaskHandle_t mqttTaskHandle = NULL;
TaskHandle_t sensorTaskHandle = NULL;

// Function prototypes
void wifiTask(void* parameter);
void mqttTask(void* parameter);
void sensorTask(void* parameter);

void setup() {
  Serial.begin(115200);
  dht.begin();
  xTaskCreatePinnedToCore(wifiTask, "WifiTask", 4096, NULL, 1, &wifiTaskHandle, 0);
  xTaskCreatePinnedToCore(mqttTask, "MqttTask", 4096, NULL, 1, &mqttTaskHandle, 1);
  xTaskCreatePinnedToCore(sensorTask, "SensorTask", 4096, NULL, 2, &sensorTaskHandle, 0);
}

void loop() {
  // Empty, everything is handled by tasks
}

void wifiTask(void* parameter) {
  Serial.println("Connecting to WiFi");
  WiFi.begin(ssid, password);
  
  while (WiFi.status() != WL_CONNECTED) {
    vTaskDelay(1000 / portTICK_PERIOD_MS);
    Serial.println("Connecting...");
  }
  
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());

  vTaskDelete(NULL);
}

void mqttTask(void* parameter) {
  Serial.println("Initializing MQTT");
  client.setServer(mqtt_server, mqtt_port);
  
  while (!client.connected()) {
    if (client.connect("esp32Client")) {
      Serial.println("Connected to MQTT broker");
    } else {
      Serial.print("MQTT connection failed, rc=");
      Serial.print(client.state());
      Serial.println(" Trying again in 5 seconds...");
      vTaskDelay(5000 / portTICK_PERIOD_MS);
    }
  }

  while (1) {
      char msg[50];
      snprintf(msg, 50, "Temperature: %.2f°C, Humidity: %.2f%%", temp, hum);
      client.publish(mqtt_publish_topic, msg);
      vTaskDelay(2000 / portTICK_PERIOD_MS); // Adjust delay as needed
  }
}

void sensorTask(void* parameter) {
  while (1) {
    // Read sensor data
    hum = dht.readHumidity();
    temp = dht.readTemperature();

    if (isnan(hum) || isnan(temp)) {
      Serial.println("Failed to read from DHT sensor!");
    } else {
      Serial.print("Temperature: ");
      Serial.print(temp);
      Serial.print("°C, Humidity: ");
      Serial.print(hum);
      Serial.println("%");
    }

    vTaskDelay(2000 / portTICK_PERIOD_MS); // Adjust delay as needed
  }
}
