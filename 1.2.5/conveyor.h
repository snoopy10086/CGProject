#pragma once
#include"Shape.h"

#define EDGE (1.0f)
class conveyor
{
public:
	float PositionX;	
	float PositionY;
	//(X,Y) means left up point of this conveyor
	//float PositionZ;
	float MotionX;
	float MotionY;
	int count = 0;
	float move = 0;
	conveyor(float PositionX, float PositionY, float MotionX, float MotionY);
	
protected:
	void Texture_Circle(int i);
	void Texture_Cylinder(int i);
	void DrawConveyor2();

public:
	bool ifOntheConveyor(Shape* shape);	//to judge if the shape is on this conveyor
	void AddMotion(Shape* shape);
	virtual void draw();
	void Move();
};

