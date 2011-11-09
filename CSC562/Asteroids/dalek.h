
#ifndef DALEK_H
#define DALEK_H

#include "model.h"

class Dalek: public Model{
	public:
		Dalek();
		void draw();
	private:
		void drawBase(float base[][3], float y);
		void drawSides();
		void drawHead();
		void drawArms();
		void drawSph(float bot[][3], float top[][3]);
		int mod(int num, int mod);
		void drawThing(float len, float scale);
		float dalekBase [9][3];
		float dalekTop [9][3];
};

#endif
