#pragma once

class Shape
{
public:
	//Robot* TheRobot;
	float globalX, globalY, globalZ;  // 世界坐标系的坐标
	float rotateX, rotateY, rotateZ;  // 相对于x, y, z轴旋转角度
	float scale;
	int Texture;
	double getGlobalX() {
		return this->globalX;
	}
	double getGlobalY() {
		return this->globalY;
	}
	double getGlobalZ() {
		return this->globalZ;
	}
	void transfer(double dx, double dy, double dz);  // 平移
	void rotate(double dx, double dy, double dz);  // 旋转
	void Scaling(float scale);
	virtual void Draw();				// 供外部调用的绘制函数
};

class ConeCylinder : public Shape
{
public:
	virtual void Draw();
	ConeCylinder(float globalX, float globalY, float globalZ);
private:
	void Texture_ConeCylinder(int i);
	void Texture_Circle(int i, float r);
};

class Cylinder : public Shape
{
public:
	virtual void Draw();
	Cylinder(float globalX, float globalY, float globalZ);
private:
	void Texture_Circle(int i, float r);
	void Texture_CylinderCircle(int i);
	void Texture_Cylinder(int i);
};

class Cone : public Shape
{
public:
	virtual void Draw();
	Cone(float globalX, float globalY, float globalZ);
private:
	void Texture_Cone(int i);
};

class Cube : public Shape
{
public:
	virtual void Draw();
	Cube(float globalX, float globalY, float globalZ);
private:

};

//六棱柱体
class Prism :public Shape
{
public:
	virtual void Draw();
	Prism(float globalX, float globalY, float globalZ);
private:

};

//六棱台(英文Trustum Of A Pyramid太长了)
class Trustum :public Shape
{
public:
	virtual void Draw();
	Trustum(float globalX, float globalY, float globalZ);
private:

};

