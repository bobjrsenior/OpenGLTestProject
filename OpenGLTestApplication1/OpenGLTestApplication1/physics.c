/*
* @file physics.c
* @brief Physics/Collision Testing for OpenGL
*/
#pragma once
#include "physics.h"

struct square{
	GLfloat x1, x2, y1, y2, rotation;
};

bool isColliding(const struct square *first, const struct square *second){
	float diffX = (0.5f * (first->x1 + first->x2)) - (0.5f * (second->x1 + second->x2));
	float diffY = (0.5f * (first->y1 + first->y2)) - (0.5f * (second->y1 + second->y2));

	if ((fabs(diffX) < fabs(first->x1 - first->x2) || fabs(diffX) < fabs(second->x1 - second->x2))
		&& (fabs(diffY) < fabs(first->y1 - first->y2) || fabs(diffY) < fabs(second->y1 - second->y2)))
		return true;
	return false;
}