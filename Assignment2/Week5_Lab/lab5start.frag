// Minimal fragment shader
// for AC41001 Lab 5
// You should modify this fragment shader to apply texture
// appropriately

#version 400

in vec4 fcolour;
in vec2 ftexcoord;
uniform sampler2D tex1;
out vec4 outputColor;
void main()
{
	vec4 texcolour = texture(tex1, ftexcoord);
	outputColor = texcolour;
}