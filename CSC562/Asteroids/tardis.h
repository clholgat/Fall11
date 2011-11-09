
#ifndef TARDIS_H
#define TARDIS_H

#include "model.h"
#include "asteroid.h"
#include <list>

using namespace std;

class Shot;

class Tardis: public Model{
	public:
		Tardis();
		void draw();
		void init();
		void shoot();
		void accelerate();
		void left();
		void right();
		void update();
		bool checkShots(Asteroid *a);
		bool checkTardis(Asteroid *a);
		list<Shot*> shots;
		list<Shot*>::iterator itS;
	private:
		void drawPointer();
		float tardisRect[44][3];
		int tardisLen;
};

class Shot: public Model{
	public:
		Shot();
		void draw();
		void init(Tardis *tardis);
};

#endif

