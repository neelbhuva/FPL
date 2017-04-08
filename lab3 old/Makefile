scanner.o : main.cpp interpreter.cpp binaryTree.cpp scanner.h binaryTree.h interpreter.h
	g++ -std=c++11 -c interpreter.cpp 
	g++ -std=c++11 -c binaryTree.cpp
	g++ -std=c++11 -c main.cpp
	g++ -std=c++11 interpreter.o binaryTree.o main.o -o main
