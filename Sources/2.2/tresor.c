#include "../../Includes/2.2/tresor.h"

/**
 * @brief Vérifie si une ligne de texte est valide
 * 
 * Cette fonction contrôle que la ligne ne contient que des
 * caractères autorisés : chiffres, espaces, tabulations et 
 * caractères de nouvelle ligne.
 * 
 * @param line Chaîne de caractères à valider
 * @return true Si la ligne est valide, false sinon
 */
bool is_valid_line(const char* line) {
    for (int i = 0; line[i] != '\0'; i++) {
        if (!isdigit(line[i]) && !isspace(line[i]) && line[i] != '-') {
            return false;
        }
    }
    return true;
}

/**
 * @brief Lit une grille de trésor à partir d'un fichier
 * 
 * Cette fonction lit le contenu d'un fichier et le convertit
 * en une grille de trésor. Elle effectue plusieurs validations :
 * - Ouverture du fichier
 * - Taille du fichier
 * - Validité des lignes
 * - Dimensions de la grille
 * 
 * @param filename Chemin du fichier à lire
 * @param grid Pointeur vers la structure de grille à remplir
 * @return true Si la lecture et la validation réussissent, false sinon
 */
bool read_grid_from_file(const char* filename, TresorGrid* grid) {
    FILE* file = fopen(filename, "r");
    if (!file) {
        fprintf(stderr, "Erreur : impossible d'ouvrir le fichier %s\n", filename);
        return false;
    }

    char line[MAX_LINE_LENGTH];
    grid->rows = 0;
    grid->cols = -1;

    // Vérification préliminaire de la taille du fichier
    fseek(file, 0, SEEK_END);
    long file_size = ftell(file);
    rewind(file);

    if (file_size > MAX_LINE_LENGTH * MAX_GRID_SIZE) {
        fprintf(stderr, "Erreur : fichier trop volumineux\n");
        fclose(file);
        return false;
    }

    // Lecture ligne par ligne
    while (fgets(line, sizeof(line), file) && grid->rows < MAX_GRID_SIZE) {
        // Ignorer les lignes vides
        if (strlen(line) <= 1) continue;

        // Vérifier la validité de la ligne
        if (!is_valid_line(line)) {
            fprintf(stderr, "Erreur : ligne invalide détectée\n");
            fclose(file);
            return false;
        }

        // Parsing des nombres de la ligne
        char* token = strtok(line, " \t\n");
        int col_count = 0;
        int row = grid->rows;

        while (token && col_count < MAX_GRID_SIZE) {
            // Convertir et stocker chaque nombre
            grid->grid[row][col_count] = atoi(token);
            col_count++;
            token = strtok(NULL, " \t\n");
        }

        // Vérifier la largeur de la grille
        if (grid->cols == -1) {
            grid->cols = col_count;
        } else if (col_count != grid->cols) {
            fprintf(stderr, "Erreur : la grille n'est pas rectangulaire\n");
            fclose(file);
            return false;
        }

        grid->rows++;

        // Vérification supplémentaire pour empêcher les grilles trop grandes
        if (grid->rows >= MAX_GRID_SIZE) {
            fprintf(stderr, "Erreur : nombre de lignes dépasse la taille maximale autorisée\n");
            fclose(file);
            return false;
        }
    }

    fclose(file);
    return validate_grid(grid);
}

/**
 * @brief Valide les dimensions d'une grille de trésor
 * 
 * Cette fonction vérifie que la grille n'est ni vide
 * ni trop grande, en respectant les contraintes définies
 * dans MAX_GRID_SIZE.
 * 
 * @param grid Pointeur vers la structure de grille à valider
 * @return true Si la grille est valide, false sinon
 */
bool validate_grid(TresorGrid* grid) {
    // Vérifier les dimensions
    if (grid->rows == 0 || grid->cols == 0) {
        fprintf(stderr, "Erreur : grille vide\n");
        return false;
    }

    if (grid->rows > MAX_GRID_SIZE || grid->cols > MAX_GRID_SIZE) {
        fprintf(stderr, "Erreur : dimensions de grille trop grandes\n");
        return false;
    }

    return true;
}

/**
 * @brief Calcule le gain maximal pour atteindre une position donnée
 * 
 * Cette fonction implémente un algorithme récursif pour calculer
 * le gain maximal qu'on peut obtenir en atteignant la position (i,j)
 * dans la grille de trésor.
 * 
 * @param i Position ligne courante
 * @param j Position colonne courante
 * @param grid Pointeur vers la structure contenant la grille
 * @return int Le gain maximal calculé pour la position donnée
 */
int tresor(int i, int j, TresorGrid* grid) {
    // Si on est arrivé à la fin de la grille
    if (i == grid->rows && j == grid->cols)
        return grid->grid[i - 1][j - 1];

    // Si on est arrivé à la fin de la ligne
    if (i == grid->rows)
        return grid->grid[i - 1][j - 1] + tresor(i, j + 1, grid);

    // Si on est arrivé à la fin de la colonne
    if (j == grid->cols)
        return grid->grid[i - 1][j - 1] + tresor(i + 1, j, grid);

    // On regarde les deux chemins possibles
    int down = tresor(i + 1, j, grid);
    int right = tresor(i, j + 1, grid);

    // On retourne le chemin le plus rentable pour le joueur
    return grid->grid[i - 1][j - 1] + (down > right ? down : right);
}