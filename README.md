# ESP32-S3 Display Project (surfPrevisions) - WIP

![image](https://github.com/user-attachments/assets/65fc37f3-13db-456b-b80d-029f78a890b0)

**requeriments**: 
- USB-C Cable OTG
- Lilygo T-DISPAY-S3 Board

## SETUP PROJECT
1. Install [Arduino IDE](https://www.arduino.cc/en/software)
2. In Arduino Preferences, on the Settings tab, enter the `https://raw.githubusercontent.com/espressif/arduino-esp32/gh-pages/package_esp32_index.json` URL in the `Additional boards manager URLs` input box.
3. Download Espressif Boards Manager Version **esp-32** <= 2.0.11   (https://forum.arduino.cc/t/esp32-s3-sudden-compile-error/1177237/22) / (https://github.com/Bodmer/TFT_eSPI/issues/3329)
4. Download [T-Display-S3](https://github.com/Xinyuan-LilyGO/T-Display-S3) , move to Arduino library folder (e.g. C:\Users\YourName\Documents\Arduino\libraries) 
5. Copy TFT-eSPI to Arduino library folder (e.g. C:\Users\YourName\Documents\Arduino\libraries)
6. Open ArduinoIDE ,`Tools` ，Make your selection according to the table below
    | Arduino IDE Setting                  | Value                             |
    | ------------------------------------ | --------------------------------- |
    | Board                                | **ESP32S3 Dev Module** OR         |
    |                                      | **LilyGo T-Display-S3**           |
    | Port                                 | Your port                         |
    | USB CDC On Boot                      | Enable                            |
    | CPU Frequency                        | 240MHZ(WiFi)                      |
    | Core Debug Level                     | None                              |
    | USB DFU On Boot                      | Disable                           |
    | Erase All Flash Before Sketch Upload | Disable                           |
    | Events Run On                        | Core1                             |
    | Flash Mode                           | QIO 80MHZ                         |
    | Flash Size                           | **16MB(128Mb)**                   |
    | Arduino Runs On                      | Core1                             |
    | USB Firmware MSC On Boot             | Disable                           |
    | Partition Scheme                     | **16M Flash(3M APP/9.9MB FATFS)** |
    | PSRAM                                | **OPI PSRAM**                     |
    | Upload Mode                          | **UART0/Hardware CDC**            |
    | Upload Speed                         | 921600                            |
    | USB Mode                             | **CDC and JTAG**                  |
    * The options in bold are required, others are selected according to actual conditions.

8. Turn-on the Board pressing **boot** button


## DATA GENERATE EVERY HOUR WITH GITHUB ACTIONS / STOPPED
barrinha.json


