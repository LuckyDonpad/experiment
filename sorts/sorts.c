//
// Created by Donpad on 11.03.2022.
//

#include "sorts.h"

void checkTime(void (*sortFunc)(int *, size_t),
               void (*generateFunc)(int *, size_t),
               size_t size, char *experimentName) {
    static size_t runCounter = 1;

    // генерация последовательности
    static int innerBuffer[100000];
    generateFunc(innerBuffer, size);
    printf("Run #%zu | ", runCounter++);
    printf("Name:  %s\n", experimentName);

    // замер времени
    double time;
    TIME_TEST({
                  sortFunc(innerBuffer, size);
              }, time);

    // результаты замера
    printf("Status:  ");
    if (isOrdered(innerBuffer, size)) {
        printf("OK! Time: %.3f s.\n", time);

        // запись в файл
        char filename[256];
        //TODO не понял до конца что такое name из методички, решил заменить на название имя файла
        sprintf(filename, "./data/%s.csv", "experiment");
        FILE *f = fopen(filename, "a");
        if (f == NULL) {
            printf("FileOpenError %s", filename);
            exit(1);
        }
        fprintf(f, "%zu; %.3f\n", size, time);
        fclose(f);
    } else {
        printf("Wrong !\n");

        // вывод массива, который не смог быть отсортирован
        //  outputArray_(innerBuffer, size);

        exit(1);
    }
}

//
// Created by Donpad on 12.03.2022.
//

#include "sorts.h"

void generateOrdered(int *a, size_t n) {
    for (int i = 0; i < n; ++i) {
        a[i] = i;
    }
}

void generateOrderedBackward(int *a, size_t n) {
    for (int i = 0; i < n; ++i) {
        a[i] = (int) n - i;
    }
}

void generateRandom(int *a, size_t n) {
    for (int i = 0; i < n; ++i) {
        a[i] = rand() % n;
    }
}

int isOrdered(int *a, size_t n) {
    int isOrdered = 1;
    if (n > 1) {
        size_t i = 1;
        while (i < n and isOrdered) {
            isOrdered = a[i] >= a[i - 1];
            i++;
        }
    }
    return isOrdered;
}

void swap(int *a, int *b) {
    int tmp = *a;
    *a = *b;
    *b = tmp;
}

void dumbBubbleSort(int *a, size_t n) {
    for (size_t i = 0; i < n - 1; ++i)
        for (size_t j = n - 1; j > i; j--)
            if (a[j] < a[j - 1])
                swap(&a[j - 1], &a[j]);
}

void smartBubbleSort(int *a, size_t n) {
    for (size_t i = 0; i < n - 1; ++i) {
        int isSwap = 0;
        for (size_t j = n - 1; j > i; j--)
            if (a[j] < a[j - 1]) {
                swap(&a[j - 1], &a[j]);
                isSwap = 1;
            }
        if (!isSwap)
            break;
    }
}

void randomSwap(int *a, size_t n) {
    swap(&a[rand() % n], &a[rand() % n]);
}

void bogoSort(int *a, size_t n) {
    while (!isOrdered(a, n)) {
        randomSwap(a, n);
    }
}

void insertionSort(int *a, size_t n) {
    for (size_t i = 1; i < n; ++i) {
        int t = a[i];
        size_t j = i;
        while (j > 0 && a[j - 1] > t) {
            a[j] = a[j - 1];
            j--;
        }
        a[j] = t;
    }
}

void selectionSort(int *a, size_t n) {
    for (size_t i = 0; i < n; ++i) {
        size_t indexOfMin = i;
        for (size_t j = i + 1; j < n; ++j)
            if (a[j] < a[indexOfMin])
                indexOfMin = j;
        if (indexOfMin != i)
            swap(&a[i], &a[indexOfMin]);
    }
}



