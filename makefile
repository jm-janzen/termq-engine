bin/main: bin/main.o
	g++ -g -o bin/main bin/main.o -std=c++11 -lncurses -fno-stack-protector # disable canaries (better err messages)

bin/main.o: src/main.cpp
	g++ -g -c -o bin/main.o src/main.cpp -std=c++11

