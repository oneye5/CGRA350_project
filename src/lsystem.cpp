#include <algorithm>
#include <vector>
#include <string>
#include "lsystem.hpp"

using std::vector;

lsystem::ruleset lsystem::iterate(const lsystem::ruleset &current, std::minstd_rand &rng, const int count) {
	lsystem::ruleset prev = current;
	lsystem::ruleset cur;
	for (int i = 0; i < count; i++) {
		for (const auto& n : prev) {
			auto vec = n->grow(rng);
			cur.insert(cur.end(), vec.begin(), vec.end());
		}

		for (const auto &n : prev) {
			delete n;
		}

		prev = cur;
		cur.clear();
	}

	return cur;
}
