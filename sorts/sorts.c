//
// Created by Donpad on 11.03.2022.
//

#include "sorts.h"
#include <math.h>


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
        char filename[256] = "SortTime";
        //TODO не понял до конца что такое name из методички, решил заменить на название имя файла
        sprintf(filename, "./data/%s.csv", experimentName);
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

void checkComparisons(long long (*sortFunc)(int *, size_t),
                      void (*generateFunc)(int *, size_t),
                      size_t size, char *experimentName) {
    static size_t runCounter = 1;

    // генерация последовательности
    static int innerBuffer[100000];
    generateFunc(innerBuffer, size);
    printf("Run #%zu | ", runCounter++);
    printf("Name:  %s\n", experimentName);

    // замер времени
    long long comparisons = sortFunc(innerBuffer, size);

    // результаты замера
    printf("Status:  ");
    if (isOrdered(innerBuffer, size)) {
        printf("OK! Comparisons: %lld \n", comparisons);

        // запись в файл
        char filename[256] = "Comparisons";
        //TODO не понял до конца что такое name из методички, решил заменить на название имя файла
        sprintf(filename, "./data/%s.csv", experimentName);
        FILE *f = fopen(filename, "a");
        if (f == NULL) {
            printf("FileOpenError %s", filename);
            exit(1);
        }
        fprintf(f, "%zu; %lld\n", size, comparisons);
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


void combSort(int *a, size_t n) {
    size_t gap = n;
    int swapped = 1;
    while (gap > 1 || swapped) {
        if (gap > 1)
            gap /= 1.24733;
        swapped = 0;
        for (size_t i = 0, j = i + gap; j < n; ++i, ++j) {
            if (a[i] > a[j]) {
                swap(&a[i], &a[j]);
                swapped = 1;
            }
        }
    }
}

void shellSort(int *const a, size_t n) {
    for (size_t s = n / 2; s > 0; s /= 2) {
        for (int i = s; i < n; ++i) {
            for (int j = i - s; j >= 0 && a[j] > a[j + s]; j -= s)
                swap(&a[j], &a[j + s]);
        }
    }
}


/// сортировка шелла с набором чисел хиббарда, сложность О(n ^^ 3/2)
void hibbardShellSort(int *const a, size_t n) {
    int *leftBorder = a;
    int *rightBorder = a + n;
    int sz = n;
    if (sz <= 1) return;
    int step = 1;
    while (step < sz) step <<= 1;
    step >>= 1;
    step--;
    while (step >= 1) {
        for (int *i = leftBorder + step; i < rightBorder; i++) {
            int *j = i;
            int *diff = j - step;
            while (diff >= leftBorder && *diff > *j) {
                swap(diff, j);
                j = diff;
                diff = j - step;
            }
        }
        step /= 2;
    }
}


long long getComparisonsDumbBubbleSort(int *a, size_t n) {
    long long comparisons = 0;
    for (size_t i = 0; i < n - 1; ++i)
        for (size_t j = n - 1; j > i; j--) {
            comparisons++;
            if (a[j] < a[j - 1])
                swap(&a[j - 1], &a[j]);
        }
    return comparisons;
}

long long getComparisonsSmartBubbleSort(int *a, size_t n) {
    long long comparisons = 0;
    for (size_t i = 0; i < n - 1; ++i) {
        int isSwap = 0;
        for (size_t j = n - 1; j > i; j--) {
            comparisons++;
            if (a[j] < a[j - 1]) {
                swap(&a[j - 1], &a[j]);
                isSwap = 1;
            }
        }
        if (!isSwap)
            break;
    }
    return comparisons;
}

long long getComparisonsInsertionSort(int *a, size_t n) {
    long long comparisons = 0;
    for (size_t i = 1; i < n; ++i) {
        int t = a[i];
        size_t j = i;
        while (++comparisons and j > 0 && a[j - 1] > t) {
            a[j] = a[j - 1];
            j--;
        }
        a[j] = t;
    }
    return comparisons;
}

long long getComparisonsSelectionSort(int *a, size_t n) {
    long long comparisons = 0;
    for (size_t i = 0; i < n; ++i) {
        size_t indexOfMin = i;
        for (size_t j = i + 1; j < n; ++j) {
            comparisons++;
            if (a[j] < a[indexOfMin])
                indexOfMin = j;
        }
        comparisons++;
        if (indexOfMin != i)
            swap(&a[i], &a[indexOfMin]);
    }
    return comparisons;
}

long long getComparisonsCombSort(int *a, size_t n) {
    long long comparisons = 1;
    size_t gap = n;
    int swapped = 1;
    while (gap > 1 || swapped) {
        comparisons++;
        if (gap > 1)
            gap /= 1.24733;
        swapped = 0;
        for (size_t i = 0, j = i + gap; j < n; ++i, ++j) {
            comparisons++;
            if (a[i] > a[j]) {
                swap(&a[i], &a[j]);
                swapped = 1;
            }
        }
    }
    return comparisons;
}

long long getComparisonsShellSort(int *a, size_t n) {
    long long comparisons = 0;
    for (size_t s = n / 2; s > 0; s /= 2) {
        for (int i = s; i < n; ++i) {
            for (int j = i - s; ++comparisons and j >= 0 && a[j] > a[j + s]; j -= s) {
                swap(&a[j], &a[j + s]);
            }
        }
    }
    return comparisons;
}

long long getComparisonsHibbardShellSort(int *a, size_t n) {
    long long comparisons = 0;
    int *leftBorder = a;
    int *rightBorder = a + n;
    int sz = n;
    if (sz <= 1) return comparisons;
    int step = 1;
    while (++comparisons and step < sz) step <<= 1;
    step >>= 1;
    step--;
    while (step >= 1) {
        for (int *i = leftBorder + step; i < rightBorder; i++) {
            int *j = i;
            int *diff = j - step;
            while (++comparisons and diff >= leftBorder && *diff > *j) {
                swap(diff, j);
                j = diff;
                diff = j - step;
            }
        }
        step /= 2;
    }
    return comparisons;
}