// WiFi Configuration
const char* ssid = "4GUFI_6914";
const char* password = "Xxitt6969";

// MQTT Configuration
const char* mqtt_server = "domohome.ddns.jazztel.es";
const int mqtt_port = 1883;
const char* mqtt_id = "mcorts-rak7258-auto";
const char* mqtt_sub_topic_healthcheck = "/outdoors/mcorts-rak7258-auto";
const char* mqtt_pub_topic_voltage = "/outdoors/mcorts-rak7258-auto/voltage";
const char* mqtt_pub_topic_temperature = "/outdoors/mcorts-rak7258-auto/temperature";
const char* mqtt_pub_topic_humidity = "/outdoors/mcorts-rak7258-auto/humidity";
const char* mqtt_pub_topic_preassure = "/outdoors/mcorts-rak7258-auto/preassure";
const char* mqtt_sub_topic_operation = "/outdoors/mcorts-rak7258-auto/operation";


// Other params
const int update_time_sensors = 60000;