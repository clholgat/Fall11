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

#include "tardish.h"

//Triangles in counter clockwise order
void rotate(int deg);

void drawPole(float pole[3], float points[][3]){
	for( int i = 0; i < 8; i++){
		glBegin( GL_LINE_LOOP );
    	glColor3f(1, 0, 0);
    	glVertex3fv(points[i]);
    	glVertex3fv(points[(i+1)%8]);
    	glVertex3fv(pole);
    	glEnd();
   	}
}

void drawAsteroid(){
	glMatrixMode( GL_MODELVIEW );		// Setup model transformations
    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
    glEnable( GL_CULL_FACE );
	glCullFace( GL_BACK );

    float poles[][3] = {
        { 1, 0, 0},
        { 0, 1, 0},
        {-1, 0, 0},
        { 0,-1, 0},
        { 0, 0, 1},
        { 0, 0,-1}
    };
    
    float xpos[][3] = {
        {0.717, 0.717, 0},
        {0.577, 0.577, 0.577},
        {0.717, 0, 0.717},
        {0.577, -0.577, 0.577},
        {0.717, -0.716, 0},
        {0.577, -0.577, -0.577},
        {0.717, 0, -0.717},
        {0.577, 0.577, -0.577}
    };
    
    float ypos[][3] = {
    	{0.717, 0.717, 0},
        {0.577, 0.577, -0.577},
        {0, 0.717, -0.717},
        {-0.577, 0.577, -0.577},
        {-0.717, 0.716, 0},
        {-0.577, 0.577, 0.577},
        {0, 0.717, 0.717},
        {0.577, 0.577, 0.577}
    };
    	
    float xneg[][3] = {
        {-0.577, 0.577, -0.577},
        {-0.717, 0, -0.717},
        {-0.577, -0.577, -0.577},
        {-0.717, -0.716, 0},
        {-0.577, -0.577, 0.577},
        {-0.717, 0, 0.717},
        {-0.577, 0.577, 0.577},
        {-0.717, 0.717, 0}
    };
    
    float yneg[][3] = {
    	{0.577, -0.577, 0.577},
    	{0, -0.717, 0.717},
    	{-0.577, -0.577, 0.577},
    	{-0.717, -0.716, 0},
    	{-0.577, -0.577, -0.577},
        {0, -0.717, -0.717},
        {0.577, -0.577, -0.577},
    	{0.717, -0.717, 0},
    };
    
    float zpos[][3] = {
    	{0.577, 0.577, 0.577},
    	{0, 0.717, 0.717},
    	{-0.577, 0.577, 0.577},
    	{-0.717, 0, 0.717},
    	{-0.577, -0.577, 0.577},
    	{0, -0.717, 0.717},
    	{0.577, -0.577, 0.577},
    	{0.717, 0, 0.717}
    };
    
    float zneg[][3] = {
    	{0.717, 0, -0.717},
    	{0.577, -0.577, -0.577},
    	{0, -0.717, -0.717},
    	{-0.577, -0.577, -0.577},
    	{-0.717, 0, -0.717},
    	{-0.577, 0.577, -0.577},
    	{0, 0.717, -0.717},
    	{0.577, 0.577, -0.577}
    };

    
    
    glPushMatrix();
    	
    drawPole(poles[0], xpos);
    drawPole(poles[1], ypos);
    drawPole(poles[2], xneg);
    drawPole(poles[3], yneg);
    drawPole(poles[4], zpos);
    drawPole(poles[5], zneg);
    
    glPopMatrix();
    glFlush();				// Flush OpenGL queue
    glutSwapBuffers();	
           
}

int main(int argc, char *argv[]){
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    
    glutCreateWindow("Asteroids Art");
    glutDisplayFunc( drawTardis );
    glutIdleFunc(&drawTardis);
    glutMainLoop();			// Enter GLUT main loop
	return 1;
}
    
