#include "tardis.h"
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <stdio.h>

int angle = 0;

void drawTardis(){
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glPushMatrix();
    glScalef(0.9, 0.9, 0.9);
    glRotatef(angle, 0, 1, .2);
    angle += 1;
    
    int pointLen = tardisLen/4;
    for(int i = 0; i < pointLen; i++){
    	glBegin( GL_LINE_LOOP );
    	glColor3f(1, 0, 0);
    	for(int j = 0; j < 4; j++){
    		glVertex3fv(tardisRect[(i*4)+j]);
    	}
    	glEnd();
    }
    
    glPopMatrix();
    glFlush();				// Flush OpenGL queue
    glutSwapBuffers();	
}
