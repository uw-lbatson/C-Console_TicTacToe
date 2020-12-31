#include <stdio.h>
#include <stdlib.h>
#include <time.h>


/*
BOARD:

  1   2   3
  4   5   6
  7   8   9

*/


// define enumerators for simplification of functions
enum {Xs, Os, EMPTY};
enum {playerWin, compWin, DRAW, CONTINUEGAME};

// initializeBoard(int *board): defines all elements of integer array board
// with size 9 to be EMPTY
void initializeBoard(int *board) {
    int index = 0;
    for (index=0; index<9; ++index) {
        board[index] = EMPTY;
    }
}

// printBoard(const int *board): prints all elements of integer array board
// with size 9 based on the numerical value of each index, adds spacing to
// make board feel less crowded
void printBoard(const int *board) {
    int index = 0;
    char pieces[] = "XO";

    printf("\nBoard:\n");
    for(index=0; index<9; ++index) {
        if(index!=0 && index%3==0) {
            printf("\n\n");
        }

        if(board[index] == 2) {
            printf("%3d", index+1);
        } else {
            printf("%3c", pieces[board[index]]);
        }
    }
    printf("\n");
}

// checkEmpty(const int *board): determines if all elements of integer array
// board with size 9 are EMPTY
int checkEmpty(const int *board) {
    int index;

    for (index=0; index<9; ++index) {
        if (board[index] == EMPTY)
            return 1;
    }
    return 0;
}

// checkWin(int *board): checks the current state of play on the board,
// returns a 'winner' value, either compWin, playerWin, or DRAW, or
// produces CONTINUEGAME, with intention to continue playing
// until there is an actual winner
int checkWin(int *board) {
    int i;
    //check cols
    for(i=0; i<2; ++i) {
        if ((board[i] == board[i+3]) &&
            (board[i] == board[i+6]) &&
            (board[i] != EMPTY)) {
            return board[i];
        } else {
            continue;
        }
    }

    //check rows
    for(i=0; i<6; i+=3) {
        if ((board[i] == board[i+1]) &&
            (board[i] == board[i+2]) &&
            (board[i] != EMPTY)) {
            return board[i];
        } else {
            continue;
        }
    }

    //check diagonals
    if ((((board[0] == board[4]) && (board[0] == board[8]))
         || (((board[2] == board[4]) && (board[2] == board[6]))))
        && (board[4] != EMPTY)) {
        return board[4];
    }

    //check if empty still exists
    if (checkEmpty(&board[0]) == 1) {
        return CONTINUEGAME;
    } else {
        return DRAW;
    }
}

// checkGoodMove(int move, int *board): determines if move is valid on
// integer array board. If it is valid, return 'true' (1), otherwise
// return 'false' (0)
int checkGoodMove(int move, int *board) {
    if(board[move-1] == EMPTY) {
        return 1;
    } else {
        return 0;
    }
}

// getPlayerMove(int *board): gets the array position of the players move,
// if players move is invalid, repeats until a valid move is given
int getPlayerMove(int *board) {
    int goodMove = 0;
    int playerMove;

    while(!goodMove) {
        printf("Enter coordinate: ");
        scanf("%d", &playerMove);

        if(!checkGoodMove(playerMove, &board[0])) {
            printf("Incorrect Move. Try again. \n");
            continue;
        }

        goodMove = 1;
    }

    return playerMove-1;
}

// getCompMove(int *board): returns computer players array position of
// move. If move is invalid, repeats getting position until valid
int getCompMove(int *board) {
    int goodMove = 0;
    int compMove;

    while (!goodMove) {
        compMove = (rand() % (9)) + 1;
        if(!checkGoodMove(compMove, &board[0])) {
            continue;
        }
        goodMove = 1;
    }
    return compMove-1;
}

// doMove(const int coord, const int side, int *board): adds side symbol
// to array location, coord, on integer array board
void doMove(const int coord, const int side, int *board) {
    board[coord] = side;
}

// playGame(): runs through a game of tictactoe, players place pieces
// until there is a winner or a draw, ending the application
void playGame() {
    // initialize gameOver var to repeat action of moves
    int gameOver = 0;
    // initialize side to keep track of which 'piece' to play
    int side = Xs;
    // initialize lastMove to keep track of move made
    int lastMove;
    // initialize game board
    int board[9];

    // set up board for tictactoe
    initializeBoard(&board[0]);
    printBoard(&board[0]);

    // run main game loop
    while(!gameOver) {
        if(side == Xs) {
            lastMove = getPlayerMove(&board[0]);
            doMove(lastMove, side, &board[0]);
            side = Os;
            printBoard(&board[0]);
        } else {
            lastMove = getCompMove(&board[0]);
            doMove(lastMove, side, &board[0]);
            side = Xs;
            printBoard(&board[0]);
        }

        // used to get winner, or continue the game
        if(checkWin(&board[0]) == CONTINUEGAME) {
            continue;
        } else if(checkWin(&board[0]) != CONTINUEGAME) {
            if(checkWin(&board[0]) == DRAW) {
                printf("It's a Draw!");
                gameOver = 1;
            } else if(checkWin(&board[0]) == playerWin) {
                printf("You Win!");
                gameOver = 1;
            } else if(checkWin(&board[0]) == compWin) {
                printf("You Lose!");
                gameOver = 1;
            }
        }
    }
}

// main(): runs main game loop, uses srand for a random seed for rand()
int main() {
    srand(time(NULL));
    playGame();

    return 0;
}
