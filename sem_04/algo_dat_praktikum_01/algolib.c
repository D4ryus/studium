#include "algolib.h"

clock_t startTime, stopTime;

void startTimer() {
    startTime = clock();
}

double readTimer() {
    return (clock() - startTime) / (double)CLOCKS_PER_SEC;
}

void printData(int* d, int numElements) {
    int i = 0;
    for (i = 0; i < numElements; i++) {
        printf("%d\t", d[i]);
    }
    printf("\n");
}

int* generateDataAscDesc(int numElements, int offset, int ascdesc) {
    int* a = (int*) malloc(numElements * sizeof(int));
    int i;
    for (i = 0; i < numElements; i++) {
        if (ascdesc > 0) 
            a[i] = i + offset;
        else
            a[numElements - i - 1] = i + offset;
    }
    return a;
}

int* generateDataAscending(int numElements, int offset) {
    return generateDataAscDesc(numElements, offset, 1);
}
int* generateDataDescending(int numElements, int offset) {
    return generateDataAscDesc(numElements, offset, 0);
}

int* generateDataRandom(int numElements, int minVal, int maxVal) {
    srand (time(NULL));
    int* a = (int*) malloc(numElements * sizeof(int));
    int i;
    for (i = 0; i < numElements; i++) {
        a[i] = (int)(rand() % (maxVal - minVal) + minVal); 
    }
    return a;
}

void swapElementA(int* theArray, int first, int second) {
    int tmp = theArray[second];
    theArray[second] = theArray[first];
    theArray[first] = tmp;
}

void swapElement(int *a, int *b) {
    int tmp = *a;
    *a = *b;
    *b = tmp;
}

int* bubbleSort(int* data, int numElements) {
    int* cpyArray = (int*) malloc(numElements * sizeof(int));
    memcpy(cpyArray, data, numElements * sizeof(int));

    int n;
    int i;
    for ( n=numElements ; n > 1; n-- ) {
        for ( i=0 ; i < n-1 ; i++ ) {
            if (data[i] > data[i+1]) {
                swapElementA(cpyArray, i, i+1);
            }
        }
    }
    return cpyArray;
}

void merge(int * list, int left_start, int left_end, int right_start, int right_end){
    /* calculate temporary list sizes */
    int left_length = left_end - left_start;
    int right_length = right_end - right_start;

    /* declare temporary lists */
    int left_half[left_length];
    int right_half[right_length];

    int r = 0; /* right_half index */
    int l = 0; /* left_half index */
    int i = 0; /* list index */

    /* copy left half of list into left_half */
    for (i = left_start; i < left_end; i++, l++)
    {
        left_half[l] = list[i];
    }

    /* copy right half of list into right_half */
    for (i = right_start; i < right_end; i++, r++)
    {
        right_half[r] = list[i];
    }

    /* merge left_half and right_half back into list */
    for ( i = left_start, r = 0, l = 0; l < left_length && r < right_length; i++)
    {
        if ( left_half[l] < right_half[r] ) { list[i] = left_half[l++]; }
        else { list[i] = right_half[r++]; }
    }

    /* Copy over leftovers of whichever temporary list hasn't finished */
    for ( ; l < left_length; i++, l++) { list[i] = left_half[l]; }
    for ( ; r < right_length; i++, r++) { list[i] = right_half[r]; }
}

void mergesort_r(int left, int right, int * list){
    /* Base case, the list can be no simpiler */
    if (right - left <= 1)
    {
        return;
    }

    /* set up bounds to slice array into */
    int left_start  = left;
    int left_end    = (left+right)/2;
    int right_start = left_end;
    int right_end   = right;

    /* sort left half */
    mergesort_r( left_start, left_end, list);
    /* sort right half */
    mergesort_r( right_start, right_end, list);

    /* merge sorted halves back together */
    merge(list, left_start, left_end, right_start, right_end);
}

int* mergeSort(int* data, int numElements) {

    int* cpyArray = (int*) malloc(numElements * sizeof(int));
    memcpy(cpyArray, data, numElements * sizeof(int));

    mergesort_r(0, numElements, cpyArray);

    return cpyArray;
}

int compare (const void * a, const void * b){
  return ( *(int*)a - *(int*)b );
}

int* quickSort(int* data, int numElements) {
    int* cpyArray = (int*) malloc(numElements * sizeof(int));
    memcpy(cpyArray, data, numElements * sizeof(int));

    qsort (cpyArray, numElements, sizeof(int), compare);
    return cpyArray;
}
