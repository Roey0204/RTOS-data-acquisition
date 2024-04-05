# ESP32 DHT11 Sensor Data Publishing with MQTT and FreeRTOS
This project utilizes the ESP32 microcontroller, DHT11 temperature and humidity sensor, MQTT protocol, and FreeRTOS to enable concurrent operation of the WiFi module and sensor data acquisition. The main goal of the project is to implement a publish/subscribe (pub/sub) method using MQTT to publish the data acquired from the DHT11 sensor.

## Components Used:
### ESP32 Microcontroller: A powerful and versatile microcontroller with built-in WiFi capabilities.
### DHT11 Sensor: A low-cost digital sensor that measures temperature and humidity.
### MQTT Protocol: A lightweight messaging protocol designed for constrained devices and low-bandwidth, high-latency, or unreliable networks.
### FreeRTOS: A real-time operating system kernel for embedded systems that supports multitasking and time-sharing.

### Purpose:The purpose of this project is to demonstrate how to leverage the capabilities of the ESP32 microcontroller along with the DHT11 sensor to publish temperature and humidity data to an MQTT broker using the pub/sub method. By implementing FreeRTOS, we ensure that the WiFi module and sensor operate concurrently, maximizing efficiency and allowing for real-time data acquisition and communication.

## How It Works:
### WiFi Connection: The ESP32 connects to a WiFi network using the provided credentials (SSID and password).
### MQTT Initialization: The MQTT client is initialized with the broker's address and port.
### Sensor Data Acquisition: The DHT11 sensor continuously reads temperature and humidity data.
### Publishing Data: Once the sensor data is obtained, it is formatted into a message and published to a specific MQTT topic.
### Concurrent Operation: FreeRTOS is utilized to create separate tasks for WiFi connection handling, MQTT communication, and sensor data acquisition. This allows for concurrent execution of these tasks, ensuring that the WiFi module and sensor operate simultaneously without blocking each other.
### Python Module for Subscribing: A Python module is developed to subscribe to the MQTT topic published by the ESP32. This enables users to easily monitor the published data from the ESP32 on their PCs.

## Setup:
### Hardware Connections: Connect the DHT11 sensor to the ESP32 microcontroller according to the specified pin configuration.
### Software Setup: Upload the provided code to the ESP32 using the Arduino IDE or a compatible development environment.
### Configuration: Modify the code to include your WiFi credentials and adjust any other settings as necessary.
