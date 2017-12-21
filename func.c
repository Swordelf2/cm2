#include <math.h>

#include "func.h"

double
f0(double x, double y)
{
    return (x - x * x) * y;
}

double
y0(double x)
{
    return exp(-1/6.0 * x * x * (-3 + 2 * x));
}

double
f1(double x, double y)
{
    return 3 - y - x;
}

double
y1(double x)
{
    return 4 - x - 4 * exp(-x);
}

double
f2(double x, double y)
{
    return -y - x * x;
}

double
y2(double x)
{
    return -x * x + 2 * x - 2 + 12 * exp(-x);
}

double
f3(double x, double y)
{
    return y - y * x;
}

double
y3(double x)
{
    return 5 * exp(-0.5f * x * (-2 + x));
}
