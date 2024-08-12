//Design and implement C/C++ Program to sort a given set of n integer elements using
//Selection Sort method and compute its time complexity. Run the program for varied
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

void selectionSort(int arr[], int n)
{
    int i, j, min_idx;
    for (i = 0; i < n - 1; i++)
    {
        min_idx = i;
        for (j = i + 1; j < n; j++)
        {
            if (arr[j] < arr[min_idx])
            {
                min_idx = j;
            }
        }
        swap(&arr[min_idx], &arr[i]);
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

double measureSelectionSortTime(int n)
{
    int *arr = (int *)malloc(n * sizeof(int));
    generateRandomArray(arr, n);
    clock_t start, end;
    double cpu_time_used;
    start = clock();
    selectionSort(arr, n);
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
        fprintf(gnuplotPipe, "set title 'Selection Sort Time Complexity'\n");
        fprintf(gnuplotPipe, "set xlabel 'Number of elements (n)'\n");
        fprintf(gnuplotPipe, "set ylabel 'Time taken (seconds)'\n");
        fprintf(gnuplotPipe, "set grid\n");
        fprintf(gnuplotPipe, "set term png\n");
        fprintf(gnuplotPipe, "set output 'selection_sort_output.png'\n");
        fprintf(gnuplotPipe, "plot 'selection_sort_data.txt' with linespoints\n");
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
    selectionSort(arr, n);
    printf("Sorted array : \n");
    for (i = 0; i < n; i++)
    {
        printf("%d\t", arr[i]);
    }
    printf("\n");
    free(arr);
}

void plotSelectionSortTimeComplexityGraph()
{
    int i;
    int values_of_n[] = {5000, 10000, 15000, 20000, 25000, 30000, 35000, 40000, 45000,
                         50000};
    int num_values = sizeof(values_of_n) / sizeof(values_of_n[0]);
    FILE *dataFile = fopen("selection_sort_data.txt", "w");
    if (dataFile == NULL)
    {
        fprintf(stderr, "Error opening file for writing\n");
        return;
    }
    for (i = 0; i < num_values; i++)
    {
        int n = values_of_n[i];
        double time_taken = measureSelectionSortTime(n);
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
        printf("\nMenu : \n");
        printf("1. Sort an array using Selection Sort\n");
        printf("2. Plot time complexity graph for Selection Sort\n");
        printf("3. Exit\n");
        printf("Enter your choice : ");
        scanf("%d", &choice);
        switch (choice)
        {
        case 1:
            sortUserArray();
            break;
        case 2:
            plotSelectionSortTimeComplexityGraph();
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