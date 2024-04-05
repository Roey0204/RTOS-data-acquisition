import paho.mqtt.client as mqtt
import paho.mqtt.publish as publish

class MQTTClient:
    def __init__(self, broker_address, broker_port):
        self.broker_address = broker_address
        self.broker_port = broker_port

        # Create MQTT client
        self.client = mqtt.Client()

        # Set callback function for subscriber
        self.client.on_message = self.on_message

        # Connect to broker
        self.client.connect(self.broker_address, self.broker_port)

    def on_message(self, client, userdata, message):
        print(f"Received message on topic '{message.topic}': {message.payload.decode()}")

    def subscribe(self, topic):
        # Subscribe to topic
        self.client.subscribe(topic)
        print(f"Subscribed to topic: {topic}")

    def publish(self, topic, message):
        # Publish message to topic
        publish.single(topic, message, hostname=self.broker_address, port=self.broker_port)
        print(f"Published message '{message}' to topic: {topic}")

    def loop_forever(self):
        # Loop to handle messages
        self.client.loop_forever()

# Example usage:
if __name__ == "__main__":
    broker_address = "test.mosquitto.org"
    broker_port = 1883
    topic = "esp32/dht"
    topic2 ="esp32/data"
    
    mqtt_client = MQTTClient(broker_address, broker_port)
    mqtt_client.subscribe(topic)
    
    # Uncomment the line below to publish a message
    # mqtt_client.publish(topic, "here is from python")
    
    mqtt_client.loop_forever()
