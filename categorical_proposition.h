#include <string>
#include <istream>

using str = std::string;

enum class type : char {
	universal_affirmative = 'A', //All S are P
	universal_negative = 'E', //All S are not P
	particular_affirmative = 'I', //Some S are P
	particular_negative = 'O', //Some S are not P
};

class categorical_proposition {
public:
	friend std::istream& operator>>(std::istream&, categorical_proposition&);
	friend class syllogism;
	void clear();
private:
	str pronoun; //possibilities: all; no
	str subject;
	str verb; //possibilities: are; aren't
	str predicate;

	void determine_type();
	char type;
};
