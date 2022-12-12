#include "syllogism.h"
#include <stdexcept>

std::istream& operator>>(std::istream& is, syllogism& syllogism) {
	syllogism.clear();

	is >> syllogism.premise1;
	is >> syllogism.premise2;
	is >> syllogism.conclusion;

	syllogism.determine_terms();	

	return is;
}
bool syllogism::is_valid() const {
	arr_venn venn_premises{state::unknown};
	if (premise1.type == 'A' || premise1.type == 'E') {
		diagram(premise1, venn_premises);
		diagram(premise2, venn_premises);
	} else {
		diagram(premise2, venn_premises);
		diagram(premise1, venn_premises);
	}
	arr_venn venn_conclusion = venn_premises;
	diagram(conclusion, venn_conclusion);	
	for (int i = 0; i < 7; ++i)
		if (venn_conclusion[i] != venn_premises[i])
			return false;
	return true;
}
void syllogism::determine_terms() {
	if (premise1.subject == premise2.subject || premise1.subject == premise2.predicate)
		middle_term = premise1.subject;
	else if (premise1.predicate == premise2.subject || premise1.predicate == premise2.predicate)
		middle_term = premise1.predicate;
	else
		throw std::runtime_error{"there are no middle term in your syllogism"};
	minor_term = conclusion.subject;
	major_term = conclusion.predicate;
}
void syllogism::clear() {
	premise1.clear();
	premise2.clear();
	conclusion.clear();
}
void syllogism::diagram(const categorical_proposition& premise, arr_venn& venn) const {
	if (premise.subject == minor_term && premise.predicate == major_term) //S P
		treat_case_sp(premise.type, venn);
	else if (premise.subject == minor_term && premise.predicate == middle_term) //S M
		treat_case_sm(premise.type, venn);
	else if (premise.subject == major_term && premise.predicate == minor_term) //P S
		treat_case_ps(premise.type, venn);
	else if (premise.subject == major_term && premise.predicate == middle_term) //P M
		treat_case_pm(premise.type, venn);
	else if (premise.subject == middle_term && premise.predicate == minor_term) //M S
		treat_case_ms(premise.type, venn);
	else if (premise.subject == middle_term && premise.predicate == major_term) //M P
		treat_case_mp(premise.type, venn);
}

void syllogism::treat_case_sp(const char& type, arr_venn& venn) const {
	if (type == 'A') { //All S are P
		venn[0] = state::shaded;
		venn[3] = state::shaded;
	} else if (type == 'E') { //All S are not P
		venn[1] = state::shaded;
		venn[4] = state::shaded;
	} else if (type == 'I') { //Some S are P
		if (venn[1] == state::unknown && venn[4] != state::x)
			venn[1] = state::x;
		if (venn[4] == state::unknown && venn[1] != state::x)
			venn[4] = state::x;
	} else if (type == 'O') { //Some S are not P
		if (venn[0] == state::unknown && venn[3] != state::x)
			venn[0] = state::x;
		if (venn[3] == state::unknown)
			venn[3] = state::x;
	}
}
void syllogism::treat_case_sm(const char& type, arr_venn& venn) const {
	if (type == 'A') { //All S are M
		venn[0] = state::shaded;
		venn[1] = state::shaded;
	} else if (type == 'E') { //All S are not M
		venn[3] = state::shaded;	
		venn[4] = state::shaded;
	} else if (type == 'I') { //Some S are M
		if (venn[3] == state::unknown)
			venn[3] = state::x;
		if (venn[4] == state::unknown)
			venn[4] = state::x;
	} else if (type == 'O') { //Some S are not M
		if (venn[0] == state::unknown)
			venn[0] = state::x;
		if (venn[1] == state::unknown)
			venn[1] = state::x;
	}
}
void syllogism::treat_case_ps(const char& type, arr_venn& venn) const {
	if (type == 'A') { //All P are S
		venn[2] = state::shaded;
		venn[5] = state::shaded;
	} else if (type == 'E') { //All P are not S
		venn[1] = state::shaded;
		venn[4] = state::shaded;
	} else if (type == 'I') { //Some P are S
		if (venn[1] == state::unknown && venn[4] != state::x)
			venn[1] = state::x;
		if (venn[4] == state::unknown && venn[1] != state::x)
			venn[4] = state::x;
	} else if (type == 'O') { //Some P are not S
		if (venn[2] == state::unknown && venn[5] != state::x)
			venn[2] = state::x;
		if (venn[5] == state::unknown && venn[2] != state::x)
			venn[5] = state::x;
	}

}
void syllogism::treat_case_pm(const char& type, arr_venn& venn) const {
	if (type == 'A') { //All P are M
		venn[1] = state::shaded;
		venn[2] = state::shaded;
	} else if (type == 'E') { //All P are not M
		venn[4] = state::shaded;
		venn[5] = state::shaded;
	} else if (type == 'I') { //Some P are M
		if (venn[4] == state::unknown)
			venn[4] = state::x;
		if (venn[5] == state::unknown)
			venn[5] = state::x;
	} else if (type == 'O') { //Some P are not M
		if (venn[1] == state::unknown)
			venn[1] = state::x;
		if (venn[2] == state::unknown)
			venn[2] = state::x;
	}
}
void syllogism::treat_case_ms(const char& type, arr_venn& venn) const {
	if (type == 'A') { //All M are S
		venn[5] = state::shaded;
		venn[6] = state::shaded; 
	} else if (type == 'E') { //All M are not S
		venn[3] = state::shaded;
		venn[4] = state::shaded;
	} else if (type == 'I') { //Some M are S
		if (venn[3] == state::unknown)
			venn[3] = state::x;
		if (venn[4] == state::unknown)
			venn[4] = state::x;
	} else if (type == 'O') { //Some M are not S
		if (venn[5] == state::unknown)
			venn[5] = state::x;
		if (venn[6] == state::unknown)
			venn[6] = state::x;
	}
}
void syllogism::treat_case_mp(const char& type, arr_venn& venn) const {
	if (type == 'A') { //All M are P
		venn[3] = state::shaded;
		venn[6] = state::shaded;
	} else if (type == 'E') { //All M are not P
		venn[4] = state::shaded;
		venn[5] = state::shaded;
	} else if (type == 'I') { //Some M are P
		if (venn[4] == state::unknown)
			venn[4] = state::x;
		if (venn[5] == state::unknown)
			venn[5] = state::x;
	} else if (type == 'O') { //Some M are not P
		if (venn[3] == state::unknown)
			venn[3] = state::x;
		if (venn[6] == state::unknown)
			venn[6] = state::x;
	}
}
