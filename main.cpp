#include "syllogism.h"
#include <iostream>

int main() {
	syllogism syllogism;
	while (std::cin >> syllogism) {
		if (syllogism.is_valid())
			std::cout << "Valid syllogism\n\n";
		else
			std::cout << "Invalid syllogism\n\n";
	}
}
