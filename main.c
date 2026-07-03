#include <stdio.h>
#include <stdlib.h>

// Announce the winner based on player number
int announceWinner(int playerNum) {
    printf("\nPlayer %c Wins!\n", (playerNum == 1) ? 'X' : 'O');
    return playerNum;
}

// Check rows, columns, and diagonals for a win or draw
int checkWinner(int grid[3][3]) {
    // Check Rows and Columns
    for (int i = 0; i < 3; i++) {
        if (grid[i][0] != 0 && grid[i][0] == grid[i][1] && grid[i][0] == grid[i][2])
            return announceWinner(grid[i][0]); // Row win
        
        if (grid[0][i] != 0 && grid[0][i] == grid[1][i] && grid[0][i] == grid[2][i])
            return announceWinner(grid[0][i]); // Column win
    }

    // Check Diagonals
    if (grid[0][0] != 0 && grid[0][0] == grid[1][1] && grid[1][1] == grid[2][2])
        return announceWinner(grid[0][0]);
    
    if (grid[2][0] != 0 && grid[2][0] == grid[1][1] && grid[1][1] == grid[0][2])
        return announceWinner(grid[2][0]);

    // Check for Draw (if no zeros left)
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (grid[i][j] == 0) return 0; // Still empty spots
        }
    }
    
    printf("\nIt's a Draw!\n");
    return -1; // Draw signal
}

// Print the grid in a readable board format
void printGrid(int grid[][3]) {
    printf("\n");
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            char symbol = (grid[i][j] == 1) ? 'X' : (grid[i][j] == 2) ? 'O' : ' ';
            printf(" %c ", symbol);
            if (j < 2) printf("|");
        }
        printf("\n");
        if (i < 2) printf("---+---+---\n");
    }
    printf("\n");
}

// Handle player input with validation
void getInput(int player, int grid[][3]) {
    int row, col;
    char symbol = (player == 1) ? 'X' : 'O';
    
    while (1) {
        printf("Player %c, enter row and column (1-3): ", symbol);
        if (scanf("%d %d", &row, &col) != 2) {
            // Clear invalid input buffer
            while(getchar() != '\n'); 
            printf("Invalid input. Please enter numbers.\n");
            continue;
        }

        if (row >= 1 && row <= 3 && col >= 1 && col <= 3) {
            if (grid[row-1][col-1] == 0) {
                grid[row-1][col-1] = player;
                break; // Valid move
            } else {
                printf("That spot is already taken!\n");
            }
        } else {
            printf("Out of bounds. Use numbers 1 to 3.\n");
        }
    }
}

int main() {
    int grid[3][3] = {0}; // Initializes all to 0
    int gameOver = 0;
    int turn = 1; // 1 for X, 2 for O

    printf("Welcome to Tic-Tac-Toe!\n");
    printGrid(grid);

    while (!gameOver) {
        getInput(turn, grid);
        printGrid(grid);
        
        int result = checkWinner(grid);
        if (result != 0) {
            gameOver = 1;
        } else {
            turn = (turn == 1) ? 2 : 1; // Switch turn
        }
    }

    return 0;
}   