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

	Monkey(float x, float y, float w, float h, float vX, float vY, GLuint& texture): TexRect(x,y,w,h,texture){
		vx = vX;
		vy = vY;
	}

	void update() {
		x += vx;
		y += vy;
	} //each gme tick, call this to run the physics on the monkey ball
	
	void bounce(TexRect& b) {
		bool l = x<b.x+b.w && x>b.x;
		bool r = x+w>b.x && x+w<b.x+b.w;
		bool u = y>b.y-b.h && y<b.y;
		bool d = y-h<b.y && y-h > b.y-b.h;

		if ((y>b.y||y-h<b.y-b.h) && (u||d)) {
			if (y>b.y) {
				vy = abs(vy);
			}
			else {
				vy = abs(vy)*-1;
			}
		}
		else {
			vx *= -1;
		}
		//cout << "bounce" << endl;
	} //call this if the monkey colides with b
};

