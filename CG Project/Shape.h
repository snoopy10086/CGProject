#pragma once

class Shape
{
public:
	//Robot* TheRobot;
	float globalX=0, globalY=0, globalZ=0;  // 世界坐标系的坐标
	float rotateX=0, rotateY=0, rotateZ=0;  // 相对于x, y, z轴旋转角度
	float scaleX=1, scaleY = 1, scaleZ = 1;
	int Texture=0;
	int Texture2=0;
	int Type = -1;//标识这个shape的类型
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
	void scaling(float scaleX, float scaleY, float scaleZ );
	virtual void Draw();				// 供外部调用的绘制函数
	int RetType() {//返回馅料/月饼的类型
		return Type;
	}
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
protected:
	void Texture_Circle(int i, float r);
	void Texture_CylinderCircle(int i,int j);
	void Texture_Cylinder(int i);
};


class YueBingPi : public Cylinder
{
public:
	YueBingPi(float globalX, float globalY, float globalZ);
};

class YueBing : public Cylinder
{
public:
	YueBing(float globalX, float globalY, float globalZ);
	YueBing(float globalX, float globalY, float globalZ, int Type);
protected:
	void SetType(int t);
};

class Sphere : public Shape
{
public:
	virtual void Draw();
	Sphere(float globalX, float globalY, float globalZ);
	Sphere(float globalX, float globalY, float globalZ, int Type);
protected:
	void Texture_Sphere(int i);
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


class LiWuHePingMian : public Cube
{
public:
	virtual void Draw();
	LiWuHePingMian(float globalX, float globalY, float globalZ);
	LiWuHePingMian(float globalX, float globalY, float globalZ, int Type);
};
class LiWuHe : public Cube
{
public:
	virtual void Draw();
	LiWuHe(float globalX, float globalY, float globalZ);
	LiWuHe(float globalX, float globalY, float globalZ, int Type);
private:
	void texture_LiWuHe(int i);
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

