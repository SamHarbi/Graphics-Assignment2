/* quad.h
 Example class to create a generic quad object
 Includes texture coordinates
 Iain Martin  November 2021
*/

#include "quad_tex.h"

/* I don't like using namespaces in header files but have less issues with them in
seperate cpp files */
using namespace std;

/* Define the vertex attributes for vertex positions, normals, colour and texcoords.
Make these match your application and vertex shader
*/
Quad::Quad(bool useTexture)
{
	attribute_v_coord = 0;
	attribute_v_colours = 1;
	attribute_v_normal = 2;
	attribute_v_texcoord = 3;

	numvertices = 12;
	this->drawmode = drawmode;

	// Turn texture off if you're not handling texture coordinates in your shaders
	enableTexture = useTexture;
}


Quad::~Quad()
{
}


/* Make a quad from hard-coded vertex positions and normals  */
void Quad::makeQuad()
{
	/* Define vertices for a quad in 12 triangles */
	GLfloat vertexPositions[] =
	{
		-0.25f, 0.25f, -0.25f,
		-0.25f, -0.25f, -0.25f,
		0.25f, -0.25f, -0.25f,

		0.25f, -0.25f, -0.25f,
		0.25f, 0.25f, -0.25f,
		-0.25f, 0.25f, -0.25f,	
	};

	/* Manually specified colours for our vertices */
	float vertexColours[] = {
		0.0f, 0.0f, 1.0f, 1.0f,
		0.0f, 0.0f, 1.0f, 1.0f,
		0.0f, 0.0f, 1.0f, 1.0f,
		0.0f, 0.0f, 1.0f, 1.0f,
		0.0f, 0.0f, 1.0f, 1.0f,
		0.0f, 0.0f, 1.0f, 1.0f,	
	};

	/* Manually specified normals for our quad */
	GLfloat normals[] =
	{
		0, 0, 1.f, 0, 0, 1.f, 0, 0, 1.f,
		0, 0, 1.f, 0, 0, 1.f, 0, 0, 1.f,
	};


	GLfloat texcoords[] =
	{
		0, 1.f, 0, 0, 1.f, 0,
		1.f, 0, 1.f, 1.f, 0, 1.f,
	};

	/* Create the vertex buffer for the quad */
	glGenBuffers(1, &positionBufferObject);
	glBindBuffer(GL_ARRAY_BUFFER, positionBufferObject);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertexPositions), vertexPositions, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	/* Create the colours buffer for the quad */
	glGenBuffers(1, &colourObject);
	glBindBuffer(GL_ARRAY_BUFFER, colourObject);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertexColours), vertexColours, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	/* Create the normals  buffer for the quad */
	glGenBuffers(1, &normalsBufferObject);
	glBindBuffer(GL_ARRAY_BUFFER, normalsBufferObject);
	glBufferData(GL_ARRAY_BUFFER, 36 * sizeof(glm::vec3), normals, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	/* Create the texture coordinate  buffer for the quad */
	if (enableTexture)
	{
		glGenBuffers(1, &texCoordsObject);
		glBindBuffer(GL_ARRAY_BUFFER, texCoordsObject);
		glBufferData(GL_ARRAY_BUFFER, sizeof(texcoords), texcoords, GL_STATIC_DRAW);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}
}


/* Draw the quad by binding the VBOs and drawing triangles */
void Quad::drawQuad(int drawmode)
{
	/* Bind quad vertices. Note that this is in attribute index 0 */
	glBindBuffer(GL_ARRAY_BUFFER, positionBufferObject);
	glEnableVertexAttribArray(attribute_v_coord);
	glVertexAttribPointer(attribute_v_coord, 3, GL_FLOAT, GL_FALSE, 0, 0);

	/* Bind quad colours. Note that this is in attribute index 1 */
	glBindBuffer(GL_ARRAY_BUFFER, colourObject);
	glEnableVertexAttribArray(attribute_v_colours);
	glVertexAttribPointer(attribute_v_colours, 4, GL_FLOAT, GL_FALSE, 0, 0);

	/* Bind quad normals. Note that this is in attribute index 2 */
	glEnableVertexAttribArray(attribute_v_normal);
	glBindBuffer(GL_ARRAY_BUFFER, normalsBufferObject);
	glVertexAttribPointer(attribute_v_normal, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);

	if (enableTexture)
	{
		/* Bind quad texture coords. Note that this is in attribute index 3 */
		glEnableVertexAttribArray(attribute_v_texcoord);
		glBindBuffer(GL_ARRAY_BUFFER, texCoordsObject);
		glVertexAttribPointer(attribute_v_texcoord, 2, GL_FLOAT, GL_FALSE, 0, (void*)0);
	}

	// Define triangle winding as clockwise
	// It would be better to make all objects have counter-clockwise winding
	glFrontFace(GL_CW);

	// Enable this line to show model in wireframe
	if (drawmode == 1)
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	else
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	if (drawmode == 2)
	{
		// Draw the vertices as GL_POINTS
		glPointSize(3.f);  // Set the point size when drawing vertices
		glDrawArrays(GL_POINTS, 0, 36);
	}
	else
	{
		// Draw the quad in triangles
		glDrawArrays(GL_TRIANGLES, 0, 6);
	}
}