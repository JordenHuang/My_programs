#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define SIZE 3
#define MAX_MOVES 150

typedef struct PuzzleState {
    int puzzle[SIZE][SIZE];
    int holeRow;
    int holeCol;
    int g;
    int h;
    struct PuzzleState* parent;
} PuzzleState;

typedef struct PriorityQueue {
    PuzzleState** states;
    int size;
    int capacity;
} PriorityQueue;

PuzzleState* createPuzzleState(int puzzle[SIZE][SIZE], int holeRow, int holeCol, int g, int h, PuzzleState* parent) {
    PuzzleState* newState = (PuzzleState*)malloc(sizeof(PuzzleState));
    memcpy(newState->puzzle, puzzle, sizeof(newState->puzzle));
    newState->holeRow = holeRow;
    newState->holeCol = holeCol;
    newState->g = g;
    newState->h = h;
    newState->parent = parent;
    return newState;
}

void destroyPuzzleState(PuzzleState* state) {
    free(state);
}

PuzzleState* clonePuzzleState(PuzzleState* state) {
    PuzzleState* cloneState = createPuzzleState(state->puzzle, state->holeRow, state->holeCol,
                                               state->g, state->h, state->parent);
    return cloneState;
}

bool isGoalState(PuzzleState* state) {
    int goal[SIZE][SIZE] = {{1, 2, 3}, {4, 5, 6}, {7, 8, 0}};
    return memcmp(state->puzzle, goal, sizeof(state->puzzle)) == 0;
}

int calculateHeuristic(PuzzleState* state) {
    int count = 0;
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            if (state->puzzle[i][j] != 0) {
                int goalRow = (state->puzzle[i][j] - 1) / SIZE;
                int goalCol = (state->puzzle[i][j] - 1) % SIZE;
                count += abs(i - goalRow) + abs(j - goalCol);
            }
        }
    }
    return count;
}

void swap(int* a, int* b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

void printPuzzleState(PuzzleState* state) {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            printf("%d ", state->puzzle[i][j]);
        }
        printf("\n");
    }
}

void printSolutionPath(PuzzleState* state) {
    if (state->parent != NULL) {
        printSolutionPath(state->parent);
        if (state->parent->holeRow > state->holeRow) {
            printf("U ");
        } else if (state->parent->holeRow < state->holeRow) {
            printf("D ");
        } else if (state->parent->holeCol > state->holeCol) {
            printf("L ");
        } else if (state->parent->holeCol < state->holeCol) {
            printf("R ");
        }
    }
}

void destroyPriorityQueue(PriorityQueue* queue) {
    free(queue->states);
    free(queue);
}

PriorityQueue* createPriorityQueue() {
    PriorityQueue* queue = (PriorityQueue*)malloc(sizeof(PriorityQueue));
    queue->states = (PuzzleState**)malloc(sizeof(PuzzleState*) * MAX_MOVES);
    queue->size = 0;
    queue->capacity = MAX_MOVES;
    return queue;
}

void enqueue(PriorityQueue* queue, PuzzleState* state) {
    int i = queue->size;
    while (i > 0 && (state->g + state->h) < (queue->states[i - 1]->g + queue->states[i - 1]->h)) {
        queue->states[i] = queue->states[i - 1];
        i--;
    }
    queue->states[i] = state;
    queue->size++;
}

PuzzleState* dequeue(PriorityQueue* queue) {
    PuzzleState* state = queue->states[0];
    queue->size--;
    for (int i = 0; i < queue->size; i++) {
        queue->states[i] = queue->states[i + 1];
    }
    return state;
}

bool isSolvable(int puzzle[SIZE][SIZE]) {
    int inversions = 0;
    int puzzleArray[SIZE * SIZE];
    int k = 0;

    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            puzzleArray[k] = puzzle[i][j];
            k++;
        }
    }

    for (int i = 0; i < SIZE * SIZE - 1; i++) {
        for (int j = i + 1; j < SIZE * SIZE; j++) {
            if (puzzleArray[i] && puzzleArray[j] && puzzleArray[i] > puzzleArray[j]) {
                inversions++;
            }
        }
    }

    return inversions % 2 == 0;
}

PuzzleState* solvePuzzle(int puzzle[SIZE][SIZE]) {
    if (!isSolvable(puzzle)) {
        printf("The puzzle is unsolvable.\n");
        return NULL;
    }

    PuzzleState* initialState = createPuzzleState(puzzle, 0, 0, 0, 0, NULL);
    PuzzleState* currentState = NULL;
    PriorityQueue* openList = createPriorityQueue();

    enqueue(openList, initialState);

    while (openList->size > 0) {
        currentState = dequeue(openList);

        if (isGoalState(currentState)) {
            destroyPriorityQueue(openList);
            return currentState;
        }

        int holeRow = currentState->holeRow;
        int holeCol = currentState->holeCol;

        if (holeRow > 0) {
            PuzzleState* newState = clonePuzzleState(currentState);
            swap(&newState->puzzle[holeRow][holeCol], &newState->puzzle[holeRow - 1][holeCol]);
            newState->holeRow--;
            newState->g++;
            newState->h = calculateHeuristic(newState);
            enqueue(openList, newState);
        }

        if (holeRow < SIZE - 1) {
            PuzzleState* newState = clonePuzzleState(currentState);
            swap(&newState->puzzle[holeRow][holeCol], &newState->puzzle[holeRow + 1][holeCol]);
            newState->holeRow++;
            newState->g++;
            newState->h = calculateHeuristic(newState);
            enqueue(openList, newState);
        }

        if (holeCol > 0) {
            PuzzleState* newState = clonePuzzleState(currentState);
            swap(&newState->puzzle[holeRow][holeCol], &newState->puzzle[holeRow][holeCol - 1]);
            newState->holeCol--;
            newState->g++;
            newState->h = calculateHeuristic(newState);
            enqueue(openList, newState);
        }

        if (holeCol < SIZE - 1) {
            PuzzleState* newState = clonePuzzleState(currentState);
            swap(&newState->puzzle[holeRow][holeCol], &newState->puzzle[holeRow][holeCol + 1]);
            newState->holeCol++;
            newState->g++;
            newState->h = calculateHeuristic(newState);
            enqueue(openList, newState);
        }
    }

    destroyPriorityQueue(openList);
    return NULL;
}

int main() {
    int puzzle[SIZE][SIZE] = {{1, 2, 3}, {4, 0, 5}, {7, 8, 6}};

    PuzzleState* solution = solvePuzzle(puzzle);

    if (solution != NULL) {
        printf("Initial State:\n");
        printPuzzleState(solution);
        printf("Moves: ");
        printSolutionPath(solution);
        printf("\nFinal State:\n");
        printPuzzleState(solution);
    }

    destroyPuzzleState(solution);

    return 0;
}
