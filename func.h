#ifndef FUNC_H
#define FUNC_H

double
f0(double x, double y);
// (x - x^2) * y
// (x0, y0) = (0, 1)

double
y0(double x);
// exp(-1/6 * x^2 * (-3 + 2x))


double
f1(double x, double y);
// 3 - y - x
// (x0, y0) = (0, 0)

double
y1(double x);
// 4 - x - 4exp(-x)


double
f2(double x, double y);
// -y - x^2
// (x0, y0) = (0, 10)

double
y2(double x);
// -x^2 + 2x - 2 + 12exp(-x)


double
f3(double x, double y);
// y - yx
// (x0, y0) = (0, 5)

double
y3(double x);
// 5exp(-1/2 * x(-2 + x))

#endif
