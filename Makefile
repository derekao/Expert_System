NAME = Expert_System

SRC = main.cpp

OBJ = $(addprefix $(O_DIR)/,$(SRC:.cpp=.o))

O_DIR = ./objs

S_DIR = ./srcs

CFLAGS = -Wall -Wextra -Werror

CC = clang++

RM = rm -rf

$(NAME): $(OBJ)
	@$(CC) -o $(NAME) $(CFLAGS) $(OBJ)

$(O_DIR)/%.o: $(S_DIR)/%.cpp
	@mkdir -p $(O_DIR)
	@$(CC) -o $@ -c $<

all: $(NAME)

clean:
	@$(RM) $(OBJ)
	@$(RM) $(O_DIR)

fclean: clean
	@$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re