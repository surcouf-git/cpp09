NAME = PmergeMe

CPP = c++
CPPFLAGS = -Wall -Wextra -Werror -g --std=c++98 # -fsanitize=address -fno-omit-frame-pointer

SRCS = PmergeMe.cpp main.cpp
OBJ_DIR = obj
OBJS = $(addprefix $(OBJ_DIR)/, $(SRCS:.cpp=.o))

$(OBJ_DIR)/%.o: %.cpp
	mkdir -p $(OBJ_DIR)
	$(CPP) $(CPPFLAGS) -c $< -o $@

all: $(NAME)

$(NAME): $(OBJS)
	$(CPP) $(CPPFLAGS) $(OBJS) -o $(NAME)

clean:
	rm -rf $(OBJ_DIR)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re