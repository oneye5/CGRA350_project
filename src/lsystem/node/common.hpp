#pragma once
#include "node.hpp"
#include "lsystem/node/node.hpp"

namespace lsystem::node::common {
	class Push : public Node {
		public:
		virtual void render(std::vector<node_stack> &stack, cgra::mesh_builder &trunk, cgra::mesh_builder &canopy) const override;
		virtual ~Push();
	};
	extern std::shared_ptr<const Push> push;

	class Pop : public Node {
		public:
		virtual void render(std::vector<node_stack> &stack, cgra::mesh_builder &trunk, cgra::mesh_builder &canopy) const override;
		virtual ~Pop();
	};
	extern std::shared_ptr<const Pop> pop;

	class Translate : public Node {
		glm::vec3 dist;
		public:
		Translate(glm::vec3 dist);

		virtual void render(std::vector<node_stack> &stack, cgra::mesh_builder &trunk, cgra::mesh_builder &canopy) const override;
		virtual ~Translate();
	};

	template<glm::vec3 axis>
	class Rotate : public Node {
		float og_angle;
		float angle;
		float variance;
		public:
		Rotate(float angle);
		Rotate(float angle, float variance);
		Rotate(float og_angle, float angle, float variance);
		virtual std::vector<std::shared_ptr<const Node>> grow(std::shared_ptr<const Node> self, std::minstd_rand &rng) const override;
		virtual void render(std::vector<node_stack> &stack, cgra::mesh_builder &trunk, cgra::mesh_builder &canopy) const override;
		virtual ~Rotate();

	};
	using RotateX = Rotate<glm::vec3{1,0,0}>;
	using RotateY = Rotate<glm::vec3{0,1,0}>;
	using RotateZ = Rotate<glm::vec3{0,0,1}>;

	class TrunkVertex : public Node {
		public:

		virtual void render(std::vector<node_stack> &stack, cgra::mesh_builder &trunk, cgra::mesh_builder &canopy) const override;
		virtual ~TrunkVertex();
	};
	extern std::shared_ptr<const TrunkVertex> trunkVertex;

	class CanopyVertex : public Node {
		public:

		virtual void render(std::vector<node_stack> &stack, cgra::mesh_builder &trunk, cgra::mesh_builder &canopy) const override;
		virtual ~CanopyVertex();
	};
	extern std::shared_ptr<const CanopyVertex> canopyVertex;
}
