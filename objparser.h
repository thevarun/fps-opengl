//objparser.h
#ifndef OBJPARSER
#define OBJPARSER
#include<vector>

//int readOBJ(char file[]);
//void normalise_v(double x1, double y1, double z1, double x2, double y2, double z2);

struct Point {
	float x, y, z;
	float h;
};

struct Face {
//triangulated
	int a, b, c;
	float norm[3];
};

extern std::vector<Face> f;
extern std::vector<Point> v;

class OBJ_holder {
	std::vector<Face> f;
	std::vector<Face> ft;
	std::vector<Point> v;
	std::vector<Point> vt;
	int readOBJ(char file[]);
	void normalise_v(double x1, double y1, double z1, double x2, double y2, double z2);
	void calc_normals();
	int is_text_specified;
	
public:
	OBJ_holder(char file[]){
		is_text_specified = 0;
		readOBJ(file);
   		normalise_v(-0.5, -0.5, -0.5, 0.5, 0.5, 0.5);
		calc_normals();
	}
	OBJ_holder(){
		is_text_specified = 0;
		//only required for dynamic array creation
	}
	void init(char file[]){
		is_text_specified = 0;
		readOBJ(file);
   		normalise_v(-0.5, -0.5, -0.5, 0.5, 0.5, 0.5);
		calc_normals();
	}
	virtual void drawOBJ();
	void drawOBJwithText();
	void drawOBJwithoutText();
	~OBJ_holder(){
		//destroy vectors
	}
};
extern OBJ_holder *models;
#endif

