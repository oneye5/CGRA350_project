#pragma once
#include <glm/glm.hpp>
#include "lsystem.hpp"
#include "cgra/cgra_mesh.hpp"
#include "opengl.hpp"
#include "renderable.hpp"

namespace plant {
	struct Mesh : Renderable {
		cgra::gl_mesh mesh;
		GLuint shader;
		glm::mat4 modelTransform;

		Mesh();
		Mesh(GLuint shader);

		virtual void draw() override;
		virtual void setProjViewUniforms(const glm::mat4& view, const glm::mat4& proj) const override;
		virtual GLuint getShader() override;
		virtual glm::mat4 getModelTransform() override;
	};

	class Plant {
		// TODO: Store like an rng or something
		Mesh trunk;
		Mesh canopy;

		lsystem::ruleset ruleset;
		std::string seed;
		/** Current representation of the plant as a string */
		std::string current;
		void recalculate_mesh();

		public:
		Plant(std::string seed, GLuint trunk_shader, GLuint canopy_shader, lsystem::ruleset ruleset, int steps = 0);
		void grow(int steps = 1);
	};
}
