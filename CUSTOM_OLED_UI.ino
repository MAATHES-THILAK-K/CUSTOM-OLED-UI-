#include<Wire.h>
#include<U8g2lib.h>
#include<WiFi.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>
#include <BluetoothSerial.h>
#include<Arduino.h>


U8G2_SH1106_128X64_NONAME_F_HW_I2C u8g2(U8G2_R0);


// 12x12 Square Bitmap


const uint8_t wifi_hider[] PROGMEM = {
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

const uint8_t square PROGMEM[] = {
  0xFF, 0xFF, 0x1F, // Row 1
  0xFF, 0xFF, 0x1F, // Row 2
  0xFF, 0xFF, 0x1F, // Row 3
  0xFF, 0xFF, 0x1F, // Row 4
  0xFF, 0xFF, 0x1F, // Row 5
  0xFF, 0xFF, 0x1F, // Row 6
  0xFF, 0xFF, 0x1F, // Row 7
  0xFF, 0xFF, 0x1F, // Row 8
  0xFF, 0xFF, 0x1F, // Row 9
  0xFF, 0xFF, 0x1F, // Row 10
  0xFF, 0xFF, 0x1F, // Row 11
  0xFF, 0xFF, 0x1F, // Row 12
  0xFF, 0xFF, 0x1F, // Row 13
  0xFF, 0xFF, 0x1F, // Row 14
  0xFF, 0xFF, 0x1F, // Row 15
  0xFF, 0xFF, 0x1F, // Row 16
  0xFF, 0xFF, 0x1F, // Row 17
  0xFF, 0xFF, 0x1F, // Row 18
  0xFF, 0xFF, 0x1F, // Row 19
  0xFF, 0xFF, 0x1F, // Row 20
  0xFF, 0xFF, 0x1F, // Row 21
  0xFF, 0xFF, 0x1F, // Row 22
  0xFF, 0xFF, 0x1F, // Row 23
};


const uint8_t pic_of_logo[] PROGMEM = {
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0xf0, 0xff, 0xff, 0x3f, 0x00, 0x00, 0x00, 0x00, 0xf0, 0xff, 0xff, 0x3f,
  0x00, 0x00, 0x00, 0x00, 0xf0, 0xff, 0xff, 0x3f, 0xe0, 0xff, 0xc0, 0x3f, 0xf0, 0xff, 0xff, 0x3f,
  0xf0, 0xff, 0xe1, 0x7f, 0xf0, 0x00, 0x00, 0x30, 0xf0, 0xff, 0xe1, 0xff, 0x70, 0x00, 0x00, 0x30,
  0xf0, 0xff, 0xf1, 0xff, 0x31, 0x00, 0x00, 0x30, 0xf0, 0xe0, 0xf9, 0xf0, 0x33, 0x00, 0x00, 0x30,
  0xf0, 0xe0, 0x79, 0xe0, 0x17, 0xf8, 0xe1, 0x33, 0xf0, 0xe0, 0x7d, 0xc0, 0x0f, 0xfc, 0xe1, 0x33,
  0x00, 0xe0, 0x3d, 0x84, 0x0f, 0xf6, 0xe1, 0x33, 0x00, 0xe0, 0x3f, 0x0c, 0x0f, 0xe3, 0xe1, 0x3f,
  0x00, 0xe0, 0x1f, 0x1c, 0x8e, 0xf1, 0xe1, 0x3f, 0x00, 0xe0, 0x1f, 0x38, 0xcc, 0xf8, 0xe1, 0x3f,
  0x00, 0xe0, 0x0f, 0x30, 0xe8, 0xfc, 0xe1, 0x3f, 0x00, 0xe0, 0x07, 0x20, 0xf0, 0xff, 0xe1, 0x3f,
  0x00, 0xe0, 0x07, 0x00, 0xf0, 0xff, 0xe1, 0x3f, 0x00, 0xe0, 0x0f, 0x00, 0xf0, 0xff, 0xe1, 0x3f,
  0x00, 0xe0, 0x1f, 0x00, 0xf0, 0xff, 0xe1, 0x3f, 0x00, 0xe0, 0x1f, 0x00, 0xf0, 0xff, 0xe1, 0x3f,
  0x00, 0xe0, 0x3c, 0x00, 0xf0, 0xff, 0xe1, 0x3f, 0x00, 0xe0, 0x7d, 0x00, 0xf0, 0xff, 0xe1, 0x3f,
  0x00, 0xe0, 0xf9, 0x00, 0xf0, 0xff, 0xe1, 0x3f, 0x00, 0xf0, 0xf1, 0x00, 0xf0, 0xff, 0xe1, 0x3f,
  0x80, 0xff, 0xf1, 0x01, 0xf0, 0xff, 0xe1, 0x3f, 0x80, 0xff, 0xe1, 0x03, 0xf0, 0xff, 0xe1, 0x3f,
  0x80, 0xff, 0xc1, 0x03, 0xf0, 0xff, 0xe1, 0x3f, 0x00, 0x00, 0x00, 0x00, 0xf0, 0xff, 0xff, 0x3f,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};
const uint8_t battery [] PROGMEM = {
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xfe, 0x7f, 0x01, 0x40, 0x01, 0x40, 0x01, 0xc0, 0x01, 0xc0,
  0x01, 0xc0, 0x01, 0x40, 0x01, 0x40, 0xfe, 0x3f
};

const uint8_t bluetooth [] PROGMEM = {
  0x00, 0x00, 0x60, 0x00, 0xc0, 0x01, 0x46, 0x06, 0x4c, 0x03, 0xf0, 0x00, 0xf0, 0x00, 0x48, 0x03,
  0x46, 0x06, 0xc0, 0x01, 0x40, 0x00, 0x00, 0x00
};

const uint8_t wifi_for_oled [] PROGMEM = {
  0x00, 0x00, 0xf0, 0x00, 0xfc, 0x03, 0x07, 0x0e, 0xf3, 0x0c, 0xfc, 0x03, 0x04, 0x02, 0xf0, 0x00,
  0x90, 0x00, 0x60, 0x00, 0x60, 0x00, 0x00, 0x00
};

const unsigned char menu_logo[] PROGMEM = {
  0xff, 0x07, 0xff, 0x07, 0x00, 0x00, 0x00, 0x00, 0xff, 0x07, 0xff, 0x07, 0x00, 0x00, 0x00, 0x00,
  0xff, 0x07, 0xff, 0x07, 0x00, 0x00, 0x00, 0x00
};

const unsigned char wifi_control [] PROGMEM = {
  0x00, 0x00, 0xe0, 0x07, 0xf8, 0x1f, 0x1e, 0x78, 0x87, 0xe1, 0xf3, 0xcf, 0x78, 0x1e, 0x0c, 0x30,
  0xe4, 0x27, 0xf0, 0x0f, 0x30, 0x0c, 0x80, 0x01, 0xc0, 0x03, 0xc0, 0x03, 0x80, 0x01, 0x00, 0x00
};

const unsigned char bluetooth_control [] PROGMEM = {
  0x00, 0x00, 0x80, 0x00, 0x80, 0x01, 0x80, 0x07, 0x80, 0x1c, 0x9c, 0x1c, 0xf0, 0x0f, 0xe0, 0x03,
  0xc0, 0x03, 0xf0, 0x0f, 0x9c, 0x18, 0x80, 0x1c, 0x80, 0x07, 0x80, 0x01, 0x80, 0x00, 0x00, 0x00
};


const unsigned char weather [] PROGMEM = {
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x00, 0x00, 0x80, 0x00, 0x00, 0x84, 0x10, 0x00, 0x08,
  0x18, 0x00, 0xc0, 0x0b, 0x00, 0x20, 0x72, 0x00, 0x10, 0xcc, 0x00, 0x17, 0x06, 0x01, 0x10, 0x02,
  0x02, 0x20, 0x02, 0x1e, 0x60, 0x03, 0x20, 0x98, 0x01, 0x40, 0x4c, 0x00, 0x40, 0x40, 0x00, 0x40,
  0x40, 0x00, 0x60, 0x80, 0x00, 0x30, 0x00, 0xff, 0x1f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00

};


int weather_item_wifi=-1;
int max_weather_item_wifi=3;
int weather_item=-1;
int max_weather_item=1;
const char* apiKey_weather = "bee6e9841064117a7fef8659311c636e";
const char* cityId_weather = "1264527";
String serverPath_weather = "http://api.openweathermap.org/data/2.5/weather?id=" + String(cityId_weather) + "&appid=" + String(apiKey_weather) + "&units=metric";
int yPosition;
int i;
const int lineHeight = 11; 
int page = 0;
String payload;
char string_network[50];
bool inagainscan=false;
bool incontrolcenter = false;
bool sw12item0 = false;
int network_item = -1;
int current_control = -1;
int max_control_item = 2;
int current_item = -1;
int num_items_page = 11;
int network_per_page=2;
int start_network=0;
String networkInfo [20];
bool selecting_network = false;
bool inscanwifi = false;
int lengths_networkinfo[20];
unsigned int n;
int scanitem=-1;
int maxscan=2;
bool in_weather_app=false;
bool in_weather_app_wifi=false;
struct NetworkCredentials {
  String ssid;
  String password;
};


NetworkCredentials knownNetworks[] = {
  {"KMT's MOBILE", "asdfghjkl"},
  {"iPhone", "1234567890"},
  {"Redmi 10", "11122006birthday"},
  {"GalaxyM01","ncxd6186"}
};

void logo() {
  u8g2.setContrast(0);
  for (int i = 0; i <= 255; i += 30) {
    u8g2.setContrast(i);
    u8g2.clearBuffer();
    u8g2.drawXBMP(30, 15, 64, 32, pic_of_logo);
    u8g2.sendBuffer();
    delay(300);
  }
  u8g2.clearBuffer();
  u8g2.drawXBMP(30, 15, 64, 32, pic_of_logo);
  u8g2.sendBuffer();
  delay(1000);
  u8g2.clearBuffer();
  u8g2.setContrast(128);
  u8g2.setFont(u8g2_font_7x13B_tr);
  u8g2.drawStr(10, 32, "KMT UNIVERSE 96");
  u8g2.setFont(u8g2_font_6x12_mf);
  u8g2.drawStr(27, 45, "WELCOMES YOU!");
  u8g2.sendBuffer();
  delay(1000);
}
void displayWeather(String weatherData){
  StaticJsonDocument<512> doc; // Increase size if necessary
  DeserializationError error = deserializeJson(doc, weatherData);
  u8g2.setDrawColor(0);
  u8g2.drawBox(0,14,128,64);
  u8g2.setDrawColor(1);
  if (error) {
    u8g2.setFont(u8g2_font_6x12_mf);
    u8g2.drawStr(46, 32, "Oops !");
    u8g2.drawStr(31,45,"Network Issue!");
    in_weather_app_wifi=false;
    in_weather_app=true;   
    u8g2.setFont(u8g2_font_5x7_tr);
    u8g2.drawStr(1,63,"<-");
    u8g2.setFont(u8g2_font_6x12_mf); 
    return;
  }
  const char* description = doc["weather"][0]["description"];
  float temp = doc["main"]["temp"];
  float feels_like = doc["main"]["feels_like"];
  float temp_min = doc["main"]["temp_min"];
  float temp_max = doc["main"]["temp_max"];
  int pressure = doc["main"]["pressure"];
  int humidity = doc["main"]["humidity"];
  int visibility = doc["visibility"];
  float wind_speed = doc["wind"]["speed"];
  int wind_deg = doc["wind"]["deg"];
  int cloudiness = doc["clouds"]["all"];


  if (weather_item_wifi==0){
         u8g2.drawFrame(112,44,15,10);
          u8g2.setDrawColor(0);
          u8g2.drawFrame(89, 60, 39, 11);
          u8g2.setDrawColor(1);
        }
        
  u8g2.setFont(u8g2_font_ncenB08_tr);
  switch (page) {
    case 0:
      u8g2.setFont(u8g2_font_twelvedings_t_all);
      u8g2.drawGlyph(114,53,125);
      u8g2.setFont(u8g2_font_ncenB08_tr);
      u8g2.drawStr(0, 24, "Weather:");
      u8g2.drawStr(0, 34, description);

      char tempString[32];
      snprintf(tempString, sizeof(tempString), "Temp: %.2f C", temp);
      u8g2.drawStr(0, 44, tempString);

      snprintf(tempString, sizeof(tempString), "Feels Like: %.2f C", feels_like);
      u8g2.drawStr(0, 54, tempString);

      snprintf(tempString, sizeof(tempString), "Min: %.2f C", temp_min);
      u8g2.drawStr(0, 64, tempString);

      snprintf(tempString, sizeof(tempString), "Max: %.2f C", temp_max);
      u8g2.drawStr(0, 74, tempString);

      snprintf(tempString, sizeof(tempString), "Pressure: %d hPa", pressure);
      u8g2.drawStr(0, 84, tempString);

      snprintf(tempString, sizeof(tempString), "Humidity: %d%%", humidity);
      u8g2.drawStr(0, 94, tempString);

      snprintf(tempString, sizeof(tempString), "Visibility: %d m", visibility);
      u8g2.drawStr(0, 104, tempString);

      snprintf(tempString, sizeof(tempString), "Wind: %.2f m/s %d", wind_speed, wind_deg);
      u8g2.drawStr(0, 114, tempString);

      snprintf(tempString, sizeof(tempString), "Cloudiness: %d%%", cloudiness);
      u8g2.drawStr(0, 124, tempString);
      break;
      
    case 1:
      u8g2.setFont(u8g2_font_twelvedings_t_all);
      u8g2.drawGlyph(114,53,125);
      u8g2.setFont(u8g2_font_ncenB08_tr);
      u8g2.drawStr(0, 24, "Weather:");
      snprintf(tempString, sizeof(tempString), "Min: %.2f C", temp_min);
      u8g2.drawStr(0, 34, tempString);

      snprintf(tempString, sizeof(tempString), "Max: %.2f C", temp_max);
      u8g2.drawStr(0, 44, tempString);

      snprintf(tempString, sizeof(tempString), "Pressure: %d hPa", pressure);
      u8g2.drawStr(0, 54, tempString);

      snprintf(tempString, sizeof(tempString), "Humidity: %d%%", humidity);
      u8g2.drawStr(0, 64, tempString);

      snprintf(tempString, sizeof(tempString), "Visibility: %d m", visibility);
      u8g2.drawStr(0, 74, tempString);

      snprintf(tempString, sizeof(tempString), "Wind: %.2f m/s %d", wind_speed, wind_deg);
      u8g2.drawStr(0, 84, tempString);

      snprintf(tempString, sizeof(tempString), "Cloudiness: %d%%", cloudiness);
      u8g2.drawStr(0, 94, tempString);
      break;
      
    case 2:
      u8g2.setFont(u8g2_font_twelvedings_t_all);
      u8g2.drawGlyph(114,53,125);
      u8g2.setFont(u8g2_font_ncenB08_tr);
      u8g2.drawStr(0, 24, "Weather:");
      snprintf(tempString, sizeof(tempString), "Wind: %.2f m/s %d", wind_speed, wind_deg);
      u8g2.drawStr(0, 34, tempString);

      snprintf(tempString, sizeof(tempString), "Cloudiness: %d%%", cloudiness);
      u8g2.drawStr(0, 44, tempString);
      u8g2.setFont(u8g2_font_5x7_tr);
      u8g2.drawStr(1,63, "<-"); 
      u8g2.drawStr(91, 62, "Refresh");
     
      break;
  } // Position for the arrow and refresh below cloudiness
  u8g2.sendBuffer();
}
void weather_app(){
   u8g2.setDrawColor(0);
   u8g2.drawBox(0,14,128,50);
   u8g2.setDrawColor(1);
   if (WiFi.status()==WL_CONNECTED){
    in_weather_app_wifi=true;
    HTTPClient http;
    http.begin(serverPath_weather.c_str());
    int httpResponseCode = http.GET();
    if (httpResponseCode > 0) {
        payload = http.getString();
        displayWeather(payload);
      }
      else {
        in_weather_app_wifi=false;
        in_weather_app=true;
        u8g2.setFont(u8g2_font_6x12_mf);
        u8g2.drawStr(46, 32, "Oops !");
        u8g2.drawStr(19,45,"No Data Found !");
        u8g2.setFont(u8g2_font_5x7_tr);
        u8g2.drawStr(1,63,"<-");
        u8g2.setFont(u8g2_font_6x12_mf);
      }
  }
  else{
    in_weather_app=true;
    u8g2.setFont(u8g2_font_6x12_mf);
    u8g2.drawStr(46, 32, "Oops !");
    u8g2.drawStr(1, 45, "No Network Connection!");
    u8g2.setFont(u8g2_font_5x7_tr);
    u8g2.drawStr(1,63,"<-");
    u8g2.setFont(u8g2_font_6x12_mf);
  }
  u8g2.sendBuffer();
}
void beep() {
  digitalWrite(13, HIGH);
  delay(50);
  digitalWrite(13, LOW);
}
void animateControlCenter() {
  const int animationSpeed = 10; // Adjust the speed of the animation

  // Slide animation
  for (int x = 128; x >= 87; x -= animationSpeed) {
    u8g2.drawFrame(x, 14, 41, 48);
    u8g2.setDrawColor(0);
    u8g2.drawBox(x + 1, 15, 38, 46);
    u8g2.setDrawColor(1);
    u8g2.sendBuffer();
    delay(7);
  }

  // Draw the final state of the control center
  u8g2.drawXBMP(91, 20, 16, 16, wifi_control); // Draw wifi icon
  u8g2.drawXBMP(110, 20, 16, 16, bluetooth_control); // Draw bluetooth icon
  u8g2.sendBuffer(); // Update the buffer to display all content
  incontrolcenter = true;
}


void update_display(int i) {
  u8g2.drawXBMP(15, 0, 12, 12, bluetooth);
  u8g2.drawXBMP(93, 0, 16, 12, battery);
  u8g2.drawXBMP(113, 2, 14, 12, menu_logo);

  int posx1 = 0, posy1 = 0, framex1 = 0, framey1 = 0;
  int posx2 = 0, posy2 = 0, framex2 = 0, framey2 = 0;

  const int frameWidth = 25;
  const int frameHeight = 25;

  // Adjust positions and dimensions based on the current item index
  switch (i) {
    case 0:
      posx2 = 3; posy2 = 37; framex2 = frameWidth; framey2 = frameHeight;
      posx1 = 111; posy1 = 0; framex1 = 15; framey1 = 14; break;
    case 1:
      posx2 = 111; posy2 = 0; framex2 = 15; framey2 = 14;
      posx1 = 3; posy1 = 13; framex1 = frameWidth; framey1 = frameHeight; break;
    case 2:
      posx2 = 3; posy2 = 13; framex2 = frameWidth; framey2 = frameHeight;
      posx1 = 33; posy1 = 13; framex1 = frameWidth; framey1 = frameHeight; break;
    case 3:
      posx2 = 33; posy2 = 13; framex2 = frameWidth; framey2 = frameHeight;
      posx1 = 63; posy1 = 13; framex1 = frameWidth; framey1 = frameHeight; break;
    case 4:
      posx2 = 63; posy2 = 13; framex2 = frameWidth; framey2 = frameHeight;
      posx1 = 93; posy1 = 13; framex1 = frameWidth; framey1 = frameHeight; break;
    case 5:
      posx2 = 93; posy2 = 13; framex2 = frameWidth; framey2 = frameHeight;
      posx1 = 3; posy1 = 37; framex1 = frameWidth; framey1 = frameHeight; break;
    case 6:
      posx1 = 33; posy1 = 37; framex1 = frameWidth; framey1 = frameHeight;
      posx2 = 3; posy2 = 37; framex2 = frameWidth; framey2 = frameHeight;
      break;
    case 7:
      posx1 = 63; posy1 = 37; framex1 = frameWidth; framey1 = frameHeight;
      posx2 = 33; posy2 = 37; framex2 = frameWidth; framey2 = frameHeight;
      break;
    case 8:
      posx1 = 93; posy1 = 37; framex1 = frameWidth; framey1 = frameHeight;
      posx2 = 63; posy2 = 37; framex2 = frameWidth; framey2 = frameHeight;
      break;
    case 9:
      posx1 = 3; posy1 = 13; framex1 = frameWidth; framey1 = frameHeight;
      posx2 = 93; posy2 = 37; framex2 = frameWidth; framey2 = frameHeight;
      break;
    case 10:
      posx1 = 3; posy1 = 37; framex1 = frameWidth; framey1 = frameHeight;
      posx2 = 3; posy2 = 13; framex2 = frameWidth; framey2 = frameHeight;
      break;
    default:
      posx1 = 0; posy1 = 0; framex1 = 0; framey1 = 0;
      posx2 = 0; posy2 = 0; framex2 = 0; framey2 = 0; break;
  }
  if (current_item > -1) {
    u8g2.drawFrame(posx1, posy1, framex1, framey1);
    u8g2.setDrawColor(0);
    u8g2.drawFrame(posx2, posy2, framex2, framey2);
    u8g2.setDrawColor(1);
  }
  if (current_item==10){
    u8g2.drawHLine(3,37,25);
  }
  u8g2.sendBuffer();
}
int stx10 = 0, sty10 = 0, stx20 = 0, sty20 = 0;
int stx11 = 0, sty11 = 0, stx21 = 0, sty21 = 0;


void update_controlcenter(int current_control) {
  switch (current_control) {
    case 0:
      stx11 = 109; sty11 = 19; stx21 = 18; sty21 = 18;
      stx10 = 90; sty10 = 19; stx20 = 18; sty20 = 18; break;
    case 1:
      stx10 = 109; sty10 = 19; stx20 = 18; sty20 = 18;
      stx11 = 90; sty11 = 19; stx21 = 18; sty21 = 18; break;
    default :
      stx10 = 0; sty10 =0; stx20 = 0; sty20 =0;
      stx11 =0; sty11 = 0; stx21 = 0; sty21 = 0; break;
  }
  if (stx20 > 0 && sty20 > 0) {
    u8g2.drawFrame(stx10, sty10, stx20, sty20);
    u8g2.setDrawColor(0);
    u8g2.drawFrame(stx11, sty11, stx21, sty21);
    u8g2.setDrawColor(1);
    u8g2.sendBuffer();
  }
  incontrolcenter = true;
}



void connection(int network_items) {

  // Fetch the SSID from the scan results
  String selectedSSID = WiFi.SSID(network_items);
  String selectedPassword = "";

  // Find the corresponding password for the selected SSID
  for (int i = 0; i < sizeof(knownNetworks) / sizeof(NetworkCredentials); i++) {
    if (knownNetworks[i].ssid == selectedSSID) {
      selectedPassword = knownNetworks[i].password;
      break;
    }
    inscanwifi=false;
    incontrolcenter=false;
  }


  // Start WiFi connection
  WiFi.begin(selectedSSID.c_str(), selectedPassword.c_str());
  WiFi.setHostname("Alien X");
  u8g2.setDrawColor(0);
  u8g2.drawBox(0, 14, 128, 50);
  u8g2.setDrawColor(1);
  u8g2.setFont(u8g2_font_6x12_mf);
  u8g2.drawStr(0, 26, "Connecting");
  u8g2.sendBuffer();
  // Wait for connection
  int maxAttempts = 30; // Adjust the number of attempts as needed
  int attempts = 0;
  while (WiFi.status() != WL_CONNECTED && attempts < maxAttempts) {
    u8g2.drawStr(60+(attempts*6), 26, ".");
    u8g2.sendBuffer();
    delay(500);
    attempts++;
  }

  if (WiFi.status() == WL_CONNECTED) {

    u8g2.setFont(u8g2_font_6x12_mf);
    u8g2.drawStr(0, 38, "Connected!");
    u8g2.sendBuffer();
    delay(500); // Wait for a moment before proceeding

    // Proceed to the next stage or interface
    selecting_network = false; // Reset the flag for selecting network
    incontrolcenter = false;
    inscanwifi=false;
    sw12item0=false;
    WiFi.scanDelete();
  } else {
    // Connection failed
    u8g2.setFont(u8g2_font_6x12_mf);
    u8g2.drawStr(0, 38, "Connection failed!");
    u8g2.sendBuffer();
    delay(500); // Display the error message for a while
    selecting_network = false; // Reset the flag for selecting network
    incontrolcenter = false;
    inscanwifi=false;
    sw12item0=false;
  }

  // Clear the scan results
  u8g2.setDrawColor(0);
  u8g2.drawBox(0,14,128,50);
  u8g2.setDrawColor(1);
  u8g2.sendBuffer();
}


void selecting_the_network(int net_item) {
  u8g2.setDrawColor(0);
  u8g2.drawBox(0,30,128,50);
  u8g2.setDrawColor(1);
  u8g2.setFont(u8g2_font_5x7_tr); 
  u8g2.drawStr(106,63,"Scan");
  u8g2.drawStr(1,63,"<-");
  u8g2.setFont(u8g2_font_6x12_tf);
  
   for(i=start_network;i<start_network+network_per_page && i<n ;i++){ 
        yPosition = 43 + (i-start_network) * 12;
       u8g2.drawStr(0, yPosition, networkInfo[i].c_str());
       if (i==net_item){
       u8g2.drawFrame(0, yPosition - 10, (lengths_networkinfo[i]), 12);
     }
   }
  u8g2.sendBuffer();
}
 
void scanAndDisplayNetworks() {  
  inscanwifi=true;
  u8g2.setDrawColor(0);
  u8g2.drawBox(0, 14, 128, 50);
  u8g2.setDrawColor(1);
  u8g2.setFont(u8g2_font_6x12_mf);
  u8g2.drawStr(22, 42, "Searching");
  u8g2.setFont(u8g2_font_streamline_all_t);
  u8g2.drawGlyph(80, 50, 0x01d0);
  u8g2.setFont(u8g2_font_6x12_mf);
  u8g2.sendBuffer();
  n = WiFi.scanNetworks();
  if (n == 0) {

    inagainscan=true;
    selecting_network=false;
    u8g2.setDrawColor(0);
    u8g2.drawBox(0, 14, 128, 50);
    u8g2.setDrawColor(1);
    u8g2.setFont(u8g2_font_6x12_mf);
    u8g2.drawStr(46, 32, "Oops !");
    u8g2.drawStr(1, 45, "No Network Available!");
    u8g2.setFont(u8g2_font_5x7_tr); 
   u8g2.drawStr(106,63,"Scan");
   u8g2.drawStr(1,63,"<-");
   u8g2.setFont(u8g2_font_6x12_mf);
   u8g2.sendBuffer();
  } else {
  
    inagainscan=false;
    selecting_network=true;
    u8g2.setDrawColor(0);
    u8g2.drawBox(0, 14, 128, 50);
    u8g2.setDrawColor(1);
    u8g2.setFont(u8g2_font_6x12_mf);
    sprintf(string_network, "Available Networks[%d]:", n);
    u8g2.drawStr(0, 30, string_network);
    for (int i = 0; i < n; i++) {
      networkInfo[i] = String(i + 1) + "." + WiFi.SSID(i) + "[" + WiFi.RSSI(i) + "]";
      lengths_networkinfo[i] = networkInfo[i].length()*6; 
    }
    u8g2.sendBuffer();
    incontrolcenter=false;
    inscanwifi = true;
    selecting_the_network(network_item);
  }
 
  incontrolcenter=false;
  
}



void setup() {
  pinMode(13, OUTPUT);
  pinMode(23, INPUT_PULLUP);
  pinMode(12, INPUT_PULLUP);
  u8g2.begin();
  logo();
  u8g2.clearBuffer();
  update_display(0);
  WiFi.mode(WIFI_STA);
  WiFi.setHostname("Alien X");
}



void fourth_icons() {

  u8g2.drawXBMP(94, 14, 23, 23, square);

  u8g2.drawXBMP(94, 38, 23, 23, square);

}

void loop() {

  if (digitalRead(23) == LOW) {
    delay(50);
    if (digitalRead(23) == LOW) {
        beep();
      if (incontrolcenter && !selecting_network && !inagainscan) {
        current_control = (current_control + 1) % max_control_item;
        update_controlcenter(current_control);

      }
      else if (!incontrolcenter && !selecting_network && !inagainscan && !inscanwifi &&!in_weather_app &&!in_weather_app_wifi) {
        current_item = (current_item + 1) % num_items_page;
        if(current_item==9){
                u8g2.setDrawColor(0);
                u8g2.drawBox(0, 14, 128, 50);
                u8g2.setDrawColor(1);
                u8g2.sendBuffer();
        }
        update_display(current_item);
      }
      else if(in_weather_app){
        weather_item=(weather_item+1)%max_weather_item;
        if (weather_item==0){
          u8g2.drawFrame(0,56,13,8);
        }
        u8g2.sendBuffer();
      }
      else if(in_weather_app_wifi)
      {
        weather_item_wifi=(weather_item_wifi+1)%max_weather_item_wifi;
        if (page==0 || page==1){
          weather_item_wifi=0;
        }
        if (weather_item_wifi==0){
          u8g2.drawFrame(112,44,15,10);
          u8g2.setDrawColor(0);
          u8g2.drawFrame(89, 55, 39, 10);
          u8g2.setDrawColor(1);
        }
        else if (weather_item_wifi==1 && page==2){
          u8g2.drawFrame(0,56,13,8);
          u8g2.setDrawColor(0);
          u8g2.drawFrame(112,44,15,10);
          u8g2.setDrawColor(1);
        }
        else if (weather_item_wifi==2 && page==2){
          u8g2.drawFrame(89,55, 39, 10);
          u8g2.setDrawColor(0);
          u8g2.drawFrame(0,56,13,8);
          u8g2.setDrawColor(1);
        }
        u8g2.sendBuffer();
      }
      else if (selecting_network && !inagainscan && inscanwifi && !incontrolcenter) {
        network_item = (network_item + 1) % (n+2); 
        if (network_item==-1 || network_item==0){
          start_network=0;
        }
        if(network_item>=start_network+network_per_page){
          if (network_item<n){
          start_network = (start_network + 1) % (n);
          }
          }
         if (network_item==n){
                 u8g2.setDrawColor(0);
                 u8g2.drawFrame(0, yPosition - 10, (lengths_networkinfo[i-1]), 12);
                 u8g2.setDrawColor(1);
                 u8g2.drawFrame(104,55,24,9);
                 u8g2.sendBuffer();       
        }
        else if (network_item==n+1){
                  u8g2.setDrawColor(0);
                  u8g2.drawFrame(104,55,24,9);
                  u8g2.setDrawColor(1);
                  u8g2.drawFrame(0,56,13,8);
                  u8g2.sendBuffer();
        }
        else {
           u8g2.setDrawColor(0);
           u8g2.drawFrame(104,55,24,9);
           u8g2.setDrawColor(1);
           u8g2.sendBuffer();
           selecting_the_network(network_item);
        }

      }
      else if (inagainscan && !selecting_network && !incontrolcenter){

        scanitem=(scanitem+1)%maxscan;
        if (scanitem==0){
          u8g2.drawFrame(104,55,24,9);
          u8g2.setDrawColor(0);
           u8g2.drawFrame(0,56,13,8);
           u8g2.setDrawColor(1);
        }
        else if (scanitem==1){
          u8g2.drawFrame(0,56,13,8);
          u8g2.setDrawColor(0);
           u8g2.drawFrame(104,55,24,9);
           u8g2.setDrawColor(1);
        }
        u8g2.sendBuffer();
        }
    }
  }

  if (digitalRead(12) == LOW) {
    delay(50);
    if (digitalRead(12) == LOW) {
       beep();
      if (incontrolcenter && !selecting_network && !inagainscan) {
        if (current_control == 0) {
          if (WiFi.status()!=WL_CONNECTED){
          scanAndDisplayNetworks();
          inscanwifi = true;
          }
          else if (WiFi.status()==WL_CONNECTED){
            WiFi.disconnect();
          }
        }
      }
      else if (in_weather_app){
        if (weather_item ==0){
         in_weather_app=false;
         sw12item0=false;
         u8g2.setDrawColor(0);
         u8g2.drawBox(0,14,128,64);
         u8g2.setDrawColor(1);
         u8g2.sendBuffer();
        }
      }
        else if (in_weather_app_wifi){
        if (weather_item_wifi==0){
          page++;
          if (page > 2) { // Number of pages
        page = 0; // Loop back to the first page
      }
          displayWeather(payload);
          delay(500);
        }
        else if(weather_item_wifi==1){
          in_weather_app_wifi=false;
          sw12item0=false;
         u8g2.setDrawColor(0);
         u8g2.drawBox(0,14,128,64);
         u8g2.drawFrame(3,13,25,25);
         u8g2.setDrawColor(1);
         u8g2.sendBuffer();
         weather_item_wifi=-1;
        }
        else if (weather_item_wifi==2 ){
          page=0;
          weather_app();
        }
      }
      else if (!incontrolcenter && !selecting_network && !inagainscan) {
        sw12item0 = true;
        if (current_item == 0) {
          animateControlCenter();
        }
        if (current_item==1){
          u8g2.setDrawColor(0);
          u8g2.drawFrame(3,13,25,25);
          u8g2.setDrawColor(1);
          u8g2.sendBuffer();
          weather_app();
        }
      }
      else if (selecting_network && !inagainscan && inscanwifi && !incontrolcenter) {
        if (network_item==n){
          scanAndDisplayNetworks();
          network_item=-1;
        }
        else if(network_item==n+1){
          u8g2.setDrawColor(0);
          u8g2.drawBox(0,14,128,50);
          u8g2.setDrawColor(1);
          u8g2.sendBuffer();
          incontrolcenter=false;
          inagainscan=false;
          selecting_network=false;
          inscanwifi=false;
          sw12item0=false;
          network_item=-1;
          }else if (network_item<n){
           connection(network_item);
           selecting_network=false;
           network_item=-1;
        }
      }
      else if (inagainscan && !selecting_network && !incontrolcenter){
        if (scanitem==0){
          scanAndDisplayNetworks();
        }
        else if (scanitem==1){
          u8g2.setDrawColor(0);
          u8g2.drawBox(0,14,128,50);
          u8g2.setDrawColor(1);
          u8g2.sendBuffer();
          incontrolcenter=false;
          inagainscan=false;
          selecting_network=false;
          inscanwifi=false;
          sw12item0=false;
          scanitem=0;
        }
      }
    }
  }

  if (WiFi.status() == WL_CONNECTED) {
    u8g2.drawXBMP(0, 0, 12, 12, wifi_for_oled);
    u8g2.sendBuffer();
  }
  if(WiFi.status()!=WL_CONNECTED){
    u8g2.drawXBMP(0, 0, 12, 12, wifi_hider);
    u8g2.sendBuffer();
  }

  
  if (current_item > 8) {
      u8g2.drawXBMP(4, 14, 23, 23, square);
      u8g2.drawXBMP(4, 38, 23, 23, square);
      u8g2.sendBuffer();
    }
  if (!inscanwifi && !incontrolcenter &&  !inagainscan && current_item<=8 && !in_weather_app_wifi && !in_weather_app) {
    
    u8g2.drawXBMP(4, 14, 23, 23, weather);

    u8g2.drawXBMP(34, 14, 23, 23, square);

    u8g2.drawXBMP(64, 14, 23, 23, square);

    if ((!sw12item0 && (current_item == -1 || current_item == 0 || current_item == 1)) || (sw12item0 && current_item == 1)) {
      fourth_icons(); // Call the function to draw the fourth and fifth icons
      sw12item0 = false; // Reset the boolean flag
    }


    // Second row (4 icons)


    u8g2.drawXBMP(4, 38, 23, 23, square);

    u8g2.drawXBMP(34, 38, 23, 23, square);

    u8g2.drawXBMP(64, 38, 23, 23, square);

    
    u8g2.sendBuffer();



    delay(100); // Control animation speed
  }
}