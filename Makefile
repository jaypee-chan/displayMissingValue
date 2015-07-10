SRC	=	displayMissingValue.cpp

OBJ	=	$(SRC:.cpp=.o)

GCC	=	g++ -o

RM	=	rm -f

NAME	=	displayMissingValue

all	:	$(NAME)

$(NAME)	:	$(OBJ)
		$(GCC) $(NAME) $(OBJ)

clean	:
		$(RM) $(OBJ)

fclean	:	clean
		$(RM) $(NAME)

re	:	fclean all

.PHONY	:	all clean fclean
