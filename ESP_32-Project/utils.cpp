#include "utils.h"
#include "time.h"

char timeHour[3];
char timeMin[3];
char timeSec[3];
char day[3];
char month[6];
char year[5];
// char timeWeekDay[3];
// String dayInWeek;


void printLocalTime()
  {
  struct tm timeinfo;
  
  if(!getLocalTime(&timeinfo)){
    
    return;
  }
  
  strftime(timeHour,3, "%H", &timeinfo);
  strftime(timeMin,3, "%M", &timeinfo);
  strftime(timeSec,3, "%S", &timeinfo);

    
  // strftime(timeWeekDay,10, "%A", &timeinfo);
  // dayInWeek=String(timeWeekDay);

  
  strftime(day,3, "%d", &timeinfo);
  strftime(month,6, "%B", &timeinfo);
  strftime(year,5, "%Y", &timeinfo);

  }


const char* getWindDirectionLetter(float windDirection) {
    if ((windDirection >= 337.5 && windDirection <= 360) || (windDirection >= 0 && windDirection < 22.5)) {
        return "N";
    } else if (windDirection >= 22.5 && windDirection < 67.5) {
        return "NE";
    } else if (windDirection >= 67.5 && windDirection < 112.5) {
        return "E";
    } else if (windDirection >= 112.5 && windDirection < 157.5) {
        return "SE";
    } else if (windDirection >= 157.5 && windDirection < 202.5) {
        return "S";
    } else if (windDirection >= 202.5 && windDirection < 247.5) {
        return "SW";
    } else if (windDirection >= 247.5 && windDirection < 292.5) {
        return "W";
    } else if (windDirection >= 292.5 && windDirection < 337.5) {
        return "NW";
    } else {
        return "Invalid";
    }
}
