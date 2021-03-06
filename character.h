#ifndef CHARACTER
#define CHARACTER
#include "robotfigure.h"
#include "glInclude.h"
//#include "arraylib.h"
//#include "collisionstuff.h"
//#include "objprimitive.cpp"
class character;
extern character *Robot;
extern double xpos, ypos, zpos;
extern string text,textdefault;
extern int text_disp_counter;
#define MAX_HEALTH_CHARACTER 30
double modd(double x);

class character: public Cylinder_obj
{
private:
	
	double dist(double a1, double b1, double a2, double b2)
	{
		double x = a1-a2;
		double y = b1 - b2;
		return (x*x + y*y);
	}

	void _copyArray(double source[3], double dest[3])
	{
		int p=0;
		for(p=0;p<3;p++)
		{
			dest[p] = source[p];
		}
	}
	void _normalize(double t[3])
	{
		double mod;
		mod = ((t[0]*t[0]) + (t[1]*t[1]) + (t[2]*t[2]));
		for(int w=0;w<3;w++)
		{
			t[w] = t[w]/mod;
		}
	}
	double _dotprod(double vec1[3], double vec2[3])
	{
		double ans = 0.0;
		ans+= vec1[0]*vec2[0];
		ans+= vec1[1]*vec2[1];
		ans+= vec1[2]*vec2[2];
		return ans;
	}
	void _scalarmul(double vec[3], double factor)
	{
		vec[0] = vec[0]*factor;
		vec[1] = vec[1]*factor;
		vec[2] = vec[2]*factor;
	}
	void _sub(double vec1[3], double vec2[3], double result[3])
	{
		result[0] = vec1[0]-vec2[0];
		result[1] = vec1[1]-vec2[1];
		result[2] = vec1[2]-vec2[2];
	}
	void _add(double vec1[3], double vec2[3], double result[3])
	{
		result[0] = vec1[0]+vec2[0];
		result[1] = vec1[1]+vec2[1];
		result[2] = vec1[2]+vec2[2];
	}
	


	/*
void testPoint(int x, int z, Quadtree *children[2][2], int pres[2][2]){

		int i = 2, j = 2;
		if(x<children[0][0]->maxX){
			if(x >= children[0][0]->minX)
				i = 0;
		}
		else if(x <= children[1][0]->maxX)
			i = 1;
		
		if(z<children[0][0]->maxZ){
			if(z >= children[0][0]->minZ)
				j = 0;
		}
		else if(z <= children[0][1]->maxZ)
			j = 1;
		
		if((i == 2) || ( j == 2)) return;
	
		pres[i][j] = 1;

}
*/
public:
	bool jumpPossible;
	Robot_Figure hero;
	double velocity[3];
	int detection,should_reset;
	int health;
	character()
	{
		hero.parent = (object_pr *) this;
		id = 99;
		rad = 2.2; //collision with wall
		detection=0;
		Robot = this;
		pos[0]=0.0;
		pos[1] = 2.2;
		pos[2] = -10.0;
		velocity[0] = 0.0;
		velocity[1] = 0.0;
		velocity[2] = 0.0;
		frontvec[0] = 0.0;
		frontvec[1] = 0.0;
		frontvec[2] = 1.0;
		upvec[0] = 0.0;
		upvec[1] = 1.0;
		upvec[2] = 0.0;
		should_reset=0;
		health = MAX_HEALTH_CHARACTER;
	}
	void draw(){
		glPushMatrix();
	//	glTranslated(xpos,ypos,zpos);	
	//	glRotatef(-yrot,0.0,1.0,0.0); 
		glRotated(180.0, upvec[0], upvec[1], upvec[2]);
	glDisable(GL_COLOR_MATERIAL);//color tracking
	GLfloat matNone[]        = {0.0, 0.0, 0.0, 1.0};
	   GLfloat matAmbientGray[] = {1.0, 1.0, 1.0, 1.0};	
	   GLfloat matDiffuseGray[] = {0.5, 0.5, 0.5, 1.0};
	   GLfloat matShineNo[]     = {0.0};
	   GLfloat matShineLittle[] = {50.0};
	   // draw robot
	   glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, matAmbientGray);
	   glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, matDiffuseGray);
	   glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, matNone);   
	   glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, matShineNo);
	   if(health>0)
		if(camera->fps == false)
		   hero.drawRobot();
		else hero.drawBullet();

		glPopMatrix();
	}
	void update(int time)
	{
		if(camera->attached == true)
			rotateVec(frontvec, base_fr, upvec, -camera->cam_yrot);
		//pos[0] = xpos;
		//pos[2] = zpos;
		/*if(detection==1)
		{
			//cout<<velocity[0]<<" "<<velocity[1]<<" "<<velocity[2]<<endl;
		}
		if(hero.is_colliding==1)
		{
			if(hero.colliding_direction!=hero.direction_of_motion)
			{
				xpos+= velocity[0]*time;
				ypos+= velocity[1]*time;
				zpos+= velocity[2]*time;
				hero.is_colliding=0;
			}
		}
		else
		{*/
			if(health>0)
			{
				pos[0]+= velocity[0]*time;
				pos[1]+= velocity[1]*time;
				pos[2]+= velocity[2]*time;
				should_reset+=1;
				if(should_reset>=40 && hero.more_bullets==1)
				{
					hero.resetAnimation();
					hero.more_bullets=0;
				}
				velocity[1] -= 0.001;
			}
		//}
		}

	bool checkProximity(object_pr *target, float min_distance)
	{
		double t[3],d;
		t[0] =  (pos[0] + xpos) - target->pos[0] ;
		t[1] =  (pos[1] + ypos) - target->pos[1];
		t[2] =  (pos[2] + zpos) - target->pos[2];

		d = ((t[0]*t[0]) + (t[1]*t[1]) + (t[2]*t[2]));
		if(d<min_distance)
		{
			return true;	
		}
		else
		{
			return false;
		}

	}

	double dotprod(double arr1[2], double arr2[2])
	{
		return ( arr1[0]*arr2[0] + arr1[1]*arr2[1]);
	}


	void collide(object_pr *other){
	double x, z, rand, y, h;
	giveDim(x, y, z, rand, h);
//	x = pos[0] + xpos;
//	z = pos[2] + zpos;
	
	double* vel = velocity;
	
	if(other->id == 2)//wall
	{
		Wall_object* obj = (Wall_object*)other;		
		double posvec[2];
		posvec[0] = x - obj->pos[0]; posvec[1] = z - obj->pos[2];

		double norm[2];
		norm[0] = obj->frontvec[0]; norm[1] = obj->frontvec[2];
		double dist = sqrt(norm[0]*norm[0]  + norm[1]*norm[1]);
		norm[0] /= dist; norm[1] /= dist; 
		//we now have front_base ang_btw_frnt_pos

		double dp1 = dotprod(norm, posvec); 
		if(dp1 == 0) {
			cout<<"wow"<<endl;
			return;
		}

		double vel_t[2];
		vel_t[0] = vel[0]; vel_t[1] = vel[2];
		double dp2 = dotprod(norm, vel_t);
		if(dp2 == 0) return;
		if(dp1*dp2 < 0 ){
			vel_t[0] -= dp2*norm[0];
			vel_t[1] -= dp2*norm[1];
			vel[0] = vel_t[0];
			vel[2] = vel_t[1];
		}

		
	}
	if(other->id == FLOOR_ID){
	//	cout<<"floor collision"<<endl;
		double dis = y - other->pos[1];
		if(dis*vel[1] < 0){
			vel[1] = 0;
			jumpPossible = true;
		}
	}
	else if(other->id == 100 || other->id==1 || other->id == 4)
	{
			double norm[2], rand, oy, oh;
			Cylinder_obj* tt = (Cylinder_obj*)other;
			tt->giveDim(norm[0], oy, norm[1], rand, oh);
		if( (h+oh)/2 - modd(y-oy) < 0.4){//not side by side collision
			if(vel[1]<0 && y > oy){
				vel[1]= 0.0;
				jumpPossible = true;
			}
			if(vel[1] > 0 && y < oy) vel[1] = -vel[1];
			return;
		}
			norm[0] -= x; 
			norm[1] -= z;
		double dist = sqrt(norm[0]*norm[0]  + norm[1]*norm[1]);
		norm[0] /= dist; norm[1] /= dist; 
		//we now have front_base ang_btw_frnt_pos

		double vel_t[2];
		vel_t[0] = vel[0]; vel_t[1] = vel[2];
		double dp1 = dotprod(norm, vel_t); 
		if(dp1 <= 0) return;

		vel[0] -= dp1*norm[0];
		vel[2] -= dp1*norm[1];
	}
	else if(other->id==101)
		health-=1;
	else if(other->id==POWER_ID){
		PowerUp* obj = (PowerUp*) other;
	 	health+=obj->energise();
		text = "Power up- Health + 5";
		text_disp_counter=0;
		//glutTimerFunc(10000,changeText,0);
	}
}

	
	void giveDim(double &x, double &z, double &rad2){
		 x = pos[0];
		 rad2 = rad; 
		 z = pos[2];
	}
	
	void giveDim(double &x, double &y, double &z, double &rad2, double &H){
			x = pos[0];
			y = pos[1];
			z = pos[2];
			rad2 = rad;
			H = 2*rad;
	}


};

#endif
