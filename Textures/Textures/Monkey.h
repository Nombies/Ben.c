#include <stdio.h>
#include "TexRect.hpp"
#include <string.h>
#include <cmath>
#include <iostream>

using namespace std;

class Monkey : public TexRect
{
public:
	float vx, vy;	//floats for the monkey's x and y velocity
	TexRect* u;
	TexRect* d;
	TexRect* l;
	TexRect* r;


	Monkey(float x, float y, float w, float h, float vX, float vY, GLuint& texture): TexRect(x,y,w,h,texture){
		vx = vX;
		vy = vY;
		u = new TexRect(x,y+1,w,1,texture);
		d = new TexRect(x, y-h, w, 1, texture);
		l = new TexRect(x-1, y, 1, h, texture);
		r = new TexRect(x+w, y, 1, h, texture);
	}

	void update() {
		x += vx;
		y += vy;
		u->x = x; u->y = y+1;
		d->x = x; d->y = y - h;
		l->x = x - 1; l->y = y;
		r->x = x + w; r->y = y;
	} //each gme tick, call this to run the physics on the monkey ball
	
	void bounce(TexRect& b) {
		bool uc = b.contains(*u);
		bool dc = b.contains(*d);
		bool lc = b.contains(*l);
		bool rc = b.contains(*r);

		if (uc &!dc) {
			vy = -1 * abs(vy);
		}
		else if (!uc & dc) {
			vy = abs(vy);
		}
		else if (lc &!rc) {
			vx = abs(vx);
		}
		else if (!lc & rc) {
			vx = -1*abs(vx);
		}
		//cout << "bounce" << endl;
	} //call this if the monkey colides with b
};

