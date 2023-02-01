# Variables
CC = gcc                   # Compilateur C
CFLAGS = -ggdb -Wall -Og   # -g pour débugger -Wall pour les warnings -O pour optimiser
EXEC = exe                 # Nom de l'executable
SRC = $(wildcard *.c)      # Fichiers sources
OBJ = $(SRC:.c=.o)         # Fichiers objets, ne pas modifier sauf si l'extension n'est pas .c
LDFLAGS = -lm              # Options de l'éditeur de liens
SAV = saves/		       # Dossier de sauvegarde

# Compilation du programme
all : $(EXEC) 
$(EXEC): $(OBJ)
	$(CC) $(CFLAGS) $^ $(LDFLAGS) -o $@

# Compilation des objets
.c.o :
	$(CC) $(CFLAGS) -c $^ -o $@

# Création de la documentation
doc : 
	doxygen Doxyfile

# Nettoyage des fichiers objets
.PHONY : clean
clean : save
	rm -rf $(OBJ)
	rm -rf $(EXEC)

# Sauvegarde des fichiers .c et .h
.PHONY : save
save :
	mkdir -p $(SAV)
	cp $(SRC) *.h $(SAV)

# Restauration des fichiers sauvegardés
.PHONY : restore
restore : 
	cp -r $(SAV)*.c $(SAV)*.h .

