Kod do porównania trzech różnych metod interpolacji na funkcji źródłowej 𝒚 =
𝟏
𝟏+𝟐𝟓𝒙
𝟐
.
Kod programu:
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <gsl/gsl_errno.h>
#include <gsl/gsl_spline.h>
#include <gsl/gsl_interp.h>
static double fun(double x)
{
return 1.0 / (1.0 + 25.0 * x * x);
}
int main(void)
{
double x_nodes[] = {-1.0, -0.5, 0.0, 0.5, 1.0};
int n_nodes = sizeof(x_nodes) / sizeof(x_nodes[0]);
double *x, *y;
double xi, yi;
FILE *linear_output, *cspline_output, *akima_output, *source_output;
x = malloc(n_nodes * sizeof(double));
y = malloc(n_nodes * sizeof(double));
if (!x || !y)
{
fprintf(stderr, "Memory allocation failed\n");
return 1;
}
linear_output = fopen("linear.txt", "w");
cspline_output = fopen("cspline.txt", "w");
akima_output = fopen("akima.txt", "w");
source_output = fopen("source.txt", "w");
if (!linear_output || !cspline_output || !akima_output || !source_output)
{
fprintf(stderr, "File opening failed\n");
free(x);
free(y);
return 1;
}
for (int i = 0; i < n_nodes; ++i)
{
x[i] = x_nodes[i];
y[i] = fun(x[i]);
fprintf(source_output, "%g %g\n", x[i], y[i]);
}
// Interpolacja liniowa
{
gsl_interp_accel *acc = gsl_interp_accel_alloc();
gsl_spline *spline = gsl_spline_alloc(gsl_interp_linear, n_nodes);
gsl_spline_init(spline, x, y, n_nodes);
for (xi = -1.0; xi <= 1.0; xi += 0.01)
{
yi = gsl_spline_eval(spline, xi, acc);
fprintf(linear_output, "%g %g\n", xi, yi);
}
gsl_spline_free(spline);
gsl_interp_accel_free(acc);
}
// Interpolacja Cubic Spline
{
gsl_interp_accel *acc = gsl_interp_accel_alloc();
gsl_spline *spline = gsl_spline_alloc(gsl_interp_cspline, n_nodes);
gsl_spline_init(spline, x, y, n_nodes);
for (xi = -1.0; xi <= 1.0; xi += 0.01)
{
yi = gsl_spline_eval(spline, xi, acc);
fprintf(cspline_output, "%g %g\n", xi, yi);
}
gsl_spline_free(spline);
gsl_interp_accel_free(acc);
}
// Interpolacja Akima
{
gsl_interp_accel *acc = gsl_interp_accel_alloc();
gsl_spline *spline = gsl_spline_alloc(gsl_interp_akima, n_nodes);
gsl_spline_init(spline, x, y, n_nodes);
for (xi = -1.0; xi <= 1.0; xi += 0.01)
{
yi = gsl_spline_eval(spline, xi, acc);
fprintf(akima_output, "%g %g\n", xi, yi);
}
gsl_spline_free(spline);
gsl_interp_accel_free(acc);
}
fclose(linear_output);
fclose(cspline_output);
fclose(akima_output);
fclose(source_output);
free(x);
free(y);
return 0;
}
Kod do stworzenia wykresu:
set terminal png size 800,600
set output 'interpolacja3.png'
set title 'Porownanie metod interpolacji funkcji y = 1/(1 + 25x^2)'
set xlabel 'x'
set ylabel 'y'
set grid
set key outside
set xrange [-1:1]
set yrange [0:1]
plot 'source.txt' using 1:2 title 'Funkcja zrodlowa' with lines linecolor rgb 'black', \
 'linear.txt' using 1:2 title 'Interpolacja Liniowa' with lines linecolor rgb 'blue', \
 'cspline.txt' using 1:2 title 'Interpolacja Cubic Spline' with lines linecolor rgb 'orange', \
 'akima.txt' using 1:2 title 'Interpolacja Akima' with lines linecolor rgb 'green