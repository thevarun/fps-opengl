#ifndef ENEMY
#define ENEMY

#include <iostream>
#include "glInclude.h"
#include <math.h>
//#include "bezier.cpp"
//#include "arraylib.h"
//#include "robotfigure.h"
#include "character.h"
//#include "room2.cpp"
using namespace std;
#define TIME_BETWEEN_CHECKS 25
extern character *Robot;
extern double xpos, ypos, zpos;
 

class Enemy: public Cylinder_obj
{
private:
	bool copied,first;
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
	

	void Setmaterial()
	{
		GLfloat matNone[]        = {0.0, 0.0, 0.0, 1.0};
		GLfloat matAmbientGray[] = {1.0, 0.0, 1.0, 1.0};
		GLfloat matDiffuseGray[] = {0.2, 0.3, 0.6, 1.0};
		GLfloat matShineNo[]     = {0.0};
		GLfloat matShineLittle[] = {50.0};

		// draw robot
		glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, matAmbientGray);
		glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, matDiffuseGray);
		glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, matNone);   
		glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, matShineNo);

	}
	void resetMaterial()
	{
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

	}
	void hitMaterial(float r, float b, float g)
	{
				GLfloat matNone[]        = {0.0, 0.0, 0.0, 1.0};
				GLfloat matAmbientGray[] = {1.0, 0.5, 0.0, 1.0};
				GLfloat matDiffuseGray[] = {r, b, g, 1.0};
				GLfloat matShineNo[]     = {10.0};
				GLfloat matShineLittle[] = {50.0};

				// draw robot
				glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, matAmbientGray);
				glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, matDiffuseGray);
				glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, matNone);   
				glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, matShineNo);

	}
	void decideColor()
	{
		float r,g,b;
		if(health<MAX_HEALTH-5)
		{
			r=0.8;
			b = 0.2;
			g = 0.5;
		}
		if(health<MAX_HEALTH-10)
		{
			r=0.6;
			b = 0.2;
			g = 0.3;
		}
		if(health<MAX_HEALTH-15)
		{
			r=0.4;
			b = 0.2;
			g = 0.2;
		}
		if(health<MAX_HEALTH-20)
		{
			r=0.3;
			b = 0.2;
			g = 0.1;
		}
		else if(health<=MAX_HEALTH && health>=MAX_HEALTH-5)
		{
			//Setmaterial();
			//return;
			r = 0.0;
			b = 0.2;
			g = 1.0;
		}
		hitMaterial(r,b,g);
	
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

}*/
	double dotprod(double arr1[2], double arr2[2])
	{
		return ( arr1[0]*arr2[0] + arr1[1]*arr2[1]);
	}

public:
	//int shootAt[3];
	Robot_Figure enemy;
	character *target;
	float min_distance,min_distance_collission;
	double velocity[3],origvel[3];
	int health;
	int MAX_HEALTH,is_reset,should_animate,should_reset;
	double origfrontvec[3], origupvec[3];
	
	Enemy()
	{
	  id = 100;
	  //p.render();
		first = true;
		is_reset = 1;
		MAX_HEALTH = 20;
		should_animate=1;
		should_reset=0;
		//hero = r;
		rad = 2.2;
        enemy.direction_of_motion = 1;
		enemy.parent = (object_pr *) this;
		_copyArray(frontvec,velocity);
		_normalize(velocity);
		_scalarmul(velocity,0.25);
		//velocity[0] = 0.0;
		//velocity[1] = 0.0;
		//velocity[2] = -2.0/TIME_BETWEEN_CHECKS;
		min_distance = 350.0; // this is the min distance within which if the character is there, enemy will shoot
		min_distance_collission = 10; // this is distance used to detect collision between robot and enemy
		target = Robot;
		health = MAX_HEALTH;
		//p.init();
	}/*
	Enemy(int direction)
	{
		//hero = r;
	  id = 100;
		enemy.direction_of_motion = direction;
		velocity[0] = 0.0;
		velocity[1] = 0.0;
		velocity[2] = 0.0;
		min_distance = 8.0;
	}*/
	void setvelocity(int v[3])
	{
		velocity[0] = v[0];
		velocity[1] = v[1];
		velocity[2] = v[2];
		origvel[0] = v[0];
		origvel[1] = v[1];
		origvel[2] = v[2];
	}
	void check()
	{
		cout<<target->pos[0];
		//cout<<target->current_x<<endl;
	}/*
	void drawEnemy(int x, int y, int z)
	{
		enemy.drawRobot();
		pos[0] = x;
		pos[1] = y;
		pos[2] = z;
		}*/
	void movEnemy(int direction=1)
	{
		
		enemy.direction_of_motion = direction;
		//should_animate++;
		//if(should_animate%2==0)
		//{
		if(should_animate==1)
		{
			pos[0]+= velocity[0];
			pos[1]+= velocity[1];
			pos[2]+= velocity[2];
			enemy.animate();
		}
		//	should_animate=0;
		//}
		//glutPostRedisplay();
		
	}
	void update(int time)
	{
		if(health>0)
		{
			bool tem;
			tem = checkProximitywithTarget(min_distance);
			if(tem==true)
				shootBullets();
			else
				stopBullets();
			should_reset+=1;
			if(should_reset>=40 && enemy.more_bullets==1 && enemy.shoot==false)
			{
					if(copied==true)
					{
						_copyArray(origfrontvec,frontvec);
						_copyArray(origupvec,upvec);
						_copyArray(origvel,velocity);
						copied = false;
					}
					enemy.resetAnimation();
					enemy.more_bullets=0;
					should_animate=1;
			}
			if(enemy.more_bullets==0)
			{
				movEnemy();
				//Enemyanimate();
				//glutPostRedisplay();
				//Setmaterial();
				decideColor();
				enemy.drawRobot();
				resetMaterial();
			}
			//else
			//	enemy.resetAnimation3();
		}
	}

	void giveDim(double &x, double &y, double &z, double &rad2, double &H){
			x = pos[0];
			y = pos[1];
			z = pos[2];
			rad2 = rad;
			H = 2*rad;
	}

	bool collideDetect(object_pr* other, bool rec)
	{
		if(health<=0)
		{
			//cout<<"RETURN FALSE"<<endl;
			return false;
		}
		else
		{
			//cout<<"TRUE";
			return Cylinder_obj::collideDetect(other,rec);
		}
	}
	void sayPresent(Quadtree *children[2][2], int pres[2][2]){
		if(health>=0)
			Cylinder_obj::sayPresent(children,pres);
	}

	void collide(object_pr *other)
	{
		double x, z, rad;//rad
		giveDim(x, z, rad);
		double* vel = velocity;
	
		/*if(p->id!=99)
		{
			double v[3],v1along[3],vperp[3],ans = 0.0;
			v[0] = p->pos[0] - pos[0];
			v[1] = p->pos[1] - pos[1];
			v[2] = p->pos[2] - pos[2];
			_normalize(v);
			ans = _dotprod(v,velocity);
			_scalarmul(v, ans);
			_sub(velocity,v,vperp);
			_scalarmul(v,(-1.0));
			_add(v,vperp,velocity);
		}*/
		/*else
		{
			velocity[0] = 0.0;
			velocity[1] = 0.0;
			velocity[2] = 0.0;
			collided_with_hero=1;
		}*/
		if(other->id == 2)//wall
		{cout<<"enemy with wall"<<endl;
			Wall_object* obj = (Wall_object*)other;		
			double posvec[2];
			posvec[0] = x - obj->pos[0]; posvec[1] = z - obj->pos[2];

			double norm[2];
			norm[0] = obj->frontvec[0]; norm[1] = obj->frontvec[2];
			double dist = sqrt(norm[0]*norm[0]  + norm[1]*norm[1]);
			norm[0] /= dist; norm[1] /= dist; 
			//we now have front_base ang_btw_frnt_pos

			double dp1 = dotprod(norm, posvec); 
			if(dp1 == 0) return;

			double vel_t[2];
			vel_t[0] = vel[0]; vel_t[1] = vel[2];
			double dp2 = dotprod(norm, vel_t);
			if(dp2 == 0) return;
			if(dp1*dp2 < 0 )
			{
				vel_t[0] -= 2*dp2*norm[0];
				vel_t[1] -= 2*dp2*norm[1];
				vel[0] = vel_t[0];
				vel[2] = vel_t[1];
				_scalarmul(frontvec,-1.0);
			}
			//rotate_vector(frontvec, upvec, 180); 
			//rotate_vector(frontvec, upvec, 90);
			
			_copyArray(velocity,origvel);
			_copyArray(frontvec,origfrontvec);

		}
		else if(other->id == 100 || other->id==1)
		{
			double norm[2], rand;
			Cylinder_obj* tt = (Cylinder_obj*)other;
			tt->giveDim(norm[0], norm[1], rand);
			norm[0] -= x; 
			norm[1] -= z;
			double dist = sqrt(norm[0]*norm[0]  + norm[1]*norm[1]);
			norm[0] /= dist; norm[1] /= dist; 
			//we now have front_base ang_btw_frnt_pos

			double vel_t[2];
			vel_t[0] = vel[0]; vel_t[1] = vel[2];
			double dp1 = dotprod(norm, vel_t); 
			if(dp1 <= 0) return;

			vel[0] -= 2.0*dp1*norm[0];
			vel[2] -= 2.0*dp1*norm[1];
			_copyArray(velocity,origvel);
			_copyArray(frontvec,origfrontvec);
		}
		else if(other->id == 101)
		{
			if(health == 0)
				quadtree->remove(this);
			health-=1;
		}
		
	}
  void draw(){
	  if(health>0)
	  {
		//Setmaterial();
		  glEnable(GL_LIGHTING);
		  decideColor();
		//if(enemy.shoot==false && is_reset==1)
		//{
		//		is_reset = 0;
		//	  enemy.resetAnimation();
		//}
		// if(enemy.shoot==true)
		//{
		//	enemy.resetAnimation3();
			//is_reset = 1;
		//}
	  		  
		enemy.drawRobot();
		resetMaterial();
		glDisable(GL_LIGHTING);
	}
	  else
	  {
			//setMaterial();		 
		  glEnable(GL_LIGHTING);
		  decideColor();
		  //glTranslatef(0.0,-2.2f,0.0);
		  //glutSolidSphere(1.0f,10,10);
		  enemy.resetAnimation();
		  enemy.drawDeadRobot();
		  //p.render();
		  resetMaterial();
		  glDisable(GL_LIGHTING);
	  }
  }
  void Enemyanimate()
	{
		enemy.animate();
	}
  void shootBullets()
  {
	  double t[3],d;
	double x,y,z,rad,h,cx,cy,cz,crad,ch;
	giveDim(x,y,z,rad,h);
	target->giveDim(cx,cy,cz,crad,ch);
		t[0] =  x - cx ;
		t[1] =  y - cy;
		t[2] =  z - cz;

	  if(first==true)
	  {
		  _copyArray(frontvec,origfrontvec);
		  _copyArray(upvec,origupvec);
		  _copyArray(velocity,origvel);
		  //_copyArray(upvec,origupvec);
		  first = false;
       }
	  //if(copied==false)
	  //{
		copied = true;
		_normalize(t);
		_copyArray(t,frontvec);
		_scalarmul(velocity,0.0);
	  //}
		enemy.shoot = true;
		//enemy.resetAnimation4();
		enemy.resetAnimation1();
		enemy.more_bullets=1;
		should_reset = 0;
		should_animate=0;
  }
  void stopBullets()
  {
	  enemy.shoot = false;	
	  /*if(enemy.shoot==true)
			{
				int max_limit,i;
				if(enemy.number_of_rounds>0)
					max_limit = enemy.Max_bullets;
				else
					max_limit = enemy.number_of_bullets;
				for(i=0;i<max_limit;i++)
				{
					if(enemy.B[i].Particle[0].Visible==true)
						break;
				}
				if(i==max_limit)
				{
					enemy.shoot = false;
					enemy.number_of_bullets=0;
					enemy.resetAnimation4();
					//glutPostRedisplay();
				}
			}*/
			
			//if(enemy.shoot==false)
			//{
				first = true;
			//}
			should_reset++;
			//enemy.more_bullets=0;
  }
	bool checkProximitywithTarget(float min_distance)
	{
		double t[3],d,x,y,z,cx,cy,cz,rad1,h,rad2,ch;
		giveDim(x,y,z,rad1,h);
		target->giveDim(cx,cy,cz,rad2,ch);
		t[0] =  x-cx ;
		t[1] =  y - cy;
		t[2] =  z - cz;

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
	bool checkProximitywithObject(object_pr *target, float min_distance)
	{
		double t[3],d;
		t[0] =  (pos[0]) - target->pos[0] ;
		t[1] =  (pos[1]) - target->pos[1];
		t[2] =  (pos[2]) - target->pos[2];

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
	void giveDim(double &x, double &z, double &rad2){

		x = pos[0]; z = pos[2]; rad2 = rad;

	}


};


#endif

