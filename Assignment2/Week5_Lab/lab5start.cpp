/*
 Lab5 Solution (Texturing)
 Applies different textures to  cube and a sphere objectss
 Includes rotation, scaling, translation, view and perspective transformations,
 Objects have normals,colours and texture coordinates defined
 for all vertices.
 Iain Martin November 2022
*/

/* Link to static libraries, could define these as linker inputs in the project settings instead
if you prefer */
#ifdef _DEBUG
#pragma comment(lib, "glfw3D.lib")
#else
#pragma comment(lib, "glfw3.lib")
#endif
#pragma comment(lib, "opengl32.lib")


/* Include the header to the GLFW wrapper class which
   also includes the OpenGL extension initialisation*/
#include "wrapper_glfw.h"
#include <iostream>

   /* Include GLM core and matrix extensions*/
#include <glm/glm.hpp>
#include "glm/gtc/matrix_transform.hpp"
#include <glm/gtc/type_ptr.hpp>

/* Include the image loader */
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

/* Include the cube and sphere objects with texture coordinates */
#include "sphere_tex.h"
#include "cube_tex.h"
#include "ChunkBlock.h"
#include <stack>


GLuint program;		/* Identifier for the shader prgoram */
GLuint vao;			/* Vertex array (Containor) object. This is the index of the VAO that will be the container for
					   our buffer objects */

GLuint colourmode;	/* Index of a uniform to switch the colour mode in the vertex shader
					  I've included this to show you how to pass in an unsigned integer into
					  your vertex shader. */

					  /* Position and view globals */
GLfloat angle_x, angle_inc_x, x, scaler, z, y;
GLfloat angle_y, angle_inc_y, angle_z, angle_inc_z;
GLuint drawmode;			// Defines drawing mode of sphere as points, lines or filled polygons
GLuint numlats, numlongs;	//Define the resolution of the sphere object

//Camera Controls
float horizontalCam;
float verticalCam;
GLfloat cam_x;
GLfloat cam_y;

/* Uniforms*/
GLuint modelID, viewID, projectionID;
GLuint colourmodeID;

GLfloat aspect_ratio;		/* Aspect ratio of the window defined in the reshape callback*/
GLuint numspherevertices;

GLuint textureID1, textureID2;

Sphere sphere;
Cube cube(true);
ChunkBlock chunkblock;

using namespace std;
using namespace glm;


bool load_texture(char* filename, GLuint& texID, bool bGenMipmaps);

bool load_texture(const char* filename, GLuint& texID, bool bGenMipmaps)
{
	glGenTextures(1, &texID);
	// local image parameters
	int width, height, nrChannels;

	/* load an image file using stb_image */
	unsigned char* data = stbi_load(filename, &width, &height, &nrChannels, 0);

	// check for an error during the load process
	if (data)
	{
		// Note: this is not a full check of all pixel format types, just the most common two!
		int pixel_format = 0;
		if (nrChannels == 3)
			pixel_format = GL_RGB;
		else
			pixel_format = GL_RGBA;

		// Bind the texture ID before the call to create the texture.
			// texID[i] will now be the identifier for this specific texture
		glBindTexture(GL_TEXTURE_2D, texID);

		// Create the texture, passing in the pointer to the loaded image pixel data
		glTexImage2D(GL_TEXTURE_2D, 0, pixel_format, width, height, 0, pixel_format, GL_UNSIGNED_BYTE, data);

		// Generate Mip Maps
		if (bGenMipmaps)
		{
			glGenerateMipmap(GL_TEXTURE_2D);
		}
		else
		{
			// If mipmaps are not used then ensure that the min filter is defined
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		}
	}
	else
	{
		printf("stb_image  loading error: filename=%s", filename);
		return false;
	}
	stbi_image_free(data);
	return true;
}

/*
This function is called before entering the main rendering loop.
Use it for all your initialisation stuff
*/
void init(GLWrapper* glw)
{
	/* Set the object transformation controls to their initial values */
	x = 0.05f;
	y = 0;
	z = 0;
	angle_x = angle_y = angle_z = 0;
	angle_inc_x = angle_inc_y = angle_inc_z = 0;
	scaler = 1.f;
	aspect_ratio = 1.3333f;
	colourmode = 0;
	numlats = 100;		// Number of latitudes in our sphere
	numlongs = 100;		// Number of longitudes in our sphere

	horizontalCam = 0.0f;
	verticalCam = 0.0f;

	cam_x = 0;
	cam_y = 0;

	// Generate index (name) for one vertex array object
	glGenVertexArrays(1, &vao);

	// Create the vertex array object and make it current
	glBindVertexArray(vao);

	/* create the sphere and cube objects */
	sphere.makeSphere(numlats, numlongs);
	cube.makeCube();
	chunkblock.makeChunkBlock();

	/* Load and build the vertex and fragment shaders */
	try
	{
		program = glw->LoadShader("lab5start.vert", "lab5start.frag");
	}
	catch (exception& e)
	{
		cout << "Caught exception: " << e.what() << endl;
		cin.ignore();
		exit(0);
	}

	/* Define uniforms to send to vertex shader */
	modelID = glGetUniformLocation(program, "model");
	colourmodeID = glGetUniformLocation(program, "colourmode");
	viewID = glGetUniformLocation(program, "view");
	projectionID = glGetUniformLocation(program, "projection");

	// Call our texture loader function to load two textures.#
	// Note that our texture loader generates the texID and is passed as a var parameter
	// The third parameter is a boolean that with generater mipmaps if true

	/* load an image file using stb_image */
	const char* filename1 = "ground1.jpg";
	const char* filename2 = "jupiter.png";

	// This will flip the image so that the texture coordinates defined in
	// the sphere, match the image orientation as loaded by stb_image
	stbi_set_flip_vertically_on_load(true);
	if (!load_texture(filename1, textureID1, true))
	{
		cout << "Fatal error loading texture: " << filename1 << endl;
		exit(0);
	}

	if (!load_texture(filename2, textureID2, false))
	{
		cout << "Fatal error loading texture: " << filename2 << endl;
		exit(0);
	}

	// This is the location of the texture object (TEXTURE0), i.e. tex1 will be the name
	// of the sampler in the fragment shader
	int loc = glGetUniformLocation(program, "tex1");
	if (loc >= 0) glUniform1i(loc, 0);

	// SET Texture MAG_FILTER to linear which will blur the texture if we
	// zoom too close in
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
}

/* Called to update the display. Note that this function is called in the event loop in the wrapper
   class because we registered display as a callback function */
void display()
{
	glfwSetTime(0);
	
	/* Define the background colour */
	glClearColor(102.0f/255.0f, 153.0f/255.0f, 255.0f/255.0f, 1.0f);

	/* Clear the colour and frame buffers */
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	/* Enable depth test  */
	glEnable(GL_DEPTH_TEST);

	/* Make the compiled shader program current */
	glUseProgram(program);

	// Define our model transformation in a stack and 
	// push the identity matrix onto the stack
	stack<mat4> model;
	model.push(mat4(1.0f));

	// Projection matrix : 45� Field of View, 4:3 ratio, display range : 0.1 unit <-> 100 units
	mat4 projection = perspective(radians(90.0f), aspect_ratio, 0.1f, 100.0f);

	vec3 camPos = vec3(cam_x, cam_y, 1);

	//Camera Direction
	vec3 camDirection = vec3(cos(verticalCam) * sin(horizontalCam), sin(verticalCam), cos(verticalCam) * cos(horizontalCam));

	//Used to calculate the correct Head up position
	vec3 right = vec3(
		sin(horizontalCam - 3.14f / 2.0f),
		0,
		cos(horizontalCam - 3.14f / 2.0f)
	);

	vec3 up = glm::cross(right, camDirection);

	// Camera matrix
	mat4 view = lookAt(
		camPos,
		camPos + camDirection, 
		up
	);

	// Send our uniforms variables to the currently bound shader,
	glUniform1ui(colourmodeID, colourmode);
	glUniformMatrix4fv(viewID, 1, GL_FALSE, &view[0][0]);
	glUniformMatrix4fv(projectionID, 1, GL_FALSE, &projection[0][0]);

	// Draw our cube
	// Mipmap defined for our cube texture so enable it with the MIN_FILTER 
	glBindTexture(GL_TEXTURE_2D, textureID1);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);

	model.top() = scale(model.top(), vec3(2.0f, 2.0f, 2.0f));//scale equally in all axis

	model.push(model.top());
	{
		model.top() = translate(model.top(), vec3(x, y, z));
		glUniformMatrix4fv(modelID, 1, GL_FALSE, &(model.top()[0][0]));
		cube.drawCube(drawmode);
		chunkblock.drawChunkBlock();
	}
	model.pop();

	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);

	// Disable everything
	glBindTexture(GL_TEXTURE_2D, 0);
	glDisableVertexAttribArray(0);
	glUseProgram(0);

	/* Modify our animation variables */
	angle_x += angle_inc_x;
	angle_y += angle_inc_y;
	angle_z += angle_inc_z;
}

/*
	Function to calculate camera angles based on mouse input
	Uses http://www.opengl-tutorial.org/beginners-tutorials/tutorial-6-keyboard-and-mouse/ as a guide
*/
static void mouseCallback(GLFWwindow* window, double xpos, double ypos)
{
	int height, width;
	int mouseSpeed = 1.0f;
	glfwGetWindowSize(window, &width, &height);

	double deltaTime = glfwGetTime();
	glfwSetTime(0);

	horizontalCam += (mouseSpeed * deltaTime * float(width / 2 - xpos));
	verticalCam += (mouseSpeed * deltaTime * float(height / 2 - ypos));

	glfwSetCursorPos(window, width/2, height/2);
	
}

/* Called whenever the window is resized. The new window size is given, in pixels. */
static void reshape(GLFWwindow* window, int w, int h)
{
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);
	aspect_ratio = ((float)w / 640.f * 4.f) / ((float)h / 480.f * 3.f);
}

/* change view angle, exit upon ESC */
static void keyCallback(GLFWwindow* window, int key, int s, int action, int mods)
{
	/* Enable this call if you want to disable key responses to a held down key*/
	//if (action != GLFW_PRESS) return;

	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);

	if (key == 'Q') angle_inc_x -= 0.05f;
	if (key == 'W') angle_inc_x += 0.05f;
	if (key == 'E') angle_inc_y -= 0.05f;
	if (key == 'R') angle_inc_y += 0.05f;
	if (key == 'T') angle_inc_z -= 0.05f;
	if (key == 'Y') angle_inc_z += 0.05f;
	if (key == 'A') scaler -= 0.02f;
	if (key == 'S') scaler += 0.02f;
	if (key == 'Z') x -= 0.05f;
	if (key == 'X') x += 0.05f;
	if (key == 'C') y -= 0.05f;
	if (key == 'V') y += 0.05f;
	if (key == 'B') z -= 0.05f;
	if (key == 'N') z += 0.05f;

	if (key == 'I') cam_x += 0.1f;
	if (key == 'K') cam_x -= 0.1f;
	if (key == 'J') cam_y += 0.1f;
	if (key == 'L') cam_y -= 0.1f;

	if (key == 'M' && action != GLFW_PRESS)
	{
		colourmode = !colourmode;
		cout << "colourmode=" << colourmode << endl;
	}

	/* Cycle between drawing vertices, mesh and filled polygons */
	if (key == 'N' && action != GLFW_PRESS)
	{
		drawmode++;
		if (drawmode > 2) drawmode = 0;
	}

}

/* Entry point of program */
int main(int argc, char* argv[])
{
	
	GLWrapper* glw = new GLWrapper(1024, 768, "Lab5 Solution: Textured cube and sphere");

	// glad: load all OpenGL function pointers
	// ---------------------------------------
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		cout << "Failed to initialize GLAD. Exiting." << endl;
		return -1;
	}

	glw->setMouseCallback(mouseCallback);
	glw->setRenderer(display);
	glw->setKeyCallback(keyCallback);
	glw->setReshapeCallback(reshape);

	init(glw);

	glw->eventLoop();


	delete(glw);
	return 0;
}


