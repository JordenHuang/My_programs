#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SIZE 3
#define POPULATION_SIZE 100
#define MAX_GENERATIONS 1000
#define MUTATION_RATE 0.1

typedef struct {
    int puzzle[SIZE][SIZE];
    int holeRow;
    int holeCol;
} State;

typedef struct {
    State state;
    int fitness;
} Individual;

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

int evaluateFitness(State *state) {
    int fitness = 0;

    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            int number = state->puzzle[i][j];
            if (number != 0) {
                int row = (number - 1) / SIZE;
                int col = (number - 1) % SIZE;
                if (row == i && col == j) {
                    fitness++;
                }
            }
        }
    }

    return fitness;
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

void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

void crossover(State *parent1, State *parent2, State *child) {
    int row = rand() % SIZE;
    int col = rand() % SIZE;

    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            if (i < row || (i == row && j <= col)) {
                child->puzzle[i][j] = parent1->puzzle[i][j];
            } else {
                child->puzzle[i][j] = parent2->puzzle[i][j];
            }
        }
    }
}

void mutate(State *state) {
    int row = state->holeRow;
    int col = state->holeCol;

    int move = rand() % 4; // 0: Up, 1: Down, 2: Left, 3: Right

    if (move == 0 && row > 0) { // Up
        swap(&state->puzzle[row][col], &state->puzzle[row - 1][col]);
        state->holeRow = row - 1;
    } else if (move == 1 && row < SIZE - 1) { // Down
        swap(&state->puzzle[row][col], &state->puzzle[row + 1][col]);
        state->holeRow = row + 1;
    } else if (move == 2 && col > 0) { // Left
        swap(&state->puzzle[row][col], &state->puzzle[row][col - 1]);
        state->holeCol = col - 1;
    } else if (move == 3 && col < SIZE - 1) { // Right
        swap(&state->puzzle[row][col], &state->puzzle[row][col + 1]);
        state->holeCol = col + 1;
    }
}

void solvePuzzle() {
    Individual population[POPULATION_SIZE];
    State bestState;
    int bestFitness = 0;

    srand(time(NULL));

    for (int i = 0; i < POPULATION_SIZE; i++) {
        initializePuzzle(&population[i].state);
        population[i].fitness = evaluateFitness(&population[i].state);
        if (population[i].fitness > bestFitness) {
            bestState = population[i].state;
            bestFitness = population[i].fitness;
        }
    }

    printf("Initial Puzzle State:\n");
    printPuzzle(&bestState);

    int generation = 0;

    while (bestFitness < SIZE * SIZE && generation < MAX_GENERATIONS) {
        Individual newPopulation[POPULATION_SIZE];
        int totalFitness = 0;

        for (int i = 0; i < POPULATION_SIZE; i++) {
            int parent1Index = rand() % POPULATION_SIZE;
            int parent2Index = rand() % POPULATION_SIZE;

            State child;
            crossover(&population[parent1Index].state, &population[parent2Index].state, &child);

            if ((double)rand() / RAND_MAX < MUTATION_RATE) {
                mutate(&child);
            }

            int childFitness = evaluateFitness(&child);

            newPopulation[i].state = child;
            newPopulation[i].fitness = childFitness;

            totalFitness += childFitness;
        }

        for (int i = 0; i < POPULATION_SIZE; i++) {
            population[i] = newPopulation[i];
            if (population[i].fitness > bestFitness) {
                bestState = population[i].state;
                bestFitness = population[i].fitness;
            }
        }

        generation++;
    }

    printf("Solution Moves:\n");
    while (bestState.holeRow != 0 || bestState.holeCol != 0) {
        if (bestState.holeRow > 0 && bestState.puzzle[bestState.holeRow - 1][bestState.holeCol] == bestFitness - 1) {
            printf("U ");
            swap(&bestState.puzzle[bestState.holeRow][bestState.holeCol], &bestState.puzzle[bestState.holeRow - 1][bestState.holeCol]);
            bestState.holeRow--;
        } else if (bestState.holeRow < SIZE - 1 && bestState.puzzle[bestState.holeRow + 1][bestState.holeCol] == bestFitness - 1) {
            printf("D ");
            swap(&bestState.puzzle[bestState.holeRow][bestState.holeCol], &bestState.puzzle[bestState.holeRow + 1][bestState.holeCol]);
            bestState.holeRow++;
        } else if (bestState.holeCol > 0 && bestState.puzzle[bestState.holeRow][bestState.holeCol - 1] == bestFitness - 1) {
            printf("L ");
            swap(&bestState.puzzle[bestState.holeRow][bestState.holeCol], &bestState.puzzle[bestState.holeRow][bestState.holeCol - 1]);
            bestState.holeCol--;
        } else if (bestState.holeCol < SIZE - 1 && bestState.puzzle[bestState.holeRow][bestState.holeCol + 1] == bestFitness - 1) {
            printf("R ");
            swap(&bestState.puzzle[bestState.holeRow][bestState.holeCol], &bestState.puzzle[bestState.holeRow][bestState.holeCol + 1]);
            bestState.holeCol++;
        }
        bestFitness--;
    }
    printf("\n");

    printf("\nSolution Puzzle State:\n");
    printPuzzle(&bestState);
}

int main() {
    solvePuzzle();
    return 0;
}