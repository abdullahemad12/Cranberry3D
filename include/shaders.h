#include <iostream>
#include <string>

#ifndef __INCLUDESHADERS 
#define __INCLUDESHADERS 



void programerrors (const GLint program) ;
void shadererrors (const GLint shader) ;
GLuint initshaders (GLenum type, const char * filename) ;
GLuint initprogram (GLuint vertexshader, GLuint fragmentshader) ;

#endif 
