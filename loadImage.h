#ifndef LOADIMAGE
#define LOADIMAGE
//#include<GL/freeglut.h>
//#include <opencv/cv.h>

#include "glInclude.h"
#ifndef TUX
#include<cv.h>
#else
#include <opencv/cv.h>
#endif

#define MAXSIZE 128


struct My_img {
	GLubyte *img;
	int height, width;
};

void loadImage(const char *file, My_img &image);

#endif

