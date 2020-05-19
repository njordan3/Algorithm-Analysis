/*
	Nicholas Jordan
	CMPS3120 Algorithm Analysis
	October 10, 2019
	Lab05

	Merge sort and bubble sort code was
	copied from geeksforgeeks.org
*/

#include <iostream>
#include <fstream>
#include <chrono>
#include <stdlib.h>
#include <cstring>
#include <cmath>

using namespace std;

//global variables to record sort timings for each sort and sample size
chrono::duration<double> bubble10;
chrono::duration<double> merge10;
chrono::duration<double> bubble100;
chrono::duration<double> merge100;
chrono::duration<double> bubble1000;
chrono::duration<double> merge1000;
#ifdef LARGER_SAMPLE_SIZE
chrono::duration<double> bubble10000;
chrono::duration<double> merge10000;
#endif
//global variables to record timing differences for each sample size
double diff10 = 0.000000;
double diff100 = 0.000000;
double diff1000 = 0.000000;
#ifdef LARGER_SAMPLE_SIZE
double diff10000 = 0.000000;
#endif
//global variables to record which sort is better based on time
//the higher the value the better
int merge_is_better = 0;
int bubble_is_better = 0;

void swap(int *xp, int *yp)
{
    int temp = *xp;
    *xp = *yp;
    *yp = temp;
}

void bubbleSort(int arr[], int n)
{
    int i, j;  
    for (i = 0; i < n-1; i++) {
    	// Last i elements are already in place  
    	for (j = 0; j < n-i-1; j++) {
        	if (arr[j] > arr[j+1])
            	swap(&arr[j], &arr[j+1]);
		}
	}
}

void merge(int arr[], int l, int m, int r)
{
	int i, j, k; 
    int n1 = m - l + 1; 
    int n2 =  r - m;
    /* create temp arrays */
    int L[n1], R[n2]; 
    /* Copy data to temp arrays L[] and R[] */
    for (i = 0; i < n1; i++) 
        L[i] = arr[l + i]; 
    for (j = 0; j < n2; j++) 
        R[j] = arr[m + 1+ j]; 
    /* Merge the temp arrays back into arr[l..r]*/
    i = 0; // Initial index of first subarray 
    j = 0; // Initial index of second subarray 
    k = l; // Initial index of merged subarray 
    while (i < n1 && j < n2) { 
        if (L[i] <= R[j]) { 
            arr[k] = L[i]; 
            i++; 
        } else { 
            arr[k] = R[j]; 
            j++; 
        } 
        k++; 
    }
    /* Copy the remaining elements of L[], if there are any */
    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }
    /* Copy the remaining elements of R[], if there are any */
    while (j < n2) { 
        arr[k] = R[j]; 
        j++; 
        k++; 
    } 
}

void mergeSort(int arr[], int l, int r)
{
	if (l < r) {
        // Same as (l+r)/2, but avoids overflow for
        // large l and h
        int m = l+(r-l)/2;
        // Sort first and second halves
        mergeSort(arr, l, m);
        mergeSort(arr, m+1, r);
        merge(arr, l, m, r);
    }
}

void compareTimes()
{
    //record which sort had less time per sample size
    /*    Sample size 10    */
    if (bubble10 < merge10) {
        bubble_is_better++;
    } else if (bubble10 > merge10) {
        merge_is_better++;
    }
    diff10 = bubble10.count() - merge10.count();
    /*    Sample size 100    */
    if (bubble100 < merge100) {
        bubble_is_better++;
    } else if (bubble100 > merge100) {
        merge_is_better++;
    }
    diff100 = bubble100.count() - merge100.count();
    /*    Sample size 1000    */
    if (bubble1000 < merge1000) {
        bubble_is_better++;
    } else if (bubble1000 > merge1000) {
        merge_is_better++;
    }
    diff1000 = bubble1000.count() - merge1000.count();
#ifdef LARGER_SAMPLE_SIZE
    /*    Sample size 10000    */ 
    if (bubble10000 < merge10000) {
        bubble_is_better++;
    } else if (bubble10000 > merge10000) {
        merge_is_better++;
    }
    diff10000 = bubble10000.count() - merge10000.count();
#endif
}

int main()
{
    string file1 = "example10.txt";
    string file2 = "example100.txt";
    string file3 = "example1000.txt";
#ifdef LARGER_SAMPLE_SIZE
    string file4 = "example10000.txt";
#endif
    string line;
    ifstream myfile(file1);
    /*
		Sorting 10 elements
	*/
    if (myfile.is_open()) {
        int array1[10];
        int array2[10];
        int i = 0;
        while(getline(myfile, line)) {
            //fill two arrays for both sorts to use
            array1[i] = atoi(line.c_str());
            array2[i] = array1[i];
            i++;
        }
		//time bubble sort
		auto start = chrono::system_clock::now();
		bubbleSort(array1, 10);
		auto end = chrono::system_clock::now();
		bubble10 = end - start;
		//time merge sort
		start = chrono::system_clock::now();
		mergeSort(array2, 0, 9);
		end = chrono::system_clock::now();
		merge10 = end - start;
#ifdef DISPLAY
		printf("10 sorted integers:\n");
		for (int i = 0; i < 10; i++) {
			printf("%d ", array1[i]);
		}
		printf("\n");
#endif
    } else {
        printf("Could not open %s...\n", file1.c_str());
    }
    myfile.close();
    /*
		Sorting 100 elements
	*/
	myfile.open(file2);
    if (myfile.is_open()) {
        int array1[100];
        int array2[100];
        int i = 0;
        while(getline(myfile, line)) {
            //fill two arrays for both sorts to use
            array1[i] = atoi(line.c_str());
            array2[i] = array1[i];
			i++;
        }
		//time bubble sort
		auto start = chrono::system_clock::now();
		bubbleSort(array1, 100);
		auto end = chrono::system_clock::now();
		bubble100 = end - start;
		//time merge sort
		start = chrono::system_clock::now();
		mergeSort(array2, 0, 99);
		end = chrono::system_clock::now();
		merge100 = end - start;
#ifdef DISPLAY
		printf("\n100 sorted integers:\n");
		//print 10 elements per line
		for (int i = 0; i < 100; i++) {
			if (i%10 == 9) {
				printf("%d ", array1[i]);
				printf("\n");
			} else {
				printf("%d ", array1[i]);
			}
		}
#endif
    } else {
        printf("Could not open %s...\n", file2.c_str());
    }
    myfile.close();
    /*
		Sorting 1000 elements
	*/
	myfile.open(file3);
    if (myfile.is_open()) {
        int array1[1000];
        int array2[1000];
        int i = 0;
        while(getline(myfile, line)) {
            //fill two arrays for both sorts to use
            array1[i] = atoi(line.c_str());
            array2[i] = array1[i];
			i++;
        }
		//time bubble sort
		auto start = chrono::system_clock::now();
		bubbleSort(array1, 1000);
		auto end = chrono::system_clock::now();
		bubble1000 = end - start;
		//time merge sort
		start = chrono::system_clock::now();
		mergeSort(array2, 0, 999);
		end = chrono::system_clock::now();
		merge1000 = end - start;
#ifdef DISPLAY
		printf("\n1000 sorted integers:\n");
		//print 10 elements per line
		for (int i = 0; i < 1000; i++) {
			if (i%10 == 9) {
				printf("%d ", array1[i]);
				printf("\n");
			} else {
				printf("%d ", array1[i]);
			}
		}
#endif
    } else {
        printf("Could not open %s...\n", file3.c_str());
    }
	myfile.close();
#ifdef LARGER_SAMPLE_SIZE
    /*
		Sorting 10000 elements
	*/
	myfile.open(file4);
    if (myfile.is_open()) {
        int array1[10000];
        int array2[10000];
        int i = 0;
        while(getline(myfile, line)) {
            //fill two arrays for both sorts to use
            array1[i] = atoi(line.c_str());
            array2[i] = array1[i];
			i++;
        }
		//time bubble sort
		auto start = chrono::system_clock::now();
		bubbleSort(array1, 10000);
		auto end = chrono::system_clock::now();
		bubble10000 = end - start;
		//time merge sort
		start = chrono::system_clock::now();
		mergeSort(array2, 0, 9999);
		end = chrono::system_clock::now();
		merge10000 = end - start;
    #ifdef DISPLAY
		printf("\n10000 sorted integers:\n");
		//print 10 elements per line
		for (int i = 0; i < 10000; i++) {
			if (i%10 == 9) {
				printf("%d ", array1[i]);
                printf("\n");
			} else {
				printf("%d ", array1[i]);
			}
		}
        printf("\n");
    #endif
    } else {
        printf("Could not open %s...\n", file4.c_str());
    }
	myfile.close();
#endif
    //get time differences and which sort is better
    compareTimes();

    //format output to be neat
	printf("\t\tBubble Sort\tMergeSort\tDifference\tAdvantage\n");
    printf("--------------|------------------------");
    printf("------------------------------------\n");
	//prints a line for every possible result
    /*    Sample size 10    */
    if (diff10 < 0) {
        printf("10 elements   |\t%fs\t%fs\t%fs\tBubble Sort\n",
		    bubble10.count(), merge10.count(), abs(diff10));
    } else if (diff10 > 0) {
        printf("10 elements   |\t%fs\t%fs\t%fs\tMerge Sort\n",
		    bubble10.count(), merge10.count(), diff10);
    } else {
        printf("10 elements   |\t%fs\t%fs\t%ds\tNULL\n",
		    bubble10.count(), merge10.count(), 0);
    }
    /*    Sample size 100    */
    if (diff100 < 0) {
        printf("100 elements  |\t%fs\t%fs\t%fs\tBubble Sort\n", 
		    bubble100.count(), merge100.count(), abs(diff100));
    } else if (diff100 > 0) {
        printf("100 elements  |\t%fs\t%fs\t%fs\tMerge Sort\n", 
		    bubble100.count(), merge100.count(), diff100);
    } else {
        printf("100 elements  |\t%fs\t%fs\t%ds\tNULL\n", 
		    bubble100.count(), merge100.count(), 0);
    }
    /*    Sample size 1000    */
    if (diff1000 < 0) {
        printf("1000 elements |\t%fs\t%fs\t%fs\tBubble Sort\n", 
		    bubble1000.count(), merge1000.count(), abs(diff1000));
    } else if (diff1000 > 0) {
        printf("1000 elements |\t%fs\t%fs\t%fs\tMerge Sort\n", 
		    bubble1000.count(), merge1000.count(), diff1000);
    } else {
        printf("1000 elements |\t%fs\t%fs\t%ds\tNULL\n", 
		    bubble1000.count(), merge1000.count(), 0);
    }
#ifdef LARGER_SAMPLE_SIZE
    /*    Sample size 10000    */
    if (diff10000 < 0) {
        printf("10000 elements|\t%fs\t%fs\t%fs\tBubble Sort\n", 
		    bubble10000.count(), merge10000.count(), abs(diff10000));
    } else if (diff10000 > 0) {
        printf("10000 elements|\t%fs\t%fs\t%fs\tMerge Sort\n", 
		    bubble10000.count(), merge10000.count(), diff10000);
    } else {
        printf("10000 elements|\t%fs\t%fs\t%ds\tNULL\n", 
		    bubble10000.count(), merge10000.count(), 0);
    }
#endif

    printf("--------------|------------------------");
    printf("------------------------------------\n");
    
    //prints an analysis for every possible result
    if (merge_is_better > bubble_is_better) {
        printf("As we can see merge sort is better than bubble sort.\n");
    } else if (merge_is_better < bubble_is_better) {
        printf("As we can see bubble sort is better than merge sort.\n");
        printf("Something must be wrong...\n");
    } else {
        printf("Somehow merge sort and bubble sort had the same timings\n");
        printf("Something is definitely wrong...\n");
    }

    return 0;
}
