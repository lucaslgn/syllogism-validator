all:
	g++ -std=c++17 -Wall -Wextra -pedantic src/categorical_proposition.cpp src/syllogism.cpp src/main.cpp -o exe
run:
	./exe
