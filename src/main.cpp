#include <WiFi.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>

// Replace with your network credentials
const char* ssid = "F11Pro";
const char* password = "1144114411";

// Replace with your server's URL
const char* serverUrl = "Url + / + .json";

void setup() {
  Serial.begin(115200);
  
  // Connect to Wi-Fi
  WiFi.begin(ssid, password);
  Serial.print("Connecting to WiFi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print(".");
  }
  Serial.println("\nConnected to WiFi");

  // Fetch JSON data
  if ((WiFi.status() == WL_CONNECTED)) {
    HTTPClient http;

    http.begin(serverUrl);  // Specify the URL
    int httpCode = http.GET();  // Make the request

    if (httpCode > 0) {  // Check for the returning code
      String payload = http.getString();
      Serial.println(payload);

      // Parse JSON
      StaticJsonDocument<200> doc;
      DeserializationError error = deserializeJson(doc, payload);

      if (error) {
        Serial.print("deserializeJson() failed: ");
        Serial.println(error.f_str());
        return;
      }

      // Example of accessing a value in JSON
      const char* exampleValue = doc["example_key"];
      Serial.println(exampleValue);
    } else {
      Serial.println("Error on HTTP request");
    }

    http.end();  // Free the resources
  }
}

void loop() {
  // Do nothing here...
}
