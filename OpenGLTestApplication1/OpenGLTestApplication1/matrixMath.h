//Includes
#include <math.h>
#include "GLFW.h"
#include <stdio.h>
#include <stdlib.h>

#define M_PI 3.14159265358979323846

typedef struct mat4{
	GLfloat x[4];
	GLfloat y[4];
	GLfloat z[4];
	GLfloat w[4];
}mat4;

typedef struct vec3{
	GLfloat arr[3];
}vec3;


mat4* getMat4();

vec3* makeVec3(const GLfloat x, const GLfloat y, const GLfloat z);

mat4* scaleMat4(const vec3* amount);

mat4* translateMat4(vec3* amount);

mat4* rotateMat4(const GLfloat degrees, const vec3* direction);

mat4* multMat4(const mat4* a, const mat4* b);

mat4* lookAtMat4(const vec3* camera, const vec3* target, const vec3* upVector);

mat4* perspective(const GLfloat fov, const GLfloat aspectRatio, const GLfloat nearClip, const GLfloat farClip);

GLfloat degToRadSin(const GLfloat degrees);

GLfloat degToRadCos(const GLfloat degrees);

GLfloat degToRadTan(const GLfloat degrees);

void normalizeVec3(vec3* vector);

vec3* normalizeNewVec3(const vec3* vector);

vec3* subVec3(const vec3* first, const vec3* second);

vec3* addVec3(const vec3* first, const vec3* second);

GLfloat dotVec3(const vec3* first, const vec3* second);

vec3* crossVec3(const vec3* first, const vec3* second);

void printMat4(const mat4* matrix);

void printVec3(const vec3* matrix);