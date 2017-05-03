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
		if (this->y < b.y) {
			vy = abs(vy)*-1;
		}else if (this->y > b.y) {
			vy = abs(vy);
		}else if (this->x<b.x) {
			vx = abs(vx);
		}else if (this->x>b.x) {
			vx = abs(vx)*-1;
		}
		cout << "bounce" << endl;
	} //call this if the monkey colides with b
};

