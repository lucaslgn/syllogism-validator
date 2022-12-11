#include <istream>
#include <array>
#include "categorical_proposition.h"

enum class state {
	unknown,
	shaded,
	x,
};

using arr_venn = std::array<state, 7>;

class syllogism {
public:
	friend std::istream& operator>>(std::istream&, syllogism&);
	bool is_valid() const;
private:
	categorical_proposition premise1, premise2, conclusion;

	str minor_term;
	str middle_term;
	str major_term;

	void determine_terms();
	void diagram(const categorical_proposition&, arr_venn&) const;

	void treat_case_sp(const char&, arr_venn&) const;
	void treat_case_sm(const char&, arr_venn&) const;
	void treat_case_ps(const char&, arr_venn&) const;
	void treat_case_pm(const char&, arr_venn&) const;
	void treat_case_ms(const char&, arr_venn&) const;
	void treat_case_mp(const char&, arr_venn&) const;

	void clear();
};
