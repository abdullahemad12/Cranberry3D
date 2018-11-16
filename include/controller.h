#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <linkedlist.h>
#include <GL/glew.h>
#include <GL/glut.h>
#include <camera.h>
using namespace glm;

class Controller{

	private:
		Linkedlist* objects; /*Keeps track of all the objects in the world*/
		Camera* camera;
		mat4 model;
		mat4 view; /*model view matricies*/
		GLuint modelViewPos; /*descriptor for model view pos*/
		GLuint vertexShader;
		GLuint fragmentShader;
		GLuint shaderProgram;
	public:
		Controller(void);
		void init(void);
};