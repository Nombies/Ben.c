#ifndef App_hpp
#define App_hpp

#include "GlutApp.h"
#include "RgbImage.h"
#include "TexRect.hpp"
#include <vector>
#include "Monkey.h"
#include "Trampoline.h"
#include "Fruit.h"
#include <string>
#include <cmath>

class App: public GlutApp {
    // Maintain app state here
    float mx;
    float my;
	float width;
	float height;
public:

	bool play = true;
	int score = 0;
	int lives = 3;
	TexRect* background;
	Monkey* monkey;
	Trampoline* trampoline;
	GLuint fruitTex[5];
	vector<TexRect*> fruits;
	vector<Powerup*> powerups;


    // Constructor, to initialize state
    App(const char* label, int x, int y, int w, int h);
    
    // These are the events we want to handle
    void draw();
    void keyPress(unsigned char key);
	void specialKeyPress(int key);
    void mouseDown(float x, float y);
    void mouseDrag(float x, float y);
    
    GLuint loadTexture(const char* filename);
	void idle();
};

#endif
