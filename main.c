#include <stdio.h>
#include "sorts/sorts.h"
#include "assert.h"

#define ARRAY_SIZE(a) sizeof(a) / sizeof(a[0]);

//void timeExperiment() {
//   // описание функций сортировки
//   SortFunc sorts[] = {
//           {selectionSort, " selectionSort "},
//           {insertionSort, " insertionSort "},
//           // вы добавите свои сортировки
//   };
//   const unsigned FUNCS_N = ARRAY_SIZE(sorts);
//
// описание функций генерации
//  GeneratingFunc generatingFuncs[] = {
// генерируется случайный массив
//        {generateRandomArray,      " random "},
// генерируется массив 0, 1, 2, ..., n - 1
//      {generateOrderedArray,     " ordered "},
// генерируется массив n - 1, n - 2, ..., 0
//    {generateOrderedBackwards, " orderedBackwards "}
//};
//const unsigned CASES_N = ARRAY_SIZE(generatingFuncs);

// запись статистики в файл
//for (size_t size = 10000; size <= 100000; size += 10000) {
//    printf(" - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -\n");
//    printf(" Size : %d\n", size);
//    for (int i = 0; i < FUNCS_N; i++) {
//        for (int j = 0; j < CASES_N; j++) {
//            // генерация имени файла
//            static char filename[128];
//            sprintf(filename, "%s_%s_time ",
//                    sorts[i].name, generatingFuncs[j].name);
//  checkTime(sorts[i].sort,
//              generatingFuncs[j].generate,
//                size, filename);
//    }
//  }
//    printf("\n");
//  }
//}

void test_isOrdered() {
    int array1[5] = {1, 1, 1, 1, 1};
    int array2[5] = {1, 2, 3, 4, 5};
    int array3[5] = {1, 8, 2, 6, 3};
    assert(isOrdered(array1, 5) and isOrdered(array2, 5) and !isOrdered(array3, 5));
}

void test_generation() {
    size_t size = 1000;
    int array[size];
    generateOrdered(array,size);
    assert(isOrdered(array, size));
    generateOrderedBackward(array, size);
    assert(!isOrdered(array, size));
    generateRandom(array, size);
    assert(!isOrdered(array, size));
}

void test() {
    test_isOrdered();
    test_generation();
}

int main() {
    test();
}

