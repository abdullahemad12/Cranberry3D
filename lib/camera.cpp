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

mat4 Camera::lookAt(void)
{
	vec3 w = normalize(this->eye);
	vec3 u = normalize(cross(this->up, w));
	vec3 v = cross(w, u);
	mat4 Ruvw = mat4(u.x, v.x, w.x, 0, u.y, v.y, w.y, 0, u.z, v.z, w.z, 0, 0, 0, 0, 1);
	mat4 trans = mat4(1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, -eye.x, -eye.y, -eye.z, 1);
	return Ruvw * trans;
}


