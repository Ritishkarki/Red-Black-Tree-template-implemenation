FLAGS = -std=c++11

LIBS = -I.

.PHONY:	run
run:	main
	./main

main: main.o
	g++ $(FLAGS) ${LIBS} -o $@ $^

main.o: main.cpp
	g++ $(FLAGS) ${LIBS} -o $@ -c $^

clean: 
	$(RM) *.o main *.txt

