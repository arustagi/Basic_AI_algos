
all: CS561A1.exe

CS561A1.exe: main.o Astar.o BFS.o DFS.o UCS.o
	g++ Astar.o BFS.o DFS.o UCS.o main.o -o CS561A1.exe

main.o: main.cc
	g++ -c -Wall main.cc

BFS.o: BFS.cc
	g++ -c -Wall BFS.cc

DFS.o: DFS.cc
	g++ -c -Wall DFS.cc

UCS.o: UCS.cc
	g++ -c -Wall UCS.cc

Astar.o: Astar.cc
	g++ -c -Wall Astar.cc

clean:
	rm -rf *.o CS561A1.exe
