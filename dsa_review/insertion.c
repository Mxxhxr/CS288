#include <stdio.h>

void swap(int *x, int *y) {
    int temp = *x;
    *x = *y;
    *y = temp;
}

void insertionSort(int arr[], int n) {
    int i;
    for (i = 1; i < n; i++) {
        while(i > 0 && arr[i-1] > arr[i]) {
            swap(&arr[i-1], &arr[i]);
            i -= 1;
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
    insertionSort(arr, n);
    printf("Sorted array: \n");
    print(arr, n);
    return 0;
}

