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
#include <FreeImage.h>
#include <iomanip>
#include <string.h>
#include <primitives.h>
#include <math.h>
#include <dimensions.h>

#ifdef _WIN32
    #include <windows.h>

    void msleep(unsigned milliseconds)
    {
        Sleep(milliseconds);
    }
#else
    #include <unistd.h>

    void msleep(unsigned milliseconds)
    {
        usleep(milliseconds * 1000); // takes microseconds
    }
#endif


/*
 * primitive: GL_POLYGON
 */
void draw_circle(int center_x, int center_y, int x, int y, uint32_t color)
{
	float b = ((color & 0x0000FF00) >> 8) / (float)0xFF;
	float g = ((color & 0x00FF0000) >> 16) / (float)0xFF;
	float r = ((color & 0xFF000000) >> 24) / (float)0xFF;
	glColor3f(r, g, b);
	glBegin(GL_POLYGON);
	for(int i = 0; i < CIRCLE_SEGMENTS; i++)
	{
		float theta = 2.0 * PI * i / (float) CIRCLE_SEGMENTS;
		float x_coord = x * cosf(theta); 
		float y_coord = y * sinf(theta);
		glVertex2f(x_coord + center_x, y_coord + center_y);	
	}
    glEnd();

}

/**
  * primitive: GL_LINE_LOOP
  */
void draw_circular_outline(int center_x, int center_y, int x, int y, uint32_t color)
{
	float b = ((color & 0x0000FF00) >> 8) / (float)0xFF;
	float g = ((color & 0x00FF0000) >> 16) / (float)0xFF;
	float r = ((color & 0xFF000000) >> 24) / (float)0xFF;
	glColor3f(r, g, b);
	glBegin(GL_LINE_LOOP);
	for(int i = 0; i < CIRCLE_SEGMENTS; i++)
	{
		float theta = 2.0 * PI * i / (float) CIRCLE_SEGMENTS;
		float x_coord = x * cosf(theta); 
		float y_coord = y * sinf(theta);
		glVertex2f(x_coord + center_x, y_coord + center_y);	
	}
    glEnd();
}

/**
  * Primitive: GL_QUAD 
  */
void draw_rect(int x, int y, int width, int height, uint32_t color, int angle)
{

	float b = ((color & 0x0000FF00) >> 8) / (float)0xFF;
	float g = ((color & 0x00FF0000) >> 16) / (float)0xFF;
	float r = ((color & 0xFF000000) >> 24) / (float)0xFF;

    glPushMatrix();
	glColor3f(r, g, b);

	float center_x = (2 * x + width) / 2;
	float center_y = (2 * y + height) / 2;

	glTranslated(center_x, center_y, 0);
	glRotatef(angle, 0, 0, 1);
	glTranslated(-center_x, -center_y, 0);
	
	glBegin(GL_QUADS);
	glVertex2f(x, y);
	glVertex2f(x + width, y);
	glVertex2f(x + width, y + height);
	glVertex2f(x, y + height);

	glEnd();

    glPopMatrix();

}


void drawImage(GLuint file, float x,float y, float w, float h)
{
	glBlendFunc  (GL_ONE_MINUS_SRC_ALPHA, GL_SRC_ALPHA);
  	glEnable     (GL_BLEND);
  	glEnable     (GL_COLOR_MATERIAL);

    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
    glPushMatrix();



	glColor4f(0, 0, 0, 0);
    glBindTexture(GL_TEXTURE_2D, file);
    glEnable(GL_TEXTURE_2D);

    glBegin(GL_QUADS);

    glTexCoord2f(0.0, 0.0); glVertex3f(x, y, 0.0f);
    glTexCoord2f(0.0, 1.0); glVertex3f(x, y + h, 0.0f);
    glTexCoord2f(1.0, 1.0); glVertex3f(x + w, y + h, 0.0f);
    glTexCoord2f(1.0, 0.0); glVertex3f(x + w, y, 0.0f);
    glEnd();
	glDisable(GL_TEXTURE_2D);
    glPopMatrix();

	glDisable(GL_BLEND);
	glDisable(GL_COLOR_MATERIAL);
}


/**
  * Primitive: GL_TRIANGLES
  *
  */
void draw_traingle(float x, float y, float ablength, float angleab, float anglecb, uint32_t color, float angle)
{

	
	float b = ((color & 0x0000FF00) >> 8) / (float)0xFF;
	float g = ((color & 0x00FF0000) >> 16) / (float)0xFF;
	float r = ((color & 0xFF000000) >> 24) / (float)0xFF;
	
	int r1 = ablength + 10000;

	
	float x1 = r1 * cosf((PI * angleab) / 180.0);
	float y1 = r1 * sinf((PI * angleab) / 180.0);
	float m1 = y1 / x1;

	float x2 = r1 * cosf((PI * abs(180 - anglecb)) / 180.0);
	float y2 = r1 * sinf((PI * abs(180 - anglecb)) / 180.0);
	float m2 = (y2 - 0) / (x2 - ablength);
	float c = y2 - (m2 * x2);

	float intx = -c / (m2 - m1);

	float inty = intx * m1;


	glPushMatrix();
	glColor3f(r, g, b);
	glTranslated(x, y, 0);
	glRotated(angle, 0, 0, 1);
	glBegin(GL_TRIANGLES);
	glVertex2f(0, 0);
	glVertex2f(ablength, 0);
	glVertex2f(intx, inty);

	

	glEnd();
	glPopMatrix();
			
}