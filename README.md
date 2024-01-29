# Project Idea

A system that allows web applications to send data to a Bluetooth Low Energy (BLE) server via the MQTT protocol. The BLE server then broadcasts the data to other BLE devices in the vicinity. These devices can then receive and act upon the data according to their specific requirements.

# Description

The system will consist of three main components:

- A web application that can send data to the BLE server.
- A BLE server that receives data from the web application and broadcasts it to other BLE devices.
- BLE devices that can receive data from the BLE server and act upon it.

The web application will use the MQTT protocol to connect to the BLE server. It will then send data to the BLE server with a specific service ID and characteristic. The BLE server will listen for messages on this topic and broadcast the data to other BLE devices that are interested in it.

The BLE devices will use Bluetooth Low Energy to scan for nearby BLE servers. When they find one, they will connect to it and subscribe to the topic that the web application is sending data to. Once they receive data from the BLE server, they can act upon it accordingly.

# Objectives

- To develop a system that allows web applications to send data to BLE devices over a local network.
- To implement the MQTT protocol for communication between the web application and the BLE server.
- To design a BLE server that can receive data from the web application and broadcast it to other BLE devices.
- To implement a mechanism for BLE devices to subscribe to topics and receive data from the BLE server.

# Use Cases

This system could be used for a variety of applications, such as:

- Smart home automation: The web application could be used to control lights, thermostats, and other devices in the home. The BLE server could then broadcast the commands to other BLE devices in the home, so that they can execute them.
- Industrial automation: The web application could be used to monitor the state of industrial equipment. The BLE server could then broadcast the data to other BLE devices, so that they can take corrective actions if necessary.
- Healthcare: The web application could be used to collect data from patients, such as their heart rate, blood pressure, and glucose levels. The BLE server could then broadcast the data to other BLE devices, so that they can be monitored remotely.


# Requirements
1. Cloud VM instance for setup MQTT server
2. Two XIAO_ESP32C3 board (one for BLE server and one for BLE receiver)
Note: The second device fot BLE receiver is optional, you can use a mobile device instead. Follow the instructions accordingly to you preference.



# Instructions

## Setup MQTT server
You can setup your own cloud MQTT server or you can use pre configured server with IP and Port

1. Login to your cloud VM instance via ssh


2. Run the below commands to install mosquitto
```
sudo apt update
sudo apt install mosquitto mosquitto-clients
```

3. Once the installation is complete start the mosquitto server
```
sudo systemctl start mosquitto
```

4. By default the mosquitto port will be 1883. Make sure the port 1883 is open for incoming connection. You can change the port opening this config file. 
```
sudo nano /etc/mosquitto/conf.d/default.conf
```

> If you have changed the port after restart the mqtt server and make sure your new port is open and this port will be required in `MQTT_BLE_SERVER.ino` file and `main.py` file.







# Install and Setup Arduino
1. Install the Arduino IDE. If you don't already have the Arduino IDE installed, download and install it from the official website.

2. In your Arduino IDE, go to `File> Preferences`.
3. Enter this link `https://raw.githubusercontent.com/espressif/arduino-esp32/gh-pages/package_esp32_index.json` into the `Additional Board Manager URLs` field:

> Note: if you already have the ESP8266 boards URL, you can separate the URLs with a comma as follows:
> `https://raw.githubusercontent.com/espressif/arduino-esp32/gh-pages/package_esp32_index.json, http://arduino.esp8266.com/stable/package_esp8266com_index.json`

4. Open the Boards Manager. Go to `Tools > Board > Boards Manager`.
5. Search for `ESP32` and press install button for the `ESP32 by Espressif Systems`
6. That’s it. It should be installed after a few seconds.



# Deploy BLE Server
## Prerequisites

- XIAO_ESP32C3 board
- Micro USB cable
- Computer with Arduino IDE installed


1. Connect the XIAO_ESP32C3 board to your computer using a micro USB cable. The board should be powered on and the green LED should be lit.
2. Select the `XIAO_ESP32C3` board
3. In the Arduino IDE, go to `Tools > Board` and select `XIAO ESP32C3`.
4. In the Arduino IDE, go to `File > Open` and then select the `MQTT_BLE_SERVER.ino` file and click `Open`.

5. Change `WIFI SSID`, `Password`, `MQTT server`, `PORT` in line 14 to 16. If you have setup your own cloud mqtt server replace update mqtt_server with your own cloud server ip and replace port `1886` to your own port in the line 50.
```  
const char* ssid = "panoulu";   // Replace with your WiFi network SSID
const char* password = "q1ghost567";   // Replace with your WiFi network password
const char* mqtt_server = "16.170.238.248";  // Replace with your MQTT server address
```
replace port `1886` to your own port in the line 50
```
client.setServer(mqtt_server, 1886);
```

> Note: If you are using an open wifi network change line 39   
```
WiFi.begin(ssid,password); to WiFi.begin(ssid);
```

If you are using our pre configured mqtt server you don't need to change the `mqtt_server` in line 16 and in line 50.


6. Click the `Upload` button. The firmware will be uploaded to the XIAO_ESP32C3 board. After upload is complete reboot the device.
7. Open serial monitor and check if its connected to `WIFI MQTT` server. If you see the message in serial monitor `Connected to MQTT server` that means everything has been configured accordingly. If it doesn't shows this message recheck the steps and double check the your wifi credentials and mqtt server and port.


# Deploy BLE Receiver
## Prerequisites:
    XIAO_ESP32C3 board
    Micro USB cable
    Computer with Arduino IDE installed

1. Connect the `XIAO_ESP32C3` board to your computer using a micro USB cable. The board should be powered on and the green LED should be lit.
2. Select the `XIAO_ESP32C3` board
3. In the Arduino IDE, go to `Tools > Board` and select `XIAO ESP32C3`.
4. In the Arduino IDE, go to `File > Open` and then select the `BLE_CLIENT.ino` file and click `Open`.
5. Click the `Upload` button. The firmware will be uploaded to the XIAO_ESP32C3 board.
6. Once the firmware is uploaded to the board reboot the board and open up `Serial Monitor` from `TOOLS > Serial Monitor` and keep it open. The transmitted message will be shown here.



# Prepare Web Application
This code should be running in your laptop or desktop. You will require `python 3.9` and virtualenv to run the project.

### 1. Create virtualenv
```
python -m venv venv
```

### 3. Install requirements
```
pip install -r requirements.txt
```

### 4. Modify Script for server and portin line 6,7 
```
broker_address = "16.170.238.248"
broker_port = 1886
```

> Note: If you are using our pre configured mqtt server you don't need to change the broker_address in line 6 and broker_port in line 7.

### 5. Run Application
```
python main.py
```

After the application has been run it should tranmit 100 message to BLE server


# Observe:








