#ifndef __moving_parts_h
#define __moving_parts_h

#include <GL/glut.h>
#define N 32

void room(GLuint *texture1, GLuint *texture2);
void mixture(int *stroke, float moment, float posX, float posY, float posZ);
void piston(float posX, float posY, float posZ);
void valveitself(int type, float posX, float posY, float posZ, float moment);
void valve(int *stroke, float moment, float delta, int type, float posX, float posY, float posZ);
void glowplug(float moment, int type, int stroke);
void block();
void crankshaft(float moment, float delta, int type, float posX, float posY, float posZ);
void flywheel(float moment);
void rackwheel(float moment);
void smallwheel(float moment);
void cylinder(int *stroke, float moment, float delta, int type, float posX, float posY, float posZ);
void load_alternative_texture(int o, GLuint *texture);
void load(GLuint *texture1, GLuint *texture2);
void set_delta(double value);
double get_delta();
void particles(int number, float moment, int type);

#endif