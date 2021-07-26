#pragma once

#include <iostream>
#include <set>
#include <vector>
#include <algorithm>


using namespace std;

class PCSetCalculator {
public:
	PCSetCalculator() = default;
	PCSetCalculator(const set <int>& input_chord);


	int WrapAroudInterval() const;
	vector <int> PrimeForm() const;
	vector <int> ICVector() const;

private:
	set <int> chord;
	vector <int> dists;
	vector <int> prime_form;
	vector <int> ic_vector;
	int wrap_around_interval;
	void CalculateDistances(const set <int>& chord);
	void CalulatePrimeForm(const vector <int>& dists);
	void IC();
};

void PCSetCalculator::CalculateDistances(const set <int>& chord) {
	set <int>::iterator it;
	for (it = chord.begin(); it != chord.end(); ++it) {
		if (it == --chord.end()) {
			dists.push_back(abs(abs(*it - *chord.begin()) - 12));
		}
		else {
			dists.push_back(abs(*it - *next(it)));
		}
	}
}

void PCSetCalculator::CalulatePrimeForm(const vector <int>& dists_) {
	set <int> types_of_pc = { dists_.begin(), dists_.end() };
	wrap_around_interval = *types_of_pc.rbegin();

	int m_times = count(dists_.begin(), dists_.end(), wrap_around_interval);

	auto it = dists_.begin();
	auto rit = dists_.rbegin();
	set <vector <int>> temp_permutations;
	for (int t = 1; t <= m_times; ++t) { //cycle of building vectors left directed and right directed
		it = find(it, dists_.end(), wrap_around_interval);
		rit = find(rit, dists_.rend(), wrap_around_interval);
		vector <int> left_dir;
		left_dir.insert(left_dir.end(), rit + 1, dists_.rend());
		left_dir.insert(left_dir.end(), dists_.rbegin(), rit + 1);
		vector <int> right_dir;
		right_dir.insert(right_dir.end(), it + 1, dists_.end());
		right_dir.insert(right_dir.end(), dists_.begin(), it + 1);
		temp_permutations.insert(left_dir);
		temp_permutations.insert(right_dir);
		++it;
		++rit;
	}

	int s = 0;
	for (size_t i = 0; i < (*temp_permutations.begin()).size(); ++i) {
		prime_form[i] = s;
		s += (*temp_permutations.begin())[i];
	}
}

void PCSetCalculator::IC() {
	for (size_t n = 0; n < prime_form.size(); ++n) {
		for (size_t f = n + 1; f < prime_form.size(); ++f) {
			++ic_vector[
				(abs(prime_form[n] - prime_form[f]) <= 6 ?
					abs(prime_form[n] - prime_form[f]) :
					12 - (abs(prime_form[n] - prime_form[f])))
					- 1];
		}
	}
}

PCSetCalculator::PCSetCalculator(const set <int>& input_chord) :
	chord(input_chord), prime_form(chord.size()), ic_vector(6, 0) {
	CalculateDistances(chord); CalulatePrimeForm(dists); IC();
}

int PCSetCalculator::WrapAroudInterval() const { return wrap_around_interval; }
vector <int> PCSetCalculator::PrimeForm() const { return prime_form; }
vector <int> PCSetCalculator::ICVector() const { return ic_vector; }


template <typename T>
ostream& operator <<(ostream& out, vector <T> v) {
	for (const auto item : v) {
		out << item << ' ';
	}
	return out;
}
