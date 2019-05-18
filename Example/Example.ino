#include "Emg.h"

Emg module;
IntervalTimer timer;

void readFromModule(){
  module.updateData();
}

void setup() {
  Serial.begin(9600);
  module.begin(Serial1, 115200);
  timer.begin(readFromModule, 10000);
}

void loop() {
  Serial.print("Z = ");
  Serial.print(module.getAccZ());
  Serial.println();
  Serial.print("EMG1 = ");
  Serial.print(module.getEmg1());
  Serial.println();
  delay(250);
}
