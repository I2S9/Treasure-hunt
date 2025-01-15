# Compilateur
CC = gcc

# Flags de compilation
# -Wall : affiche tous les warnings
# -Wextra : affiche des warnings supplémentaires
# -Werror : traite les warnings comme des erreurs
# -pedantic : respecte strictement le standard C
# -std=c99 : utilise le standard C99
# -g : ajoute des informations de débogage
CFLAGS = -Wall -Wextra -Werror -pedantic -std=c99 -g
# Flags de liaison
# -lm : lie la bibliothèque mathématique
LDFLAGS = -lm

# Répertoires des fichiers
INCLUDES = -I Includes

# Paramètres pour l'exercice 2.2
NAME_2_2 = tresor
SRC_DIR_2_2 = Sources/2.2
SRC_2_2 = main.c tresor.c
OBJ_DIR_2_2 = Objets/2.2
OBJ_2_2 = $(SRC_2_2:%.c=$(OBJ_DIR_2_2)/%.o)
HEADERS_2_2 = Includes/2.2/tresor.h

# Paramètres pour l'exercice 2.3
NAME_2_3 = gain
SRC_DIR_2_3 = Sources/2.3
SRC_2_3 = main.c gain.c check.c
OBJ_DIR_2_3 = Objets/2.3
OBJ_2_3 = $(SRC_2_3:%.c=$(OBJ_DIR_2_3)/%.o)
HEADERS_2_3 = Includes/2.3/gain.h

# Paramètres pour le bonus (2.4)
NAME_TRESOR_BONUS = tresor_bonus
NAME_GAIN_BONUS = gain_bonus
SRC_DIR_TRESOR_BONUS = Sources/Bonus/Tresor
SRC_DIR_GAIN_BONUS = Sources/Bonus/Gain
SRC_TRESOR_BONUS = main.c tresor_bonus.c
SRC_GAIN_BONUS = main.c gain_bonus.c check.c
OBJ_DIR_TRESOR_BONUS = Objets/Bonus/Tresor
OBJ_DIR_GAIN_BONUS = Objets/Bonus/Gain
OBJ_TRESOR_BONUS = $(SRC_TRESOR_BONUS:%.c=$(OBJ_DIR_TRESOR_BONUS)/%.o)
OBJ_GAIN_BONUS = $(SRC_GAIN_BONUS:%.c=$(OBJ_DIR_GAIN_BONUS)/%.o)
HEADERS_TRESOR_BONUS = Includes/2.4/tresor_bonus.h
HEADERS_GAIN_BONUS = Includes/2.4/gain_bonus.h

# Créer les répertoires des objets s'ils n'existent pas
$(shell mkdir -p $(OBJ_DIR_2_2) $(OBJ_DIR_2_3) $(OBJ_DIR_TRESOR_BONUS) $(OBJ_DIR_GAIN_BONUS))

# Règle générale pour compiler les fichiers objets de l'exercice 2.2
$(OBJ_DIR_2_2)/%.o: $(SRC_DIR_2_2)/%.c $(HEADERS_2_2)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

# Règle générale pour compiler les fichiers objets de l'exercice 2.3
$(OBJ_DIR_2_3)/%.o: $(SRC_DIR_2_3)/%.c $(HEADERS_2_3)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

# Règle générale pour compiler les fichiers objets pour le bonus Tresor
$(OBJ_DIR_TRESOR_BONUS)/%.o: $(SRC_DIR_TRESOR_BONUS)/%.c $(HEADERS_TRESOR_BONUS)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

# Règle générale pour compiler les fichiers objets pour le bonus Gain
$(OBJ_DIR_GAIN_BONUS)/%.o: $(SRC_DIR_GAIN_BONUS)/%.c $(HEADERS_GAIN_BONUS)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

# Règle par défaut : compiler tous les exercices et bonus
all: 2.2 2.3 2.4

# Compilation de l'exercice 2.2
2.2: $(NAME_2_2)
$(NAME_2_2): $(OBJ_2_2)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

# Compilation de l'exercice 2.3
2.3: $(NAME_2_3)
$(NAME_2_3): $(OBJ_2_3)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

# Compilation des bonus (2.4)
bonus: $(NAME_TRESOR_BONUS) $(NAME_GAIN_BONUS)
2.4: $(NAME_TRESOR_BONUS) $(NAME_GAIN_BONUS)

# Compilation du bonus Tresor
$(NAME_TRESOR_BONUS): $(OBJ_TRESOR_BONUS)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

# Compilation du bonus Gain
$(NAME_GAIN_BONUS): $(OBJ_GAIN_BONUS)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

# Nettoyer les fichiers objets (sans les exécutables)
clean:
	rm -rf Objets

# Nettoyer tous les fichiers générés (exécutables inclus)
fclean: clean
	rm -f $(NAME_2_2) $(NAME_2_3) $(NAME_TRESOR_BONUS) $(NAME_GAIN_BONUS)

# Recompiler entièrement le projet
re: fclean all

.PHONY: all clean fclean re 2.2 2.3 2.4 bonus