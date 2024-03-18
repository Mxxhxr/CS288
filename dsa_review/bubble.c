#include <stdio.h>

void swap(int *x, int *y) {
    int temp = *x;
    *x = *y;
    *y = temp;
}

void bubbleSort(int arr[], int n) {
    int i, j;

    for (i = 0; i < n; i++) {
        for (j = 0; j < n-1; j++) {
            if (arr[j] > arr[j+1]) { // if item is greater than the next item, swap
                swap(&arr[j], &arr[j+1]);
            }
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
    int arr[] = {1, 2, 3, 4, 5};
    int n = sizeof(arr) / sizeof(arr[0]);
    printf("UnSorted array: \n");
    print(arr, n);
    bubbleSort(arr, n);
    printf("Sorted array: \n");
    print(arr, n);
    return 0;
}

