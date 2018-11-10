#ifndef _CAMERA_H
#define _CAMERA_H
#include <iostream>
#include <sstream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <linkedlist.h>
#include <GL/glew.h>
#include <GL/glut.h>

using namespace std;
class Object{
	private:
		GLuint VAO;
		GLuint VBO;
		GLuint NBO;
		GLuint EBO;
		GLuint CBO;
		GLuint  vertexshader;
		GLuint fragmentshader;
		GLuint shaderprogram;
		Array* verticies;
		Array* normals;
		Array* colors;
		Array* indicies;

	public: 
		Object(const char* filename);
		Object(Array* verticies, Array* normals, Array* colors, Array* indicies);
};



#endif