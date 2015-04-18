//Author: Thomas Opitz
//Compile with: gcc -lpthread

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct element_t {
    float * sub_vector;
    int length;
    int id;
} element_t;

float * vector;
float * result;

/**
*Calculate part of the maximum norm
*/
void * calculate_maximum(void * arg) {
    element_t * element = (element_t *) arg;

    float maximum = 0;

    int k;
    for (k = 0; k < element->length; k++) {
        if (element->sub_vector[k] > maximum) {
            maximum = element->sub_vector[k];
        }
    }

    result[element->id] = maximum;
}


int main(int argc, char *argv[]) {
    if (argc != 3) {
        printf("Usage maximum <n> <p>\n");
        return 0;
    }

    int n = atoi(argv[1]);
    int p = atoi(argv[2]);

    //Create vector for calculation
    vector = malloc(n * sizeof(*vector));

    //Create result structure, to store results of single threads
    result = malloc(p * sizeof(*result));

    //Fill with numbers
    int t;
    for (t = 0; t < n; t++) {
        vector[t] = t * 1;
    }

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
        pthread_create(&tid[k], NULL, &calculate_maximum, &elements[k]);
    }

    for (k = 0; k < p; k++) {
        pthread_join(tid[k], NULL);
    }

    //Reduce result of threads
    float result_maximum = 0;
    for (k = 0; k < p; k++) {
        if (result[k] > result_maximum) {
            result_maximum = result[k];
        }
    }

    printf("Maximum Norm: %f\n", result_maximum);
}

