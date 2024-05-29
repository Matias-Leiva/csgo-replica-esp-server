#include <Arduino.h>
#include "WebServer.h"

void setup()
{
  Serial.begin(115200);
  startWebServer();
}

void loop()
{
  if (!setTime)
  {
    handleClientRequests();
  }
  else
  {
    timerBomb();
  }
}