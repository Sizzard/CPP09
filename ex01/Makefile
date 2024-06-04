CPPFLAGS = -Wall -Wextra -Werror -std=c++98
NAME = RPN
SRC = RPN.cpp \
	main.cpp
OBJ = $(SRC:.cpp=.o)

all : $(NAME)

$(NAME) : $(OBJ)
	c++ $(CPPFLAGS) -o $(NAME) $(OBJ) 

%.o:%.cpp RPN.hpp
	c++ $(CPPFLAGS) -c -o $@ $<

clean : 
	rm -f $(OBJ)

fclean :
	rm -f $(OBJ)
	rm -f $(NAME)

re : fclean all

.PHONY : clean fclean re all