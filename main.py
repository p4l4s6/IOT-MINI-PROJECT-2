from time import sleep

import paho.mqtt.client as mqtt

# Define the MQTT broker address and port
broker_address = "16.170.238.248"
broker_port = 1886
topic = "ble_project_2"


def on_connect(cl, userdata, flags, rc):
    print("Connected with result code " + str(rc))


# Create a MQTT client instance


# Connect to the MQTT broker
def connect():
    cl = mqtt.Client()
    cl.on_connect = on_connect
    cl.connect(broker_address, broker_port)
    cl.loop()
    return cl


# Publish the message to the MQTT topic
def publish(cl, message):
    for i in range(0, 100):
        print(f"Sending message: {message} {i}")
        cl.publish(topic, f"{message} {i}", qos=1)
        sleep(5)


if __name__ == '__main__':
    client = connect()
    publish(client, "Hello from python")
