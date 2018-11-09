#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
// OSX systems need their own headers
#ifdef __APPLE__
#include <OpenGL/gl3.h>
#include <OpenGL/glext.h>
#include <GLUT/glut.h>
#else
#include <GL/glew.h>
#include <GL/glut.h>
#endif
// Use of degrees is deprecated. Use radians for GLM functions
#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <dimensions.h>
#include<iostream>
#include<camera.h>
#include <FreeImage.h>

float rotAng;

Camera* cam;
/**
  * initilizes the eye and up vectors
  */
void init(void)
{
	const vec3 eye(0.0,0.0,7.0); 
	const vec3 up(0.0,1.0,0.0);
	cam = new Camera(eye, up);
}

void keyboard(unsigned char key,int x,int y) 
{


}

// This function gets called when the window size gets changed
void reshape(int width,int height){
	glViewport(0,0,width,height);
	gluPerspective(90.0f, (float)width / (float) height, 0.1f, 100.0f);
}



void display(void) 
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
 	//vec3 center(0.0,0.0,0.0); 
	//glm::lookAt(cam->getEye(), center, cam->getUp());
	glClearColor(0,0,1,0);

	glPushMatrix();
	glRotatef(rotAng, 0, 1, 0);
	glColor3f(0.0f, 0.0f, 0.0f);
	glutSolidCube(1);
	glPopMatrix();

	glPushMatrix();
	glRotatef(-rotAng, 0, 1, 0);
	glTranslatef(2, 0, 0);
	glRotatef(rotAng, 1, 0, 0);
	glColor3f(0.5f, 0.5f, 0.5f);
	glutSolidSphere(0.5, 25, 25);
	glPopMatrix();

	glutSwapBuffers();
}

void cleanup(void)
{

}


int main(int argc,char* argv[]) 
{
	FreeImage_Initialise();
	//Initialize GLUT
	glutInit(&argc,argv);
#ifdef __APPLE__ // OSX systems require an extra flag
	glutInitDisplayMode(GLUT_3_2_CORE_PROFILE | GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
#else
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
#endif
	glutCreateWindow("Ghosts House");

#ifndef __APPLE__ // GLew not needed on OSX systems.
	GLenum err = glewInit() ; 
	if (GLEW_OK != err) { 
		std::cerr << "Error: " << glewGetString(err) << std::endl; 
	} 
#endif

	init();
	glutDisplayFunc(display);
	glutKeyboardFunc(keyboard);
	glutReshapeFunc(reshape);
	glutReshapeWindow(SCREEN_WIDTH, SCREEN_HEIGHT);
	glutMainLoop();
	FreeImage_DeInitialise();	
	gluLookAt(0.0f, 2.0f, 5.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f);
	cleanup();
	return 0;
}

