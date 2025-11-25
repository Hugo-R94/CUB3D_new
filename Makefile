# ===========================
#        VARIABLES
# ===========================

NAME        = cub3D
NAME_BONUS  = cub3D_bonus
CC          = cc
# CFLAGS      = -Wall -Wextra -Werror -g -fPIC
CFLAGS		= -g
# ===========================
#        DIRECTORIES
# ===========================

SRC_DIR     = srcs
CHECK_DIR   = $(SRC_DIR)/checking
CLN_DIR		= $(SRC_DIR)/cleaning
GRP_DIR		= $(SRC_DIR)/graphic
MAP_DIR		= $(SRC_DIR)/map
INIT_DIR	= $(SRC_DIR)/initialization
KEY_DIR		= $(SRC_DIR)/key_handling
MAND_DIR    = $(SRC_DIR)/mandatory
BONUS_DIR   = $(SRC_DIR)/bonus
OBJ_DIR     = objs
INC_DIR     = includes
LIBFT_DIR   = My_libft
MLX_DIR     = minilibx-linux

# ===========================
#        LIBRARIES
# ===========================

LIBFT       = $(LIBFT_DIR)/libft.a
MLX         = $(MLX_DIR)/libmlx.a
INCLUDES    = -I$(INC_DIR) -I$(LIBFT_DIR) -I$(MLX_DIR)
LDFLAGS     = -L$(LIBFT_DIR) -lft -L$(MLX_DIR) -lmlx -lXext -lX11 -lm -lz

# ===========================
#        SOURCES
# ===========================


COMMON_SRCS =	$(CLN_DIR)/clean_exit.c \
				$(CLN_DIR)/free.c \
				$(CLN_DIR)/free_mand.c \
				$(CHECK_DIR)/check_args.c \
				$(CHECK_DIR)/check_map.c \
				$(CHECK_DIR)/check_map_utils.c \
				$(INIT_DIR)/init_texture.c \
				$(INIT_DIR)/init_mob.c \
				$(INIT_DIR)/init_texture_bonus.c \
				$(INIT_DIR)/windows.c \
				$(INIT_DIR)/data.c \
				$(KEY_DIR)/handle_key_press_bonus.c \
				$(KEY_DIR)/handle_keys.c \
				$(KEY_DIR)/handle_keys_mand.c \
				$(KEY_DIR)/handle_mouse.c \
				$(KEY_DIR)/highlight_button.c \
				$(GRP_DIR)/draw_img.c \
				$(GRP_DIR)/draw_map.c \
				$(GRP_DIR)/draw_map_utils.c \
				$(GRP_DIR)/draw_menu.c \
				$(GRP_DIR)/draw_utils.c \
				$(GRP_DIR)/ft_putstr.c \
				$(GRP_DIR)/handle_mode_select.c \
				$(GRP_DIR)/handle_pause_menu.c \
				$(GRP_DIR)/handle_setting_menu.c \
				$(GRP_DIR)/raycasting.c \
				$(GRP_DIR)/raycasting_h.c \
				$(GRP_DIR)/handle_death_menu.c \
				$(GRP_DIR)/floor_render_bonus.c \
				$(GRP_DIR)/win_screen.c \
				$(GRP_DIR)/draw_sprite.c \
				$(GRP_DIR)/post_process.c \
				$(GRP_DIR)/animate.c \
				$(GRP_DIR)/exit_render.c \
				srcs/utils/rand.c \
				srcs/gameplay/mob.c \
				srcs/gameplay/collision.c \
				srcs/gameplay/wall_collision.c \
				srcs/gameplay/shoot.c \
				srcs/gameplay/chainsaw.c \
				srcs/gameplay/mode.c \
				srcs/gameplay/mode1.c \
				srcs/gameplay/spawn_mob.c \
				$(GRP_DIR)/draw_mob.c \
				$(GRP_DIR)/ceiling_render_bonus.c \
				$(GRP_DIR)/wall_render_bonus.c \
				$(GRP_DIR)/render_utils_bonus.c \
				$(GRP_DIR)/render_utils_bonus2.c \
				$(GRP_DIR)/draw_doors.c \
				$(GRP_DIR)/raycasting_utils.c \
				$(GRP_DIR)/raycasting_v.c \
				$(GRP_DIR)/render.c \
				$(GRP_DIR)/render_gameplay.c \
				$(GRP_DIR)/render_mandatory.c \
				$(GRP_DIR)/render_bonus.c \
				$(GRP_DIR)/resize.c \
				$(GRP_DIR)/upscale.c \
				$(SRC_DIR)/ft_sprintf.c \
				$(SRC_DIR)/game_loop_bonus.c \
				$(MAP_DIR)/get_map.c \
				$(MAP_DIR)/get_map_utils.c \
				$(MAP_DIR)/get_player_pos.c \
				$(MAP_DIR)/map_generator2.c \
				$(MAP_DIR)/map_generator.c \
				$(MAP_DIR)/map_generator_utils.c \
				$(MAP_DIR)/reparse.c \
				$(MAP_DIR)/reparse_utils.c 


MAND_SRCS   = $(COMMON_SRCS) $(MAND_DIR)/mandatory.c
BONUS_SRCS  = $(COMMON_SRCS) $(BONUS_DIR)/bonus.c

# ===========================
#        OBJECTS
# ===========================
MAND_OBJS   = $(MAND_SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/mandatory/%.o)
BONUS_OBJS  = $(BONUS_SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/bonus/%.o)

# ===========================
#        COLORS
# ===========================
YELLOW      = \033[1;33m
GREEN       = \033[1;32m
RESET       = \033[0m

# ===========================
#        RULES
# ===========================
all: $(NAME)

bonus: CFLAGS += -DBONUS
bonus: $(NAME_BONUS)

$(NAME): $(LIBFT) $(MLX) $(MAND_OBJS)
	$(CC) $(CFLAGS) $(INCLUDES) $(MAND_OBJS) $(LIBFT) $(LDFLAGS) -o $@
	@echo "$(GREEN)✅ Compilation terminée : $(NAME)$(RESET)"

$(NAME_BONUS): $(LIBFT) $(MLX) $(BONUS_OBJS)
	$(CC) $(CFLAGS) $(INCLUDES) $(BONUS_OBJS) $(LIBFT) $(LDFLAGS) -o $@
	@echo "$(GREEN)🎉 Compilation bonus terminée : $(NAME_BONUS)$(RESET)"

$(OBJ_DIR)/mandatory/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	@echo "$(YELLOW)Compiling $<...$(RESET)"
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(OBJ_DIR)/bonus/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	@echo "$(YELLOW)Compiling $<...$(RESET)"
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR)

$(MLX):
	$(MAKE) -C $(MLX_DIR)

clean:
	$(MAKE) clean -C $(LIBFT_DIR)
	$(MAKE) clean -C $(MLX_DIR)
	rm -rf $(OBJ_DIR)
	@echo "$(YELLOW)🧹 Nettoyage des objets terminé.$(RESET)"

fclean: clean
	$(MAKE) fclean -C $(LIBFT_DIR)
	rm -f $(NAME) $(NAME_BONUS)
	@echo "$(YELLOW)🔥 Nettoyage complet terminé.$(RESET)"

re: fclean all

.PHONY: all bonus clean fclean re