#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void insertionSort(char arr[], int numDigits)
{
    int i, key, j;

    for (i = 0; i < numDigits; i++)
    {
        key = arr[i];
        j = i - 1;

        while (j >= 0 && arr[j] > key)
        {
            arr[j + 1] = arr[j];
            j = j - 1;
        }
        arr[j + 1] = key;
    }
}

void merge(char arr[], int left, int mid, int right)
{
    int i, j, k;
    int n1 = mid - left + 1;
    int n2 = right - mid;
    int *L = (int *)malloc(n1 * sizeof(int)); // Dynamic allocation
    int *R = (int *)malloc(n2 * sizeof(int)); // Dynamic allocation

    // copy data to temp arrs
    for (i = 0; i < n1; i++)
    {
        L[i] = arr[left + i];
    }
    for (j = 0; j < n2; j++)
    {
        R[j] = arr[mid + 1 + j];
    }
    // merge temp arrs back into arr[l..r]
    i = 0;
    j = 0;
    k = left;

    while (i < n1 && j < n2)
    {
        if (L[i] <= R[j])
        {
            arr[k] = L[i];
            i++;
        }
        else
        {
            arr[k] = R[j];
            j++;
        }
        k++;
    }
    // copy remaining elemets of L if any
    while (i < n1)
    {
        arr[k] = L[i];
        i++;
        k++;
    }
    // copy remaining elemets of R if any
    while (j < n2)
    {
        arr[k] = R[j];
        j++;
        k++;
    }
    free(L);
    free(R);
}

void mergeSort(char arr[], int left, int right)
{
    if (left < right)
    {
        int m = left + (right - left) / 2;

        // sort first and second halves
        mergeSort(arr, left, m);
        mergeSort(arr, m + 1, right);

        merge(arr, left, m, right);
    }
}

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define STACK_SIZE 1000

// Structure for stack
struct Stack
{
    int low;
    int high;
};

// Function to swap two elements
void swap(char *a, char *b)
{
    char temp = *a;
    *a = *b;
    *b = temp;
}

// Function to find median of three elements
int medianOfThree(char arr[], int low, int high)
{
    int mid = low + (high - low) / 2;
    if (arr[low] > arr[mid])
    {
        swap(&arr[low], &arr[mid]);
    }
    if (arr[low] > arr[high])
    {
        swap(&arr[low], &arr[high]);
    }
    if (arr[mid] > arr[high])
    {
        swap(&arr[mid], &arr[high]);
    }
    return mid;
}

// Partition function for quicksort
int partition(char arr[], int low, int high)
{
    int pivotIndex = medianOfThree(arr, low, high);
    char pivot = arr[pivotIndex];
    int i = low - 1;

    for (int j = low; j <= high - 1; j++)
    {
        if (arr[j] < pivot)
        {
            i++;
            swap(&arr[i], &arr[j]);
        }
    }
    swap(&arr[i + 1], &arr[pivotIndex]);
    return (i + 1);
}

// Quicksort function
void quickSort(char arr[], int low, int high)
{
    // Create a stack for storing subarray indices
    struct Stack stack[STACK_SIZE];
    int top = -1;

    // Push initial values of low and high to stack
    stack[++top].low = low;
    stack[top].high = high;

    // Keep popping from stack while it's not empty
    while (top >= 0)
    {
        // Pop low and high indices
        high = stack[top].high;
        low = stack[top--].low;

        // If there are more than 2 elements in the subarray, use quicksort
        if (high - low > 1)
        {
            int pi = partition(arr, low, high);
            // Push the left and right subarrays to the stack
            if (pi - 1 > low)
            {
                stack[++top].low = low;
                stack[top].high = pi - 1;
            }
            if (pi + 1 < high)
            {
                stack[++top].low = pi + 1;
                stack[top].high = high;
            }
        }
    }
}

// Function to get the largest element from an array
int getMax(int array[], int n)
{
    int max = array[0];
    for (int i = 1; i < n; i++)
        if (array[i] > max)
            max = array[i];
    return max;
}

void countingSort(char arr[], int size, int place)
{
    const int range = 256; // Assuming ASCII characters (0-255)
    int count[range], i;
    char *output = (char *)malloc(size * sizeof(char));

    // Initialize count array
    for (i = 0; i < range; i++)
        count[i] = 0;

    // Store count of occurrences in count[]
    for (i = 0; i < size; i++)
        count[(arr[i] / place) % range]++;

    // Change count[i] so that count[i] now contains actual position of this digit in output[]
    for (i = 1; i < range; i++)
        count[i] += count[i - 1];

    // Build the output array
    for (i = size - 1; i >= 0; i--)
    {
        output[count[(arr[i] / place) % range] - 1] = arr[i];
        count[(arr[i] / place) % range]--;
    }

    // Copy the output array to arr[], so that arr[] now contains sorted numbers according to current digit
    for (i = 0; i < size; i++)
        arr[i] = output[i];

    free(output);
}

void radixsort(char arr[], int size)
{
    // Find the maximum number to know number of digits
    int max = arr[0];
    for (int i = 1; i < size; i++)
    {
        if (arr[i] > max)
            max = arr[i];
    }

    // Do counting sort for every digit. Note that instead of passing digit number, place is passed. place is 10^i where i is current digit number
    for (int place = 1; max / place > 0; place *= 10)
        countingSort(arr, size, place);
}

// Print an array
void printArray(int array[], int size)
{
    for (int i = 0; i < size; ++i)
    {
        printf("%d  ", array[i]);
    }
    printf("\n");
}

int main()
{
    FILE *file;
    char filename[] = "numbers.txt";
    int numDigits = 100000000; // Number of digits to read (max 100000000)
    char *digits = (char *)malloc(numDigits * sizeof(char));
    int length = numDigits - 1;

    // Open the file in read mode
    file = fopen(filename, "r");
    if (file == NULL)
    {
        fprintf(stderr, "Error opening file.\n");
        return 1;
    }

    // Read the digits from the file into the array
    fread(digits, sizeof(char), numDigits, file);

    clock_t startTime = clock();
    // insertionSort(digits, numDigits);
    // mergeSort(digits, 0, length);
    // quickSort(digits, 0, length);
    radixsort(digits, length);
    clock_t endTime = clock();

    double totalTime = ((double)(endTime - startTime)) / CLOCKS_PER_SEC;

    printf("Time taken for sorting: %f seconds\n", totalTime);

    free(digits);
    fclose(file);
    return 0;
}