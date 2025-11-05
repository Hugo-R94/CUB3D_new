NAME = libft.a

CC = cc
CFLAGS = -Wall -Wextra -Werror

SRCDIR = srcs
OBJDIR = dest
INCLUDES = headers

GREEN = \033[0;32m
BLUE = \033[1;34m
YELLOW = \033[1;33m
RED = \033[0;31m
RESET = \033[0m

CFILES := $(shell find $(SRCDIR) -type f -name "*.c")

OFILES := $(patsubst $(SRCDIR)/%, $(OBJDIR)/%, $(CFILES:.c=.o))

all: $(NAME)

$(NAME): $(OFILES)
	@echo "$(BLUE)[LINK]$(RESET) Création de la bibliothèque $(NAME)"
	@ar rcs $(NAME) $(OFILES)
	@echo "$(GREEN)[OK]$(RESET) Compilation terminée !"

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) -I$(INCLUDES) -c $< -o $@
	@echo "$(YELLOW)[BUILD]$(RESET) Compilation de $<"

clean:
	@rm -rf $(OBJDIR)
	@echo "$(YELLOW)[CLEAN]$(RESET) Suppression des fichiers objets"

fclean: clean
	@rm -f $(NAME)
	@echo "$(YELLOW)[FCLEAN]$(RESET) Suppression de $(NAME)"

re: fclean all

.PHONY: all clean fclean re
