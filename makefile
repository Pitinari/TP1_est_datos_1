#abreviaturas para los archivos
OP	=	operadores
ET	=	ExpTree
EX	=	Expression

#declaracion de destinos
main:	main.o	$(OP).o	$(ET).o	$(EX).o
	gcc	-o $@.exe $@.o $(ET).o $(EX).o $(OP).o -lm

main.o:	main.c $(EX).o $(ET).o $(OP).o
	gcc	-c	main.c

$(EX).o: $(EX).c $(EX).h $(ET).h $(OP).h
	gcc	-c	$(EX).c

$(ET).o: $(ET).c $(ET).h $(OP).h
	gcc	-c	$(ET).c

$(OP).o: $(OP).h $(OP).c	
	gcc -c  $(OP).c -lm

clean:
	rm	*.o
	rm  $@.exe