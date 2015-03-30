#include<iostream> 
#include<fstream>
#include<string>
#include<sstream>
#include<vector>
#include "objparser.h"
#include <math.h>
//#include<GL/gl.h>
#include "glInclude.h"
using namespace std;

OBJ_holder *models;
void testcor();


void calc_normals();
/*
int main2(int argc, char *argv[]){



  int i;
  if (argc != 2){
    cout<<"Usage objparser filename";
    exit(1);
  }
  
  cout<<argv[1]<<endl;
  readOBJ(argv[1]);
  //   normalise_v(0.0, 0.0, 0.0, 1.0, 1.0, -1.0);
   normalise_v(-0.5, -0.5, 0.5, 0.5, 0.5, -0.5);
  testcor();
  return 1;
}
*/

int strtoint(const string &s)
{
  istringstream myStream(s);
  int i;
  myStream>>i;
  return i;
}

 
int OBJ_holder::readOBJ(char file[]){

  ifstream fp(file);
  string p;
  char line[200];
  Point tp;
  Face tf;
  Face tft;
  int ind,ind2;
  float homo;

  if(!fp){
    cout<<"Failed to open file: "<<file<<endl;
    exit(1);
  }

  while(1){
    
    fp.getline(line, 199);
    istringstream token(line);
    token>>p;
    if(p.compare("v") == 0) {
	token>>tp.x>>tp.y>>tp.z;
	tp.h = 1.0;
	v.push_back(tp);
      }
	if(p.compare("vt") == 0) {
	token>>tp.x>>tp.y;
	tp.z = 0.0;
	tp.h = 1.0;
	vt.push_back(tp);
	is_text_specified = 1;
      }
    if(p.compare("f") == 0){
      token>>p;
      ind = p.find_first_of('/');
      tf.a =  strtoint(p.substr(0, ind)) - 1;
	  if(is_text_specified==1)//check if texture co-ordinates were specified in the file or not
	  {
		//for getting texture vertex
		ind2 = p.find_first_of('/',ind+1);
		tft.a = strtoint(p.substr(ind+1, ind2-ind-1)) - 1;
	  }
      
	  token>>p;
      ind = p.find_first_of('/');
      tf.b =  strtoint(p.substr(0, ind)) - 1;
	  if(is_text_specified==1)//check if texture co-ordinates were specified in the file or not
	  {
		//for getting texture vertex
		ind2 = p.find_first_of('/',ind+1);
		tft.b = strtoint(p.substr(ind+1, ind2-ind-1)) - 1;
	  }
      

      token>>p;
      ind = p.find_first_of('/');
      tf.c =  strtoint(p.substr(0, ind)) - 1;
	  if(is_text_specified==1)//check if texture co-ordinates were specified in the file or not
	  {
		//for getting texture vertex
		ind2 = p.find_first_of('/',ind+1);
		tft.c = strtoint(p.substr(ind+1, ind2-ind-1)) - 1;
	  }
      //      token>>p;
      //      ind = p.find_first_of('/');
      //      tf.d =  strtoint(p.substr(0, ind)) - 1;

      f.push_back(tf);

	  if(is_text_specified==1)//check if texture co-ordinates were specified in the file or not
		  ft.push_back(tft);
    }
    if(fp.eof()) break;
  }
  
}

/*
void testcor(){

   int ii = 0;
	cout<<f.size()<<endl;
	cout<<v.size()<<endl;
   for(ii=0; ii < f.size(); ii++)
   {  
      cout << f[ii].a<<" "<< f[ii].b <<" "<< f[ii].c<<" "<< endl;
     // cout << v[ii].x<<" "<< v[ii].y <<" "<< v[ii].z<< endl;
   }

}*/

void OBJ_holder::normalise_v(double x1, double y1, double z1, double x2, double y2, double z2){//assume x1 < x2 y1 < y2 z1 > z2

  float maxx = 0.0, maxy = 0.0, maxz = 0.0;
  float lesx = 0.0, lesy = 0.0, lesz = 0.0;

  int i;
  Point tp;
  for(i = 0; i <v.size(); i++){
    tp = v[i];
    if(tp.x>maxx) maxx = tp.x;
    if(tp.y>maxy) maxy = tp.y;
    if(tp.z>maxz) maxz = tp.z;
	
    if(tp.x<lesx) lesx = tp.x;
    if(tp.y<lesy) lesy = tp.y;
    if(tp.z<lesz) lesz = tp.z;
  }
  for(i = 0; i < v.size(); i++){
    v[i].x += -lesx;
    v[i].y += -lesy;
    v[i].z -= maxz;
  }
  
  maxx += -lesx;
  maxy += -lesy;
  maxz += -lesz;

  for(i = 0; i < v.size(); i++){
   if(maxx >0)
    v[i].x /= maxx;
   if(maxy >0)
    v[i].y /= maxy;
   if(maxz >0)
    v[i].z /= maxz;
  }
  //now the vertices are normalised about (0, 0, 0) and (1, 1, -1);
  
  for(i = 0; i < v.size(); i++){
    v[i].x += -0.5;
    v[i].y += -0.5;
    v[i].z += 0.5;
  }
  //now the vertices are normalised about (-0.5, -0.5, 0.5) and (0.5, 0.5, -0.5);

  //scaling
  for(i = 0; i < v.size(); i++){
    v[i].x *= (x2 - x1);
    v[i].y *= (y2-y1);
    v[i].z *= (z1 - z2);
  }
  //moving centre
  for(i = 0; i < v.size(); i++){
    v[i].x += (x2 + x1)/2;
    v[i].y += (y2 + y1)/2;
    v[i].z += (z1 + z2)/2;
    }
  
  calc_normals();
}
void normc(Point a, Point b, Point c, float normal[3]){
  float vector1[3], vector2[3];

  vector1[0] = a.x - b.x;
  vector1[1] = a.y - b.y;
  vector1[2] = a.z - b.z;

  vector2[0] = a.x - c.x;
  vector2[1] = a.y - c.y;
  vector2[2] = a.z - c.z;
  
  normal[0] = vector1[1] *vector2[2] - vector1[2]*vector2[1];
  normal[1] = vector1[2] *vector2[0] - vector1[0]*vector2[2];
  normal[2] = vector1[0] *vector2[1] - vector1[1]*vector2[0];

  double length = sqrt(normal[0]*normal[0] + normal[1]*normal[1] + normal[2]*normal[2] );
  
  normal[0] /= -length;
  normal[1] /= -length;
  normal[2] /= -length;

}

void OBJ_holder::calc_normals(){
  int i;
  for(i = 0; i < f.size(); i++){
    normc(v[f[i].a], v[f[i].b], v[f[i].c], f[i].norm);
  }
}

void OBJ_holder::drawOBJ(){
  //if(is_text_specified==1)
	//  drawOBJwithText();
  //else
	  drawOBJwithoutText();
}
extern GLuint textures[];
void OBJ_holder::drawOBJwithText()
{
	int i;
  for(i = 0; i < f.size(); i++){
	  glEnable(GL_TEXTURE_2D);
    glBegin(GL_TRIANGLES);
   glBindTexture(GL_TEXTURE_2D, textures[0]);
    glNormal3fv(f[i].norm);
	glTexCoord2f(vt[ft[i].a].x, vt[ft[i].a].y);
    glVertex3f(v[f[i].a].x, v[f[i].a].y, v[f[i].a].z);
	glTexCoord2f(vt[ft[i].b].x, vt[ft[i].b].y);
    glVertex3f(v[f[i].b].x, v[f[i].b].y, v[f[i].b].z);
	glTexCoord2f(vt[ft[i].c].x, vt[ft[i].c].y);
    glVertex3f(v[f[i].c].x, v[f[i].c].y, v[f[i].c].z);
    glEnd();
  }	
}
void OBJ_holder::drawOBJwithoutText()
{
	int i;
  for(i = 0; i < f.size(); i++){
    glBegin(GL_TRIANGLES);
    glNormal3fv(f[i].norm);
	glVertex3f(v[f[i].a].x, v[f[i].a].y, v[f[i].a].z);
	glVertex3f(v[f[i].b].x, v[f[i].b].y, v[f[i].b].z);
	glVertex3f(v[f[i].c].x, v[f[i].c].y, v[f[i].c].z);
    glEnd();
  }	
}

