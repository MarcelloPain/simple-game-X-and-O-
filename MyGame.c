#include <stdio.h>
/*
a. The game is played on a 5x5 board between player A and player B in turn.
b. Player A always starts the game.
c. Player A puts X, while player B puts O in empty cells of the board.
d. Player moves are taken in the following format
x,y
Here, x and y indicate the board coordinates where the player wants to insert X
or O.
e. At the end of the game, the score for player A is computed based on the number
of the following shape he/she obtains:
  X
X X X
In this shape, three Xs are placed next to each other, while in the above line,
there is an X in the middle.
f. Similarly, the score for player B is computer based on the number of the following
shape
O O O
  O
In this shape, three Os are next to each other, while the below line contains an O
right in the middle.
g. At the end of the game, the player who obtains the most score wins.
h. Your program will print the current state of the board after each player’s move.
i. The game ends when there is no empty cell in the board.
j. Your program needs to do necessary error controls, e.g., if the player selects a
position that is already occupied or the position is outside the board then print an
informative message and ask the user to enter his move again.
 */

void printBoard(char matrix[5][5]){
    int i, j;
    for (i = 0; i < 5; i++) {
        for (j = 0; j < 5; j++) {
            printf("%3c", matrix[i][j]);
        }
        printf("\n");
    }
}

int main()
{
    setvbuf(stdout, NULL, _IONBF, 0);
    int i, j;
    //Create a game board containing only # in each element
    char board[5][5];
    for (i = 0; i < 5; i++) {
        for(j = 0; j < 5; j++)
            board[i][j] = '#';
    }
    
    //Print the board to the screen
    printf("Game started.. Current state of the board: \n");
    printBoard (board);
    
    //Starting to input moves and checking the occupancy
    _Bool is_full = 0;
    do {
        int row, column;
        
        //Inputs A's move
        printf("A’s move: ");
        do {
            scanf("%i, %i", &row, &column);
            
            //checking the limit of the input (must be between 1 and 5)
            if ((row > 5 || row < 1) || (column > 5 || column < 1)) {
                printf("Invalid move for A! Board coordinates must be in [1,5]. Enter again: ");
                continue;
            }
            //check the occupancy, hence, not #
            else if (board[row-1][column-1] == 'O' || board[row-1][column-1] == 'X'){
                printf("position [%i,%i] is full! Enter again A's move: ", row, column);
                continue;
            }
            //occupying the element of the matrix (player A)
            else {
                board[row-1][column-1] = 'X';
                //printing the new board to the screen
                printBoard(board);
                //after the assigning A's move, we should continue to B's move
                break;
            }
        } while(1);
        
        do {
            //check whether the matrix is full (breaks from the loops if the board is full)
            is_full = 1;
            int r, c;
            for (r = 0; r < 5; r++) {
                //if it finds at least one # in the board, it will resume to input B's move
                for (c = 0; c < 5; c++) {
                    if (board[r][c] == '#') {
                        is_full = 0;
                        break;
                    }
                }
                if(is_full == 0)
                    break;
            }
            //if there is no # on the board, it doesn't input B's move
            if(is_full == 1)
                break;
            
            //Inputs B's move
            printf("B’s move: ");
            scanf("%i, %i", &row, &column);
            
            //checking the limit of the input
            if ((row > 5 || row < 1) || (column > 5 || column < 1)) {
                printf("Invalid move for B! Board coordinates must be in [1,5]. Enter again: ");
                continue;
            }
            
            //check the occupancy
            else if (board[row-1][column-1] == 'X' || board[row-1][column-1] == 'O') {
                printf("position [%i,%i] is full! Enter again B's move: ", row, column);
                continue;
            }
            
            //occupying the element of the matrix (player A)
            else {
                board[row-1][column-1] = 'O';
                //printing the new board to the screen
                printBoard(board);
                break;
            }
        } while(1);
    } while(is_full == 0);
    
    //is outputted when the board is fully occupied
    printf("Board is full\n");
    
    //Counting the scores:
    //counting A's score
    int A_score = 0, k;
    for (i = 0; i < 4; i++) {
        for (j = 1; j < 4; j++) {
            if (board[i][j] == 'X') {
                _Bool maybe = 1;
                for (k = j - 1; k < j + 2; k++) {
                    if (board[i+1][k] != 'X') {
                        maybe = 0;
                        break;
                    }
                }
                if (maybe == 1)
                    A_score++;
            }
        }
    }
    printf("Score for player A: %i\n", A_score);
    
    //counting B's score
    int B_score = 0, h, l, p;
    for (h = 1; h < 5; h++) {
        for (l = 1; l < 4; l++) {
            if (board[h][l] == 'O') {
                _Bool maybe = 1;
                for (p = l - 1; p < l + 2; p++) {
                    if (board[h-1][p] != 'O')
                        maybe = 0;
                }
                if(maybe == 1)
                    B_score++;
            }
        }
    }
    printf("Score for player B: %i\n", B_score);
    
    //checking for the winner
    if (A_score > B_score) {
        printf("The winner is player A!\n");
    }
    else if (B_score > A_score) {
        printf("The winner is player B!\n");
    }
    else{
        printf("No one wins\n");
    }
    
    return 0;
}
