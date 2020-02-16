# MQTTHandler
A simple Arduino class written for the ESP8266 for automatically connecting to a MQTT broker that doesn't require hard-coding WiFi credentials.

This is a simple library that will allow a user to manually connect to a Wi-Fi router using the WiFiManager library for arduino. An access point will be created on an address in the local network for you to connect to. Wi-Fi details are saved using DNS so you only need to connect once.

For a simple Wi-Fi connection just use the MQTTHandler() instance without any arguments. Use the 
MQTTHandler(serverAddress, uplinkTopic, downlinkTopic) instance for the MQTT connection. An example can be found in the MQTTDevice.iso file.

***This was a simple weekend project I am not upkeeping dependancies/libraries***
