#ifndef TRESOR_H
#define TRESOR_H

#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_GRID_SIZE 1000
#define MAX_LINE_LENGTH 10000

// Structure pour stocker les informations de la grille
typedef struct
{
	int	grid[MAX_GRID_SIZE][MAX_GRID_SIZE];
	int	rows;
	int	cols;
}		TresorGrid;

// Prototypes des fonctions

// Fonctions de lecture et validation
bool	read_grid_from_file(const char *filename, TresorGrid *grid);
bool	validate_grid(TresorGrid *grid);

// Fonction de calcul du trésor
int		tresor(int i, int j, TresorGrid *grid);

#endif