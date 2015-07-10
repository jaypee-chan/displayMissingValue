SRC	=	checkValue.cpp

OBJ	=	$(SRC:.cpp=.o)

GCC	=	g++ -o

RM	=	rm -f

NAME	=	checkValue

all	:	$(NAME)

$(NAME)	:	$(OBJ)
		$(GCC) checkValue $(OBJ)

clean	:
		$(RM) $(OBJ)

fclean	:	clean
		$(RM) $(NAME)

re	:	fclean all

.PHONY	:	all clean fclean
