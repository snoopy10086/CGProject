#pragma once
#include <stdlib.h>
#include <gl/glut.h>
#include <stdio.h>
#include <math.h>
#include <string.h>
#include"Shape.h"
#include <vector>
#define CollisionThreshold (0.5f)
//#define DEBUG
/*
 * the parent class , two types of robot will inherit from this
 */
class Robot
{
public:
	/* the position of the robot */
	float GripperX;
	float GripperY;
	float GripperZ;
	float BindPositionX = 0;
	float BindPositionY = 0.8;
	float BindPositionZ = 0;
	/*
	 * bCatch : the state of the claw, if bCatch is set, the robot is catch a shape
	 */
	float fCatch = 45;
	bool bCatch = false;
	double getGripperX() {
		return this->GripperX;
	}
	double getGripperY() {
		return this->GripperY;
	}
	double getGripperZ() {
		return this->GripperZ;
	}
	bool enable;
	Shape* TheShape;
protected:
	/*
	 * the methods used to draw the robot
	 */
	void Draw_Robot();
	void Draw_Claw(float angle);
public:
	/*
	 * according to position info above to draw this robot
	 * update the position and the claw's angle while the state transist
	 */
	virtual void Draw();
	virtual void update();
	void not_catch();
};

/*
 * the claw of robot will inherit from class Robot
 */
class Robot_1 : public Robot
{
public:
	/*
	 * length : the length of the arm
	 * quad_obj : use to draw the arm
	 */
	float length = 3;
	GLUquadricObj* quad_obj = NULL;
	Robot_1(float PositionX, float PositionY, float PositionZ);
public:
	void Draw();
	void update();
	void len_inc();
	void len_dec();
};

class Robot_2 : public Robot
{
public:
	/* four DoFs of the robot  */
	GLfloat rotate1 = 90;
	GLfloat rotate2 = 0;
	GLfloat rotate3 = 45;
	GLfloat rotate4 = 90;

	/* whether the robot binds to a shape */
	bool IsBind = false;
	/* whether to check if bind */
	bool Check = false;
	/* the time flag of capture process animation */
	int timeflag = -1;

	float PositionX = 4;
	float PositionY = 0.1;
	float PositionZ = 4;

	/* overall size */
	float ZoomIndex = 1.0;
	Robot_2(float PositionX, float PositionY, float PositionZ);
	
	GLUquadricObj* quad_obj = NULL;
protected:
	/*
	 * the methods used to draw the robot
	 */
	void DrawJoint();
	void DrawRod(GLdouble baseR, GLdouble topR, GLdouble h);
	/* find the position of bound shape */
	void SetBindPosition();
public:
	void Draw();
	void update();
	/* the grab animation */
	void HandleRotate();
	void setPositionX(float position);
	void setPositionY(float position);
	void setPositionZ(float position);
	void not_is_bind();
};
