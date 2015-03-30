
#include<fstream>
#include<string>
#include<sstream>
#include<iostream> 
#include "glInclude.h"
//#include "objparser.h"
//#include "objprimitive.h"
//#include "loadImage.h"
#include "enemy.h"

#define CHILD_LEVEL 7

using namespace std;
void getObject(object_pr* &temp2, ifstream &fp, int id);
extern object_pr* theworldsend;

class stack{
  int level;
  int noc[CHILD_LEVEL];
  object_pr* prev_obj[CHILD_LEVEL];
public:

  stack(object_pr &xxx){
    prev_obj[0] = &xxx;
    level = 0;
    for(int i = 0; i < CHILD_LEVEL  ;i++)
      noc[i] = 0;

    prev_obj[0]->next = new character();
    prev_obj[0] = prev_obj[0]->next;
    
    prev_obj[0]->next = new Camera();
    prev_obj[0] = prev_obj[0]->next;

  }

  void addNext(ifstream &fp, int id){
    object_pr *next;      
    cout<<"level: "<<level<<endl;
    if(level != 0)
      cout<<"No of objects at level remaining: "<<noc[level-1]<<endl;
    while(level != 0)
      if (noc[level-1] <= 0){
	level--;
	cout<<"--------------------End Level: "<<(level+1)<<" -----------"<<endl;
      }
      else break;

    getObject(next, fp, id);
    if(level > 0)
      noc[level-1]--;
    prev_obj[level]->next = next;
    prev_obj[level] = next;
    
  }
  void addChildLevel(int x, int id, ifstream &fp){
    cout<<"--------------------Start level: "<<(level+1)<<" ----------------------"<<endl;
    cout<<"no of objects at level : "<<x<<endl;
    noc[level] = x-1;//no of childrem starts with 1;
      object_pr *child;      
      getObject(child, fp, id);
      prev_obj[level]->child = child;
      prev_obj[++level] = child;
  }
  void annoy(){
	theworldsend = prev_obj[0];
  }
} object_ll(theworld);

GLuint *textures;
My_img *tex_images;
int no_of_tex = 0;
int no_of_models = 0;
int no_of_objs = 0;

void getObject(object_pr* &temp2, ifstream &fp, int id){
  char objstuff[200];

      switch(id){
	
      case 1:
	{
	//simple encapsulation of an instance of the obj file
	OBJ_object *temp = new OBJ_object();
	string bg;
	double i, j, k;

	{
	  fp.getline(objstuff, 199);
	  cout<<objstuff<<endl;
	  istringstream tok(objstuff);
	  tok>>bg>>i>>j>>k;
	  cout<<bg<<i<<j<<k<<endl;
	  temp->upvec[0] = i; temp->upvec[1] = j;temp->upvec[2] = k;
	}
	{
	  fp.getline(objstuff, 199);
	  istringstream tok(objstuff);
	  tok>>bg>>i>>j>>k;
	  cout<<i<<j<<k<<endl;
	  temp->frontvec[0] = i; temp->frontvec[1] = j;temp->frontvec[2] = k;
	}
	{
	  fp.getline(objstuff, 199);
	  istringstream tok(objstuff);
	  tok>>bg>>i>>j>>k;
	  cout<<i<<j<<k<<endl;
	  temp->pos[0] = i; temp->pos[1] = j;temp->pos[2] = k;
	}
	{
	  fp.getline(objstuff, 199);
	  istringstream tok(objstuff);
	  tok>>bg>>i>>j>>k;
	  cout<<i<<j<<k<<endl;
	  temp->scale[0] = i; temp->scale[1] = j;temp->scale[2] = k;
	}
	{
	  int mm;
	  fp.getline(objstuff, 199);
	  istringstream tok(objstuff);
	  tok>>bg>>mm;
	  temp->shape = mm;
	}
	temp2 = temp;
	break;
	}
      case 2:
      case 3:
	{
	//simple encapsulation of an instance of the obj file
	Wall_object *temp;
	if(id == 2) temp = new Wall_object();
	else temp = new Floor_object();
	string bg;
	double i, j, k;

	{
	  fp.getline(objstuff, 199);
	  cout<<objstuff<<endl;
	  istringstream tok(objstuff);
	  tok>>bg>>i>>j>>k;
	  cout<<bg<<i<<j<<k<<endl;
	  temp->upvec[0] = i; temp->upvec[1] = j;temp->upvec[2] = k;
	}
	{
	  fp.getline(objstuff, 199);
	  istringstream tok(objstuff);
	  tok>>bg>>i>>j>>k;
	  cout<<i<<j<<k<<endl;
	  temp->frontvec[0] = i; temp->frontvec[1] = j;temp->frontvec[2] = k;
	}
	{
	  fp.getline(objstuff, 199);
	  istringstream tok(objstuff);
	  tok>>bg>>i>>j>>k;
	  cout<<i<<j<<k<<endl;
	  temp->pos[0] = i; temp->pos[1] = j;temp->pos[2] = k;
	}
	{
	  fp.getline(objstuff, 199);
	  istringstream tok(objstuff);
	  tok>>bg>>i>>j>>k;
	  cout<<i<<j<<k<<endl;
	  temp->scale[0] = i; temp->scale[1] = j;temp->scale[2] = k;
	}
	{
	  int mm;
	  fp.getline(objstuff, 199);
	  istringstream tok(objstuff);
	  tok>>bg>>mm;
	  temp->tex = mm;
	}
	temp2 = temp;
	break;
	}
	/*      case 99:
	{
	character *temp = new character();
	temp2 = temp;
	break;
	}*/
      case 100:
	{
	Enemy *temp = new Enemy();
	string bg;
	double i, j, k;

	{
	  fp.getline(objstuff, 199);
	  cout<<objstuff<<endl;
	  istringstream tok(objstuff);
	  tok>>bg>>i>>j>>k;
	  cout<<bg<<i<<j<<k<<endl;
	  temp->upvec[0] = i; temp->upvec[1] = j;temp->upvec[2] = k;
	}
	{
	  fp.getline(objstuff, 199);
	  istringstream tok(objstuff);
	  tok>>bg>>i>>j>>k;
	  cout<<i<<j<<k<<endl;
	  temp->frontvec[0] = i; temp->frontvec[1] = j;temp->frontvec[2] = k;
	}
	{
	  fp.getline(objstuff, 199);
	  istringstream tok(objstuff);
	  tok>>bg>>i>>j>>k;
	  cout<<i<<j<<k<<endl;
	  temp->pos[0] = i; temp->pos[1] = j;temp->pos[2] = k;
	}
	temp2 = temp;
	break;
	}
	case 11:
	{
	PowerUp *temp = new PowerUp();
	string bg;
	double i, j, k;

	{
	  fp.getline(objstuff, 199);
	  istringstream tok(objstuff);
	  tok>>bg>>i>>j>>k;
	  cout<<i<<j<<k<<endl;
	  temp->pos[0] = i; temp->pos[1] = j;temp->pos[2] = k;
	}
	{
	  int mm;
	  fp.getline(objstuff, 199);
	  istringstream tok(objstuff);
	  tok>>bg>>mm;
	  temp->tex = mm;
	}
	temp2 = temp;
	break;
	}
	case BOX_ID:
	{
	Box_object *temp = new Box_object();
	string bg;
	double i, j, k;

	{
	  fp.getline(objstuff, 199);
	  istringstream tok(objstuff);
	  tok>>bg>>i>>j>>k;
	  cout<<i<<j<<k<<endl;
	  temp->pos[0] = i; temp->pos[1] = j;temp->pos[2] = k;
	}
	{
	  int mm;
	  fp.getline(objstuff, 199);
	  istringstream tok(objstuff);
	  tok>>bg>>mm;
	  temp->scale[0] = mm;
	  temp->scale[1] = mm;
	  temp->scale[2] = mm;
	}
	temp2 = temp;
	break;
	}
      default:
	break;
      }

}



void readTextScene(const char* file){

  ifstream fp(file);

  if(!fp){
    cout<<"Failed to open file: "<<file<<endl;
    exit(1);
  }

  //an empty line can appear anywhere in the file except the end
  //maximum line length 190
  //0 = comment
  string opt;
  
  char line[200];
  int pt_model = 0, pt_tex = 0;

  while(1){
    
    fp.getline(line, 199);
    istringstream token(line);
    token>>opt;
    cout<<opt<<endl;
    if(opt.compare("end") == 0) //comment
      break;
    if(opt.compare("//") == 0) //comment
      continue;

    else if(opt.compare("init") == 0){//tell no. of things
      token>>no_of_tex>>no_of_models>>no_of_objs;

      textures = new GLuint[no_of_tex];
      glGenTextures(no_of_tex, textures);
      tex_images = new My_img[no_of_tex];

      models = new OBJ_holder[no_of_models];
    }

    else if(opt.compare("obj") == 0){
      char file[30];
      token>>file;
      models[pt_model++].init(file);
    }


    else if(opt.compare("tex") == 0){
      char file[30];
      token>>file;
      loadImage(file, tex_images[pt_tex]);
      
      glBindTexture(GL_TEXTURE_2D, textures[pt_tex]);
      glTexImage2D(GL_TEXTURE_2D, 0, 3, tex_images[pt_tex].height,tex_images[pt_tex].width, 0, GL_RGB, GL_UNSIGNED_BYTE, tex_images[pt_tex].img);
      gluBuild2DMipmaps(GL_TEXTURE_2D,3, tex_images[pt_tex].height,tex_images[pt_tex].width,GL_RGB, GL_UNSIGNED_BYTE, tex_images[pt_tex].img);
      glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
      glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
      glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
      glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_NEAREST);
      glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_BLEND);
      pt_tex++;
    }


    else if(opt.compare("id") == 0){//a display object
      int id;
      token>>id;
      object_ll.addNext(fp, id);
    }
    if(opt.compare("child") == 0){
      int noc;
      token>>noc;
      object_pr *child;
      string opt; 
      int id;
      char objstuff[200];
      fp.getline(objstuff, 199);
      istringstream tok(objstuff);
      tok>>opt>>id;
      object_ll.addChildLevel(noc, id, fp);
    }
    if(fp.eof()) break;
  }
  object_ll.annoy();
}
