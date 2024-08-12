//Design and implement C/C++ Program for N Queen's problem using Backtracking.

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// Function to print the solution
void printSolution(int **board, int N)
{
    int i, j;
    for (i = 0; i < N; i++)
    {
        for (j = 0; j < N; j++)
        {
            printf("%s ", board[i][j] ? "Q" : "#");
        }
        printf("\n");
    }
}

// Function to check if a queen can be placed on board[row][col]
bool isSafe(int **board, int N, int row, int col)
{
    int i, j;
    for (i = 0; i < col; i++)
    {
        if (board[row][i])
        {
            return false;
        }
    }
    for (i = row, j = col; i >= 0 && j >= 0; i--, j--)
    {
        if (board[i][j])
        {
            return false;
        }
    }
    for (i = row, j = col; j >= 0 && i < N; i++, j--)
    {
        if (board[i][j])
        {
            return false;
        }
    }
    return true;
}

bool solveNQUtil(int **board, int N, int col)
{
    int i;
    if (col >= N)
    {
        return true;
    }
    for (i = 0; i < N; i++)
    {
        if (isSafe(board, N, i, col))
        {
            board[i][col] = 1;
            if (solveNQUtil(board, N, col + 1))
            {
                return true;
            }
            board[i][col] = 0; // BACKTRACK
        }
    }
    return false;
}

bool solveNQ(int N)
{
    int i, j;
    int **board = (int **)malloc(N * sizeof(int *));
    for (i = 0; i < N; i++)
    {
        board[i] = (int *)malloc(N * sizeof(int));
        for (j = 0; j < N; j++)
        {
            board[i][j] = 0;
        }
    }
    if (!solveNQUtil(board, N, 0))
    {
        printf("Solution does not exist\n");
        for (i = 0; i < N; i++)
        {
            free(board[i]);
        }
        free(board);
        return false;
    }
    printSolution(board, N);
    for (i = 0; i < N; i++)
    {
        free(board[i]);
    }
    free(board);
    return true;
}

int main()
{
    int N;
    printf("Enter the number of queens: ");
    scanf("%d", &N);
    solveNQ(N);
    return 0;
}