/*************************************************
 * Author: Abdullah Emad                         *
 * Description: this class contains the abstract *
 * implementation of an Object in a 3D world     *
 *************************************************/

/*
 * Inherit this if you need to add more features to your object
 *
 */
#include <object.h>
#include <linkedlist.h>




Object::Object(const char* id, Array* verticies, Array* normals, Array* colors, Array* indicies)
{
	memcpy(this->id, id);
	this->verticies = verticies; 
	this->normals = normals;
	this->colors = colors;
	this->indicies = indicies;

	glGenVertexArrays(1, &this->VAO);
	// Now allocate some space for all the buffer objects
	glGenBuffers(1, &this->VBO);
	glGenBuffers(1, &this->NBO);
	glGenBuffers(1, &this->EBO);
	if(this->colors)
	{
		glGenBuffers(1, &this->CBO);
	}
	this->bound = false;
}

void Object::bind(void)
{

}

void Object::setInitialTranslate(vec3 intialTranslate)
{
	this->initialTranslate = initialTranslate;
}

void Object::setInitialRotate(float angle, vec3 axis)
{
	this->initialRotate = angle;
	this->rotationAxis = axis;
}

void Object::setInitailScale(vec3 scale)
{
	this->initialScale = scale;
}

