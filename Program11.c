//Design and implement C/C++ Program to sort a given set of n integer elements using
//Merge Sort method and compute its time complexity. Run the program for varied
//values of n> 5000, and record the time taken to sort. Plot a graph of the time taken
//versus n. The elements can be read from a file or can be generated using the random
//number generator.

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void merge(int arr[], int l, int m, int r)
{
    int i, j, k;
    int n1 = m - l + 1;
    int n2 = r - m;
    // Create temp arrays
    int L[n1], R[n2];
    // Copy data to temp arrays L[] and R[]
    for (i = 0; i < n1; i++)
        L[i] = arr[l + i];
    for (j = 0; j < n2; j++)
        R[j] = arr[m + 1 + j];
    // Merge the temp arrays back into arr[l..r]
    i = 0; // Initial index of first subarray
    j = 0; // Initial index of second subarray
    k = l; // Initial index of merged subarray
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
    // Copy the remaining elements of L[], if there are any
    while (i < n1)
    {
        arr[k] = L[i];
        i++;
        k++;
    }
    // Copy the remaining elements of R[], if there are any
    while (j < n2)
    {
        arr[k] = R[j];
        j++;
        k++;
    }
}

void mergeSort(int arr[], int l, int r)
{
    if (l < r)
    {
        int m = l + (r - l) / 2;
        // Sort first and second halves
        mergeSort(arr, l, m);
        mergeSort(arr, m + 1, r);
        merge(arr, l, m, r);
    }
}

void generateRandomArray(int arr[], int n)
{
    int i;
    for (i = 0; i < n; i++)
    {
        arr[i] = rand() % 10000;
    }
}

double measureMergeSortTime(int n)
{
    int *arr = (int *)malloc(n * sizeof(int));
    generateRandomArray(arr, n);
    clock_t start, end;
    double cpu_time_used;
    start = clock();
    mergeSort(arr, 0, n - 1);
    end = clock();
    cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
    free(arr);
    return cpu_time_used;
}

void plotGraph()
{
    FILE *gnuplotPipe = popen("gnuplot -persistent", "w");
    if (gnuplotPipe)
    {
        fprintf(gnuplotPipe, "set title 'Merge Sort Time Complexity'\n");
        fprintf(gnuplotPipe, "set xlabel 'Number of elements (n)'\n");
        fprintf(gnuplotPipe, "set ylabel 'Time taken (seconds)'\n");
        fprintf(gnuplotPipe, "set grid\n");
        fprintf(gnuplotPipe, "set term png\n");
        fprintf(gnuplotPipe, "set output 'merge_sort_output.png'\n");
        fprintf(gnuplotPipe, "plot 'merge_sort_data.txt' with linespoints\n");
        pclose(gnuplotPipe);
    }
}

void sortUserArray()
{
    int n, i;
    printf("Enter the number of elements: ");
    scanf("%d", &n);
    int *arr = (int *)malloc(n * sizeof(int));
    printf("Enter the elements:\n");
    for (i = 0; i < n; i++)
    {
        scanf("%d", &arr[i]);
    }
    mergeSort(arr, 0, n - 1);
    printf("Sorted array:\n");
    for (i = 0; i < n; i++)
    {
        printf("%d ", arr[i]);
    }
    printf("\n");
    free(arr);
}

void plotMergeSortTimeComplexityGraph()
{
    int values_of_n[] = {5000, 10000, 15000, 20000, 25000, 30000, 35000, 40000, 45000,
                         50000};
    int num_values = sizeof(values_of_n) / sizeof(values_of_n[0]);
    int i;
    FILE *dataFile = fopen("merge_sort_data.txt", "w");
    if (dataFile == NULL)
    {
        fprintf(stderr, "Error opening file for writing\n");
        return;
    }
    for (i = 0; i < num_values; i++)
    {
        int n = values_of_n[i];
        double time_taken = measureMergeSortTime(n);
        fprintf(dataFile, "%d %f\n", n, time_taken);
        printf("Sorted %d elements in %f seconds\n", n, time_taken);
    }
    fclose(dataFile);
    plotGraph();
}

int main()
{
    srand(time(0)); // Seed the random number generator
    int choice;
    do
    {
        printf("\nMenu:\n");
        printf("1. Sort an array using Merge Sort\n");
        printf("2. Plot time complexity graph for Merge Sort\n");
        printf("3. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        switch (choice)
        {
        case 1:
            sortUserArray();
            break;
        case 2:
            plotMergeSortTimeComplexityGraph();
            break;
        case 3:
            printf("Exiting...\n");
            break;
        default:
            printf("Invalid choice. Please try again.\n");
        }
    } while (choice != 3);
    return 0;
}