CPPFLAGS = -Wall -Wextra -Werror -std=c++98 -g3
NAME = btc
SRC = BitcoinExchange.cpp \
	main.cpp
OBJ = $(SRC:.cpp=.o)

all : $(NAME)

$(NAME) : $(OBJ)
	c++ $(CPPFLAGS) -o $(NAME) $(OBJ)

%.o:%.cpp BitcoinExchange.hpp
	c++ $(CPPFLAGS) -c -o $@ $<

clean :
	rm -f $(OBJ)

fclean : 
	rm -f $(OBJ)
	rm -f $(NAME)

re : fclean all

.PHONY : clean fclean all re