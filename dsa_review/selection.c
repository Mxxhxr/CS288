#include <stdio.h>

void swap(int *x, int *y) {
    int temp = *x;
    *x = *y;
    *y = temp;
}
void print(int arr[], int size);

void selectionSort(int arr[], int n) {
    int i, j, min_idx;

    for (i = 0; i < n-1; i++) {
        min_idx = i;

        for (j = i+1; j < n; j++) {
            if (arr[j] < arr[min_idx]) {
                min_idx = j;
            }
        }

        if (min_idx != i) {
            swap(&arr[min_idx], &arr[i]);
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
