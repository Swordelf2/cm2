#include <stdio.h>
#include <stdlib.h>

enum
{
    ARG_EXPECT = 1 + 4
};

void
Cauchy(double (*f)(double, double),
        double x0,
        double y0,
        double arr[], /* of size 2 * n + 1 */
        int n,
        double h);

double
f1(double x, double y);

double
y1(double x);

double
f2(double x, double y);

double
y2(double x);

int
main(int argc, char *argv[])
{
    double (*y)(double) = y2;
    double (*f)(double, double) = f2;

    if (argc == 1) {
        printf("Usage: %s [x0] [y0] [n] [h]\n", argv[0]);
        exit(1);
    }
    if (argc < ARG_EXPECT) {
        fprintf(stderr, "Too few arguments\n");
        exit(1);
    }

    double x0 = strtod(argv[1], NULL);
    double y0 = strtod(argv[2], NULL);
    int n = strtol(argv[3], NULL, 0);
    double h = strtod(argv[4], NULL);

    double *arr = calloc(2 * n + 1, sizeof(*arr));
    Cauchy(f, x0, y0, arr, n, h);
    printf("%12s%12s%12s%12s\n",
            "X",
            "Y calc",
            "Y real",
            "Difference");
    double x_first = x0 - n * h;
    for (int i = 0; i < 2 * n + 1; ++i) {
        double xi = x_first + i * h;
        double yi = y(xi);
        printf("%12.6f%12.6f%12.6f%12.6f\n",
                xi,
                arr[i],
                yi,
                arr[i] - yi);
    }
    return 0;
}
       
void
Cauchy(double (*f)(double, double),
        double x0,
        double y0,
        double arr[],
        int n,
        double h)
{
    // arr[i] = y(x0 - nh + ih)
    double *mid = arr + n;
    arr[n + 1] = y0;
    for (int i = 0; i < n; ++i) {
        // Calculate y_(i+1)
        double xi = x0 + h * i;
        double xn = x0 + h * (i + 1); // x_next ~ x_(i+1)
        double yn_rude = mid[i] + f(xi, mid[i]); // y_next ~ y_(i+1)
        double yn = mid[i] + (f(xi, mid[i]) + f(xn, yn_rude)) * h * 0.5f;
        mid[i + 1] = yn;
    }
    for (int i = 0; i < n; ++i) {
        double xi = x0 - h * i;
        double xn = x0 - h * (i + 1);
        double yn_rude = mid[i] - f(xi, mid[i]);
        double yn = mid[-i] - (f(xi, mid[-i]) + f(xn, yn_rude)) * h * 0.5f;
        mid[-(i + 1)] = yn;
    }
}
