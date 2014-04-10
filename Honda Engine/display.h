#ifndef __display_h
#define __display_h

#include <GL/glut.h>

GLuint LoadTexture(char *TexName);
void init();
void displayObjects(float moment, float delta);
void display();
void reshape(GLsizei w, GLsizei h);

#endif

