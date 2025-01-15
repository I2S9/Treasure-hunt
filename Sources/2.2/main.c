#include "../../Includes/2.2/tresor.h"

int main(int argc, char* argv[]) {
    // Vérifier le nombre d'arguments
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <fichier_grille>\n", argv[0]);
        return 1;
    }

    // Structure pour stocker la grille
    TresorGrid grid;

    // Lire le fichier de grille
    if (!read_grid_from_file(argv[1], &grid)) {
        fprintf(stderr, "Erreur lors de la lecture de la grille\n");
        return 1;
    }

    // Calculer le trésor maximum
    int max_tresor = tresor(1, 1, &grid);

    // Afficher le résultat
    printf("Trésor maximum de (1,1) à (%d,%d): %d\n", grid.rows, grid.cols, max_tresor);

    return 0;
}