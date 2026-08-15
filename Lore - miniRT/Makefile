NAME			= minirt

CC				= gcc
CFLAGS			= -Wextra -Wall -Werror -g
CFLAGS			+= -fsanitize=address -fno-omit-frame-pointer
RM				= rm -rf

LIBFT_DIR		= ./libft
SRC_DIR			= ./src
BUILD_DIR		= ./.build

TARGET			= $(BUILD_DIR)/.project
LIBFT			= $(LIBFT_DIR)/libft.a
LIBFT_HEADERS	= $(LIBFT_DIR)/libft.h

HEADERS			= -I $(LIBFT_DIR)
INC				= $(HEADERS)

LIBS			= $(LIBFT)

SRCS			= $(addprefix $(SRC_DIR)/, \
					main.c \
					)

OBJS			= $(SRCS:$(SRC_DIR)/%.c=$(BUILD_DIR)/%.o)


# **************************************************************************** #
#                                  TARGETS                                     #
# **************************************************************************** #

all: $(NAME)

$(NAME): $(TARGET)

$(TARGET): $(OBJS) $(LIBFT)
	@echo "Creating $(NAME)..."
	@$(CC) $(CFLAGS) $(OBJS) $(INC) $(LIBS) -o $(NAME)
	@touch $(TARGET)
	@echo "Done! :D"


# **************************************************************************** #
#                                 COMPILING                                    #
# **************************************************************************** #

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c $(LIBFT_HEADERS) $(LIBFT)
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
