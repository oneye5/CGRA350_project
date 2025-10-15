#include <algorithm>
#include <fstream>
#include <iostream>
#include <vector>
#include <istream>
#include <sstream>
#include <string>
#include <unordered_map>
#include "imgui.h"
#include "lsystem.hpp"

using std::vector;

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
	std::string cur = seed;
	for (int i = 0; i < count; i++) {
		std::stringstream res{};
		for (const auto& c : cur) {
			if (rules.find(c) != rules.end()) {
				res << rules.at(c);
			} else {
				res << c;
			}
		}
		cur = res.str();
	}
	return cur;
}
