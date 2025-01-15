#include "../../../Includes/2.4/gain_bonus.h"

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
        if (line[i] != ' ' && line[i] != '\t' && 
            line[i] != '\n' && (line[i] < '0' || line[i] > '9')) {
            return false;
        }
    }
    return true;
}

/**
 * @brief Valide les dimensions de la grille
 * 
 * Cette fonction vérifie que la grille n'est ni vide 
 * ni trop grande, en respectant les contraintes définies.
 * 
 * @param grid Pointeur vers la structure de grille à valider
 * @return true Si la grille est valide, false sinon
 */
bool validate_grid(TreasureGrid* grid) {
    // Vérifier que la grille n'est pas vide
    if (grid->rows == 0 || grid->cols == 0) {
        fprintf(stderr, "Erreur : grille vide\n");
        return false;
    }

    // Vérifier que les dimensions ne dépassent pas la taille maximale
    if (grid->rows > MAX_SIZE || grid->cols > MAX_SIZE) {
        fprintf(stderr, "Erreur : dimensions de grille trop grandes\n");
        return false;
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
bool read_grid_from_file(const char* filename, TreasureGrid* grid) {
    // Tentative d'ouverture du fichier
    FILE* file = fopen(filename, "r");
    if (!file) {
        fprintf(stderr, "Erreur : impossible d'ouvrir le fichier %s\n", filename);
        return false;
    }

    char line[MAX_PATH_LENGTH];  // Tampon pour la lecture des lignes
    grid->rows = 0;
    grid->cols = -1;

    // Vérification préliminaire de la taille du fichier
    fseek(file, 0, SEEK_END);
    long file_size = ftell(file);
    rewind(file);

    // Contrôle de la taille maximale du fichier
    if (file_size > MAX_PATH_LENGTH * MAX_SIZE) {
        fprintf(stderr, "Erreur : fichier trop volumineux\n");
        fclose(file);
        return false;
    }

    // Lecture ligne par ligne
    while (fgets(line, sizeof(line), file) && grid->rows < MAX_SIZE) {
        // Ignorer les lignes vides
        if (strlen(line) <= 1) continue;

        // Validation de la ligne courante
        if (!is_valid_line(line)) {
            fprintf(stderr, "Erreur : ligne invalide détectée\n");
            fclose(file);
            return false;
        }

        // Analyse des nombres de la ligne
        char* token = strtok(line, " \t\n");
        int col_count = 0;
        int row = grid->rows;

        // Conversion et stockage des nombres
        while (token && col_count < MAX_SIZE) {
            grid->grid[row][col_count] = atoi(token);
            col_count++;
            token = strtok(NULL, " \t\n");
        }

        // Vérification de la largeur de la grille
        if (grid->cols == -1) {
            grid->cols = col_count;
        } else if (col_count != grid->cols) {
            fprintf(stderr, "Erreur : la grille n'est pas rectangulaire\n");
            fclose(file);
            return false;
        }

        grid->rows++;

        // Contrôle du nombre maximum de lignes
        if (grid->rows >= MAX_SIZE) {
            fprintf(stderr, "Erreur : nombre de lignes dépasse la taille maximale autorisée\n");
            fclose(file);
            return false;
        }
    }

    // Fermeture du fichier et validation finale de la grille
    fclose(file);
    return validate_grid(grid);
}