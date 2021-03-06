// g++ loadImage.cpp -o loadImage -L /usr/lib -lhighgui -lglut


//#include <opencv/highgui.h>
//#include<highgui.h>
#include<iostream>
//#include <GL/freeglut.h>
#include "glInclude.h"

#ifndef TUX
#include<highgui.h>
#else
#include <opencv/highgui.h>
#endif

#include "loadImage.h"
using namespace std;

const int sizes[] = {128, 64, 32, 16, 8, 4, 2, 1};
IplImage* currImg;

GLubyte *giveImage2(){
  	uchar *img = (uchar *)currImg->imageData;
	return (GLubyte*)img;
}

void invertColors(My_img &img){
  
  int step = img.width*3;
  uchar *data = img.img;
  for(int i = 0; i< img.height; i++)
    for(int j = 0; j < img.width; j++){
	uchar temp =  data[i*step + j*3+2];
      data[i*step + j*3+2] = data[i*step + j*3];
      data[i*step + j*3] = temp;
    }
      /*{
      uchar temp = data[i*img.width + j +2];
      data[i*img.width + j + 2] = data[i*img.width + j + 1];
      data[i*img.width + j + 1] = temp;
      }*/
}

void loadImage( const char *file, My_img &image){
//	if(currImg != NULL)
	//	cvReleaseImage( &currImg);
	currImg = NULL;	
	currImg = cvLoadImage(file,1);
	if(currImg == NULL)
		cout<<"Could not load file: "<<file<<endl;
	image.img = giveImage2();
	image.height = currImg->height;
	image.width = currImg->width;
		invertColors(image);
}

void giveImage(int dim, GLubyte *datanew){
	cout<<"inside scaleImage "<<sizes[dim]<<endl;
  	uchar *img = (uchar *)currImg->imageData;
	GLubyte *data = (GLubyte*)img;
	//gluScaleImage(GLenum GL_RGB, GLint widthin, GLint heightin, GLenum typein, const void *datain, GLint widthout, GLint heightout, GLenum typeout, void *dataout); 
	datanew = new GLubyte[64*64];
	if(datanew == NULL){
		cout<<"could not allocate memory"<<endl;
	}
	cout<<"size of datanew = "<<sizeof(datanew)<<" size of img = "<<sizeof(img)<<endl;		
//	gluScaleImage( GL_RGB, currImg->width, currImg->height, GL_UNSIGNED_BYTE, data, sizes[dim], sizes[dim], GL_UNSIGNED_BYTE, datanew); 
	gluScaleImage( GL_RGB, 100, 100, GL_UNSIGNED_BYTE, data, 64, 64, GL_UNSIGNED_BYTE, datanew); 
	cout<<"aaaaaaa"<<endl;
}

int mainx(int argc, char *argv[]){
	My_img ptr;
	loadImage(argv[1], ptr);
		cvNamedWindow("Window", 1);
	cout<<"width "<<currImg->width<<"height "<<currImg->height<<endl;
	cout<<sizeof(GLubyte)<<" <= Glubyte  uchar => "<<sizeof(uchar)<<endl;
//display the image in the window
	cvShowImage("Window", currImg);
//wait for key to close the window
	cvWaitKey(0);
	cout<<"in LoadImage"<<endl;
	cout<<currImg->height<<" "<<currImg->width<<" "<<currImg->nChannels<<endl;
	cvDestroyWindow( "Window" ); //destroy the window
	GLubyte *datanew;
	giveImage(1, datanew);

	cvReleaseImage( &currImg ); //release the memory for the image

	return 0;
}

