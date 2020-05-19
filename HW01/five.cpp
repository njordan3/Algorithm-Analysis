#include <stdio.h>

using namespace std;

int main()
{
    int list1[] = {2, 5, 5, 5};
    int list2[] = {2, 2, 3, 5, 5, 7};
    int size_of_list1 = sizeof(list1) / sizeof(list1[0]);
    int size_of_list2 = sizeof(list2) / sizeof(list2[0]);
    int list3[size_of_list1];   // the size of the resulting list will be at 
                                // most the size of the smallest list
    int common_elements = 0;
    for (int i = 0; i < size_of_list1; i++) {
        for (int j = 0; j < size_of_list2; j++) {
            if (list1[i] == list2[j]) {
                list3[common_elements] = list1[i];    // copy common elements to list3
                list2[j] = -1;  // replace with -1 so we don't get repeats
                common_elements++;
                break;
            }   
        }
    }
    for (int i = 0; i < common_elements; i++) {
        printf("%i ", list3[i]);
    }
    printf("\n");

    return 0;
}
