#include "utils.h"

// Variables to store the parsed values
float surf_waves_min;
float surf_waves_max;
int probability;
int wind_direction;
float wind_speed;
float general_temp;
float max_tideshigh;
String timestamp_max_tideshigh;
float min_tideslow;
String timestamp_min_tideslow;


void fetchData(const char* apiUrl) {
    HTTPClient http;
    http.begin(apiUrl);
    int httpResponseCode = http.GET();

    if (httpResponseCode > 0) {
      String payload = http.getString();
      Serial.println(payload);

      // Allocate the JSON document
      const size_t capacity = JSON_OBJECT_SIZE(11) + 300;
      DynamicJsonDocument doc(capacity);

      // Parse JSON object
      DeserializationError error = deserializeJson(doc, payload);
      if (error) {
        Serial.print(F("deserializeJson() failed: "));
        Serial.println(error.f_str());
        return;
      }

      // Extract values
      surf_waves_min = doc["surf_waves_min"];
      surf_waves_max = doc["surf_waves_max"];
      probability = doc["probability"];
      wind_direction = doc["wind_direction"];
      wind_speed = doc["wind_speed"];
      general_temp = doc["general_temp"];
      max_tideshigh = doc["max_tideshigh"];
      timestamp_max_tideshigh = String(doc["timestamp_max_tideshigh"].as<const char*>());
      min_tideslow = doc["min_tideslow"];
      timestamp_min_tideslow = String(doc["timestamp_min_tideslow"].as<const char*>());

    } else {
      Serial.print("Error on HTTP request: ");
      Serial.println(httpResponseCode);
    }
    http.end();
}
