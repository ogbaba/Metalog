bool bool_not (bool a)
{
    return !a;
}

bool bool_or (bool a, bool b)
{
    return (a || b);
}

bool bool_and (bool a, bool b)
{
    return (a && b);
}

bool bool_nor (bool a, bool b)
{
    return !(a || b);
}

bool bool_nand (bool a, bool b)
{
    return !(a && b);
}

bool bool_xor (bool a, bool b)
{
    return (a != b);
}

bool update_output (struct Comp * comp)
{
    if (!comp) return false;
    bool a, b;
    if (!comp->pr_a)
        a = comp->a;
    else
        a = update_output (comp->pr_a);

    if (!comp->pr_b)
        b = comp->b;
    else
        b = update_output (comp->pr_b);

    switch (comp->id)
    {
        case NOT:
            return bool_not (a);
            break;
        case OR:
            return bool_or (a, b);
            break;
        case AND:
            return bool_and (a, b);
            break;
        case NOR:
            return bool_nor (a, b);
            break;
        case NAND:
            return bool_nand (a, b);
            break;
        case XOR:
            return bool_xor (a, b);
            break;
        default:
            Serial.println(a);
            return a;
    }
}

void update_outputs (struct Comp * comps [])
{
    for (int i = 0; i < MAXOUTP; ++i)
    {
        comps[i]->a = update_output(comps[i]);
    }
}
