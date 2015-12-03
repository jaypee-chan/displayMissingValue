SRC	=	displayMissingValue.c

OBJ	=	$(SRC:.c=.o)

GCC	=	gcc -o

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
