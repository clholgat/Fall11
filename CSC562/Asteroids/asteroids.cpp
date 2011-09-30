#ifdef _M_IX86
#include <windows.h>
#else
#include <iostream>
#endif

#include <string.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <math.h>

#include "tardis.h"
#include "asteroid.h"
#include "dalek.h"
#include "asteroids.h"
#include "draw.h"

//Triangles in counter clockwise order
int angle = 0;

int getAngle(){
	return angle;
}

// dz = two[0]-one[0], two[1]-one[1], two[2]-one[2]
// do = three[0]-two[0], three[1]-two[1], three[2]-two[2]

float *norm(float one[], float two[], float three[]){
	float *ret = (float *)malloc(sizeof(float)*3);
	ret[0] = (two[1]-one[1])*(three[2]-two[2])-(two[2]-one[2])*(three[1]-two[1]);
	ret[1] = (two[2]-one[2])*(three[0]-two[0])-(two[0]-one[0])*(three[2]-two[2]);
	ret[2] = (two[0]-one[0])*(three[1]-two[1])-(two[1]-one[1])*(three[0]-two[0]);
	return ret;
}

void rotate(int deg){
	angle += 2;
	angle %= 360;
	glutPostRedisplay();
	glutTimerFunc(25, rotate, 0);
}
	
	
void handle_menu(int ID){
	switch(ID){
		case 0:
			exit(0);
	}
}

void reshape(int w, int h){
	glMatrixMode(GL_PROJECTION);     // Select The Projection Matrix
	glLoadIdentity();                // Reset The Projection Matrix
	// Calculate The Aspect Ratio And Set The Clipping Volume
	if (h == 0) h = 1;
	glOrtho(-w/80, w/80, -h/80, h/80, -10, 10);
	glMatrixMode( GL_MODELVIEW );		// Setup model transformations
 	glLoadIdentity();
  	gluLookAt( 0, 0, 5, 0, 0, -1, 0, 1, 0 );             // Reset The Modelview Matrix
}

int main(int argc, char *argv[]){
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    
    int width = 600;
    int height = 600;
    glutInitWindowSize(width, height);
    glutCreateWindow("Asteroids Art");
    glutDisplayFunc( drawScene );  	
    
    glMatrixMode( GL_MODELVIEW );		// Setup model transformations
    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
    glEnable( GL_CULL_FACE );
	glCullFace( GL_BACK );
	glShadeModel( GL_FLAT );		// Flat shading
  	glEnable( GL_NORMALIZE );		// Normalize normals
  	glEnable(GL_COLOR_MATERIAL);

  	glClearDepth( 1.0 );			// Setup background colour
  	glClearColor( 0, 0, 0, 0 );
  	glEnable( GL_DEPTH_TEST );
	
	glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-width/80, width/80, -height/80, height/80, -10, 10);
    
    glMatrixMode( GL_MODELVIEW );		// Setup model transformations
 	glLoadIdentity();
  	gluLookAt( 0, 0, 5, 0, 0, -1, 0, 1, 0 );
	
    glutCreateMenu(handle_menu);
    glutAddMenuEntry("Quit", 0);
    glutAttachMenu(GLUT_RIGHT_BUTTON);
    glutReshapeFunc(reshape);
    glutSpecialFunc(specialKeys);
    glutKeyboardFunc(keys);
    
    glutTimerFunc(35, rotate, 0);
    glutMainLoop();			// Enter GLUT main loop
	return 1;
}
    
