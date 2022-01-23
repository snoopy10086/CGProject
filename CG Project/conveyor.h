#pragma once
#include"Shape.h"

#define EDGE (1.0f)
class conveyor
{
public:
	float PositionX=0;	// 世界坐标系的坐标(怎么说，就是一个画传送带这个整体的起点，是传送带的中心)
	float PositionY=0;
	float PositionZ=0;
	float ConrotateX = 0, ConrotateY = 0, ConrotateZ = 0;
	//(X,Y) means left up point of this conveyor
	//float PositionZ;
	float MotionX=0;
	float MotionZ = 0;
	int count = 0;
	float move = 0;///不需要
	conveyor(float PositionX, float PositionY, float PositionZ, float MotionX, float MotionY);
	void rotate(double dx, double dy, double dz);  // 旋转
	
protected:
	void Texture_Circle(int i);
	void Texture_Cylinder(int i);
	void DrawConveyor2();

public:
	bool ifOntheConveyor(Shape* shape);	//to judge if the shape is on this conveyor
	void AddMotion(Shape* shape);
	virtual void draw();
	//void MoveShape();///不需要
};

