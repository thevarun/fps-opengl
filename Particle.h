#ifndef PARTICLE
#define PARTICLE

//#include <gl.h>
//#include <iostream>
//#include <GL/freeglut.h>
//#include <windows.h>
#include "glInclude.h"
#include <stdio.h>
#include <math.h>
#include "objprimitive.h"
//using namespace std;
class Quadtree;
extern double xpos,ypos,zpos;
extern double yrot;
extern object_pr *theworldsend;
//void testPoint(int x, int z, Quadtree *children[2][2], int pres[2][2]);


typedef struct particles
{
double Xpos;
double Ypos;
double Zpos;

double OrigXpos;
double OrigYpos;
double OrigZpos;
double Xmov;
double Zmov;
double Ymov;
double Red;
double Green;
double Blue;
double Direction;
double Acceleration;
double Deceleration;
double Scalez;
bool Visible;
double Range;
} PARTICLES;

//extern particles PARTICLES;

class bullet : public object_pr
{
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
	void _normalize_modify(double t[3])
	{
		
		double mod;
		mod = sqrt(((t[0]*t[0]) + (t[1]*t[1]) + (t[2]*t[2])));
		for(int w=0;w<3;w++)
		{
			t[w] = t[w]/mod;
		}

	}

public:
	PARTICLES *Particle;
	GLfloat Bullet_texture[10];
	object_pr *previous;
	object_pr *parent;
	//friend GLuint Bullet_LoadTextureRAW( const char * filename, int width, int height);
	//friend void Bullet_FreeTexture( GLuint texturez );
	int ParticleCount;
	double velocity[3];

	//function to load the RAW file

	/*GLuint Bullet_LoadTextureRAW( const char * filename, int width, int height )
	{
		GLuint texture;
		unsigned char * data;
		FILE * file;

		file = fopen( filename, "rb" );
		if ( file == NULL ) return 0;

		data = (unsigned char *)malloc( width * height * 3 );

		fread( data, width * height * 3, 1, file );
		fclose( file );

		glGenTextures(1, &texture ); 

		glBindTexture(GL_TEXTURE_2D, texture);

		glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

		glTexEnvi( GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE );

		glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR );

		glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );

		gluBuild2DMipmaps(GL_TEXTURE_2D, 3, width, height, GL_RGB, GL_UNSIGNED_BYTE, data);

		free( data );

		return texture;

	}

	void Bullet_FreeTexture( GLuint texture )
	{

		glDeleteTextures( 1, &texture );

	}


	void square (void) 
	{
		glBindTexture( GL_TEXTURE_2D, Bullet_texture[0] );
		glBegin (GL_QUADS);
		glTexCoord2d(0.0,0.0); 
		glVertex2d(-1.0,-1.0);
		glTexCoord2d(1.0,0.0); 
		glVertex2d(1.0,-1.0);
		glTexCoord2d(1.0,1.0); 
		glVertex2d(1.0,1.0);
		glTexCoord2d(0.0,1.0); 
		glVertex2d(-1.0,1.0);
		glEnd();
	}*/
	void glCreateParticles (double x, double y, double z, double range) 
	{
		int i;
		//ParticleCount = num;
		//Particle = new PARTICLES[ParticleCount];
		for (i = 0; i < ParticleCount; i++)
		{
			Particle[i].Xpos = x;
			Particle[i].Ypos = y;
			Particle[i].Zpos = z;
			Particle[i].OrigXpos = x;
			Particle[i].OrigYpos = y;
			Particle[i].OrigZpos = z;
			
			//Particle[i].Xmov = (((((((2 - 1 + 1) * rand()%11) + 1) - 1 + 1) * rand()%11) + 1) * 0.005) - (((((((2 - 1 + 1) * rand()%11) + 1) - 1 + 1) * rand()%11) + 1) * 0.005);
			//Particle[i].Zmov = (((((((2 - 1 + 1) * rand()%11) + 1) - 1 + 1) * rand()%11) + 1) * 0.005) - (((((((2 - 1 + 1) * rand()%11) + 1) - 1 + 1) * rand()%11) + 1) * 0.005);
			Particle[i].Xmov = velocity[0];
			Particle[i].Ymov = velocity[1];
			Particle[i].Zmov = velocity[2];
			Particle[i].Red = 1;
			Particle[i].Green = 1;
			Particle[i].Blue = 1;
			Particle[i].Scalez = 0.25;
			Particle[i].Direction = 0;
			//Particle[i].Acceleration = 0.01;//((((((8 - 5 + 2) * rand()%11) + 5) - 1 + 1) * rand()%11) + 1) * 0.02;
			//cout<<Particle[i].Acceleration<<endl;
			//Particle[i].Deceleration = 0.0025;
			Particle[i].Acceleration = 0.0;
			Particle[i].Deceleration = 0.0;
			Particle[i].Range = range;
			Particle[i].Visible = true;
		}
	}

	void glUpdateParticles (void) 
	{
		int i;
		for (i = 0; i < ParticleCount; i++)
		{

			glColor3f (Particle[i].Red, Particle[i].Green, Particle[i].Blue);

			//Particle[i].Ypos = Particle[i].Ypos + Particle[i].Acceleration - Particle[i].Deceleration;
			//Particle[i].Deceleration = Particle[i].Deceleration + 0.0025;

			//Particle[i].Xpos = Particle[i].Xpos + Particle[i].Xmov;
			Particle[i].Zpos = Particle[i].Zpos + (Particle[i].Zmov);
			Particle[i].Ypos = Particle[i].Ypos + (Particle[i].Ymov);
			Particle[i].Xpos = Particle[i].Xpos + (Particle[i].Xmov);
			
			pos[0] = Particle[i].Xpos;
			pos[1] = Particle[i].Ypos;
			pos[2] = Particle[i].Zpos;
			Particle[i].Direction = Particle[i].Direction + ((((((int)(0.5 - 0.1 + 0.1) * rand()%11) + 1) - 1 + 1) * rand()%11) + 1);
			double d1,d2,d3,dist;
			d1 = Particle[i].OrigXpos - Particle[i].Xpos;
			d2 = Particle[i].OrigYpos - Particle[i].Ypos;
			d3 = Particle[i].OrigZpos - Particle[i].Zpos;
			dist = ((d1*d1) + (d2*d2) + (d3*d3));
			//cout<< Particle[i].Zpos<<" "<<Particle[i].Range<<endl;
			if (dist > (Particle[i].Range * Particle[i].Range))
			{
				//if(Particle[i].Visible == false)
				//	destroy();
				//else
					Particle[i].Visible = false;
					destroy();
					
			}

		}
	}
	void update(int time)
	{
		glUpdateParticles();
	}
	void glDrawParticles (void) 
	{
		//glEnable( GL_TEXTURE_2D );
		//glEnable(GL_DEPTH_TEST);
		
		int i;
		//int checker=0;
		//glPushMatrix();
		//glTranslatef (0,0,-10);
		for (i = 0; i < ParticleCount; i++)
		{
			if(Particle[i].Visible == true)
			{
				glPushMatrix();
				//glEnable( GL_TEXTURE_2D );
				//glTranslatef (Particle[i].Xpos, Particle[i].Ypos, Particle[i].Zpos);
				glRotatef (Particle[i].Direction - 90, 0, 0, 1);

				glScalef (Particle[i].Scalez, Particle[i].Scalez, Particle[i].Scalez);

				//glDisable (GL_DEPTH_TEST);
				/*glEnable (GL_BLEND);

				glBlendFunc (GL_DST_COLOR, GL_ZERO);
				glBindTexture (GL_TEXTURE_2D, Bullet_texture[0]);

				glBegin (GL_QUADS);
				glTexCoord2d (0, 0);
				glVertex3f (-1, -1, 0);
				glTexCoord2d (1, 0);
				glVertex3f (1, -1, 0);
				glTexCoord2d (1, 1);
				glVertex3f (1, 1, 0);
				glTexCoord2d (0, 1);
				glVertex3f (-1, 1, 0);
				glEnd();

				glBlendFunc (GL_ONE, GL_ONE);
				glBindTexture (GL_TEXTURE_2D, Bullet_texture[1]);

				glBegin (GL_QUADS);
				glTexCoord2d (0, 0);
				glVertex3f (-1, -1, 0);
				glTexCoord2d (1, 0);
				glVertex3f (1, -1, 0);
				glTexCoord2d (1, 1);
				glVertex3f (1, 1, 0);
				glTexCoord2d (0, 1);
				glVertex3f (-1, 1, 0);
				glEnd();

				//glEnable(GL_DEPTH_TEST);
				glDisable(GL_BLEND);*/
				//glDisable(GL_TEXTURE_2D);
				GLfloat matNone[]        = {0.0, 0.0, 0.0, 1.0};
				GLfloat matAmbientGray[] = {1.0, 0.5, 0.0, 1.0};
				GLfloat matDiffuseGray[] = {0.5, 0.2, 0.0, 1.0};
				GLfloat matShineNo[]     = {10.0};
				GLfloat matShineLittle[] = {50.0};

				// draw robot
				glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, matAmbientGray);
				glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, matDiffuseGray);
				glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, matNone);   
				glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, matShineNo);
				glutSolidSphere(0.5,10,10);
				GLfloat matNone1[]        = {0.0, 0.0, 0.0, 1.0};
				GLfloat matAmbientGray1[] = {1.0, 1.0, 1.0, 1.0};
				GLfloat matDiffuseGray1[] = {0.5, 0.5, 0.5, 1.0};
				GLfloat matShineNo1[]     = {0.0};
				GLfloat matShineLittle1[] = {50.0};

				// draw robot
				glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, matAmbientGray1);
				glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, matDiffuseGray1);
				glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, matNone1);   
				glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, matShineNo1);
				glPopMatrix();
			}
			//else
			//	checker=1;
		}
		//if(checker==1)
		//	delete this;
		//glPopMatrix();
		//glDisable( GL_TEXTURE_2D );
		//glDisable(GL_DEPTH_TEST);
	}
	void draw()
	{
		//if(parent->id==99)
		//{	
		//	glPushMatrix();
		//	glRotatef(-xrot,0.0,1.0,0.0); //rotate our camera on the y-axis (up and down)
		//	glDrawParticles();
		//	glPopMatrix();
		//}
		//else
			glDrawParticles();
	}
	
	bullet ()
	{
		ParticleCount=0;
	}

	void init(int num, float acc, double range, object_pr *p)
	{
		glPushMatrix();
		theworldsend->next = (object_pr *)this;
		previous = theworldsend;
		theworldsend = (object_pr*)this;		
		id = 101;
		next = NULL;
		//glEnable( GL_TEXTURE_2D );
		//glEnable(GL_DEPTH_TEST);
		pos[0] = p->pos[0];
		pos[1] = p->pos[1];
		pos[2] = p->pos[2];
		frontvec[0] = p->frontvec[0];
		frontvec[1] = p->frontvec[1];
		frontvec[2] = p->frontvec[2];
		upvec[0] = p->upvec[0];
		upvec[1] = p->upvec[1];
		upvec[2] = p->upvec[2];
		_copyArray(frontvec,velocity);
		_normalize(velocity);
		_scalarmul(velocity, acc);		
		ParticleCount = num;
		Particle = new PARTICLES[ParticleCount];
		glCreateParticles(pos[0],pos[1],pos[2],range);
		//Bullet_texture[0] = Bullet_LoadTextureRAW( "particle_mask.raw",256,256); //load our texture
		//Bullet_texture[1] = Bullet_LoadTextureRAW( "particle.raw",256,256); //load our texture
		//glDisable(GL_TEXTURE_2D);
		glPopMatrix();
	}
	void init(int num, float acc, double range, object_pr *p, string s1, string s2)
	{
		
		theworldsend->next = (object_pr *)this;
		previous = theworldsend;
		theworldsend = (object_pr*)this;		
		theworldsend->next = NULL;
		pos[0] = p->pos[0];
		pos[1] = p->pos[1];
		pos[2] = p->pos[2];
		frontvec[0] = p->frontvec[0];
		frontvec[1] = p->frontvec[1];
		frontvec[2] = p->frontvec[2];
		upvec[0] = p->upvec[0];
		upvec[1] = p->upvec[1];
		upvec[2] = p->upvec[2];
		_copyArray(frontvec,velocity);
		_normalize(velocity);
		_scalarmul(velocity, acc);		
				
		ParticleCount = num;
		Particle = new PARTICLES[ParticleCount];
		glCreateParticles(pos[0],pos[1],pos[2],range);
		//glCreateParticles(x,y,z,range);
		//Bullet_texture[0] = Bullet_LoadTextureRAW( s1.c_str(),256,256); //load our texture
		//Bullet_texture[1] = Bullet_LoadTextureRAW( s2.c_str(),256,256); //load our texture
	}
	bullet (int num, float acc, double range, object_pr *p) 
	{
		//
		
		parent = p;
		//theworldsend->next = (object_pr *)this;
		//previous = theworldsend;
	    //theworldsend = (object_pr*)this;		
		id = 101;
		//theworldsend->next = NULL;
		/*if(p->id==99)
		{
			pos[0] = p->pos[0]+xpos;
			pos[1] = p->pos[1]+ypos;
			pos[2] = p->pos[2]+zpos + 1.0; // need to add offset to show bullet going out from robot arm
			frontvec[0] = -1;
			frontvec[1] = 0;
			frontvec[2] = 0;
			upvec[0] = 0;
			upvec[1] = 1;
			upvec[2] = 0;
			rotateVec(frontvec, frontvec, upvec, (-180-yrot)); 
			double prepfront[3];
			_copyArray(frontvec, prepfront);
			rotate_vector(prepfront, upvec, 90);
			_normalize_modify(prepfront);
			_add(pos,prepfront,pos);
		
		}
		else
		{*/
			pos[0] = p->pos[0];
			pos[1] = p->pos[1];
			pos[2] = p->pos[2] ;
			if(p->id==99)
			{
				frontvec[0] = (-1)*p->frontvec[0];
				frontvec[1] = (-1)*p->frontvec[1];
				frontvec[2] = (-1)*p->frontvec[2];
			}
			else
			{
				frontvec[0] = p->frontvec[0];
				frontvec[1] = p->frontvec[1];
				frontvec[2] = p->frontvec[2];
			}
			upvec[0] = p->upvec[0];
			upvec[1] = p->upvec[1];
			upvec[2] = p->upvec[2];
		
		//}
		_copyArray(frontvec,velocity);
		_normalize_modify(velocity);
		_scalarmul(velocity, acc);		
// to ensure that the bullet thrown by object doesnt collide with itself, start bullet a bit farther from the body
		_add(pos,velocity,pos);
		_add(pos,velocity,pos);
	//	_add(pos,velocity,pos);
	
		ParticleCount = num;
		Particle = new PARTICLES[ParticleCount];
		glCreateParticles(pos[0],pos[1],pos[2],40);
		//glCreateParticles(x,y,z,range);
		//Bullet_texture[0] = Bullet_LoadTextureRAW( "particle_mask.raw",256,256); //load our texture
		//Bullet_texture[1] = Bullet_LoadTextureRAW( "particle.raw",256,256); //load our texture
	}
	int live;
	bullet (int num, float acc, double range, object_pr *p, string s1, string s2) 
	{
		live = 1;
		theworldsend->next = (object_pr *)this;
		previous = theworldsend;
		//theworldsend = this;		
		theworldsend = (object_pr*)this;		
		theworldsend->next = NULL;
		pos[0] = p->pos[0];
		pos[1] = p->pos[1];
		pos[2] = p->pos[2];
		frontvec[0] = p->frontvec[0];
		frontvec[1] = p->frontvec[1];
		frontvec[2] = p->frontvec[2];
		upvec[0] = p->upvec[0];
		upvec[1] = p->upvec[1];
		upvec[2] = p->upvec[2];
		_copyArray(frontvec,velocity);
		_normalize(velocity);
		_scalarmul(velocity, acc);		
		
		//glEnable( GL_TEXTURE_2D );
		//glEnable(GL_DEPTH_TEST);
		ParticleCount = num;
		Particle = new PARTICLES[ParticleCount];
		glCreateParticles(pos[0],pos[1],pos[2],range);
		//glCreateParticles(x,y,z,range);
		//Bullet_texture[0] = Bullet_LoadTextureRAW( s1.c_str(),256,256); //load our texture
		//Bullet_texture[1] = Bullet_LoadTextureRAW( s2.c_str(),256,256); //load our texture
	}
	void destroy()
	{
		live = 0;
	//	delete this;
	}
	~bullet(){
		//cout<<"destroyed bullet"<<endl;
		if((object_pr*)this==theworldsend){
			theworldsend = previous;
			previous->next = NULL;
		}
		else{
			previous->next = this->next;
			bullet* temp = (bullet*)(this->next);
			temp->previous = previous;
		}
	}
	void collide(object_pr *other_obj){
		destroy();
		//cout<<"collided bullet"<<endl;
	}
	void sayPresent(Quadtree *children[2][2], int pres[2][2]){
		testPoint(pos[0], pos[2], children, pres);
		//cout<<"present bullet"<<endl;
	}

	
	bool collideDetect(object_pr* other, bool rec){
		switch(other->id){
		case CHAR_ID:
		case ENEMY_ID:
			if(parent->id == other->id)
				return false;
		case OBJ_ID:
		case BOX_ID:
		{
			double x2, z2, rad2;
			Cylinder_obj* tt = (Cylinder_obj*)other;
			tt->giveDim(x2, z2, rad2);
			double d;
			d = (x2 - pos[0])*(x2 - pos[0]) + (z2 - pos[2]) * (z2 - pos[2]);
			double min_dist = rad2*rad2;
			if(d<min_dist)
				return true;	
			else
				return false;
		}
		break;
		default:
			if(rec == true)
				return other->collideDetect(this, false);
			else return false;
			
		}
	}

};

#endif
