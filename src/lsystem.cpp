#include <iostream>
#include <istream>
#include <sstream>
#include <string>
#include <unordered_map>
#include "imgui.h"
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
	std::string cur = seed;
	std::stringstream res{};
	for (int i = 0; i < count; i++) {
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

namespace lsystem::gui {
	void rules_window(struct Data &data) {
		ImGui::SetNextWindowPos(ImVec2(5, 205), ImGuiSetCond_Once);
		ImGui::SetNextWindowSize(ImVec2(300, 200), ImGuiSetCond_Once);
		ImGui::Begin("LSystem Rules", nullptr);

		static int rule_idx = 0;
		if (ImGui::Combo("Rule", &rule_idx, available_rule_names, sizeof(available_rule_names)/sizeof(*available_rule_names))) {
			if (rule_idx) {
				// TODO: Load rules
			} else {
				data.rules = {};
			}
		}

		ImGui::End();
	}
}
