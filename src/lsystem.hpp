#pragma once
#include "lsystem/node/node.hpp"
#include <vector>

namespace lsystem {
	typedef std::vector<const node::Node *> ruleset;
	lsystem::ruleset iterate(const lsystem::ruleset &current, std::minstd_rand &rng, const int count = 1);
}
