#pragma once



#include "wrapper_glfw.h"
#include "cube_tex.h"
#include <vector>
#include <iostream>
#include <random>

/* Include GLM core and matrix extensions*/
#include <glm/glm.hpp>
#include "glm/gtc/matrix_transform.hpp"

//Include Noise Function
# include "PerlinNoise.hpp"

class ChunkBlock
{
	public: 
		ChunkBlock();
		~ChunkBlock();

		void makeChunkBlock();
		void drawChunkBlock();
		int getChunkSize();
		void buildInstanceData(glm::vec3 position);

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

		Cube instanceCube;

		int numvertices;
		int drawmode;
		bool enableTexture;
		int size; // size * size * size gives number of blocks

		const siv::PerlinNoise::seed_type seed = 78948u;
		const siv::PerlinNoise perlin{ seed };
};
