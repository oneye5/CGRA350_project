#include "lsystem/node/node.hpp"
#include "lsystem/node/common.hpp"
#include "lsystem/node/tree.hpp"

using namespace lsystem::node::common;

namespace lsystem::node::tree {

	void Leaf::render(std::vector<node_stack> &stack, cgra::mesh_builder &trunk, cgra::mesh_builder &canopy) const {

	}

	Leaf::~Leaf() {}

	void Branch::render(std::vector<node_stack> &stack, cgra::mesh_builder &trunk, cgra::mesh_builder &canopy) const {
	}

	Branch::~Branch() {}

	const Branch *branch = new Branch();
	const Leaf *leaf = new Leaf();
	std::vector<const Node*> Leaf::grow(std::minstd_rand& rng) const {
		std::vector<const Node*> ret;
		ret.push_back(branch);                   // F
		ret.push_back(push);                     // [
		ret.push_back(new RotateX(0.3));  // +
		ret.push_back(leaf);                     // A
		ret.push_back(pop);                      // ]
		ret.push_back(push);                     // [
		ret.push_back(new RotateX(-0.3)); // -
		ret.push_back(leaf);                     // A
		ret.push_back(pop);                      // ]
		return ret;
	}
}
