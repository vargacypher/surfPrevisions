#include "surf.h"
#include "utils.h"

#include "TFT_eSPI.h"
#include <WiFi.h>


TFT_eSPI lcd = TFT_eSPI();
TFT_eSprite sprite = TFT_eSprite(&lcd);
TFT_eSprite spr = TFT_eSprite(&lcd); //sprite for seconds
TFT_eSprite spr2 = TFT_eSprite(&lcd); //sprite for calendar
TFT_eSprite spr3 = TFT_eSprite(&lcd); //sprite for waves
TFT_eSprite cal = TFT_eSprite(&lcd);

const char* ssid     = "";
const char* password = "";

const char* ntpServer = "pool.ntp.org";
const long  gmtOffset_sec = -3 * 3600;             //time zone * 3600 , my time zone is  -3 GTM
const int   daylightOffset_sec = 3600;   

const char* apiUrl = "https://raw.githubusercontent.com/vargacypher/surfPrevisions/refs/heads/master/barrinha.json";

#define gray 0x6B6D
#define blue 0x0AAD
#define orange 0xC260
#define purple 0x604D
#define green 0x1AE9



void setup(void){    


  lcd.init();
  lcd.setRotation(1);
  sprite.createSprite(320, 170);
  sprite.setSwapBytes(true);
  sprite.setTextColor(TFT_WHITE,0xEAA9);
  sprite.setTextDatum(4);

  cal.createSprite(218,31);
  cal.fillSprite(TFT_GREEN);
  cal.setTextColor(TFT_WHITE,TFT_GREEN);
  //cal.setFreeFont(&Orbitron_Light_24);


  spr.createSprite(120,250);
  spr.fillSprite(TFT_GREEN);
  spr2.createSprite(100,100);
  spr2.setSwapBytes(true);
  spr2.fillSprite(TFT_GREEN);
  spr2.setTextDatum(4);
  spr.setTextColor(TFT_WHITE,TFT_GREEN);
  spr2.setTextColor(TFT_WHITE,TFT_GREEN);
  spr.setFreeFont(&Orbitron_Light_32);
  spr2.setFreeFont(&Orbitron_Light_24);
  

  spr3.createSprite(120,250);
  spr3.fillSprite(TFT_GREEN);
  spr3.setTextColor(TFT_WHITE,TFT_GREEN);
  spr3.setFreeFont(&Orbitron_Light_24);


  lcd.fillScreen(TFT_BLACK);
  
  Serial.begin(9600);
  lcd.print("Connecting to ");
  lcd.println(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
  delay(500);
  lcd.print(".");
  Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected.");

  configTime(gmtOffset_sec, daylightOffset_sec, ntpServer);

  fetchData(apiUrl);
  Serial.println("Data fetched");

  printLocalTime();

}

int temp=0;
int x=0;
long t=0;
int xt=230;
int yt=8;
static unsigned long lastFetchTime = 0;
unsigned long currentTime = millis();

void loop(){  
  if (currentTime - lastFetchTime >= 3600000 && WiFi.status() == WL_CONNECTED)  { // 60 minutes
    fetchData(apiUrl);
    lastFetchTime = currentTime;
  }

  spr.fillSprite(TFT_GREEN);
  spr2.fillSprite(TFT_GREEN);
  spr3.fillSprite(TFT_GREEN);
  spr2.setFreeFont(&Orbitron_Light_24);
  sprite.pushImage(0,0,aniWidth,aniHeigth,logo2[x]);
  delay(80);

  //clock - date
  sprite.setTextColor(purple,TFT_WHITE);
  sprite.fillRoundRect(234,3,65,26,3,TFT_WHITE);
  sprite.drawString(String(timeHour)+":"+String(timeMin),xt+36,yt+3,2);
  sprite.drawString(String(day)+"/"+String(month),265,23,1);
  
  //Temp and Windy
  sprite.setTextColor(TFT_BLACK);
  sprite.drawString(String(general_temp)+"°C",40,150,2);
  sprite.setTextColor(TFT_WHITE);
  sprite.drawString(getWindDirectionLetter(wind_direction),173,118,2);
  sprite.drawString(String(wind_speed)+"km/h",170,165,1);


  // Tides
  spr.drawString("Pico de Mares",8,5,2);
    // High tids
  spr.drawString(String(max_tideshigh)+"m/"+String(timestamp_max_tideshigh)+"h",0,56,2);
    // low tids
  spr.drawString(String(min_tideslow)+"m/"+String(timestamp_min_tideslow)+"h",59,56,2);

  //Waves
  spr3.drawString(String("Swell e Periodo"),12,35,2);
  spr3.drawString(String(surf_waves_max)+"/"+String("15")+"h",8,75,2);
  spr3.drawString("-",73,75,2);
  spr3.drawString(String("10")+"s",85,75,2);

  //Main title
  cal.drawRoundRect(0,0,150,28,4,TFT_WHITE);
  cal.setTextSize(2);
  cal.drawString("Surf Predict",20,4);
 

  cal.pushToSprite(&sprite,xt-224,yt,TFT_GREEN);
  spr.pushToSprite(&sprite,192,yt+16+6,TFT_GREEN);
  spr2.pushToSprite(&sprite,217,55,TFT_GREEN);
  spr3.pushToSprite(&sprite,195,yt+60+6,TFT_GREEN);
  sprite.pushSprite(0,0);

  //Update clock
  if(t+1000<millis()){
  printLocalTime();
  t=millis();
  }

  x++;
  if(x==framesNumber)
  x=0;
  
}
