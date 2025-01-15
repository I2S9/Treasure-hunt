#ifndef TRESOR_BONUS_H
#define TRESOR_BONUS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#include <limits.h>

#define MAX_GRID_SIZE 100
#define MAX_LINE_LENGTH 1024

// Structure représentant une grille
typedef struct {
    int grid[MAX_GRID_SIZE][MAX_GRID_SIZE];
    int rows;
    int cols;
} TresorGrid;

// Prototypes des fonctions
bool is_valid_line(const char* line);
bool validate_grid(TresorGrid* grid);
bool read_grid_from_file(const char* filename, TresorGrid* grid);
void initialize_memo(int rows, int cols, long k);
int tresor_with_k(int i, int j, long k, TresorGrid* grid);
int calculer_tresor_maximal(TresorGrid* grid, long k);

#endif