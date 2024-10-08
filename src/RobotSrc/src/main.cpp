#include <Arduino.h>
#include "LCD.h"
#include "Comms/CommsMain.h"

#define LOGTAG "Main"

void InitCritical(bool (*initFunc)(), const char* loadingText, const char* errorText)
{
  LCD::PrintCenter(loadingText);

  bool suc = initFunc();
  if (!suc)
  {
    LCD::PrintCenter(errorText);
    delay(1500);
    LCD::PrintCenter("Restarting");
    delay(800);
    ESP.restart();
  }
}

void setup() {
  Serial.begin(921600);
  Serial.println("Starting");
  LCD::Initialize();
  LCD::PrintCenter("Starting..");

  InitCritical(CommsMain::Initialize, "Initializing Comms", "Comms failed to initialize");



  Serial.println("Started");
  LCD::PrintCenter("Started");
}

void loop() {
  CommsMain::Loop();
  delay(1000);
}