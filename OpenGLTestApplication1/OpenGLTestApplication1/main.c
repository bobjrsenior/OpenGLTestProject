/*
* @file main.c
* @brief a testing file for OpenGL
*/
#pragma once
#include "main.h"
//#include "physics.h"
#include "matrixMath.h"

int randint(int n);

struct square{
	GLfloat x1, x2, y1, y2, rotation;
};

struct square chars[2];

bool keys[349];

GLfloat vertices[] = {
	//  Position   Color             Texcoords
	-0.5f, 0.5f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, // Top-left
	0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, // Top-right
	0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, // Bottom-right
	-0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f  // Bottom-left
};

GLuint elements[] = {
	0, 1, 2,
	2, 3, 0
};

// Shader sources
const GLchar* vertexSource =
"#version 150 core\n"
"in vec2 position;"
"in vec3 color;"
"in vec2 texcoord;"
"out vec3 Color;"
"out vec2 Texcoord;"
"uniform mat4 model;"
"uniform mat4 view;"
"uniform mat4 proj;"
"void main() {"
"   Color = color;"
"   Texcoord = texcoord;"
"   gl_Position = proj * view * model * vec4(position, 0.0, 1.0);"
"}";
const GLchar* fragmentSource =
"#version 150 core\n"
"in vec3 Color;"
"in vec2 Texcoord;"
"out vec4 outColor;"
"uniform sampler2D texKitten;"
"uniform sampler2D texPuppy;"
"void main() {"
"   outColor = mix(texture(texKitten, Texcoord), texture(texPuppy, Texcoord), 0.5);"
"}";


int main(void)
{
	srand(time(NULL));
	//Set the error callback  
	glfwSetErrorCallback(error_callback);

	//Initialize GLFW  
	if (!glfwInit())
	{
		exit(EXIT_FAILURE);
	}

	//Set the GLFW window creation hints - these are optional  
	//glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); //Request a specific OpenGL version  
	//glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3); //Request a specific OpenGL version  
	//glfwWindowHint(GLFW_SAMPLES, 4); //Request 4x antialiasing  
	//glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);  

	//Declare a window object  
	GLFWwindow* window;

	//Create a window and create its OpenGL context  
	window = glfwCreateWindow(640, 480, "Test Window", NULL, NULL);

	//If the window couldn't be created  
	if (!window)
	{
		fprintf(stderr, "Failed to open GLFW window.\n");
		glfwTerminate();
		exit(EXIT_FAILURE);
	}

	//This function makes the context of the specified window current on the calling thread.   
	glfwMakeContextCurrent(window);

	//Sets the key callback  
	glfwSetKeyCallback(window, key_callback);

	//Set cursor pos callback
	glfwSetCursorPosCallback(window, cursor_position_callback);

	//Initialize GLEW  
	GLenum err = glewInit();

	//If GLEW hasn't initialized  
	if (err != GLEW_OK)
	{
		fprintf(stderr, "Error: %s\n", glewGetErrorString(err));
		return -1;
	}

	//Set a background color  
	glClearColor(0.5f, 0.5f, .05f, 0.0f);
	glfwSwapInterval(1);

	//Initialization
	chars[0].x1 = -.25f;
	chars[0].x2 = .25f;
	chars[0].y1 = -.25f;
	chars[0].y2 = .25f;
	chars[0].rotation = 0.0f;

	chars[1].x1 = -.25f;
	chars[1].x2 = .25f;
	chars[1].y1 = -.25f;
	chars[1].y2 = .25f;
	chars[1].rotation = 0.0f;

	//New Drawing Test
	// Create Vertex Array Object
	GLuint vao;
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	// Create a Vertex Buffer Object and copy the vertex data to it
	GLuint vbo;
	glGenBuffers(1, &vbo);

	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	GLuint ebo;
	glGenBuffers(1, &ebo);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(elements), elements, GL_STATIC_DRAW);

	// Create and compile the vertex shader
	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexSource, NULL);
	glCompileShader(vertexShader);

	// Create and compile the fragment shader
	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentSource, NULL);
	glCompileShader(fragmentShader);

	// Link the vertex and fragment shader into a shader program
	GLuint shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glBindFragDataLocation(shaderProgram, 0, "outColor"); //Unnecsary for now
	glLinkProgram(shaderProgram);
	glUseProgram(shaderProgram);

	// Specify the layout of the vertex data
	GLint posAttrib = glGetAttribLocation(shaderProgram, "position");
	glEnableVertexAttribArray(posAttrib);
	glVertexAttribPointer(posAttrib, 2, GL_FLOAT, GL_FALSE, 7 * sizeof(GLfloat), 0);

	// Get the location of the color uniform
	//GLint uniColor = glGetUniformLocation(shaderProgram, "triangleColor");
	GLint colAttrib = glGetAttribLocation(shaderProgram, "color");
	glEnableVertexAttribArray(colAttrib);
	glVertexAttribPointer(colAttrib, 3, GL_FLOAT, GL_FALSE, 7 * sizeof(GLfloat), (void*)(2 * sizeof(GLfloat)));

	//Texture coordinates
	GLint texAttrib = glGetAttribLocation(shaderProgram, "texcoord");
	glEnableVertexAttribArray(texAttrib);
	glVertexAttribPointer(texAttrib, 2, GL_FLOAT, GL_FALSE, 7 * sizeof(GLfloat), (void*)(5 * sizeof(GLfloat)));
	
	// Load textures
	GLuint textures[2];
	glGenTextures(2, textures);

	int width, height;
	unsigned char* image;

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, textures[0]);
	image = SOIL_load_image("sample.png", &width, &height, 0, SOIL_LOAD_RGB);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
	SOIL_free_image_data(image);
	glUniform1i(glGetUniformLocation(shaderProgram, "texKitten"), 0);
	
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	/*glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, textures[1]);
	image = SOIL_load_image("sample2.png", &width, &height, 0, SOIL_LOAD_RGB);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
	SOIL_free_image_data(image);
	glUniform1i(glGetUniformLocation(shaderProgram, "texPuppy"), 1);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	*/
	//Transformations
	
	//printf("X: %f\nY: %f\nZ: %f\n", trans.arr[0], trans.arr[5], trans.arr[10]);
	GLint uniTrans = glGetUniformLocation(shaderProgram, "model");

	//
	mat4* view = lookAtMat4(makeVec3(1.2f, 1.2f, 1.2f),
		makeVec3(0.0f, 0.0f, 0.0f),
		makeVec3(0.0f, 0.0f, 1.0f));
	GLint uniView = glGetUniformLocation(shaderProgram, "view");
	glUniformMatrix4fv(uniView, 1, GL_FALSE, &view);

	mat4* proj = perspective(45.0f, 800.0f / 600.0f, 1.0f, 10.0f);
	GLint uniProj = glGetUniformLocation(shaderProgram, "proj");
	glUniformMatrix4fv(uniProj, 1, GL_FALSE, &proj);
	
	GLint uniTime = glGetUniformLocation(shaderProgram, "time");

	GLfloat test = *(GLfloat*)malloc(sizeof(GLfloat));
	test = 45.0f;
	printf("%f : %f\n", degToRadCos(test), degToRadSin(test));
	//printVec3(normalizeNewVec3(makeVec3(3, 2, 7)));
	//printVec3(normalizeNewVec3(makeVec3(11, 4, 1)));

	//Main Loop  
	do
	{
		float ratio;
		int width, height;
		glfwGetFramebufferSize(window, &width, &height);
		ratio = width / (float)height;

		glViewport(0, 0, width, height);

		//Clear color buffer  
		glClear(GL_COLOR_BUFFER_BIT);
		//glClearColor((float)rand() / (float)RAND_MAX, (float)rand() / (float)RAND_MAX, (float)rand() / (float)RAND_MAX, 1.0f);
		
		movement(&chars[0]);
		//render(&ratio);
		//Rendering
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		glOrtho(-ratio, ratio, -1.f, 1.f, 1.f, -1.f);
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		glRotatef((float)glfwGetTime() * chars[0].rotation, 0.0f, 0.f, 1.0f);

		//Set color of and draw the triangle
		glUniform3f(colAttrib, 1.0f, 0.0f, 0.0f);
		glUniform1f(uniTime, glfwGetTime());
		mat4* model;
		model = rotateMat4(glfwGetTime() * 180.0f, makeVec3(0.0f, 0.0f, 1.0f));
		glUniformMatrix4fv(uniTrans, 1, GL_FALSE, model);
		//glUniformMatrix4fv(uniTrans, 1, GL_FALSE, glm:value_ptr(trans));
		//glDrawArrays(GL_TRIANGLES, 0, 3); //For non buffered/index drawing
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);


		for (int e = 0; e < 0; e++){
			glBegin(GL_QUADS);
			glColor3f(1.f, 0.f, 0.f);
			glVertex3f(chars[e].x1, chars[e].y1, 0.f);
			glColor3f(0.f, 1.f, 0.f);
			glVertex3f(chars[e].x1, chars[e].y2, 0.f);
			glColor3f(0.f, 0.f, 1.f);
			glVertex3f(chars[e].x2, chars[e].y2, 0.f);
			glColor3f(0.f, 0.f, 1.f);
			glVertex3f(chars[e].x2, chars[e].y1, 0.f);
			glEnd();
		}


		//Swap buffers  
		glfwSwapBuffers(window);
		//Get and organize events, like keyboard and mouse input, window resizing, etc...  
		glfwPollEvents();

	} //Check if the ESC key had been pressed or if the window had been closed  
	while (!glfwWindowShouldClose(window));

	//Close OpenGL window and terminate GLFW  
	glfwDestroyWindow(window);
	//Finalize and clean up GLFW  
	glfwTerminate();

	exit(EXIT_SUCCESS);
}

//Rendering
void render(const float *ratio){
	//Rendering
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-*ratio, *ratio, -1.f, 1.f, 1.f, -1.f);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glRotatef((float)glfwGetTime() * chars[0].rotation, 0.0f, 0.f, 1.0f);
	
	//Set color of and draw the triangle
	//glUniform3f(uniColor, 1.0f, 0.0f, 0.0f);
	glDrawArrays(GL_TRIANGLES, 0, 3);


	for (int e = 0; e < 0; e++){
		glBegin(GL_QUADS);
		glColor3f(1.f, 0.f, 0.f);
		glVertex3f(chars[e].x1, chars[e].y1, 0.f);
		glColor3f(0.f, 1.f, 0.f);
		glVertex3f(chars[e].x1, chars[e].y2, 0.f);
		glColor3f(0.f, 0.f, 1.f);
		glVertex3f(chars[e].x2, chars[e].y2, 0.f);
		glColor3f(0.f, 0.f, 1.f);
		glVertex3f(chars[e].x2, chars[e].y1, 0.f);
		glEnd();
	}
}

//Character
void movement(struct square *character){
	if (keys[GLFW_KEY_W]){
		character->y1 += .001f;
		character->y2 += .001f;
		//printf("%s", isColliding(&chars[0], &chars[1]) ? "True" : "False");
	}
	else if (keys[GLFW_KEY_S]){
		character->y1 -= .001f;
		character->y2 -= .001f;
		//printf("%s", isColliding(&chars[0], &chars[1]) ? "True" : "False");
	}
	if (keys[GLFW_KEY_D]){
		character->x1 += .001f;
		character->x2 += .001f;
		//printf("%s", isColliding(&chars[0], &chars[1]) ? "True" : "False");
	}
	else if (keys[GLFW_KEY_A]){
		character->x1 -= .001f;
		character->x2 -= .001f;
		//printf("%s", isColliding(&chars[0], &chars[1]) ? "True" : "False");
	}

}


//Callbacks

//Define an error callback  
static void error_callback(int error, const char* description)
{
	fputs(description, stderr);
	_fgetchar();
}

//Define the key input callback  
static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	printf("%i", key);
	if (action == GLFW_PRESS){
		if (key == GLFW_KEY_ESCAPE){
			glfwSetWindowShouldClose(window, GL_TRUE);
		}
		keys[key] = true;
	}
	else if (action == GLFW_REPEAT){
		
	}
	else if (action == GLFW_RELEASE){
		keys[key] = false;
	}

}

//Mouse Position Callback
static void cursor_position_callback(GLFWwindow* window, double xpos, double ypos)
{
	//printf("%f : %f\n", xpos, ypos);
}