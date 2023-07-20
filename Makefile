CC	=	gcc
CFLAGS	=	-W	-Wall	-ansi	-pedantic	-std=c99	-lm   -pthread
SRC	=	$(wildcard *.c)
OBJ	=	$(SRC:.c=.o)
EXEC	=	prod_cons
$(EXEC)	:	$(OBJ)
				  				$(CC)	-o	$(EXEC)	$(OBJ)	$(CFLAGS)
%.o	:	%.c
	$(CC)	-o	$@	-c	$<	$(CFLAGS)
clean	:	
								rm	-rf	*.o
clean_all	:	clean							
								rm	-rf	prod_cons
