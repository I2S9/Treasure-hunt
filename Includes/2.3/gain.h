#ifndef GAIN_H
#define GAIN_H

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SIZE 1000
#define MAX_PATH_LENGTH (2 * MAX_SIZE)

// Structure pour stocker le résultat et le chemin
typedef struct
{
	int			max_treasure;
	int			path_length;
	char		path[MAX_PATH_LENGTH];
}				TreasureResult;

// Structure de la grille
typedef struct
{
	int			grid[MAX_SIZE][MAX_SIZE];
	int			rows;
	int			cols;
}				TreasureGrid;

// Prototypes des fonctions

bool			read_grid_from_file(const char *filename, TreasureGrid *grid);
TreasureResult	calculate_optimal_treasure(TreasureGrid *grid);
void			print_treasure_result(TreasureResult *result);

#endif