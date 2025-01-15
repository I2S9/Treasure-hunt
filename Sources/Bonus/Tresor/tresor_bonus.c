#include "../../../Includes/2.4/tresor_bonus.h"

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
    return true;
}

/**
 * @brief Fonction récursive avec mémorisation pour calculer le gain maximal
 * tout en respectant la contrainte de k salles visitées.
 * 
 * Cette fonction prend en compte les 4 directions possibles (haut, bas, gauche, droite)
 * ainsi que la contrainte k pour calculer le gain maximal.
 * 
 * @param i Position ligne courante 
 * @param j Position colonne courante
 * @param k Nombre de salles visitées restantes
 * @param grid Pointeur vers la structure contenant la grille
 * @param memo Table de mémorisation pour stocker les résultats calculés
 * @return int Le gain maximal calculé pour la position donnée
 */
int tresor(int i, int j, long k, TresorGrid* grid, int memo[MAX_GRID_SIZE][MAX_GRID_SIZE][MAX_GRID_SIZE]) {
    // Si k est épuisé avant d'atteindre la sortie
    if (k < 0) return INT_MIN;

    // Si on est arrivé à la sortie (coin inférieur droit)
    if (i == grid->rows - 1 && j == grid->cols - 1)
        return grid->grid[i][j];

    // Si la position est invalide (hors grille)
    if (i < 0 || j < 0 || i >= grid->rows || j >= grid->cols)
        return INT_MIN;

    // Si la position est déjà mémorisée, retourner la valeur mémorisée
    if (memo[i][j][k] != -1)
        return memo[i][j][k];

    // Calculer les chemins possibles dans les 4 directions
    int down = tresor(i + 1, j, k - 1, grid, memo);
    int right = tresor(i, j + 1, k - 1, grid, memo);
    int up = tresor(i - 1, j, k - 1, grid, memo);
    int left = tresor(i, j - 1, k - 1, grid, memo);

    // Trouver le maximum parmi les chemins valides
    int max_path = INT_MIN;
    if (down != INT_MIN) max_path = down;
    if (right != INT_MIN) max_path = max_path > right ? max_path : right;
    if (up != INT_MIN) max_path = max_path > up ? max_path : up;
    if (left != INT_MIN) max_path = max_path > left ? max_path : left;

    // Si aucun chemin valide n'a été trouvé
    if (max_path == INT_MIN) {
        memo[i][j][k] = INT_MIN;
        return INT_MIN;
    }

    // Mémoriser le résultat pour cette position et ce nombre de salles
    memo[i][j][k] = grid->grid[i][j] + max_path;
    return memo[i][j][k];
}

/**
 * @brief Fonction pour initialiser la mémorisation et appeler la fonction principale de calcul du trésor
 * 
 * Cette fonction initialise la table de mémorisation et lance le calcul avec k salles restantes.
 * 
 * @param grid Grille de trésor
 * @param k Nombre de salles visitées autorisées
 * @return int Le trésor maximal obtenu
 */
int calculer_tresor_maximal(TresorGrid* grid, long k) {
    // Initialisation de la mémorisation (-1 signifie que la position n'a pas encore été visitée)
    int memo[MAX_GRID_SIZE][MAX_GRID_SIZE][MAX_GRID_SIZE];
    for (int i = 0; i < grid->rows; i++) {
        for (int j = 0; j < grid->cols; j++) {
            for (int l = 0; l <= k; l++) {
                memo[i][j][l] = -1;
            }
        }
    }

    // Appeler la fonction récursive à partir de (0, 0) avec k salles restantes
    return tresor(0, 0, k, grid, memo);
}