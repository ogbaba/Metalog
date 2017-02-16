#include <EEPROM.h>
#include <SPI.h>
#include <Gamebuino.h>

#define NULLCOMP 0
#define NOT 1
#define OR 2
#define AND 3
#define NOR 4
#define NAND 5
#define XOR 6
#define INP 7
#define LED 8

#define CAMERA_SPEED 5

struct Comp
{
    byte id = 0;
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
    byte nbcomps = 0;
    struct GComp comps[32];
    struct Comp * outputs [16] = {NULL};
};

struct Save
{
    struct Circuit circuits[8];
};

struct Camera
{
    int x = 0;
    int y = 0;
};

struct Circuit circuit;
struct Comp comp;
struct GComp gcomp;

Camera camera;

Gamebuino gb;

void setup() {
    gb.begin();
    gb.titleScreen(F("Metalog"));
    comp.id = 1;
    circuit.comps[0] = gcomp;
    circuit.comps[0].x = 3;
    circuit.comps[0].y = 5;
    circuit.comps[0].comp = comp;
    circuit.nbcomps = 1;
}

void loop() {
    if (gb.update()){
        get_inputs();
        // update_logic();
        draw_circuit();
    }
}
