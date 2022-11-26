
#include "ChunkBlock.h"

using namespace std;

ChunkBlock::ChunkBlock()
{
	size = 16;

	attribute_v_coord = 0;
	attribute_v_colours = 1;
	attribute_v_normal = 2;
	attribute_v_texcoord = 3;
	attribute_v_instance = 4;

	numvertices = 12;
}

ChunkBlock::~ChunkBlock()
{

}

void ChunkBlock::makeChunkBlock()
{
	
	GLfloat vertexPositions[] =
	{
		// Face 0;
		-0.25f, 0.25f, -0.25f,
		-0.25f, -0.25f, -0.25f,
		0.25f, -0.25f, -0.25f,

		0.25f, -0.25f, -0.25f,
		0.25f, 0.25f, -0.25f,
		-0.25f, 0.25f, -0.25f,

		// Face 1
		0.25f, -0.25f, -0.25f,
		0.25f, -0.25f, 0.25f,
		0.25f, 0.25f, -0.25f,

		0.25f, -0.25f, 0.25f,
		0.25f, 0.25f, 0.25f,
		0.25f, 0.25f, -0.25f,

		// Face 2
		0.25f, -0.25f, 0.25f,
		-0.25f, -0.25f, 0.25f,
		0.25f, 0.25f, 0.25f,

		-0.25f, -0.25f, 0.25f,
		-0.25f, 0.25f, 0.25f,
		0.25f, 0.25f, 0.25f,

		// Face 3
		-0.25f, -0.25f, 0.25f,
		-0.25f, -0.25f, -0.25f,
		-0.25f, 0.25f, 0.25f,

		-0.25f, -0.25f, -0.25f,
		-0.25f, 0.25f, -0.25f,
		-0.25f, 0.25f, 0.25f,

		// Face 4
		-0.25f, -0.25f, 0.25f,
		0.25f, -0.25f, 0.25f,
		0.25f, -0.25f, -0.25f,

		0.25f, -0.25f, -0.25f,
		-0.25f, -0.25f, -0.25f,
		-0.25f, -0.25f, 0.25f,

		// Face 5
		-0.25f, 0.25f, -0.25f,
		0.25f, 0.25f, -0.25f,
		0.25f, 0.25f, 0.25f,

		0.25f, 0.25f, 0.25f,
		-0.25f, 0.25f, 0.25f,
		-0.25f, 0.25f, -0.25f,
	};

	/* Manually specified colours for our cube */
	float vertexColours[] = {
		0.0f, 0.0f, 1.0f, 1.0f,
		0.0f, 0.0f, 1.0f, 1.0f,
		0.0f, 0.0f, 1.0f, 1.0f,
		0.0f, 0.0f, 1.0f, 1.0f,
		0.0f, 0.0f, 1.0f, 1.0f,
		0.0f, 0.0f, 1.0f, 1.0f,

		0.0f, 1.0f, 0.0f, 1.0f,
		0.0f, 1.0f, 0.0f, 1.0f,
		0.0f, 1.0f, 0.0f, 1.0f,
		0.0f, 1.0f, 0.0f, 1.0f,
		0.0f, 1.0f, 0.0f, 1.0f,
		0.0f, 1.0f, 0.0f, 1.0f,

		1.0f, 1.0f, 0.0f, 1.0f,
		1.0f, 1.0f, 0.0f, 1.0f,
		1.0f, 1.0f, 0.0f, 1.0f,
		1.0f, 1.0f, 0.0f, 1.0f,
		1.0f, 1.0f, 0.0f, 1.0f,
		1.0f, 1.0f, 0.0f, 1.0f,

		1.0f, 0.0f, 0.0f, 1.0f,
		1.0f, 0.0f, 0.0f, 1.0f,
		1.0f, 0.0f, 0.0f, 1.0f,
		1.0f, 0.0f, 0.0f, 1.0f,
		1.0f, 0.0f, 0.0f, 1.0f,
		1.0f, 0.0f, 0.0f, 1.0f,

		1.0f, 0.0f, 1.0f, 1.0f,
		1.0f, 0.0f, 1.0f, 1.0f,
		1.0f, 0.0f, 1.0f, 1.0f,
		1.0f, 0.0f, 1.0f, 1.0f,
		1.0f, 0.0f, 1.0f, 1.0f,
		1.0f, 0.0f, 1.0f, 1.0f,

		0.0f, 1.0f, 1.0f, 1.0f,
		0.0f, 1.0f, 1.0f, 1.0f,
		0.0f, 1.0f, 1.0f, 1.0f,
		0.0f, 1.0f, 1.0f, 1.0f,
		0.0f, 1.0f, 1.0f, 1.0f,
		0.0f, 1.0f, 1.0f, 1.0f,
	};

	/* Manually specified normals for our cube */
	GLfloat normals[] =
	{
		0, 0, -1.f, 0, 0, -1.f, 0, 0, -1.f,
		0, 0, -1.f, 0, 0, -1.f, 0, 0, -1.f,
		1.f, 0, 0, 1.f, 0, 0, 1.f, 0, 0,
		1.f, 0, 0, 1.f, 0, 0, 1.f, 0, 0,
		0, 0, 1.f, 0, 0, 1.f, 0, 0, 1.f,
		0, 0, 1.f, 0, 0, 1.f, 0, 0, 1.f,
		-1.f, 0, 0, -1.f, 0, 0, -1.f, 0, 0,
		-1.f, 0, 0, -1.f, 0, 0, -1.f, 0, 0,
		0, -1.f, 0, 0, -1.f, 0, 0, -1.f, 0,
		0, -1.f, 0, 0, -1.f, 0, 0, -1.f, 0,
		0, 1.f, 0, 0, 1.f, 0, 0, 1.f, 0,
		0, 1.f, 0, 0, 1.f, 0, 0, 1.f, 0,
	};

	GLfloat texcoords[] =
	{
		// Face 0
		0, 1.f, 0, 0, 1.f, 0,
		1.f, 0, 1.f, 1.f, 0, 1.f,

		// Face 1
		1.0, 0.f, 0.f, 0.f, 1.f, 1.f,
		0.f, 0.f, 0.f, 1.f, 1.f, 1.f,

		// Face 2
		1.f, 0.f, 0.f, 0.f, 1.f, 1.f,
		0.f, 0.f, 0.f, 1.f, 1.f, 1.f,

		// Face 3
		1.f, 0.f, 0.f, 0.f, 1.f, 1.f,
		0.f, 0.f, 0.f, 1.f, 1.f, 1.f,

		// Face 4
		0.f, 0.f, 1.f, 0.f, 1.f, 1.f,
		1.f, 1.f, 0.f, 1.f, 0.f, 0.f,

		// Face 5
		0.f, 1.f, 1.f, 1.f, 1.f, 0.f,
		1.f, 0.f, 0.f, 0.f, 0.f, 1.f
	};
	
	
	GLint blockCount = size * size * size;
	std::vector<glm::vec3> translations;
	
	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{
			for (int k = 0; k < size; k++)
			{
				translations.push_back(glm::vec3(i+3, j, k));
			}
		}
	}

	/* Create the vertex buffer for the cube */
	glGenBuffers(1, &positionBufferObject);
	glBindBuffer(GL_ARRAY_BUFFER, positionBufferObject);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertexPositions), vertexPositions, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	/* Create the colours buffer for the cube */
	glGenBuffers(1, &colourObject);
	glBindBuffer(GL_ARRAY_BUFFER, colourObject);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertexColours), vertexColours, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	/* Create the normals  buffer for the cube */
	glGenBuffers(1, &normalsBufferObject);
	glBindBuffer(GL_ARRAY_BUFFER, normalsBufferObject);
	glBufferData(GL_ARRAY_BUFFER, 36 * sizeof(glm::vec3), normals, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glGenBuffers(1, &texCoordsObject);
	glBindBuffer(GL_ARRAY_BUFFER, texCoordsObject);
	glBufferData(GL_ARRAY_BUFFER, sizeof(texcoords), texcoords, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glGenBuffers(1, &instanceData);
	glBindBuffer(GL_ARRAY_BUFFER, instanceData);
	glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3) * blockCount, &translations[0], GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

}

void ChunkBlock::drawChunkBlock()
{
	/* Bind cube colours. Note that this is in attribute index 1 */
	glBindBuffer(GL_ARRAY_BUFFER, colourObject);
	glEnableVertexAttribArray(attribute_v_colours);
	glVertexAttribPointer(attribute_v_colours, 4, GL_FLOAT, GL_FALSE, 0, 0);

	/* Bind cube normals. Note that this is in attribute index 2 */
	glEnableVertexAttribArray(attribute_v_normal);
	glBindBuffer(GL_ARRAY_BUFFER, normalsBufferObject);
	glVertexAttribPointer(attribute_v_normal, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);

	/* Bind cube texture coords. Note that this is in attribute index 3 */
	glEnableVertexAttribArray(attribute_v_texcoord);
	glBindBuffer(GL_ARRAY_BUFFER, texCoordsObject);
	glVertexAttribPointer(attribute_v_texcoord, 2, GL_FLOAT, GL_FALSE, 0, (void*)0);

	glEnableVertexAttribArray(4);
	glBindBuffer(GL_ARRAY_BUFFER, instanceData);
	glVertexAttribPointer(4, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glVertexAttribDivisor(4, 1);
	
	glFrontFace(GL_CW);
	
	glPointSize(8.f);
	glBindVertexArray(positionBufferObject);
	glDrawArraysInstanced(GL_TRIANGLES, 0, 36, (size * size * size));
}

	