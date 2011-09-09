#ifdef _M_IX86
#include <windows.h>
#else
#include <iostream>
#endif

#include "asteroid.h"
#include "asteroids.h"

#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>


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
/*	Original copy of these points
	float tweak[][3] = {
		{0.717, 0.717, 0},
		{-0.577, 0.577, 0.577},
		{-0.717, -0.716, 0},
		{0, 0.717, -0.717},
		{0.577, -0.577, -0.577},
		{-1, 0, 0},
		{ 0, 0, 1}
	};
*/

	float tweak[][3] = {
		{0.717, 0.68, 0.2},
		{-0.788, 0.577, 0.46},
		{-0.50, -0.99, -0.1},
		{0, 0.624, -0.717},
		{0.788, -0.447, -0.577},
		{-1.3, 0, 0},
		{ 0, 0, 0.6}
	};


    float poles[][3] = {
        { 1, 0, 0},
        { 0, 1, 0},
        {tweak[5][0], tweak[5][1], tweak[5][2]},
        { 0,-1, 0},
        {tweak[6][0], tweak[6][1], tweak[6][2]},
        { 0, 0,-1}
    };
    
    float xpos[][3] = {
        {tweak[0][0], tweak[0][1], tweak[0][2]},
        {0.577, 0.577, 0.577},
        {0.717, 0, 0.717},
        {0.577, -0.577, 0.577},
        {0.717, -0.716, 0},
        {tweak[4][0], tweak[4][1], tweak[4][2]},
        {0.717, 0, -0.717},
        {0.577, 0.577, -0.577}
    };
    
    float ypos[][3] = {
    	{tweak[0][0], tweak[0][1], tweak[0][2]},
        {0.577, 0.577, -0.577},
        {tweak[3][0], tweak[3][1], tweak[3][2]},
        {-0.577, 0.577, -0.577},
        {-0.717, 0.716, 0},
        {tweak[1][0], tweak[1][1], tweak[1][2]},
        {0, 0.717, 0.717},
        {0.577, 0.577, 0.577}
    };
    	
    float xneg[][3] = {
        {-0.577, 0.577, -0.577},
        {-0.717, 0, -0.717},
        {-0.577, -0.577, -0.577},
        {tweak[2][0], tweak[2][1], tweak[2][2]},
        {-0.577, -0.577, 0.577},
        {-0.717, 0, 0.717},
        {tweak[1][0], tweak[1][1], tweak[1][2]},
        {-0.717, 0.717, 0}
    };
    
    float yneg[][3] = {
    	{0.577, -0.577, 0.577},
    	{0, -0.717, 0.717},
    	{-0.577, -0.577, 0.577},
    	{tweak[2][0], tweak[2][1], tweak[2][2]},
    	{-0.577, -0.577, -0.577},
        {0, -0.717, -0.717},
        {tweak[4][0], tweak[4][1], tweak[4][2]},
    	{0.717, -0.717, 0},
    };
    
    float zpos[][3] = {
    	{0.577, 0.577, 0.577},
    	{0, 0.717, 0.717},
    	{tweak[1][0], tweak[1][1], tweak[1][2]},
    	{-0.717, 0, 0.717},
    	{-0.577, -0.577, 0.577},
    	{0, -0.717, 0.717},
    	{0.577, -0.577, 0.577},
    	{0.717, 0, 0.717}
    };
    
    float zneg[][3] = {
    	{0.717, 0, -0.717},
    	{tweak[4][0], tweak[4][1], tweak[4][2]},
    	{0, -0.717, -0.717},
    	{-0.577, -0.577, -0.577},
    	{-0.717, 0, -0.717},
    	{-0.577, 0.577, -0.577},
    	{tweak[3][0], tweak[3][1], tweak[3][2]},
    	{0.577, 0.577, -0.577}
    };

    
    
    glPushMatrix();
    glTranslatef(-2, 0, 0);
    glRotatef(getAngle(), 0, 1, 0);	
    	
    drawPole(poles[0], xpos);
    drawPole(poles[1], ypos);
    drawPole(poles[2], xneg);
    drawPole(poles[3], yneg);
    drawPole(poles[4], zpos);
    drawPole(poles[5], zneg);
    
    glPopMatrix();
	
           
}
