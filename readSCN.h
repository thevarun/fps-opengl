#ifndef READSCN
#define READSCN

#include "objparser.h"
#include "loadImage.h"

extern OBJ_holder *models;
extern GLuint *textures;
extern My_img *tex_images;

//extern object_pr* prev_obj;
void readTextScene(const char* file);

extern int no_of_tex;
extern int no_of_models;
extern int no_of_objs;


#endif

