#include <string>
#include <istream>

using str = std::string;

class categorical_proposition {
public:
	friend std::istream& operator>>(std::istream&, categorical_proposition&);
	friend class syllogism;
	void clear();
private:
	str pronoun; //possibilities: all; some
	str subject;
	str verb; //possibilities: are; are not
	str predicate;

	void determine_type();
	char type;
};
