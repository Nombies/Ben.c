#include "App.h"

extern void createMenu(void);
extern void display(void);
int main(int argc, char** argv) {
	// Initialize GLUT
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_DEPTH);
    
    // Instantiate a new App
    App* myApp = new App("MyApp", 50, 50, 600, 600);
	createMenu();
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glutDisplayFunc(display);
	// Start the app
    myApp->run();
}
