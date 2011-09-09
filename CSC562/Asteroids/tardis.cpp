#ifdef _M_IX86
#include <windows.h>
#else
#include <iostream>
#endif

#include "tardis.h"
#include "asteroids.h"
#include "dalek.h"
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <stdio.h>


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

void drawTardis(){
    glPushMatrix();
    glScalef(0.9, 0.9, 0.9);
    glRotatef(getAngle(), .2, 1, 0);
    
    int pointLen = tardisLen/4;
    for(int i = 0; i < pointLen; i++){
    	glBegin( GL_LINE_LOOP );
    	//glColor3f(0.129, 0.024, 0.392);
    	glColor3f(1, 0, 0);
    	for(int j = 0; j < 4; j++){
    		glVertex3fv(tardisRect[(i*4)+j]);
    	}
    	glEnd();
    }
    
    glPopMatrix();

}
