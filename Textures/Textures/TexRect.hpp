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
        glVertex2f(x-w/2, y - h/2);
        
        glTexCoord2f(0.0, 1.0);
        glVertex2f(x-w/2, y+h/2);
        
        glTexCoord2f(1.0, 1.0);
        glVertex2f(x+w/2, y+h/2);
        
        glTexCoord2f(1.0, 0.0);
        glVertex2f(x+w/2, y - h/2);
        
        glEnd();
        
        glDisable(GL_TEXTURE_2D);
    }

	int contains(float X, float Y) {
		return X >= x - w/2&&X <= x + w/2&&Y <= y+h/2&&Y >= y - h/2;
	}

	int contains(TexRect v) {
		return v.x >= x - w / 2 && v.x <= x + w / 2 && v.y <= y + h / 2 && v.y >= y - h / 2;
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
