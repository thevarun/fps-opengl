
#include <iostream>
#include "glInclude.h"
#include <math.h>
#include <iostream>
#include <sstream>
#include "enemy.h"
#include "panelrobot.h"
//#include "readSCN.h"
//#include "collisionstuff.h"
#include "text3d.h"
#include "objprimitive.h"
using namespace std;
#define NO_OF_ENEMIES 10
#define TIME_BETWEEN_CHECKS 25
//g++ ver1.c -o ver1 -lGL -lglut
class Quadtree;
Quadtree *quadtree;
extern Camera *camera;


//***************************************************************************************************************************

int r_w = 100, r_h = 20, r_d = 50;
//double curr_x = 0.0, curr_y = 5.0, curr_z = 20.0;
//double look_x = 0.0, look_y = 5.0, look_z = 0.0;
//double lookang = 0.0;
int window_width = 1,window_height =1 ;
string textdefault = "Mission: Kill all enemies";
string text = textdefault;
int text_disp_counter=0;

//light stuff
GLfloat light_pos[] = { 0.0, 0.0, 0.0, 1.0 };
GLfloat red[] = { 0.8f, 0.0, 0.0, 1.0 };
GLfloat white[] = { 1.0, 1.0, 1.0, 1.0 };
GLfloat grey[] = { 0.5, 0.5, 0.5, 1.0 };
GLfloat black[] = { 0.0, 0.0, 0.0, 1.0 };
GLfloat dull[] = { 100.0 };
GLfloat blue[] = { 0.0, 0.2f, 1.0, 1.0 };
bool lgt_1 = false;
int key_pressed=0;

//texture stuff
My_img texFloor;


//angle of rotation
double xpos = 0; 
double ypos = 0;
double zpos = -10;
double xrot = 0, yrot = 0, angle=0.0;
float lastx, lasty;
float scale = 1.0;
//Enemy e[NO_OF_ENEMIES];
 //int current_x;
 //int current_y;
void drawRoom();
void drawObj();

//Returns a random float from 0 to < 1

void init(){
  glShadeModel(GL_SMOOTH);
  glEnable(GL_LIGHTING);
  glEnable(GL_LIGHT0);
  GLfloat light_position[] = {1.0, 1.0, 1.0, 0.0};
   glLightfv(GL_LIGHT0, GL_POSITION, light_position);
  glEnable (GL_DEPTH_TEST);
  glDisable(GL_DITHER);
  glPixelStorei(GL_PACK_ALIGNMENT, 1);
  glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
  glClearColor(-1.0, 0.0, -1.0, 0.0);                   // bg color
	//*character = Robot;
  
  //e.shootAt[0] += 100;
  //for(int w=0;w< NO_OF_ENEMIES;w++)
	//  e[w].target = &Robot;

  //Robot->current_x = 100;
  //cout<<"HERE HERE HERE"<<endl;
  //cout<<Robot->current_x<<endl;
  //e.check();
  //cout<<endl;
  //glClearDepth(1.0);
  //glDepthFunc(GL_LESS); 

  //light
  float ambientLightModel[] = { 0.5, 0.5, 0.5, 1.0};
   //glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambientLightModel);
  //glLightfv(GL_LIGHT0, GL_DIFFUSE, white);
  //glLightfv(GL_LIGHT0, GL_SPECULAR, white);
  //glLightfv(GL_LIGHT0, GL_POSITION, light_pos);
  //glLightf(GL_LIGHT0, GL_LINEAR_ATTENUATION, 0.1);

  //material
 
  //glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
  glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, white);
  glMaterialfv(GL_FRONT, GL_SPECULAR, white);
  glMaterialfv(GL_FRONT, GL_SHININESS, dull);

	readTextScene("test2.scn");
   glEnable(GL_NORMALIZE);

}


void reshape(GLsizei W, GLsizei H){
//cout<<"not here yet?"<<endl;
	 window_width = W;
	 window_height = H;
	scale = W/2;
        GLfloat ratio = W*(1.0) / H;
        glViewport(0, 0, (GLsizei)W, (GLsizei)H);
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        //gluLookAt not defined ie using default
 	gluPerspective(45.0f,(GLfloat)W/(GLfloat)H, 1.0f,150.0f);
       // glOrtho(-7.0*ratio, 7.0*ratio, -7.0, 7.0, -10.0, 10.0);

	glutPostRedisplay();

}

void drawText(string text) {
	ostringstream oss;
	oss << text;
	string str = oss.str();
	
	glDisable(GL_TEXTURE_2D);
	glColor3f(1.0f, 1.0f, 0.0f);
	glPushMatrix();
		glTranslatef(3.0f, 6.0f, 0.0f);
		glScalef(0.4f, 0.4f, 0.4f);
		t3dDraw2D(str, 0, 0);
	glPopMatrix();
}

void drawPanel(){

////////////////////////////////////////2d panel/////////////////
glMatrixMode(GL_PROJECTION);
glDisable(GL_LIGHTING);
glPushMatrix();
	glLoadIdentity();
	//cout<<"check 0.7 "<<window_width<<" "<< window_height<<endl;
	double ratio = window_width/window_height;
	//cout<<"check 0.75"<<endl;
    glOrtho(-7.0*ratio, 7.0*ratio, -7.0, 7.0, -10.0, 10.0);
	//cout<<"check 0.8"<<endl;
glMatrixMode(GL_MODELVIEW);
glPushMatrix();
	glLoadIdentity();
	//cout<<"check 0.9"<<endl;
	drawText(text);
	//cout<<"check 1"<<endl;
	glPushMatrix();
		if(Robot->health>0)
		{
		//float xp = window_width*8/600 - 0.5;
		//float yp = window_height*12/600 - 0.5;
			glTranslatef(-5.0f,6.0f,0.0);
			glScaled(0.2,0.2,0.2);
			DrawRobot(0.0f, 0.0f, 0.0f);
		}
	glPopMatrix();
	//cout<<"check 2"<<endl;

	glPushMatrix();
		glTranslatef(0.0,7.0f,0.0);
		glColor3f(0.4,0.4,0.6);
		glBegin(GL_POLYGON);
                /*      This is the top face*/
                glVertex2f(-4.0f, 0.0f);
                glVertex2f(-4.0f, -2.0f);
                glVertex2f(6.0f, -2.0f);
				glVertex2f(6.0f, 0.0f);
		glEnd();
    glPopMatrix();
	//cout<<"check 3"<<endl;

glPopMatrix();
glMatrixMode(GL_PROJECTION);
glPopMatrix();
glMatrixMode(GL_MODELVIEW);
glEnable(GL_LIGHTING);
}

void display(){
//sequence of tasks required
//initialise
//camera
//player
//camera
//lights
//objects
//	
	//cout<<"draw"<<endl;
  glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
  glClearColor(0.0, 0.0, 0.0, 0.0);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
   glShadeModel(GL_SMOOTH);
   glEnable(GL_LIGHTING);

  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();

	drawPanel();//cout<<"panel drawed"<<endl;
	camera->applyCamera();
//cout<<"cameradone"<<endl;
glPushMatrix();  
  glColor3f(1.0, 1.0, 1.0);
  {
	glTranslatef(0.0, 0.0, -10.0);
	glColor3f(1.0, 0.5, 0.5);
	glutSolidSphere(0.5, 10, 10);
	
  }
  glPopMatrix();



//draw the world!!
	glPushMatrix();
	{
		object_pr *temp = theworld.next;
		while(temp != NULL){
			temp->display();
			temp = temp->next;
		}
	}
	glPopMatrix();
  glutSwapBuffers();
  //cout<<"outdraw"<<endl;
}


void keyboard(unsigned char key, int x, int y){
if(camera->attached){
	if (key=='w')
	{
		key_pressed=1;
		Robot->hero.is_moving=true;
		Robot->hero.direction_of_motion=1;

		float xrotrad, yrotrad;
		yrotrad = (camera->cam_yrot / 180 * 3.141592654f);
		xrotrad = (camera->cam_xrot / 180 * 3.141592654f);
		Robot->velocity[0] = (float(sin(yrotrad))) / TIME_BETWEEN_CHECKS;
		Robot->velocity[2] = (((-1)*float(cos(yrotrad))) / TIME_BETWEEN_CHECKS);
		//xpos += float(sin(yrotrad)) ;
		//zpos -= float(cos(yrotrad)) ;

		//ypos -= float(sin(xrotrad)) ;
		Robot->hero.animate();
	}

	if (key=='s')
	{
		key_pressed=1;
		Robot->hero.is_moving=true;
		Robot->hero.direction_of_motion=4;

		float xrotrad, yrotrad;
		yrotrad = (camera->cam_yrot / 180 * 3.141592654f);
		xrotrad = (camera->cam_xrot / 180 * 3.141592654f);

		Robot->velocity[0] = ((-1)* float(sin(yrotrad))) / TIME_BETWEEN_CHECKS;
		Robot->velocity[2] = float(cos(yrotrad)) / TIME_BETWEEN_CHECKS;
		//xpos -= float(sin(yrotrad));
		//zpos += float(cos(yrotrad)) ;
	//ypos += float(sin(xrotrad));
		
	}

	if (key=='d')
	{
		key_pressed=1;
		Robot->hero.is_moving=true;
		Robot->hero.direction_of_motion=2;

		float yrotrad;
		yrotrad = (yrot / 180 * 3.141592654f);
		Robot->velocity[0] = (float(cos(yrotrad)) * 0.2) / TIME_BETWEEN_CHECKS;
		Robot->velocity[2] = (float(sin(yrotrad)) * 0.2) / TIME_BETWEEN_CHECKS;
		//xpos += float(cos(yrotrad)) * 0.2;
		//zpos += float(sin(yrotrad)) * 0.2;
	}

	if (key=='a')
	{
		key_pressed=1;
		Robot->hero.is_moving=true;
		Robot->hero.direction_of_motion=3;

		float yrotrad;
		yrotrad = (yrot / 180 * 3.141592654f);
		Robot->velocity[0] = ((-1)*float(cos(yrotrad)) * (0.2)) / TIME_BETWEEN_CHECKS;
		Robot->velocity[2] = ((-1)*float(sin(yrotrad)) * (0.2)) / TIME_BETWEEN_CHECKS;
		//xpos -= float(cos(yrotrad)) * 0.2;
		//zpos -= float(sin(yrotrad)) * 0.2;
	}

	if(key == ' '){
		if(Robot->jumpPossible == true){
			Robot->velocity[1] = 0.025;
			Robot->jumpPossible = false;
		}
	}
}

else {//camera not attached
	if (key=='w')
	{
		float xrotrad, yrotrad;
		yrotrad = (camera->cam_yrot / 180 * 3.141592654f);
		xrotrad = (camera->cam_xrot / 180 * 3.141592654f);
		xpos += float(sin(yrotrad)) ;
		zpos -= float(cos(yrotrad)) ;

		ypos -= float(sin(xrotrad)) ;
	}

	if (key=='s')
	{
		float xrotrad, yrotrad;
		yrotrad = (camera->cam_yrot / 180 * 3.141592654f);
		xrotrad = (camera->cam_xrot / 180 * 3.141592654f);

		xpos -= float(sin(yrotrad));
		zpos += float(cos(yrotrad)) ;
		ypos += float(sin(xrotrad));
		
	}

	if (key=='d')
	{
		float yrotrad;
		yrotrad = (yrot / 180 * 3.141592654f);
		xpos += float(cos(yrotrad)) * 0.2;
		zpos += float(sin(yrotrad)) * 0.2;
	}

	if (key=='a')
	{
		float yrotrad;
		yrotrad = (yrot / 180 * 3.141592654f);
		xpos -= float(cos(yrotrad)) * 0.2;
		zpos -= float(sin(yrotrad)) * 0.2;
	}



}

	if(key == 'c')
		camera->detach();
	if(key == 'm')
		camera->mode();
	  if (key==27)
	  {
		//glutLeaveGameMode(); //set the resolution how it was
		exit(0); //quit the program
	  }
}



int init_over = 1;
void mouseMovement(int x, int y) {
	float diffx=x-lastx; //check the difference between the current x and the last x position
	float diffy=y-lasty; //check the difference between the current y and the last y position
	lastx=x; //set lastx to the current x position
	lasty=y; //set lasty to the current y position
	if(init_over++ == 1)	return;
	xrot += (float) diffy*180/scale; //set the xrot to xrot with the addition of the difference in the y position
	yrot += (float) diffx*180/scale; //set the xrot to yrot with the addition of the difference in the x position
	//glutPostRedisplay();
}

void key_up(unsigned char key, int x, int y)
{
	switch(key)
	{
	case 'w':
	case 'a':
	case 'd':
	case 's':
		Robot->velocity[0]=0.0;
	//	Robot->velocity[1]=0.0;
		Robot->velocity[2]=0.0;
		key_pressed=0;
		Robot->hero.is_moving=false;
		Robot->hero.direction_of_motion=1;
		break;
	}
	//glutPostRedisplay();
}

void idle(void){
	//Robot->resetAnimation();
	
	//Robot->idle();
	//check_call();
	
	if(key_pressed==0)
	{
		Robot->hero.is_moving=false;
		if(Robot->hero.shoot==false)
		{
			if(Robot->hero.more_bullets==0)
			{
				Robot->hero.resetAnimation();
			}
			else 
				Robot->hero.resetAnimation1();
		}
		else
		{
			
			Robot->hero.resetAnimation1();
			glutPostRedisplay();
		}
		glutPostRedisplay();
	}
		
	else if(key_pressed==1)
	{
		//Robot->animate();
		if(Robot->hero.more_bullets>0)
		{
			//cout<<"ENTERED";
			Robot->hero.resetAnimation2();
			glutPostRedisplay();
			Robot->hero.animate();
			glutPostRedisplay();
		}
		else
		{
			Robot->hero.animate();
			glutPostRedisplay();
		}
		
	}
	glutPostRedisplay();
}

void click(int button, int state, int x, int y)
{
	if(camera->attached == true){
		if(button==GLUT_LEFT_BUTTON && state ==	GLUT_DOWN)
		{
			//getColor(x,y);
			//Robot->shootAnimation();
			Robot->hero.shoot=true;
			Robot->should_reset = 0;
			if(key_pressed==0)
			{
				Robot->hero.resetAnimation1();
				glutPostRedisplay();
			}
			else
			{
				Robot->hero.resetAnimation2();
				glutPostRedisplay();
				Robot->hero.animate();
				glutPostRedisplay();
			}
			Robot->hero.more_bullets=1;
			//cout<<Robot->shoot<<endl;
			//idle();
			
		}
		else if(button==GLUT_LEFT_BUTTON && state ==GLUT_UP)
		{
			int i=0;
			int max_limit;
			Robot->hero.shoot=false;
			Robot->should_reset+=1;

		}
	}
}


void update(int value){
	//cout<<"update"<<endl;
	set<Object_Pair*> ops;
	quadtree->potentialCollisions(ops);
	for(set<Object_Pair*>::iterator it = ops.begin(); it != ops.end();
						it++) {
		Object_Pair* ob = *it;
		//Object_Pair op = <Object_Pair> 
		object_pr* o1;
		object_pr* o2;
		 o1 = ob->obj1;
		 o2 = ob->obj2;
			delete ob;
		if (o1->collideDetect(o2, true)) {
			o1->collide((object_pr*)o2);
			o2->collide((object_pr*)o1);
		//	numCollisions++;
		}
	}

	glutPostRedisplay();
		object_pr *temp = theworld.next;
	while(temp != NULL) {
		if( temp->id > 10){
			quadtree->remove(temp);
			temp->update_B(TIME_BETWEEN_CHECKS);
			quadtree->add(temp);
		}
		if(temp->id == 101 ){
			bullet* tt = (bullet*)temp;
			if(tt->live == 0){
				temp = temp->next;
				quadtree->remove(tt);
				delete tt;
				continue;
			}
		}
		temp = temp->next;
	}
	
	if(text!=textdefault)
	{
		text_disp_counter++;
		if(text_disp_counter%40==0)
		{
			text = textdefault;
			text_disp_counter=0;
		}
		
	}
	glutTimerFunc(TIME_BETWEEN_CHECKS, update, 0);
}


void initCollisionSystem()
		{
			
			quadtree = new Quadtree(-60, -60, 60, 60, 0);
			object_pr *temp = theworld.next;
			while(temp != NULL) 
			{
				quadtree->add(temp);
	   			temp = temp->next;
			}
			//glutTimerFunc(TIME_BETWEEN_CHECKS, update, 0);
		}


//user interaction
int main(int argc, char** argv)
{
    glutInit (&argc, argv);
	//t3dInit(); //Initialize text drawing functionality
    glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
   glutInitWindowSize (600, 600); 
//   glutGameModeString( "1440x900:32@60" ); //the settings for fullscreen mode
  // glutEnterGameMode(); //set glut to fullscreen using the settings in the line above
   glutInitWindowPosition (100, 100);
   glutCreateWindow ("First born");   
	//current_x = 100;
	//current_y=100;

   init();
   //quadtree = new Quadtree(-50, -50, 50, 50, 0);
    glutDisplayFunc(display);
   glutPassiveMotionFunc(mouseMovement);
    glutReshapeFunc (reshape);
   glutIdleFunc(idle);
   glutKeyboardFunc(keyboard);
   glutKeyboardUpFunc(key_up);
   glutMouseFunc(click);
   initCollisionSystem();
   glutTimerFunc(TIME_BETWEEN_CHECKS, update, 0);
   
   t3dInit();
	//cout<<"loop"<<endl;
    glutMainLoop();
	
	t3dCleanup();
}
