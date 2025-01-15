#include "../../../Includes/2.4/tresor_bonus.h"

int main(int argc, char* argv[]) {
    // Vérifier le nombre d'arguments
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <fichier_grille> <k>\n", argv[0]);
        return 1;
    }

    // Structure pour stocker la grille
    TresorGrid grid;

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
    // Vérifier que k n'est pas plus grand que INT_MAX
    if (k > INT_MAX) {
        fprintf(stderr, "Erreur : k ne peut pas être plus grand que %d\n", INT_MAX);
        return 1;
    }
    // Vérifier que k n'est pas supérieur au nombre total de salles
    if (k > grid.rows * grid.cols) {
        fprintf(stderr, "Erreur : k ne peut pas être supérieur au nombre total de salles (%d)\n", grid.rows * grid.cols);
        return 1;
    }
    // Calculer le trésor maximal
    int max_tresor = calculer_tresor_maximal(&grid, k);

    if (max_tresor == -1 || max_tresor == INT_MIN) {
        printf("Aucun chemin valide trouvé avec %ld salle(s) visitée(s).\n", k);
    } else
        // Afficher le résultat
        printf("Trésor maximum avec au plus %ld salles visitées : %d\n", k, max_tresor);
    

    return 0;
}