#include <stdio.h>
#include "TexRect.hpp"
#include <string.h>
#include <cmath>

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
		if (this->y < b.y) {
			vy = abs(vy)*-1;
		}
	} //call this if the monkey colides with b
};

