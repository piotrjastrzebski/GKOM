#include <iostream>
#include <GL/glut.h>

#include "scene_controls.h"
#include "display.h"
#include "moving_parts.h"

int o;
double alpha=0.9;
double XX=45.0;
double YY=5.0;
double ZZ=14.0;

void control_alpha(){
	GLfloat block_diffuse[] = { 0, 0, 0, alpha};
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, block_diffuse);
}

void scene(){
	gluLookAt(0,0,ZZ,0,0,0,0,1,0);
	glRotatef(YY, 1, 0, 0);
	glRotatef(XX, 0, 1, 0);
}

void light(int whichone) //lights control
{
	bool static a=true, b=false, c=false;
	switch(whichone)
	{
		case(0):
			if(a==false)
				{glEnable(GL_LIGHT0); a=true;}
			else
				{glDisable(GL_LIGHT0); a=false;}
			break;
		case(1):
			if(b==false)
				{glEnable(GL_LIGHT1); b=true;}
			else
				{glDisable(GL_LIGHT1); b=false;}
			break;
		case(2):
			if(c==false)
				{glEnable(GL_LIGHT2); c=true;}
			else
				{glDisable(GL_LIGHT2); c=false;}
			break;
	}
	std::cout << "L: " << a << "/" << b << "/" << c << " ";
}

void Keyboard (int key, int x, int y)
{	
	system("cls");
	switch(key) //camera rotation control
	{ 
		case(GLUT_KEY_UP): if(YY<90) YY+=5; break;
		case(GLUT_KEY_DOWN): if(YY>0) YY-=5; break;
		case(GLUT_KEY_LEFT): XX+=5; break;
		case(GLUT_KEY_RIGHT): XX-=5; break;
		case(GLUT_KEY_PAGE_UP): if(ZZ<26) ZZ+=1;  break;
		case(GLUT_KEY_PAGE_DOWN): if(ZZ>8) ZZ-=1; break;
		case(GLUT_KEY_HOME): XX=0.0; YY=0.0; ZZ=10.0; break;
		case(GLUT_KEY_F1): light(0); break;
		case(GLUT_KEY_F2): light(1); break;
		case(GLUT_KEY_F3): light(2); break;
	}
	display();
	//std::cout
	//<< "X: " << XX
	//<< " Y: " << YY
	//<< " Z: " << ZZ
	//<< " delta:" << get_delta()
	//<< " o:" << o
	//<< " alpha:" << alpha
	//<< std::endl;
}

void Keyboard (unsigned char key, int x, int y)
{
	system("cls");
	switch(key) //engine speed control & fullscreen
	{ 
		case('`'): if(get_delta()>=0) set_delta(DBL_MIN); else set_delta(-DBL_MIN); break;
		case('1'): if(get_delta()>=0) set_delta(0.015); else set_delta(-0.015); break;
		case('2'): if(get_delta()>=0) set_delta(0.030); else set_delta(-0.030); break;
		case('3'): if(get_delta()>=0) set_delta(0.045); else set_delta(-0.045); break;
		case('F'): glutFullScreen(); break;
		case('f'): glutReshapeWindow(600,600); glutInitWindowPosition(0, 0); break;
		case('x'): o++; /*load_alternative_texture(o, &TexID1);*/ break;
		case('+'): if(alpha<1) alpha+=0.1; break;
		case('-'): if(alpha>0.2) alpha-=0.1; break;
	}
	display();
	//std::cout
	//<< "X: " << XX
	//<< " Y: " << YY
	//<< " Z: " << ZZ
	//<< " delta:" << get_delta()
	//<< " o:" << o
	//<< " alpha:" << alpha
	//<< std::endl;
}

int get_o()
{
	return o;
}

void set_o(int value)
{
	o=value;
}
