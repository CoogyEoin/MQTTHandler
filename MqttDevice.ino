#include "MQTTHandler.h"
#include "DataHandler.h"

char* mqtt_server = "broker.mqttdashboard.com";
char* mqtt_uplink_topic = "grianity/mqtt/uplink/ireland/dublin/dun_laoghaire";
char* mqtt_downlink_topic = "grianity/mqtt/downlink/ireland/dublin/1";

int inputPin = 5;
int outputPin = 7;

//Objects
MQTTHandler MQTTClient(mqtt_server,mqtt_uplink_topic,mqtt_downlink_topic);
DataHandler DataClient(inputPin, outputPin);


//Callback function for MQTT connection
void mqttCallback(char* topic, byte* payload, unsigned int length){
  Serial.print("Message arrived [");
    Serial.print(topic);
    Serial.print("] ");
    for (int i = 0; i < length; i++) {
        Serial.print((char)payload[i]);
    }

  if((char)payload[0] == '1'){
    digitalWrite(outputPin, HIGH);
  }
    
}


void setup() {
  Serial.begin(115200);
  MQTTClient.setupWiFi();
  MQTTClient.setupMQTT(&mqttCallback);
}

void loop() {

  MQTTClient.checkPubSubConnection();

  //Used to maintain connection to client and poll messages
  MQTTClient.maintainPubSubConnection();

  //Publish Message every 3 seconds
  delay(3000);
  char* msg = DataClient.getMessage();
  MQTTClient.publishToMQTT(msg);
 
}
