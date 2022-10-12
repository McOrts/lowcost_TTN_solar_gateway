// WiFi Configuration
const char* ssid = "4GUFI_6914";
const char* password = "??????";
//const char* ssid = "iot-anywhere.net";
//const char* password = "NoOlvides2";

// MQTT Configuration
const char* mqtt_server = "????";
const int   mqtt_port = 1188;
const char* mqttUser = "?????";
const char* mqttPassword = "?????";
const char* mqtt_id = "mcorts-rak7258-auto";
const char* mqtt_sub_topic_healthcheck = "/mcorts-rak7258-auto/alive";
const char* mqtt_pub_topic_voltage = "/mcorts-rak7258-auto/voltage";
const char* mqtt_pub_topic_temperature = "/mcorts-rak7258-auto/temperature";
const char* mqtt_pub_topic_humidity = "/mcorts-rak7258-auto/humidity";
const char* mqtt_pub_topic_preassure = "/mcorts-rak7258-auto/preassure";
const char* mqtt_sub_topic_operation = "/mcorts-rak7258-auto/operation";


// Other params
const int update_time_sensors = 600000;
