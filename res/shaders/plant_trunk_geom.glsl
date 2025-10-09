#version 440

layout (lines) in;
layout (triangle_strip, max_vertices = 4) out;

uniform mat4 uModelMatrix;
uniform mat4 uViewMatrix;
uniform mat4 uProjectionMatrix;
uniform int uVoxelRes;
uniform float uVoxelWorldSize;
uniform int uRenderMode; // 0 = write voxels, 1 = write to gbuffer

in vec3 inWorldPos[];
in vec3 inNormal[];
out vec3 worldPos;
out vec3 normal;

void main() {
	mat4 mvp = uModelMatrix * uViewMatrix * uProjectionMatrix;
	vec4 p0 = gl_in[0].gl_Position;
	vec4 p1 = gl_in[1].gl_Position;

    vec3 dir = normalize(p1.xyz - p0.xyz);
    vec3 perpendicular = normalize(cross(dir, vec3(0.0, 0.0, 1.0)));
    perpendicular *= /*width * */ 0.5;

	gl_Position = vec4(p0.xyz + perpendicular, p0.w);
	normal = inNormal[0];
	worldPos = inWorldPos[0];
	EmitVertex();
	gl_Position = vec4(p1.xyz + perpendicular, p1.w);
	normal = inNormal[1];
	worldPos = inWorldPos[1];
	EmitVertex();
	gl_Position = vec4(p0.xyz - perpendicular, p0.w);
	normal = inNormal[0];
	worldPos = inWorldPos[0];
	EmitVertex();
	gl_Position = vec4(p1.xyz - perpendicular, p1.w);
	normal = inNormal[1];
	worldPos = inWorldPos[1];
	EmitVertex();

	EndPrimitive();
}
