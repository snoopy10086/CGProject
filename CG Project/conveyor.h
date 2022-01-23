#pragma once
#include"Shape.h"

#define EDGE (1.0f)
class conveyor
{
public:
	float PositionX=0;	// ��������ϵ������(��ô˵������һ�������ʹ�����������㣬�Ǵ��ʹ�������)
	float PositionY=0;
	float PositionZ=0;
	float ConrotateX = 0, ConrotateY = 0, ConrotateZ = 0;
	//(X,Y) means left up point of this conveyor
	//float PositionZ;
	float MotionX=0;
	float MotionZ = 0;
	int count = 0;
	float move = 0;///����Ҫ
	conveyor(float PositionX, float PositionY, float PositionZ, float MotionX, float MotionY);
	void rotate(double dx, double dy, double dz);  // ��ת
	
protected:
	void Texture_Circle(int i);
	void Texture_Cylinder(int i);
	void DrawConveyor2();

public:
	bool ifOntheConveyor(Shape* shape);	//to judge if the shape is on this conveyor
	void AddMotion(Shape* shape);
	virtual void draw();
	//void MoveShape();///����Ҫ
};

