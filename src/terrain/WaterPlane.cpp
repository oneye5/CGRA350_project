
#include "WaterPlane.hpp"

#include "cgra/cgra_image.hpp"

using namespace Terrain;

WaterPlane::WaterPlane(GLuint texid) : plane_mesh(cgra::CREATE_PLANE(256, 256).build()), water_texture(texid), water_height(0.0f) {
	if (!water_texture) { // Water texture not supplied
		water_texture = cgra::rgba_image(WATER_TEXTURE_PATH).uploadTexture();
	}

	
}

GLuint WaterPlane::getShader() {
	return shader;
}

void WaterPlane::setProjViewUniforms(const glm::mat4 &view, const glm::mat4 &proj) const {
}

void WaterPlane::draw() {
}

glm::mat4 WaterPlane::getModelTransform() {
	return init_transform;
}
