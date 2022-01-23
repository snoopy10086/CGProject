#pragma once

class Shape
{
public:
	//Robot* TheRobot;
	float globalX=0, globalY=0, globalZ=0;  // ��������ϵ������
	float rotateX=0, rotateY=0, rotateZ=0;  // �����x, y, z����ת�Ƕ�
	float scaleX=1, scaleY = 1, scaleZ = 1;
	int Texture=0;
	int Texture2=0;
	int Type = -1;//��ʶ���shape������
	double getGlobalX() {
		return this->globalX;
	}
	double getGlobalY() {
		return this->globalY;
	}
	double getGlobalZ() {
		return this->globalZ;
	}
	void transfer(double dx, double dy, double dz);  // ƽ��
	void rotate(double dx, double dy, double dz);  // ��ת
	void scaling(float scaleX, float scaleY, float scaleZ );
	virtual void Draw();				// ���ⲿ���õĻ��ƺ���
	int RetType() {//��������/�±�������
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

//��������
class Prism :public Shape
{
public:
	virtual void Draw();
	Prism(float globalX, float globalY, float globalZ);
private:

};

//����̨(Ӣ��Trustum Of A Pyramid̫����)
class Trustum :public Shape
{
public:
	virtual void Draw();
	Trustum(float globalX, float globalY, float globalZ);
private:

};

