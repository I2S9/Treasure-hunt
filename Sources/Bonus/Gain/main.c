#include "../../../Includes/2.4/gain_bonus.h"

int main(int argc, char* argv[]) {
    // Vérifier le nombre d'arguments
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <fichier_grille> <k>\n", argv[0]);
        return 1;
    }

    // Structure pour stocker la grille
    TreasureGrid grid;

    // Lire le fichier de grille
    if (!read_grid_from_file(argv[1], &grid)) {
        fprintf(stderr, "Erreur lors de la lecture de la grille\n");
        return 1;
    }

    // Lire la valeur de k
    long k = atol(argv[2]);
    // Vérifier que k est un entier positif
    if (k <= 0) {
        fprintf(stderr, "Erreur : la valeur de k doit être un entier positif\n");
        return 1;
    }
    // Vérifier que k n'est pas supérieur au nombre total de salles
    if (k > grid.rows * grid.cols) {
        fprintf(stderr, "Erreur : k ne peut pas être supérieur au nombre total de salles (%d)\n", grid.rows * grid.cols);
        return 1;
    }
    // Vérifier que k n'est pas plus grand que INT_MAX
    if (k > INT_MAX) {
        fprintf(stderr, "Erreur : k ne peut pas être plus grand que %d\n", INT_MAX);
        return 1;
    }
    // Vérifier que k n'est pas inférieur à la distance minimale
    int min_moves = (grid.rows - 1) + (grid.cols - 1);
    if (k < min_moves) {
        fprintf(stderr, "Erreur : k doit être au moins égal à la distance minimale (%d).\n", min_moves);
        return 1;
    }

    // Calculer le trésor optimal avec k déplacements
    TreasureResult result = calculate_optimal_treasure_with_k(&grid, k);
    if (result.max_treasure == INT_MIN) {
        printf("Aucun chemin valide trouvé avec %ld déplacement(s).\n", k);
    } else

    // Afficher le résultat
    print_treasure_result(&result);

    return 0;
}