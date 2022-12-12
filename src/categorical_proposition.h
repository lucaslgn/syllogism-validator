#include <string>
#include <istream>

using str = std::string;

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
