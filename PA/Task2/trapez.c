//Author: Thomas Opitz
//Compile with gcc -o trapez trapez.c -lpthread

#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

typedef struct element_t {
    int start;
    int end;
    int N;
    int id;
} element_t;

double * result;
double a = -400;
double b = 600;

double function(double x) {
    return x * x - 5*x;
}

/**
*Calculate trapez
*/
void * calculate_trapez(void * arg) {
    element_t * element = (element_t *) arg;

    double res = 0;

    double h = (b - a) / element->N;

    int i;
    for (i = element->start + 1; i <= element->end; i++) {
        double x_i = a + (i - 1) * h;
        res += function(x_i);
    }

    result[element->id] = res;
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        printf("Usage trapez <N> <p>\n");
        return 0;
    }

    int N = atoi(argv[1]);
    int p = atoi(argv[2]);

    clock_t start = clock() / (CLOCKS_PER_SEC / 1000);

    result = malloc(p * sizeof(*result));
    pthread_t * tid = malloc(p * sizeof(*tid));
    element_t * elements = malloc(p * sizeof(*elements));
    int current = 1;

    int k;
    for (k = 0; k < p; k++) {
        elements[k].id = k;
        elements[k].N = N;
        elements[k].start = current;
        elements[k].end = (N /p) * (k + 1);

        current += (N / p);
    }

    elements[p - 1].end += (N % p) - 1;


    for (k = 0; k < p; k++) {
        pthread_create(&tid[k], NULL, &calculate_trapez, &elements[k]);
    }

    for (k = 0; k < p; k++) {
        pthread_join(tid[k], NULL);
    }

    double total_result = 0;
    double h = (b - a) / N;

    for (k = 0; k < p; k++) {
        total_result += result[k];
    }

    total_result *= 2;
    total_result += function(a);
    total_result += function(b);

    total_result *= h / 2;


    clock_t end = (clock() / (CLOCKS_PER_SEC / 1000) - start);

    printf("%f\n%ld ms\n", total_result, end);
}

