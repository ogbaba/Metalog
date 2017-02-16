void save_circuit(struct Save save, struct Circuit circuit, byte savenb)
{
    save.circuits[savenb] = circuit;
}

void save_game(struct Save * save)
{
    for (unsigned i = 0; i<sizeof(&save); ++i)
        EEPROM.write(i,((uint8_t*)&save)[i]);
}

void restore_game(struct Save * save)
{
    for (unsigned i=0; i<sizeof(&save); ++i)
        ((uint8_t*)&save)[i] = EEPROM.read(i);
}
