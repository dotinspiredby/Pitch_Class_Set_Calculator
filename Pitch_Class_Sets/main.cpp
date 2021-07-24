#include "pc_sets.h"
#include <sstream>

using namespace std;


void ParseTheChord(const string& s) {
	set <int> chord;
	
	auto left = begin(s);
	auto right = begin(s);

	while (right != s.end()) {
		right = find(left, s.end(), ' ');
		string extr = { left, right };
		if (stoi(extr) >= 0 && stoi(extr) < 12) {
			chord.insert(stoi(extr));
		}
		else {
			throw (invalid_argument("Unknown data in set"));
		}
		if (right != s.end()) {
			++right;
			left = right;
		}
	}

	if (!chord.empty()) {
		PCSetCalculator pc(chord);

		cout << "wrap around interval " << pc.WrapAroudInterval() << '\n';
		cout << "prime form " << pc.PrimeForm() << '\n';
		cout << "interval vector " << pc.ICVector() << '\n';
	}
	else {
		PCSetCalculator pc;
	}
	
}

int main() {
	cout << "Enter the chord pitch classes from 0 to 11 " << '\n';
	for (string line; getline(cin, line);) {
		istringstream input(line);
		try {
			ParseTheChord(line);
		}
		catch (invalid_argument& in_varg) {
			cout << in_varg.what() << '\n';
		}
	}
	return 0;
}

