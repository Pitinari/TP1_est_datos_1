#abreviaturas para los archivos
OP	=	operadores
ET	=	ExpTree
EX	=	Expression
T = test_

#declaracion de destinos
test:	main.o	$(T)$(OP).o	$(T)$(ET).o	$(T)$(EX).o
	gcc	-o main main.o $(T)$(ET).o $(T)$(EX).o $(T)$(OP).o -lm

main.o:	main.c $(T)$(EX).o $(T)$(ET).o $(T)$(OP).o
	gcc	-c	main.c

$(T)$(EX).o: $(T)$(EX).c $(T)$(EX).h ../$(EX).h  ../$(ET).h ../$(OP).h
	gcc	-c	$(T)$(EX).c

$(T)$(ET).o: $(T)$(ET).c $(T)$(ET).h ../$(OP).h ../$(ET).h
	gcc	-c	$(T)$(ET).c

$(T)$(OP).o:	../$(OP).h	$(T)$(OP).c	$(T)$(OP).h
	gcc -c  $(T)$(OP).c -lm

../$(EX).o: ../$(EX).c ../$(EX).h ../$(ET).h ../$(OP).h
	gcc	-c	../$(EX).c

../$(ET).o: ../$(ET).c ../$(ET).h ../$(OP).h
	gcc	-c	../$(ET).c

../$(OP).o: ../$(OP).h ../$(OP).c	
	gcc -c  ../$(OP).c -lm

clean:
	rm	*.o
	rm  *.exe