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

//Triangles in counter clockwise order
int angle = 0;

int getAngle(){
	return angle;
}

void rotate(int deg){
	angle += 2;
	angle %= 360;
	glutPostRedisplay();
	glutTimerFunc(25, rotate, 0);
}


void drawScene(){
	glMatrixMode( GL_MODELVIEW );		// Setup model transformations
    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
    glEnable( GL_CULL_FACE );
	glCullFace( GL_BACK );
	
	drawAsteroid();
	drawTardis();
	drawDalek();
	
	glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-4, 4, -2, 2, -10, 10);
	
	glFlush();				// Flush OpenGL queue
    glutSwapBuffers();
}
	

int main(int argc, char *argv[]){
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    
    glutInitWindowSize(600, 300);
    glutCreateWindow("Asteroids Art");
    glutDisplayFunc( drawScene );
    glutTimerFunc(25, rotate, 0);
    glutMainLoop();			// Enter GLUT main loop
	return 1;
}
    
