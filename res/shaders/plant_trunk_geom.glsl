#version 440

layout (lines) in;
layout (triangle_strip, max_vertices = 24) out;

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

// uniform mat4 projection;
// uniform mat4 view;
// uniform mat4 model;

// Cylinder radius
uniform float lineRadius = 0.05;

// // Input vertices from vertex shader
// in vec3 vertexColor[];
// // Output for fragment shader
// out vec3 fragColor;

void main() {
    // Get start and end points of the line
    vec4 start = gl_in[0].gl_Position;
    vec4 end = gl_in[1].gl_Position;

    // Calculate line direction and length
    vec3 lineDir = normalize(end.xyz - start.xyz);
    float lineLength = distance(start.xyz, end.xyz);

    // Create a perpendicular vector (for cylinder cross-section)
    vec3 up = abs(lineDir.y) > 0.9 ? vec3(1, 0, 0) : vec3(0, 1, 0);
    vec3 right = normalize(cross(lineDir, up));
    up = normalize(cross(right, lineDir));

    // Generate cylinder vertices
    for (int i = 0; i <= 8; i++) {
        float angle = i * (2.0 * 3.14159 / 8.0);
        vec3 offset = lineRadius * (right * cos(angle) + up * sin(angle));

        // Bottom circle
        gl_Position = uProjectionMatrix * uViewMatrix * uModelMatrix * vec4(start.xyz + offset, 1.0);
		worldPos = inWorldPos[0];
		normal = normalize(offset);
        EmitVertex();

        // Top circle
        gl_Position = uProjectionMatrix * uViewMatrix * uModelMatrix * vec4(end.xyz + offset, 1.0);
		worldPos = inWorldPos[1];
		normal = normalize(offset);
        EmitVertex();
    }

    // Close the triangle strip
    EndPrimitive();
}
