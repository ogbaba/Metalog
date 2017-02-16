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
    char * bitmap;
    char * bitmapAct;
    struct Comp * comp;
};

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
    bool a, b;
    if (comp->pr_a == NULL) 
    {
        a = comp->a;
    }
    else
    {
        a = update_output (comp->pr_a);
    }
    if (comp->pr_b == NULL)
    {
        b = comp->b;
    }
    else
    {
        b = update_output (comp->pr_b);
    }
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
            return false;
    }
}

