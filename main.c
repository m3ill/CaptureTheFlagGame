#include <stdio.h>
#include <stdlib.h>
#include <time.h>


// we will use F for flag 1 for player1 and 2 for player2 on the board.
#define FLAG 'F'
#define PLAYER1 '1'
#define PLAYER2 '2'

int flagX,flagY;

char** initializeBoard(int size);
void displayBoard(char** board, int size);
int hasCapturedFlag(char** board, int x, int y,int size) ;
void movePlayer(char** board, int size, int* row, int* column, char direction,char player);
void placeFlag(char** board,int size);

int main() {
    int size;

    printf("Enter the size of the game board: ");
    scanf("%d", &size);

    char** board = initializeBoard(size);
    int player1X = 0, player1Y = 0; // Player 1 starting position
    int player2X = size - 1, player2Y = size - 1; // Player 2 starting position
    board[player1X][player1Y] = PLAYER1;
    board[player2X][player2Y] = PLAYER2;
    placeFlag(board,size);

    printf("Welcome to Capture the Flag!\n");
    printf("Player 1 (1) starts at (0, 0) and Player 2 (2) starts at (%d, %d).\n", size - 1, size - 1);
    printf("The flag (F) is hidden on the board. Move your player to capture it.\n");

    // Main game loop
    while (1) {
        system("cls");

        printf("\nCurrent Board:\n");
        displayBoard(board, size);

        // Player 1's turn
        printf("\nPlayer 1's turn (1): Enter move (w/a/s/d): ");
        char move;
        scanf(" %c", &move);
        movePlayer(board, size, &player1X, &player1Y, move, PLAYER1);

        if (hasCapturedFlag(board, player1X, player1Y, size)) {
            displayBoard(board, size);
            printf("\nPlayer 1 has captured the flag! Player 1 wins!\n");
            break;
        }

        system("cls");
        printf("\nCurrent Board:\n");
        displayBoard(board, size);

        // Player 2's turn
        printf("\nPlayer 2's turn (2): Enter move (w/a/s/d): ");
        scanf(" %c", &move);
        movePlayer(board, size, &player2X, &player2Y, move, PLAYER2);
        if (hasCapturedFlag(board, player2X, player2Y,size)) {
            displayBoard(board, size);
            printf("\nPlayer 2 has captured the flag! Player 2 wins!\n");
            break;
        }
    }

    getchar();
    getchar();
    // Free allocated memory
    for (int i = 0; i < size; i++) {
        free(board[i]);
    }
    free(board);

    return 0;
}

// Function to initialize the game board
char** initializeBoard(int size) {

    char** board = (char**)malloc(size * sizeof(char*));

    for (int i = 0; i < size; i++) {
        board[i] = (char*)malloc(size * sizeof(char));
    }

    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            board[i][j] = 'x';
        }
    }

    return board;
}

void placeFlag(char** board, int size) {
    int x,y;
    srand(time(NULL));
    do {
        flagX = rand() % size;
        flagY = rand() % size;
    }while (board[flagX][flagY] != 'x');
    board[flagX][flagY] = FLAG;
    printf("placed flag is : [%d][%d]",flagX,flagY);
}

// Function to display the game board
void displayBoard(char** board, int size) {

    for (int i = 0; i < size; i++) {
        for (int j = 0 ; j < size; j++) {
            if (board[i][j] == FLAG)
                printf(" x ");
            else
                printf(" %c ", board[i][j]);
        }
        printf("\n");
    }

}

// Function to check if a player has captured the flag
int hasCapturedFlag(char** board, int x, int y, int size) {
    return (flagX == x && flagY == y);
}

// Function to update player position on the board
void movePlayer(char** board, int size, int* row, int* column, char direction, char player) {

    board[*row][*column] = 'x';
    switch (direction) {
        case 'w':
            if (*row > 0)
                *row -= 1;
            break;
        case 'a':
            if (*column > 0)
                *column -= 1;
            break;
        case 's':
            if (*row < size - 1)
                *row += 1;
            break;
        case 'd':
            if (*column < size - 1)
                *column += 1;
            break;
        default:
            break;
    }
    board[*row][*column] = player;
}