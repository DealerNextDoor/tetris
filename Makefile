NAME		=	tetris

CXXFLAGS	=	-I include/ -Wextra -Wall -g3 -fpermissive

LDFLAGS		=	-lsfml-window -lsfml-graphics -lsfml-system -lfmodex

CC		=	g++

RM		=	rm -fv

SRC		=	src/main.cpp		\
			src/object.cpp		\
			src/music.cpp		\
			src/file.cpp		\
			src/tetris.cpp		\
			src/l_object.cpp

OBJ		=	$(SRC:.cpp=.o)

all:	$(OBJ)
	$(CC) -o $(NAME) $(OBJ) $(LDFLAGS) $(CXXFLAGS)

clean:
	$(RM) $(OBJ)

fclean: clean
	$(RM) $(NAME)

re:	fclean all
