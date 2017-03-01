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
    bool out;
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
            out = bool_not (a);
            break;
        case OR:
            out = bool_or (a, b);
            break;
        case AND:
            out = bool_and (a, b);
            break;
        case NOR:
            out = bool_nor (a, b);
            break;
        case NAND:
            out = bool_nand (a, b);
            break;
        case XOR:
            out = bool_xor (a, b);
            break;
        default:
            out = a;
    }
    comp->a = out;
    return out;
}

void update_outputs (struct Comp *comps)
{
    for (int i = 0; i < MAXCOMP; ++i)
    {
        update_output(comps + i);
    }
}
