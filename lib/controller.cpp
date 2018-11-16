/**
  * This is the main file that controlls everything you see in the seen and is responsible for
  * All the initializations necessary for OpenGl
  */

#include <iostream>
#include <controller.h>
using namespace glm;


Controller::Controller(void)
{
	this->objects = new Linkedlist();
	vec3 eyeinit = vec3(0.0, 0.0, 7.0);
	vec3 upinit = vec3(0.0, 1.0, 0.0);
	this->camera = new Camera(eyeinit, upinit);
	glEnable(GL_DEPTH_TEST);
}

void Controller::init(void)
{


}