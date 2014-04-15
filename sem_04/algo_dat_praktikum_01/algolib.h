#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <string.h>

#ifndef __ALGOLIB__
#define __ALGOLIB__ 

void startTimer();
double readTimer();
void printData(int*, int);
int* generateDataAscDesc(int, int, int);
int* generateDataAscending(int, int);
int* generateDataDescending(int, int);
int* generateDataRandom(int, int, int);
void swapElementA(int*, int, int);
void swapElement(int*, int*);
void merge(int*, int, int, int, int);
void mergesort_r(int, int, int*);
int* bubbleSort(int*, int);
int* mergeSort(int*, int);
int compare(const void*, const void*);
int* quickSort(int*, int);

#endif
