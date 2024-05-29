#include "WebServer.h"
#include <ArduinoJson.h>

// Access Point config
const char *ssid = "ESP8266_AP";
const char *password = "12345678";

ESP8266WebServer server(80);

int secondsG = 15;
int minutesG = 0;
int hoursG = 0;
long secMillisG = 0;
int secondsB = 15;
int minutesB = 0;
int hoursB = 0;
long secMillisB = 0;
long interval = 1000;

bool setTime = false;
bool bombStarted = false;

unsigned long duracion = 100;

const int REDLED = D5;
const int BUTTON = D6;
const int BUZZER = D7;

LiquidCrystal_I2C lcd(0x27, 16, 2);

int device;

void timerBomb()
{
  // TODO create time logic
}

void startWebServer()
{
  lcd.init();
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("CSGO Bomb");
  lcd.setCursor(0, 1);
  lcd.print("Replica");

  pinMode(REDLED, OUTPUT);
  pinMode(BUTTON, INPUT_PULLUP);
  pinMode(BUZZER, OUTPUT);

  WiFi.softAP(ssid, password);

  server.on("/connect", HTTP_POST, handleConnect);
  server.onNotFound(handleNotFound);
  server.on("/start", HTTP_POST, handleStartGame);

  server.begin();
  Serial.print("Server started. ");
  Serial.print("Access Point IP: ");
  Serial.print(WiFi.softAPIP());

  digitalWrite(REDLED, HIGH);
  tone(BUZZER, 440);
  delay(1500);

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Server started");
  lcd.setCursor(0, 1);
  lcd.print("Connect a device");
  digitalWrite(REDLED, LOW);
  noTone(BUZZER);
}

void handleClientRequests()
{
  server.handleClient();
}

void handleConnect()
{
  digitalWrite(REDLED, HIGH);
  if (server.hasArg("plain"))
  {
    String body = server.arg("plain");
    DynamicJsonDocument doc(1024);
    deserializeJson(doc, body);
    int deviceC = doc["device"];
    Serial.print(deviceC);
    if (deviceC)
    {
      device = deviceC;
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Device Connected");
      lcd.setCursor(0, 1);
      lcd.print("Select Game Times");
      server.send(200, "application/json", "{\"connected\":\"true\"}");
      tone(BUZZER, 440);
    }
    else
    {
      server.send(400, "application/json", "{\"msg\":\"wrong device\"}");
    }
  }
  else
  {
    server.send(400, "application/json", "{\"msg\":\"connection denied\"}");
  }
  delay(500);
  digitalWrite(REDLED, LOW);
  noTone(BUZZER);
}

void handleNotFound()
{
  server.send(404, "application/json", "{\"msg\":\"wrong endpoint\"}");
}

void handleStartGame()
{
  digitalWrite(REDLED, HIGH);
  if (server.hasArg("plain"))
  {
    String body = server.arg("plain");
    DynamicJsonDocument doc(1024);
    deserializeJson(doc, body);
    int deviceC = doc["device"];
    String hoursGame = doc["hoursGame"];
    String minutesGame = doc["minutesGame"];
    String secondsGame = doc["secondsGame"];
    String hoursBomb = doc["hoursBomb"];
    String minutesBomb = doc["minutesBomb"];
    String secondsBomb = doc["secondsBomb"];
    if (deviceC != device)
    {
      server.send(400, "application/json", "{\"msg\":\"wrong device\"}");
    }
    else
    {
      if (hoursGame)
      {
        Serial.println(hoursGame);
        hoursG = 10 * (int(hoursGame[0]) - 48) + (int(hoursGame[1] - 48));
      }
      if (minutesGame)
      {
        Serial.println(minutesGame);
        minutesG = 10 * (int(minutesGame[0]) - 48) + (int(minutesGame[1] - 48));
      }
      if (secondsGame)
      {
        secondsG = 10 * (int(secondsGame[0]) - 48) + (int(secondsGame[1] - 48));
      }
      if (hoursBomb)
      {
        hoursB = 10 * (int(hoursBomb[0]) - 48) + (int(hoursBomb[1] - 48));
      }
      if (minutesBomb)
      {
        Serial.println(minutesBomb);
        minutesB = 10 * (int(minutesBomb[0]) - 48) + (int(minutesBomb[1] - 48));
      }
      if (secondsBomb)
      {
        secondsB = 10 * (int(secondsBomb[0]) - 48) + (int(secondsBomb[1] - 48));
      }
      if (hoursGame && minutesGame && secondsGame && hoursBomb && minutesBomb && secondsBomb)
      {
        setTime = true;
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("Game started");
        lcd.setCursor(0, 1);
        lcd.print("Press to activ");
        server.send(200, "application/json", "{\"msg\":\"Game had started\"}");
        tone(BUZZER, 440);
      }
      else
      {
        server.send(400, "application/json", "{\"msg\":\"wrong inputs\"}");
      }
    }
  }
  else
  {
    server.send(400, "application/json", "{\"msg\":\"some error\"}");
  }
  delay(500);
  digitalWrite(REDLED, LOW);
  noTone(BUZZER);
}