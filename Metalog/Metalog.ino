#include <EEPROM.h>
#include <SPI.h>
#include <Gamebuino.h>

Gamebuino gb;

struct Comp lecomp;

void setup() {
  gb.begin();
  gb.titleScreen(F("Metalog"));
}

void loop() {
  if(gb.update()){
  }
}
