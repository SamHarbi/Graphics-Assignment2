#pragma once

#include "wrapper_glfw.h"
#include <vector>
#include <glm/glm.hpp>
#include <glm/gtc/noise.hpp>

class Noise
{
public:
	Noise();
	~Noise();

	double IntegerNoise(int n);
	void calculateNoise(GLuint width, GLuint height, GLfloat perlin_freq, GLfloat perlin_scale, GLuint perlin_octaves);

	float generatedValues[];

};
