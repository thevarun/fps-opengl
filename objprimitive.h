#ifndef OBJ_PRIMITIVE
#define OBJ_PRIMITIVE
//#include<GL/gl.h>
#include "glInclude.h"
#include <math.h>
#include "readSCN.h"
#include <iostream>
//#include "collisionstuff.h"
using namespace std;
///////////////////////////
/// Design choices
/// Children are only for ease of room specification
/// Children and parents act as one for collision detection . Only parent modified on collision
/// need to change!!!! no children as data structure....only in file syntax

#define CHAR_ID 99
#define ENEMY_ID 100
#define BULLET_ID 101
#define OBJ_ID 1
#define WALL_ID 2
#define FLOOR_ID 3
#define POWER_ID 11
#define ID_CAMERA 12
#define BOX_ID 4

class character;
extern character *Robot ;
class Quadtree;
extern Quadtree *quadtree;
class Camera;
extern Camera *camera;
extern double xrot, yrot;
extern double xpos, ypos, zpos;

void rotateVec(double front_rotated[3], double base_fr[3], double rotvec[3], double ang);

class object_pr {
public:
	//render with up vec [0 1 0] and front vectore [0 0 -1]
	int id;
	//double rad;
	double base_up[3] ;
	double base_fr[3] ;
	virtual void draw() {cout<<"you should never ever be here"<<endl;};
	bool isCylinder;

	double upvec[3];
	double frontvec[3] ;
	double pos[3] ;
	double scale[3] ;
	void display() {
		double rotvec[3];
		double rotvec2[3];
		glPushMatrix();
		//orient the up vec in the correct dirn first
			glTranslated(pos[0], pos[1], pos[2]);
			double ang = dotprodang(upvec, base_up);//angle returned in deg
			double front_rotated[3] = {0.0, 0.0, -1.0};
			if(ang >= 5){
			//	cout<<ang<<endl;
				crossprod(upvec, base_up, rotvec);
				rotate_vector(front_rotated, rotvec, ang);
			}
			//up vec now aligned
			double ang1 = dotprodang(frontvec, front_rotated);
			if(ang1 >= 5 ){
			//	cout<<"2nd"<<ang1<<endl;
				if(ang1 < 175){
					crossprod(frontvec, front_rotated, rotvec2);
					glRotated(ang1, rotvec2[0], rotvec2[1], rotvec2[2]);
				}
				else glRotated(ang1, upvec[0], upvec[1], upvec[2]);
			}
			if(ang >= 5){
				glRotated(ang, rotvec[0], rotvec[1], rotvec[2]);
			}

			glScaled(scale[0], scale[1], scale[2]);
			draw();
			object_pr *temp = child;
			glPushMatrix();
			while(temp != NULL){
				//cout<<"displaying child"<<endl;
				temp->display();
				temp = temp->next;
			}
			glPopMatrix();
		glPopMatrix();
	}

	void rotate_vector(double front_rotated[3], double rotvec[3], double ang){
		rotateVec(front_rotated, base_fr, rotvec, ang);
	}
/*	  double b = rotvec[0];
	  double c = rotvec[1];
	  double d = rotvec[2];
	  double theta = (3.14/180)*ang;
	
	  double a = cos(theta/2);
	  //normalising
	  double sum = sqrt(b*b + c*c + d*d);
	  b /= sum; c/= sum; d /= sum;
	
	  double sint = sin(theta/2);
	  b *= sint;    c *= sint;    d *= sint;  
	  double trans[4][4];
	  //loadId(temp);
	  //mult(temp, mat);
	  //loadZero(trans);	
    
	  // cout<<a<<" "<<b<<" "<<c<<" "<<d<<endl;
	  trans[0][0] = a*a + b*b - c*c - d*d;  
	  trans[0][1] = 2*b*c - 2*a*d;  
	  trans[0][2] = 2*a*c + 2*b*d;
	  trans[0][3] = 0.0;
	
	  trans[1][0] = 2*a*d + 2*b*c;  
	  trans[1][1] = a*a - b*b + c*c - d*d;	
	  trans[1][2] = 2*c*d - 2*a*b;
	  trans[1][3] = 0.0;
	
	  trans[2][0] = 2*b*d - 2*a*c;  
	  trans[2][1] = 2*a*b + 2*c*d;  
	  trans[2][2] = a*a - b*b - c*c + d*d;
	  trans[2][3] = 0.0;
	
	  trans[3][0] = 0.0;
	  trans[3][1] = 0.0;
	  trans[3][2] = 0.0;
	  trans[3][3] = 1.0;
	
	  double x = base_fr[0], y = base_fr[1], z = base_fr[2], w = 1.0;
	  for(int i = 0 ; i< 3; i++)
	    front_rotated[i] = trans[i][0]*x + trans[i][1]*y + trans[i][2]*z + trans[i][3]*w;
	
	
	}
*/
	void crossprod(double vector1[3], double vector2[3], double normal[3]){

 		 normal[0] = vector1[1] *vector2[2] - vector1[2]*vector2[1];
 		 normal[1] = vector1[2] *vector2[0] - vector1[0]*vector2[2];
 		 normal[2] = vector1[0] *vector2[1] - vector1[1]*vector2[0];
	
 		 double length = sqrt(normal[0]*normal[0] + normal[1]*normal[1] + normal[2]*normal[2] );
 	 
 		 normal[0] /= -length;
 		 normal[1] /= -length;
 		 normal[2] /= -length;
	}

	double dotprodang(double vec1[3], double vec2[3] ){//angle returned in degrees
		double dotp = vec1[0]*vec2[0] + vec1[1]*vec2[1] + vec1[2]*vec2[2];
		double len1 = sqrt(vec1[0]*vec1[0] + vec1[1]*vec1[1] + vec1[2]*vec1[2]);
		double len2 = sqrt(vec2[0]*vec2[0] + vec2[1]*vec2[1] + vec2[2]*vec2[2]);
		double ang = acos(dotp/(len1*len2));
		ang *= (180/3.14);
		return ang;
	}
	object_pr *next;
	object_pr *child;
	object_pr(){
		//rad = 1.0;
		id = -1;
		isCylinder = false;
		next = NULL;
		child = NULL;
		base_up[0] = 0.0;
		base_up[1] = 1.0;
		base_up[2] = 0.0;
		base_fr[0] = 0.0;
		base_fr[1] = 0.0;
		base_fr[2] = -1.0;
		scale[0] = 1.0;
		scale[1] = 1.0;
		scale[2] = 1.0;
		frontvec[0] = -1.0;
		frontvec[1] = 0.0;
		frontvec[2] = 0.0;
		upvec[0] = 0.0;
		upvec[1] = 1.0;
		upvec[2] = 0.0;
	}

	virtual ~object_pr() {
			object_pr *temp = child, *nextc;
			while(temp != NULL){
				nextc = temp->next;
				delete temp;
				temp = nextc;
			}
	}
///////////////////////////change with time stuff///////////////////////////////////////////////

	virtual void update(int time){}; //do the updating of the object eg move/rotate with time
	void update_B(int time){
		
		glPushMatrix();
		update(time);
			object_pr *temp = this->child;
			glPushMatrix();
			while(temp != NULL){
				temp->update_B(time);
				temp = temp->next;
			}
			glPopMatrix();
		glPopMatrix();
	}

	static void testPoint(double x, double z, Quadtree *children[2][2], int pres[2][2]);
	virtual void sayPresent(Quadtree *children[2][2], int pres[2][2]){
	//given the children, this should return which children[x][z] this belongs to
		/*object_pr *temp = child;
		while(temp != NULL){
			temp->sayPresent(children, pres);
			temp = temp->next;
		}*/
	}

	virtual bool collideDetect(object_pr* other_obj, bool rec){
   //detect  if theres a collision b/w this object and other_obj
		if(rec == true) 
		{
			return other_obj->collideDetect(this, false);
		}
		return false;
	} 

   virtual void collide(object_pr *other_obj);
    //modifications required on this object due to collision. 

//////////////////////////////////////////change with time stuff///////////////////////////////////////////

} ;
extern object_pr theworld ;
//the world be an object, not a pointer. hence of no use(no overloading)
//we start drawing with theworld.next which be a pointer

class Cylinder_obj : public object_pr {
//bullet is not of this type
public:
	double rad;
	Cylinder_obj(){
		rad = 1.0;
		isCylinder = true;
	}
	void sayPresent(Quadtree *children[2][2], int pres[2][2]);
	bool collideDetect(object_pr* other_obj, bool rec);
	virtual void giveDim(double &x, double &z, double &rad2) = 0;
	//cylinder is of dim r = rad h = 2*rad located at x, z
	virtual void giveDim(double &x, double &y, double &z, double &rad2, double &H){
		giveDim(x, z, rad2);
		H = 2*rad2*scale[1]/scale[0];
		y = rad2;
	}
};

class OBJ_object : public Cylinder_obj {
public:
	void draw(){
		models[shape].drawOBJ();
	}
	OBJ_object() { id = OBJ_ID;}
	int shape;
	void giveDim(double &x, double &z, double &rad);
};

class Box_object :public Cylinder_obj {
public:
	void draw();
	Box_object() {id = BOX_ID;}
	void giveDim(double &x, double &z, double &rad2){

		x = pos[0];
		z = pos[2];
		rad2 = scale[1]/2;	
	}

	void giveDim(double &x, double &y, double &z, double &rad, double &h){
		x = pos[0];
		y = pos[1];
		z = pos[2];
		rad = scale[1]/2;
		h = scale[1];
	}

};


class Wall_object : public object_pr {
	double _dotprod(double vec1[3], double vec2[3])
	{
		double ans = 0.0;
		ans+= vec1[0]*vec2[0];
		ans+= vec1[1]*vec2[1];
		ans+= vec1[2]*vec2[2];
		return ans;
	}
public:
	void draw();
	int tex;
	Wall_object(): object_pr(){id = 2;}
	void sayPresent(Quadtree *children[2][2], int pres[2][2]);
	bool collideDetect(object_pr* other_obj, bool rec);
   //	void collide(object_pr *other_obj){};
	
};

class Floor_object : public Wall_object {
	double _dotprod(double vec1[3], double vec2[3])
	{
		double ans = 0.0;
		ans+= vec1[0]*vec2[0];
		ans+= vec1[1]*vec2[1];
		ans+= vec1[2]*vec2[2];
		return ans;
	}
public:
	int tex;
	Floor_object(){
		id = FLOOR_ID;
		frontvec[0] = 0.0;
		frontvec[1] = 1.0;
		frontvec[2] = 0.0;	
		upvec[0] = 0.0;
		upvec[1] = 0.0;
		upvec[2] = 1.0;	
	}
	void sayPresent(Quadtree *children[2][2], int pres[2][2]);
	bool collideDetect(object_pr* other_obj, bool rec);
   //	void collide(object_pr *other_obj){};
	
};

class PowerUp : public Cylinder_obj {
public:
	void draw();
	bool taken;
	int energise();
	PowerUp() {
		taken = false; 
		id = 11;
		rad = 0.5;
		frontvec[0] = -1.0;
		frontvec[1] = 0.0;
		frontvec[2] = 0.0;
		upvec[0] = 0.0;
		upvec[1] = 1.0;
		upvec[2] = 0.0;
	}
	void sayPresent(Quadtree *children[2][2], int pres[2][2]);
	int tex;
	void update(int time);
	void giveDim(double &x, double &z, double &rad2){
		x = pos[0];
		z = pos[2];
		rad2 = rad*scale[0];//assumed sphere, not oval
	}
	virtual void giveDim(double &x, double &y, double &z, double &rad2, double &H){
		giveDim(x, z, rad2);
		H = pos[1]+rad;
		y = pos[1];
	}
//	void sayPresent(Quadtree *children[2][2], int pres[2][2]);
//	bool collideDetect(object_pr* other_obj, bool rec);
};

class Camera : public object_pr{
	double cam_x, cam_y, cam_z ;
	double back_x, back_y, back_z;
	double x, y, z, xr, yr;
	double basepos[3];
	double yaxis[3];
	double xaxis[3];
	double back_pos[3], back_xrot, back_yrot;
public:

	double cam_yrot, cam_xrot;
	bool attached;
	bool fps;

	Camera(){
		fps = false;
		id = ID_CAMERA;
		camera = this;
		attached = true;
		x = 0; 
		y = 0;
 		z = -10;
		xr = 0;
		yr = 0;
		basepos[0] = 0.0;
		basepos[1] = 6.0;
		basepos[2] = 24.0;
		for(int i = 0 ; i < 3; i++){
			pos[i] = basepos[i];
			back_pos[i] = pos[i];
		}
		cam_xrot = 0; cam_yrot = 0;
		back_xrot = 0; back_yrot= 0;

		yaxis[0] = 0.0;
		yaxis[1] = 1.0;
		yaxis[2] = 0.0;
		xaxis[0] = 1.0;
		xaxis[1] = 0.0;
		xaxis[2] = 0.0;
	}
	void applyCamera(){	
		if(attached && !fps)
			gluLookAt(0.0, 5.0, 20.0, 0.0, 5.0, 0.0,0.0,1.0,0.0);
		else {
			gluLookAt(0.0, 0.0, 0.0, 0.0, 0.0, -1.0,0.0,1.0,0.0);
		}
		glRotatef(cam_xrot,1.0,0.0,0.0); 	
		glRotatef(cam_yrot,0.0,1.0,0.0); //rotate our camera on the y-axis (up and down)
		glTranslated(-cam_x,-cam_y,-cam_z); //translate the screen to the position of our camera
	}
	void detach(){
		if(attached == true){
			if(fps)
				mode();
			attached = false;
			xpos = pos[0];
			ypos = pos[1];
			zpos = pos[2];
		}
		else{
			attached = true;
			cam_x = back_x;
			cam_y = back_y;
			cam_z = back_z;
			pos[0] = back_pos[0];
			pos[1] = back_pos[1];
			pos[2] = back_pos[2];
			cam_xrot = back_xrot;
			cam_yrot = back_yrot;
			xrot = cam_xrot;
			yrot = cam_yrot;
		
		}
	}
	void mode(){
		if(attached)
			if(fps == false){
				fps = true;

			}
			else{
				fps = false;


			}

	}
	void update(int time){
		if(attached && !fps){
		//backups are for collision detection routine
			object_pr* Rob = (object_pr *)Robot;
			//x = xpos; y = ypos; z = zpos; xr = xrot; yr = yrot;
			back_x = cam_x;
			back_y = cam_y;
			back_z = cam_z;
			cam_x = Rob->pos[0];
			cam_y = Rob->pos[1];			
			cam_z = Rob->pos[2];

			back_xrot = cam_xrot;
			back_yrot = cam_yrot;
			cam_xrot = xrot;
			cam_yrot = yrot;

			back_pos[0] = pos[0];
			back_pos[1] = pos[1];
			back_pos[2] = pos[2];
			rotateVec(pos, basepos, xaxis, -cam_xrot);
			rotateVec( pos, pos, yaxis, -cam_yrot);
			//cout<<pos[0]<<" "<<pos[1]<<" "<<pos[2]<<endl;
			pos[0]+= cam_x;
			pos[1]+= cam_y;
			pos[2]+= cam_z;
		}
		else if (!attached){
			cam_x = xpos;
			cam_y = ypos;			
			cam_z = zpos;

			cam_xrot = xrot;
			cam_yrot = yrot;


		}
		else if(attached && fps){

			object_pr* Rob = (object_pr *)Robot;
			cam_x = Rob->pos[0];
			cam_y = Rob->pos[1]+4.5;			
			cam_z = Rob->pos[2];

			cam_xrot = xrot;
			cam_yrot = yrot;

		}
	}
	void sayPresent(Quadtree *children[2][2], int pres[2][2]){
	//	testPoint(pos[0], pos[2], children, pres);
	}
	void draw(){};
	bool collideDetect(object_pr* other_obj, bool rec);
   	void collide(object_pr *other_obj);
	
};

#endif

