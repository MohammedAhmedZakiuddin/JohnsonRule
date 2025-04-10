#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

typedef struct washing washer;

struct washing {
    int wTime;
    int dTime;
    int arrayToSort;
};

washer *basket;

int printOutput(int n, int jBasketWt[], int jBasketDt[], int index[]) {
    int washSTime = 0;
    int DrySTime = jBasketWt[0];
    int Dend = DrySTime + jBasketDt[0];
    int i;

    for (i = 0; i < n; i++) {
        printf("%d %d %d %d %d\n", index[i], jBasketWt[i], jBasketDt[i], washSTime, DrySTime);
        washSTime = washSTime + jBasketWt[i];
        if ((washSTime + jBasketWt[i + 1]) < (DrySTime + jBasketDt[i]))
            DrySTime = DrySTime + jBasketDt[i];
        else
            DrySTime = washSTime + jBasketWt[i + 1];
        if (Dend < DrySTime && i < (n - 1)) {
            printf("Gap time from %d to %d\n", Dend, DrySTime);
        }
        if (i < (n - 1))
            Dend = DrySTime + jBasketDt[i + 1];
    }

    printf("Makespan is : %d\n", Dend);

    return 0;
}

int johnsonRule(int n, int washtime[], int drytime[]) {
    int *jBasketWt = malloc(n * sizeof(int));
    int *jBasketDt = malloc(n * sizeof(int));
    int *index = malloc(n * sizeof(int));
    int p = n - 1, o = 0, k = 0;
    int i, j;

    if (!jBasketWt || !jBasketDt || !index) {
        printf("Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }

    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            if (basket[i].arrayToSort == washtime[j]) {
                jBasketWt[o] = washtime[j];
                jBasketDt[o] = drytime[j];
                index[o] = j;
                o++;
                k++;
            }
            if (basket[i].arrayToSort == drytime[j]) {
                jBasketWt[p] = washtime[j];
                jBasketDt[p] = drytime[j];
                index[p] = j;
                p--;
                k++;
            }
        }
    }

    printOutput(n, jBasketWt, jBasketDt, index);

    free(jBasketWt);
    free(jBasketDt);
    free(index);

    return 0;
}

int numCompare(const void *x, const void *y) {
    const washer *a = x, *b = y;
    return a->arrayToSort - b->arrayToSort;
}

int theQSort(int n, int washtime[], int drytime[]) {
    qsort((void *)basket, n, sizeof(washer), numCompare);
    johnsonRule(n, washtime, drytime);
    return 0;
}

int arrayOfSort(int n, int washtime[], int drytime[]) {
    for (int i = 0; i < n; i++) {
        if (basket[i].wTime < basket[i].dTime)
            basket[i].arrayToSort = basket[i].wTime;
        else
            basket[i].arrayToSort = basket[i].dTime;
    }

    theQSort(n, washtime, drytime);
    return 0;
}

int acceptTimes(int nBaskets, FILE *fp) {
    int n = nBaskets;
    int *washtime = malloc(n * sizeof(int));
    int *drytime = malloc(n * sizeof(int));
    int i;

    if (!washtime || !drytime) {
        printf("Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }

    basket = (washer *)malloc(n * sizeof(washer));
    if (!basket) {
        printf("Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }

    for (i = 0; i < n; i++) {
        fscanf(fp, "%d", &basket[i].wTime);
        washtime[i] = basket[i].wTime;
        fscanf(fp, "%d", &basket[i].dTime);
        drytime[i] = basket[i].dTime;
    }

    arrayOfSort(n, washtime, drytime);

    free(washtime);
    free(drytime);
    free(basket);

    return 0;
}

int noOfBaskets(FILE *fp) {
    int nBaskets;
    fscanf(fp, "%d", &nBaskets);
    acceptTimes(nBaskets, fp);
    return 0;
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("Usage: %s <input file>\n", argv[0]);
        return EXIT_FAILURE;
    }

    FILE *fp = fopen(argv[1], "r");
    if (!fp) {
        printf("Error: Cannot open file %s\n", argv[1]);
        return EXIT_FAILURE;
    }

    noOfBaskets(fp);
    fclose(fp);

    return 0;
}