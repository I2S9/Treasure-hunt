#include "../../../Includes/2.4/gain_bonus.h"

// Tableau de mémoïsation global pour stocker les résultats intermédiaires
int gain[MAX_SIZE][MAX_SIZE][MAX_SIZE];

/**
 * @brief Calcule récursivement le trésor maximal avec une limite de déplacements
 * 
 * Cette fonction utilise un tableau tridimensionnel pour gérer la contrainte \( k \),
 * qui représente le nombre maximum de déplacements restants.
 * 
 * @param i Position courante en ligne
 * @param j Position courante en colonne
 * @param k Déplacements restants
 * @param grid Pointeur vers la grille de trésor
 * @return Le trésor maximal possible depuis la position (i,j) avec \( k \) déplacements restants
 */
int calculate_max_treasure_with_k(int i, int j, int k, TreasureGrid* grid) {
    // Vérifier les limites de la grille
    if (i < 0 || j < 0 || i >= grid->rows || j >= grid->cols || k <= 0)
        return INT_MIN;

    // Si on est à la sortie et que k est suffisant, retourner la valeur de la case
    if (i == grid->rows - 1 && j == grid->cols - 1)
        return grid->grid[i][j];

    // Si le résultat est déjà calculé, le retourner
    if (gain[i][j][k] != -1)
        return gain[i][j][k];

    // Calculer les gains possibles en se déplaçant dans les 4 directions
    int up = calculate_max_treasure_with_k(i - 1, j, k - 1, grid);
    int down = calculate_max_treasure_with_k(i + 1, j, k - 1, grid);
    int left = calculate_max_treasure_with_k(i, j - 1, k - 1, grid);
    int right = calculate_max_treasure_with_k(i, j + 1, k - 1, grid);

    // Calculer le maximum des gains
    int max_gain = fmax(fmax(up, down), fmax(left, right));
    gain[i][j][k] = (max_gain == INT_MIN) ? INT_MIN : grid->grid[i][j] + max_gain;

    return gain[i][j][k];
}

/**
 * @brief Calculer le trésor optimal avec une contrainte de déplacements
 * 
 * @param grid Pointeur vers la grille de trésor
 * @param k Nombre maximum de déplacements
 * @return Structure TreasureResult contenant le trésor maximal et le chemin optimal
 */
TreasureResult calculate_optimal_treasure_with_k(TreasureGrid* grid, int k) {
    TreasureResult result = {0};

    // Initialiser le tableau gain avec -1
    memset(gain, -1, sizeof(gain));

    // Calculer le trésor maximum avec la contrainte de \( k \)
    result.max_treasure = calculate_max_treasure_with_k(0, 0, k, grid);

    // Reconstruire le chemin (adapté pour inclure \( k \))
    reconstruct_path_with_k(grid, &result, k);

    return result;
}

/**
 * @brief Reconstruire le chemin optimal en fonction de \( k \)
 * 
 * Cette fonction suit les valeurs du tableau `gain` pour déterminer
 * le chemin optimal, en prenant en compte les déplacements restants.
 * 
 * @param grid Pointeur vers la grille
 * @param result Structure pour stocker le résultat
 * @param k Nombre de déplacements restants
 */
void reconstruct_path_with_k(TreasureGrid* grid, TreasureResult* result, int k) {
    int i = 0, j = 0;
    result->path_length = 0;

    while (i < grid->rows || j < grid->cols) {
        result->path[result->path_length++] = '(';
        result->path[result->path_length++] = '1' + i;
        result->path[result->path_length++] = ',';
        result->path[result->path_length++] = '1' + j;
        result->path[result->path_length++] = ')';

        if (k == 0 || (i == grid->rows - 1 && j == grid->cols - 1)) break;

        int up = (i > 0) ? gain[i - 1][j][k - 1] : INT_MIN;
        int down = (i < grid->rows - 1) ? gain[i + 1][j][k - 1] : INT_MIN;
        int left = (j > 0) ? gain[i][j - 1][k - 1] : INT_MIN;
        int right = (j < grid->cols - 1) ? gain[i][j + 1][k - 1] : INT_MIN;

        // Ajouter la flèche seulement si on n'est pas à la dernière coordonnée
        result->path[result->path_length++] = ' ';
        result->path[result->path_length++] = '-';
        result->path[result->path_length++] = '>';
        result->path[result->path_length++] = ' ';

        if (down >= fmax(fmax(up, left), right)) i++;
        else if (right >= fmax(fmax(up, left), down)) j++;
        else if (up >= fmax(fmax(left, right), down)) i--;
        else j--;
        k--;
    }

    result->path[result->path_length] = '\0';
}

void print_treasure_result(TreasureResult* result) {
    printf("Trésor maximum : %d\n", result->max_treasure);
    printf("Chemin optimal : %s\n", result->path);
}