
/* Copyright (c) Mark J. Kilgard, 1995. */

/* This program is freely distributable without licensing fees 
   and is provided without guarantee or warrantee expressed or 
   implied. This program is -not- in the public domain. */

/* molehill uses the GLU NURBS routines to draw some nice surfaces. */

#include <freeglut.h>

static GLfloat mat_red_diffused[4] = { 0.7, 0.0, 0.1, 1.0 };
static GLfloat mat_green_diffused[4] = { 0.0, 0.7, 0.1, 1.0 };
static GLfloat mat_blue_diffused[4] = { 0.0, 0.1, 0.7, 1.0 };
static GLfloat mat_yellow_diffused[4] = { 0.7, 0.8, 0.1, 1.0 };
static GLfloat mat_speculard[4] = { 1.0, 1.0, 1.0, 1.0 };
static GLfloat mat_shininessd[1] = { 100.0 };
static GLfloat knotsd[8] = { 0.0, 0.0, 0.0, 0.0, 1.0, 1.0, 1.0, 1.0 };

class patch{

	void _copyArray(GLfloat source[], GLfloat dest[], int limit)
	{
		int p=0;
		for(p=0;p<limit;p++)
		{
			dest[p] = source[p];
		}
	}

public:

GLfloat mat_red_diffuse[4];
GLfloat mat_green_diffuse[4];
GLfloat mat_blue_diffuse[4] ;
GLfloat mat_yellow_diffuse[4] ;
GLfloat mat_specular[4] ;
GLfloat mat_shininess[1] ;
GLfloat knots[8] ;
GLfloat pts1[4][4][3], pts2[4][4][3];
GLfloat pts3[4][4][3], pts4[4][4][3];
GLUnurbsObj *nurb;
int u, v;

void init()
{
	_copyArray(mat_red_diffused,mat_red_diffuse,4);
	_copyArray(mat_green_diffused,mat_green_diffuse,4);
	_copyArray(mat_blue_diffuse,mat_blue_diffuse,4);
	_copyArray(mat_yellow_diffuse,mat_yellow_diffuse,4);
	_copyArray(mat_speculard,mat_specular,4);
	_copyArray(mat_shininessd,mat_shininess,1);
	_copyArray(knotsd,knots,8);

}
void draw(void)
{
  //glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  
  //glFlush();
}

void render()
{
  glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
  glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
  //glEnable(GL_LIGHTING);
  //glEnable(GL_LIGHT5);
  //glEnable(GL_DEPTH_TEST);
  //glEnable(GL_AUTO_NORMAL);
  //glEnable(GL_NORMALIZE);
  nurb = gluNewNurbsRenderer();
  gluNurbsProperty(nurb, GLU_SAMPLING_TOLERANCE, 25.0);
  gluNurbsProperty(nurb, GLU_DISPLAY_MODE, GLU_FILL);

  /* Build control points for NURBS mole hills. */
  for(u=0; u<4; u++) {
    for(v=0; v<4; v++) {
      /* Red. */
      pts1[u][v][0] = 2.0*((GLfloat)u);
      pts1[u][v][1] = 2.0*((GLfloat)v);
      if((u==1 || u == 2) && (v == 1 || v == 2))
	/* Stretch up middle. */
	pts1[u][v][2] = 6.0;
      else
	pts1[u][v][2] = 0.0;


      /* Blue. */
      pts3[u][v][0] = 2.0*((GLfloat)u - 3.0);
      pts3[u][v][1] = 2.0*((GLfloat)v);
      if((u==1 || u == 2) && (v == 1 || v == 2))
	if(u == 1 && v == 2)
	  /* Pull up on single middple square. */
	  pts3[u][v][2] = 11.0;
	
    }
  }
 // glMatrixMode(GL_PROJECTION);
  //gluPerspective(55.0, 1.0, 2.0, 24.0);
  //glMatrixMode(GL_MODELVIEW);
  //glTranslatef(2.0, 2.0, 0.0);
  //glRotatef(330.0, 1.0, 0.0, 0.0);

  //glNewList(1, GL_COMPILE);

    /* Render blue hill. */
    glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_blue_diffuse);
    gluBeginSurface(nurb);
      gluNurbsSurface(nurb, 8, knots, 8, knots,
        4 * 3, 3, &pts3[0][0][0],
        4, 4, GL_MAP2_VERTEX_3);
    gluEndSurface(nurb);

  //glEndList();
	//glCallList(1);
  
}
};
