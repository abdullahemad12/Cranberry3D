#include <iostream>
#include <fstream>
#include <cstring>
// OSX systems need their own headers
#ifdef __APPLE__
#include <OpenGL/gl3.h>
#include <OpenGL/glext.h>
#include <GLUT/glut.h>
#else
#include <GL/glew.h>
#include <GL/glut.h>
#endif

using namespace std ; 


/**
  * EFFECTS: calculates the size of the file
  * RETURNS: the file size in BYTES
  * ADAPTED FROM: https://stackoverflow.com/a/238607
  */
size_t fsize(FILE* fp)
{
	fseek(fp, 0L, SEEK_END);
	size_t sz = ftell(fp);
	fseek(fp, 0, SEEK_SET);
	return sz;
}

/**
  * EFFECTS: loads a text file whose path is filename into memory
  * REQUIRES: filename to be of an existing text file otherwise terminates the program
  * MODIFIES: char** prog_ptr
  * PARAMETERS:
  * - const char* filename: the name of the file to be loaded into memory
  * - char** prog_ptr: a pointer to String that will to the loaded text
  */
size_t load_text_file(const char* filename, char** prog_ptr)
{
	FILE* file = fopen(filename, "r");	
	if(file == NULL)
	{
		printf("couldn't load the shader program: %s\n", filename);
		exit(2);
	}

	size_t fs = fsize(file);
	char* prog = (char*) malloc(sizeof(char) * (fs+2));
	unsigned int strPTR = 0;
	char c;
	while(!feof(file))
	{
		c = fgetc(file);
		if(c == EOF)
		{
			break;
		}
		prog[strPTR++] = c;		
	}
	*prog_ptr = prog;
	return strPTR;
}

void programerrors (const GLint program) {
	GLint length ; 
	GLchar * log ; 
	glGetProgramiv(program, GL_INFO_LOG_LENGTH, &length) ; 
	log = new GLchar[length+1] ;
	glGetProgramInfoLog(program, length, &length, log) ; 
	cout << "Compile Error, Log Below\n" << log << "\n" ; 
	delete [] log ; 
}
void shadererrors (const GLint shader) {
	GLint length ; 
	GLchar * log ; 
	glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &length) ; 
	log = new GLchar[length+1] ;
	glGetShaderInfoLog(shader, length, &length, log) ; 
	cout << "Compile Error, Log Below\n" << log << "\n" ; 
	delete [] log ; 
}

GLuint initshaders (GLenum type, const char *filename) 
{
	// Using GLSL shaders, OpenGL book, page 679 

	GLuint shader = glCreateShader(type) ; 
	/*GLint compiled ; 
	string str = textFileRead (filename) ; 
	const GLchar * cstr = str.c_str() ; 
	glShaderSource (shader, 1, &cstr, NULL) ; 
	glCompileShader (shader) ; 
	glGetShaderiv (shader, GL_COMPILE_STATUS, &compiled) ; 
	if (!compiled) { 
		shadererrors (shader) ; 
		throw 3 ; 
	}*/
	return shader ; 
}

GLuint initprogram (GLuint vertexshader, GLuint fragmentshader) 
{
	GLuint program = glCreateProgram() ; 
	GLint linked ; 
	glAttachShader(program, vertexshader) ; 
	glAttachShader(program, fragmentshader) ; 
	glLinkProgram(program) ; 
	glGetProgramiv(program, GL_LINK_STATUS, &linked) ; 
	if (linked) glUseProgram(program) ; 
	else { 
		programerrors(program) ; 
		throw 4 ; 
	}
	return program ; 
}
