#include <ESP8266WiFi.h>
#include <PubSubClient.h>

const char* ssid = "MCLEANS";
const char* password =  "agwaya234";

const char* mqttServer = "https://io.adafruit.com";
const int mqttPort = 1883;
const char* mqttUser = "jack_the_nerd";
const char* mqttPassword = "aio_RybB55PZpZzZb4mgsYrFpLRPhDTr";

WiFiClient espClient;
PubSubClient client(espClient);

void callback(char* topic, byte* payload, unsigned int length) {
 
  Serial.print("Message arrived in topic: ");
  Serial.println(topic);
 
  Serial.print("Message:");
  for (int i = 0; i < length; i++) {
    Serial.print((char)payload[i]);
  }
 
  Serial.println();
  Serial.println("-----------------------");
 
}

void setup() {
 
  Serial.begin(115200);
 
  WiFi.begin(ssid, password);
 
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.println("Connecting to WiFi..");
  }
  Serial.println("Connected to the WiFi network");
 
  client.setServer(mqttServer, mqttPort);
  client.setCallback(callback);
  String clientId = "ESP8266Client-";
  clientId += String(random(0xffff), HEX);
  while (!client.connected()) {
    Serial.println("Connecting to MQTT...");
 
    if (client.connect((clientId.c_str(),mqttUser,mqttPassword ))) {
 
      Serial.println("connected");  
 
    } else {
 
      Serial.print("failed with state ");
      Serial.print(client.state());
      delay(2000);
 
    }
  }
 
  client.publish("jack_the_nerd/feeds/switch-feed", "OFF");
  client.subscribe("jack_the_nerd/feeds/switch-feed");
 
}

void loop() {
  client.loop();
}
