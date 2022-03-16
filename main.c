#include <stdio.h>
#include "sorts/sorts.h"
#include "assert.h"


void timeExperiment() {
    // описание функций сортировки
    SortFunc sorts[] = {
            {selectionSort,    " selectionSort "},
            {insertionSort,    " insertionSort "},
            {shellSort,        " shellSort "},
            {hibbardShellSort, " hibbardShellSort "},
            {smartBubbleSort,  " dumbBubbleSort "},
            {combSort, " combSort "},
            // вы добавите свои сортировки
    };
    const unsigned FUNCS_N = ARRAY_SIZE(sorts);

// описание функций генерации
    GeneratingFunc generatingFuncs[] = {
// генерируется случайный массив
            {generateRandom,          " random "},
// генерируется массив 0, 1, 2, ..., n - 1
            {generateOrdered,         " ordered "},
// генерируется массив n - 1, n - 2, ..., 0
            {generateOrderedBackward, " orderedBackwards "}
    };
    const unsigned CASES_N = ARRAY_SIZE(generatingFuncs);

// запись статистики в файл
    for (size_t size = 10000; size <= 100000; size += 10000) {
        printf(" - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -\n");
        printf(" Size : %d\n", size);
        for (int i = 0; i < FUNCS_N; i++) {
            for (int j = 0; j < CASES_N; j++) {
                // генерация имени файла
                static char filename[128] = "SortTime";
                sprintf(filename, "%s_%s_time ",
                        sorts[i].name, generatingFuncs[j].name);
                checkTime(sorts[i].sort,
                          generatingFuncs[j].generate,
                          size, filename);
            }
        }
        printf("\n");
    }
}

void comparisonsExperiment() {
    // описание функций сортировки
    SortFunc_C sorts[] = {
            {getComparisonsSelectionSort,    " selectionSort "},
            {getComparisonsInsertionSort,    " insertionSort "},
            {getComparisonsShellSort,        " shellSort "},
            {getComparisonsHibbardShellSort, " hibbardShellSort "},
            {getComparisonsSmartBubbleSort,  " smartBubbleSort "},
            {getComparisonsCombSort, " combSort "},
            {getComparisonsDumbBubbleSort, " dumbBubbleSort "}
            // вы добавите свои сортировки
    };
    const unsigned FUNCS_N = ARRAY_SIZE(sorts);

// описание функций генерации
    GeneratingFunc generatingFuncs[] = {
// генерируется случайный массив
            {generateRandom,          " random "},
// генерируется массив 0, 1, 2, ..., n - 1
            {generateOrdered,         " ordered "},
// генерируется массив n - 1, n - 2, ..., 0
            {generateOrderedBackward, " orderedBackwards "}
    };
    const unsigned CASES_N = ARRAY_SIZE(generatingFuncs);

// запись статистики в файл
    for (size_t size = 10000; size <= 100000; size += 10000) {
        printf(" - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -\n");
        printf(" Size : %d\n", size);
        for (int i = 0; i < FUNCS_N; i++) {
            for (int j = 0; j < CASES_N; j++) {
                // генерация имени файла
                static char filename[128] = "Comparisons";
                sprintf(filename, "%s_%s_comparisons ",
                        sorts[i].name, generatingFuncs[j].name);
                checkComparisons(sorts[i].sort,
                          generatingFuncs[j].generate,
                          size, filename);
            }
        }
        printf("\n");
    }
}


void test_isOrdered() {
    int array1[5] = {1, 1, 1, 1, 1};
    int array2[5] = {1, 2, 3, 4, 5};
    int array3[5] = {1, 8, 2, 6, 3};
    assert(isOrdered(array1, 5) and isOrdered(array2, 5) and !isOrdered(array3, 5));
}

void test_generation() {
    size_t size = 1000;
    int array[size];
    generateOrdered(array, size);
    assert(isOrdered(array, size));
    generateOrderedBackward(array, size);
    assert(!isOrdered(array, size));
    generateRandom(array, size);
    assert(!isOrdered(array, size));
}

void test_swap_smokeTest() {
    int a = 42;
    int b = 69;
    swap(&a, &b);
    assert(a == 69 and b == 42);
}

void test_dumbBubbleSort_smokeTest() {
    int array[100];
    generateRandom(array, 100);
    dumbBubbleSort(array, 100);
    assert(isOrdered(array, 100));
}

void test_smartBubbleSort_smokeTest() {
    int array[100];
    generateRandom(array, 100);
    smartBubbleSort(array, 100);
    assert(isOrdered(array, 100));
}

// You have awakened an ancient evil
void test_bogosort_loooooooooooooooooooooooooongTest() {
    int array[13];
    generateRandom(array, 13);
    bogoSort(array, 13);
    assert(isOrdered(array, 13));
}

void test_insertionSort_smokeTest() {
    int array[100];
    generateRandom(array, 100);
    insertionSort(array, 100);
    assert(isOrdered(array, 100));
}

void test_selectionSort_smokeTest() {
    int array[100];
    generateRandom(array, 100);
    selectionSort(array, 100);
    assert(isOrdered(array, 100));
}

void test_combSort_smokeTest() {
    int array[100];
    generateRandom(array, 100);
    combSort(array, 100);
    assert(isOrdered(array, 100));
}

void test_ShellSort_smokeTest() {
    int array[100];
    generateRandom(array, 100);
    shellSort(array, 100);
    assert(isOrdered(array, 100));
}

void test_HibardShellSort_smokeTest() {
    int array[10];
    generateRandom(array, 10);
    hibbardShellSort(array, 10);
    assert(isOrdered(array, 10));
}


void test() {
    test_isOrdered();
    test_generation();
    test_swap_smokeTest();
    test_dumbBubbleSort_smokeTest();
    test_smartBubbleSort_smokeTest();
    //test_bogosort_loooooooooooooooooooooooooongTest();
    test_insertionSort_smokeTest();
    test_selectionSort_smokeTest();
    test_combSort_smokeTest();
    test_ShellSort_smokeTest();
    test_HibardShellSort_smokeTest();
}

int main() {
    timeExperiment();

    return 0;
}

