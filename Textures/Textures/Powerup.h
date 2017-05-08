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

/*boolean Random(GLuint chance) {
	GLuint random = rand() % chance;
	return random == 0;
}

void powerUps(App &b) {
	if (Random(20)) {
		this->powerUps.push_back(PowerUp("pad-size-increase", glm::vec3(1.0f, .06f, 0.4f), 0.0f, block.postion, tex_pass));
	}
} */

/*bool Random(GLuint chance) {
	GLuint random = rand() % chance;
	return random == 0;
}

void powerUps(App &b) {
	if (Random(20)) {
		Trampoline(xx, yy, ww, hh, texture);



	}
} */

#endif // !pwrup