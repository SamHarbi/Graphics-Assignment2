#include "Noise.h"

using namespace std;
using namespace glm;

Noise::Noise()
{

}

Noise::~Noise()
{

}

double Noise::IntegerNoise(int n)
{
	n = (n >> 13) ^ n;
	int nn = (n * (n * n * 60493 + 19990303) + 1376312589) & 0x7fffffff;
	return 1.0 - ((double)nn / 1073741824.0);
}

void Noise::calculateNoise(GLuint width, GLuint height, GLfloat perlin_freq, GLfloat perlin_scale, GLuint perlin_octaves)
{
	
}