#include "surf.h"
#include "utils.h"

#include "TFT_eSPI.h"
#include <WiFi.h>


TFT_eSPI lcd = TFT_eSPI();
TFT_eSprite sprite = TFT_eSprite(&lcd);
TFT_eSprite spr = TFT_eSprite(&lcd); //sprite for seconds
TFT_eSprite spr2 = TFT_eSprite(&lcd); //sprite for calendar
TFT_eSprite cal = TFT_eSprite(&lcd);

const char* ssid     = "dasdasdasdasdasd-NW";
const char* password = "dasdsadfdgf32432afhg";

const char* ntpServer = "pool.ntp.org";
const long  gmtOffset_sec = -3 * 3600;             //time zone * 3600 , my time zone is  +1 GTM
const int   daylightOffset_sec = 3600;   

String apiUrl = "https://raw.githubusercontent.com/vargacypher/surfPrevisions/master/barrinha.json";

#define gray 0x6B6D
#define blue 0x0AAD
#define orange 0xC260
#define purple 0x604D
#define green 0x1AE9

String IP;


// int left=0;
// int right=14;

void setup(void)
{    

    // pinMode(left,INPUT_PULLUP);
    // pinMode(right,INPUT_PULLUP);
    lcd.init();
    lcd.setRotation(1);
    sprite.createSprite(320, 170);
    sprite.setSwapBytes(true);
    sprite.setTextColor(TFT_WHITE,0xEAA9);
    sprite.setTextDatum(4);

    cal.createSprite(218,31);
    cal.fillSprite(TFT_GREEN);
    cal.setTextColor(TFT_WHITE,TFT_GREEN);

    spr.createSprite(80,64);
    //spr.fillSprite(TFT_GREEN);
    spr2.createSprite(100,100);
    spr2.setSwapBytes(true);
    spr2.fillSprite(TFT_GREEN);
    spr2.setTextDatum(4);
    spr.setTextColor(TFT_WHITE,TFT_GREEN);
    spr2.setTextColor(TFT_WHITE,TFT_GREEN);
    spr.setFreeFont(&Orbitron_Light_32);
    spr2.setFreeFont(&Orbitron_Light_24);
    
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
   IP=WiFi.localIP().toString();

  configTime(gmtOffset_sec, daylightOffset_sec, ntpServer);

//   DynamicJsonDocument data = getDataFromAPI(apiUrl);
  
//   // Access data as needed
//   Serial.print("surf_waves_min: ");
//   Serial.println(data["surf_waves_min"].as<float>());

}

int temp=0;
int x=0;
long startF=0;
long endF=0;
double fps=0;

long t=0;
int xt=230;
int yt=8;


void loop()
{
  startF=millis();
  
  spr.fillSprite(TFT_GREEN);
  spr2.fillSprite(TFT_GREEN);
  spr2.setFreeFont(&Orbitron_Light_24);
  sprite.pushImage(0,0,aniWidth,aniHeigth,logo2[x]);
  delay(80);

  sprite.setTextColor(purple,TFT_WHITE);

  
  sprite.fillRoundRect(234,3,65,28,3,TFT_WHITE);
  sprite.drawString(String(timeHour)+":"+String(timeMin),xt+36,yt+5,2);
  sprite.drawString(String(day)+"/"+String(month),265,25,1);

  spr2.drawString("Pico de Mares",52,2,2);
  // High tids
  spr2.drawString(String("0.5")+"m",1,40,2);
  // low tids
  spr2.drawString(String("0.2")+"m",9,40,2);



  cal.drawRoundRect(0,0,150,28,4,TFT_WHITE);
  cal.drawString("Pvisao Ondas e Mares",7,4,2);
 


  cal.pushToSprite(&sprite,xt-224,yt,TFT_GREEN);
  //spr.pushToSprite(&sprite,xt,yt+70+16+6,TFT_GREEN);
  spr2.pushToSprite(&sprite,217,55,TFT_GREEN);
  sprite.pushSprite(0,0);


  if(t+1000<millis()){
  printLocalTime();
  t=millis();
  }

  x++;
  if(x==framesNumber)
  x=0;
  
  endF=millis();
  fps=1000/(endF-startF);
}

