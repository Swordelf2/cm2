#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "func.h"

typedef double (*f_ptr) (double, double);
typedef double (*y_ptr) (double);

const f_ptr f_all[] = {f0, f1, f2, f3};
const y_ptr y_all[] = {y0, y1, y2, y3};

enum
{
    ARG_EXPECT = 1 + 5
};

void
RK_method2(f_ptr f,
        double x0,
        double y0,
        double arr[], /* of size 2 * n + 1 */
        int n,
        double h);

void
RK_method4(f_ptr f,
        double x0,
        double y0,
        double arr[], /* of size 2 * n + 1 */
        int n,
        double h);

int
main(int argc, char *argv[])
{
    if (argc == 1) {
        printf("Usage: %s [fnum] [x0] [y0] [n] [h]\n", argv[0]);
        exit(1);
    }
    if (argc < ARG_EXPECT) {
        fprintf(stderr, "Too few arguments\n");
        exit(1);
    }

    int fnum = strtol(argv[1], NULL, 0);
    double x0 = strtod(argv[2], NULL);
    double y0 = strtod(argv[3], NULL);
    int n = strtol(argv[4], NULL, 0);
    double h = strtod(argv[5], NULL);

    y_ptr y = y_all[fnum];
    f_ptr f = f_all[fnum];

    double *arr2 = calloc(2 * n + 1, sizeof(*arr2));
    double *arr4 = calloc(2 * n + 1, sizeof(*arr4));

    RK_method2(f, x0, y0, arr2, n, h);
    RK_method4(f, x0, y0, arr4, n, h);
    printf("%12s%12s%12s%12s%12s%12s\n",
            "X",
            "Y calc (II)",
            "Y calc (IV)",
            "Y real",
            "Diff (II)",
            "Diff (IV)");
    double x_first = x0 - n * h;
    for (int i = 0; i < 2 * n + 1; ++i) {
        double xi = x_first + i * h;
        double yi = y(xi);
        printf("%12.6f%12.6f%12.6f%12.6f%12.6f%12.6f\n",
                xi,
                arr2[i],
                arr4[i],
                yi,
                fabs(arr2[i] - yi),
                fabs(arr4[i] - yi));
    }

    free(arr2);
    free(arr4);
    return 0;
}
       
void
RK_method2(f_ptr f,
        double x0,
        double y0,
        double arr[],
        int n,
        double h)
{
    double *mid = arr + n;
    mid[0] = y0;
    // Go right
    for (int i = 0; i < n; ++i) {
        // Calculate y_(i+1)
        double xi = x0 + h * i;
        double xn = x0 + h * (i + 1); // x_next ~ x_(i+1)
        double yn_rude = mid[i] + f(xi, mid[i]) * h; // y_next ~ y_(i+1)
        double yn = mid[i] + (f(xi, mid[i]) + f(xn, yn_rude)) * h * 0.5f;
        mid[i + 1] = yn;
    }
    // Go left
    for (int i = 0; i < n; ++i) {
        double xi = x0 - h * i;
        double xn = x0 - h * (i + 2);
        double yn_rude = mid[-i] - f(xi, mid[-i]) * h;
        double yn = mid[-i] - (f(xi, mid[-i]) + f(xn, yn_rude)) * h * 0.5f;
        mid[-(i + 1)] = yn;
    }
}

void
RK_method4(f_ptr f,
        double x0,
        double y0,
        double arr[],
        int n,
        double h)
{
    double *mid = arr + n;
    mid[0] = y0;
    // Right
    for (int i = 0; i < n; ++i) {
        double xi = x0 + i * h;
        double yi = mid[i];
        double k1 = f(xi, yi);
        double k2 = f(xi + h * 0.5f, yi + k1 * h * 0.5f);
        double k3 = f(xi + h * 0.5f, yi + k2 * h * 0.5f);
        double k4 = f(xi + h, yi + h * k3);
        double yn = yi + 1/6.0 * h * (k1 + 2 * k2 + 2 * k3 + k4);
        mid[i + 1] = yn;
    }
    // Left
    for (int i = 0; i < n; ++i) {
        double xi = x0 - i * h;
        double yi = mid[-i];
        double k1 = f(xi, yi);
        double k2 = f(xi - h * 0.5f, yi - k1 * h * 0.5f);
        double k3 = f(xi - h * 0.5f, yi - k2 * h * 0.5f);
        double k4 = f(xi - h, yi - h * k3);
        double yn = yi - 1/6.0 * h * (k1 + 2 * k2 + 2 * k3 + k4);
        mid[-(i + 1)] = yn;
    }
}   
