#ifdef _M_IX86
#include <windows.h>
#else
#include <iostream>
#endif

#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <stdlib.h>
#include <time.h>

#include "asteroid.h"

Asteroid::Asteroid(float size){
	rad = size;
	return;
}

void Asteroid::init(int num){
	srand(num);
	
	float max = RAND_MAX/1.5;
	
	poles = {
        { ((float)rand()/max), 0, 0},
        { 0, ((float)rand()/max), 0},
        {-((float)rand()/max), 0, 0},
        { 0,-((float)rand()/max), 0},
        { 0, 0, ((float)rand()/max)},
        { 0, 0,-((float)rand()/max)},
    };
    
    for(int i = 0; i < 6; i++){
    	for(int j = 0; j < 3; j++){
    		poles[i][j] *= rad;
    	}
    }
    
    xpos = {
        {0.717, 0.717, 0},
        {0.577, 0.577, 0.577},
        {0.717, 0, 0.717},
        {0.577, -0.577, 0.577},
        {0.717, -0.716, 0},
        {0.577, -0.577, -0.577},
        {0.717, 0, -0.717},
        {0.577, 0.577, -0.577}
    };
    
    ypos = {
    	{0.717, 0.717, 0},
        {0.577, 0.577, -0.577},
        {0, 0.717, -0.717},
        {-0.577, 0.577, -0.577},
        {-0.717, 0.716, 0},
        {-0.577, 0.577, 0.577},
        {0, 0.717, 0.717},
        {0.577, 0.577, 0.577}
    };
    	
    xneg = {
        {-0.577, 0.577, -0.577},
        {-0.717, 0, -0.717},
        {-0.577, -0.577, -0.577},
        {-0.717, -0.716, 0},
        {-0.577, -0.577, 0.577},
        {-0.717, 0, 0.717},
        {-0.577, 0.577, 0.577},
        {-0.717, 0.717, 0}
    };
    
    yneg = {
    	{0.577, -0.577, 0.577},
    	{0, -0.717, 0.717},
    	{-0.577, -0.577, 0.577},
    	{-0.717, -0.716, 0},
    	{-0.577, -0.577, -0.577},
        {0, -0.717, -0.717},
        {0.577, -0.577, -0.577},
    	{0.717, -0.717, 0},
    };
    
    zpos = {
    	{0.577, 0.577, 0.577},
    	{0, 0.717, 0.717},
    	{-0.577, 0.577, 0.577},
    	{-0.717, 0, 0.717},
    	{-0.577, -0.577, 0.577},
    	{0, -0.717, 0.717},
    	{0.577, -0.577, 0.577},
    	{0.717, 0, 0.717}
    };
    
    zneg = {
    	{0.717, 0, -0.717},
    	{0.577, -0.577, -0.577},
    	{0, -0.717, -0.717},
    	{-0.577, -0.577, -0.577},
    	{-0.717, 0, -0.717},
    	{-0.577, 0.577, -0.577},
    	{0, 0.717, -0.717},
    	{0.577, 0.577, -0.577}
    };
    
    for(int i = 0; i < 8; i++){
    	for(int j = 0; j < 3; j++){
    		xpos[i][j] *= rad;
    		xneg[i][j] *= rad;
    		ypos[i][j] *= rad;
    		yneg[i][j] *= rad;
    		zpos[i][j] *= rad;
    		zneg[i][j] *= rad;
    	}
    }
    
	wrap();
}

void Asteroid::drawPole(float pole[3], float points[][3]){
	for( int i = 0; i < 8; i++){
		glBegin( GL_TRIANGLES );
		glNormal3fv(norm(points[i], points[(i+1)%8], pole));
    	glColor3f(0.804+0.01*i, 0.522-0.01*i, 0.247+0.01*i);
    	glVertex3fv(points[i]);
    	glVertex3fv(points[(i+1)%8]);
    	glVertex3fv(pole);
    	glEnd();
   	}
}

void Asteroid::draw(){
    glMatrixMode( GL_MODELVIEW );		// Setup model transformations
    glPushMatrix();
    
    applyTrans();
    	
    drawPole(poles[0], xpos);
    drawPole(poles[1], ypos);
    drawPole(poles[2], xneg);
    drawPole(poles[3], yneg);
    drawPole(poles[4], zpos);
    drawPole(poles[5], zneg);
    
    glPopMatrix();
	glFlush();				// Flush OpenGL queue
           
}
