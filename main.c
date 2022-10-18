#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void resetBoard();
void printBoard();
int checkFreeSpaces();
void playerMove();
void computerMove();
char checkWinner();
void printWinner(char);

void getPlayerInput(int *, char[]);

char board[3][3];
const char PLAYER = 'X';
const char COMPUTER = 'O';

int main()
{
    char winner = ' ';
    char lastMove = COMPUTER;

    resetBoard();
    printBoard();

    while (winner == ' ')
    {
        if (!checkFreeSpaces())
        {
            break;
        }

        switch (lastMove)
        {
        case 'X':
            computerMove();
            printf("\n");
            lastMove = 'O';

        case 'O':
            playerMove();
            printf("\n");
            lastMove = 'X';
        }

        winner = checkWinner();
    }

    printWinner(winner);

    return 0;
}

void resetBoard()
{
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            board[i][j] = ' ';
        }
    }
};

void printBoard()
{
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            if (j == 0)
            {
                printf("|");
            }
            printf(" %c |", board[i][j]);
        }
        if (i != 2)
        {
            printf("\n|---|---|---|\n");
        }
        else
        {
            printf("\n");
        }
    }
};

int checkFreeSpaces()
{
    int freeSpaces = 9;

    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            if (board[i][j] != ' ')
            {
                freeSpaces -= 1;
            }
        }
    }

    return freeSpaces;
};

void playerMove()
{
    if (checkWinner() != ' ')
    {
        return;
    }

    printf("Player move!\n");

    while (1)
    {
        int row;
        int col;

        getPlayerInput(&row, "Row");
        getPlayerInput(&col, "Column");

        if (board[row][col] == PLAYER || board[row][col] == COMPUTER)
        {
            printf("It's occupied!\n");
        }
        else if (row > 2 || row < 0 && col > 2 || col < 0)
        {
            printf("Invalid position!\n");
        }
        else
        {
            board[row][col] = PLAYER;
            printBoard();
            break;
        }
    }
};

void computerMove()
{
    printf("Computer move!\n");

    srand(time(0));

    int row;
    int col;

    do
    {
        row = rand() % 3;
        col = rand() % 3;
    } while (board[row][col] != ' ');

    board[row][col] = COMPUTER;
    printBoard();
};

char checkWinner()
{
    char symbol;

    // check rows
    for (int i = 0; i < 3; i++)
    {
        symbol = board[i][0];

        if (board[i][0] == board[i][1] && board[i][1] == board[i][2] && symbol != ' ')
        {
            return symbol;
        }
    }

    // check columns
    for (int i = 0; i < 3; i++)
    {
        symbol = board[0][i];

        if ((board[0][i] == board[1][i] && board[1][i] == board[2][i]) && symbol != ' ')
        {
            return symbol;
        }
    }

    // check diagonals
    symbol = board[1][1];

    if ((board[0][0] == board[1][1] && board[1][1] == board[2][2]) && symbol != ' ')
    {
        return symbol;
    }
    else if ((board[2][0] == board[1][1] && board[1][1] == board[0][2]) && symbol != ' ')
    {
        return symbol;
    }

    return ' ';
};
void printWinner(char w)
{
    if (w == ' ')
    {
        printf("\nTie!\n");
    }

    char *winner = (w == COMPUTER) ? "Computer" : "Player";

    printf("\nAnd the winner is... \n");
    printf("%s", winner);
};

void getPlayerInput(int *wsk, char dimension[])
{
    printf("%s", dimension);
    printf(": ");
    scanf("%d", wsk);

    *wsk = *wsk - 1;
}