#include <math.h>

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
