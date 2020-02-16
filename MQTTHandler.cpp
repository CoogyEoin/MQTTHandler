#include "Arduino.h"
#include <ESP8266WebServer.h>
#include <DNSServer.h>    
#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include <WiFiManager.h> 
#include "MQTTHandler.h"


MQTTHandler::MQTTHandler(){
	theWiFiClient = new WiFiClient;
	theWiFiManager = new WiFiManager;
}


MQTTHandler::MQTTHandler(char* MqttServer, char* MqttUplinkTopic, char* MqttDownlinkTopic){
	theMqttServer = MqttServer;
	theMqttUplinkTopic = MqttUplinkTopic;
	theMqttDownlinkTopic = MqttDownlinkTopic;

	//There might be a better way of using these objects
	//without declaring them as members
	theWiFiClient = new WiFiClient;
	thePubSubClient = new PubSubClient(*theWiFiClient);
	theWiFiManager = new WiFiManager;
}

MQTTHandler::~MQTTHandler(){
	delete(theWiFiClient);
	delete(thePubSubClient);
	delete(theWiFiManager);
}


void MQTTHandler::setupWiFi() {
  	//sets timeout until configuration portal gets turned off in seconds
  	theWiFiManager->setTimeout(120);
    
  	if (!theWiFiManager->autoConnect("GrianityWiFiHub")) {
    		Serial.println("failed to connect and hit timeout");
    		ESP.reset();
    		delay(5000);
  	}
  
  	//if you get here you have connected to the WiFi
  	Serial.println("connected to Wi-Fi");
}


void MQTTHandler::setupMQTT( void(*callbackFunction)(char*, unsigned char*, unsigned int)){
  	thePubSubClient->setServer(theMqttServer, 1883);
  	thePubSubClient->setCallback(callbackFunction);
}

void MQTTHandler::reconnect() {
	// Loop until we're reconnected
  	while (!thePubSubClient->connected()) {
    		Serial.print("Attempting MQTT connection...");
    		// Create a random client ID
    		String clientId = "ESP8266Client-";
    		clientId += String(random(0xffff), HEX);
    		// Attempt to connect
    			if (thePubSubClient->connect(clientId.c_str())) {
      				Serial.println("connected");
      				thePubSubClient->publish(theMqttUplinkTopic, "Connection Established");
      				thePubSubClient->subscribe(theMqttDownlinkTopic);
    			} else {
      				Serial.print("failed, rc=");
      				Serial.print(thePubSubClient->state());
      				Serial.println(" try again in 5 seconds");
      				// Wait 5 seconds before retrying
      				delay(5000);
    			}
  	}
}

void MQTTHandler::publishToMQTT(char* mqttMessage){
  	Serial.print("Publishing message: ");
  	Serial.println(mqttMessage);
  	thePubSubClient->publish(theMqttUplinkTopic, mqttMessage);
  
}

void MQTTHandler::checkPubSubConnection(){
	if(!thePubSubClient->connected()){
		reconnect();
	}
}

void MQTTHandler::maintainPubSubConnection(){
	thePubSubClient->loop();
}
