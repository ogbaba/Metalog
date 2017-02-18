void draw_circuit () {
    const byte * bitmap;
    for (unsigned i=0; i < circuit.nbcomps; ++i) {
        /*gb.display.drawRect(circuit.comps[i].x - camera.x,
                            circuit.comps[i].y - camera.y,
                            3, 3);
                            */
        if (gb.collideRectRect(
                    circuit.comps[i].x, circuit.comps[i].y, 16, 16,
                    camera.x, camera.y, LCDWIDTH - 16, LCDHEIGHT))
        {
            switch (circuit.comps[i].id)
            {
                case OR:
                    bitmap = BMOR;
                    break;
                case AND:
                    bitmap = BMAND;
                    break;
                case NOR:
                    bitmap = BMNOR;
                    break;
                case NAND:
                    bitmap = BMNAND;
                    break;
                case XOR:
                    bitmap = BMXOR;
                    break;
                case NOT:
                    bitmap = BMNOT;
                    break;
                case INP:
                    if (circuit.comps[i].a)
                        bitmap = BMSWITCHON;
                    else
                        bitmap = BMSWITCHOFF;
                    break;
                case LED:
                    if (circuit.comps[i].a)
                        bitmap = BMLEDON;
                    else 
                        bitmap = BMLEDOFF;
                    break;
                default:
                    continue;
            }    
            gb.display.drawBitmap(
                    circuit.comps[i].x - camera.x,
                    circuit.comps[i].y - camera.y,
                    bitmap);
                // Drawing wires
            int mono_inp = 0;
            if (circuit.comps[i].id == LED)
            {
                mono_inp = 3;
            }
            if (circuit.comps[i].pr_a)
            {
                gb.display.drawLine(
                        circuit.comps[i].x - camera.x,
                        circuit.comps[i].y + 5 + mono_inp - camera.y,
                        circuit.comps[i].pr_a->x + 16 - camera.x,
                        circuit.comps[i].pr_a->y + 8 - camera.y);

            }
            if (circuit.comps[i].pr_b)
            {
                gb.display.drawLine(
                        circuit.comps[i].x - camera.x,
                        circuit.comps[i].y + 10 - camera.y,
                        circuit.comps[i].pr_b->x + 16 - camera.x,
                        circuit.comps[i].pr_b->y + 8 - camera.y);
            }
        }
    }
}

void draw_ui() {
    gb.display.drawBitmap(
            LCDWIDTH/2 - 2,
            LCDHEIGHT/2 - 2,
            BMCURS);
    gb.display.setColor(WHITE);
    gb.display.fillRect(LCDWIDTH - 16, 0, 16, LCDHEIGHT); 
    gb.display.setColor(BLACK);
    gb.display.drawFastVLine(LCDWIDTH - 17, 0, LCDHEIGHT);
}

void get_inputs() {
    // Camera movements
    if (gb.buttons.repeat(BTN_UP, CAMERA_SPEED))
        camera.y -= 1;
    if (gb.buttons.repeat(BTN_DOWN, CAMERA_SPEED))
        camera.y += 1;
    if (gb.buttons.repeat(BTN_LEFT, CAMERA_SPEED))
        camera.x -= 1;
    if (gb.buttons.repeat(BTN_RIGHT, CAMERA_SPEED))
        camera.x += 1;

    // Camera position clamping
    camera.x = max(-(LCDWIDTH/2), camera.x);
    camera.y = max(-(LCDHEIGHT/2), camera.y);
    
}

void place_comp(byte id){
    int i = 0;
    for (; i < circuit.nbcomps; ++i)
        if (circuit.comps[i].id == NULLCOMP) break; 
    circuit.comps[i].id = id;
    circuit.comps[i].x = camera.x + LCDWIDTH/2 - 8;
    circuit.comps[i].y = camera.y + LCDHEIGHT/2 - 8;
}

void place_wire(){
    static bool placing_wire;
    static struct Comp * pin_wire;

    if (!placing_wire)
    {
        for (int i = 0; i < 64; ++i) 
        {
            if (gb.collidePointRect(camera.x + LCDWIDTH/2,
                        camera.y + LCDHEIGHT/2,
                        circuit.comps[i].x, circuit.comps[i].y,
                        16,16))
            {
                if (gb.collidePointRect(camera.x + LCDWIDTH/2,
                            camera.y + LCDHEIGHT/2,
                            circuit.comps[i].x, circuit.comps[i].y,
                            16,8))
                {//a
                    pin_wire = circuit.comps[i].pr_a;
                }
                if (gb.collidePointRect(camera.x + LCDWIDTH/2,
                            camera.y + LCDHEIGHT/2,
                            circuit.comps[i].x, circuit.comps[i].y + 8,
                            16,8))
                {//b
                    pin_wire = circuit.comps[i].pr_b;
                }
                placing_wire = true;   
                break;
            }
        }   
    }
    else
    {
        for (int i = 0; i < 64; ++i) 
        {
            if (gb.collidePointRect(camera.x + LCDWIDTH/2,
                        camera.y + LCDHEIGHT/2,
                        circuit.comps[i].x, circuit.comps[i].y,
                        16,16))
            {
                * pin_wire = circuit.comps[i];
                placing_wire = false;
            }

        }
    }
}
