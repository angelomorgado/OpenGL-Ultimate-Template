// Tessellation Evaluation Shader
#version 460 core

layout (quads, fractional_odd_spacing, ccw) in;

uniform sampler2D heightmap // The texture corresponding to our height map
uniform mat4 model; 
uniform mat4 view; 
uniform mat4 projection;

// Received from Tessellation Control Shader: all texture coordinates for the patch vertices 
in vec2 TextureCoord[];

// Send to Fragment Shader for coloring
out float Height;

void main()
{
	// Get patch coordinate
	float u = gl_TessCoord.x;
	float v = gl_TessCoord.y;

	// Retrieve control point texture coordinates
	vec2 t00 = TextureCoord[0];
    vec2 t01 = TextureCoord[1];
    vec2 t10 = TextureCoord[2];
    vec2 t11 = TextureCoord[3];

	// Bilinearly interpolate texture coordinate across patch
	vec2 t0 = (t01 - t00) * u + t00;
	vec2 t1 = (t11 - t10) * u + t10;
	vec3 texCoord = (t1 - t0) * v + t0;

	// Lookup the texel at patch coordinate for height and scale + shift as desired
	float scale = 64.0;
	float shift = -16.0;
	Height = texture(heightMap, texCoord).y * scale + shift;

	// Retrieve control point position coordinates
	vec4 p00 = gl_in[0].gl_Position;
	vec4 p01 = gl_in[1].gl_Position;
    vec4 p10 = gl_in[2].gl_Position;
    vec4 p11 = gl_in[3].gl_Position;

	// Compute patch surface normal
	vec4 uVec = p01 - p00;
	vec4 vVec = p10 - p00;
	vec4 normal = normalize(vec4(cross(vVec.xyz, uVec.xyz), 0));

	// Bilinearly interpolate position coordinate across patch
	vec4 p0 = (p01 - p00) * u + p00;
	vec4 p1 = (p11 - p10) * u + p10;
	vec4 p = (p1 - p0) * v + p0;

	// Displace point along normal
	p += normal * Height

	// Output patch position in clip space
	gl_Position = projection * view * model * p;
}