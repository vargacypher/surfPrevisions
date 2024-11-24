#ifndef UTILS_H
#define UTILS_H


#include <HTTPClient.h>
#include <ArduinoJson.h>


// Variables to store the parsed values of http request
extern float surf_waves_min;
extern float surf_waves_max;
extern int probability;
extern int wind_direction;
extern float wind_speed;
extern float general_temp;
extern float max_tideshigh;
extern String timestamp_max_tideshigh;
extern float min_tideslow;
extern String timestamp_min_tideslow;



extern char timeHour[3];
extern char timeMin[3];
extern char timeSec[3];
extern char day[3];
extern char month[6];
extern char year[5];
// extern char timeWeekDay[10];

// Function declarations
void fetchData(const char* apiUrl);
void printLocalTime();

const char* getWindDirectionLetter();

#endif