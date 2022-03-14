//
// Created by Donpad on 11.03.2022.
//

#ifndef UNTITLED_SORTS_H
#define UNTITLED_SORTS_H

# include <stdlib.h>
# include <stdio.h>
# include <stdbool.h>
# include <time.h>
# include "iso646.h"

#define ARRAY_SIZE(a) sizeof(a) / sizeof(a[0]);

# define TIME_TEST(testCode, time) {\
 clock_t start_time = clock();\
 testCode\
    clock_t end_time = clock();\
 clock_t sort_time = end_time - start_time;\
 time = (double) sort_time / CLOCKS_PER_SEC;\
  }

typedef struct SortFunc {
    void (*sort )(int *a, size_t n); // указатель на функцию сортировки
    char name[64];                   // имя сортировки используемое при выводе
} SortFunc;

typedef struct GeneratingFunc {
    void (*generate )(int *a, size_t n); // указатель на функцию генерации последовательности.
    char name[64];                       // имя генератора, используемое при выводе
} GeneratingFunc;

double getTime();

void checkTime(void (*sortFunc)(int *, size_t),
               void (*generateFunc)(int *, size_t),
               size_t size, char *experimentName);

void generateOrdered(int *a, size_t n);

void generateOrderedBackward(int *a, size_t n);

void generateRandom(int *a, size_t n);

int isOrdered(int *a, size_t n);

void swap(int *a, int *b);

void dumbBubbleSort(int *a, size_t n);

void smartBubbleSort(int *a, size_t n);

void randomSwap(int *a, size_t n);

void bogoSort(int *a, size_t n);

void insertionSort(int *a, size_t n);

void selectionSort(int *a, size_t n);

void combSort(int *a, size_t n);

void shellSort(int *a, size_t n);

void hibbardShellSort(int *const a, size_t n);

void radixSort(int *a, size_t n);

#endif //UNTITLED_SORTS_H
