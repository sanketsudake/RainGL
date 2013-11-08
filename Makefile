# File name :- makefile
# Licence:- GNU GPL v3
# Project Name:- RainGL
## Makefile
##=============================================================================

NAME	= raingl

DIRECTORY = RainGL

CC	=	g++

ECHO = @echo

RM	= rm -f

SRC	= main.cpp

CFLAGS	= -Wall	\
		-W		\
		-Werror

LFLAGS	=	-lglut	\
			-lGL	\
			-lGLU	\
			-lm		\
			-lSDL	\
			-lSDL_image

OBJ 	= $(SRC:.cpp=.o)

all	:	$(NAME)

$(NAME)	:	$(OBJ)
	$(CC) $(OBJ) $(LFLAGS) -o $(NAME)

.cpp.o :
		$(CC) $(CFLAGS) $(IFLAGS) $< -c -o $@

clean :
		$(RM) $(OBJ)
		$(RM) *~ \#*\#

distclean :	clean
		$(RM) $(NAME)

separator :
		$(ECHO) "------------------------------------------"

re :		clean separator all

run :		all
		./$(NAME)

# This option use useful when nvidia graphics card
# is enabled in ubuntu
# Runs program on graphics card providing greater
# fps rate.
cudarun	:	all
		primusrun ./$(NAME)

tarball :	clean separator
		$(ECHO) "Archiving..."
		cd .. && $(ARCHIVE) $(NAME).tar.gz $(DIRECTORY)
		$(ECHO) "Done !"

install :
		$(ECHO) "Not implemented yet."
