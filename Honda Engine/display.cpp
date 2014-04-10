#include <windows.h>
#include <iostream>

#include "scene_controls.h"
#include "moving_parts.h"
#include "display.h"

#include "tga.h"

GLuint TexID1, TexID2;

GLuint LoadTexture(char *TexName)
{	
	//std::cout<<"laduje texture"<<std::endl;
	TGAImg Img;
	GLuint Texture;

	if(Img.Load(TexName)!=IMG_OK)
		return -1;
 
	glGenTextures(1,&Texture);            // Allocate space for texture
	glBindTexture(GL_TEXTURE_2D,Texture); // Set our Tex handle as current
 
	// Create the texture
	if(Img.GetBPP()==24)
		glTexImage2D(GL_TEXTURE_2D,0,3,Img.GetWidth(),Img.GetHeight(),0,GL_RGB,GL_UNSIGNED_BYTE,Img.GetImg());
	else if(Img.GetBPP()==32)
		glTexImage2D(GL_TEXTURE_2D,0,4,Img.GetWidth(),Img.GetHeight(),0,GL_RGBA,GL_UNSIGNED_BYTE,Img.GetImg());
	else
		return -1;
 
	// Specify filtering and edge actions
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_CLAMP);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_CLAMP);
 
	return Texture;
}

void init()
{	
	
	GLfloat lightparam0[5][4] = //LIGHT0
	{
           {0,0,0,1},			//[0] swiatlo otoczenia
           {1,1,1,1},			//[1] swiatlo rozproszone
           {1,1,1,1},			//[2] swiatlo zwierciadlane
		   {0,0,0,1},			//[3] polozenie
		   {0,0,0,0}			//[4] kierunek swiecenia
	};    
	
	GLfloat lightparam1[5][4] = //LIGHT1
	{
           {0,0,0,1},			//[0] swiatlo otoczenia
           {1,1,1,1},			//[1] swiatlo rozproszone
           {1,1,1,1},			//[2] swiatlo zwierciadlane
		   {25,25,0,1},			//[3] polozenie
		   {0,0,0,0}			//[4] kierunek swiecenia
	};    

	GLfloat lightparam2[5][4] = //LIGHT2
	{
           {0,0,0,1},			//[0] swiatlo otoczenia
           {1,1,1,1},			//[1] swiatlo rozproszone
           {1,1,1,1},			//[2] swiatlo zwierciadlane
		   {-25,0,0,1},			//[3] polozenie
		   {0,0,0,0}			//[4] kierunek swiecenia
	}; 

	GLfloat lightparam3[5][4] = //LIGHT3-blysk
	{
		{1,1,0,1},			//[0] swiatlo otoczenia
		{1,1,0,1},			//[1] swiatlo rozproszone
		{1,1,0,1},			//[2] swiatlo zwierciadlane
		{0,0,0,1},			//[3] polozenie
		{0,0,0,0}			//[4] kierunek swiecenia
	};	

	glLightfv(GL_LIGHT3, GL_AMBIENT, lightparam3[0]);
	glLightfv(GL_LIGHT3, GL_DIFFUSE, lightparam3[1]);
	glLightfv(GL_LIGHT3, GL_SPECULAR, lightparam3[2]);
	glLightfv(GL_LIGHT3, GL_POSITION, lightparam3[3]);
	glLightfv(GL_LIGHT3, GL_SPOT_DIRECTION, lightparam3[4]);

	glLightfv(GL_LIGHT0, GL_AMBIENT, lightparam0[0]);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, lightparam0[1]);
	glLightfv(GL_LIGHT0, GL_SPECULAR, lightparam0[2]);
	glLightfv(GL_LIGHT0, GL_POSITION, lightparam0[3]);
	glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, lightparam0[4]);

	glLightfv(GL_LIGHT1, GL_AMBIENT, lightparam1[0]);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, lightparam1[1]);
	glLightfv(GL_LIGHT1, GL_SPECULAR, lightparam1[2]);
	glLightfv(GL_LIGHT1, GL_POSITION, lightparam1[3]);
	glLightfv(GL_LIGHT1, GL_SPOT_DIRECTION, lightparam1[4]);

	glLightfv(GL_LIGHT2, GL_AMBIENT, lightparam2[0]);
	glLightfv(GL_LIGHT2, GL_DIFFUSE, lightparam2[1]);
	glLightfv(GL_LIGHT2, GL_SPECULAR, lightparam2[2]);
	glLightfv(GL_LIGHT2, GL_POSITION, lightparam2[3]);
	glLightfv(GL_LIGHT2, GL_SPOT_DIRECTION, lightparam2[4]);
    
	//materialy
	GLfloat mat_ambient[]    = { 1.0, 1.0,  1.0, 1.0 };
	GLfloat mat_diffuse[] = { 1.0, 1.0,  1.0, 1.0 };
    GLfloat mat_specular[]   = { 1.0, 1.0,  1.0, 1.0 };
	glMaterialf( GL_FRONT_AND_BACK, GL_SHININESS, 50.0 );
	glMaterialfv( GL_FRONT_AND_BACK, GL_AMBIENT, mat_ambient );
	glMaterialfv( GL_FRONT_AND_BACK, GL_SPECULAR, mat_specular );
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, mat_diffuse);
	//materialy

	glShadeModel( GL_SMOOTH );
    glEnable( GL_LIGHTING );
	glEnable(GL_LIGHT0);
	glDepthFunc( GL_LESS );
    glEnable( GL_DEPTH_TEST );
	
	load(&TexID1, &TexID2);
}

void displayObjects(float moment, float delta)
{
	static int tactA=4, tactB=3, tactC=1, tactD=2;
	room(&TexID1, &TexID2);
	
	glTranslatef(0,2,0); //moving cylinders to the top

	glPushMatrix();
		glRotatef(90, 0, 1, 0);
		glTranslatef(0,-4.15,-4.3);
		flywheel(moment);
		rackwheel(moment);
		crankshaft(moment, delta, 1, 0, 0, 0); //draw crankshaft
		crankshaft(moment, delta, -1, 0, 0, 2);
		crankshaft(moment, delta, -1, 0, 0, 4);
		crankshaft(moment, delta, 1, 0, 0, 6);
		glPushMatrix();
			glTranslatef(-1,0.8,0);
			smallwheel(-moment);
		glPopMatrix();
	glPopMatrix();

	cylinder(&tactA, moment, delta, 1, -3, 0, 0);
	cylinder(&tactB, moment, delta, -1, -1, 0, 0);
	cylinder(&tactC, moment, delta, -1, 1, 0, 0);
	cylinder(&tactD, moment, delta, 1, 3, 0, 0);

	glEnable(GL_BLEND);
	glDepthMask(GL_FALSE);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		mixture(&tactA, moment,-3, 0, 0);
		mixture(&tactD, moment, 3, 0, 0);
		mixture(&tactB, -moment, -1, 0, 0);
		mixture(&tactC, -moment, 1, 0, 0);
		block(); //draw engine block
	glDepthMask(GL_TRUE);
	glDisable(GL_BLEND);
}

void display()
{	
	load_alternative_texture(get_o(), &TexID2);
	static float i=0.0;
	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
	glClearColor(0, 0, 0, 0);
	glLoadIdentity();
	scene();
	displayObjects(i, get_delta());
	
	if((i-1>DBL_MIN) || (i+1<-DBL_MIN))
		set_delta(get_delta()*(-1.0));
	i+=get_delta();
	glFlush();
	glutSwapBuffers();
}

void reshape(GLsizei w, GLsizei h)
{
	if( h > 0 && w > 0 ){
		glViewport( 0, 0, w, h );
		glMatrixMode( GL_PROJECTION );
		glLoadIdentity();
		if( w <= h )        
			glFrustum ( -1, 1, -1*h/w, 1*h/w, 1.5, 200.0);
		else
			glFrustum ( -1*w/h, 1*w/h, -1, 1, 1.5, 200.0);
		glMatrixMode( GL_MODELVIEW );		
    }
}


