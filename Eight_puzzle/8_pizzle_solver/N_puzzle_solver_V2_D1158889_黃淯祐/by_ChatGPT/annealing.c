#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

#define SIZE 5
#define MAX_MOVES 100000
#define INITIAL_TEMPERATURE 100.0
#define FINAL_TEMPERATURE 0.1
#define COOLING_FACTOR 0.99

typedef struct {
    int puzzle[SIZE][SIZE];
    int holeRow;
    int holeCol;
} State;

int getManhattanDistance(int row1, int col1, int row2, int col2) {
    return abs(row1 - row2) + abs(col1 - col2);
}

void initializePuzzle(State *state) {
    int numbers[SIZE * SIZE];
    for (int i = 0; i < SIZE * SIZE; i++) {
        numbers[i] = i;
    }

    srand(time(NULL));
    for (int i = SIZE * SIZE - 1; i > 0; i--) {
        int j = rand() % (i + 1);
        int temp = numbers[i];
        numbers[i] = numbers[j];
        numbers[j] = temp;
    }

    int count = 0;
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            if (numbers[count] == 0) {
                state->holeRow = i;
                state->holeCol = j;
            }
            state->puzzle[i][j] = numbers[count++];
        }
    }
}

int evaluateHeuristic(State *state) {
    int heuristic = 0;

    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            int number = state->puzzle[i][j];
            if (number != 0) {
                int row = (number - 1) / SIZE;
                int col = (number - 1) % SIZE;
                heuristic += getManhattanDistance(i, j, row, col);
            }
        }
    }

    return heuristic;
}

void printPuzzle(State *state) {
    printf("\n");
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            if (state->puzzle[i][j] == 0) {
                printf("  ");
            } else {
                printf("%d ", state->puzzle[i][j]);
            }
        }
        printf("\n");
    }
    printf("\n");
}

void makeMove(State *state, int row, int col) {
    state->puzzle[state->holeRow][state->holeCol] = state->puzzle[row][col];
    state->puzzle[row][col] = 0;
    state->holeRow = row;
    state->holeCol = col;
}

int getRandomMove() {
    return rand() % 4; // 0: Up, 1: Down, 2: Left, 3: Right
}

int isMoveValid(State *state, int move) {
    int holeRow = state->holeRow;
    int holeCol = state->holeCol;

    if (move == 0 && holeRow > 0) { // Up
        return 1;
    } else if (move == 1 && holeRow < SIZE - 1) { // Down
        return 1;
    } else if (move == 2 && holeCol > 0) { // Left
        return 1;
    } else if (move == 3 && holeCol < SIZE - 1) { // Right
        return 1;
    }

    return 0;
}

void applyMove(State *state, int move) {
    int holeRow = state->holeRow;
    int holeCol = state->holeCol;

    if (move == 0) { // Up
        makeMove(state, holeRow - 1, holeCol);
    } else if (move == 1) { // Down
        makeMove(state, holeRow + 1, holeCol);
    } else if (move == 2) { // Left
        makeMove(state, holeRow, holeCol - 1);
    } else if (move == 3) { // Right
        makeMove(state, holeRow, holeCol + 1);
    }
}

void solvePuzzle() {
    State currentState;
    initializePuzzle(&currentState);
    int currentHeuristic = evaluateHeuristic(&currentState);

    printf("Initial Puzzle State:\n");
    printPuzzle(&currentState);

    State bestState = currentState;
    int bestHeuristic = currentHeuristic;

    double temperature = INITIAL_TEMPERATURE;
    int moves = 0;

    while (currentHeuristic > 0 && moves < MAX_MOVES && temperature > FINAL_TEMPERATURE) {
        State nextState = currentState;
        int nextMove = getRandomMove();

        if (isMoveValid(&nextState, nextMove)) {
            applyMove(&nextState, nextMove);

            int nextHeuristic = evaluateHeuristic(&nextState);
            int delta = nextHeuristic - currentHeuristic;

            if (delta < 0 || exp(-delta / temperature) > (double)rand() / RAND_MAX) {
                currentState = nextState;
                currentHeuristic = nextHeuristic;

                if (currentHeuristic < bestHeuristic) {
                    bestState = currentState;
                    bestHeuristic = currentHeuristic;
                }
            }
        }

        temperature *= COOLING_FACTOR;
        moves++;
    }

    printf("Solution Moves:\n");
    while (bestState.holeRow != 0 || bestState.holeCol != 0) {
        if (bestState.holeRow > 0 && bestState.puzzle[bestState.holeRow - 1][bestState.holeCol] == bestHeuristic - 1) {
            printf("U ");
            makeMove(&bestState, bestState.holeRow - 1, bestState.holeCol);
        } else if (bestState.holeRow < SIZE - 1 && bestState.puzzle[bestState.holeRow + 1][bestState.holeCol] == bestHeuristic - 1) {
            printf("D ");
            makeMove(&bestState, bestState.holeRow + 1, bestState.holeCol);
        } else if (bestState.holeCol > 0 && bestState.puzzle[bestState.holeRow][bestState.holeCol - 1] == bestHeuristic - 1) {
            printf("L ");
            makeMove(&bestState, bestState.holeRow, bestState.holeCol - 1);
        } else if (bestState.holeCol < SIZE - 1 && bestState.puzzle[bestState.holeRow][bestState.holeCol + 1] == bestHeuristic - 1) {
            printf("R ");
            makeMove(&bestState, bestState.holeRow, bestState.holeCol + 1);
        }

        bestHeuristic--;
    }
    printf("\n");

    printf("\nSolution Puzzle State:\n");
    printPuzzle(&bestState);
}

int main() {
    solvePuzzle();
    return 0;
}
