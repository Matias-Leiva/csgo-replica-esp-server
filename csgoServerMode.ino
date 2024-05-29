#include <ESP8266WebServer.h>
#include <ArduinoJson.h>
#include <LiquidCrystal.h>

// Access Point config
const char *ssid = "ESP8266_AP";
const char *password = "12345678";

ESP8266WebServer server(80);

int SecondsG = 0;
int MinutesG = 0;
int HoursG = 0;
long secMillisG = 0;
int SecondsB = 0;
int MinutesB = 0;
int HoursB = 0;
long secMillisB = 0;
long interval = 1000;

bool setTime = false;
bool bombStarted = false;

unsigned long duracion = 100;

const int Buzzer = ;
const int REDLED = A0;
const int Button = D8;

LiquidCrystal lcd(D6, D5, D3, D2, D1, D0); // Rs, E, D4, D5, D6, D7;

int device;

void handleRoot()
{
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
}

void handleNotFound()
{
  server.send(404, "application/json", "{\"msg\":\"wrong endpoint\"}");
}

void handleStartGame()
{
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
        HoursG = 10 * (int(hoursGame[0]) - 48) + (int(hoursGame[1] - 48));
      }
      if (minutesGame)
      {
        Serial.println(minutesGame);
        MinutesG = 10 * (int(minutesGame[0]) - 48) + (int(minutesGame[1] - 48));
      }
      if (secondsGame)
      {
        SecondsG = 10 * (int(secondsGame[0]) - 48) + (int(secondsGame[1] - 48));
      }
      if (hoursBomb)
      {
        HoursB = 10 * (int(hoursBomb[0]) - 48) + (int(hoursBomb[1] - 48));
      }
      if (minutesBomb)
      {
        Serial.println(minutesBomb);
        MinutesB = 10 * (int(minutesBomb[0]) - 48) + (int(minutesBomb[1] - 48));
      }
      if (secondsBomb)
      {
        SecondsB = 10 * (int(secondsBomb[0]) - 48) + (int(secondsBomb[1] - 48));
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
}

void handleStartBomb()
{
  while (!bombStarted)
  {
  }
}

void setup()
{
  Serial.begin(115200);

  WiFi.softAP(ssid, password);

  server.on("/connect", HTTP_POST, handleRoot);
  server.onNotFound(handleNotFound);
  server.on("/start", HTTP_POST, handleStartGame);

  server.begin();
  Serial.print("Servidor iniciado. ");
  Serial.print("IP del punto de acceso: ");
  Serial.println(WiFi.softAPIP());
  pinMode(Buzzer, OUTPUT);
  pinMode(REDLED, OUTPUT);
  pinMode(Button, INPUT_PULLUP);

  lcd.begin(16, 2);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("CSGO Bomb");
  lcd.setCursor(0, 1);
  lcd.print("Replica");

  delay(3000);

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Servidor started");
  lcd.setCursor(0, 1);
  lcd.print("Connect a device");
}

void loop()
{
  if (!setTime)
  {
    server.handleClient();
  }
  else
  {
    handleStartBomb();
  }
}