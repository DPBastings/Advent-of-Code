NAME 		:= bin

SRC_FILES	:= main.cpp\
			CubeSet.cpp\
			Game.cpp\
			parse.cpp
OBJ_FILES	:= $(patsubst %.cpp,%.o,$(SRC_FILES))
HDR_FILES	:= aoc.hpp\
			CubeSet.hpp\
			Game.hpp

SRC_DIR		:= ./source/
OBJ_DIR		:= ./object/
HDR_DIR		:= ./include/

CXX			:= g++
CXXFLAGS	+= -std=c++17 -O0 -Wall -Wextra -Werror -I$(HDR_DIR) -g
DEPFLAGS	:= -MMD $(@.o=.d) -MP
DEP_FILES	:= $(patsubst %.o,%.d,$(addprefix $(OBJ_DIR), $(OBJ_FILES)))

.PHONY: all clean fclean re

all: $(NAME)

$(NAME): $(addprefix $(OBJ_DIR),$(OBJ_FILES))
	@$(CXX) $(CXXFLAGS) $^ -o $@

$(OBJ_DIR)%.o: $(SRC_DIR)%.cpp
	@mkdir -p $(OBJ_DIR)
	@$(CXX) $(CXXFLAGS) $(DEPFLAGS) -I$(HDR_DIR) -I$(SRC_DIR) $< -c -o $@

clean:
	@rm -f $(addprefix $(OBJ_DIR),$(OBJ_FILES))\
		$(addprefix $(OBJ_DIR),$(patsubst %.o,%.d,$(OBJ_FILES)))

fclean: clean
	@rm -f $(NAME)

re: fclean all

-include $(DEP_FILES)
