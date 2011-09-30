#ifdef _M_IX86
#include <windows.h>
#else
#include <iostream>
#endif

#include "tardis.h"
#include "asteroids.h"
#include "dalek.h"
#include "draw.h"
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <stdio.h>
#include <math.h>


int tardisLen = 44;

float tardisRect[][3] = {
	{0.66, 1, 0.66},	//front
	{0.66, -1, 0.66},
	{-0.66, -1, 0.66},
	{-0.66, 1, 0.66},
	
	{-0.66, 1, -0.66},	//back
	{-0.66, -1, -0.66},
	{0.66, -1, -0.66},
	{0.66, 1, -0.66},
	
	{0.66, 1, -0.66},	//right
	{0.66, -1, -0.66},
	{0.66, -1, 0.66},
	{0.66, 1, 0.66},
	
	{-0.66, 1, 0.66},	//left
	{-0.66, -1, 0.66},
	{-0.66, -1, -0.66},
	{-0.66, 1, -0.66},
	
	{0.66, 1, 0.66},	//top
	{-0.66, 1, 0.66},
	{-0.66, 1, -0.66},
	{0.66, 1, -0.66},
	
	{0.66, -1, 0.66},	//bottom
	{0.66, -1, -0.66},
	{-0.66, -1, -0.66},
	{-0.66, -1, 0.66},
	
	{0.5, 1.2, 0.5}, 	//top thing (tt) front
	{0.5, 1, 0.5},
	{-0.5, 1, 0.5},
	{-0.5, 1.2, 0.5},
	
	{-0.5, 1.2, -0.5},	//tt back
	{-0.5, 1, -0.5},
	{0.5, 1, -0.5},
	{0.5, 1.2, -0.5},
	
	{0.5, 1.2, -0.5},	//tt left
	{0.5, 1, -0.5},
	{0.5, 1, 0.5},
	{0.5, 1.2, 0.5},
	
	{-0.5, 1.2, 0.5},	//tt left
	{-0.5, 1, 0.5},
	{-0.5, 1, -0.5},
	{-0.5, 1.2, -0.5},
	
	{0.5, 1.2, 0.5},	//tt top
	{-0.5, 1.2, 0.5},
	{-0.5, 1.2, -0.5},
	{0.5, 1.2, -0.5}
};

void drawPointer(){
	glColor3f(0.2, 0.2, 0.2);
	glutSolidTorus(0.05, 1.2, 20, 20);
	glBegin(GL_TRIANGLES);
	glColor3f(1, 1, 0.2);
	glNormal3f(0, 0, 1);
	glVertex3f(-.5, 1.3, 0);
	glVertex3f(.5, 1.3, 0);
	glVertex3f(0, 2, 0);
	glEnd();
}

void drawTardis(Props Tardis){
	glMatrixMode( GL_MODELVIEW );		// Setup model transformations

  	glPushMatrix();
  	
  	glTranslatef(Tardis->pos[0], Tardis->pos[1], 0);
  	glRotatef(Tardis->dir-90,0, 0, 1);
  	
  	drawPointer();
  	glRotatef(90, 1, 0, 0);
    glScalef(0.9, 0.9, 0.9);
    glRotatef(getAngle(), .2, 1, .2);
    
    int pointLen = tardisLen/4;
    for(int i = 0; i < pointLen; i++){
    	glBegin( GL_QUADS );
    	glNormal3fv(norm(tardisRect[i*4], tardisRect[i*4+1], tardisRect[i*4+2]));
    	//glColor3f(0.129, 0.024, 0.392);
    	glColor3f(0, 0.234, 0.410);
    	for(int j = 0; j < 4; j++){
    		glVertex3fv(tardisRect[(i*4)+j]);
    	}
    	glEnd();
    }
    glPopMatrix();
	glFlush();				// Flush OpenGL queue
	

}

void drawShots(Props Shots[4]){
	glMatrixMode(GL_MODELVIEW);
	for(int i = 0; i < 4; i++){
		if(Shots[i] == NULL){
			continue;
		}
		glPointSize(5);
		glBegin(GL_POINTS);
		glColor3f(1, 1, 1);
		glNormal3f(0, 0, 1);
		glVertex3f(Shots[i]->pos[0], Shots[i]->pos[1], 0);
		glEnd();
	}
}
		
	
