#include <iostream>
#include <string>

#ifndef __INCLUDESHADERS 
#define __INCLUDESHADERS 



void programerrors (const GLint program) ;
void shadererrors (const GLint shader) ;
GLuint initshaders (GLenum type, const char * filename) ;
GLuint initprogram (GLuint vertexshader, GLuint fragmentshader) ;


class Shaders{
	private: 
		GLuint frag_shader;
		GLuint vertex_shader;
		GLuint shader_program;
		GLuint isLight;
		GLuint light0posn;
		GLuint light0color;
		GLuint light1posn;
		GLuint light1color;
		GLuint ambient;
		GLuint diffuse;
		GLuint specular;
		GLuint shininess;
		GLuint color;
}; 


#endif 
