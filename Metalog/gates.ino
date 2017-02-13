#define NOT 1
#define OR 2
#define AND 3
#define NOR 4
#define NAND 5
#define XOR 6

typedef struct 
{
  byte id;
  int x;
  int y;
  bool a = false;
  bool b = false;
} Gate;

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

bool bool_output (Gate *gate)
{
  switch (gate->id)
  {
    case NOT:
      return bool_not (gate->a);
    break;
    case OR:
      return bool_or (gate->a, gate->b);
    break;
    case AND:
      return bool_and (gate->a, gate->b);
    break;
    case NOR:
      return bool_nor (gate->a, gate->b);
    break;
    case NAND:
      return bool_nand (gate->a, gate->b);
    break;
    case XOR:
      return bool_xor (gate->a, gate->b);    
    break;
    default:
      return false;
  }
}
