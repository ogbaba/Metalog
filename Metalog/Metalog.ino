#include <EEPROM.h>
#include <SPI.h>
#include <Gamebuino.h>


#define NOT 1
#define OR 2
#define AND 3
#define NOR 4
#define NAND 5
#define XOR 6
#define INP 7
#define LED 8

struct Comp
{
    byte id;
    bool a = false;
    bool b = false;
    struct Comp * pr_a = NULL;
    struct Comp * pr_b = NULL;
};

struct GComp
{
    int x;
    int y;
    char name [8];
    struct Comp comp;
};

struct Circuit
{
    char name [8];
    struct GComp comps[64];
    struct Comp * outputs [16] = {NULL};
};

struct Save
{
    struct Circuit circuits[8];
};


Gamebuino gb;

void setup() {
    gb.begin();
    gb.titleScreen(F("Metalog"));
}

void loop() {
    if (gb.update()){
    }
}
