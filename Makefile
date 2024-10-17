########## Makefile para el proyecto de los filósofos ##########

# Nombre del ejecutable
NAME = philo

# Directorios
SRC_DIR = src/
OBJ_DIR = .objs/
INC_DIR = include/

# Archivos fuente (.c)
SOURCES = philo.c philosophers.c forks.c time_utils.c \
		  mutex_utils.c logger.c parse_args.c
SRCS = $(addprefix $(SRC_DIR), $(SOURCES))

# Archivos objeto (.o)
OBJECTS = $(addprefix $(OBJ_DIR), $(SOURCES:.c=.o))

# Dependencias
DEPS = $(OBJECTS:.o=.d)

# Compilador y flags
CC = gcc
CFLAGS = -g -Wall -Wextra -Werror -I$(INC_DIR) -MMD -MP

# Colores para los mensajes
GREEN = \033[1;92m
RED = \033[1;91m
YELLOW = \033[1;33m
RESET = \033[0m

# Objetivo principal
all: $(NAME)

# Regla para compilar el ejecutable
$(NAME): $(OBJECTS)
	@echo -e "$(GREEN)Compilando el proyecto...$(RESET)"
	$(CC) $(CFLAGS) $(OBJECTS) -o $(NAME)
	@echo -e "$(GREEN)Compilación completa.$(RESET)"

# Compilación de archivos objeto en el directorio OBJ_DIR
$(OBJ_DIR)%.o: $(SRC_DIR)%.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

# Crear el directorio de objetos si no existe
$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

# Limpieza de archivos generados
clean:
	@rm -rf $(OBJ_DIR)
	@echo -e "$(YELLOW)Archivos objeto limpiados.$(RESET)"

fclean: clean
	@rm -f $(NAME)
	@echo -e "$(RED)Todo limpio.$(RESET)"

re: fclean all

# Incluir dependencias
-include $(DEPS)

.PHONY: all clean fclean re
