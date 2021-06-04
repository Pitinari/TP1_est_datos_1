#abreviaturas para los archivos
OP	=	operadores
ET	=	ExpTree
EX	=	Expression
T = test_

#declaracion de destinos
main:	main.o	$(OP).o	$(ET).o	$(EX).o
	gcc	-o $@.out $@.o $(ET).o $(EX).o $(OP).o -lm

main.o:	main.c $(EX).o $(ET).o $(OP).o
	gcc	-c	main.c

test:	test.o	$(T)$(OP).o	$(T)$(ET).o	$(T)$(EX).o
	gcc	-o $@.out test.o $(T)$(ET).o $(T)$(EX).o $(T)$(OP).o $(OP).o	$(ET).o	$(EX).o	-lm


test.o:	./test/test.c $(T)$(EX).o $(T)$(ET).o $(T)$(OP).o	$(OP).o	$(ET).o	$(EX).o
	gcc	-c	./test/test.c

$(EX).o: $(EX).c $(EX).h $(ET).h $(OP).h
	gcc	-c	$(EX).c

$(ET).o: $(ET).c $(ET).h $(OP).h
	gcc	-c	$(ET).c

$(OP).o: $(OP).h $(OP).c	
	gcc -c  $(OP).c -lm

$(T)$(EX).o: ./test/$(T)$(EX).c ./test/$(T)$(EX).h	./test/$(T)$(ET).h $(EX).h  $(ET).h $(OP).h
	gcc	-c	./test/$(T)$(EX).c

$(T)$(ET).o: ./test/$(T)$(ET).c ./test/$(T)$(ET).h $(OP).h $(ET).h
	gcc	-c	./test/$(T)$(ET).c

$(T)$(OP).o:	$(OP).h	./test/$(T)$(OP).c	./test/$(T)$(OP).h
	gcc -c  ./test/$(T)$(OP).c -lm
clean:
	rm	*.o
	rm  main