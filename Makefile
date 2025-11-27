NAME        = cub3D
NAME_BONUS  = cub3D_bonus
CC          = cc
CFLAGS      = -Wall -Wextra -Werror -g -fPIC

SRC_DIR     = srcs
CHECK_DIR   = $(SRC_DIR)/checking
CLN_DIR     = $(SRC_DIR)/cleaning
GRP_DIR     = $(SRC_DIR)/graphic
MAP_DIR     = $(SRC_DIR)/map
INIT_DIR    = $(SRC_DIR)/initialization
GMP_DIR     = $(SRC_DIR)/gameplay
KEY_DIR     = $(SRC_DIR)/key_handling
MAND_DIR    = $(SRC_DIR)/mandatory
BONUS_DIR   = $(SRC_DIR)/bonus
OBJ_DIR     = objs
INC_DIR     = includes
LIBFT_DIR   = My_libft
MLX_DIR     = minilibx-linux
MLX_URL     = https://cdn.intra.42.fr/document/document/42054/minilibx-linux.tgz
MLX_ARCHIVE = minilibx-linux.tgz

LIBFT       = $(LIBFT_DIR)/libft.a
MLX         = $(MLX_DIR)/libmlx.a
INCLUDES    = -I$(INC_DIR) -I$(LIBFT_DIR) -I$(MLX_DIR)
LDFLAGS     = -L$(LIBFT_DIR) -lft -L$(MLX_DIR) -lmlx -lXext -lX11 -lm -lz

# ===========================
#        SOURCES
# ===========================
COMMON_SRCS =  \
    $(CLN_DIR)/clean_exit.c \
    $(CLN_DIR)/free.c \
    $(CLN_DIR)/free_mand.c \
    $(CHECK_DIR)/check_args.c \
    $(CHECK_DIR)/check_map.c \
    $(CHECK_DIR)/check_map_utils.c \
    $(INIT_DIR)/init_texture.c \
    $(INIT_DIR)/init_mob.c \
    $(INIT_DIR)/data_mand.c \
    $(INIT_DIR)/init_texture_bonus.c \
    $(INIT_DIR)/windows.c \
    $(INIT_DIR)/data.c \
    $(KEY_DIR)/handle_key_press_bonus.c \
    $(KEY_DIR)/handle_esc.c \
    $(KEY_DIR)/handle_keys.c \
    $(KEY_DIR)/handle_keys_mand.c \
    $(KEY_DIR)/handle_mouse.c \
    $(KEY_DIR)/handle_mouse2.c \
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
    $(GRP_DIR)/raycasting_bonus.c \
    $(GRP_DIR)/raycasting_h.c \
    $(GRP_DIR)/handle_death_menu.c \
    $(GRP_DIR)/render_texture_mand.c \
    $(GRP_DIR)/render_distance_mand.c \
    $(GRP_DIR)/render_wall_coord_mand.c \
    $(GRP_DIR)/render_column_mand.c \
    $(GRP_DIR)/render_column_draw_mand.c \
    $(GRP_DIR)/floor_render_bonus.c \
    $(GRP_DIR)/win_screen.c \
    $(GRP_DIR)/draw_sprite.c \
    $(GRP_DIR)/draw_sprite_utils.c \
    $(GRP_DIR)/post_process.c \
    $(GRP_DIR)/animate.c \
    $(GRP_DIR)/exit_render.c \
    srcs/utils/rand.c \
    $(GMP_DIR)/mob.c \
    $(GMP_DIR)/monitor.c \
    $(GMP_DIR)/collision.c \
    $(GMP_DIR)/wall_collision.c \
    $(GMP_DIR)/shoot.c \
    $(GMP_DIR)/mouvement.c \
    $(GMP_DIR)/action.c \
    $(GMP_DIR)/chainsaw.c \
    $(GMP_DIR)/mode.c \
    $(GMP_DIR)/mode1.c \
    $(GMP_DIR)/spawn_mob.c \
    $(GRP_DIR)/draw_mob.c \
    $(GRP_DIR)/draw_mob_utils.c \
    $(GRP_DIR)/compose_ceilling.c \
    $(GRP_DIR)/draw_ceilling.c \
    $(GRP_DIR)/wall_render_bonus.c \
    $(GRP_DIR)/render_bonus_utils.c \
    $(GRP_DIR)/render_bonus_utils2.c \
    $(GRP_DIR)/render_utils_bonus.c \
    $(GRP_DIR)/render_utils_bonus2.c \
    $(GRP_DIR)/draw_doors.c \
    $(GRP_DIR)/draw_doors_utils.c \
    $(GRP_DIR)/raycasting_utils.c \
    $(GRP_DIR)/raycasting_utils_bonus.c \
    $(GRP_DIR)/raycasting_v.c \
    $(GRP_DIR)/render_gameplay.c \
    $(GRP_DIR)/render_mandatory.c \
    $(GRP_DIR)/render_bonus.c \
    $(GRP_DIR)/resize.c \
    $(GRP_DIR)/upscale.c \
    $(GRP_DIR)/upscale_utils.c \
    $(SRC_DIR)/ft_sprintf.c \
    $(GMP_DIR)/game_loop_bonus.c \
    $(GMP_DIR)/game_loop_bonus2.c \
    $(GMP_DIR)/game_loop_bonus3.c \
    $(GMP_DIR)/resize_func.c \
    $(GMP_DIR)/sensi_fov.c \
    $(MAP_DIR)/get_map.c \
    $(MAP_DIR)/get_map_utils.c \
    $(MAP_DIR)/get_map_utils2.c \
    $(MAP_DIR)/get_player_pos.c \
    $(MAP_DIR)/map_generator.c \
    $(MAP_DIR)/map_room.c \
    $(MAP_DIR)/map_ff.c \
    $(MAP_DIR)/map_alloc.c \
    $(MAP_DIR)/map_corridor.c \
    $(MAP_DIR)/map_player_exit.c \
    $(MAP_DIR)/map_generator_utils.c \
    $(MAP_DIR)/map_generator_utils2.c \
    $(MAP_DIR)/reparse.c \
    $(MAP_DIR)/reparse_utils.c

MAND_SRCS = $(COMMON_SRCS) $(MAND_DIR)/mandatory.c
BONUS_SRCS = $(COMMON_SRCS) $(BONUS_DIR)/bonus.c

MAND_OBJS   = $(MAND_SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/mandatory/%.o)
BONUS_OBJS  = $(BONUS_SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/bonus/%.o)

YELLOW      = \033[1;33m
GREEN       = \033[1;32m
RESET       = \033[0m

all: $(MLX) $(NAME)

bonus: CFLAGS += -DBONUS
bonus: $(MLX) $(NAME_BONUS)

$(MLX_DIR):
	@echo "$(YELLOW)📥 Téléchargement de la MiniLibX...$(RESET)"
	@wget -q $(MLX_URL) -O $(MLX_ARCHIVE)
	@tar -xzf $(MLX_ARCHIVE)
	@rm -f $(MLX_ARCHIVE)
	@echo "$(GREEN)MiniLibX téléchargée et extraite !$(RESET)"

$(MLX): $(MLX_DIR)
	$(MAKE) -C $(MLX_DIR)

###############################################
# Compilation
###############################################
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

###############################################
# Cleaning
###############################################
clean:
	$(MAKE) clean -C $(LIBFT_DIR)
	@if [ -d $(MLX_DIR) ]; then $(MAKE) clean -C $(MLX_DIR); fi
	 rm -rf $(OBJ_DIR)
	rm -rf minilibx-linux
	@echo "$(YELLOW)🧹 Nettoyage des objets terminé.$(RESET)"

fclean: clean
	$(MAKE) fclean -C $(LIBFT_DIR)
	rm -f $(NAME) $(NAME_BONUS)
	@echo "$(YELLOW)🔥 Nettoyage complet terminé.$(RESET)"

re: fclean all

.PHONY: all bonus clean fclean re
