#pragma once
#include "matrixMath.h"

mat4* getMat4(){
	mat4* temp = (mat4*) malloc(sizeof(mat4));
	temp->x[0] = 1.0f;
	temp->x[1] = 0.0f;
	temp->x[2] = 0.0f;
	temp->x[3] = 0.0f;
	temp->y[0] = 0.0f;
	temp->y[1] = 1.0f;
	temp->y[2] = 0.0f;
	temp->y[3] = 0.0f;
	temp->z[0] = 0.0f;
	temp->z[1] = 0.0f;
	temp->z[2] = 1.0f;
	temp->z[3] = 0.0f;
	temp->w[0] = 0.0f;
	temp->w[1] = 0.0f;
	temp->w[2] = 0.0f;
	temp->w[3] = 1.0f;
	return temp;
}

vec3* makeVec3(const GLfloat x, const GLfloat y, const GLfloat z){
	vec3* temp = (vec3*) malloc(sizeof(vec3));;
	temp->arr[0] = (GLfloat) x;
	temp->arr[1] = (GLfloat) y;
	temp->arr[2] = (GLfloat) z;
	return temp;
}

mat4* scaleMat4(const vec3* amount){
	mat4* in = getMat4();
	in->x[0] *= amount->arr[0];
	in->y[1] *= amount->arr[1];
	in->z[2] *= amount->arr[2];

	return in;
}

mat4* translateMat4(vec3* amount){
	mat4* in = getMat4();
	in->x[3] += amount->arr[0];
	in->y[3] += amount->arr[1];
	in->z[3] += amount->arr[2];

	return in;
}

mat4* rotateMat4(const GLfloat degrees, const vec3* direction){
	mat4* in = getMat4();
	vec3* dir = (vec3*)malloc(sizeof(vec3));
	dir = normalizeNewVec3(direction);
	GLfloat sinDeg = degToRadSin(degrees);
	GLfloat cosDeg = degToRadCos(degrees);

	//http://inside.mines.edu/fs_home/gmurray/ArbitraryAxisRotation/
	//First row
	in->x[0] = dir->arr[0] + (cosDeg * (1.0 - (dir->arr[0] * dir->arr[0])));
	in->x[1] = ((dir->arr[0] * dir->arr[1]) * (1.0 - cosDeg)) - (dir->arr[2] * sinDeg);
	in->x[2] = ((dir->arr[0] * dir->arr[2]) * (1.0 - cosDeg)) + (dir->arr[1] * sinDeg);
	//Second row
	in->y[0] = ((dir->arr[0] * dir->arr[1]) * (1.0 - cosDeg)) + (dir->arr[2] * sinDeg);
	in->y[1] = (dir->arr[1] * dir->arr[1]) + ((1.0 - (dir->arr[1] * dir->arr[1])) * cosDeg);
	in->y[2] = ((dir->arr[1] * dir->arr[2]) * (1.0 - cosDeg)) - (dir->arr[0] * sinDeg);
	//Third row
	in->z[0] = ((dir->arr[0] * dir->arr[2]) * (1.0 - cosDeg)) - (dir->arr[1] * sinDeg);
	in->z[1] = ((dir->arr[1] * dir->arr[2]) * (1.0 - cosDeg)) + (dir->arr[0] * sinDeg);
	in->z[2] = (dir->arr[2] * dir->arr[2]) + (((1.0 - (dir->arr[2] * dir->arr[2]))) * cosDeg);
	
	return in;
}

mat4* lookAtMat4(const vec3* camera, const vec3* target, const vec3* upVector){
	mat4* temp = (mat4*)malloc(sizeof(mat4));

	//vec3* f = (vec3*)malloc(sizeof(vec3));
	//vec3* u = (vec3*)malloc(sizeof(vec3));
	//vec3* s = (vec3*)malloc(sizeof(vec3));

	vec3* f = subVec3(target, camera);
	normalizeVec3(f);
	
	vec3* s = crossVec3(upVector, f);
	normalizeVec3(s);

	vec3* u = crossVec3(f, s);

	temp->x[0] = s->arr[0];
	temp->x[1] = u->arr[0];
	temp->x[2] = f->arr[0];
	temp->x[3] = 1;

	temp->y[0] = s->arr[1];
	temp->y[1] = u->arr[1];
	temp->y[2] = f->arr[1];
	temp->y[3] = 1;

	temp->z[0] = s->arr[2];
	temp->z[1] = u->arr[2];	
	temp->z[2] = f->arr[2];
	temp->z[3] = 1;

	temp->w[0] = -dotVec3(s, camera);
	temp->w[1] = -dotVec3(u, camera);
	temp->w[2] = -dotVec3(f, camera);
	temp->w[3] = 1;
	return temp;
}

mat4* perspective(const GLfloat fov, const GLfloat aspectRatio, const GLfloat nearClip, const GLfloat farClip){
	mat4* temp = (mat4*)malloc(sizeof(mat4));

	GLfloat tanHalfFov = degToRadTan(fov / 2.0f);

	temp->x[0] = 1.0f / (aspectRatio * tanHalfFov);
	temp->x[1] = 0;
	temp->x[2] = 0;
	temp->x[3] = 0;

	temp->y[0] = 0;
	temp->y[1] = 1.0f / (tanHalfFov);
	temp->y[2] = 0;
	temp->y[3] = 0;

	temp->z[0] = 0;
	temp->z[1] = 0;
	temp->z[2] = (farClip + nearClip) / (farClip - nearClip);
	temp->z[3] = 1;

	temp->w[0] = 0;
	temp->w[1] = 0;
	temp->w[2] = -(2 * farClip * nearClip) / (farClip - nearClip);
	temp->w[3] = 1;

	return temp;
}

GLfloat degToRadSin(const GLfloat degrees){
	return (GLfloat)sin(degrees * (M_PI / 180.0));
}

GLfloat degToRadCos(const GLfloat degrees){
	return (GLfloat)cos(degrees * (M_PI / 180.0));
}

GLfloat degToRadTan(const GLfloat degrees){
	return (GLfloat)tan(degrees * (M_PI / 180.0));
}

void normalizeVec3(vec3* vector){
	GLfloat magnitude = *(GLfloat*) malloc(sizeof(GLfloat));
	magnitude = (vector->arr[0] * vector->arr[0]) + (vector->arr[1] * vector->arr[1]) + (vector->arr[2] * vector->arr[2]);
	magnitude = sqrtf(magnitude);
	vector->arr[0] /= magnitude;
	vector->arr[1] /= magnitude;
	vector->arr[2] /= magnitude;
	//free(&magnitude);
}

vec3* normalizeNewVec3(const vec3* vector){
	vec3* temp = (vec3*)malloc(sizeof(vec3));
	temp->arr[0] = vector->arr[0];
	temp->arr[1] = vector->arr[1];
	temp->arr[2] = vector->arr[2];
	normalizeVec3(temp);
	return temp;
}

vec3* subVec3(const vec3* first, const vec3* second){
	vec3* temp = (vec3*)malloc(sizeof(vec3));
	temp->arr[0] = first->arr[0] - second->arr[0];
	temp->arr[1] = first->arr[1] - second->arr[1];
	temp->arr[2] = first->arr[2] - second->arr[2];
	return temp;
}

vec3* addVec3(const vec3* first, const vec3* second){
	vec3* temp = (vec3*)malloc(sizeof(vec3));
	temp->arr[0] = first->arr[0] + second->arr[0];
	temp->arr[1] = first->arr[1] + second->arr[1];
	temp->arr[2] = first->arr[2] + second->arr[2];
	return temp;
}

GLfloat dotVec3(const vec3* first, const vec3* second){
	return (first->arr[0] * second->arr[0]) + (first->arr[1] * second->arr[1]) + (first->arr[2] * second->arr[2]);
}

vec3* crossVec3(const vec3* first, const vec3* second){
	vec3* temp = (vec3*)malloc(sizeof(vec3));
	temp->arr[0] = (first->arr[1] * second->arr[2]) - (first->arr[2] * second->arr[1]);
	temp->arr[1] = (first->arr[2] * second->arr[0]) - (first->arr[0] * second->arr[2]);
	temp->arr[2] = (first->arr[0] * second->arr[1]) - (first->arr[1] * second->arr[0]);
	return temp;
}

void printMat4(const mat4* matrix){
	printf("%f %f %f %f\n", matrix->x[0], matrix->x[1], matrix->x[2], matrix->x[3]);
	printf("%f %f %f %f\n", matrix->y[0], matrix->y[1], matrix->y[2], matrix->y[3]);
	printf("%f %f %f %f\n", matrix->z[0], matrix->z[1], matrix->z[2], matrix->z[3]);
	printf("%f %f %f %f\n", matrix->w[0], matrix->w[1], matrix->w[2], matrix->w[3]);
}

void printVec3(const vec3* vector){
	printf("%f %f %f\n", vector->arr[0], vector->arr[1], vector->arr[2]);
}
