#ifndef UTILS_H
#define UTILS_H

#include "ArduinoJson.h"

extern char timeHour[3];
extern char timeMin[3];
extern char timeSec[3];
extern char day[3];
extern char month[6];
extern char year[5];
// extern char timeWeekDay[10];

extern const char* apiUrl;

void printLocalTime();

DynamicJsonDocument getDataFromAPI();
const char* getWindDirectionLetter();

#endif 