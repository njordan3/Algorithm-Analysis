#include <stdio.h>

int main()
{
    int array[] = { 12, 51, 532, 63, 93, 1, 42, 52, 73, 74, 23, 761, 12, 65 };
    int arraySize = sizeof(array) / sizeof(array[0]);
    int largestIndex = 0;
    for (int i = 1; i < arraySize; i++) {
        if (array[i] > array[largestIndex]) {
            largestIndex = i;
        }
    }
    printf("The largest integer is %i. It was found at index: %i\n", 
            array[largestIndex], largestIndex);

    return 0;
}
