#include <stdio.h>

void swap(int *x, int *y) {
    int temp = *x;
    *x = *y;
    *y = temp;
}

void selectionSort(int arr[], int n) {
    int i, j, minIndex;

    for (i=0; i < n-1; i++) {
        minIndex = i;

        for (j=i+1; j < n; j++) {
            
            if (arr[j] < arr[minIndex]) {
                minIndex = j;
            }
        }
        if (minIndex != i) {
            swap(&arr[minIndex], &arr[i]);
        }
    }
}

void print(int arr[], int size) {
    int i;
    for (i = 0; i < size; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

int main() {
    int arr[] = {3, 1, 5, 4, 2};
    int n = sizeof(arr) / sizeof(arr[0]);
    printf("UnSorted array: \n");
    print(arr, n);
    selectionSort(arr, n);
    printf("Sorted array: \n");
    print(arr, n);
    return 0;
}