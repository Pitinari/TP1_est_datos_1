#abreviaturas para los archivos
OP	=	operadores
ET	=	ExpTree
EX	=	Expression
T = test_
FLAGS = -Wall -Wextra -Werror -std=c99 -g

#declaracion de destinos
main:	main.o	$(OP).o	$(ET).o	$(EX).o
	gcc $(FLAGS)	-o $@.out $@.o $(ET).o $(EX).o $(OP).o -lm

main.o:	main.c $(EX).o $(ET).o $(OP).o
	gcc $(FLAGS)	-c	main.c -lm

test:	test.o	$(T)$(OP).o	$(T)$(ET).o	$(T)$(EX).o
	gcc $(FLAGS)	-o $@.out test.o $(T)$(ET).o $(T)$(EX).o $(T)$(OP).o $(OP).o	$(ET).o	$(EX).o	-lm


test.o:	./test/test.c $(T)$(EX).o $(T)$(ET).o $(T)$(OP).o	$(OP).o	$(ET).o	$(EX).o
	gcc $(FLAGS)	-c	./test/test.c -lm

$(EX).o: $(EX).c $(EX).h $(ET).h $(OP).h
	gcc $(FLAGS)	-c	$(EX).c -lm

$(ET).o: $(ET).c $(ET).h $(OP).h
	gcc $(FLAGS)	-c	$(ET).c -lm

$(OP).o: $(OP).h $(OP).c	
	gcc $(FLAGS) -c  $(OP).c -lm

$(T)$(EX).o: ./test/$(T)$(EX).c ./test/$(T)$(EX).h	./test/$(T)$(ET).h $(EX).h  $(ET).h $(OP).h
	gcc $(FLAGS)	-c	./test/$(T)$(EX).c -lm

$(T)$(ET).o: ./test/$(T)$(ET).c ./test/$(T)$(ET).h $(OP).h $(ET).h
	gcc $(FLAGS)	-c	./test/$(T)$(ET).c -lm

$(T)$(OP).o:	$(OP).h	./test/$(T)$(OP).c	./test/$(T)$(OP).h
	gcc $(FLAGS) -c  ./test/$(T)$(OP).c -lm

clean:
	rm	*.o
	rm  *.out
	rm	./test/*.o
	rm	./test/*.out