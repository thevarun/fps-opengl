#include "glInclude.h"
extern character *Robot;
//float angle = 0.0f;
float legAngle[2] = {0.0f, 0.0f};
float armAngle[2] = {0.0f, 0.0f};
bool fullScreen = false;

/*      Function:       DrawCube
        Purpose:        As the name would suggest, this is
                                the function for drawing the cubes.
*/
#define MAX_HEALTH_CHARACTER 30

void setcolorHit()
{
		glColor3f(0.5f,0.2f,0.0f);
}

void setcolorback()
{
	
	glColor3f(0.5f,0.5f,0.5f);
				// draw robot
}

void DrawCube(float xPos, float yPos, float zPos)
{
        glPushMatrix();
        glBegin(GL_POLYGON);

                /*      This is the top face*/
                glVertex2f(0.0f, 0.0f);
                glVertex2f(0.0f, -1.0f);
                glVertex2f(-1.0f, -1.0f);
				glVertex2f(-1.0f, 0.0f);
                

                
        glEnd();
        glPopMatrix();
}

/*      Function:       DrawArm
        Purpose:        This function draws the arm
                                for the robot.
*/

void DrawArm(float xPos, float yPos, float zPos)
{
        glPushMatrix();

                /*      Sets color to red*/
                //glColor3f(1.0f, 0.0f, 0.0f);
                glTranslatef(xPos, yPos, zPos);

                /*      Creates 1 x 4 x 1 cube*/
                glScalef(1.0f, 4.0f, 1.0f);
                DrawCube(0.0f, 0.0f, 0.0f);

        glPopMatrix();
}

/*      Function:       DrawHead
        Purpose:        This function will create the
                                head for the robot.
*/

void DrawHead(float xPos, float yPos, float zPos)
{
        glPushMatrix();

                /*      Sets color to white*/
                //glColor3f(1.0f, 1.0f, 1.0f);
                glTranslatef(xPos, yPos, zPos);

                /*      Creates 2 x 2 x 2 cube*/
                glScalef(2.0f, 2.0f, 2.0f);
                DrawCube(0.0f, 0.0f, 0.0f);

        glPopMatrix();
}

/*      Function:       DrawTorso
        Purpose:        Function will do as suggested
                                and draw a torso for our robot.
*/

void DrawTorso(float xPos, float yPos, float zPos)
{
        glPushMatrix();

                /*      Sets color to blue*/
                //glColor3f(0.0f, 0.0f, 1.0f);
                glTranslatef(xPos, yPos, zPos);

                /*      Creates 3 x 5 x 1 cube*/
                glScalef(3.0f, 5.0f, 1.0f);
                DrawCube(0.0f, 0.0f, 0.0f);

        glPopMatrix();
}

/*      Function:       DrawLeg
        Purpose:        Not to sound repetitve, but as suggested
                                this function will draw our robots legs.
*/

void DrawLeg(float xPos, float yPos, float zPos)
{
        glPushMatrix();

                /*      Sets color to yellow*/
                //glColor3f(1.0f, 1.0f, 0.0f);
                glTranslatef(xPos, yPos, zPos);

                /*      Creates 1 x 5 x 1 cube*/
                glScalef(1.0f, 5.0f, 1.0f);
                DrawCube(0.0f, 0.0f, 0.0f);

        glPopMatrix();
}

/*      Function:       DrawRobot
        Purpose:        Function to draw our entire robot
*/

void DrawRobot(float xPos, float yPos, float zPos)
{
        /*      Variables for state of robots legs. True
                means the leg is forward, and False means
                the leg is back. The same applies to the
                robots arm states.
        */
        static bool leg1 = true;
        static bool leg2 = false;
        static bool arm1 = true;
        static bool arm2 = false;

        glPushMatrix();

                /*      This will draw our robot at the
                        desired coordinates.
                */
                //glTranslatef(xPos, yPos, zPos);

                /*      These three lines will draw the
                        various components of our robot.
                */
			setcolorback();
			if(Robot->health<MAX_HEALTH_CHARACTER-30)
			{
				setcolorHit();
			}
            
                DrawHead(1.0f, 2.0f, 0.0f);
			setcolorback();
			if(Robot->health<MAX_HEALTH_CHARACTER-25)
			{
				setcolorHit();
			}
                DrawTorso(1.5f, 0.0f, 0.0f);

                glPushMatrix();


                /*      If the arm is moving forward we will increase
                        the angle; otherwise, we will decrease the
                        angle.
                */
				setcolorback();
				if(Robot->health<MAX_HEALTH_CHARACTER-20)
				{
					setcolorHit();
				}
        
                
                glTranslatef(0.0f, -0.5f, 0.0f);
                glRotatef(armAngle[0], 1.0f, 0.0f, 0.0f);
                DrawArm(2.5f, 0.0f, -0.5f);
				setcolorback();
	       
        glPopMatrix();

        glPushMatrix();


		if(Robot->health<MAX_HEALTH_CHARACTER-15)
		{
			setcolorHit();
		}
                glTranslatef(0.0f, -0.5f, 0.0f);
                glRotatef(armAngle[1], 1.0f, 0.0f, 0.0f);
                DrawArm(-1.5f, 0.0f, -0.5f);
				setcolorback();
		
		
		glPopMatrix();

        /*      Now its time to rotate the legs relative to the
                robots position in the world, this is the first
                leg, ie the right one.
        */
        glPushMatrix();

                /*      If the leg is moving forward we will increase
                        the angle; otherwise, we will decrease the
                        angle.
                */
		if(Robot->health<MAX_HEALTH_CHARACTER-5)
		{
			setcolorHit();
		}
        
                glTranslatef(0.0f, -0.5f, 0.0f);
                glRotatef(legAngle[0], 1.0f, 0.0f, 0.0f);


                /*      Time to draw the leg.
                */
                DrawLeg(-0.5f, -5.0f, -0.5f);
				setcolorback();
		

        glPopMatrix();

        /*      Same as above, for the left leg.
        */
        glPushMatrix();

            if(Robot->health<MAX_HEALTH_CHARACTER-10)
			{
				setcolorHit();
			}
        
                glTranslatef(0.0f, -0.5f, 0.0f);
                glRotatef(legAngle[1], 1.0f, 0.0f, 0.0f);
                DrawLeg(1.5f, -5.0f, -0.5f);
				setcolorback();
        glPopMatrix();

        glPopMatrix();

}
