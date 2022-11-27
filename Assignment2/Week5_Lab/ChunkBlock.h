#pragma once

#include "wrapper_glfw.h"
#include <vector>
#include <iostream>

/* Include GLM core and matrix extensions*/
#include <glm/glm.hpp>
#include "glm/gtc/matrix_transform.hpp"

class ChunkBlock
{
	public: 
		ChunkBlock();
		~ChunkBlock();

		void makeChunkBlock(glm::vec3 position);
		void drawChunkBlock();
		int getChunkSize();

		// Define vertex buffer object names (e.g as globals)
		GLuint positionBufferObject;
		GLuint colourObject;
		GLuint normalsBufferObject;
		GLuint texCoordsObject;
		GLuint instanceData;

		GLuint attribute_v_coord;
		GLuint attribute_v_normal;
		GLuint attribute_v_colours;
		GLuint attribute_v_texcoord;
		GLuint attribute_v_instance;

		int numvertices;
		int drawmode;
		bool enableTexture;
		int size; // size * size * size gives number of blocks
};
