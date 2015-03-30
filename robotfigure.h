#ifndef ROBOT_FIGURE
#define ROBOT_FIGURE

#include "glInclude.h"
//#include <GL/freeglut.h>
//#include <freeglut_ext.h>
#include <iostream>
#include <vector>
#include <math.h>
#include <string.h>
#include <stdlib.h>
//#include <math.h>
#include "Particle.h"
//#include "enemy.h"

#include "collisionstuff.h"


using namespace std;





//float randomFloat() {
//	return (float)rand() / ((float)RAND_MAX + 1);
//}

class Enemy;
extern object_pr *theworldsend;

/// TYPE DEFINITIONS ////////////////////////////////////////////////////////////

enum direction {FORWARD, BACKWARD, UP, DOWN, NONE};
enum selection {LEFT_ARM, LEFT_ARM_LOWER,
                RIGHT_ARM, RIGHT_ARM_LOWER,
                LEFT_LEG, LEFT_LEG_LOWER,
                RIGHT_LEG, RIGHT_LEG_LOWER,
                NONE_SELECTED};

typedef struct apptag                     // Used for current state of
{                                         //   appendages
   float     rotation;
   float     jointrot;
   float     footrot;
   direction dMain;
   direction dSecondary;
   direction dfoot;
} appendageState;

typedef struct robottag                   // Used for current state of 
{                                         //   robot (torso) location
   float     vertPos;
   float     rotation;
   direction bounce;
   direction lean;
} robotState;

typedef struct pixeltag                   // structure for pixel
{
   unsigned char r, g, b;
} pixel;

extern  float defview_rotate[];
//float default_view_rotate[16]  = { 1,0,0,0, 0,1,0,0, 0,0,1,0, 0,0,0,1 };

// GLOBAL ANIMATION VARIABLES ///////////////////////////////////////////////////

/*ArmL = {42.7, 0.0, 0.0, FORWARD, FORWARD, NONE};
appendageState    ArmR = {-42.7, -85.4, 0.0, BACKWARD, BACKWARD, NONE};
appendageState    LegL = {-42.7, 0.0, 0.0,  BACKWARD, BACKWARD, FORWARD};
appendageState    LegR = {42.7, 85.4, 0.0, FORWARD, FORWARD, FORWARD};
robotState          RS = {0.41, 9.0, UP, BACKWARD};*/
extern  appendageState    defArmL;
extern  appendageState    defArmR;
extern  appendageState    defLegL;
extern  appendageState    defLegR;
extern  robotState          defRS;

class Robot_Figure  {
	public:

object_pr *parent;
  
/// GLOBAL CONTROL VARIABLES ////////////////////////////////////////////////////
//int mainWindow;                           // application window ID
bool reset;                       // flag to reset view
float rotationX;                          // mouse mov't rotation factor in x
float rotationY;                          // mouse mov't rotation factor in y
float current_x;                               // current x coord of robot
float current_y;                               // current y coord of robot
float current_z;
int health;

/// GLOBAL GLUI DEFNS & VARIABLES ///////////////////////////////////////////////

#define RESET_ID 100


int inmotion;
int speedSel;

int checkbox,radio,trans_xy,trans_z,view_rot ;

float view_rotate[16];
float view_translate[3];
float default_view_rotate[16];

// GLOBAL ANIMATION VARIABLES ///////////////////////////////////////////////////

appendageState    ArmL ;
appendageState    ArmR ;
appendageState    LegL ;
appendageState    LegR ;
robotState          RS ;

int                  i;      // animation step control for RS
int                  j;      // animation step control for Arm, Leg
bool             moved;  // true if some appendage has been hand-moved
bool reset_in_progress;  // true if we are reseting the animation
bool shoot;
bool is_moving; //true if robot is in motion else false
int direction_of_motion; //1 if forward, 2 if leftward, 3 if rightward, 4 if backward
bullet B[200];
long int number_of_bullets;
long int Max_bullets;
int more_bullets,number_of_rounds,checker;
int colliding_direction,is_colliding;

float rsv, rsr,                  // incrementors for each movable appendage
      alr, als,                  //   see resetAnimation()
      arr, ars,
      llr, lls, llf,
      lrr, lrs, lrf;

/// CALLBACK FUNCTIONS //////////////////////////////////////////////////////////

/*
void idle(void);

/// GL DRAWING ACCESSORY FUNCTIONS //////////////////////////////////////////////

void crossprod(float v1[3], float v2[3], float out[3]);
void drawFrustum(GLfloat top, GLfloat bottom, GLfloat height, GLfloat width);
void drawAppendage(appendageState as, bool foot);
void drawRobot(void);
//void drawGround(void);
void animate(void);
void resetAnimation(void);
*/
/// MAIN PROGRAM ////////////////////////////////////////////////////////////////

Robot_Figure()
{
  	  
   inmotion = 1;
   //radio =1 fast
   //radio =2 normal
   //radio=3 slow motion
   speedSel = 1;
   health = 100;
   shoot = false;
    reset = false;
	number_of_bullets=0;
	Max_bullets=200;
	more_bullets=0;
	number_of_rounds=0;
	is_moving=false;
	colliding_direction=1;
	is_colliding=0;
	//view_rot = glui->add_rotation("Change Viewpoint", view_rotate);
   //view_rot->set_spin(1.0);
   //glui->add_statictext("");
   
   //trans_xy = glui->add_translation("Translate", GLUI_TRANSLATION_XY, view_translate);
   //trans_xy->set_speed(0.005);
   //glui->add_statictext("");

   //trans_z = glui->add_translation("Near & Far", GLUI_TRANSLATION_Z, &view_translate[2]);
   //trans_z->set_speed(0.005);
   //glui->add_statictext("");

   //glui->add_button("Reset View", RESET_ID, controlCB);
   //glui->add_statictext("");

   //glui->add_button("Quit", 0, (GLUI_Update_CB) exit);
   
   // finialize setup, call main loop
	ArmL = defArmL;
	ArmR = defArmR;
	LegL = defLegL;
	LegR = defLegR;
	RS = defRS;/*
	int p;
	for( p=0;p<16;p++)
	{
		view_rotate[p]= defview_rotate[p];
		default_view_rotate[p] = defview_rotate[p];
	}*/
	view_translate[0] = 0.0;
	view_translate[1] = 0.0;
	view_translate[2] = 0.0;

	i = 0;      // animation step control for RS
    j = 0;      // animation step control for Arm, Leg
    moved = false;  // true if some appendage has been hand-moved
    reset_in_progress = false;  // true if we are reseting the animation

 
}



/********************************************************************* idle ****/
void idle(void)
//
// Desc: Std idle callback
//       Calls animate() and resetAnimation() functions
//
{
   // Slow animation if requested by radio buttons
   int x;
   //if (speedSel == 1)
      //for (x = 0; x < 5000; x++);
   //else if (speedSel == 2)
     // for (x = 0; x < 1000000; x++);
			animate();
   
   // tell glui that it's not the mainWindow
   //if (glutGetWindow() != mainWindow)
     // glutSetWindow(mainWindow);   

   // redisplay
   glutPostRedisplay();
}

void crossprod(float v1[3], float v2[3], float out[3])
//
// Desc: Find cross product
// Pre:  v1 and v2 are vectors of which the cross product will be taken
// Post: result in out
//
{
   out[0] = v1[1]*v2[2] - v1[2]*v2[1];
   out[1] = v1[2]*v2[0] - v1[0]*v2[2];
   out[2] = v1[0]*v2[1] - v1[1]*v2[0];
}

/************************************************************** drawFrustum ****/
void drawFrustum(GLfloat top, GLfloat bottom, GLfloat height, GLfloat width)
//
// Desc: Draw a 3D frustum shape.
// Pre:  top, bottom = length of top and bottom
//          (top and bottom form parallel planes)
//       width = depth of frustum
// Note: Drawing is from center of 3D object described by the inputs
//       Used in drawing robot torso
//
{
   GLfloat t = top / 2;
   GLfloat b = bottom / 2;
   GLfloat h = height / 2;
   GLfloat w = width / 2;

   GLfloat vert[8][3] = {
      {-t, h, w}, {t, h, w}, {-b, -h, w}, {b, -h, w},
      {-t, h, -w}, {t, h, -w}, {-b, -h, -w}, {b, -h, -w}};

   GLuint indices[6][4] = {
      {2, 3, 1, 0}, {1, 5, 4, 0}, {1, 3, 7, 5},
      {6, 7, 3, 2}, {4, 6, 2, 0}, {5, 7, 6, 4}};

   GLfloat d1[3], d2[3], norm[3];

   glBegin(GL_QUADS);
   for (int i = 0; i < 6; i++)
   {
      for(int j = 0; j < 3; j++)
      {
         d1[j] = vert[indices[i][0]][j] - vert[indices[i][1]][j];
         d2[j] = vert[indices[i][1]][j] - vert[indices[i][2]][j];
      }
      crossprod(d1, d2, norm);
	  //glNormal3f(norm[0],(-1)*norm[1],(-1)*norm[2]);
      glNormal3fv(norm);
      glVertex3fv(&vert[ indices[i][0] ][0]);
      glVertex3fv(&vert[ indices[i][1] ][0]);
      glVertex3fv(&vert[ indices[i][2] ][0]);
      glVertex3fv(&vert[ indices[i][3] ][0]);
   }
   glEnd();
}

/************************************************************ drawAppendage ****/
void drawAppendage(appendageState as, bool foot, unsigned char color1, unsigned char color2)
//
// Desc: Draws appendage beginning from top (of appendage) on center
// Pre:  as = the current state of the appendage (rotations, etc.)
//       foot == true, a foot will be drawn on the end of the appendage.
//       color1 = color of upper half of appendage
//       color2 = color of lower half of appendage
// Note: color1, color2 do not show up on screen; they are used to distinguish
//       between appendages for selection/picking from GL_BACK (buffer)
// 
{
   glPushMatrix();

   glRotatef(as.rotation, 1.0, 0.0, 0.0);   
   glTranslatef(0.0, -0.375, 0.0);

   glColor3ub(color1, 0, 0);

   glPushMatrix();
   glScalef(0.3, 0.75, 0.30);
   glutSolidCube(1.0);
   glPopMatrix();
   
   glTranslatef(0.0, -0.4, 0.0);
   glutSolidSphere(0.2, 10, 5);

   glColor3ub(color2, 0, 0);

   glRotatef(as.jointrot, 1.0, 0.0, 0.0);

   glTranslatef(0.0, -0.5, 0.0);
   
   glPushMatrix();
   glScalef(0.3, 0.75, 0.30);
   glutSolidCube(1.0);
   
   glPopMatrix();

   if (foot)
   {
      glRotatef(as.footrot, 1.0, 0.0, 0.0);
      glTranslatef(0.0, -0.4, 0.2);
      glPushMatrix();
      glScalef(0.3, 0.15, 0.75);
      glutSolidCube(1.0);
      glPopMatrix();
   }
   glPopMatrix();
}

/**************************************************************** drawRobot ****/
void drawRobot(void)
//
// Desc: Draws the robot
//
{
   glColor3ub(0,0,0);
   glPushMatrix();
   glTranslatef(0.0, RS.vertPos, 0.0);
   glRotatef(RS.rotation, 1.0, 0.0, 0.0);

   // torso
   glPushMatrix();
   //decideColor(3);
   glTranslatef(0.0, 0.25, 0.0);
   	//glutSolidSphere(3,10,10);
   drawFrustum(1.0, 0.65, 1.0, 0.65);
   glTranslatef(0.0, -0.75, 0.0);
   drawFrustum(0.55, 0.70, 0.5, 0.5);   
   glPopMatrix();

   // head with eyes
   glPushMatrix();
   //decideColor(4);
   throwLight(2);
   glTranslatef(0.0, 0.75, 0.0);
   glutSolidSphere(0.2, 10, 5);
   glTranslatef(0.0, 0.60, 0.0);
   glutSolidSphere(0.45, 30, 20);
   glTranslatef(0.15, 0.05, 0.4);
   glutSolidSphere(0.08, 20, 10);
   glTranslatef(-0.3, 0.0, 0.0);
   glutSolidSphere(0.08, 20, 10);
   
   glPopMatrix();
	
   // torso joints
   glPushMatrix();
   //decideColor(3);
	if(more_bullets==0)
		decideDirection();
   //right arm joint
   glTranslatef(0.5, 0.75, 0.0);
   glutSolidSphere(0.2, 10, 5);
   
   //left arm joint
   glTranslatef(-1.0, 0.0, 0.0);
   
   glutSolidSphere(0.2, 10, 5);
   glTranslatef(0.25, -1.6, 0.0);
   glutSolidSphere(0.2, 10, 5);
   glTranslatef(0.5, 0.0, 0.0);
   glutSolidSphere(0.2, 10, 5);
   glPopMatrix();

   // arms
   glPushMatrix();
   if(more_bullets==0)
		decideDirection();
   //decideColor(2);
   glTranslatef(0.80, 0.9, 0.0);
   drawAppendage(ArmL, false, 8, 16);  // don't draw feet
   glTranslatef(-1.60, 0.0, 0.0);
   drawBullet();
   throwLight(1);
   drawAppendage(ArmR, false, 25, 33);  // don't draw feet
   
   glPopMatrix();
   // legs
   glPushMatrix();
	decideDirection();	
   glTranslatef(0.25, -1.0, 0.0);
	//decideColor(1);
	drawAppendage(LegL, true, 41, 49);   // draw feet
	glTranslatef(-0.5, 0.0, 0.0);
	drawAppendage(LegR, true, 58, 66);   // draw feet

	glPopMatrix();
   glPopMatrix();
   glDisable(GL_LIGHT3);
	glDisable(GL_LIGHT4);
   
}

void drawDeadRobot(void)
//
// Desc: Draws the robot
//
{
   glColor3ub(0,0,0);
   glPushMatrix();
   glTranslatef(0.0, RS.vertPos, 0.0);
   glRotatef(RS.rotation, 1.0, 0.0, 0.0);

   // torso
   glPushMatrix();
   //decideColor(3);
   glTranslatef(0.0, -2.2, 0.0);
   glRotatef(90,1.0,0.0,0.0);
   	//glutSolidSphere(3,10,10);
   drawFrustum(1.0, 0.65, 1.0, 0.65);
   glTranslatef(0.0, -0.75, 0.0);
   drawFrustum(0.55, 0.70, 0.5, 0.5);   
   glPopMatrix();

   // arms
   glPushMatrix();
   if(more_bullets==0)
		decideDirection();
   //decideColor(2);
   glTranslatef(0.80, -2.2, 0.0);
   glRotatef(90,1.0,0.0,0.0);
   drawAppendage(ArmL, false, 8, 16);  // don't draw feet
   glTranslatef(-1.60, 0.0, 0.0);
   drawBullet();
   throwLight(1);
   drawAppendage(ArmR, false, 25, 33);  // don't draw feet
   
   glPopMatrix();
   // legs
   glPushMatrix();
	decideDirection();	
   glTranslatef(0.25, -2.2, 0.0);
   glRotatef(90,1.0,0.0,0.0);
   glRotatef(90,0.0,0.0,1.0);
	//decideColor(1);
	drawAppendage(LegL, true, 41, 49);   // draw feet
	glTranslatef(-0.5, 0.0, 0.0);
	glRotatef(90,1.0,0.0,0.0);
	glRotatef(90,0.0,0.0,1.0);
	drawAppendage(LegR, true, 58, 66);   // draw feet

	glPopMatrix();
   glPopMatrix();
   glDisable(GL_LIGHT3);
	glDisable(GL_LIGHT4);
   
}

float randomFloat() {
	return (float)rand() / ((float)RAND_MAX + 1);
}

void decideDirection()
{
	switch(direction_of_motion)
	{
	case 2:		
		glRotatef(-90,0,1,0);
		break;
	case 3:		
		glRotatef(90,0,1,0);
		break;
	//case 4: glRotatef(180,0,1,0);
	//	break;
	default : break;
	}
	
}

void throwLight(int mode)
{
	if(more_bullets>0)
	{
		
		GLfloat light_pos[] = { 0.0, 0.0, 0.0, 1.0 };
		GLfloat light_dir[] = { 0.0, 0.0, -1.0, 0.0 };
		GLfloat red[] = { 0.6f, 0.0f, 0.0, 1.0 };
		GLfloat white[] = { 1.0, 1.0, 1.0, 1.0 };
		GLfloat grey[] = { 0.5, 0.5, 0.5, 1.0 };
		GLfloat black[] = { 0.0, 0.0, 0.0, 1.0 };
		GLfloat dull[] = { 100.0 };
		GLfloat blue[] = { 0.0, 0.2f, 1.0, 1.0 };
		glPushMatrix();
		if(mode==1)
		{
			//glRotatef(180,0,1,0);
			glTranslatef(0.5,0.7,3);
			//glutSolidSphere(1,10,10);
			glLightfv(GL_LIGHT3, GL_POSITION, light_pos);
			glLightfv(GL_LIGHT3, GL_DIFFUSE, red);
			glLightfv(GL_LIGHT3, GL_AMBIENT, red);
			//const GLfloat *cut=15.0;
			//*cut = 15.0;
			glLightf(GL_LIGHT3, GL_SPOT_CUTOFF, 25);
			glLightfv(GL_LIGHT3, GL_SPOT_DIRECTION,light_dir);
			//glLightfv(GL_LIGHT3, GL_SPECULAR, white);
			glLightf(GL_LIGHT3, GL_LINEAR_ATTENUATION, 0.1);
			glLightf(GL_LIGHT3, GL_QUADRATIC_ATTENUATION, 0.005);
			glEnable(GL_LIGHT3);
		}
		else if(mode==2)
		{
			glTranslatef(-0.6,0.7,3);
			//glutSolidSphere(0.5,10,10);
			glLightfv(GL_LIGHT4, GL_POSITION, light_pos);
			glLightfv(GL_LIGHT4, GL_DIFFUSE, red);
			glLightfv(GL_LIGHT4, GL_AMBIENT, red);
			//const GLfloat *cut=15.0;
			//*cut = 15.0;
			glLightf(GL_LIGHT4, GL_SPOT_CUTOFF, 10);
			glLightfv(GL_LIGHT4, GL_SPOT_DIRECTION,light_dir);
			//glLightfv(GL_LIGHT3, GL_SPECULAR, white);
			glLightf(GL_LIGHT4, GL_LINEAR_ATTENUATION, 0.1);
			glLightf(GL_LIGHT4, GL_QUADRATIC_ATTENUATION, 0.005);
			glEnable(GL_LIGHT4);
		}


		glPopMatrix();	
	}
	else
	{
		//glDisable(GL_LIGHT3);
		//glDisable(GL_LIGHT4);
	}

	

}

void drawBullet()
{
	if(shoot==true)
	{
		//cout<<"entered";
	    if(more_bullets==1)
	    {
			float random;
			random = randomFloat();
			if(random<0.4)
				random = 0.4;
			random = (-1)*random; //-0.5 was default
			bullet* temp = new bullet(1,random,200,parent);
			quadtree->add(temp);
			theworldsend->next = (object_pr *)temp;
			temp->previous = theworldsend;
			theworldsend = (object_pr*)temp;		
			theworldsend->next = NULL;
		
			//B[number_of_bullets].init(1,-0.5,200,parent);
			//temp->init();
			if(number_of_bullets+1 == Max_bullets)
				number_of_rounds++;
			number_of_bullets = (number_of_bullets + 1)%Max_bullets;
			//more_bullets=0;
			shoot = false;
		}
	    //glPushMatrix();
		//int max_limit;
		//if(number_of_rounds>0)
		//	max_limit = Max_bullets;
		//else
		//	max_limit = number_of_bullets;
		//cout<<max_limit<<endl;
		//for(int i=0;i<max_limit;i++)
		//{
		//	if(B[i].Particle[0].Visible==true)
		//	{
				//  cout<<"inside"<<endl;
		//		B[i].glDrawParticles();
		//	}
			//glDisable(GL_LIGHTING);
		//}
		//glPopMatrix();
	} 
}

/****************************************************************** animate ****/
void animate(void)
//
// Desc: Modififies robot and appendage state info for the robot
//       Calling this function successively and displaying the
//       updated frame buffer in between will illustrate the appearance
//       of a walking/running robot
// Note: i and j are global cycle variables
//
{
   // Robot State /////////////////////////
	//cout<<"CALLED"<<endl;
	if(more_bullets==0)//(shoot==false)
	{
   if (RS.bounce == UP)
   {
      if (i == 30)
      {
         RS.vertPos = 0.635;
         RS.bounce = DOWN;
      }
      else RS.vertPos += 0.0075;
   }
   else
   {
      if (i == 30)
      {
         RS.vertPos = 0.41;
         RS.bounce = UP;
      }
      else RS.vertPos -= 0.0075;
   }
   if (RS.lean == FORWARD)
   {
      if (i == 30)
      {
         RS.rotation = 9.0;
         RS.lean = BACKWARD;
      }
      else RS.rotation += 0.3;
   }
   else
   {
      if (i == 30)
      {
         RS.rotation = 0.0;
         RS.lean = FORWARD;
      }
      else RS.rotation -= 0.3;
   }
	}
   // Left Arm ////////////////////////////
	if(more_bullets==0 || direction_of_motion==1 || direction_of_motion==4)
	{
		if (ArmL.dMain == FORWARD)
		{
			if (j == 61)
			{
				ArmL.rotation = -42.7;
				ArmL.dMain = BACKWARD;
			}
			else ArmL.rotation -= 1.4;
		}
		else
		{
			if (j == 61)
			{
				ArmL.rotation = 42.7;
				ArmL.dMain = FORWARD;
			}
			else ArmL.rotation += 1.4;
		}
		if (ArmL.dSecondary == FORWARD)
		{
			if (j == 61)
			{
				ArmL.jointrot = -85.4;
				ArmL.dSecondary = BACKWARD;
			}
			else ArmL.jointrot -= 1.4;
		}
		else
		{
			if (j == 61)
			{
				ArmL.jointrot = 0.0;
				ArmL.dSecondary = FORWARD;
			}
			else ArmL.jointrot += 1.4;
		}
	}

   // Right Arm ///////////////////////////
   if(more_bullets==0) //shoot == false
   {
	 //  cout<<"Entered";
	   if (ArmR.dMain == FORWARD)
	   {
		   if (j == 61)
		   {
			   ArmR.rotation = -42.7;
			   ArmR.dMain = BACKWARD;
		   }
		   else ArmR.rotation -= 1.4;
	   }
	   else
	   {
		   if (j == 61)
		   {
			   ArmR.rotation = 42.7;
			   ArmR.dMain = FORWARD;
		   }
		   else ArmR.rotation += 1.4;
	   }
	   if (ArmR.dSecondary == FORWARD)
		{
			if (j == 61)
			{
				ArmR.jointrot = -85.4;
				ArmR.dSecondary = BACKWARD;
			}
			else ArmR.jointrot -= 1.4;
		}
		else
		{
			if (j == 61)
			{
				ArmR.jointrot = 0.0;
				ArmR.dSecondary = FORWARD;
			}
			else ArmR.jointrot += 1.4;
		}
   }
   //else
   //{
	 //  checker=0;
	//	resetAnimation1();
	//	cout<<"TATA"<<endl;
//   }
   
   // Left Leg ////////////////////////////

   if (LegL.dMain == FORWARD)
   {
      if (j == 61)
      {
         LegL.rotation = -42.7;
         LegL.dMain = BACKWARD;
      }
      else LegL.rotation -= 1.4;
   }
   else
   {
      if (j == 61)
      {
         LegL.rotation = 42.7;
         LegL.dMain = FORWARD;
      }
      else LegL.rotation += 1.4;
   }
   if (LegL.dSecondary == FORWARD)
   {
      if (j == 61)
      {
         LegL.jointrot = 0.0;
         LegL.dSecondary = BACKWARD;
      }
      else LegL.jointrot -= 1.4;
   }
   else
   {
      if (j == 61)
      {
         LegL.jointrot = 85.4;
         LegL.dSecondary = FORWARD;
      }
      else LegL.jointrot += 1.4;
   }

   if (LegL.dfoot == FORWARD)
   {
      if (i == 30)
      {
         LegL.footrot = -25.2; 
         LegL.dfoot = BACKWARD;
      }
      else LegL.footrot -= 0.84;
   }
   else
   {
      if (i == 30)
      {
         LegL.footrot = 0.0;
         LegL.dfoot = FORWARD;
      }
      else LegL.footrot += 0.84;
   }

   // Right Leg ///////////////////////////

   if (LegR.dMain == FORWARD)
   {
      if (j == 61)
      {
         LegR.rotation = -42.7;
         LegR.dMain = BACKWARD;
      }
      else LegR.rotation -= 1.4;
   }
   else
   {
      if (j == 61)
      {
         LegR.rotation = 42.7;
         LegR.dMain = FORWARD;
      }
      else LegR.rotation += 1.4;
   }
   if (LegR.dSecondary == FORWARD)
   {
      if (j == 61)
      {
         LegR.jointrot = 0.0;
         LegR.dSecondary = BACKWARD;
      }
      else LegR.jointrot -= 1.4;
   }
   else
   {
      if (j == 61)
      {
         LegR.jointrot = 85.4;
         LegR.dSecondary = FORWARD;
      }
      else LegR.jointrot += 1.4;
   }
   if (LegR.dfoot == FORWARD)
   {
      if (i == 30)
      {
         LegR.footrot = -25.2; 
         LegR.dfoot = BACKWARD;
      }
      else LegR.footrot -= 0.84;
   }
   else
   {
      if (i == 30)
      {
         LegR.footrot = 0.0;
         LegR.dfoot = FORWARD;
      }
      else LegR.footrot +=  0.84;
   }

   if (i == 30) // reverse direction if at end of smaller cycle
      i = 0;    //   used for feet
   else
      i++;

   if (j == 61) // reverse direction if at end of larger cycle
      j = 0;    //   used for arms and legs
   else
      j++;
   //cout<<i<<" "<<j<<endl;
}


void resetAnimation(void)
//
// Desc: Get all appendages back to initial positions so the animation
//       looks normal when restarted.
//
// appendageState ArmL  = {42.7, 0.0, 0.0, FORWARD, FORWARD, NONE};
// appendageState ArmR  = {-42.7, -85.4, 0.0, BACKWARD, BACKWARD, NONE};
// appendageState LegL  = {-42.7, 0.0, 0.0,  BACKWARD, BACKWARD, FORWARD};
// appendageState LegR  = {42.7, 85.4, 0.0, FORWARD, FORWARD, FORWARD};
// robotState     RS    = {0.41, 9.0, UP, BACKWARD};
//
{
   bool good2go = true; // if this is true at end, the reset is complete

   // if this is the first time in this function since moved has been set
   // to true and the user has requested animation...set 'incrementors' 
   // to use to get each appendage back to the original start position
   // and have all appendages gradually move back so they all arrive at 
   // the start position at the same time

   if (!reset_in_progress) 
   {
      const float step = 1.0;

      rsv = (RS.vertPos - 0.41) / step;
      rsr = (9.0 - RS.rotation) / step;

      alr = (42.7 - ArmL.rotation) / step;
      als = (0.0 - ArmL.jointrot) / step;
      arr = (ArmR.rotation + 42.7) / step;
      ars = (ArmR.jointrot + 85.4) / step;

      llr = (LegL.rotation + 42.7) / step;
      lls = (LegL.jointrot) / step;
      llf = (0.0 - LegL.footrot) / step;
      lrr = (42.7 - LegR.rotation) / step;
      lrs = (85.4 - LegR.jointrot) / step;
      lrf = (0.0 - LegR.footrot) / step;
      
      reset_in_progress = true;  // a reset is in progress
                                 //   do not to above again
   }

   // Robot State ///////////////

   RS.vertPos -= rsv;
   if (RS.vertPos <= 0.5225)
   {
      RS.vertPos = 0.5225;
      RS.bounce = UP;
   }
   else good2go = false;

   RS.rotation += rsr;
   if (RS.rotation >= 4.5)
   {
      RS.rotation = 4.5;
      RS.lean = BACKWARD;
   }
   else good2go = false;

   // Left Arm //////////////////

   ArmL.rotation += alr;
   if (ArmL.rotation >= 0.0)
   {
      ArmL.rotation = 0.0;
      ArmL.dMain = FORWARD;
   }
   else good2go = false;

   ArmL.jointrot += als;
   if (ArmL.jointrot >= -42.7)
   {
      ArmL.jointrot = -42.7;
      ArmL.dSecondary = FORWARD;
   }
   else good2go = false;

   // Right Arm /////////////////

   ArmR.rotation -= arr;
   if (ArmR.rotation <= 0.0)
   {
      ArmR.rotation = 0.0;
      ArmR.dMain = BACKWARD;
   }
   else good2go = false;

   ArmR.jointrot -= ars;
   if (ArmR.jointrot <= -42.7)
   {
      ArmR.jointrot = -42.7;
      ArmR.dSecondary = BACKWARD;
   }
   else good2go = false;

   // Left Leg //////////////////

   LegL.rotation -= llr;
   if (LegL.rotation <= 0.0)
   {
      LegL.rotation = 0.0;
      LegL.dMain = BACKWARD;
   }
   else good2go = false;

   LegL.jointrot -= lls;
   if (LegL.jointrot <= 42.7)
   {
      LegL.jointrot = 42.7;
      LegL.dSecondary = BACKWARD;
   }
   else good2go = false;

   LegL.footrot += llf;
   if (LegL.footrot >= -12.6)
   {
      LegL.footrot = -12.6;
      LegL.dfoot = FORWARD;
   }
   else good2go = false;

   // Right Leg /////////////////

   LegR.rotation += lrr;
   if (LegR.rotation >= 0.0)
   {
      LegR.rotation = 0.0;
      LegR.dMain = FORWARD;
   }
   else good2go = false;

   LegR.jointrot += lrs;
   if (LegR.jointrot >= 42.7)
   {
      LegR.jointrot = 42.7;
      LegR.dSecondary = FORWARD;
   }
   else good2go = false;

   LegR.footrot += lrf;
   if (LegR.footrot >= -12.6)
   {
      LegR.footrot = -12.6;
      LegR.dfoot = FORWARD;
   }
   else good2go = false;

   if (good2go)
   {
      moved = false;  // global: reset complete, continue animation
      i = 29;          // reset global animation controls
      j = 29;
      reset_in_progress = false; 
   }
}

void resetAnimation1(void)
//
// Desc: Get all appendages back to initial positions so the animation
//       looks normal when restarted.
//
// appendageState ArmL  = {42.7, 0.0, 0.0, FORWARD, FORWARD, NONE};
// appendageState ArmR  = {-42.7, -85.4, 0.0, BACKWARD, BACKWARD, NONE};
// appendageState LegL  = {-42.7, 0.0, 0.0,  BACKWARD, BACKWARD, FORWARD};
// appendageState LegR  = {42.7, 85.4, 0.0, FORWARD, FORWARD, FORWARD};
// robotState     RS    = {0.41, 9.0, UP, BACKWARD};
//
{
   bool good2go = true; // if this is true at end, the reset is complete

   // if this is the first time in this function since moved has been set
   // to true and the user has requested animation...set 'incrementors' 
   // to use to get each appendage back to the original start position
   // and have all appendages gradually move back so they all arrive at 
   // the start position at the same time

   if (!reset_in_progress) 
   {
      const float step = 1.0;

	  rsv = (RS.vertPos - 0.41) / step;
      rsr = (9.0 - RS.rotation) / step;

      //alr = (42.7 - ArmL.rotation) / step;
      //als = (0.0 - ArmL.jointrot) / step;
      arr = (ArmR.rotation + 32.7) / step;
      ars = (ArmR.jointrot + 65.4) / step;
      //reset_in_progress = true;  // a reset is in progress
      

      //rsv = (RS.vertPos - 0.41) / step;
      //rsr = (9.0 - RS.rotation) / step;

      alr = (42.7 - ArmL.rotation) / step;
      als = (0.0 - ArmL.jointrot) / step;
      //arr = (ArmR.rotation + 42.7) / step;
      //ars = (ArmR.jointrot + 85.4) / step;

      llr = (LegL.rotation + 42.7) / step;
      lls = (LegL.jointrot) / step;
      llf = (0.0 - LegL.footrot) / step;
      lrr = (42.7 - LegR.rotation) / step;
      lrs = (85.4 - LegR.jointrot) / step;
      lrf = (0.0 - LegR.footrot) / step;
      
      reset_in_progress = true;  // a reset is in progress
                                 //   do not to above again
   }

   // Robot State ///////////////

   RS.vertPos -= rsv;
   if (RS.vertPos <= 0.41)
   {
      RS.vertPos = 0.41;
      RS.bounce = UP;
   }
   else good2go = false;

   RS.rotation += rsr;
   if (RS.rotation >= 9.0)
   {
      RS.rotation = 9.0;
      RS.lean = BACKWARD;
   }
   else good2go = false;

   // Left Arm //////////////////

   ArmL.rotation += alr;
   if (ArmL.rotation >= 0.0)
   {
      ArmL.rotation = 0.0;
      ArmL.dMain = FORWARD;
   }
   else good2go = false;

   ArmL.jointrot += als;
   if (ArmL.jointrot >= -42.7)
   {
      ArmL.jointrot = -42.7;
      ArmL.dSecondary = FORWARD;
   }
   else good2go = false;

   // Right Arm /////////////////
   ArmR.rotation -= arr;
   if (ArmR.rotation <= -32.7)
   {
      ArmR.rotation = -32.7;
      ArmR.dMain = BACKWARD;
   }
   else good2go = false;

   ArmR.jointrot -= ars;
   if (ArmR.jointrot <= -65.4)
   {
      ArmR.jointrot = -65.4;
      ArmR.dSecondary = BACKWARD;
   }
   else good2go = false;


   // Left Leg //////////////////

   LegL.rotation -= llr;
   if (LegL.rotation <= 0.0)
   {
      LegL.rotation = 0.0;
      LegL.dMain = BACKWARD;
   }
   else good2go = false;

   LegL.jointrot -= lls;
   if (LegL.jointrot <= 42.7)
   {
      LegL.jointrot = 42.7;
      LegL.dSecondary = BACKWARD;
   }
   else good2go = false;

   LegL.footrot += llf;
   if (LegL.footrot >= -12.6)
   {
      LegL.footrot = -12.6;
      LegL.dfoot = FORWARD;
   }
   else good2go = false;

   // Right Leg /////////////////

   LegR.rotation += lrr;
   if (LegR.rotation >= 0.0)
   {
      LegR.rotation = 0.0;
      LegR.dMain = FORWARD;
   }
   else good2go = false;

   LegR.jointrot += lrs;
   if (LegR.jointrot >= 42.7)
   {
      LegR.jointrot = 42.7;
      LegR.dSecondary = FORWARD;
   }
   else good2go = false;

   LegR.footrot += lrf;
   if (LegR.footrot >= -12.6)
   {
      LegR.footrot = -12.6;
      LegR.dfoot = FORWARD;
   }
   else good2go = false;

   if (good2go)
   {
      moved = false;  // global: reset complete, continue animation
    //  i = 29;          // reset global animation controls
     // j = 29;
      reset_in_progress = false; 
   }
}

void resetAnimation3(void)
//
// Desc: Get all appendages back to initial positions so the animation
//       looks normal when restarted.
//
// appendageState ArmL  = {42.7, 0.0, 0.0, FORWARD, FORWARD, NONE};
// appendageState ArmR  = {-42.7, -85.4, 0.0, BACKWARD, BACKWARD, NONE};
// appendageState LegL  = {-42.7, 0.0, 0.0,  BACKWARD, BACKWARD, FORWARD};
// appendageState LegR  = {42.7, 85.4, 0.0, FORWARD, FORWARD, FORWARD};
// robotState     RS    = {0.41, 9.0, UP, BACKWARD};
//
{
   bool good2go = true; // if this is true at end, the reset is complete

   // if this is the first time in this function since moved has been set
   // to true and the user has requested animation...set 'incrementors' 
   // to use to get each appendage back to the original start position
   // and have all appendages gradually move back so they all arrive at 
   // the start position at the same time

   if (!reset_in_progress) 
   {
      const float step = 1.0;

	  rsv = (RS.vertPos - 0.5225) / step;
      rsr = (4.5 - RS.rotation) / step;

      //alr = (42.7 - ArmL.rotation) / step;
      //als = (0.0 - ArmL.jointrot) / step;
      arr = (ArmR.rotation + 32.7) / step;
      ars = (ArmR.jointrot + 65.4) / step;
      //reset_in_progress = true;  // a reset is in progress
      

      //rsv = (RS.vertPos - 0.41) / step;
      //rsr = (9.0 - RS.rotation) / step;

      alr = (42.7 - ArmL.rotation) / step;
      als = (0.0 - ArmL.jointrot) / step;
      //arr = (ArmR.rotation + 42.7) / step;
      //ars = (ArmR.jointrot + 85.4) / step;

      llr = (LegL.rotation + 0.0) / step;
      lls = (LegL.jointrot+0.0) / step;
      llf = (-12.6 - LegL.footrot) / step;
      lrr = (0.0 - LegR.rotation) / step;
      lrs = (0.0 - LegR.jointrot) / step;
      lrf = (12.6 - LegR.footrot) / step;
      
      reset_in_progress = true;  // a reset is in progress
                                 //   do not to above again
   }

   // Robot State ///////////////

   RS.vertPos -= rsv;
   if (RS.vertPos <= 0.5225)
   {
      RS.vertPos = 0.5225;
      RS.bounce = UP;
   }
   else good2go = false;

   RS.rotation += rsr;
   if (RS.rotation >= 4.5)
   {
      RS.rotation = 4.5;
      RS.lean = BACKWARD;
   }
   else good2go = false;

   // Left Arm //////////////////

   ArmL.rotation += alr;
   if (ArmL.rotation >= 0.0)
   {
      ArmL.rotation = 0.0;
      ArmL.dMain = FORWARD;
   }
   else good2go = false;

   ArmL.jointrot += als;
   if (ArmL.jointrot >= -42.7)
   {
      ArmL.jointrot = -42.7;
      ArmL.dSecondary = FORWARD;
   }
   else good2go = false;

   // Right Arm /////////////////
   ArmR.rotation -= arr;
   if (ArmR.rotation <= -32.7)
   {
      ArmR.rotation = -32.7;
      ArmR.dMain = BACKWARD;
   }
   else good2go = false;

   ArmR.jointrot -= ars;
   if (ArmR.jointrot <= -65.4)
   {
      ArmR.jointrot = -65.4;
      ArmR.dSecondary = BACKWARD;
   }
   else good2go = false;


   // Left Leg //////////////////

   LegL.rotation -= llr;
   if (LegL.rotation <= 0.0)
   {
      LegL.rotation = 0.0;
      LegL.dMain = BACKWARD;
   }
   else good2go = false;

   LegL.jointrot -= lls;
   if (LegL.jointrot <= 0.0)
   {
      LegL.jointrot = 0.0;
      LegL.dSecondary = BACKWARD;
   }
   else good2go = false;

   LegL.footrot += llf;
   if (LegL.footrot <= -12.6)
   {
      LegL.footrot = -12.6;
      LegL.dfoot = FORWARD;
   }
   else good2go = false;

   // Right Leg /////////////////

   LegR.rotation += lrr;
   if (LegR.rotation >= 0.0)
   {
      LegR.rotation = 0.0;
      LegR.dMain = FORWARD;
   }
   else good2go = false;

   LegR.jointrot += lrs;
   if (LegR.jointrot >= 0.0)
   {
      LegR.jointrot = 0.0;
      LegR.dSecondary = FORWARD;
   }
   else good2go = false;

   LegR.footrot += lrf;
   if (LegR.footrot >= -12.6)
   {
      LegR.footrot = -12.6;
      LegR.dfoot = FORWARD;
   }
   else good2go = false;

   if (good2go)
   {
      moved = false;  // global: reset complete, continue animation
    //  i = 29;          // reset global animation controls
     // j = 29;
      reset_in_progress = false; 
   }
}

void resetAnimation4(void)
//
// Desc: Get all appendages back to initial positions so the animation
//       looks normal when restarted.
//
// appendageState ArmL  = {42.7, 0.0, 0.0, FORWARD, FORWARD, NONE};
// appendageState ArmR  = {-42.7, -85.4, 0.0, BACKWARD, BACKWARD, NONE};
// appendageState LegL  = {-42.7, 0.0, 0.0,  BACKWARD, BACKWARD, FORWARD};
// appendageState LegR  = {42.7, 85.4, 0.0, FORWARD, FORWARD, FORWARD};
// robotState     RS    = {0.41, 9.0, UP, BACKWARD};
//
{
   bool good2go = true; // if this is true at end, the reset is complete

   // if this is the first time in this function since moved has been set
   // to true and the user has requested animation...set 'incrementors' 
   // to use to get each appendage back to the original start position
   // and have all appendages gradually move back so they all arrive at 
   // the start position at the same time

   if (!reset_in_progress) 
   {
      const float step = 1.0;

	  rsv = (RS.vertPos - 0.5225) / step;
      rsr = (4.5 - RS.rotation) / step;

      //alr = (42.7 - ArmL.rotation) / step;
      //als = (0.0 - ArmL.jointrot) / step;
      arr = (ArmR.rotation + 0.0) / step;
      ars = (ArmR.jointrot + 65.4) / step;
      //reset_in_progress = true;  // a reset is in progress
      

      //rsv = (RS.vertPos - 0.41) / step;
      //rsr = (9.0 - RS.rotation) / step;

      alr = (42.7 - ArmL.rotation) / step;
      als = (0.0 - ArmL.jointrot) / step;
      //arr = (ArmR.rotation + 42.7) / step;
      //ars = (ArmR.jointrot + 85.4) / step;

      llr = (LegL.rotation + 0.0) / step;
      lls = (LegL.jointrot+0.0) / step;
      llf = (-12.6 - LegL.footrot) / step;
      lrr = (0.0 - LegR.rotation) / step;
      lrs = (0.0 - LegR.jointrot) / step;
      lrf = (12.6 - LegR.footrot) / step;
      
      reset_in_progress = true;  // a reset is in progress
                                 //   do not to above again
   }

   // Robot State ///////////////

   RS.vertPos -= rsv;
   if (RS.vertPos <= 0.5225)
   {
      RS.vertPos = 0.5225;
      RS.bounce = UP;
   }
   else good2go = false;

   RS.rotation += rsr;
   if (RS.rotation >= 4.5)
   {
      RS.rotation = 4.5;
      RS.lean = BACKWARD;
   }
   else good2go = false;

   // Left Arm //////////////////

   ArmL.rotation += alr;
   if (ArmL.rotation >= 0.0)
   {
      ArmL.rotation = 0.0;
      ArmL.dMain = FORWARD;
   }
   else good2go = false;

   ArmL.jointrot += als;
   if (ArmL.jointrot >= -42.7)
   {
      ArmL.jointrot = -42.7;
      ArmL.dSecondary = FORWARD;
   }
   else good2go = false;

   // Right Arm /////////////////
   ArmR.rotation -= arr;
   if (ArmR.rotation <= 0.0)
   {
      ArmR.rotation = 0.0;
      ArmR.dMain = BACKWARD;
   }
   else good2go = false;

   ArmR.jointrot -= ars;
   if (ArmR.jointrot <= -65.4)
   {
      ArmR.jointrot = -65.4;
      ArmR.dSecondary = BACKWARD;
   }
   else good2go = false;


   // Left Leg //////////////////

   LegL.rotation -= llr;
   if (LegL.rotation <= 0.0)
   {
      LegL.rotation = 0.0;
      LegL.dMain = BACKWARD;
   }
   else good2go = false;

   LegL.jointrot -= lls;
   if (LegL.jointrot <= 0.0)
   {
      LegL.jointrot = 0.0;
      LegL.dSecondary = BACKWARD;
   }
   else good2go = false;

   LegL.footrot += llf;
   if (LegL.footrot <= -12.6)
   {
      LegL.footrot = -12.6;
      LegL.dfoot = FORWARD;
   }
   else good2go = false;

   // Right Leg /////////////////

   LegR.rotation += lrr;
   if (LegR.rotation >= 0.0)
   {
      LegR.rotation = 0.0;
      LegR.dMain = FORWARD;
   }
   else good2go = false;

   LegR.jointrot += lrs;
   if (LegR.jointrot >= 0.0)
   {
      LegR.jointrot = 0.0;
      LegR.dSecondary = FORWARD;
   }
   else good2go = false;

   LegR.footrot += lrf;
   if (LegR.footrot >= -12.6)
   {
      LegR.footrot = -12.6;
      LegR.dfoot = FORWARD;
   }
   else good2go = false;

   if (good2go)
   {
      moved = false;  // global: reset complete, continue animation
    //  i = 29;          // reset global animation controls
     // j = 29;
      reset_in_progress = false; 
   }
}

void resetAnimation2(void)
//
// Desc: Get all appendages back to initial positions so the animation
//       looks normal when restarted.
//
// appendageState ArmL  = {42.7, 0.0, 0.0, FORWARD, FORWARD, NONE};
// appendageState ArmR  = {-42.7, -85.4, 0.0, BACKWARD, BACKWARD, NONE};
// appendageState LegL  = {-42.7, 0.0, 0.0,  BACKWARD, BACKWARD, FORWARD};
// appendageState LegR  = {42.7, 85.4, 0.0, FORWARD, FORWARD, FORWARD};
// robotState     RS    = {0.41, 9.0, UP, BACKWARD};
//
{
   bool good2go = true; // if this is true at end, the reset is complete

   // if this is the first time in this function since moved has been set
   // to true and the user has requested animation...set 'incrementors' 
   // to use to get each appendage back to the original start position
   // and have all appendages gradually move back so they all arrive at 
   // the start position at the same time

   if (!reset_in_progress) 
   {
      const float step = 1.0;

	  rsv = (RS.vertPos - 0.41) / step;
      rsr = (9.0 - RS.rotation) / step;
	  alr = (42.7 - ArmL.rotation) / step;
      als = (0.0 - ArmL.jointrot) / step;
      
      //alr = (42.7 - ArmL.rotation) / step;
      //als = (0.0 - ArmL.jointrot) / step;
      arr = (ArmR.rotation + 32.7) / step;
      ars = (ArmR.jointrot + 65.4) / step;
      //reset_in_progress = true;  // a reset is in progress
      reset_in_progress = true;  // a reset is in progress
                                 //   do not to above again
   }

   // Robot State ///////////////

   RS.vertPos -= rsv;
   if (RS.vertPos <= 0.41)
   {
      RS.vertPos = 0.41;
      RS.bounce = UP;
   }
   else good2go = false;

   RS.rotation += rsr;
   if (RS.rotation >= 9.0)
   {
      RS.rotation = 9.0;
      RS.lean = BACKWARD;
   }
   else good2go = false;
	
   if((more_bullets>0) && (direction_of_motion==2 || direction_of_motion==3)) //shoot==true
   {
		ArmL.rotation += alr;
		if (ArmL.rotation >= 0.0)
		{
			ArmL.rotation = 0.0;
			ArmL.dMain = FORWARD;
		}
		else good2go = false;

		ArmL.jointrot += als;
		if (ArmL.jointrot >= -42.7)
		{
			ArmL.jointrot = -42.7;
			ArmL.dSecondary = FORWARD;
		}
		else good2go = false;
   }


 
   // Right Arm /////////////////
   ArmR.rotation -= arr;
   if (ArmR.rotation <= -32.7)
   {
      ArmR.rotation = -32.7;
      ArmR.dMain = BACKWARD;
   }
   else good2go = false;

   ArmR.jointrot -= ars;
   if (ArmR.jointrot <= -65.4)
   {
      ArmR.jointrot = -65.4;
      ArmR.dSecondary = BACKWARD;
   }
   else good2go = false;


   if (good2go)
   {
      moved = false;  // global: reset complete, continue animation
    //  i = 29;          // reset global animation controls
     // j = 29;
      reset_in_progress = false; 
   }
}


};

#endif


