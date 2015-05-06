//Author: Thomas Opitz
//Compile with gcc -o trapez_sequential trapez_sequential.c

#include <time.h>
#include <stdio.h>
#include <stdlib.h>

double function(double x) {
    return x * x - 5*x;
}

/**
*Calculate trapez
*/
double calculate_trapez(double N) {
    double result = 0;

    double a = -400;
    double b = 600;

    double h = (b - a) / N;

    int i;
    for (i = 2; i < N; i++) {
        double x_i = a + (i - 1) * h;
        result += function(x_i);
    }

    result *= 2;
    result += function(a);
    result += function(b);

    result *= h / 2;

    return result;
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage trapez <N>\n");
        return 0;
    }

    int N = atoi(argv[1]);

    clock_t start = clock() / (CLOCKS_PER_SEC / 1000);

    double total_result = 0;


    total_result += calculate_trapez(N);


    clock_t end = (clock() / (CLOCKS_PER_SEC / 1000) - start);

    printf("%f\n%ld ms\n", total_result, end);
}

