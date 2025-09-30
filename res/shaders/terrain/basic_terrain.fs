#version 450 core

uniform mat4 uProjectionMatrix;
uniform mat4 uModelViewMatrix;
uniform vec3 uColor;

// viewspace data
in VertexData {
    vec3 position;
    vec3 normal;
    vec2 textureCoord;
} f_in;

// framebuffer output
out vec4 fb_color;

uniform sampler2D heightMap;

uniform sampler2D water_texture;
uniform sampler2D sand_texture;
uniform sampler2D grass_texture;
uniform sampler2D rock_texture;
uniform sampler2D snow_texture;
uniform bool useTexturing; // whether or not to use texturing or just display the heightmap

vec3 getTerrainColor(vec2 uv, float height) {
	// Define height thresholds
	const float water_level = 0.4;
	const float sand_level = 0.45;
	const float grass_level = 0.5;
	const float rock_level = 0.65;
   
	// Define blend ranges for smooth transitions
	const float blend_range = 0.1;
   
	// Sample all textures
	vec3 water_color = texture(water_texture, uv).rgb;
	vec3 sand_color = texture(sand_texture, uv).rgb;
	vec3 grass_color = texture(grass_texture, uv).rgb;
	vec3 rock_color = texture(rock_texture, uv).rgb;
	vec3 snow_color = texture(snow_texture, uv).rgb;
   
	vec3 final_color;
   
	// Water to sand transition
	if (height < sand_level) {
		float t = smoothstep(water_level - blend_range, water_level + blend_range, height);
		final_color = mix(water_color, sand_color, t);
	}
	// Sand to grass transition
	else if (height < grass_level) {
		float t = smoothstep(sand_level - blend_range, sand_level + blend_range, height);
		final_color = mix(sand_color, grass_color, t);
	}
	// Grass to rock transition
	else if (height < rock_level) {
		float t = smoothstep(grass_level - blend_range, grass_level + blend_range, height);
		final_color = mix(grass_color, rock_color, t);
	}
	// Rock to snow transition
	else {
		float t = smoothstep(rock_level - blend_range, rock_level + blend_range, height);
		final_color = mix(rock_color, snow_color, t);
	}
   
	return final_color;
}

void main() {
    float height = texture(heightMap, f_in.textureCoord).r;
	if (!useTexturing) { // Just use a simple faked lighting with the heightmap
		vec3 col = vec3(height, height, height);
	
		// calculate lighting (hack)
		vec3 eye = normalize(-f_in.position);
		float light = abs(dot(normalize(f_in.normal), eye));
		vec3 color = mix(col / 4, col, light);

		// output to the frambuffer
		fb_color = vec4(color, 1);
		return;
	}
    
    // Get base terrain color
    vec3 col = getTerrainColor(f_in.textureCoord * 5.0f, height).xyz;
	col = mix(vec3(height, height, height), col, 0.8);
    
    // Calculate lighting
    vec3 eye = normalize(vec3(1.5, 3.0, 2.0));
    vec3 normal = normalize(f_in.normal);
    
    // Diffuse lighting
    float diffuse = max(dot(normal, eye), 0.0);
    
    // Ambient + diffuse
    float ambient = 0.8;
    float light = ambient + diffuse;
    
    // Apply lighting
    vec3 color = col * light;
    
    // Output to framebuffer
    fb_color = vec4(color, 1.0);
}
