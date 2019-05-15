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
		const char* id;
		GLuint VAO;
		GLuint VBO;
		GLuint NBO;
		GLuint EBO;
		GLuint CBO;
		Array* verticies;
		Array* normals;
		Array* colors;
		Array* indicies;

		/*initial Transformation*/
		vec3 initialTranslate;
		float initialRotate; /*in degrees*/
		vec3 rotationAxis;
		vec3 initialScale;
		bool bound;

		/*functions*/
		void bind(void);
	public: 
		Object(const char* id, Array* verticies, Array* normals, Array* colors, Array* indicies);
		void setInitialTranslate(vec3 intialTranslate);
		void setInitialRotate(float angle, vec3 axis);
		void setInitailScale(vec3 scale);
};



#endif