/*
* @file physics.h
* @brief Function prototypes and includes for physics.c
*
*/
//Includes
#include "GLFW.h"
#include <stdio.h>  
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>

//Function Prototypes

/*
* @brief Tells if two square objects are colliding
* @params Pointers to square struct objects
* @return Whether or not the two square structs are colliding
*/
bool isColliding(const struct square *first,const struct square *second);