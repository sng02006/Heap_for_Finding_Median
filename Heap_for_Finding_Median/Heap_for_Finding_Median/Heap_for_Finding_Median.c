/*Reheap_Up_Max, Reheap_Up_Min, Reheap_Down_Max, Reheap_Down_Min
 - Richard F. Gilberg & Behrouz A. Forouzan, Data Structure : A Pseudocode Approach with C, CENGAGE Learning(2005), P405-P407*/

//////////////////////////////////////////////////////////////////
// If you have referred any code, leave the comments like this
// to avoid "COPY"
// SOURCE for heapify: https://www.geeksforgeeks.org/heap-sort/
///////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MEASURE_TIME	// to measure execution time
// from GJANG: not sure if the time measurement code works with Windows
// If it works, execution time will be printed.
// Otherwise, comment out the line "#define MEASURE_TIME" and compile again.

/////////////////////////////////////////////////////////////////////
// to compute execution time in seconds
/////////////////////////////////////////////////////////////////////
#ifdef MEASURE_TIME
#include<time.h>
#endif

///////////////////////////////////////////////////////////////////
// function to find median using min heap and max heap
// to find median value from an array, use the following heap architecture
// 1) store all the data to heap L and heap R
// 2) all values in L < any value in R
// 3) if the number of total items is N,
//   odd  N: number of items in L = N/2+1, number of items in R = N/2
//   even N: number of items in L = number of items in R = N/2
//     i.e. n_L = n_R or n_L = n_R+1
// 4) keep L as max heap, keep R as min heap, then the median is root(L)
//   *in many definitions of median, when N is even, the median is
//    defined as an average of item N/2 and item N/2+1, but we assume
//    it is root(L) (item ceiling(N/2)) to make the problem simple
//   *all values in L <= root(L), so it also satisfies definition of median
//   *Reference:
// https://www.quora.com/How-do-you-find-the-median-from-a-set-of-even-numbers
// https://www.dkfindout.com/us/math/averages/more-about-medians/
//
// What to do:
// 1) Implement
//    Heap4Median_AddItem(int L[], int *n_L, int R[], int *n_R, int value)
//    to add a value to L and R
//    heaps L and R should satisfy the above conditions
// 2) Implement
//    Heap4Median_Build(int A[], int N, int L[], int *n_L, int R[], int *n_R)
//    For an unsorted array, it builds heaps L and R from empty heaps
//    A: size N array
//    L: size ceil(N/2) array,  R: size floor(N/2) array
//    the array memory should be allocated in advance
///////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////
// ***FILL*** if necessary, your functions can be added
/////////////////////////////////////////////////////////////////////
void Heap4Median_Build(int A[], int N, int L[], int *numL, int R[], int *numR);
void Heap4Median_Addition(int L[], int *numL, int R[], int *numR, int value);
void Reheap_Up_Max(int L[], int child);
void Reheap_Up_Min(int R[], int child);
void Reheap_Down_Max(int L[], int parent, int max);
void Reheap_Down_Min(int R[], int parent, int max);
int compare(int Lc, int Lp);
void swap(int *Lc, int *Lp);

/////////////////////////////////////////////////////////////////////
// midterm problem 1
/////////////////////////////////////////////////////////////////////
int main()
{
    int i, N;
    int *A, *L, *R;

    int l = 0, r = 0;

    int *numL = &l;
    int *numR = &r;

#ifdef MEASURE_TIME
    clock_t start, end;
    double cpu_time_used;

    start = clock();
#endif

  // 0. read input
    fscanf(stdin, "%d", &N);

  // allocate interger arrays and read input values
  // In the textbook, the array indexing is 1-based (i.e. starts with 1)
  // so this template code is written for 1-based indexing
  // (starts with 1, leaving A[0] untouched.
  // If you prefer 0-based indexing, you may modify the example code below
  // ex.) "for (i=1; i<=N; i++) " --> "for (i=0; i<N; i++) "
  // "median = L[1]; " --> "median = L[0]; "
    A = (int*)malloc(sizeof(int)*N);
    for (i=0; i<N; i++) {
        if ( fscanf(stdin, "%d", A+i) != 1 ) {
        fprintf(stderr, "cannot read integer from standard input.\n");
        free(A);
        exit(0);
    }
  }

    L = (int*)malloc(sizeof(int)*(N/2+1));
    R = (int*)malloc(sizeof(int)*(N/2+1));

    /////////////////////////////////////////////////////////////////////
    // ***FILL*** :  invoke Heap4Median_Build(...) to obtain sub-heaps L and R
    /////////////////////////////////////////////////////////////////////
    Heap4Median_Build(A, N, L, numL, R, numR);

    // output for evaluation: print median only
    fprintf(stdout,"%d\n",L[0]);

#ifdef MEASURE_TIME
    end = clock();
    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
    fprintf(stderr,">> Execution time: %.5f seconds\n",cpu_time_used);
#endif

  // free memory
    free(A);
    free(L);
    free(R);

    return 0;
}

void Heap4Median_Build(int A[], int N, int L[], int *numL, int R[], int *numR) {
    int i = 0;
    int value = 0;

    while(i < N) {
        value = A[i];
        Heap4Median_Addition(L, numL, R, numR, value);
        i++;
    }
}

void Heap4Median_Addition(int L[], int *numL, int R[], int *numR, int value)  {
    if(((*numL) + (*numR)) % 2 == 0) {
        if((*numL) == 0) {
            L[(*numL)] = value;
            (*numL)++;

            return;
        }

        if(R[0] < value) {
            L[(*numL)] = R[0];
            R[0] = value;

            Reheap_Up_Max(L, (*numL));
            Reheap_Down_Min(R, 0, (*numR));

            (*numL)++;
        }
        else {
            L[(*numL)] = value;

            Reheap_Up_Max(L, (*numL));

            (*numL)++;
        }
    }
    else {
        if(L[0] > value) {
            R[(*numR)] = L[0];
            L[0] = value;

            Reheap_Up_Min(R, (*numR));
            Reheap_Down_Max(L, 0, (*numL));

            (*numR)++;
        }
        else {
            R[(*numR)] = value;

            Reheap_Up_Min(R, (*numR));

            (*numR)++;
        }
    }
}

void Reheap_Up_Max(int L[], int child){
    int parent;

    if(child != 0) {
        parent = (child - 1) / 2;

        if(compare(L[child], L[parent])) {
            swap(L + child, L + parent);
            Reheap_Up_Max(L, parent);
        }
    }
}

void Reheap_Up_Min(int R[], int child) {
    int parent;

    if(child != 0) {
        parent = (child - 1) / 2;

        if(compare(R[parent], R[child])) {
            swap(R + child, R + parent);
            Reheap_Up_Min(R, parent);
        }
    }
}

void Reheap_Down_Max(int L[], int parent, int max) {
    int child1, child2;

    child1 = parent * 2 + 1;
    child2 = parent * 2 + 2;

    if((child1 < max) && (child2 < max)) {
        if(compare(L[child1], L[child2]) && compare(L[child1], L[parent])) {
            swap(L + child1, L + parent);
            Reheap_Down_Max(L, child1, max);
            return;
        }
        else if(!compare(L[child1], L[child2]) && compare(L[child2], L[parent])) {
            swap(L + child2, L + parent);
            Reheap_Down_Max(L, child2, max);
            return;
        }
        else {
            return;
        }
    }
    else if((child1 < max) && (child2 >= max)) {
        if(compare(L[child1], L[parent])) {
            swap(L + child1, L + parent);
            Reheap_Down_Max(L, child1, max);
            return;
        }
        else {
            return;
        }
    }
    else {
        return;
    }
}

void Reheap_Down_Min(int R[], int parent, int max) {
    int child1, child2;

    child1 = parent * 2 + 1;
    child2 = parent * 2 + 2;

    if((child1 < max) && (child2 < max)) {
        if(compare(R[child2], R[child1]) && compare(R[parent], R[child1])) {
            swap(R + child1, R + parent);
            Reheap_Down_Min(R, child1, max);
            return;
        }
        else if(!compare(R[child2], R[child1]) && compare(R[parent], R[child2])) {
            swap(R + child2, R + parent);
            Reheap_Down_Min(R, child2, max);
            return;
        }
        else {
            return;
        }
    }
    else if ((child1 < max) && (child2 >= max)) {
        if(compare(R[parent], R[child1])) {
            swap(R + child1, R + parent);
            Reheap_Down_Min(R, child1, max);
            return;
        }
        else {
            return;
        }
    }
    else {
        return;
    }
}

int compare(int Lc, int Lp) {
    if(Lc > Lp)
        return 1;
    else
        return 0;
}

void swap(int *Lc, int *Lp) {
    int temp;

    temp = *Lc;
    *Lc = *Lp;
    *Lp = temp;
}
