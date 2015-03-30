#include "robotfigure.h"

 float defview_rotate[16]  = { 1,0,0,0, 0,1,0,0, 0,0,1,0, 0,0,0,1 };



 appendageState    defArmL = {0.0, -42.7, 0.0, FORWARD, FORWARD, NONE};
 appendageState    defArmR = {0.0, -42.7, 0.0, BACKWARD, BACKWARD, NONE};
 appendageState    defLegL = {0.0, 42.7, -12.6,  BACKWARD, BACKWARD, FORWARD};
 appendageState    defLegR = {0.0, 42.7, -12.6, FORWARD, FORWARD, FORWARD};
 robotState          defRS = {0.5225, 4.5, UP, BACKWARD};
