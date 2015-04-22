//Author: Thomas Opitz
//Compile with: gcc -lpthread -lm

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct element_t {
    float * sub_vector;
    int length;
    int id;
} element_t;

float * vector;
float * result;

/**
*Calculate part of the Euclidean norm
*/
void * calculate_euclidean(void * arg) {
    element_t * element = (element_t *) arg;

    float sum = 0;

    int k;
    for (k = 0; k < element->length; k++) {
        sum += element->sub_vector[k] * element->sub_vector[k];
    }

    result[element->id] = sum;
}


int main(int argc, char *argv[]) {
    if (argc != 3) {
        printf("Usage euclidean <n> <p>\n");
        return 0;
    }
    //Generate random seed
    srand (time(NULL));

    int n = atoi(argv[1]);
    int p = atoi(argv[2]);

    //Create vector for calculation
    vector = malloc(n * sizeof(*vector));

    //Create result structure, to store results of single threads
    result = malloc(p * sizeof(*result));

    //Fill with numbers
    int t;
    for (t = 0; t < n; t++) {
        vector[t] = rand() % 1000000;
    }

    //Calculate norm sequential for comparison
    float sequential_norm = 0;
    for (t = 0; t < n; t++) {
        sequential_norm += vector[t] * vector[t];
    }
    sequential_norm = sqrt(sequential_norm);


    pthread_t * tid = malloc(p * sizeof(*tid));
    element_t * elements = malloc(p * sizeof(*elements));

    //Initialize parameters for threads
    int k;
    for (k = 0; k < p; k++) {
        elements[k].sub_vector = vector;
        elements[k].length = (n / p);
        elements[k].id = k;

        vector += (n / p);
    }

    elements[p - 1].length += (n % p);

    for (k = 0; k < p; k++) {
        pthread_create(&tid[k], NULL, &calculate_euclidean, &elements[k]);
    }

    for (k = 0; k < p; k++) {
        pthread_join(tid[k], NULL);
    }

    //Reduce result of threads
    float result_sum = 0;
    for (k = 0; k < p; k++) {
        result_sum += result[k];
    }

    printf("Sequential Euclidean Norm: %f\n", sequential_norm);
    printf("Parallel Euclidean Norm: %f\n", sqrt(result_sum));
}

