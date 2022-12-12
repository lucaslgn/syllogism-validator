#include "categorical_proposition.h"
#include <stdexcept>
#include <sstream>

std::istream& operator>>(std::istream& is, categorical_proposition& proposition) {
	str line;
	std::getline(is, line);
	auto ss = std::stringstream(line);

	ss >> proposition.pronoun;
	if (proposition.pronoun[0] >= 97)
		proposition.pronoun[0] -= 32;

	//determining the subject
	str aux;
	while (ss >> aux && aux != "are") {
		proposition.subject += aux;
		proposition.subject += " ";
	}
	proposition.subject.pop_back();

	//determining the verb
	proposition.verb = aux;
	ss >> aux;
	if (aux == "not") {
		proposition.verb += " ";
		proposition.verb += aux;
		ss >> aux;
	}

	//determining the predicate
	do {
		proposition.predicate += aux;
		proposition.predicate += " ";
	}
	while (ss >> aux);
	proposition.predicate.pop_back();

	if (proposition.predicate.back() == '.' || proposition.predicate.back() == ',')
		proposition.predicate.pop_back();

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
