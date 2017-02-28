bool menu_on;
int menu_curs_x, menu_curs_y;
byte sel_tool = HAND;

void draw_circuit () {
    if (menu_on) return;
    for (unsigned i=0; i < circuit.nbcomps; ++i) {
        /*gb.display.drawRect(circuit.comps[i].x - camera.x,
          circuit.comps[i].y - camera.y,
          3, 3);
        */
        if (gb.collideRectRect(
                circuit.comps[i].x, circuit.comps[i].y, 16, 16,
                camera.x, camera.y, LCDWIDTH - 16, LCDHEIGHT))
        {
            draw_comp(
                circuit.comps[i].x - camera.x,
                circuit.comps[i].y - camera.y,
                circuit.comps[i].id,
                circuit.comps[i].a);
            // Drawing wires
            int mono_inp = 0;
            if (is_mono_inp(circuit.comps[i].id))
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

void draw_comp (int x, int y, byte id, byte state)
{
    const byte * bitmap;
    switch (id)
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
        if (state)
            bitmap = BMSWITCHON;
        else
            bitmap = BMSWITCHOFF;
        break;
    case LED:
        if (state)
            bitmap = BMLEDON;
        else
            bitmap = BMLEDOFF;
        break;
    case HAND:
        bitmap = BMHAND;
        break;
    case PLIERS:
        bitmap = BMPLIERS;
        break;
    case WIRE:
        bitmap = BMWIRE;
        break;
    default:
        return;
    }
    gb.display.drawBitmap(x,y,bitmap);
}

bool is_mono_inp (byte id)
{
    return ((id == NOT ) || (id == LED));
}
void draw_ui(void) {
    if (!menu_on)
    {
        gb.display.drawBitmap(
            LCDWIDTH/2 - 2 - 16,
            LCDHEIGHT/2 - 2,
            BMCURS);
        gb.display.setColor(WHITE);
        gb.display.fillRect(LCDWIDTH - 16, 0, 16, LCDHEIGHT);
        gb.display.setColor(BLACK);
        gb.display.drawFastVLine(LCDWIDTH - 17, 0, LCDHEIGHT);
        draw_comp (LCDWIDTH - 16, 0, sel_tool, 0);
    }
    else
    {
        for (int i = 0; i < MENUH; ++i)
        {
            for (int j = 0; j < MENUW; ++j)
            {
                draw_comp (j*16,i*16,menu_arr[i][j],0);
            }
        }
        gb.display.drawRect(menu_curs_x * 16, menu_curs_y * 16, 16,16);
    }
}

void get_inputs() {
    // Camera movements
    if (!menu_on)
    {
        if (gb.buttons.repeat(BTN_UP, CAMERA_SPEED))
            camera.y -= 1;
        if (gb.buttons.repeat(BTN_DOWN, CAMERA_SPEED))
            camera.y += 1;
        if (gb.buttons.repeat(BTN_LEFT, CAMERA_SPEED))
            camera.x -= 1;
        if (gb.buttons.repeat(BTN_RIGHT, CAMERA_SPEED))
            camera.x += 1;
        if (gb.buttons.pressed(BTN_A))
        {
            if (sel_tool == HAND)
            {
                for (int i = 0; i < MAXCOMP; ++i)
                {
                    if ((gb.collidePointRect(camera.x + LCDWIDTH/2 - 16,
                                             camera.y + LCDHEIGHT/2,
                                             circuit.comps[i].x, circuit.comps[i].y,
                                             16,16)) && (circuit.comps[i].id == INP))
                    {
                        circuit.comps[i].a = !circuit.comps[i].a;
                        update_outputs(circuit.outputs);
                    }

                }
            }
            else if (sel_tool == WIRE)
            {
                place_wire();
                update_outputs(circuit.outputs);
            }
            else if (sel_tool == PLIERS)
            {
                del_comp();
                update_outputs(circuit.outputs);
            }
            else
            {
                place_comp(sel_tool);
                update_outputs(circuit.outputs);
            }
        }
    }
    else
    {
        if ((gb.buttons.pressed(BTN_UP))&&(menu_curs_y > 0))
            menu_curs_y -= 1;
        if ((gb.buttons.pressed(BTN_DOWN))&&(menu_curs_y < MENUH - 1))
            menu_curs_y += 1;
        if ((gb.buttons.pressed(BTN_LEFT))&&(menu_curs_x > 0))
            menu_curs_x -= 1;
        if ((gb.buttons.pressed(BTN_RIGHT))&&(menu_curs_x < MENUW - 1))
            menu_curs_x += 1;
        if (gb.buttons.pressed(BTN_A))
            sel_tool = menu_arr[menu_curs_y][menu_curs_x];
    }
    if (gb.buttons.pressed(BTN_B))
    {
        menu_on = !menu_on;
    }
    if (gb.buttons.pressed(BTN_C))
    {
        save_game(&circuit);
        gb.titleScreen(F("Metalog"),BMOR);
    }
    // Camera position clamping
    camera.x = max(-(LCDWIDTH/2), camera.x);
    camera.y = max(-(LCDHEIGHT/2), camera.y);

}

void place_comp(byte id){
    int i = 0;
    // looking for empty pos in the array
    for (; i < circuit.nbcomps; ++i)
        if (circuit.comps[i].id == NULLCOMP) break;
    circuit.comps[i].id = id;
    circuit.comps[i].x = camera.x + LCDWIDTH/2 - 8 -16;
    circuit.comps[i].y = camera.y + LCDHEIGHT/2 - 8;
    for (int j = 0; j < MAXOUTP; ++j)
    {
        circuit.outputs[j] = &circuit.comps[i];
    }
    ++circuit.nbcomps;
}

void del_comp()
{
    for (int i = 0; i < MAXCOMP; ++i)
    {
        if (gb.collidePointRect(camera.x + LCDWIDTH/2 - 16,
                                camera.y + LCDHEIGHT/2,
                                circuit.comps[i].x, circuit.comps[i].y,
                                16,16))
        {
            if (((camera.y+LCDHEIGHT/2 < circuit.comps[i].y + 8) || (is_mono_inp(circuit.comps[i].id)))
                    && (circuit.comps[i].pr_a))

                {//a
                    circuit.comps[i].pr_a = NULL;
                }
            else if ((camera.y+LCDHEIGHT/2 >= circuit.comps[i].y + 8)&&(circuit.comps[i].pr_b))
                {//b
                    circuit.comps[i].pr_b = NULL;
                }
            else 
            {
                circuit.comps[i].id = NULLCOMP;
                circuit.comps[i].pr_a = NULL;
                circuit.comps[i].pr_b = NULL;
                for (int j = 0; j < MAXOUTP; ++j)
                {
                    if (circuit.outputs[i] == &circuit.comps[i])
                    {
                        circuit.outputs[i] = NULL;
                    }
                }
            }
        }
    }

}

void place_wire(){
    static bool placing_wire;
    static struct Comp * pin_wire;
    if (!placing_wire)
    {
        for (int i = 0; i < MAXCOMP; ++i)
        {
            if (gb.collidePointRect(camera.x + LCDWIDTH/2 - 16,
                                    camera.y + LCDHEIGHT/2,
                                    circuit.comps[i].x, circuit.comps[i].y,
                                    16,16))
            {
                pin_wire = &circuit.comps[i];
                placing_wire = true;
                //return placing_wire;
            }
        }
    }
    else
    {
        for (int i = 0; i < MAXCOMP; ++i)
        {
            if (gb.collidePointRect(camera.x + LCDWIDTH/2 - 16,
                                    camera.y + LCDHEIGHT/2,
                                    circuit.comps[i].x, circuit.comps[i].y,
                                    16,16))
            {
                if (circuit.comps + i == pin_wire) return;
                if ((camera.y+LCDHEIGHT/2 < circuit.comps[i].y + 8) || (is_mono_inp(circuit.comps[i].id)))
                {//a
                    circuit.comps[i].pr_a = pin_wire;
                }
                else if (camera.y+LCDHEIGHT/2 >= circuit.comps[i].y + 8)
                {//b
                    circuit.comps[i].pr_b = pin_wire;
                }
                placing_wire = false;
                pin_wire = NULL;
                //return placing_wire;
            }

        }
    }
}
