#include <SPI.h>
#include <Gamebuino.h>

Gamebuino gb;

void setup() {
  gb.begin();
  gb.titleScreen(F("Metalog"));
}

void loop() {
  if(gb.update()){
    
  }
}
