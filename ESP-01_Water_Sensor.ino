#include <PubSubClient.h>
#include <ESP8266WiFi.h>
#include <ESP8266mDNS.h>
ADC_MODE(ADC_VCC);

//USER CONFIGURED SECTION START//
const char* ssid = "YourWiFiName";
const char* password = "YourWiFiPassword";
const char* mqtt_server = "MQTT address";
const int mqtt_port = 1883; //MQTT port
const char* mqtt_user = "mqtt-user";
const char* mqtt_pass = "mqtt-password";
const char* mqtt_client_name = "watersensor1"; //Client connections cant have the same connection name. Use like: watersensor1, watersensor2 etc.
const char* mqtt_topic = "alarm/water/1/status"; //Topic has to be unique. Use like: alarm/water/1/status, alarm/water/2/status etc.

//I could not get static IP to work, therefore the following 3 lines are commented out.
//IPAddress ip(192, 168, 1, 10); 
//IPAddress gateway(192, 168, 1, 1); 
//IPAddress subnet(255, 255, 255, 0);
//USER CONFIGURED SECTION END//

WiFiClient espClient;
PubSubClient client(espClient);

// Variables
bool boot = true;
char batteryVoltageMQTT[50];

//Functions
void setup_wifi() 
{
// Static IP did not work, therefore the following like was commented out
//  WiFi.config(ip, gateway, subnet);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) 
    {
      delay(50);
    }
}

void reconnect() 
{
  while (!client.connected()) 
  {
      int battery_Voltage = ESP.getVcc() + 600;
      String temp_str = String(battery_Voltage);
      String mqttString = temp_str + "mV Replace Battery";
      mqttString.toCharArray(batteryVoltageMQTT, mqttString.length() + 1);
      if (battery_Voltage <= 2900)
      {
        if (client.connect(mqtt_client_name, mqtt_user, mqtt_pass, mqtt_topic, 0, 1, batteryVoltageMQTT)) 
        {
        
          if(boot == true)
          {
            client.publish(mqtt_topic,"on");
            boot = false;
          }
        } 
        else 
        {
          ESP.restart();
        }
      }
      if (battery_Voltage > 2900)
      {
        if (client.connect(mqtt_client_name, mqtt_user, mqtt_pass, mqtt_topic, 0, 1, "off"))
        {
          if(boot == true)
          {
            client.publish(mqtt_topic,"on");
            boot = false;
          }
        } 
        else 
        {
          ESP.restart();
        }
      }
  }
}

void setup() 
{
  setup_wifi();
  client.setServer(mqtt_server, mqtt_port);
}

void loop() 
{
  
  if (boot == true) 
  {
    reconnect();
  }
  else
  {
    ESP.deepSleep(0);
  }
}


