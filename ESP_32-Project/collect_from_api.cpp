#include "utils.h"
#include <HTTPClient.h>


DynamicJsonDocument getDataFromAPI(String apiUrl) {
  HTTPClient http;

  Serial.print("[HTTP] begin...\n");

  // Specify content type header
  http.begin(apiUrl);

  int httpCode = http.GET();  // Make the request

  // Check for a successful request
  if (httpCode == HTTP_CODE_OK) {
    String payload = http.getString();  // Get the response payload

    // Parse JSON
    DynamicJsonDocument doc(1024);  // Adjust the size based on your JSON response
    DeserializationError error = deserializeJson(doc, payload);

    // Check for JSON parsing errors
    if (error) {
      Serial.print(F("JSON parsing failed! Error code: "));
      Serial.println(error.c_str());
    } else {
        return doc;
    }
  } else {
    Serial.printf("[HTTP] GET request failed, error code: %d\n", httpCode);
  }

  http.end();  // Free resources
}

