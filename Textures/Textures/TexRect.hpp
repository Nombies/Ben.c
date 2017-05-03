//
//  TexRect.hpp
//  glutapp
//
//  Created by Angelo Kyrilov on 4/11/17.
//  Copyright © 2017 Angelo Kyrilov. All rights reserved.
//

#ifndef TexRect_hpp
#define TexRect_hpp
#include "RgbImage.h"
#include <algorithm>
#if defined WIN32
#include <freeglut.h>
#elif defined __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/freeglut.h>
#endif

class TexRect {
    
public:
	float x;
	float y;
	float w;
	float h;
	GLuint texture;
    TexRect (float x, float y, float w, float h,GLuint& tex){
        this->x = x;
        this->y = y;
        this->w = w;
        this->h = h;
		texture = tex;
    }
    
    
    virtual void draw(){
		glBindTexture(GL_TEXTURE_2D, texture);
        glEnable(GL_TEXTURE_2D);
        glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
        
		glBegin(GL_QUADS);

		glTexCoord2f(0.0, 0.0);
		glVertex2f(x, y - h);

		glTexCoord2f(0.0, 1.0);
		glVertex2f(x, y);

		glTexCoord2f(1.0, 1.0);
		glVertex2f(x + w, y);

		glTexCoord2f(1.0, 0.0);
		glVertex2f(x + w, y - h);

		glEnd();
        
        glDisable(GL_TEXTURE_2D);
    }

	//bool IsInBounds(int value, int low, int high) {
	//	return !(value <= low) && (value <= high);
	//}

	virtual int contains(float X, float Y) {
		return X >= x&&X <= x + w&&Y <= y&&Y >= y - h;
	}

	virtual int contains(TexRect b) {
		return x < b.x + b.w && b.x + b.w > x &&
			y > b.y - b.h && y - h < b.y;
	}

	GLuint loadTexture(const char *filename) {
		GLuint texture_id;
		glClearColor(0.0, 0.0, 0.0, 0.0);
		glShadeModel(GL_FLAT);
		glEnable(GL_DEPTH_TEST);

		RgbImage theTexMap(filename);

		// Pixel alignment: each row is word aligned (aligned to a 4 byte boundary)
		//    Therefore, no need to call glPixelStore( GL_UNPACK_ALIGNMENT, ... );


		glGenTextures(1, &texture_id);
		glBindTexture(GL_TEXTURE_2D, texture_id);





		gluBuild2DMipmaps(GL_TEXTURE_2D, 3, theTexMap.GetNumCols(), theTexMap.GetNumRows(),
			GL_RGB, GL_UNSIGNED_BYTE, theTexMap.ImageData());

		return texture_id;
	}
};

#endif /* TexRect_hpp */
