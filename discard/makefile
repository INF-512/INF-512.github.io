
CFLAG = -std=c++20 -Wall -Wextra -Wfatal-errors -Wno-unused-variable -Wno-sign-compare -Wno-char-subscripts

all : $(NAME).exe

$(NAME).exe : $(NAME).cpp
	g++ $(NAME).cpp -o $(NAME) $(CFLAG) $(STATIC)
