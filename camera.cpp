#include <camera.h>
#include <iostream>

using namespace glm;


Camera::Camera(vec3 eye, vec3 up)
{
	this->eye = eye;
	this->up = up;
}

vec3 Camera::getEye(void)
{
	return this->eye; 
}
vec3 Camera::getUp(void)
{
	return this->up;
}


