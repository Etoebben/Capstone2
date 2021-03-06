/*
  Capstone Project
  A-Team

  Balanced Breaker Box Sensor Array Controller
*/

/* NOTE
 * client.subscribe(MQTT_SERIAL_RECEIVER_CH) used to subsctibe to a mqtt 
 * channelclient.publish(MQTT_SERIAL_PUBLISH_CH, MESSAGE) used to publish message to data 
*/

#include <WiFi.h>
#include <PubSubClient.h>

//Device Info
#define DEVICE_NAME "Box Sensor V0.1"
#define DEVICE_ID "bs00120350" 

//Size of buffer
#define BUFFER_SIZE 20

//Declaring Pins **temp pin numbers currently**
#define MUX0_PIN_S0 0 //out put pin 0 for mux0
#define MUX0_PIN_S1 1 //out put pin 1 for mux0
#define MUX0_PIN_S2 2 //out put pin 2 for mux0
#define MUX0_SIG_PIN 3 //pin signal is read from mux0
#define MUX1_PIN_S0 4 //out put pin 0 for mux1
#define MUX1_PIN_S1 5 //out put pin 1 for mux1
#define MUX1_PIN_S2 6 //out put pin 2 for mux1
#define MUX1_SIG_PIN 7//pin signal is read from mux1

//WiFi Connection
#define ssid "Apt 109"
#define password "kamiy9ce1e"

//Mqtt Connection
#define mqttServer "hairdresser.cloudmqtt.com"
#define mqttPort 17102
#define mqttUser "mqtsqrfd"
#define mqttPassword "qWsfSyHmt1D-"

/* Mqtt Communication
 * transmiting channel /{DEVICE_ID}
 * receiveing channel /{DEVICE_ID}/ping 
*/
char* mqttTransmitChannel;
char* mqttReceiveChannel;

//Buffer for storing data. May not need
short buff[BUFFER_SIZE];

WiFiClient wifiClient;
PubSubClient client(wifiClient);

/*
  Connects Controller to WiFi
*/
void setup_wifi(){
  delay(10);
  Serial.print("\nConnecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  while(WiFi.status() != WL_CONNECTED){
    delay(500);
    Serial.print(".");
  }
  randomSeed(micros());
  Serial.print("\nWifi Connected\nIp address: ");
  Serial.println(WiFi.localIP());
}

void reconnect(){
  while(!client.connected()){
    Serial.print("Attempting to connect to MQTT...");
    String clientId = DEVICE_ID;
    if(client.connect(clientId.c_str(), mqttUser, mqttPassword)){
      Serial.println("Connected");
      client.publish(mqttConnectedChannel, "Connected");
      client.subscribe(mqttReceiveChannel);
    }
    else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      // Wait 5 seconds before retrying
      delay(5000);
    }
  }
}

void callback(char* topic, byte *payload, unsigned int length) {
    Serial.println("-------new message from broker-----");
    Serial.print("channel:");
    Serial.println(topic);
    Serial.print("data:"); 
    Serial.write(payload, length);
    Serial.println();
}

void resetBuffer(){
  for(int i = 0; i < BUFFER_SIZE; i++){
    buff[i] = 0;
  }
}

void setup(){
  mqttTransmitChannel = strcat("/", DEVICE_ID);
  mqttReceiveChannel = strcat("/", strcat(DEVICE_ID, "/ping"));
  Serial.begin(115200);
  Serial.setTimeout(500);
  resetBuffer();
  setup_wifi();
  client.setServer(mqttServer, mqttPort);
  client.setCallback(callback);
  reconnect();
}

void loop(){
  client.loop();
  
  for(int i = 0; i < BUFFER_SIZE; i++){
    if(i == 0){
      //set timestamp
    }
    //set serial pins
    //store sensor data into buff[i] (May be able to skip and save memory)
    //delay(50)
  }

  //send timestamp and buffer to server
  //resetBuffer
  
}
