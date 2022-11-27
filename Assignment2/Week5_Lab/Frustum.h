#pragma once

#include "wrapper_glfw.h"
#include <vector>
#include <glm/glm.hpp>

class Frustum
{
public:
	Frustum();
	~Frustum();

	void init();
	void checkSphere();

	
};
