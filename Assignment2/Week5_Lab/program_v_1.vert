// Simple Vertex Skybox Shader
// Sameer Al Harbi 2022

#version 420

// These are the vertex attributes
layout(location = 0) in vec3 position;
layout(location = 1) in vec4 colour;
layout(location = 2) in vec3 normal;
layout(location = 3) in vec3 texcoord;
layout(location = 4) in vec3 offset;

// Uniform variables are passed in from the application
uniform mat4 model, view, projection;

// Output the  texture coordinate - just pass it through
out vec3 ftexcoord;


void main()
{
	// Define the vertex position
	gl_Position = projection * view * model * vec4(position.x+offset.x/2, position.y+offset.y/2, position.z+offset.z/2, 1.0);

	// Pas through the texture coordinate
	ftexcoord = position;
}

