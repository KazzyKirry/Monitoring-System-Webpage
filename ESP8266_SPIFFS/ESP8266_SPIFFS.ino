// Import required libraries
#include <ESP8266WiFi.h>
#include <ESPAsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include <FS.h>
#include <Wire.h>

// Replace with your network credentials
const char* ssid = "POCO X3 Pro";
const char* password = "zwtpxdhbycn5k7g";

// Create AsyncWebServer object on port 80
AsyncWebServer server(80);

/*String getTemperature() {
  float temperature = bme.readTemperature();
  // Read temperature as Fahrenheit (isFahrenheit = true)
  //float t = dht.readTemperature(true);
  Serial.println(temperature);
  return String(temperature);
}
  
String getHumidity() {
  float humidity = bme.readHumidity();
  Serial.println(humidity);
  return String(humidity);
}

String getPressure() {
  float pressure = bme.readPressure()/ 100.0F;
  Serial.println(pressure);
  return String(pressure);
}*/

String getvWater()
{
  int wvalue = analogRead(A0);
  Serial.print(wvalue);
  return String(wvalue);
}
 
void setup(){
  // Serial port for debugging purposes
  Serial.begin(115200);

  // Initialize SPIFFS
  if(!SPIFFS.begin()){
    Serial.println("An Error has occurred while mounting SPIFFS");
    return;
  }

  // Connect to Wi-Fi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi..");
  }

  // Print ESP32 Local IP Address
  Serial.println(WiFi.localIP());

  // Route for root / web page
  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send(SPIFFS, "/index.html");
  });

  server.on("/gauge.js", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send(SPIFFS, "/gauge.js");
  });

  server.on("/index.js", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send(SPIFFS, "/index.js");
  });
  
  // Route to load style.css file
  server.on("/styles.css", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send(SPIFFS, "/styles.css", "text/css");
  });

  server.on("/water", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send_P(200, "text/plain", getvWater().c_str());
  });

  // Start server
  server.begin();
}
 
void loop(){
  
}
