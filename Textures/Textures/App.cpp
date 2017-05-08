#include "App.h"
#include "Monkey.h"
#include "Powerup.h"
#include "Trampoline.h"
#include "Fruit.h"
#include <string>
#include <cmath>

using namespace std;

TexRect* background;
Monkey* monkey;
Trampoline* trampoline;
vector<TexRect*> fruits;

App::App(const char* label, int x, int y, int w, int h): GlutApp(label, x, y, w, h){
    // Initialize state variables
	mx = -0.1;
	my = -0.9;
	width = 0.3;
	height = 0.05;
    
	#if defined WIN32
	GLuint monkeyTexture = loadTexture("..//Ape.bmp");
	GLuint trampolineTexture = loadTexture("..//trampoline_1.bmp");
	GLuint backgroundTexture = loadTexture("..//background.bmp");
	GLuint strawberryTexture = loadTexture("..//Strawberry.bmp");
	GLuint watermelonTexture = loadTexture("..//watermelon.bmp");
	GLuint rasberryTexture = loadTexture("..//rasberry.bmp");
	GLuint appleTexture = loadTexture("..//apple.bmp");
	GLuint blackberryTexture = loadTexture("..//blackberry.bmp");

	#else
	GLuint monkeyTexture = loadTexture("Ape.bmp");
	GLuint trampolineTexture = loadTexture("trampoline_1.bmp");
	GLuint backgroundTexture = loadTexture("background.bmp");
	GLuint strawberryTexture = loadTexture("Strawberry.bmp");
	GLuint watermelonTexture = loadTexture("watermelon.bmp");
	GLuint rasberryTexture = loadTexture("rasberry.bmp");
	GLuint appleTexture = loadTexture("apple.bmp");
	GLuint blackberryTexture = loadTexture("blackberry.bmp");
	#endif

	background = new TexRect(-1,1,2,2,backgroundTexture);
	monkey = new Monkey(0,-0.5,.2,.2, 0.0001,0.0005,monkeyTexture);
	trampoline = new Trampoline(mx,my,0.3,0.05,monkeyTexture);
	/*
	fruits.push_back(new Fruit((-.5 + 0.25 * 0), 0.5, 0.2, 0.2, 0, 0, strawberryTexture, NULL));
	fruits.push_back(new Fruit((-.5 + 0.25 * 1), 0.5, 0.2, 0.2, 0, 0, watermelonTexture, NULL));
	fruits.push_back(new Fruit((-.5 + 0.25 * 2), 0.5, 0.2, 0.2, 0, 0, rasberryTexture, NULL));
	fruits.push_back(new Fruit((-.5 + 0.25 * 3), 0.5, 0.2, 0.2, 0, 0, appleTexture, NULL));
	fruits.push_back(new Fruit((-.5 + 0.25 * 4), 0.5, 0.2, 0.2, 0, 0, blackberryTexture, NULL));
	*/

	for (int i = 0; i < 5;i++) {
		fruits.push_back(new Fruit((-.5+0.25*i),0.5,0.25,0.25,0,0,appleTexture,NULL));
	}

}


GLuint App::loadTexture(const char *filename) {
    GLuint texture_id;
    glClearColor (0.0, 0.0, 0.0, 0.0);
    glShadeModel(GL_FLAT);
    glEnable(GL_DEPTH_TEST);
    
    RgbImage theTexMap( filename );
    
    // Pixel alignment: each row is word aligned (aligned to a 4 byte boundary)
    //    Therefore, no need to call glPixelStore( GL_UNPACK_ALIGNMENT, ... );
    
    
    glGenTextures( 1, &texture_id );
    glBindTexture( GL_TEXTURE_2D, texture_id );
    
    

    
    
    gluBuild2DMipmaps(GL_TEXTURE_2D, 3, theTexMap.GetNumCols(), theTexMap.GetNumRows(),
                      GL_RGB, GL_UNSIGNED_BYTE, theTexMap.ImageData() );
    
    return texture_id;
}

void App::idle() {
	trampoline->moveTo(mx,my);
	monkey->update();
	for (vector<TexRect*>::iterator i = fruits.begin(); i != fruits.end(); i++) {
		if (monkey->contains(*(TexRect*)(*i))) {
			monkey->bounce(**i);
		}
	}
	if (monkey->contains(*trampoline) ){
		monkey->bounce(*trampoline);
	}
	else if (monkey->x<-1) {
		monkey->vx = abs(monkey->vx);
	}else if (monkey->x>(1-monkey->w)) {
		monkey->vx = abs(monkey->vx)*-1;
	}else if (monkey->y>1) {
		monkey->vy = abs(monkey->vy)*-1;
	}


	draw();
}

void App::draw() {

    // Clear the screen
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    // Set background color to black
    glClearColor(0.0, 0.0, 0.0, 1.0);
    
    // Set up the transformations stack
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    
    // Set Color
    glColor3d(1.0, 1.0, 1.0);
    

	for (vector<TexRect*>::iterator i = fruits.begin(); i != fruits.end(); i++) {
		(*i)->draw();
	}
	monkey->draw();
	trampoline->draw();
	background->draw();

    
    glDisable(GL_TEXTURE_2D);
    
    // We have been drawing everything to the back buffer
    // Swap the buffers to see the result of what we drew
    glFlush();
    glutSwapBuffers();
}

void App::specialKeyPress(int key) {
	switch (key) {
	case GLUT_KEY_LEFT:
		mx -= 0.05;
		break;
	case GLUT_KEY_RIGHT:
		mx += 0.05;
		break;
	}
	if (mx < -1) {
		mx = -1;
	}else 
	if (mx + width > 1) {
		mx = 1 - trampoline->w;
	}
	//Sleep();
	//glutPostRedisplay();
}

void App::mouseDown(float x, float y){
    // Update app state
    mx = x;
    my = y;
    
    // Redraw the scene
    redraw();
}

void App::mouseDrag(float x, float y){
    // Update app state
    mx = x;
    my = y;
    
    // Redraw the scene
    redraw();
}

void App::keyPress(unsigned char key) {
    if (key == 27){
        // Exit the app when Esc key is pressed
        exit(0);
    }
}
