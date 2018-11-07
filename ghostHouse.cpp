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

float rotAng;


/**
  * initilizes the eye and up vectors
  */
void init(void)
{

}




void Display(void) {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

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

	glFlush();
}

void Anim() {
	rotAng += 0.01;

	glutPostRedisplay();
}


int main(int argc,char* argv[]) {

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
	glutSpecialFunc(specialKey);
	glutKeyboardFunc(keyboard);
	glutReshapeFunc(reshape);
	glutReshapeWindow(w,h);

	if(argc > 1) {
		allowGrader = true;
		grader.init(argv[1]);
		grader.loadCommands(argv[1]);
		grader.bindDisplayFunc(display);
		grader.bindSpecialFunc(specialKey);
		grader.bindKeyboardFunc(keyboard);
		grader.bindScreenshotFunc(saveScreenshot);
	}

	printHelp();
	glutMainLoop();	
	FreeImage_DeInitialise();
	cleanup();

	return 0;
}

