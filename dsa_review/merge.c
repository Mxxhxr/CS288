#include <stdio.h>





void merge(int arr[], int low, int mid, int high) {
    int n1 = mid - low + 1; // size of left sub arr
    int n2 = high - mid; // size of right sub arr

    int left[n1], right[n2]; // create sub arr's

    // copy data to temp arr's
    for (int i = 0; i<n1; i++) {
        left[i] = arr[low+1];
    }
    for (int j = 0; j<n2; j++) {
        right[j] = arr[mid + 1 + j];
    }

    // merge temp arr's
    int i = 0; // index of first sub arr
    int j = 0; // index of second sub arr
    int k = low; // index of merged sub arr

    while (i < n1 && j < n2) {
        if(left[i] <= right[j]) {
            arr[k] = left[i];
            i++;
        }
        else {
            arr[k] = right[j];
            j++;
        }
        k++;
    }
    // copy remaining elements of left[] if there are any
    while (i < n1) {
        arr[k] = left[i];
        i++;
        k++;
    }

    // copy remaining elements of right[] if there are any
    while (j < n2) {
        arr[k] = right[j];
        j++;
        k++;
    }
}

void mergeSort(int arr[], int low, int high) {
    if (low < high) {
        int mid = (low + high) / 2;
        mergeSort(arr, low, mid);
        mergeSort(arr, mid+1, high);
        merge(arr, low, mid, high);
    }
}

void printArray(int arr[], int size) {
    for (int i = 0; i < size; i++)
        printf("%d ", arr[i]);
    printf("\n");
}

int main() {
    int arr[] = {12, 11, 13, 5, 6, 7};
    int arr_size = sizeof(arr) / sizeof(arr[0]);

    printf("Given array is \n");
    printArray(arr, arr_size);

    mergeSort(arr, 0, arr_size - 1);

    printf("\nSorted array is \n");
    printArray(arr, arr_size);
    return 0;
}