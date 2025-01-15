#include "../../Includes/2.3/gain.h"

int main(int argc, char* argv[]) {
    // Vérifier le nombre d'arguments
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <fichier_grille>\n", argv[0]);
        return 1;
    }

    // Structure pour stocker la grille
    TreasureGrid grid;

    // Lire le fichier de grille
    if (!read_grid_from_file(argv[1], &grid)) {
        fprintf(stderr, "Erreur lors de la lecture de la grille\n");
        return 1;
    }

    // Calculer le trésor optimal
    TreasureResult result = calculate_optimal_treasure(&grid);

    // Afficher le résultat
    print_treasure_result(&result);

    return 0;
}