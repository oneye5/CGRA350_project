#version 440
in vec2 texCoord;
out vec4 FragColor;

uniform sampler2D gBufferPosition;
uniform sampler2D gBufferNormal;
uniform sampler2D gBufferAlbedo;
uniform sampler2D gBufferEmissive;

uniform sampler3D voxelTex0; // Pos.xyz + Metallic
uniform sampler3D voxelTex1; // Normal.xyz + Smoothness
uniform sampler3D voxelTex2; // Albedo.rgb + EmissiveFactor

uniform int uDebugIndex;
uniform int uVoxelRes;
uniform float uVoxelWorldSize;

int debugPass(vec3 worldPos, float metallic, vec3 worldNormal, float smoothness,
    vec3 albedo, float emissiveFactor, vec3 emissiveRgb, float spare) {
    if (uDebugIndex == 1)      FragColor = vec4(worldPos, 1.0);
    else if (uDebugIndex == 2) FragColor = vec4(metallic);
    else if (uDebugIndex == 3) FragColor = vec4(worldNormal, 1.0);
    else if (uDebugIndex == 4) FragColor = vec4(smoothness);
    else if (uDebugIndex == 5) FragColor = vec4(albedo, 1.0);
    else if (uDebugIndex == 6) FragColor = vec4(emissiveFactor);
    else if (uDebugIndex == 7) FragColor = vec4(emissiveRgb, 1.0);
    else if (uDebugIndex == 8) FragColor = vec4(spare);
    else return 0;
    return 1;
}

// Convert world position to voxel UVW [0,1]
vec3 worldToVoxel(vec3 pos) {
    return (pos / uVoxelWorldSize) + 0.5;
}

void main() {
    // unpack channels
    vec3 worldPos = texture(gBufferPosition, texCoord).xyz;
    float metallic = texture(gBufferPosition, texCoord).w;
    vec3 worldNormal = texture(gBufferNormal, texCoord).xyz;
    float smoothness = texture(gBufferNormal, texCoord).w;
    vec3 albedo = texture(gBufferAlbedo, texCoord).xyz;
    float emissiveFactor = texture(gBufferAlbedo, texCoord).w;
    vec3 emissiveRgb = texture(gBufferEmissive, texCoord).xyz;
    float spare = texture(gBufferEmissive, texCoord).w;

    if (debugPass(worldPos, metallic, worldNormal, smoothness, albedo, emissiveFactor, emissiveRgb, spare) == 1)
        return;


    vec3 outColor = vec3(1);
    outColor = texture(voxelTex2, worldToVoxel(worldPos)).xyz;
    if (outColor != vec3(0))
    {
        FragColor = vec4(outColor, 1.0);
    }
    else
    {
        FragColor = vec4(1, 1, 1, 1);
    }
}