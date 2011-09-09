#ifdef _M_IX86
#include <windows.h>
#else
#include <iostream>
#endif

#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <stdio.h>
#include "dalek.h"
#include "asteroids.h"

#define BOT -1
#define TOP 0.8

void drawBase(float base[][3], float y){
	float pole[3] = {0, y, 0};
	for(int i = 0; i < 9; i++){
		glBegin(GL_LINE_LOOP);
		glColor3f(1, 0, 0);
		glVertex3fv(base[i]);
		glVertex3fv(base[(i+1)%9]);
		glVertex3fv(pole);
		glEnd();
	}
}

int mod(int num, int mod){
	return (num + mod)%mod;
}

void drawSides(float top[][3], float bot[][3]){
	int j = 0;
	for(int i = 0; i < 9; i++){
		j = 8-i;
		glBegin(GL_LINE_LOOP);
		glColor3f(1, 0 , 0);
		glVertex3fv(top[i]);
		glVertex3fv(top[mod(i+1,9)]);
		glVertex3fv(bot[mod(j-1, 9)]);
		glVertex3fv(bot[j]);
		glEnd();
	}
}
		
void drawSph(float top[][3], float bot[][3]){
	float cent[3] = {-0.8, -0.5, -0.2};
	double midTop[2];
	double midBot[2];
	double slopeX = 0;
	double slopeZ = 0;
	double x = 0;
	double z = 0;
	int j = 0;
	for(int i = 0; i < 9; i++){
		j = 8-i;
		midTop = {(top[i][0] + top[mod(i+1,9)][0])/2, (top[i][2] + top[mod(i+1,9)][2])/2};
		midBot = {(bot[j][0] + bot[mod(j-1,9)][0])/2, (bot[j][2] + bot[mod(j-1,9)][2])/2};
		slopeX = (TOP-BOT)/(midTop[0]-midBot[0]);
		slopeZ = (TOP-BOT)/(midTop[1]-midBot[1]);
		
		for(int k = 0; k < 3; k++){
			x = midBot[0] + (1+cent[k])*(1/slopeX);
			z = midBot[1] + (1+cent[k])*(1/slopeZ);
			
			glTranslatef(x, cent[k], z);
			glutWireSphere(0.1, 10, 10);
			glTranslatef(-x, -cent[k], -z);
		}
	}
}

void drawHead(){
	glPushMatrix();
	glTranslatef(0, TOP+0.1, 0.05);
	glutWireSphere(0.52, 10, 10);
	//glTranslatef(0, -(TOP+0.1), -0.05);
	glPopMatrix();
	
	glPushMatrix();
	glTranslatef(0, TOP-0.3, 0.05);
	glRotatef(90, 1, 0, 0);
	glutWireTorus(0.02, 0.6, 10, 10);
	glTranslatef(0, 0, 0.25);
	glutWireTorus(0.02, 0.69, 10, 10);
	glPopMatrix();
}

void drawThing(float len, float scale){
	float armBot[][3] = {
		{1, 0, 0.5},
		{0.5, 0, 1},
		{-0.5, 0, 1},
		{-1, 0, 0.5},
		{-1, 0, -0.5},
		{-0.5, 0, -1},
		{0.5, 0, -1},
		{1, 0, -0.5},
	};
	
	float armTop[8][3] = {
		{1, len, -0.5},
		{0.5, len, -1},
		{-0.5, len, -1},
		{-1, len, -0.5},
		{-1, len, 0.5},
		{-0.5, len, 1},
		{0.5, len, 1},
		{1, len, 0.5},
	};
	
	for(int i = 0; i < 8; i++){
		for(int j = 0; j < 3; j += 2){
			armTop[i][j] *= scale;
			armBot[i][j] *= scale;
		}
	}
	
	int j = 0;
	for(int i = 0; i < 8; i++){
		j = 7-i;
		glBegin(GL_LINE_LOOP);
		glColor3f(1, 0 , 0);
		glVertex3fv(armTop[i]);
		glVertex3fv(armTop[mod(i+1,8)]);
		glVertex3fv(armBot[mod(j-1,8)]);
		glVertex3fv(armBot[j]);
		glEnd();
	}
	
}

void drawArms(){
	glPushMatrix();
	glTranslatef(-0.2, 0.3, -0.2);
	glRotatef(110, -1, 1, 0);
	drawThing(1.2, 0.03);
	glPopMatrix();
	
	glPushMatrix();
	glTranslatef(0.2, 0.3, -0.2);
	glRotatef(130, -1, -1, 0);
	drawThing(1.2, 0.03);
	glTranslatef(0, 1.2, 0);
	glutWireSphere(0.1, 10, 10);
	glPopMatrix();
	
	glPushMatrix();
	glTranslatef(0.3, 1.3, 0);
	glRotatef(30, 0, 0, -1);
	drawThing(0.15, 0.1);
	glPopMatrix();
	
	glPushMatrix();
	glTranslatef(-0.3, 1.3, 0);
	glRotatef(30, 0, 0, 1);
	drawThing(0.15, 0.1);
	glPopMatrix();
	
	glPushMatrix();
	glTranslatef(0, 0.8, -0.8);
	glRotatef(100, 1, 0, 0);
	drawThing(0.4, 0.03);
	glTranslatef(0, 0, 0);
	glutWireSphere(0.1, 10, 10);
	glPopMatrix();
}


void drawDalek(){
	float dalekBase[][3] = {
		{0.6, BOT, 1},
		{.8, BOT, 0.7},
		{.8, BOT, 0},
		{0.6, BOT, -0.6},
		{0, BOT, -1},
		{-0.6, BOT, -0.6},
		{-.8, BOT, -0},
		{-.8, BOT, 0.7},
		{-.6, BOT, 1},
	};
	
	/*float dalekTop[][3] = {
		{-0.5, TOP, 0.8},
		{-0.75, TOP, 0.5},
		{-0.75, TOP, 0},
		{-0.6, TOP, -0.5},
		{0, TOP, -0.75},
		{0.6, TOP, -0.5},
		{0.75, TOP, 0},
		{0.75, TOP, 0.5},
		{.5, TOP, 0.8},
	};*/
	
	float dalekTop[][3] =  {
		{-0.6, TOP, 1},
		{-.8, TOP, 0.7},
		{-.8, TOP, 0},
		{-0.6, TOP, -0.6},
		{0, TOP, -1},
		{0.6, TOP, -0.6},
		{.8, TOP, -0},
		{.8, TOP, 0.7},
		{.6, TOP, 1},
	};
	
	float scalef = .4;
	for(int i = 0; i < 9; i++){
		for(int j = 0; j < 3; j += 2){
			dalekTop[i][j] = dalekTop[i][j]*scalef;
		}
	}
		
	glPushMatrix();
	glTranslatef(2, 0, 0);
	glScalef(0.9, 0.9, 0.9);
	glRotatef(getAngle(), .2, 1, .2);
	
	drawBase(dalekBase, BOT);
	drawBase(dalekTop, TOP);
	drawSides(dalekTop, dalekBase);
	drawSph(dalekTop, dalekBase);
	drawHead();
	drawArms();
	
	glPopMatrix();
}
