void draw_circuit() {
    for (unsigned i=0; i < circuit.nbcomps; ++i) {
        gb.display.drawRect(circuit.comps[i].x - camera.x,
                            circuit.comps[i].y - camera.y,
                            3, 3);
    }
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
    camera.x = max(0, camera.x);
    camera.y = max(0, camera.y);
}
