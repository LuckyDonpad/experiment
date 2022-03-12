//
// Created by Donpad on 11.03.2022.
//

#ifndef UNTITLED_SORTS_H
#define UNTITLED_SORTS_H

# include <stdlib.h>
# include <stdio.h>
# include <stdbool.h>
# include <time.h>

# define TIME_TEST (testCode, time) { \
 clock_t start_time = clock(); \
 testCode \
    clock_t end_time = clock(); \
 clock_t sort_time = end_time - start_time; \
 time = (double) sort_time / CLOCKS_PER_SEC; \
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

#endif //UNTITLED_SORTS_H
