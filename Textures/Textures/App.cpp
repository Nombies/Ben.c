#include "App.h"
#include "Powerup.h"
#include <time.h>
#include <cstdlib>
#include <string>

using namespace std;


void examplePowerup(App& b) {
	b.monkey->vy *= 2;
	cout << "Speeding up!" << endl;
}

void examplePowerDown(App& b) {
	b.trampoline->w = 0.15;
}
void examplePadleInc(App& b) {
	b.trampoline->w = 0.6;
}

void oneUp(App& b) {
	b.lives++;
	cout << "1 UP!" <<" You now have "<<b.lives<<" lives"<< endl;
}


App::App(const char* label, int x, int y, int w, int h): GlutApp(label, x, y, w, h){
    // Initialize state variables
reset:
	srand(time(NULL));
	mx = -0.1;
	my = -0.9;
	width = 0.3;
	height = 0.05;
    
	Function[0] = examplePowerup;
	Function[1] = examplePowerDown;
	Function[2] = examplePadleInc;
	Function[3] = oneUp;

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
	monkey = new Monkey(0,-0.5,.2,.2, 0.001, 0.001,monkeyTexture);
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
		
		if (abs((trampoline->x + trampoline->w / 2) - mx)>0.005)
			if (mx>(trampoline->x + trampoline->w / 2)) {
				trampoline->moveTo(trampoline->x + 0.005, -0.9);
			}
			else {
				trampoline->moveTo(trampoline->x - 0.005, -0.9);
			}

		monkey->update();
		for (vector<TexRect*>::iterator i = fruits.begin(); i != fruits.end(); i++) {
			if (monkey->contains(*(TexRect*)(*i))) {
				monkey->bounce(**i);
				((Fruit*)(*i))->markdel = 1;
				((Fruit*)(*i))->hit();
				score += 100;
				cout << "Score: " << score << endl;
				if (rand() % 100 > 80)
				{
					powerups.push_back(new Powerup((*i)->x, (*i)->y, 0.23, 0.2, 0, -0.001, (*i)->texture, Function[rand() % 4]));
				}


				//break;
			}
		}
		for (vector<Powerup*>::iterator i = powerups.begin(); i != powerups.end(); i++) {
			(*i)->update();
			if (trampoline->contains(*(TexRect*)(*i))) {
				(*i)->collect(*this);
				(*i)->markdel = 1;
			}
			else if ((*i)->y<-1.5) {
				(*i)->markdel = 1;
			}
		}
		for (int i = 0; i < powerups.size(); i++) {
			if (powerups[i]->markdel) {
				powerups.erase(powerups.begin() + i);
			}
		}
		for (int i = 0; i < fruits.size(); i++) {
			if (fruits[i]->markdel) {
				fruits.erase(fruits.begin() + i);
			}
		}
		if (monkey->contains(*trampoline)) {
			monkey->bounce(*trampoline);
			monkey->vx += ((monkey->x+monkey->w/2) - (trampoline->x+trampoline->w / 2))/trampoline->w *0.0005;
			monkey->vy *= 1.01;
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
		else if(monkey->y<-1) {
			lives--;
			cout << "Out of Bounds!" << endl;
			cout << "Lives left: " << lives << endl;
			Monkey* tmp = monkey;
			monkey = new Monkey(0, -0.5, .2, .2, 0.0005, 0.0005, monkey->texture);
			delete tmp;
			play = 0;
		}
		//monkey->vy = fmod(monkey->vy, 0.001);

		if (fruits.size() == 0 && monkey->contains(*trampoline)) {
			for (int i = 0; i < 8; i++) {
				for (int j = 0; j < 4; j++)
					fruits.push_back(new Fruit((-1 + 0.25*i), 1 - 0.25*j, 0.25, 0.25, 0, 0, fruitTex[rand() % 5], NULL));
			}
		}

		if (lives == 0) {
			cout << "Game Over!" << endl;
			cout << "Your Score: " << score << endl;

			file_reader.open("../score.txt");

			if (file_reader.is_open()) {
				string line;
				char* temp;
				getline(file_reader, line);
				temp = new char[line.size() + 1];
				strcpy(temp, line.c_str());
				high_score = atoi(temp);
				file_reader.close();
			}

			file_writer.open("../score.txt");

			if (score > high_score) {
				cout << "New High Score: " << score << endl;
				high_score = score;
			}
			cout << "High Score: " << high_score << endl;
			if (file_writer.is_open()) {
				string str = to_string(high_score);
				file_writer << str;
				file_writer.close();
			}
			cout << "press esc to exit" << endl;
			play = 0;
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
/*
	glRasterPos2i(0, 0);
	glColor4f(0.0f, 0.0f, 1.0f, 1.0f);
	const char* c = "Score";//to_string(lives).c_str();
	cout << c << endl;
	glutBitmapString(GLUT_BITMAP_HELVETICA_18, (const unsigned char*)c);
	glColor3d(1.0, 1.0, 1.0);
	*/
	for (vector<TexRect*>::iterator i = fruits.begin(); i != fruits.end(); i++) {
		(*i)->draw();
	}
	for (vector<Powerup*>::iterator i = powerups.begin(); i != powerups.end(); i++) {
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
		play = !play;
	}
}
