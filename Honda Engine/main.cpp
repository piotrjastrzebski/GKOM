#include <GL/glut.h>
#include "display.h"
#include "scene_controls.h"
#include "moving_parts.h"

int main(int argc, char** argv)
{  
	glutInit( &argc, argv );
	glutInitDisplayMode( GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH );

	glutInitWindowPosition( 0, 0 );
	glutInitWindowSize( 600, 600 );

	glutCreateWindow( "Honda R18A2 i-VTEC engine" );
	glutDisplayFunc( display );
	glutReshapeFunc( reshape );

	glutIdleFunc(display);
	init();
	glutSpecialFunc (Keyboard);
	glutKeyboardFunc(Keyboard);
	
	glutMainLoop();
	return 0;
}