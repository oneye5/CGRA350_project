#include "lsystem/node/node.hpp"
#include "lsystem/node/common.hpp"

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/transform.hpp>

using namespace glm;

namespace lsystem::node::common {
	void Push::render(std::vector<node_stack> &stack, cgra::mesh_builder &trunk, cgra::mesh_builder &canopy) const {
		(void)trunk, (void)canopy;
		stack.push_back(stack.back());
	}
	Push::~Push() {}
	std::shared_ptr<const Push> push = std::make_shared<Push>();

	void Pop::render(std::vector<node_stack> &stack, cgra::mesh_builder &trunk, cgra::mesh_builder &canopy) const {
		(void)trunk, (void)canopy;
		stack.pop_back();
	}
	Pop::~Pop() {}
	std::shared_ptr<const Pop> pop = std::make_shared<Pop>();

	template<glm::vec3 axis>
	Rotate<axis>::Rotate(float angle) : angle{angle} {}

	template<glm::vec3 axis>
	Rotate<axis>::~Rotate() {}

	template<glm::vec3 axis>
	void Rotate<axis>::render(std::vector<node_stack> &stack, cgra::mesh_builder &trunk, cgra::mesh_builder &canopy) const {
		(void)trunk, (void)canopy;
		stack.back().trans = rotate(stack.back().trans, this->angle, axis);
	}

	//  From https://stackoverflow.com/a/8752879
	template class Rotate<glm::vec3{1,0,0}>;  // RotateX
	template class Rotate<glm::vec3{0,1,0}>;  // RotateY
	template class Rotate<glm::vec3{0,0,1}>;  // RotateZ

	// RotateX::RotateX(float angle) : Rotate<vec3{1,0,0}>(angle) {};
	// RotateX::~RotateX() {};

	Translate::Translate(vec3 dist) : dist{dist} {}
	void Translate::render(std::vector<node_stack> &stack, cgra::mesh_builder &trunk, cgra::mesh_builder &canopy) const {
		(void)trunk, (void)canopy;
		stack.back().trans = translate(stack.back().trans, dist);
	}
	Translate::~Translate() {}

	void TrunkVertex::render(std::vector<node_stack> &stack, cgra::mesh_builder &trunk, cgra::mesh_builder &canopy) const {
		(void)trunk, (void)canopy;
		// TODO: Normals: translate by one then see where that leaves us as the normal?
		trunk.push_index(trunk.push_vertex({vec3{stack.back().trans * vec4{0,0,0,1}} }));
	}
	TrunkVertex::~TrunkVertex() {}
	std::shared_ptr<const TrunkVertex> trunkVertex = std::make_shared<TrunkVertex>();

	void CanopyVertex::render(std::vector<node_stack> &stack, cgra::mesh_builder &trunk, cgra::mesh_builder &canopy) const {
		(void)trunk, (void)canopy;
		// TODO: Normals: translate by one then see where that leaves us as the normal?
		canopy.push_index(trunk.push_vertex({vec3{stack.back().trans * vec4{0,0,0,1}}}));
	}
	CanopyVertex::~CanopyVertex() {}
	std::shared_ptr<const CanopyVertex> canopyVertex = std::make_shared<CanopyVertex>();
}
