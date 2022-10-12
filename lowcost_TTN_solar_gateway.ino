/*****************************************************
 * Date: september 2021
 * Written by: McOrts
 * 
 * ***************************************************/
#include <ESP8266WiFi.h>
#include <PubSubClient.h>

#include "settings.h"

long lastMsg = 0;

/* Meassure configuration */
int BAT= A0;              //Analog channel A0 as used to measure battery voltage
float RatioFactor=3.73;  //Resistors Ration Factor

/* Configuración cliente WiFi */
WiFiClient espClient;

/* Configuración MQTT */
PubSubClient clientMqtt(espClient);
char msg[50];
String mqttcommand = String(14);

void setup() {
  Serial.begin(9600);

  /* Iniciar wifi */
  setup_wifi();
  clientMqtt.setServer(mqtt_server, mqtt_port);
  clientMqtt.setCallback(callback);
}

void setup_wifi() {
  delay(10);

  // Comienza el proceso de conexión a la red WiFi
  Serial.println();
  Serial.print("[WIFI]Conectando a ");
  Serial.println(ssid);

  // Modo estación
  WiFi.mode(WIFI_STA);
  // Inicio WiFi
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("[WIFI]WiFi conectada");
  Serial.print("[WIFI]IP: ");
  Serial.print(WiFi.localIP());
  Serial.println("");
}

void callback(char* topic, byte* payload, unsigned int length) {
  Serial.print("[MQTT]Mensaje recibido (");
  Serial.print(topic);
  Serial.print(") ");
  mqttcommand = "";
  for (int i = 0; i < length; i++) {
    mqttcommand += (char)payload[i];
  }
  Serial.print(mqttcommand);
  Serial.println();
  // Switch on the LED if an 1 was received as first character
  if (mqttcommand == "comando") {
    Serial.println("comando");
  }  
}

void reconnect() {
  Serial.print("[MQTT]Intentando conectar a servidor MQTT... ");
  // Bucle hasta conseguir conexión
  while (!clientMqtt.connected()) {
    Serial.print(".");
    // Intento de conexión
    if (clientMqtt.connect(mqtt_id, mqttUser, mqttPassword )) { // Ojo, para más de un dispositivo cambiar el nombre para evitar conflicto
      Serial.println("");
      Serial.println("[MQTT]Conectado al servidor MQTT");
      // Once connected, publish an announcement...
      clientMqtt.publish(mqtt_sub_topic_healthcheck, "starting");
      // ... and subscribe
      clientMqtt.subscribe(mqtt_sub_topic_operation);
    } else {
      Serial.print("[MQTT]Error, rc=");
      Serial.print(clientMqtt.state());
      Serial.println("[MQTT]Intentando conexión en 5 segundos");

      delay(5000);
    }
  }
}

void loop() {
  if (!clientMqtt.connected()) {
    reconnect();
  }
  clientMqtt.loop();

  long now_sensors = millis();
  if (now_sensors - lastMsg > update_time_sensors) {
    lastMsg = now_sensors;
  
    int value = LOW;
    float Tvoltage=0.0;
    float Vvalue=0.0,Rvalue=0.0;
    
    /////////////////////////////////////Battery Voltage//////////////////////////////////  
    for(unsigned int i=0;i<10;i++){
      Vvalue=Vvalue+analogRead(BAT);         //Read analog Voltage
      delay(5);                              //ADC stable 
    }
    Vvalue=(float)Vvalue/10.0;            //Find average of 10 values
    Rvalue=(float)(Vvalue/1024.0)*5;      //Convert Voltage in 5v factor
    Serial.print("Voltage measured: ");
    Serial.print(Rvalue);
    Serial.println(" V");
    
    Tvoltage=Rvalue*RatioFactor;          //Find original voltage by multiplying with factor
    
    // Send voltage value throught MQTT
    Serial.print("Voltage: ");
    Serial.print(Tvoltage);
    Serial.println(" V");
    snprintf (msg, 6, "%2.1f", Tvoltage);
    Serial.print("[MQTT] Sending data: ");
    Serial.println(msg);
    clientMqtt.publish(mqtt_pub_topic_voltage, msg);
  }

}
