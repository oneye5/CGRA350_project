#include "lsystem/node/node.hpp"
#include <memory>

namespace lsystem::node {
	std::vector<std::shared_ptr<const Node>> Node::grow(std::shared_ptr<const Node> self, std::minstd_rand &rng) const {
		(void)rng;
		return std::vector{self};
	}
	Node::Node() {}
	Node::~Node() {}
}
