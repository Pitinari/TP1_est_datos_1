#abreviaturas para los archivos
OP	=	operadores
ET	=	ExpTree
EX	=	Expression

#declaracion de destinos
main:	main.c	$(OP).o	$(ET).o	$(EX).o
	$(CC)	-o	$@.exe	$@.c
$(EX).o:	$(EX).c	$(EX).h	$(ET).o
	$(CC)	-c	$(EX).c
$(ET).o:	$(ET).c	$(ET).h	$(OP).o
	$(CC)	-c	$(ET).c
$(OP).o:	$(OP).c	$(OP).h
	$(CC) -c $(OP).c
clean:
	rm	*.o