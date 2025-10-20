#version 440

layout (points) in;
layout (triangle_strip, max_vertices = 12) out;

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
out vec2 uvCoord;


// uniform mat4 projection;
// uniform mat4 view;
// uniform mat4 model;

// Cylinder radius
uniform float lineRadius = 0.1;

// // Input vertices from vertex shader
// in vec3 vertexColor[];
// // Output for fragment shader
// out vec3 fragColor;

void main() {
	// Get start and end points of the line
	vec4 pt = gl_in[0].gl_Position;
	mat4 mvp = uProjectionMatrix * uViewMatrix * uModelMatrix;

	vec3 right = normalize(cross(inNormal[0], vec3(0,1,0)));
	vec3 up = normalize(cross(right, inNormal[0]));
	vec3 norm = normalize(-cross(right, up));
	vec3 nDir = -inNormal[0];
	float sc = 0.05;
	float dx = 0.0;
	float dy = 0.0;
	float dz = 0.0;

	dx = -0.1; dy = 0; dz = 0;
	gl_Position = mvp * vec4(pt.xyz + right * sc * dx + up * sc * dy + nDir * sc * dz, 1.0); // 0
	uvCoord = vec2(0.5 + dx, 0.5 + dy);
	worldPos = inWorldPos[0];
	normal = norm;
	EmitVertex();

	dx = 0.1; dy = 0; dz = 0;
	gl_Position = mvp * vec4(pt.xyz + right * sc * dx + up * sc * dy + nDir * sc * dz, 1.0); // 0
	uvCoord = vec2(0.5 + dx, 0.5 + dy);
	worldPos = inWorldPos[0];
	normal = norm;
	EmitVertex();

	dx = 0.1; dy = 0.1; dz = 0;
	gl_Position = mvp * vec4(pt.xyz + right * sc * dx + up * sc * dy + nDir * sc * dz, 1.0); // 0
	uvCoord = vec2(0.5 + dx, 0.5 + dy);
	worldPos = inWorldPos[0];
	normal = norm;
	EmitVertex();

	dx = 0.0; dy = 0; dz = -0.1;
	gl_Position = mvp * vec4(pt.xyz + right * sc * dx + up * sc * dy + nDir * sc * dz, 1.0); // 0
	uvCoord = vec2(0.5 + dx, 0.5 + dy);
	worldPos = inWorldPos[0];
	normal = norm;
	EmitVertex();

	dx = 0.0; dy = 0; dz = 0.1;
	gl_Position = mvp * vec4(pt.xyz + right * sc * dx + up * sc * dy + nDir * sc * dz, 1.0); // 0
	uvCoord = vec2(0.5 + dx, 0.5 + dy);
	worldPos = inWorldPos[0];
	normal = norm;
	EmitVertex();

	dx = 0.0; dy = 0.1; dz = 0;
	gl_Position = mvp * vec4(pt.xyz + right * sc * dx + up * sc * dy + nDir * sc * dz, 1.0); // 0
	uvCoord = vec2(0.5 + dx, 0.5 + dy);
	worldPos = inWorldPos[0];
	normal = norm;
	EmitVertex();

	dx = 0.2; dy = 0.2; dz = 0.3;
	gl_Position = mvp * vec4(pt.xyz + right * sc * dx + up * sc * dy + nDir * sc * dz, 1.0); // 0
	uvCoord = vec2(0.5 + dx, 0.5 + dy);
	worldPos = inWorldPos[0];
	normal = norm;
	EmitVertex();

	dx = 0.2; dy = 0.0; dz = 0.1;
	gl_Position = mvp * vec4(pt.xyz + right * sc * dx + up * sc * dy + nDir * sc * dz, 1.0); // 0
	uvCoord = vec2(0.5 + dx, 0.5 + dy);
	worldPos = inWorldPos[0];
	normal = norm;
	EmitVertex();

	dx = 0.2; dy = 0.3; dz = 0.1;
	gl_Position = mvp * vec4(pt.xyz + right * sc * dx + up * sc * dy + nDir * sc * dz, 1.0); // 0
	uvCoord = vec2(0.5 + dx, 0.5 + dy);
	worldPos = inWorldPos[0];
	normal = norm;
	EmitVertex();

	// Close the triangle strip
	EndPrimitive();
}
