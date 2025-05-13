########## Makefile para el proyecto de los filósofos ##########

# Nombre del ejecutable
NAME = philo

# Directorios
SRC_DIR = src/
OBJ_DIR = .objs/
INC_DIR = include/

# Archivos fuente (.c)
SOURCES = main.c philosophers.c utils.c parse_args.c \
			time_utils.c mutex_utils.c init.c\
			free_resources.c philos_init.c philo_actions.c
SRCS = $(addprefix $(SRC_DIR), $(SOURCES))

# Archivos objeto (.o)
OBJECTS = $(addprefix $(OBJ_DIR), $(SOURCES:.c=.o))

# Dependencias
DEPS = $(OBJECTS:.o=.d)

# Compilador y flags
CC = cc -g
CFLAGS = -Wall -Wextra -Werror -I$(INC_DIR) -MMD -MP #-fsanitize=thread

# Colores para los mensajes
GREEN = \033[1;92m
RED = \033[1;91m
YELLOW = \033[1;33m
RESET = \033[0m

# Objetivo principal
all: $(NAME)

# Regla para compilar el ejecutable
$(NAME): $(OBJECTS) Makefile
	@printf "$(GREEN)Compilando el proyecto...\n$(RESET)"
	@$(CC) $(CFLAGS) $(OBJECTS) -o $(NAME)
	@printf "$(GREEN)Compilación completa.\n$(RESET)"

# Compilación de archivos objeto en el directorio OBJ_DIR
$(OBJ_DIR)%.o: $(SRC_DIR)%.c | $(OBJ_DIR)
	@$(CC) $(CFLAGS) -c $< -o $@

# Crear el directorio de objetos si no existe
$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

# Limpieza de archivos generados
clean:
	@rm -rf $(OBJ_DIR)
	@printf "$(YELLOW)Archivos objeto limpiados.\n$(RESET)"

fclean: clean
	@rm -f $(NAME)
	@printf "$(RED)Todo limpio.\n$(RESET)"

re: fclean all

# Incluir dependencias
-include $(DEPS)

.PHONY: all clean fclean re
