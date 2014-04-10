#include <cstdlib>
#include <ctime>
#include <math.h>
#include <cfloat>
#include <iostream>

#include "scene_controls.h"
#include "moving_parts.h"
#include "display.h"

double delta=0.015;

void load_alternative_texture(int o, GLuint *texture)
{
	if(o!=0 && o%3==0){
		*texture=LoadTexture("textures/omg.tga");
		set_o(-2);
	}
	else if(o==-1){
		*texture=LoadTexture("textures/sciana.tga");
		set_o(0);
	}
}

void load(GLuint *texture1, GLuint *texture2)
{
	*texture1=LoadTexture("textures/podloga.tga");
	*texture2=LoadTexture("textures/sciana.tga");
}

void room(GLuint *texture1, GLuint *texture2){
	glColor3f(1.0f,1.0f,1.0f);
	glEnable(GL_TEXTURE_2D);

	//ceiling
	glBegin(GL_QUADS);
		glVertex3f(-25.0f, 25.0f, -25.0f);
		glVertex3f(-25.0f, 25.0f, 25.0f);
		glVertex3f( 25.0f, 25.0f, 25.0f);
		glVertex3f( 25.0f, 25.0f, -25.0f);
	glEnd();
 
	//floor
	glBindTexture(GL_TEXTURE_2D, *texture1);
 	glBegin(GL_QUADS);
		glTexCoord2f(0.0f,0.0f); glVertex3f(-25.0f,-25.0f, -25.0f);
		glTexCoord2f(0.0f,1.0f); glVertex3f(-25.0f,-25.0f, 25.0f);
		glTexCoord2f(1.0f,1.0f); glVertex3f( 25.0f,-25.0f, 25.0f);
		glTexCoord2f(1.0f,0.0f); glVertex3f( 25.0f,-25.0f, -25.0f);
	glEnd();

	//wall1
	glBindTexture(GL_TEXTURE_2D,*texture2);
 	glBegin(GL_QUADS);
		glTexCoord2f(0.0f,0.0f); glVertex3f(-25.0f,-25.0f, 25.0f);
		glTexCoord2f(0.0f,1.0f); glVertex3f(-25.0f, 25.0f, 25.0f);
		glTexCoord2f(1.0f,1.0f); glVertex3f( 25.0f, 25.0f, 25.0f);
		glTexCoord2f(1.0f,0.0f); glVertex3f( 25.0f,-25.0f, 25.0f);
	glEnd();
	
	//wall2
 	glBegin(GL_QUADS);
		glTexCoord2f(0.0f,0.0f); glVertex3f(25.0f,-25.0f, 25.0f);
		glTexCoord2f(0.0f,1.0f); glVertex3f(25.0f, 25.0f, 25.0f);
		glTexCoord2f(1.0f,1.0f); glVertex3f( 25.0f, 25.0f, -25.0f);
		glTexCoord2f(1.0f,0.0f); glVertex3f( 25.0f,-25.0f, -25.0f);
	glEnd();

	//wall3
 	glBegin(GL_QUADS);
		glTexCoord2f(0.0f,0.0f); glVertex3f(25.0f,-25.0f, -25.0f);
		glTexCoord2f(0.0f,1.0f); glVertex3f(25.0f, 25.0f, -25.0f);
		glTexCoord2f(1.0f,1.0f); glVertex3f(-25.0f, 25.0f, -25.0f);
		glTexCoord2f(1.0f,0.0f); glVertex3f(-25.0f,-25.0f, -25.0f);
	glEnd();

	//wall4
 	glBegin(GL_QUADS);
		glTexCoord2f(0.0f,0.0f); glVertex3f(-25.0f,-25.0f, -25.0f);
		glTexCoord2f(0.0f,1.0f); glVertex3f(-25.0f, 25.0f, -25.0f);
		glTexCoord2f(1.0f,1.0f); glVertex3f(-25.0f, 25.0f, 25.0f);
		glTexCoord2f(1.0f,0.0f); glVertex3f(-25.0f,-25.0f, 25.0f);
	glEnd();

//table
glPushMatrix();
	glPushAttrib(GL_ALL_ATTRIB_BITS);
		glPushMatrix();
			GLfloat mat_ambient1[]    = {0.0, 1.0,  0.0, 1.0 };
			GLfloat mat_specular1[]   = { 0.0, 1.0,  0.0, 1.0 };
			glMaterialf( GL_FRONT_AND_BACK, GL_SHININESS, 50.0 );
			glMaterialfv( GL_FRONT_AND_BACK, GL_AMBIENT, mat_ambient1 );
			glMaterialfv( GL_FRONT_AND_BACK, GL_SPECULAR, mat_specular1 );
			GLUquadricObj *myQuad;
			myQuad=gluNewQuadric();
			glTranslatef(0,-4.25,0);
			glRotatef(90, 1,0,0);
			gluCylinder(myQuad, 1.5, 0.25, 20.75, N, 1); //cylinder
			glTranslatef(0,0,20.7);
			gluDisk(myQuad, 0, 3, N, N); //cylinder's lid
			gluDeleteQuadric(myQuad);
		glPopMatrix();
		glTranslatef(0,-4.25,0);
		glScalef(13.5,0.3,9);
		glutSolidCube(1);
	glPopAttrib();
glPopMatrix();
	glDisable(GL_TEXTURE_2D);
}

void mixture(int *stroke, float moment, float posX, float posY, float posZ)
{	
	float dk=0;
	int color=1;
	if(*stroke==1){
		dk=0.25*moment+0.25;
		color=0;
	}
	else
		if(*stroke==2){
			dk=-0.25*moment+0.75;
			color=0;
		}
		else
			if(*stroke==3){
				dk=-0.25*moment+0.75;
				color=1;
			}
			else
				if(*stroke==4){
					dk=0.25*moment+0.25;
					color=1;
				}

	glPushMatrix();
	glPushAttrib(GL_ALL_ATTRIB_BITS);
		glRotatef(90, 1.0, 0, 0);
		glTranslatef(posX, posY, posZ); 
		GLfloat mixture_diffuse[] = { color, 0, 1-color, dk};
		glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, mixture_diffuse);
		GLUquadricObj *myQuad;
		myQuad=gluNewQuadric();
		glTranslatef(0, 0, -1);
		gluCylinder(myQuad, 0.85, 0.85, 1+moment, N, 1); //cylinder
		glRotatef(180, 0,1,0);
		gluDisk(myQuad, 0, 0.85, N, N); //cylinder's lid
	glPopAttrib();
	glPopMatrix();
	gluDeleteQuadric(myQuad);
}

void piston(float posX, float posY, float posZ)
{
	glPushMatrix();
	glPushAttrib(GL_ALL_ATTRIB_BITS);
		GLfloat cylinder_diffuse[] = { 0.5, 0.5, 0.5, 1.0 };
		glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, cylinder_diffuse);
			GLUquadricObj *myQuad;
		myQuad=gluNewQuadric();
			glTranslatef(posX, posY, posZ); 
							glPushMatrix();
							glPushAttrib(GL_ALL_ATTRIB_BITS);
								GLfloat cylinder_diffuse2[] = { 0, 0, 0, 1.0 };
								glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, cylinder_diffuse2);
								for(int i=0;i<3;i++){
									glTranslatef(0, 0, 0.1); 
									gluCylinder(myQuad, 0.86, 0.86, 0.03, N, 1);
								}
							glPopAttrib();
							glPopMatrix();
				gluCylinder(myQuad, 0.85, 0.85, 1.75, N, 1); //cylinder
			gluDisk(myQuad, 0, 0.85, N, N); //cylinder's lid
	glPopAttrib();
	glPopMatrix();
	gluDeleteQuadric(myQuad);
}

void valveitself(int type, float posX, float posY, float posZ, float moment)
{
	glPushMatrix();
	glPushAttrib(GL_ALL_ATTRIB_BITS);
	GLUquadricObj *myQuad;
	myQuad=gluNewQuadric();
	if(type==0)
	{
		GLfloat blueValve_diffuse[] = { 0, 0, 1, 1.0 }; //blue - intake v.
		glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, blueValve_diffuse);
	}
	else
	{
		GLfloat redValve_diffuse[] = { 1, 0, 0, 1.0 }; //red - exhaust v.
		glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, redValve_diffuse);
	}
	

		glTranslatef(posX, posY, posZ);
	
		glRotatef(225-90*type,1,0,0);

		gluDisk(myQuad, 0, 0.25, N, N); 			//		|
		glutSolidCone(0.25, 0.25, N, N); 			//		|>
		gluCylinder(myQuad, 0.05, 0.05, 1, N, 1);	//		|>--
		if(posZ==-1)
			particles(200, moment, type);
	glPopAttrib();
	glPopMatrix();
	gluDeleteQuadric(myQuad);
}

void valve(int *stroke, float moment, float delta, int type, float posX, float posY, float posZ)
{
	if(type==1)
		delta*=-1;
	glPushMatrix();
	glPushAttrib(GL_ALL_ATTRIB_BITS);
	glTranslatef(posX, posY, posZ-0.250);

	if(*stroke==1){ //E close I open
		if(delta >= 0)
			*stroke=2;
		else{
			valveitself(0, 0, 0.5, -1, moment);
			valveitself(1, 0, -0.75, -1.25, moment);
		}
	}
	
	if(*stroke==2){//E close I close
		if(delta <= 0)
			*stroke=3;
		else{
			valveitself(0, 0,0.75,-1.25, moment);
			valveitself(1, 0,-0.75,-1.25, moment);
		}
	}
	
	if(*stroke==3){//E close I close
		if(delta >= 0)
			*stroke=4;
		else{
			valveitself(0, 0, 0.75, -1.25, moment);
			valveitself(1, 0,-0.75, -1.25, moment);
		}
	}
	if(*stroke==4){//E open I close
		if(delta<=0)
			*stroke=1;
		else{
			valveitself(0, 0, 0.75, -1.25, moment);
			valveitself(1, 0, -0.5, -1, moment);
		}
	}
	glPopAttrib();
	glPopMatrix();
}

void glowplug(float moment, int type, int stroke)
{	
	if((moment-0.9>=DBL_MIN && type==-1 && stroke==3) || (moment+0.9<=-DBL_MIN && type==1 && stroke==3)) // change colour
		glEnable(GL_LIGHT3);
	else
		glDisable(GL_LIGHT3);					
	glPushMatrix();
	glPushAttrib(GL_ALL_ATTRIB_BITS);
		GLfloat sparkGP_diffuse[] = { 1, 1, 0, 1.0 };
		GLfloat normalGP_diffuse[] = { 0.5, 0.5, 0.5, 1.0 };
		GLfloat blackGP_diffuse[] = { 0, 0, 0, 1.0 };
		GLfloat whiteGP_diffuse[] = {1,1,1,1};
		GLUquadricObj *myQuad;
		myQuad=gluNewQuadric();
		glPushMatrix();
			glTranslatef(0,0,-2);
			glutSolidSphere(0.1,6,6);
		glPopMatrix();
		glTranslatef(0,0,-1.25);
		glRotatef(180,1,0,0);
		glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, blackGP_diffuse);
		glPushMatrix();
			glTranslatef(0,0,0.5);
			glutSolidSphere(0.2,6,6);
		glPopMatrix();
		gluCylinder(myQuad, 0.2, 0.2, 0.5, 6, 1);
		glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, whiteGP_diffuse);
		gluCylinder(myQuad, 0.1, 0.1, 0.8, 6, 1);
		if((moment-0.9>=DBL_MIN && type==-1 && stroke==3) || (moment+0.9<=-DBL_MIN && type==1 && stroke==3)) // change colour
			glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, sparkGP_diffuse);	
		else
			glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, normalGP_diffuse);
		glutSolidSphere(0.1, 10, 10);
	glPopAttrib();
	glPopMatrix();
	gluDeleteQuadric(myQuad);
}

void block()
{
	glPushMatrix();
	glPushAttrib(GL_ALL_ATTRIB_BITS);
		control_alpha();
		glTranslatef(0,-2,0);
		glScalef(8, 9, 5);
		glutSolidCube(1);
	glPopAttrib();
	glPopMatrix();
}

void crankshaft(float moment, float delta, int type, float posX, float posY, float posZ)
{	double beta=73.3984504;
	glPushAttrib(GL_ALL_ATTRIB_BITS);	
	GLfloat cylinder_diffuse[] = { 0.5, 0.5, 0.5, 1.0 };
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, cylinder_diffuse);
	GLUquadricObj *myQuad;
	myQuad=gluNewQuadric();
	float degree=0.0, omg=0.0;

	if(delta<0) //keeps pole straight
		degree=90*moment+270;
	else
		degree=-90*moment+90;
glPushMatrix();
	glTranslatef(posX, posY, posZ);
	glPushMatrix();
		
		if(type==1){ //reversed pole keeps the same direction as normal one
			degree=180-degree;
			degree*=-1;
		}
		glRotatef(degree, 0, 0, 1);

		glPushMatrix(); //3rd tube
			glTranslatef(0,0, 2.0);
			gluCylinder(myQuad, 0.1, 0.1, 0.3, N, 1);
		glPopMatrix();

		glPushMatrix(); //2nd crank
			glTranslatef(0,0.5, 1.9);
			glScalef(2, 12, 2);
			glutSolidCube(0.1);
		glPopMatrix();

		glPushMatrix(); //thingamajig goes to piston

			glRotatef(90, 1, 0, 0);

			glTranslatef(0,1.3,-1);

			if(type==-1){
				if(delta>0)
					if(moment<0)
						degree=beta*moment+beta;//1
					else
						degree=(180-beta)*moment+beta;//2
				else
					if(moment<0)
						degree=-(beta)*moment+360-beta;//4
					else
						degree=-(180-beta)*moment+360-beta;//3
			}
			else{
				if(delta>0)
					if(moment<0)
						degree=(180-beta)*moment+360-beta;
					else
						degree=beta*moment+360-beta;
				else
					if(moment<0)
						degree=-(180-beta)*moment+beta;
					else
						degree=(-beta)*moment+beta;
			}
			
			glRotatef(degree, 0,1,0);
			gluCylinder(myQuad, 0.1, 0.1, 3.5, N, 1);
		glPopMatrix();

		glPushMatrix(); //torus
			glTranslatef(0,1,1.3);
			glutSolidTorus(0.1, 0.15, 20, 20);
		glPopMatrix();

		glPushMatrix(); //2nd tube
			glTranslatef(0,1, 0.8);
			gluCylinder(myQuad, 0.1, 0.1, 1, N, 1);
		glPopMatrix();

		glPushMatrix(); //1st crank
			glTranslatef(0,0.5, 0.7);
			glScalef(2, 12, 2);
			glutSolidCube(0.1);
		glPopMatrix();

	glPopMatrix();

	glTranslatef(0,0, 0.3);
	gluCylinder(myQuad, 0.1, 0.1, 0.3, N, 1); //1st tube
glPopMatrix();
glPopAttrib();
	gluDeleteQuadric(myQuad);
}

void flywheel(float moment)
{
glPushAttrib(GL_ALL_ATTRIB_BITS);
	GLfloat cylinder_diffuse[] = { 0.5, 0.5, 0.5, 1.0 };
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, cylinder_diffuse);
	GLUquadricObj *myQuad;
	myQuad=gluNewQuadric();
	float degree;
	if(delta<0)
		degree=90*moment+270;
	else
		degree=-90*moment+90;

	glPushMatrix();
		glRotatef(degree, 0, 0, 1);
		glTranslatef(0,0, -0.3);
			glPushMatrix(); //cross inside
				glTranslatef(0,0,0.15);
				glScalef(1, 20, 3);
				glutSolidCube(0.1);
			glPopMatrix();
			glPushMatrix(); //cross inside
				glTranslatef(0,0,0.15);
				glScalef(20, 1, 3);
				glutSolidCube(0.1);
			glPopMatrix();
		gluCylinder(myQuad, 1, 1, 0.3, N, 1); //interior flywheel
		gluCylinder(myQuad, 1.5, 1.5, 0.3, N, 1); //exteror flywheel

		glPushMatrix();

			for(int i=0; i<36;i++)
			{
				glPushMatrix();
				
					glRotatef(i*10,0,0,1);
					glTranslatef(1.5,0,0.15);
					glScalef(0.5,1,1.5);
					glutSolidCube(0.15);
				glPopMatrix();
			}

		glPopMatrix();

		gluDisk(myQuad, 1, 1.5, N, N); //flywheel's lid
		glPushMatrix();
			glTranslatef(0,0, 0.6);
			glRotatef(180, 1, 0, 0);
			gluCylinder(myQuad, 0.1, 0.1, 0.9, N, 1); //distance between block and flywheel
		glPopMatrix();
		glTranslatef(0,0, 0.3);
		gluDisk(myQuad, 1, 1.5, N, N); //flywheel's lid
	glPopMatrix();
glPopAttrib();
	
	gluDeleteQuadric(myQuad);
}

void rackwheel(float moment)
{
	glPushMatrix();
	glPushAttrib(GL_ALL_ATTRIB_BITS);
		GLfloat cylinder_diffuse[] = { 0.5, 0.5, 0.5, 1.0 };
		glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, cylinder_diffuse);
		GLUquadricObj *myQuad;
		myQuad=gluNewQuadric();
		float degree;
		if(delta<0)
			degree=90*moment+270;
		else
			degree=-90*moment+90;
		glTranslatef(1.868, 1.868, -0.3);
		glRotatef(-degree, 0, 0, 1);
		gluCylinder(myQuad, 1, 1, 0.3, N, 1);
		gluDisk(myQuad, 0, 1, N, N); //flywheel's lid
		glPushMatrix();

			for(int i=0; i<18;i++)
			{
				glPushMatrix();
				
					glRotatef(i*20,0,0,1);
					glTranslatef(1,0,0.15);
					glScalef(1,4,1.5);
					glutSolidCube(0.15);
				glPopMatrix();
			}

		glPopMatrix();
		glPushMatrix();
			glTranslatef(0,0, 0.6);
			glRotatef(180, 1, 0, 0);
			gluCylinder(myQuad, 0.1, 0.1, 0.9, N, 1); //distance between block and flywheel
		glPopMatrix();
		glTranslatef(0,0, 0.3);
		gluDisk(myQuad, 0, 1, N, N); //flywheel's lid
	glPopAttrib();
	glPopMatrix();
	gluDeleteQuadric(myQuad);
}

void smallwheel(float moment)
{
	glPushMatrix();
	glPushAttrib(GL_ALL_ATTRIB_BITS);
		GLfloat cylinder_diffuse[] = { 0.5, 0.5, 0.5, 1.0 };
		glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, cylinder_diffuse);
		GLUquadricObj *myQuad;
		myQuad=gluNewQuadric();
		float degree;
		if(delta<0)
			degree=90*moment+270;
		else
			degree=-90*moment+90;
		glTranslatef(1.868, 1.868, -0.3);
		glRotatef(-degree*5, 0, 0, 1);
		gluCylinder(myQuad, 0.2, 0.2, 0.3, 6, 1);
		gluDisk(myQuad, 0.1, 0.2, 6, 6); //flywheel's lid

		glPushMatrix();
			glTranslatef(0,0, 0.6);
			glRotatef(180, 1, 0, 0);
			gluCylinder(myQuad, 0.1, 0.1, 0.6, N, 1); //distance between block and flywheel
		glPopMatrix();
		glTranslatef(0,0, 0.3);
		gluDisk(myQuad, 0.1, 0.2, 6, 6); //flywheel's lid
	glPopAttrib();
	glPopMatrix();
	gluDeleteQuadric(myQuad);
}

void cylinder(int *stroke, float moment, float delta, int type, float posX, float posY, float posZ){
	glPushMatrix();
	glPushAttrib(GL_ALL_ATTRIB_BITS);
		glRotatef(90, 1.0, 0, 0);
		glTranslatef(posX, posY, posZ); 
		
		
		piston (0, 0, moment*type);
		glowplug(moment, type, *stroke);
		valve(stroke, moment, delta, type, -0.3, 0, 0);
		valve(stroke, moment, delta, type, 0.3, 0, 0);
		
	glPopAttrib();
	glPopMatrix();
}

void set_delta(double value){
	delta=value;
}

double get_delta(){
	return delta;
}

void particles(int number, float moment, int type)
{ double x=0.0,y=0.0,z=0.0;
	for(int i=0; i<number;i++)
	{
		glPushMatrix();
			x=(rand()%20)/40.0-0.25;
			y=(rand()%20)/40.0-0.25;
			z=(rand()%170)/100.0;
			glTranslatef(x,y,z-0.2);
			glRotatef(rand()%90+1, 1,0,0);
			glRotatef(rand()%90+1, 0,1,0);
			glRotatef(rand()%90+1, 0,0,1);
			glRectf(-0.03, -0.03, 0.03, 0.03);
		glPopMatrix();
	}


}