#include "lsystem/node/node.hpp"
#include "lsystem/node/common.hpp"
#include "lsystem/node/tree.hpp"

using namespace lsystem::node::common;

namespace lsystem::node::tree {
	std::shared_ptr<const Branch> branch = std::make_shared<Branch>();
	std::shared_ptr<const Leaf> leaf = std::make_shared<Leaf>();

	Branch::~Branch() {}
	void Branch::render(std::vector<node_stack> &stack, cgra::mesh_builder &trunk, cgra::mesh_builder &canopy) const {
	}

	Leaf::~Leaf() {}
	std::vector<std::shared_ptr<const Node>> Leaf::grow(std::shared_ptr<const Node> self, std::minstd_rand& rng) const {
		std::vector<std::shared_ptr<const Node>> ret;
		ret.push_back(branch);                                     // F
		ret.push_back(push);                                       // [
		ret.push_back(std::make_shared<RotateX>(0.3));         // +
		ret.push_back(leaf);                                       // A
		ret.push_back(pop);                                        // ]
		ret.push_back(push);                                       // [
		ret.push_back(std::make_shared<RotateX>(-0.3));            // -
		ret.push_back(leaf);                                       // A
		ret.push_back(pop);                                        // ]
		return ret;
	}
	void Leaf::render(std::vector<node_stack> &stack, cgra::mesh_builder &trunk, cgra::mesh_builder &canopy) const {

	}
}
