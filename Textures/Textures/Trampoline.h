#include <stdio.h>
#include "TexRect.hpp"

class Trampoline: public TexRect
{	
public:

	Trampoline(float x, float y, float w, float h, GLuint& texture) : TexRect(x, y, w, h, texture) {}

	void move(int lr); //if lr is posetive move right, if negative move left 
};

