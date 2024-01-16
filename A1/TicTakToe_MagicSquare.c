#include <stdio.h>
#include <stdlib.h>

#define SIZE 3

void displayMatrix(int matrix[SIZE][SIZE])
{
    printf("Current Board:\n");
    for (int i = 0; i < SIZE; i++)
    {
        for (int j = 0; j < SIZE; j++)
        {
            printf("%2d ", matrix[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

void displayPossibleMoves(int matrix[SIZE][SIZE], int currentPlayer)
{
    printf("Possible Moves for Player %d:\n", currentPlayer);
    for (int i = 0; i < SIZE; i++)
    {
        for (int j = 0; j < SIZE; j++)
        {
            if (matrix[i][j] == 0)
            {
                printf("(%d, %d) ", i + 1, j + 1);
            }
        }
    }
    printf("\n\n");
}

int checkWin(int matrix[SIZE][SIZE], int player)
{
    // Check rows and columns
    for (int i = 0; i < SIZE; i++)
    {
        if (matrix[i][0] == player && matrix[i][1] == player && matrix[i][2] == player)
        {
            return 1; // Row win
        }
        if (matrix[0][i] == player && matrix[1][i] == player && matrix[2][i] == player)
        {
            return 1; // Column win
        }
    }

    // Check diagonals
    if (matrix[0][0] == player && matrix[1][1] == player && matrix[2][2] == player)
    {
        return 1; // Diagonal win (top-left to bottom-right)
    }
    if (matrix[0][2] == player && matrix[1][1] == player && matrix[2][0] == player)
    {
        return 1; // Diagonal win (top-right to bottom-left)
    }

    return 0; // No win yet
}

int main()
{
    int magicSquare[SIZE][SIZE], board[SIZE][SIZE] = {0};
    int currentPlayer = 1, moveCount = 0;

    // Step 1: Ask for the user the size of the matrix of the magic square
    printf("Enter the order of the magic square (must be 3 for a 3x3 Tic Tac Toe): ");
    int order;
    scanf("%d", &order);

    if (order != 3)
    {
        printf("Invalid order for Tic Tac Toe. Exiting...\n");
        exit(0);
    }

    // Step 2: Display the magic square and its sum row and col wise
    printf("Magic Square for Tic Tac Toe (Order %d):\n", order);
    // Insert your code to generate and display the magic square here...

    // Assume a predefined magic square for a 3x3 Tic Tac Toe
    int predefinedMagicSquare[3][3] = {
        {8, 1, 6},
        {3, 5, 7},
        {4, 9, 2}};

    // Display the predefined magic square
    displayMatrix(predefinedMagicSquare);

    // Step 3: Generate another matrix with numbers starting from 1 to 9
    int numberMatrix[SIZE][SIZE];
    int number = 1;
    for (int i = 0; i < SIZE; i++)
    {
        for (int j = 0; j < SIZE; j++)
        {
            numberMatrix[i][j] = number++;
        }
    }

    // Main game loop
    while (1)
    {
        // Display the current state of the board
        displayMatrix(board);

        // Step 4: Display possible moves for the current player
        displayPossibleMoves(board, currentPlayer);

        // Step 5: Accept user move
        int row, col;
        printf("Enter your move (row and column): ");
        scanf("%d %d", &row, &col);

        // Check if the move is valid
        if (row < 1 || row > SIZE || col < 1 || col > SIZE || board[row - 1][col - 1] != 0)
        {
            printf("Invalid move! Try again.\n");
            continue;
        }

        // Make the move
        board[row - 1][col - 1] = currentPlayer;

        // Check for a win
        if (checkWin(board, currentPlayer))
        {
            displayMatrix(board);
            printf("Player %d wins!\n", currentPlayer);
            break;
        }

        // Check for a draw
        moveCount++;
        if (moveCount == SIZE * SIZE)
        {
            displayMatrix(board);
            printf("It's a draw!\n");
            break;
        }

        // Switch to the next player
        currentPlayer = 3 - currentPlayer; // Alternates between 1 and 2
    }

    return 0;
}
