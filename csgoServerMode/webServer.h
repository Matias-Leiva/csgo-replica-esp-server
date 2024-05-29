#ifndef WEBSERVER_H
#define WEBSERVER_H

#include <ESP8266WebServer.h>
#include <LiquidCrystal_I2C.h>

extern ESP8266WebServer server; // Declarar el servidor web externamente
extern bool setTime;

void startWebServer();
void handleClientRequests();
void handleConnect();
void handleNotFound();
void handleStartGame();
void timerBomb();

#endif