Project for IoT Security course (EE 5453).

Project makes use of MQTT protocol for secure communication of analog weight sensor data to be recorded on a database (InfluxDB).

<img src="https://github.com/miguelleonel/Portfolio/blob/main/%5BC%20(Arduino)%5D%20MQTT%20Communication%20with%20Arduino/Figures/Diagram.png?raw=true" width="800">

Diagram is a two part visual aid, where the the top is the incoming analog input, bottom is the dataflow after data retreival.
The analog sensor data is communicated wirelessly from the ESP8266 boards to the MQTT broker hosted on a Raspberry Pi.
The locally hosted MQTT broker, using Mosquitto, is then connected to Node-RED to be able to log the data to the InfluxDB database, and Grafana to easily visualize the data. 

Powerpoint presentation is uploaded in this directory, which better explains the overall project. 


Part 1 video presenting powerpoint (11 minutes). 
https://youtu.be/M4bxYHJGwyM

Part 2 video presenting a demo of the proof of concept, functionality of the MQTT communication (12 minutes).
https://youtu.be/zvRsn--bYKk
