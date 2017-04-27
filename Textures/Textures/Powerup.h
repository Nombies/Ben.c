#ifndef PWRUP_H
#define PWRUP_H 

#include <stdio.h>
#include "TexRect.hpp"
#include "App.h"

class Powerup : public TexRect
{
public:
	float vx, vy;	//floats for the x and y velocity
	void(*powerup) (App &b); //function pointer for what to do when this powerup is colleced

	Powerup(float x, float y, float w, float h, float vX, float vY, GLuint& texture, void(*p) (App &b)) : TexRect(x, y, w, h, texture) {
		vx = vX;
		vy = vY;
		powerup = p;
	}

	void update(); //each gme tick, call this to run the physics
	void collect(); //call this if the trampoline colides with this
};

#endif // !pwrup