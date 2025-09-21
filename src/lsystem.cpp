#include <iostream>
#include <istream>
#include <sstream>
#include <string>
#include <unordered_map>
#include "lsystem.hpp"

lsystem::ruleset lsystem::parse_rules(std::istream& rules) {
	std::unordered_map<char, std::string> map;
	
	while(rules.peek() && !rules.eof()) {
		char k = rules.get();
		if (rules.get() != ':') {
			throw "Bad rules format, missing :";
		}
		std::string v;
		std::getline(rules, v);
		map[k] = v;
	}

	return map;
}

std::string lsystem::iterate(const std::string &seed, const ruleset &rules, int count) {
	if (count <= 0) return seed;
	std::cout << "TODO! iterate\n";
	return seed;
}
