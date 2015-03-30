//#include "objprimitive.h"
#include "collisionstuff.h"
//class Quadtree;
//Quadtree *quadtree;
#include "objprimitive.h"

/////////////////////////////////////Data allocation///////////////////////////////////////
class Quadtree;
extern Quadtree *quadtree;
object_pr theworld ;
//object_pr movables;
class character;
character *Robot = NULL;
object_pr* theworldsend;
Camera *camera = NULL;

//////////////////////helper functions/////////////////////////////////////////////////////
double distt (double a1, double b1, double a2, double b2){
	double x = a1-a2;
	double y = b1 - b2;
	return (x*x + y*y);
}

double dotprod(double arr1[2], double arr2[2])
{
	return ( arr1[0]*arr2[0] + arr1[1]*arr2[1]);
}

double modd(double x){
	if(x < 0)
		return (-x);
	return x;
}

void rotateVec(double front_rotated[3], double base_fr[3], double rotvec[3], double ang){//and in degrees
  double b = rotvec[0];
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
///////////////////////////////object_pr//////////////////////////////////////////////////

void object_pr::collide(object_pr *other_obj){
		//just so header does not compile the class
}


void object_pr::testPoint(double x, double z, Quadtree *children[2][2], int pres[2][2]){

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

//////////////////////////////Wall_object////////////////////////////////////////////////////

void Wall_object::draw(){//a square 1*1 centered at origin facing negative z
  GLfloat white[] = { 1.0, 1.0, 1.0, 1.0 };
   glEnable(GL_TEXTURE_2D);
   glBindTexture(GL_TEXTURE_2D, textures[tex]);
   glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, white);
   glBegin(GL_QUADS);
   {
     glNormal3f(0.0, 0.0, -1.0);
     glTexCoord2f(0.0, 0.0); glVertex3f(-0.5, -0.5, -0.5);
     glTexCoord2f(0.0, scale[1]/10); glVertex3f(-0.5, 0.5, -0.5);
     glTexCoord2f(scale[0]/10, scale[1]/10); glVertex3f(0.5, 0.5, -0.5);
     glTexCoord2f(scale[0]/10, 0.0); glVertex3f(0.5, -0.5, -0.5);
   }
   glEnd();

   glBegin(GL_QUADS);
   {
     glNormal3f(0.0, 0.0, 1.0);
     glTexCoord2f(0.0, 0.0); glVertex3f(-0.5, -0.5, 0.5);
     glTexCoord2f(0.0, scale[1]/10); glVertex3f(-0.5, 0.5, 0.5);
     glTexCoord2f(scale[0]/10, scale[1]/10); glVertex3f(0.5, 0.5, 0.5);
     glTexCoord2f(scale[0]/10, 0.0); glVertex3f(0.5, -0.5, 0.5);
   }
   glEnd();

   glDisable(GL_LIGHTING);
  glDisable(GL_TEXTURE_2D);

   glBegin(GL_QUADS);
   {//left
     glVertex3f(-0.5, -0.5, 0.5);
     glVertex3f(-0.5, 0.5, 0.5);
     glVertex3f(-0.5, 0.5, -0.5);
     glVertex3f(-0.5, -0.5, -0.5);
   }
   glEnd();
  glBegin(GL_QUADS);
   {//right
     glVertex3f(0.5, -0.5, 0.5);
     glVertex3f(0.5, 0.5, 0.5);
     glVertex3f(0.5, 0.5, -0.5);
     glVertex3f(0.5, -0.5, -0.5);
   }
   glEnd();


  glBegin(GL_QUADS);
   {//up
     glVertex3f(0.5, 0.5, -0.5);
     glVertex3f(-0.5, 0.5, -0.5);
     glVertex3f(-0.5, 0.5, 0.5);
     glVertex3f(0.5, 0.5, 0.5);
   }
   glEnd();

  glBegin(GL_QUADS);
   {//down
     glVertex3f(0.5, -0.5, -0.5);
     glVertex3f(-0.5, -0.5, -0.5);
     glVertex3f(-0.5, -0.5, 0.5);
     glVertex3f(0.5, -0.5, 0.5);
       }
   glEnd();
  glEnable(GL_LIGHTING);


    }	


void Wall_object::sayPresent(Quadtree *children[2][2], int pres[2][2]){
	if(dotprodang(upvec, base_up) > 5)
		return;//to avoid doing this for ground
	double p1[] = {0.5, 0.0, 0.0};
	double p2[] = {-0.5, 0.0, 0.0};
	p1[0] *= scale[0]; p2[0] *= scale[0];

			double ang1 = dotprodang(frontvec, base_fr);
	double rotvec2[3];
	double test[3], test2[3], pa[3], pb[3];
	test[0] = base_fr[0];test[1] = base_fr[1];test[2] = base_fr[2];
			if(ang1 >= 5 ){
			//	cout<<"2nd"<<ang1<<endl;
				if(ang1 < 175){
					crossprod(frontvec, base_fr, rotvec2);
					rotateVec(test2, test, rotvec2, ang1);
					rotateVec(pa, p1, rotvec2, ang1);
					rotateVec(pb, p2, rotvec2, ang1);
				}
				else {
					rotateVec(test2, test, upvec, ang1);
					rotateVec(pa, p1, upvec, ang1);
					rotateVec(pb, p2, upvec, ang1);		
				}
			}
			else{
				pa[0] = p1[0];pa[1] = p1[1];pa[2] = p1[2];
				pb[0] = p2[0];pb[1] = p2[1];pb[2] = p2[2];
			}

	pa[0] += pos[0]; pb[0] += pos[0];
	pa[2] += pos[2]; pb[2] += pos[2];

	double xstep = pa[0] - pb[0];
	double zstep = pa[2] - pb[2];
	double x = pb[0];
	double z = pb[2];
	double lstep = 0;
	if(fabs(xstep) < fabs(zstep)) lstep = fabs(zstep);
	else lstep = fabs(xstep);

	for(int l = 0 ;l <= lstep*2 ;l++){
		x += l*xstep/(2*lstep);
		z += l*zstep/(2*lstep);
		testPoint(x, z, children, pres);

	}
}

bool Wall_object::collideDetect(object_pr* other, bool rec){

	switch(other->id){
	case 101:
	{
		double norm[2], pow[2];
		norm[0] = frontvec[0]; norm[1] = frontvec[2];
		double dist = sqrt(norm[0]*norm[0] +norm[1]*norm[1] );
		norm[0] /= dist; norm[1] /= dist;
		pow[0] = pos[0] - other->pos[0]; pow[1] = pos[2] - other->pos[2];

		double dot = dotprod(pow, norm);
	//	cout<<"bullet "<<modd(dot)<<" "<<rad<<endl;
		if(modd(dot) < 2 ) {
			if(modd(other->pos[1] - pos[1])	< scale[1]/2){//height criterion	
				double parr[2];
				parr[0] = -norm[1];
				parr[1] = norm[0];
				dot = dotprod(pow, norm);
				if(modd(dot) < scale[0]/2)
					return true;
			}
		}
	}
	return false;
	default:
		if(rec == true) 
		{
			return other->collideDetect(this, false);
		}
		else return false;
	}
}
///////////////////////////////////////floor////////////////////////////////////////////////////

void Floor_object::sayPresent(Quadtree *children[2][2], int pres[2][2]){
//floor is always up and aligned with axes
	double stepZ = 1.0, stepX = 1.0;
	double x , z;
	for(x = pos[0] - scale[0]/2; x < (pos[0]+scale[0]/2); x += stepX){
		for(z = pos[2] - scale[1]/2; z < (pos[2] + scale[1]/2) ;  z += stepZ){
			//cout<<x<<" "<<z<<endl;
			testPoint(x, z, children, pres);
		}
	}
}/*
	if(dotprodang(upvec, base_up) > 5)
		return;//to avoid doing this for ground
	double p1[] = {0.5, 0.0, 0.0};
	double p2[] = {-0.5, 0.0, 0.0};
	p1[0] *= scale[0]; p2[0] *= scale[0];

			double ang1 = dotprodang(frontvec, base_fr);
	double rotvec2[3];
	double test[3], test2[3], pa[3], pb[3];
	test[0] = base_fr[0];test[1] = base_fr[1];test[2] = base_fr[2];
			if(ang1 >= 5 ){
			//	cout<<"2nd"<<ang1<<endl;
				if(ang1 < 175){
					crossprod(frontvec, base_fr, rotvec2);
					rotateVec(test2, test, rotvec2, ang1);
					rotateVec(pa, p1, rotvec2, ang1);
					rotateVec(pb, p2, rotvec2, ang1);
				}
				else {
					rotateVec(test2, test, upvec, ang1);
					rotateVec(pa, p1, upvec, ang1);
					rotateVec(pb, p2, upvec, ang1);		
				}
			}
			else{
				pa[0] = p1[0];pa[1] = p1[1];pa[2] = p1[2];
				pb[0] = p2[0];pb[1] = p2[1];pb[2] = p2[2];
			}

	pa[0] += pos[0]; pb[0] += pos[0];
	pa[2] += pos[2]; pb[2] += pos[2];

	double xstep = pa[0] - pb[0];
	double zstep = pa[2] - pb[2];
	double x = pb[0];
	double z = pb[2];
	double lstep = 0;
	if(fabs(xstep) < fabs(zstep)) lstep = fabs(zstep);
	else lstep = fabs(xstep);

	for(int l = 0 ;l <= lstep*2 ;l++){
		x += l*xstep/(2*lstep);
		z += l*zstep/(2*lstep);
		testPoint(x, z, children, pres);

	}
}*/


bool Floor_object::collideDetect(object_pr* other, bool rec){
	double height = 0.5;
	switch(other->id){
	case 101:
	{
			if(modd(pos[1]-other->pos[1]-1.0) <= (height/2)){
			
				double norm[2], pow[2];
				norm[0] = upvec[0]; norm[1] = upvec[2];
				double dist = sqrt(norm[0]*norm[0] +norm[1]*norm[1] );
				norm[0] /= dist; norm[1] /= dist;
				pow[0] = pos[0] - other->pos[0]; pow[1] = pos[2] - other->pos[2];	
				double dot = dotprod(pow, norm);
				if(modd(dot) < scale[1]/2){	
					double parr[2];
					parr[0] = -norm[1];
					parr[1] = norm[0];
					dot = dotprod(pow, parr);
					if(modd(dot) < scale[0]/2)
						return true;
				}
			}	
	/*	double norm[2], pow[2];
		norm[0] = frontvec[0]; norm[1] = frontvec[2];
		double dist = sqrt(norm[0]*norm[0] +norm[1]*norm[1] );
		norm[0] /= dist; norm[1] /= dist;
		pow[0] = pos[0] - other->pos[0]; pow[1] = pos[2] - other->pos[2];

		double dot = dotprod(pow, norm);
	//	cout<<"bullet "<<modd(dot)<<" "<<rad<<endl;
		if(modd(dot) < 0.5 ) return true;*/
		return false;
	}
	break;
	default:
		if(rec == true) 
		{
			return other->collideDetect(this, false);
		}
		else return false;
	}
}



///////////////////////////////////cylinder_obj/////////////////////////////////////////////////

void Cylinder_obj::sayPresent(Quadtree *children[2][2], int pres[2][2]){

	
	double x, z, scale;
	giveDim(x, z, scale);
	double rad2 = scale*scale;;

//need to check 9 points 
	//centre

	if(distt(children[0][0]->maxX, children[0][0]->maxZ, x, z) < rad){
		pres[0][0] = 1;
		pres[1][0] = 1;
		pres[0][1] = 1;
		pres[1][1] = 1;
		return;
	}	
	//now going left right, top down
	if(distt(children[0][0]->minX, children[0][0]->minZ, x, z) < rad2){
		pres[0][0] = 1;
	}	
	if(distt(children[0][0]->maxX, children[0][0]->minZ, x, z) < rad2){
		pres[0][0] = 1;
		pres[1][0] = 1;
	}	
	if(distt(children[1][0]->maxX, children[1][0]->minZ, x, z) < rad2){
		pres[1][0] = 1;
	}	
	if(distt(children[0][0]->minX, children[0][0]->maxZ, x, z) < rad2){
		pres[0][0] = 1;
		pres[0][1] = 1;
	}	
	if(distt(children[1][0]->maxX, children[1][0]->maxZ, x, z) < rad2){
		pres[1][0] = 1;
		pres[1][1] = 1;
	}	
	if(distt(children[0][1]->minX, children[0][1]->maxZ, x, z) < rad2){
		pres[0][1] = 1;
	}	
	if(distt(children[0][1]->maxX, children[0][1]->maxZ, x, z) < rad2){
		pres[0][1] = 1;
		pres[1][1] = 1;
	}	
	if(distt(children[1][1]->maxX, children[1][1]->maxZ, x, z) < rad2){
		pres[1][1] = 1;
	}	

	testPoint(x, z, children, pres);
	testPoint(x+scale, z, children, pres);
	testPoint(x-scale, z, children, pres);
	testPoint(x, z + scale, children, pres);
	testPoint(x, z - scale, children, pres);
	
}

bool Cylinder_obj::collideDetect(object_pr* other, bool rec){
	double x, z, radius, height, y;
	giveDim(x, y, z, radius, height);
	
	if(other == this)
		return false;

	switch(other->id)
		{
		case WALL_ID: //wall
		{
			Wall_object* obj = (Wall_object*)other;
			double norm[2], pow[2];
			norm[0] = obj->frontvec[0]; norm[1] = obj->frontvec[2];
			double dist = sqrt(norm[0]*norm[0] +norm[1]*norm[1] );
			norm[0] /= dist; norm[1] /= dist;
/*			pow[0] = obj->pos[0]; pow[1] = obj->pos[2];

			double x1, x2, z1, z2;
			x1 = x + radius*norm[0] - pow[0]; z1 = z + radius*norm[1] - pow[1];
			x2 = x - radius*norm[0] - pow[0]; z2 = z - radius*norm[1] - pow[1];

			double dot1 = x1*norm[0] + z1*norm[1];
			double dot2 = x2*norm[0] + z2*norm[1];

			if(dot1*dot2 > 0)	return false;//both on same side
			else return true;*/

			pow[0] = pos[0] - other->pos[0]; pow[1] = pos[2] - other->pos[2];

			double dot = dotprod(pow, norm);
			if(modd(dot) < radius ) 
				if(modd(other->pos[1] - y)< (other->scale[1]+height)/2){//height criterion	
					double parr[2];
					parr[0] = -norm[1];
					parr[1] = norm[0];
					dot = dotprod(pow, parr);
					if(modd(dot) < (other->scale[0]/2))
						return true;
				}
			return false;		
		}
		break;
		case FLOOR_ID:	
		{
		//	cout<<y<<" "<<other->pos[1]<<" "<<height<<endl;
			if(modd(y-other->pos[1]-1.0) <= (height/2)){
			
				double norm[2], pow[2];
				norm[0] = other->upvec[0]; norm[1] = other->upvec[2];
				double dist = sqrt(norm[0]*norm[0] +norm[1]*norm[1] );
				norm[0] /= dist; norm[1] /= dist;
				pow[0] = pos[0] - other->pos[0]; pow[1] = pos[2] - other->pos[2];	
				double dot = dotprod(pow, norm);
				if(modd(dot) < (other->scale[1]/2)){	
					double parr[2];
					parr[0] = -norm[1];
					parr[1] = norm[0];
					dot = dotprod(pow, parr);
					if(modd(dot) < (other->scale[0]/2))
						return true;
				}
			}	
			return false;
		}
		break;	
		case CHAR_ID:
		case ENEMY_ID:
		case OBJ_ID:
		case POWER_ID:
			{	
				double x2, y2, z2, r2, h2;
				Cylinder_obj* tt = (Cylinder_obj*)other;
				tt->giveDim(x2, y2, z2, r2, h2);
				double d;
				d = (x2 - x)*(x2 - x) + (z2 - z) * (z2 - z);
				double min_dist = (radius+r2)*(radius+r2);
				if(d<min_dist){
					if(modd(y2-y) < (height+h2)/2)				
						return true;	
				}
				return false;
			}
		break;/*
		case 101:
			{
				bullet* b;
				b = (bullet *)other;
				if(b->parent->id == id)
					return false;
				else 
					return checkProximitywithObject(other,rad);
			}
			break;*/
		default:
			if(rec == true)
				return other->collideDetect(this, false);
			else return false;
			
		}



}


/////////////////////////////////OBJ_object//////////////////////////////////////////////////////


void OBJ_object::giveDim(double &x, double &z, double &rad2){
	x = pos[0];
	z = pos[2];
	rad2 = rad*scale[0]/2;//assumed sphere, not oval
}
//////////////////////////////////////////BOX OBJECT////////////////////////////////////////////
void Box_object::draw(){
  GLfloat white[] = { 1.0, 1.0, 1.0, 1.0 };
   glEnable(GL_LIGHTING);
  // glEnable(GL_TEXTURE_2D);
 //  glBindTexture(GL_TEXTURE_2D, textures[tex]);
   glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, white);
    //glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER,
      //  GL_NEAREST);
        //glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,
        //    GL_NEAREST_MIPMAP_NEAREST);
    glBegin(GL_QUADS);
      // front
   
      
      glNormal3f(0, 0, 1);
      glTexCoord2f(0, 4);
      glVertex3f(-0.5, 0.5, 0.5);
      glTexCoord2f(0, 0);
      glVertex3f(-0.5, -0.5, 0.5);
      glTexCoord2f(4, 0);
      glVertex3f(0.5, -0.5, 0.5);
      glTexCoord2f(4, 4);
      glVertex3f(0.5, 0.5, 0.5);
        glEnd();
   
      // back
      //
        glBegin(GL_QUADS);
     
      glNormal3f(0, 0, -1);
     glTexCoord2f(1, 1);   
      glVertex3f(-0.5, 0.5, -0.5);
      glTexCoord2f(0, 1);
      glVertex3f(0.5, 0.5, -0.5);
      glTexCoord2f(0, 0);
      glVertex3f(0.5, -0.5, -0.5);
      glTexCoord2f(1, 0);
      glVertex3f(-0.5, -0.5, -0.5);
        glEnd(); 
       
        glBegin(GL_QUADS);
   
      // top
      glNormal3f(0, 1, 0);
      glTexCoord2f(0, 1);
      glVertex3f(-0.5, 0.5, -0.5);
      glTexCoord2f(0, 0);
      glVertex3f(-0.5, 0.5, 0.5);
      glTexCoord2f(1, 0);
      glVertex3f(0.5, 0.5, 0.5);
      glTexCoord2f(1, 1);
      glVertex3f(0.5, 0.5, -0.5);
     
    glEnd();

      // bottom
      glBegin(GL_QUADS);
   
      glNormal3f(0, -1, 0);
      glTexCoord2f(0, 0);
      glVertex3f(-0.5, -0.5, -0.5);
      glTexCoord2f(1, 0);
      glVertex3f(0.5, -0.5, -0.5);
      glTexCoord2f(1, 1);
      glVertex3f(0.5, -0.5, 0.5);
      glTexCoord2f(0, 1);
      glVertex3f(-0.5, -0.5, 0.5);
     
      glEnd();
         

      // left
        glBegin(GL_QUADS);
   
      glNormal3f(-1, 0, 0);
      glTexCoord2f(0, 1);
      glVertex3f(-0.5, 0.5, -0.5);
      glTexCoord2f(0, 0);
      glVertex3f(-0.5, -0.5, -0.5);
      glTexCoord2f(1, 0);
      glVertex3f(-0.5, -0.5, 0.5);
      glTexCoord2f(1, 1);
      glVertex3f(-0.5, 0.5, 0.5);
        glEnd();   
      // right
     
        glBegin(GL_QUADS);
   
        glNormal3f(1, 0, 0);
        glTexCoord2f(0, 1);
      glVertex3f(0.5, 0.5, 0.5);
      glTexCoord2f(0, 0);
      glVertex3f(0.5, -0.5, 0.5);
      glTexCoord2f(1, 0);
      glVertex3f(0.5, -0.5, -0.5);
      glTexCoord2f(1, 1);
      glVertex3f(0.5, 0.5, -0.5);

   glEnd();

 // glDisable(GL_TEXTURE_2D);
  glDisable(GL_LIGHTING);
}

//////////////////////PowerUp/////////////////////////////////////////////////////////////////////////////////
void PowerUp::update(int time){
	rotateVec(frontvec, frontvec, upvec, 5);
}
void PowerUp::sayPresent(Quadtree *children[2][2], int pres[2][2]){
	if(taken == false)
		Cylinder_obj::sayPresent(children,pres);
}	
int PowerUp::energise(){
	if(taken == false){
		taken = true;	
		return 5;
	}
	else return 0;
}
void PowerUp::draw(){

	if(taken) 
		return;
  GLfloat white[] = { 1.0, 1.0, 1.0, 1.0 };
   glEnable(GL_LIGHTING);
   glEnable(GL_TEXTURE_2D);
   glBindTexture(GL_TEXTURE_2D, textures[tex]);
   glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, white);
    //glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER,
      //  GL_NEAREST);
        //glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,
        //    GL_NEAREST_MIPMAP_NEAREST);
    glBegin(GL_QUADS);
      // front
   
      
      glNormal3f(0, 0, 1);
      glTexCoord2f(0, 4);
      glVertex3f(-0.5, 0.5, 0.5);
      glTexCoord2f(0, 0);
      glVertex3f(-0.5, -0.5, 0.5);
      glTexCoord2f(4, 0);
      glVertex3f(0.5, -0.5, 0.5);
      glTexCoord2f(4, 4);
      glVertex3f(0.5, 0.5, 0.5);
        glEnd();
   
      // back
      //
        glBegin(GL_QUADS);
     
      glNormal3f(0, 0, -1);
     glTexCoord2f(1, 1);   
      glVertex3f(-0.5, 0.5, -0.5);
      glTexCoord2f(0, 1);
      glVertex3f(0.5, 0.5, -0.5);
      glTexCoord2f(0, 0);
      glVertex3f(0.5, -0.5, -0.5);
      glTexCoord2f(1, 0);
      glVertex3f(-0.5, -0.5, -0.5);
        glEnd(); 
       
        glBegin(GL_QUADS);
   
      // top
      glNormal3f(0, 1, 0);
      glTexCoord2f(0, 1);
      glVertex3f(-0.5, 0.5, -0.5);
      glTexCoord2f(0, 0);
      glVertex3f(-0.5, 0.5, 0.5);
      glTexCoord2f(1, 0);
      glVertex3f(0.5, 0.5, 0.5);
      glTexCoord2f(1, 1);
      glVertex3f(0.5, 0.5, -0.5);
     
    glEnd();

      // bottom
      glBegin(GL_QUADS);
   
      glNormal3f(0, -1, 0);
      glTexCoord2f(0, 0);
      glVertex3f(-0.5, -0.5, -0.5);
      glTexCoord2f(1, 0);
      glVertex3f(0.5, -0.5, -0.5);
      glTexCoord2f(1, 1);
      glVertex3f(0.5, -0.5, 0.5);
      glTexCoord2f(0, 1);
      glVertex3f(-0.5, -0.5, 0.5);
     
      glEnd();
         

      // left
        glBegin(GL_QUADS);
   
      glNormal3f(-1, 0, 0);
      glTexCoord2f(0, 1);
      glVertex3f(-0.5, 0.5, -0.5);
      glTexCoord2f(0, 0);
      glVertex3f(-0.5, -0.5, -0.5);
      glTexCoord2f(1, 0);
      glVertex3f(-0.5, -0.5, 0.5);
      glTexCoord2f(1, 1);
      glVertex3f(-0.5, 0.5, 0.5);
        glEnd();   
      // right
     
        glBegin(GL_QUADS);
   
        glNormal3f(1, 0, 0);
        glTexCoord2f(0, 1);
      glVertex3f(0.5, 0.5, 0.5);
      glTexCoord2f(0, 0);
      glVertex3f(0.5, -0.5, 0.5);
      glTexCoord2f(1, 0);
      glVertex3f(0.5, -0.5, -0.5);
      glTexCoord2f(1, 1);
      glVertex3f(0.5, 0.5, -0.5);

   glEnd();

  glDisable(GL_TEXTURE_2D);
  glDisable(GL_LIGHTING);
}

/*
OBJ_object(): object_pr() { id = 1;}
	int tex;
	void sayPresent(Quadtree *children[2][2], int pres[2][2]);
	bool collideDetect(object_pr* other_obj, bool rec);*/

///////////////////////camera//////////////////////
bool Camera::collideDetect(object_pr* other_obj, bool rec){/*
	double plus[3];
	for(int i = 0; i < 3 ; i++)
		plus[i] = pos[i] - this->back_pos[i];
	
	double back_pos[3];
	for(int i = 0; i < 3 ; i++)
		back_pos[i] = pos[i] + plus[i];*/
	
	if(other_obj->id == WALL_ID)
		{
			Wall_object* obj = (Wall_object*)other_obj;
			double norm[3], pow[3];
			norm[0] = obj->frontvec[0]; norm[1] = obj->frontvec[1]; norm[2] = obj->frontvec[2];
			double dist = sqrt(norm[0]*norm[0] +norm[1]*norm[1] +norm[2]*norm[2]);
			norm[0] /= dist; norm[1] /= dist; norm[2] /= dist;
			pow[0] = obj->pos[0]; pow[1] = obj->pos[1];pow[2] = obj->pos[2];

			double p1[3], p2[3], dot1 = 0, dot2 = 0;
			for(int i = 0; i < 3 ; i++){
				p1[i] = pos[i] - pow[i];
				p2[i] = back_pos[i] - pow[i];

				dot1 += p1[i]*norm[i];
				dot2 += p2[i]*norm[i];
			}

			if(dot1*dot2 >= 0)	return false;//both on same side
			else return true;
		}
	if(other_obj->id == FLOOR_ID){
		y = other_obj->pos[1]; 
		int tt = 1;
		if( y < pos[1]) tt = 1;
		else if( y == pos[1]) tt = 0;
		else tt = -1;
		if (y <= back_pos[1])  tt *= 1;
		else tt *= -1;
		
		if(tt > 0)	return false;
		else return true;
	}
/////////////
/*
			pow[0] = pos[0] - other->pos[0]; pow[1] = pos[2] - other->pos[2];

			double dot = dotprod(pow, norm);
			if(modd(dot) < radius ) return true;
			else return false;		
			Wall_object* obj = (Wall_object*)other_obj;
			double norm[2], pow[2];
			norm[0] = obj->frontvec[0]; norm[1] = obj->frontvec[2];
			double dist = sqrt(norm[0]*norm[0] +norm[1]*norm[1] );
			norm[0] /= dist; norm[1] /= dist;

			pow[0] = pos[0] - obj->pos[0]; pow[1] = pos[2] - obj->pos[2];

			double dot = dotprod(pow, norm);
			if(modd(dot) < 0.3 ) return true;
			else return false;		*/
	return false;

}
void Camera::collide(object_pr *other_obj){
	if((back_x == cam_x)&&(back_x == cam_x)&&(back_x == cam_x)){//collision due to mouse movement
	//	cout<<"here"<<endl;
		double ttx = back_xrot - cam_xrot;
		double tty = back_yrot - cam_yrot;
		cam_xrot += ttx;
		cam_yrot += tty;
		yrot = cam_yrot;
		xrot = cam_xrot;
	}
	/*else{//collision due to keyboard/robot movement
		cam_x = back_x;
		cam_y = back_y;
		cam_z = back_z;
		 pos[0] = back_pos[0];
		 pos[1] = back_pos[1];
		 pos[2] = back_pos[2];
		//cam_xrot = back_xrot;
		//cam_yrot = back_yrot;
		//xrot = cam_xrot;
		//yrot = cam_yrot;
		cout<<cam_z<<" "<<back_z<<endl;
	}*/

	//cout<<"colliding camera"<<endl;
}
