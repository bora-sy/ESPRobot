#include <Arduino.h>
#include "Comms/CommsMain.h"
#include "JoystickHandler.h"

#define LOGTAG "Main"

void setup() {
  Serial.begin(921600);
  Serial.println("Starting");

  if(!CommsMain::Initialize())
  {
    Serial.println("Failed to initialize comms");
    delay(2000);
    ESP.restart();
    return;
  }

  JoystickHandler::Initialize();

  Serial.println("Started");
}

void loop() {
  
}