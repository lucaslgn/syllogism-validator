#include "categorical_proposition.h"
#include <stdexcept>
#include <iostream>

std::istream& operator>>(std::istream& is, categorical_proposition& proposition) {
	is >> proposition.pronoun;

	//determining the subject
	str aux;
	while (is >> aux && aux != "are") {
		proposition.subject += aux;
		proposition.subject += " ";
	}
	proposition.subject.pop_back();

	//determining the verb
	proposition.verb = aux;
	is >> aux;
	if (aux == "not") {
		proposition.verb += " ";
		proposition.verb += aux;
		is >> aux;
	}

	//determining the predicate
	do {
		proposition.predicate += aux;
		proposition.predicate += " ";
	}
	while (aux.back() != '.' && is >> aux);
	proposition.predicate.pop_back();
	proposition.predicate.pop_back();

	/*
	std::cout << "pronoun: " << proposition.pronoun << '\n';
	std::cout << "subject: " << proposition.subject << '\n';
	std::cout << "verb: " << proposition.verb << '\n';
	std::cout << "predicate: " << proposition.predicate << '\n';
	*/

	proposition.determine_type();

	return is;
}
void categorical_proposition::determine_type() {
	if (pronoun == "All" && verb == "are") 
		type = 'A';
	else if (pronoun == "Some" && verb == "are")
		type = 'I';
	else if (pronoun == "All" && verb == "are not")
		type = 'E';
	else if (pronoun == "Some" && verb == "are not")
		type = 'O';
	else
		throw std::runtime_error{"Invalid proposition"};
}
void categorical_proposition::clear() {
	pronoun.clear();
	subject.clear();
	verb.clear();
	predicate.clear();
}
