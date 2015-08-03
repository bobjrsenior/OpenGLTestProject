/*
* @file main.h
* @brief Function prototypes and includes for main.c
*
*/

//Includes
#include "GLFW.h"

//Include the standard C++ headers  
#include <stdio.h>  
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
// Image importing
#include <SOIL.h>

//Matrix manipulation
//#include "glm/glm.hpp""
//#include "glm/gtc/matrix_transform.hpp"
//#include "glm/gtc/type_ptr.hpp"

#include <math.h>


//Rendering
void render(const float *ratio);

//Character

void movement(struct square *character);

//Callbacks

/**
* @brief the callback for GLFW Errors
*/
static void error_callback(int error, const char* description);

/**
* @brief the callback for GLFW Keyboard Input
*/
static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);

/**
* @brief the callback for GLFW Mouse Position
*/
static void cursor_position_callback(GLFWwindow* window, double xpos, double ypos);