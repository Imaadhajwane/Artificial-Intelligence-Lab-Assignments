#include <stdio.h>
#include <stdbool.h>

#define MAX_N 20

int board[MAX_N][MAX_N];
int solutionsCount = 0;
int queenPositions[MAX_N];

void initializeBoard(int n)
{
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            board[i][j] = 0;
}

long long calculateCombinations(int n, int r)
{
    // Calculate n! / (r! * (n-r)!)
    long long result = 1;
    for (int i = 1; i <= r; i++)
    {
        result *= (n - i + 1);
        result /= i;
    }
    return result;
}

void printBoard(int n)
{
    printf("Solution %d:\n", solutionsCount);
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
            printf("%c ", (board[i][j] == 1) ? 'Q' : '.');
        printf("\n");
    }

    // Display positions of queens in the array
    printf("Queen positions: ");
    for (int i = 0; i < n; i++)
        printf("%d ", queenPositions[i] + 1); // Adding 1 to convert to 1-indexed positions
    printf("\n");
}

bool isSafe(int row, int col, int n)
{
    // Check the row on the left side
    for (int i = 0; i < col; i++)
        if (board[row][i] == 1)
            return false;

    // Check upper diagonal on the left side
    for (int i = row, j = col; i >= 0 && j >= 0; i--, j--)
        if (board[i][j] == 1)
            return false;

    // Check lower diagonal on the left side
    for (int i = row, j = col; i < n && j >= 0; i++, j--)
        if (board[i][j] == 1)
            return false;

    return true;
}

void solveNQueens(int col, int n)
{
    if (col == n)
    {
        // Solution found
        solutionsCount++;
        // Store queen positions
        for (int i = 0; i < n; i++)
            queenPositions[i] = -1; // Reset array
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++)
                if (board[j][i] == 1)
                    queenPositions[i] = j;
        printBoard(n);
        return;
    }

    for (int i = 0; i < n; i++)
    {
        if (isSafe(i, col, n))
        {
            board[i][col] = 1;
            solveNQueens(col + 1, n);
            board[i][col] = 0; // Backtrack
        }
    }
}

int main()
{
    char c = 'Y';

    while (c == 'Y' || c == 'y')
    {
        int n, queens;

        printf("Enter the size of the chessboard: ");
        scanf("%d", &n);

        printf("Enter the number of queens: ");
        scanf("%d", &queens);

        if (n < 1 || queens < 1 || queens > n)
        {
            printf("Invalid input. Exiting...\n");
            return 1;
        }

        initializeBoard(n);

        solveNQueens(0, queens);

        printf("Total number of solutions: %d\n", solutionsCount);

        // Display total number of ways queens can be placed
        long long totalWays = calculateCombinations(n * n, n);
        printf("Total ways queens can be placed: %lld\n\n", totalWays);

        printf("Do you want to continue? (Y/N): ");
        scanf(" %c", &c);
    }

    return 0;
}
