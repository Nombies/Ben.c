#include "App.h"
#include "Monkey.h"
#include "Powerup.h"
#include "Trampoline.h"
#include "Fruit.h"
#include <string>
#include <cmath>

using namespace std;

bool play = true;
int score = 0;
int lives = 3;
TexRect* background;
Monkey* monkey;
Trampoline* trampoline;
GLuint fruitTex[5];
vector<TexRect*> fruits;
static int submenu_id;
static int window;
static int value = 0;
static int menu_id;

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

	fruitTex[0] = strawberryTexture;
	fruitTex[1] = watermelonTexture;
	fruitTex[2] = rasberryTexture;
	fruitTex[3] = appleTexture;
	fruitTex[4] = blackberryTexture;

	background = new TexRect(-1,1,2,2,backgroundTexture);
	monkey = new Monkey(0,-0.5,.2,.2, 0.005, 0.005,monkeyTexture);
	trampoline = new Trampoline(mx,my,0.3,0.05,trampolineTexture);
	/*
	fruits.push_back(new Fruit((-.5 + 0.25 * 0), 0.5, 0.2, 0.2, 0, 0, strawberryTexture, NULL));
	fruits.push_back(new Fruit((-.5 + 0.25 * 1), 0.5, 0.2, 0.2, 0, 0, watermelonTexture, NULL));
	fruits.push_back(new Fruit((-.5 + 0.25 * 2), 0.5, 0.2, 0.2, 0, 0, rasberryTexture, NULL));
	fruits.push_back(new Fruit((-.5 + 0.25 * 3), 0.5, 0.2, 0.2, 0, 0, appleTexture, NULL));
	fruits.push_back(new Fruit((-.5 + 0.25 * 4), 0.5, 0.2, 0.2, 0, 0, blackberryTexture, NULL));
	*/

	for (int i = 0; i < 8;i++) {
		for (int j = 0; j < 4;j++)
		fruits.push_back(new Fruit((-1+0.25*i),1-0.25*j,0.25,0.25,0,0,fruitTex[rand()%5],NULL));
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
	if (play) {
		trampoline->moveTo(mx, my);
		monkey->update();
		for (vector<TexRect*>::iterator i = fruits.begin(); i != fruits.end(); i++) {
			if (monkey->contains(*(TexRect*)(*i))) {
				monkey->bounce(**i);
				((Fruit*)(*i))->markdel = 1;
				((Fruit*)(*i))->hit();
				score += 100;
				break;
			}
		}
		for (int i = 0; i < fruits.size(); i++) {
			if (((Fruit*)fruits[i])->markdel) {
				fruits.erase(fruits.begin() + i);
			}
		}
		if (monkey->contains(*trampoline)) {
			monkey->bounce(*trampoline);
		}
		else if (monkey->x<-1) {
			monkey->vx = abs(monkey->vx);
		}
		else if (monkey->x > (1 - monkey->w)) {
			monkey->vx = abs(monkey->vx)*-1;
		}
		else if (monkey->y > 1) {
			monkey->vy = abs(monkey->vy)*-1;
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

void menu(int num) {
	if (num == 0) {
		//glutDestroyWindow(window);
		exit(0);
	}
	else {
		value = num;
	}
	glutPostRedisplay();
}
void createMenu(void) {
	submenu_id = glutCreateMenu(menu);
	glutAddMenuEntry("PowerUp", 2);
	glutAddMenuEntry("PowerDown", 3);
	glutAddMenuEntry("Reset", 4);
	glutAddMenuEntry("Other", 5);     menu_id = glutCreateMenu(menu);
	glutAddMenuEntry("Clear", 1);
	glutAddSubMenu("Control", submenu_id);
	glutAddMenuEntry("Quit", 0);     glutAttachMenu(GLUT_RIGHT_BUTTON);
}
void display(void) {
	glClear(GL_COLOR_BUFFER_BIT);   if (value == 1) {
		return; //glutPostRedisplay();
	}
	else if (value == 2) {
		//glPushMatrix();
		// glColor3d(1.0, 0.0, 0.0);
		// glutWireSphere(0.5, 50, 50);
		// glPopMatrix();
		cout << "PowerUp " << endl;
		monkey->vy = monkey->vy*2.0;
	}
	else if (value == 3) {
		//glPushMatrix();
		//glColor3d(0.0, 1.0, 0.0);
		//glRotated(65, -1.0, 0.0, 0.0);
		//glutWireCone(0.5, 1.0, 50, 50);
		//glPopMatrix();
		cout << "PowerDown " << endl;
		monkey->vy = monkey->vy * 0.5;
	}
	else if (value == 4) {
		//glPushMatrix();
		//glColor3d(0.0, 0.0, 1.0);
		//glutWireTorus(0.3,0.6,100,100);
		//glPopMatrix();
		cout << "Reset " << endl;
	}
	else if (value == 5) {
		//glPushMatrix();
		//glColor3d(1.0, 0.0, 1.0);
		//glutSolidTeapot(0.5);
		//glPopMatrix();
		cout << "Other " << endl;
	}
	glFlush();
}


void App::mouseDown(float x, float y){
    // Update app state
    mx = x;
    my = y;
    
    // Redraw the scene
    //redraw();
}

void App::mouseDrag(float x, float y){
    // Update app state
    mx = x;
    my = y;
    
    // Redraw the scene
    //redraw();
}

void App::keyPress(unsigned char key) {
    if (key == 27){
        // Exit the app when Esc key is pressed
        exit(0);
    }if (key == 'p') {
		cout << "paused" << endl;
		play = !play;
	}
	cout << key << endl;
}
