#ifndef COLLISION_STUFF
#define COLLISION_STUFF
//#include <iostream>
#include <string>
#include <set>
#include <math.h>
#include <sstream>
#include <stdlib.h>
#include <vector>
#include "objprimitive.h"
#include <iostream>
using namespace std;
//typedef object_pr Object_pr;

class Object_Pair {
public:
	object_pr* obj1;
	object_pr* obj2;
};

#define TIME_BETWEEN_CHECKS 25

#define MAX_QUADTREE_DEPTH  6
#define MIN_GUYS_PER_QUADTREE  2
#define MAX_GUYS_PER_QUADTREE  5





////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//Our data structure for making collision detection faster
class Quadtree {
	public:
		
		/* The children of this, if this has any.  children[0][*] are the
		 * children with x coordinates ranging from minX to centerX.
		 * children[1][*] are the children with x coordinates ranging from
		 * centerX to maxX.  Similarly for the other dimension of the children
		 * array.
		 */
		Quadtree *children[2][2];
		//Whether this has children
		bool hasChildren;
		//The objs in this, if this doesn't have any children
		set<object_pr*> objs;
		//The depth of this in the tree
		int depth;
		//The number of objs in this, including those stored in its children
		int numObject_prs;
		
		//Adds a obj to or removes one from the children of this
		//called after checking that the children exist
		void fileObject_pr(object_pr* obj, bool addObject_pr) {
			int xi, zi;	
			int pres[2][2];
			for(xi =0; xi < 2; xi++)
				for(zi = 0; zi < 2; zi++)
					pres[xi][zi] = 0;		
			//Figure out in which child(ren) the obj belongs
			obj->sayPresent(children, pres);

			//Add or remove the obj
			for(xi =0; xi < 2; xi++)
				for(zi = 0; zi < 2; zi++)
					if(pres[xi][zi] > 0) {
						if (addObject_pr) 
							children[xi][zi]->add(obj);
						else 
							children[xi][zi]->remove(obj);
						
					}
		}
		
		//Creates children of this, and moves the objs in this to the children
		void haveChildren() {
			for(int x = 0; x < 2; x++) {
				float minX2;
				float maxX2;
				if (x == 0) {
					minX2 = minX;
					maxX2 = centerX;
				}
				else {
					minX2 = centerX;
					maxX2 = maxX;
				}
				
				for(int z = 0; z < 2; z++) {
					float minZ2;
					float maxZ2;
					if (z == 0) {
						minZ2 = minZ;
						maxZ2 = centerZ;
					}
					else {
						minZ2 = centerZ;
						maxZ2 = maxZ;
					}
					
					children[x][z] =
						new Quadtree(minX2, minZ2, maxX2, maxZ2, depth + 1);
				}
			}
			
			//Remove all objs from "objs" and add them to the new children
			for(set<object_pr*>::iterator it = objs.begin(); it != objs.end();
					it++) {
				object_pr* obj = *it;
				fileObject_pr(obj, true);
			}
			objs.clear();
			
			hasChildren = true;
		}
		
		//Adds all objs in this or one of its descendants to the specified set
		void collectObject_prs(set<object_pr*> &gs) {
			if (hasChildren) {
				for(int x = 0; x < 2; x++) {
					for(int z = 0; z < 2; z++) {
						children[x][z]->collectObject_prs(gs);
					}
				}
			}
			else {
				for(set<object_pr*>::iterator it = objs.begin(); it != objs.end();
						it++) {
					object_pr* obj = *it;
					gs.insert(obj);
				}
			}
		}
		
		//Destroys the children of this, and moves all objs in its descendants
		//to the "objs" set
		void destroyChildren() {
			//Move all objs in descendants of this to the "objs" set
			collectObject_prs(objs);
			
			for(int x = 0; x < 2; x++) {
				for(int z = 0; z < 2; z++) {
					delete children[x][z];
				}
			}
			
			hasChildren = false;
		}
		
		//Removes the specified obj at the indicated position
		
	//public:
		float minX;
		float minZ;
		float maxX;
		float maxZ;
		float centerX; //(minX + maxX) / 2
		float centerZ; //(minZ + maxZ) / 2
		
		//Constructs a new Quadtree.  d is the depth, which starts at 1.
		Quadtree(float minX1, float minZ1, float maxX1, float maxZ1, int d) {
			minX = minX1;
			minZ = minZ1;
			maxX = maxX1;
			maxZ = maxZ1;
			centerX = (minX + maxX) / 2;
			centerZ = (minZ + maxZ) / 2;
			
			depth = d;
			numObject_prs = 0;
			hasChildren = false;
		}
		
		~Quadtree() {
			if (hasChildren) {
				destroyChildren();
			}
		}


		
		void remove(object_pr* obj, float x, float z) {
			numObject_prs--;
			
			if (hasChildren && numObject_prs < MIN_GUYS_PER_QUADTREE) {
				destroyChildren();
			}
			
			if (hasChildren) {
				fileObject_pr(obj, false);
			}
			else {
				objs.erase(obj);
			}
		}
		
		//Adds a obj to this
		void add(object_pr* obj) {
			numObject_prs++;
			if (!hasChildren && depth < MAX_QUADTREE_DEPTH &&
				numObject_prs > MAX_GUYS_PER_QUADTREE) {
				haveChildren();
			}
			
			if (hasChildren) {
				fileObject_pr(obj, true);
			}
			else {
				objs.insert(obj);
			}
		}
		
		//Removes a obj from this
		void remove(object_pr* obj) {
			remove(obj, obj->pos[0], obj->pos[2]);
		}
		
		//Changes the position of a obj in this from the specified position to
		//its current position
		
		//Adds potential collisions to the specified set
		void potentialCollisions(set<Object_Pair*> &collisions) {
			if (hasChildren) {
				for(int x = 0; x < 2; x++) {
					for(int z = 0; z < 2; z++) {
						children[x][z]->potentialCollisions(collisions);
					}
				}
			}
			else {
				//Add all pairs (obj1, obj2) from objs
				for(set<object_pr*>::iterator it = objs.begin(); it != objs.end();
						it++) {
					object_pr* obj1 = *it;
					for(set<object_pr*>::iterator it2 = objs.begin();
							it2 != objs.end(); it2++) {
						object_pr* obj2 = *it2;
						//This test makes sure that we only add each pair once
						if (obj1 < obj2) {
							Object_Pair* gp;
							gp = new Object_Pair();
							gp->obj1 = obj1;
							gp->obj2 = obj2;
							collisions.insert(gp);

						}
					}
				}
			}
		}
} ;

/*
void update(int value){

 	object_pr *temp = theworld.next;
	while(temp != NULL) {
		if(temp->id > 10){
			quadtree->remove(temp);
			temp->update_B(TIME_BETWEEN_CHECKS);
			quadtree->add(temp);
		}
   		temp = temp->next;
	}

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
	glutTimerFunc(TIME_BETWEEN_CHECKS, update, 0);
}
void initCollisionSystem()
		{
			
			quadtree = new Quadtree(-50, -50, 50, 50, 0);
			object_pr *temp = theworld.next;
			while(temp != NULL) 
			{
				quadtree->add(temp);
	   			temp = temp->next;
			}
			//glutTimerFunc(TIME_BETWEEN_CHECKS, update, 0);
		}
*/
#endif

