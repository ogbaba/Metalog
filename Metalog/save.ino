void save_circuit(struct Save save, struct Circuit circuit, byte savenb)
{
    save.circuits[savenb] = circuit;
}

void save_game()
{
    for (unsigned i = 0; i<sizeof(circuit); ++i)
        EEPROM.write(i,((uint8_t*)&circuit)[i]);
}

void restore_game(void)
{
    for (unsigned i=0; i<sizeof(circuit); ++i)
        ((uint8_t*)&circuit)[i] = EEPROM.read(i);
}
