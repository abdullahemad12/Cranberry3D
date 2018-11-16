#ifndef _CAMERA_H
#define _CAMERA_H
#include <iostream>
#include <sstream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

using namespace glm;


class Camera{
	private: 
		vec3 eye; /*eye vector*/
		vec3 up; /*up vector*/
	public: 
		Camera(vec3 eye, vec3 up);
		vec3 getEye(void);
		vec3 getUp(void);
		mat4 lookAt(void);

};



#endif