#ifndef MQTTHandler_h
#define MQTTHandler_h

#include "Arduino.h"
#include <ESP8266WebServer.h>
#include <DNSServer.h>    
#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include <WiFiManager.h>


/*
MQTTHandler:
This class is used for configuring the Wi-Fi and MQTT
connection for a main Arduino script.
*/
class MQTTHandler{
	public:
		//Used for simple WiFi configuration
		MQTTHandler();
		
		//Used for MQTT configuration
		MQTTHandler(char* MqttServer, char* MqttUplinkTopic, char* MqttDownlinkTopic);
		~MQTTHandler();
		void publishToMQTT(char* mqttMessage);		
		void maintainPubSubConnection();
		void checkPubSubConnection();
		void setupMQTT(void(*callbackFunction)(char*, unsigned char*, unsigned int));
		void setupWiFi();
	private:
		char* theMqttServer;
		char* theMqttUplinkTopic;
		char* theMqttDownlinkTopic;
		void reconnect();

		//The clients and objects used to establish connections
		WiFiClient* theWiFiClient;
		PubSubClient* thePubSubClient;
		WiFiManager* theWiFiManager;

};

#endif
