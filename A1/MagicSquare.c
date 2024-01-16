#include <stdio.h>
#include <stdlib.h>

#define SIZE 20

int main()
{
    char choice;

    do
    {
        int order, i, j, k, p, q, mid, magic[SIZE][SIZE];

        // Input the order of the magic square (must be odd)
        printf("Enter order of magic square (order must be odd): ");
        scanf("%d", &order);

        if (order % 2 == 0)
        {
            printf("Order must be odd.\n");
            printf("Exiting...\n");
            exit(0);
        }

        mid = order / 2;

        // Initialize the magic square with zeros
        for (i = 0; i < order; i++)
        {
            for (j = 0; j < order; j++)
            {
                magic[i][j] = 0;
            }
        }

        k = mid;
        j = 0;
        for (i = 1; i <= order * order; i++)
        {
            // Fill the magic square
            magic[j][k] = i;
            p = j--;
            q = k++;

            // Wrap around if needed
            if (j < 0)
            {
                j = order - 1;
            }

            if (k > order - 1)
            {
                k = 0;
            }

            // If the cell is already filled, adjust position
            if (magic[j][k] != 0)
            {
                k = q;
                j = p + 1;
            }
        }

        // Display the generated magic square
        printf("Generated MAGIC SQUARE:\n");

        // Display the top border
        for (i = 0; i < order * 7 + 1; i++)
        {
            printf("-");
        }
        printf("\n");

        // Display the magic square
        for (j = 0; j < order; j++)
        {
            printf("|");
            for (k = 0; k < order; k++)
            {
                printf(" %4d |", magic[j][k]);
            }
            printf("\n");

            // Display the row separator
            for (i = 0; i < order * 7 + 1; i++)
            {
                printf("-");
            }
            printf("\n");
        }

        // Display the sum of each row
        printf("Row Sums: ");
        for (j = 0; j < order; j++)
        {
            int rowSum = 0;
            for (k = 0; k < order; k++)
            {
                rowSum += magic[j][k];
            }
            printf("%4d ", rowSum);
        }
        printf("\n");

        // Display the sum of each column
        printf("Col Sums: ");
        for (k = 0; k < order; k++)
        {
            int colSum = 0;
            for (j = 0; j < order; j++)
            {
                colSum += magic[j][k];
            }
            printf("%4d ", colSum);
        }
        printf("\n");

        // Ask the user if they want to continue
        printf("Do you want to continue? (Y/N): ");
        scanf(" %c", &choice);
    } while (choice == 'Y' || choice == 'y');

    return 0;
}
