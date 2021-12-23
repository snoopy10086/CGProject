#pragma once

class Shape
{
public:
	//Robot* TheRobot;
	float globalX, globalY, globalZ;  // ��������ϵ������
	float rotateX, rotateY, rotateZ;  // �����x, y, z����ת�Ƕ�
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
	void transfer(double dx, double dy, double dz);  // ƽ��
	void rotate(double dx, double dy, double dz);  // ��ת
	void Scaling(float scale);
	virtual void Draw();				// ���ⲿ���õĻ��ƺ���
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

