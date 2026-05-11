# Object and source path directories
SRC_DIR = src/
SRC_DIR2 = $(SRC_DIR)shapes_parser/
SRC_DIR3 = $(SRC_DIR)tuples/
SRC_DIR4 = $(SRC_DIR)matrix/
SRC_DIR5 = $(SRC_DIR)canvas/
SRC_DIR6 = $(SRC_DIR5)shape_intersections/
BONUS_DIR = bonus/
OBJ_PATH = src/.obj/
OBJ_BONUS_PATH = src/.obj_bonus/
LIBFT_PATH = libft/

# Program & build names
NAME = miniRT
NAME_BONUS = miniRT_bonus
LIBFT = $(LIBFT_PATH)libft.a

# Program sauce files
SRC = $(SRC_DIR)minirt.c \
$(SRC_DIR)parser.c \
$(SRC_DIR)error.c \
$(SRC_DIR)cleanup_linux.c \
$(SRC_DIR)utils.c

SRC_BONUS = $(filter-out $(SRC_DIR)cleanup_linux.c,$(SRC)) \
$(BONUS_DIR)cleanup/cleanup_bonus.c

SRC2 = $(SRC_DIR2)p_ambient.c \
$(SRC_DIR2)p_camera.c \
$(SRC_DIR2)p_cylinder.c \
$(SRC_DIR2)p_light.c \
$(SRC_DIR2)p_plane.c \
$(SRC_DIR2)p_sphere.c \
$(SRC_DIR2)parse_utils.c \
$(SRC_DIR2)add_lists.c \
$(SRC_DIR2)free_lists.c \
$(SRC_DIR2)vec_normalizer.c

SRC2_BONUS = $(filter-out $(SRC_DIR2)p_light.c $(SRC_DIR2)add_lists.c \
$(SRC_DIR2)free_lists.c,$(SRC2)) \
$(BONUS_DIR)parser/p_light_bonus.c \
$(BONUS_DIR)parser/add_lists_bonus.c \
$(BONUS_DIR)parser/free_lists_bonus.c

SRC3 = $(SRC_DIR3)tuple_utils.c \
$(SRC_DIR3)tuple_operations.c \
$(SRC_DIR3)scalar_operations.c \
$(SRC_DIR3)vector_operations.c \
$(SRC_DIR3)color_operations.c

SRC4 = $(SRC_DIR4)matrix_utils.c \
$(SRC_DIR4)matrix_operations.c \
$(SRC_DIR4)matrix_init.c \
$(SRC_DIR4)determinants.c \
$(SRC_DIR4)cofactors.c \
$(SRC_DIR4)inversion.c \
$(SRC_DIR4)translations.c

SRC5 = $(SRC_DIR5)canvas_operations.c \
$(SRC_DIR5)intersections_list.c \
$(SRC_DIR5)intersect_world.c \
$(SRC_DIR5)init_shapes.c \
$(SRC_DIR5)rays.c \
$(SRC_DIR5)shadows/shadow.c \
$(SRC_DIR5)shadows/sphere_shadow_hit.c \
$(SRC_DIR5)shadows/plane_shadow_hit.c \
$(SRC_DIR5)shadows/cyl_shadow_hit.c \
$(SRC_DIR5)render_info.c \
$(SRC_DIR5)reflections.c \
$(SRC_DIR5)new_world.c \
$(SRC_DIR5)draw_world.c \
$(SRC_DIR5)transform.c \
$(SRC_DIR5)lighting.c

SRC5_BONUS = $(filter-out $(SRC_DIR5)lighting.c $(SRC_DIR5)shadows/shadow.c \
$(SRC_DIR5)new_world.c $(SRC_DIR5)draw_world.c \
$(SRC_DIR5)shadows/sphere_shadow_hit.c \
$(SRC_DIR5)shadows/plane_shadow_hit.c \
$(SRC_DIR5)shadows/cyl_shadow_hit.c,$(SRC5)) \
$(BONUS_DIR)canvas/lighting_bonus.c \
$(BONUS_DIR)canvas/shadows/shadow_bonus.c \
$(BONUS_DIR)canvas/shadows/sphere_shadow_hit_bonus.c \
$(BONUS_DIR)canvas/shadows/plane_shadow_hit_bonus.c \
$(BONUS_DIR)canvas/shadows/cyl_shadow_hit_bonus.c \
$(BONUS_DIR)canvas/new_world_bonus.c \
$(BONUS_DIR)canvas/draw_world_bonus.c

SRC_BONUS_SRC = $(filter $(SRC_DIR)%,$(SRC_BONUS))
SRC_BONUS_BONUS = $(filter $(BONUS_DIR)%,$(SRC_BONUS))

SRC2_BONUS_SRC = $(filter $(SRC_DIR)%,$(SRC2_BONUS))
SRC2_BONUS_BONUS = $(filter $(BONUS_DIR)%,$(SRC2_BONUS))

SRC5_BONUS_SRC = $(filter $(SRC_DIR5)%,$(SRC5_BONUS))
SRC5_BONUS_BONUS = $(filter $(BONUS_DIR)%,$(SRC5_BONUS))

SRC6 = $(SRC_DIR6)intersect_cylinder.c \
$(SRC_DIR6)intersect_plane.c \
$(SRC_DIR6)intersect_sphere.c

# Object files
OBJ = $(SRC:src/%.c=$(OBJ_PATH)%.o) \
$(SRC2:src/%.c=$(OBJ_PATH)%.o) \
$(SRC3:src/%.c=$(OBJ_PATH)%.o) \
$(SRC4:src/%.c=$(OBJ_PATH)%.o) \
$(SRC5:src/%.c=$(OBJ_PATH)%.o) \
$(SRC6:src/%.c=$(OBJ_PATH)%.o)

OBJ_BONUS = $(SRC_BONUS_SRC:src/%.c=$(OBJ_BONUS_PATH)%.o) \
$(SRC_BONUS_BONUS:bonus/%.c=$(OBJ_BONUS_PATH)%.o) \
$(SRC2_BONUS_SRC:src/%.c=$(OBJ_BONUS_PATH)%.o) \
$(SRC2_BONUS_BONUS:bonus/%.c=$(OBJ_BONUS_PATH)%.o) \
$(SRC3:src/%.c=$(OBJ_BONUS_PATH)%.o) \
$(SRC4:src/%.c=$(OBJ_BONUS_PATH)%.o) \
$(SRC5_BONUS_SRC:src/%.c=$(OBJ_BONUS_PATH)%.o) \
$(SRC5_BONUS_BONUS:bonus/%.c=$(OBJ_BONUS_PATH)%.o) \
$(SRC6:src/%.c=$(OBJ_BONUS_PATH)%.o)

MLX_DIR := ./minilibx-linux
	MLX := minilibx-linux
	MLX_FLAGS = -L$(MLX_DIR) -lmlx -L/usr/lib/X11 -lXext -lX11

# Compiler n flags
CC		=		cc
CFLAGS	= -Wall -Wextra -Werror -O3 -Ofast -Wno-unused-result -mavx -mavx2 -flto -funroll-loops -fno-signed-zeros -Iincludes/ -I$(MLX_DIR)

MLX_LIB = $(MLX_DIR)/libmlx.a

# Color codes ✨
WHITE = \033[0;37m
BRED = \033[1;31m
BWHITE = \033[1;37m
BGREEN = \033[1;32m
RESET = \033[0m

# hide directory access printing (linux thing)
MAKEFLAGS += --no-print-directory

# Build magicc
all: $(OBJ_PATH) $(LIBFT) $(MLX_LIB) $(NAME)

bonus: $(OBJ_BONUS_PATH) $(LIBFT) $(MLX_LIB) $(NAME_BONUS)

$(NAME): $(OBJ) $(LIBFT) $(MLX_LIB)
	@echo "$(WHITE)Compiling $(BWHITE)$(NAME)$(WHITE) program...$(RESET)"
	@$(CC) $(CFLAGS) $(OBJ) $(MLX_FLAGS) $(LIBFT) -lm -o $(NAME)
	@echo "$(BWHITE)$(NAME)$(WHITE) program is $(BGREEN)ready! $(RESET)✅"

$(NAME_BONUS): $(OBJ_BONUS) $(LIBFT) $(MLX_LIB)
	@echo "$(WHITE)Compiling $(BWHITE)$(NAME_BONUS)$(WHITE) program...$(RESET)"
	@$(CC) $(CFLAGS) $(OBJ_BONUS) $(MLX_FLAGS) $(LIBFT) -lm -o $(NAME_BONUS)
	@echo "$(BWHITE)$(NAME_BONUS)$(WHITE) program is $(BGREEN)ready! $(RESET)✅"

$(LIBFT):
	@echo "$(WHITE)Compiling $(BWHITE)libft$(WHITE) functions...$(RESET)"
	@make -C $(LIBFT_PATH) all
	@echo "$(WHITE)libft is $(BGREEN)ready! $(RESET)✅"

$(OBJ_PATH)%.o : src/%.c
	@mkdir -p $(dir $@)
	@echo "$(WHITE)Compiling $(BWHITE)$<$(WHITE)...$(RESET)"
	@$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_BONUS_PATH)%.o : src/%.c
	@mkdir -p $(dir $@)
	@echo "$(WHITE)Compiling $(BWHITE)$<$(WHITE)...$(RESET)"
	@$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_BONUS_PATH)%.o : bonus/%.c
	@mkdir -p $(dir $@)
	@echo "$(WHITE)Compiling $(BWHITE)$<$(WHITE)...$(RESET)"
	@$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_PATH):
	@mkdir -p $(OBJ_PATH) $(OBJ_PATH)shapes_parser/ $(OBJ_PATH)tuples/ $(OBJ_PATH)matrix/ $(OBJ_PATH)canvas/ $(OBJ_PATH)shapes/ $(OBJ_PATH)canvas/shape_intersections/

$(OBJ_BONUS_PATH):
	@mkdir -p $(OBJ_BONUS_PATH) $(OBJ_BONUS_PATH)shapes_parser/ $(OBJ_BONUS_PATH)tuples/ $(OBJ_BONUS_PATH)matrix/ $(OBJ_BONUS_PATH)canvas/ $(OBJ_BONUS_PATH)shapes/ $(OBJ_BONUS_PATH)canvas/shape_intersections/ $(OBJ_BONUS_PATH)cleanup/ $(OBJ_BONUS_PATH)parser/ $(OBJ_BONUS_PATH)canvas/

$(MLX_LIB):
	@echo "$(WHITE)Compiling $(BWHITE)MinilibX$(WHITE)...$(RESET)"
	@make -C $(MLX_DIR)
	@echo "$(WHITE)MinilibX is $(BGREEN)ready! $(RESET)✅"

clean:
	@rm -rf $(OBJ_PATH) $(OBJ_BONUS_PATH)
	@make clean -C $(LIBFT_PATH)
	@make clean -C $(MLX_DIR)
	@echo "$(BGREEN)cleaned like the blackhole you guys are getting if you DON'T GET TO COOKING$(WHITE)"

fclean: clean
	@rm -f $(NAME)
	@rm -f $(NAME_BONUS)
	@rm -f $(LIBFT)

re: fclean all

# Calls the sonnovagun of the subject to norm check the src folder + header file
# Will only print any errors found (which it shouldn't)
norm:
	norminette includes/ src/ libft/ bonus/ | grep -e Error -e Global

# fires valgrind with leaks flags and parses additional input arguments (LAGGY)
leak: all
	@valgrind --leak-check=full --leak-resolution=high -s --track-origins=yes \
	--num-callers=500 --show-mismatched-frees=yes --show-leak-kinds=all \
	--track-fds=yes --gen-suppressions=no \
	--error-limit=no --undef-value-errors=yes --expensive-definedness-checks=yes \
	--read-var-info=yes --keep-debuginfo=yes ./$(NAME) $(filter-out $@,$(MAKECMDGOALS))

leak_bonus: bonus
	@valgrind --leak-check=full -s --track-origins=yes \
	--num-callers=500 --show-mismatched-frees=yes --show-leak-kinds=all \
	--track-fds=yes ./$(NAME_BONUS) $(filter-out $@,$(MAKECMDGOALS))
%:
	@:

.PHONY: all bonus clean fclean re norm leak leak_bonus