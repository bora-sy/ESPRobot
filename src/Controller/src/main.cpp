#include <Arduino.h>
#include "Comms/CommsMain.h"

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

  Serial.println("Started");
}

void loop() {
  
}