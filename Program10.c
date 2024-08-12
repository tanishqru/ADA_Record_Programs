//Design and implement C/C++ Program to sort a given set of n integer elements using
//Quick Sort method and compute its time complexity. Run the program for varied
//values of n> 5000 and record the time taken to sort. Plot a graph of the time taken
//versus n. The elements can be read from a file or can be generated using the random
//number generator.

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void swap(int *a, int *b)
{
    int t = *a;
    *a = *b;
    *b = t;
}

int partition(int arr[], int low, int high)
{
    int pivot = arr[high];
    int i = (low - 1);
    int j;
    for (j = low; j <= high - 1; j++)
    {
        if (arr[j] < pivot)
        {
            i++;
            swap(&arr[i], &arr[j]);
        }
    }
    swap(&arr[i + 1], &arr[high]);
    return (i + 1);
}

void quickSort(int arr[], int low, int high)
{
    if (low < high)
    {
        int pi = partition(arr, low, high);
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
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

double measureSortTime(int n)
{
    int *arr = (int *)malloc(n * sizeof(int));
    generateRandomArray(arr, n);
        clock_t start,
        end;
    double cpu_time_used;
    start = clock();
    quickSort(arr, 0, n - 1);
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
        fprintf(gnuplotPipe, "set title 'Quick Sort Time Complexity'\n");
        fprintf(gnuplotPipe, "set xlabel 'Number of elements (n)'\n");
        fprintf(gnuplotPipe, "set ylabel 'Time taken (seconds)'\n");
        fprintf(gnuplotPipe, "set grid\n");
        fprintf(gnuplotPipe, "set term png\n");
        fprintf(gnuplotPipe, "set output 'output.png'\n");
        fprintf(gnuplotPipe, "plot 'data.txt' with linespoints\n");
        pclose(gnuplotPipe);
    }
}

void sortUserArray()
{
    int n, i;
    printf("Enter the number of elements : ");
    scanf("%d", &n);
    int *arr = (int *)malloc(n * sizeof(int));
    printf("Enter the elements : \n");
    for (i = 0; i < n; i++)
    {
        scanf("%d", &arr[i]);
    }
    quickSort(arr, 0, n - 1);
    printf("Sorted array : \n");
    for (i = 0; i < n; i++)
    {
        printf("%d\t", arr[i]);
    }
    printf("\n");
    free(arr);
}

void plotTimeComplexityGraph()
{
    int i;
    int values_of_n[] = {5500, 10000, 20000, 30000, 40000, 50000};
    int num_values = sizeof(values_of_n) / sizeof(values_of_n[0]);
    FILE *dataFile = fopen("data.txt", "w");
    if (dataFile == NULL)
    {
        fprintf(stderr, "Error opening file for writing\n");
        return;
    }
    for (i = 0; i < num_values; i++)
    {
        int n = values_of_n[i];
        double time_taken = measureSortTime(n);
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
        printf("1. Sort an array\n");
        printf("2. Plot time complexity graph\n");
        printf("3. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        switch (choice)
        {
        case 1:
            sortUserArray();
            break;
        case 2:
            plotTimeComplexityGraph();
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