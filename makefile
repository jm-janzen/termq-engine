CFLAGS = -std=c++11 -w -fno-stack-protector # disable canaries

bin/main: bin/main.o bin/menu.o bin/InfoPanel.o
	g++ -g -o bin/main bin/main.o bin/menu.o bin/InfoPanel.o $(CFLAGS) -lncurses

bin/main.o: src/main.cpp
	g++ -g -c -o bin/main.o src/main.cpp $(CFLAGS)

bin/menu.o: src/menu.cpp src/menu.h src/InfoPanel.h
	g++ -g -c -o bin/menu.o src/menu.cpp $(CFLAGS)

bin/InfoPanel.o: src/InfoPanel.cpp src/InfoPanel.h
	g++ -g -c -o bin/InfoPanel.o src/InfoPanel.cpp $(CFLAGS)

