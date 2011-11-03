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
#include <list>

#include "tardis.h"
#include "asteroid.h"
#include "dalek.h"
#include "asteroids.h"
#include "explosion.h"

using namespace std;

int w;
int h;
double timer = 0;
bool firstT = true;
Tardis tardis;
list<Asteroid*> asteroids;
list<Asteroid*>::iterator itA;
list<Explosion*> explosions;
list<Explosion*>::iterator itE;

void idle(){
	timer += 0.5;
	tardis.update();
	for(itA = asteroids.begin(); itA != asteroids.end(); itA++){
		(**itA).update();
	}
	for(itA = asteroids.begin(); itA != asteroids.end(); itA++){
		if(tardis.checkTardis((*itA))){
			if((**itA).rad <= 2.0/4.0){
			}else{
				Asteroid *newA = new Asteroid((**itA).rad/2);
				Asteroid *newB = new Asteroid((**itA).rad/2);
				(*newA).modelInit(rand());
				(*newA).init(rand());
				(*newB).modelInit(rand());
				(*newB).init(rand());
				printf("%f\n", (**itA).rad/2);
				(*newA).pos[0] = (**itA).pos[0];
				(*newA).pos[1] = (**itA).pos[1];
				(*newB).pos[0] = (**itA).pos[0];
				(*newB).pos[1] = (**itA).pos[1];
				asteroids.push_back(newA);
				asteroids.push_back(newB);
			}
			explosions.push_back(new Explosion((**itA).pos[0], (**itA).pos[1]));
			delete (*itA);
			itA = asteroids.erase(itA);
			if(asteroids.empty()){
				firstT = true;
			}
		}
		if(tardis.checkShots((*itA))){
			if((**itA).rad <= 2.0/4.0){
			}else{
				Asteroid *newA = new Asteroid((**itA).rad/2);
				Asteroid *newB = new Asteroid((**itA).rad/2);
				(*newA).modelInit(rand());
				(*newA).init(rand());
				(*newB).modelInit(rand());
				(*newB).init(rand());
				printf("%f\n", (**itA).rad/2);
				(*newA).pos[0] = (**itA).pos[0];
				(*newA).pos[1] = (**itA).pos[1];
				(*newB).pos[0] = (**itA).pos[0];
				(*newB).pos[1] = (**itA).pos[1];
				asteroids.push_back(newA);
				asteroids.push_back(newB);
			}
			explosions.push_back(new Explosion((**itA).pos[0], (**itA).pos[1]));
			delete (*itA);
			asteroids.erase(itA);
			if(asteroids.empty()){
				firstT = true;
			}
			break;
		}
	}
	
	for(itE = explosions.begin(); itE != explosions.end(); itE++){
		if(!(**itE).update()){
			delete *itE;
			itE = explosions.erase(itE);
		}
	}
	//printf("%f %f\n", tardis.pos[0], tardis.pos[1]);
	glutPostRedisplay();
}

void specialKeys(int key, int x, int y){
	float th = 0;
	switch(key){
		case GLUT_KEY_LEFT:
			tardis.left();
			printf("LEFT\n");
			break;
		case GLUT_KEY_RIGHT:
			tardis.right();
			printf("RIGHT\n");
			break;
		default:
			break;
	}
}

void keys(unsigned char key, int x, int y){
	switch(key){
		case 'x':	
			tardis.accelerate();
			printf("ACC\n");
			break;
		case 'z':
			tardis.shoot();
			printf("SHOOT\n");
			break;
		default:
			break;
	}
}

void drawScene(){
	glMatrixMode( GL_MODELVIEW );
	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
	
	glPushMatrix();
	glLoadIdentity();
	
	if(firstT){
		tardis.modelInit(1);
		tardis.init();
		firstT = false;
		for(int i = 0; i < 4; i++){
			asteroids.push_back(new Asteroid(2));
		}
		int i = 0;
		for(itA = asteroids.begin(); itA != asteroids.end(); itA++){
			(**itA).modelInit(i+10);
			(**itA).init(i+5);
			i++;
		}
	}
	
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
	
	tardis.draw();
	for(itA = asteroids.begin(); itA != asteroids.end(); itA++){
		(**itA).draw();
		
	}
	for(itE = explosions.begin(); itE != explosions.end(); itE++){
		(**itE).draw();
	}
	
	glFlush();				// Flush OpenGL queue
    glutSwapBuffers();
    //glutTimerFunc(35, drawScene, 0);
}
