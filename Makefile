all:
	g++ -std=c++17 -Wall -Wextra -pedantic categorical_proposition.cpp syllogism.cpp main.cpp -o exe
run:
	./exe
