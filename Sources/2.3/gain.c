#include "../../Includes/2.3/gain.h"

// Tableau de mémoïsation global pour stocker les résultats intermédiaires
int gain[MAX_SIZE][MAX_SIZE];

/**
 * @brief Calcule récursivement le trésor maximal possible
 * 
 * Cette fonction utilise la mémoïsation pour calculer le chemin
 * qui maximise la somme des trésors. Elle explore les chemins
 * possibles en allant soit à droite soit en bas.
 * 
 * @param i Position courante en ligne
 * @param j Position courante en colonne
 * @param grid Pointeur vers la grille de trésor
 * @return Le trésor maximal possible depuis la position (i,j)
 */
int calculate_max_treasure(int i, int j, TreasureGrid* grid) {
    // Vérifier si on est sorti des limites de la grille
    if (i >= grid->rows || j >= grid->cols) 
        return 0;

    // Si le résultat est déjà calculé, le retourner
    if (gain[i][j] != -1) 
        return gain[i][j];

    // Calculer le maximum entre aller à droite et aller en bas
    int right = calculate_max_treasure(i, j + 1, grid);
    int down = calculate_max_treasure(i + 1, j, grid);

    // Stocker et retourner le maximum
    gain[i][j] = grid->grid[i][j] + (right > down ? right : down);
    return gain[i][j];
}

/**
 * @brief Reconstruit le chemin optimal pour atteindre le trésor maximal
 * 
 * Cette fonction détermine et enregistre le chemin optimal en suivant
 * les valeurs maximales calculées dans le tableau de mémoïsation.
 * Le chemin est stocké sous forme de chaîne de caractères avec le format
 * "(x,y) -> (x,y) -> ..."
 * 
 * @param grid Pointeur vers la grille de trésor
 * @param result Pointeur vers la structure stockant le résultat
 */
void reconstruct_path(TreasureGrid* grid, TreasureResult* result) {
    int i = 0, j = 0;
    result->path_length = 0;
    result->path[result->path_length++] = '(';
    
    // Convertir les indices en représentation de coordonnées
    result->path[result->path_length++] = '1' + i;
    result->path[result->path_length++] = ',';
    result->path[result->path_length++] = '1' + j;
    result->path[result->path_length++] = ')';

    while (i < grid->rows - 1 || j < grid->cols - 1) {
        // Ajouter un séparateur entre les points
        result->path[result->path_length++] = ' ';
        result->path[result->path_length++] = '-';
        result->path[result->path_length++] = '>';
        result->path[result->path_length++] = ' ';

        // Choisir la direction qui maximise le gain
        if (i == grid->rows - 1) {
            // On ne peut qu'aller à droite
            j++;
        } else if (j == grid->cols - 1) {
            // On ne peut qu'aller en bas
            i++;
        } else {
            // Comparer les gains potentiels
            if (gain[i+1][j] > gain[i][j+1]) {
                i++;
            } else {
                j++;
            }
        }

        // Ajouter le nouveau point
        result->path[result->path_length++] = '(';
        result->path[result->path_length++] = '1' + i;
        result->path[result->path_length++] = ',';
        result->path[result->path_length++] = '1' + j;
        result->path[result->path_length++] = ')';
    }

    // Terminer la chaîne
    result->path[result->path_length] = '\0';
}

/**
 * @brief Calcule le trésor optimal et son chemin associé
 * 
 * Cette fonction principale initialise le tableau de mémoïsation,
 * calcule le trésor maximal possible et reconstruit le chemin optimal.
 * Elle combine les résultats dans une structure TreasureResult.
 * 
 * @param grid Pointeur vers la grille de trésor
 * @return Structure TreasureResult contenant le trésor max et le chemin
 */
TreasureResult calculate_optimal_treasure(TreasureGrid* grid) {
    TreasureResult result = {0};

    // Initialiser le tableau gain avec -1
    for (int i = 0; i < grid->rows; i++) {
        for (int j = 0; j < grid->cols; j++) {
            gain[i][j] = -1;
        }
    }

    // Calculer le trésor maximum
    result.max_treasure = calculate_max_treasure(0, 0, grid);

    // Reconstruire le chemin
    reconstruct_path(grid, &result);

    return result;
}

/**
 * @brief Affiche le résultat du calcul du trésor optimal
 * 
 * Cette fonction affiche de manière formatée le trésor maximal
 * trouvé ainsi que le chemin optimal pour l'atteindre.
 * 
 * @param result Pointeur vers la structure contenant le résultat
 */
void print_treasure_result(TreasureResult* result) {
    printf("Trésor maximum : %d\n", result->max_treasure);
    printf("Chemin optimal : %s\n", result->path);
}