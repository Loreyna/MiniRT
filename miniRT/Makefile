NAME			= miniRT

CC				= gcc
CFLAGS			= -Wextra -Wall -Werror -g -lm
CFLAGS			+= -fsanitize=address -fno-omit-frame-pointer
RM				= rm -rf

LIBFT_DIR		= ./libft
MLX42_DIR		= ./MLX42
MLX42_LIB		= $(MLX42_DIR)/build/libmlx42.a
MLX42_HEADERS		= $(MLX42_DIR)/include/MLX42/MLX42.h
SRC_DIR			= ./src
BUILD_DIR		= ./.build

TARGET			= $(BUILD_DIR)/.project
LIBFT			= $(LIBFT_DIR)/libft.a
LIBFT_HEADERS	= $(LIBFT_DIR)/libft.h

HEADERS			= -I $(LIBFT_DIR) -I $(MLX42_DIR)/include
INC				= $(HEADERS)

LIBS			= $(LIBFT) $(MLX42_LIB) -ldl -lglfw -pthread -lm

SRCS			= $(addprefix $(SRC_DIR)/,				\
					main.c					\
					)
BASE_DIR_RAY = $(SRC_DIR)/render
SRCS		+= $(addprefix $(BASE_DIR_RAY)/,				\
					ray_at.c				\
					ray_create.c				\
					)
BASE_DIR_SPHERE = $(SRC_DIR)/sphere
SRCS		+= $(addprefix $(BASE_DIR_SPHERE)/,				\
					sphere.c				\
					)

BASE_DIR_VECTOR = $(SRC_DIR)/vector
SRCS		+= $(addprefix $(BASE_DIR_VECTOR)/,				\
					vec3_add.c				\
					vec3_create.c				\
					vec3_cross.c				\
					vec3_dot.c				\
					vec3_length.c				\
					vec3_normalize.c			\
					vec3_scale.c				\
					vec3_sub.c				\
					)
BASE_DIR_PARSER = $(SRC_DIR)/parser
SRCS		+= $(addprefix $(BASE_DIR_PARSER)/,				\
					count.c					\
					check_args.c				\
					parse_objects.c				\
					parse_ambient.c				\
					parse_camera.c				\
					parse_light.c				\
					parse_sphere.c				\
					parse_plane.c				\
					parse_cylinder.c			\
					)

BASE_DIR_MEMORY = $(SRC_DIR)/memory
SRCS		+= $(addprefix $(BASE_DIR_MEMORY)/,				\
					allocate_scene.c			\
					)

OBJS			= $(SRCS:$(SRC_DIR)/%.c=$(BUILD_DIR)/%.o)

# **************************************************************************** #
#                                  TARGETS                                     #
# **************************************************************************** #

all: $(NAME)

$(NAME): $(TARGET)

$(TARGET): $(OBJS) $(LIBFT) $(MLX42_LIB)
	@echo "Creating $(NAME)..."
	@$(CC) $(CFLAGS) $(OBJS) $(INC) $(LIBS) -o $(NAME)
	@touch $(TARGET)
	@echo "Done! :D"


# **************************************************************************** #
#                                 COMPILING                                    #
# **************************************************************************** #

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c $(LIBFT_HEADERS) $(LIBFT) $(MLX42_HEADERS) $(MLX42_LIB)
	@echo "Compiling $<..."
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) -c $< $(INC) -o $@


# **************************************************************************** #
#                                   LIBFT                                      #
# **************************************************************************** #

$(LIBFT): $(LIBFT_HEADERS)
	@echo "Compiling libft..."
	@$(MAKE) -C $(LIBFT_DIR) --no-print-directory
	@echo "Libft done! :D"

# **************************************************************************** #
#                                   MLX42                                      #
# **************************************************************************** #

$(MLX42_LIB):
	@echo "Compiling MLX42..."
	@cmake -S $(MLX42_DIR) -B $(MLX42_DIR)/build
	@cmake --build $(MLX42_DIR)/build -j4
	@echo "MLX42 done! :D"


# **************************************************************************** #
#                                  CLEANING                                    #
# **************************************************************************** #

clean:
	@echo "Cleaning objects..."
	@$(RM) $(OBJS) $(TARGET)
	@$(MAKE) -C $(LIBFT_DIR) fclean --no-print-directory
	@echo "Done! :D"

fclean: clean
	@echo "Cleaning all..."
	@$(RM) $(BUILD_DIR)
	@$(RM) $(NAME)
	@echo "Done! :D"

re: fclean all

run: re
	@./$(NAME)


.PHONY: all clean fclean re run
