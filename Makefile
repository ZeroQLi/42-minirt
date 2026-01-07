# Object and source path directories
SRC_DIR = ./src/
OBJ_PATH = src/obj/
LIBFT_PATH = libft/

# Program & build names
NAME = miniRT
LIBFT = $(LIBFT_PATH)libft.a

# Program sauce files
SRC = $(SRC_DIR)minirt.c \
$(SRC_DIR)parser.c \
$(SRC_DIR)error.c \
# $(SRC_DIR)cleanup_linux \

SRC2 = 

# Object files
OBJ = $(SRC:src/%.c=$(OBJ_PATH)%.o)

ifeq ($(shell uname), Linux)
	MLX_DIR := ./minilibx_linux
	MLX := mlx_linux
	MLX_FLAGS = -L$(MLX_DIR) -l$(MLX) -L/usr/lib/X11 -lXext -lX11
else
	MLX_DIR := ./minilibx_macos
	MLX := mlx
	MLX_FLAGS = -L$(MLX_DIR) -l$(MLX) -framework OpenGL -framework AppKit
endif

# Compiler n flags
CC		=		cc
CFLAGS	= -Wall -Wextra -Werror -Iincludes/ -I$(MLX_DIR)

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

$(NAME): $(OBJ) $(LIBFT) $(MLX_LIB) 
	@echo "$(WHITE)Compiling $(BWHITE)$(NAME)$(WHITE) program...$(RESET)"
	@$(CC) $(CFLAGS) $(OBJ) $(MLX_FLAGS) $(LIBFT) -o $(NAME)
	@echo "$(BWHITE)$(NAME)$(WHITE) program is $(BGREEN)ready! $(RESET)✅"

$(LIBFT):
	@echo "$(WHITE)Compiling $(BWHITE)libft$(WHITE) functions...$(RESET)"
	@make -C $(LIBFT_PATH) all
	@echo "$(WHITE)libft is $(BGREEN)ready! $(RESET)✅"

$(OBJ_PATH)%.o : src/%.c
	@$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_PATH):
	@mkdir -p $(OBJ_PATH)

$(MLX_LIB):
	@echo "$(WHITE)Compiling $(BWHITE)MinilibX$(WHITE)...$(RESET)"
	@make -C $(MLX_DIR)
	@echo "$(WHITE)MinilibX is $(BGREEN)ready! $(RESET)✅"

clean:
	@rm -rf $(OBJ_PATH)
	@make clean -C $(LIBFT_PATH)
	@echo "$(BGREEN)cleaned like the blackhole you guys are getting if you DON'T GET TO COOKING$(WHITE)"

fclean: clean
	@rm -f $(NAME)
	@rm -f $(LIBFT)

re: fclean $(NAME)

# Complies and runs the program at once (does not re)
runngun: all
	@./minirt

# Only recompiles the src files and the program, ignoring libft as its always the same.
remake:
	@rm -f $(NAME)
	@rm -rf $(OBJ_PATH)
	@make all

# Calls the sonnovagun of the subject to norm check the src folder + header file
# Will only print any errors found (which it shouldn't)
norm:
	norminette includes/ src/ | grep -e Error -e Global

.PHONY: all clean fclean re norm