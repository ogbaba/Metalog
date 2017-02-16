void draw_circuit() {
    for (unsigned i=0; i < circuit.nbcomps; ++i) {
        gb.display.drawRect(circuit.comps[i].x - camera.x,
                            circuit.comps[i].y - camera.y,
                            3, 3);
    }
}

void get_inputs() {
    // Camera movements
    if (gb.buttons.pressed(BTN_UP))
        camera.y -= CAMERA_SPEED;
    if (gb.buttons.pressed(BTN_DOWN))
        camera.y += CAMERA_SPEED;
    if (gb.buttons.pressed(BTN_LEFT))
        camera.x -= CAMERA_SPEED;
    if (gb.buttons.pressed(BTN_RIGHT))
        camera.x += CAMERA_SPEED;

    // Camera position clamping
    camera.x = max(0, camera.x);
    camera.y = max(0, camera.y);
}
