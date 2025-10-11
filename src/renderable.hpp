#pragma once
#include <GL/glew.h>
#include <glm/detail/type_mat.hpp>
#include <glm/detail/type_gentype.hpp>
#include <vector>


class Renderable {
public:
    virtual GLuint getShader() = 0;  // return shader program to use
    virtual std::vector<GLuint> getShaders() { return std::vector<GLuint> {getShader()}; }; // return shaders, override if more than 1 shader
    
    // all projection, model and view related uniforms should be set here
    virtual void setProjViewUniforms(const glm::mat4& view, const glm::mat4& proj) const = 0;

    // all other shader uniforms may be set here, as well as of course a draw call, make sure to call useProgram
    virtual void draw() = 0; 

    // also needed for the voxelization process, can just return an identity matrix if no model transformations are made
    virtual glm::mat4 getModelTransform() = 0;
};
