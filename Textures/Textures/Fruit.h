#include <stdio.h>
#include "TexRect.hpp"
#include "Powerup.h"

class Fruit : public TexRect
{
public:
	Powerup* p;
	Fruit(float x, float y, float w, float h, float vX, float vY, GLuint& texture, Powerup* P) : TexRect(x, y, w, h, texture) {
		p = P;
	}
	void hit(); //call this if the monkey colides with this fruit
};

