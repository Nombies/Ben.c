#include <stdio.h>
#include "TexRect.hpp"

class Trampoline: public TexRect
{	
public:

	Trampoline(float x, float y, float w, float h, GLuint& texture) : TexRect(x, y, w, h, texture) {}

	void moveTo(float X, float Y) {
		x = X;
		y = Y;
	}; //if lr is posetive move right, if negative move left 
};

