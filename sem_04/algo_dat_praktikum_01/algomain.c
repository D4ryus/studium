#include <stdio.h>
#include <limits.h>
#include <stdlib.h>
#include "algolib.h"

#define START_VALUE 10
#define TEST_MULTIPLICATOR 2 
#define TEST_ITERATIONS 22

/* run this program using the console pauser or add your own getch, system("pause") or input loop */

int main(int argc, char *argv[]) {

    double testTimesMerge[TEST_ITERATIONS];
    double testTimesElements[TEST_ITERATIONS];
    double testTimesBubble[TEST_ITERATIONS];
    double testTimesQuick[TEST_ITERATIONS];
    int n = START_VALUE, i = 0;
    int *r;
    int *a;
    printf("int maximum: %d\n", INT_MAX);
 
    printf("N       ; Algorithm ; Data  ; Time[s]\n");
    for (i = 0; i < TEST_ITERATIONS; i++) {

        //Generate test data
        //r = generateDataDescending(n, 0);
        //r = generateDataAscending(n, 0);
        r = generateDataRandom(n, 0, n);

        //printData(r, n);
        startTimer();
        a = bubbleSort(r, n);
        testTimesBubble[i] = readTimer();
        printf("%-8d; BubbleSort; Random; %0.5f\n", n, testTimesBubble[i]);
        //printData(a, n);
        free(a);
 
        //printData(r, n);
        startTimer();
        a = mergeSort(r, n);
        testTimesMerge[i] = readTimer();
        printf("%-8d; MergeSort ; Random; %0.5f\n", n, testTimesMerge[i]);
        //printData(a, n);
        free(a);

        //printData(r, n);
        startTimer();
        a = quickSort(r, n);
        testTimesQuick[i] = readTimer();
        printf("%-8d; QuickSort ; Random; %0.5f\n", n, testTimesQuick[i]);
        //printData(a, n);
        free(a);

        testTimesElements[i] = n;
        n = n * TEST_MULTIPLICATOR;
        free(r);

    }
    system("PAUSE");
    return 0;
}
