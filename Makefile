NAME = etudes
C_FILES = main.c scatter_gather_io.c
FLAGS = -Wall -Wextra -pedantic -std=c11

etudes: $(C_FILES)
	$(CC) $(C_FILES) -o $(NAME) $(FLAGS)
