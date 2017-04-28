#include "App.h"
#include "Monkey.h"
#include "Powerup.h"
#include "Trampoline.h"
#include "Fruit.h"
#include <string>

using namespace std;

TexRect* background;
Monkey* monkey;
vector<TexRect*> fruits;

App::App(const char* label, int x, int y, int w, int h): GlutApp(label, x, y, w, h){
    // Initialize state variables
    mx = 0.0;
    my = 0.0;
    
	GLuint monkeyTexture = loadTexture("..//monalisa.bmp");
	GLuint trampolineTexture = loadTexture("..//monalisa.bmp");
	GLuint backgroundTexture = loadTexture("..//wall.bmp");

	background = new TexRect(0,0,2,2,backgroundTexture);
	monkey = new Monkey(0,-0.5,.25,.35,0,0.0005,monkeyTexture);
    
	for (int i = 0; i < 5;i++) {
		fruits.push_back(new Fruit((-.5+0.25*i),0.5,0.1,0.1,0,0,monkeyTexture,NULL));
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
	monkey->update();
	for (vector<TexRect*>::iterator i = fruits.begin(); i != fruits.end(); i++) {
		if (monkey->contains(*(TexRect*)(*i))) {
			monkey->bounce(**i);
		}
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
	background->draw();

    
    glDisable(GL_TEXTURE_2D);
    
    // We have been drawing everything to the back buffer
    // Swap the buffers to see the result of what we drew
    glFlush();
    glutSwapBuffers();
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
