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
#include <stdlib.h>

#include "tardis.h"
#include "asteroid.h"
#include "dalek.h"
#include "asteroids.h"

Props Tardis;
Props Shots[4];
Props Ast[4];
int first = 1;
int frames = 0;
int w;
int h;

void wrap(Props obj){
	w = glutGet(GLUT_WINDOW_WIDTH);
	h = glutGet(GLUT_WINDOW_HEIGHT);
	
	if(obj->pos[0] > w/80){
		obj->pos[0] = -w/80;
	}else if(obj->pos[0] < -w/80){
		obj->pos[0] = w/80;
	}
	if(obj->pos[1] > h/80){
		obj->pos[1] = -h/80;
	}else if(obj->pos[1] < -h/80){
		obj->pos[1] = h/80;
	}
}

void update(){
	Tardis->pos[0] += (Tardis->velocity/4)*cos(Tardis->movDir*0.017);
	Tardis->pos[1] += (Tardis->velocity/4)*sin(Tardis->movDir*0.017);
	
	frames = (frames+1)%10;
	if(frames == 0){
		Tardis->velocity -= 1;
	}
	if(Tardis->velocity <= 0){
		Tardis->velocity = 0;
	}
	wrap(Tardis);
	
	for(int i = 0; i < 4; i++){
		if(Shots[i] == NULL){
			continue;
		}
		Shots[i]->pos[0] += (Shots[i]->velocity/4)*cos(Shots[i]->dir*0.017);
		Shots[i]->pos[1] += (Shots[i]->velocity/4)*sin(Shots[i]->dir*0.017);
		wrap(Shots[i]);
	}
	
	for(int i = 0; i < 4; i++){
		Ast[i]->pos[0] += (Ast[i]->velocity/4)*cos(Ast[i]->dir*0.017);
		Ast[i]->pos[1] += (Ast[i]->velocity/4)*sin(Ast[i]->dir*0.017);
		Ast[i]->ang += Ast[i]->wonky->rate;
		Ast[i]->ang %= 360;
		wrap(Ast[i]);
	}
}

void setupTardis(){
	w = glutGet(GLUT_WINDOW_WIDTH);
	h = glutGet(GLUT_WINDOW_HEIGHT);
	
	Tardis = (Props)malloc(sizeof(struct props));
	Tardis->movDir = 90;
	Tardis->pos[0] = 0;
	Tardis->pos[1] = 0;
	Tardis->dir = 90;
	Tardis->velocity = 0;
	Tardis->wonky = NULL;
	
	
	for(int i = 0; i < 4; i++){
		Shots[i] = NULL;
	}
	
	for(int i = 0; i < 4; i++){
		Ast[i] = (Props)malloc(sizeof(struct props));
		Ast[i]->pos[0] = (rand()%w) - w/2;
		Ast[i]->pos[1] = (rand()%h) - h/2;
		Ast[i]->dir = rand()%360;
		Ast[i]->velocity = rand()%3;
		Ast[i]->wonky = (Spin)malloc(sizeof(struct spin));
		Ast[i]->wonky->axis[0] = rand();
		Ast[i]->wonky->axis[1] = rand();
		Ast[i]->wonky->axis[2] = rand();
		Ast[i]->wonky->rate = rand()%10;
		Ast[i]->ang = 0;
	}
}

void specialKeys(int key, int x, int y){
	float th = 0;
	switch(key){
		case GLUT_KEY_LEFT:
			Tardis->dir += 4;
			break;
		case GLUT_KEY_RIGHT:
			Tardis->dir -= 4;
			break;
		default:
			break;
	}
}

void keys(unsigned char key, int x, int y){
	int vel = Tardis->velocity;
	float movx = vel*cos(Tardis->movDir*0.0175);
	float movy = vel*sin(Tardis->movDir*0.0175);
	float xx = 2*cos(Tardis->dir*0.0175);
	float yy = 2*sin(Tardis->dir*0.0175);
	float xs = 3*cos(Tardis->dir*0.0175);
	float ys = 3*sin(Tardis->dir*0.0175);
	float mag = sqrt((xx+movx)*(xx+movx)+(yy+movy)*(yy+movy));
	float mags = sqrt((xs+movx)*(xs+movx)+(ys+movy)*(ys+movy));
	float normx = (movx+xx)/mag;
	float normy = (movy+yy)/mag;
	float normxs = (movx+xs)/mags;
	float normys = (movy+ys)/mags;
	float delta = 0.001;
	switch(key){
		case 'x':	
			Tardis->movDir = acos(normx)*57.296;
			if(normx < 0+delta && normy < 0+delta){
				Tardis->movDir = -Tardis->movDir;
			}else if(normx > 0-delta && normy < 0+delta){
				Tardis->movDir = -Tardis->movDir;
			}
			Tardis->velocity = mag;
			if(Tardis->velocity > 6){
				Tardis->velocity = 6;
			}
			break;
		case 'z':
			for(int i = 0; i < 4; i++){
				if(Shots[i] == NULL){
					Shots[i] = (Props)malloc(sizeof(struct props));
					Shots[i]->pos[0] = Tardis->pos[0];
					Shots[i]->pos[1] = Tardis->pos[1];
					Shots[i]->dir = acos(normxs)*57.296;
					if(normxs < 0+delta && normys < 0+delta){
						Shots[i]->dir = -Shots[i]->dir;
					}else if(normxs > 0-delta && normys < 0+delta){
						Shots[i]->dir = -Shots[i]->dir;
					}
					Shots[i]->velocity = mag;
					break;
				}
			}
			break;
		default:
			break;
	}
}

void drawScene(){
	if(first){
		setupTardis();
		first = 0;
	}else{
		update();
	}
	glMatrixMode( GL_MODELVIEW );
	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
	
	glPushMatrix();
	glLoadIdentity();
	
	float  amb[] = { 0, 0, 0, 1 };	// Ambient material property
	float  lt_amb[] = { .2, .2, .2, 1 };	// Ambient light property
  	float  lt_dif[] = { .8, .8, .8, 1 };	// Ambient light property
  	float  lt_pos[] = {0, .39392, .91914, 0};
  	float  lt_spc[] = { 0, 0, 0, 1 };	// Specular light property
  	
  	glEnable( GL_LIGHT0 );
  	glEnable( GL_LIGHTING );
	glLightModelfv( GL_LIGHT_MODEL_AMBIENT, amb );

  	glLightfv( GL_LIGHT0, GL_POSITION, lt_pos );
  	glLightfv( GL_LIGHT0, GL_AMBIENT, lt_amb );
  	glLightfv( GL_LIGHT0, GL_DIFFUSE, lt_dif );
  	glLightfv( GL_LIGHT0, GL_SPECULAR, lt_spc );
	
	glPopMatrix();
	
	drawTardis(Tardis);
	drawShots(Shots);
	for(int i = 0; i < 4; i++){
		drawAsteroid(Ast[i], Ast[i]->ang);
	}
	//drawAsteroid();
	//drawDalek();
	
	glFlush();				// Flush OpenGL queue
    glutSwapBuffers();
}
