#include "conveyor.h"
#include <stdlib.h>
#include <gl/glut.h>
#include <stdio.h>
#include <string.h>
#include <iostream>
using namespace std;
extern unsigned int texture[50];
void Texture_cube(int n, int i, int j, int k);

conveyor::conveyor(float PositionX, float PositionY, float PositionZ, float MotionX, float MotionY)
{
	this->PositionX = PositionX;
	this->PositionY = PositionY;
	this->PositionZ = PositionZ;
	this->MotionX = MotionX;
	this->MotionY = MotionY;
}

void conveyor::rotate(double dx, double dy, double dz)
{
	//cout << "rx" << this->rotateX << endl;
	this->ConrotateX += dx;
	this->ConrotateY += dy;
	this->ConrotateZ += dz;
}

bool conveyor::ifOntheConveyor(Shape* shape)
{
	float shapeZ = shape->getGlobalZ();
	float shapeX = shape->getGlobalX();
	float shapeY = shape->getGlobalY();

	if (fabs(shapeY - 0.2) < 1e-6 && shapeX > this->PositionX - 0.75 && shapeX< this->PositionX + 0.75 && shapeZ>this->PositionZ - 0.2 && shapeZ < this->PositionZ + 0.2)
	{ 
		/*cout << "sy:" << shapeY << endl;
		cout << "sx:" << shapeX << endl;
		cout << "sz:" << shapeZ << endl;
		cout << "py:" << this->PositionY << endl;
		cout << "px:" << this->PositionX << endl;
		cout << "pz:" << this->PositionZ << endl;
		cout << "------------------" << endl;*/
		return true;
	}
	return false;
}

void conveyor::AddMotion(Shape* shape)//��shape�ڴ��ʹ��Ͼ��˶�
{
	if (ifOntheConveyor(shape)) 
	{
		this->MotionX = -0.1;
		//shape->rotateX = this->ConrotateX;//���ϵ�����Ҫ�ʹ��ʹ�һ��ѡ����������ʹ�ת�ķ����ƶ�---����д���ԣ�����motionX����
		//shape->rotateY = this->ConrotateY;
		//shape->rotateZ = this->ConrotateZ;
		shape->transfer(this->MotionX, this->MotionY, 0);
	}
	return ;
}

//���ƴ������Բ�Σ����ڴ��ʹ������ϣ�iΪ������
void conveyor::Texture_Circle(int i)
{
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texture[i]);  //ѡ������texture[1]
	GLfloat mat_specular[] = { 1., 1., 1., 1.0 };	         // ���淴����ɫ
	GLfloat mat_shininess[] = { 50.0 };							// ���淴�����
	GLfloat lmodel_ambient[] = { 1., 1., 1., 1.0 };		// ɢ����ɫ
	GLfloat lmodel_emmision[] = { 0.0, 0.0, 0.0, 1.0 };

	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, lmodel_ambient);
	glMaterialfv(GL_FRONT, GL_EMISSION, lmodel_emmision);
	glPushMatrix();
	GLUquadricObj* frontface = gluNewQuadric();
	gluQuadricTexture(frontface, true);
	gluQuadricDrawStyle(frontface, GLU_FILL);
	gluDisk(frontface, 0, 0.5, 100, 2);
	glPopMatrix();
	glDisable(GL_TEXTURE_2D);
}

//���ƴ������Բ���棬iΪΪ�����
void conveyor::Texture_Cylinder(int i)
{
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texture[i]);  //ѡ������texture[1]
	GLfloat mat_specular[] = { 1., 1., 1., 1.0 };	         // ���淴����ɫ
	GLfloat mat_shininess[] = { 50.0 };							// ���淴�����
	GLfloat lmodel_ambient[] = { 1., 1., 1., 1.0 };		// ɢ����ɫ
	GLfloat lmodel_emmision[] = { 0.0, 0.0, 0.0, 1.0 };

	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, lmodel_ambient);
	glMaterialfv(GL_FRONT, GL_EMISSION, lmodel_emmision);
	glPushMatrix();

	GLUquadricObj* left1 = gluNewQuadric();
	gluQuadricDrawStyle(left1, GLU_FILL);
	gluQuadricTexture(left1, GL_TRUE);//�����������԰󶨲�ͬ�����������ͼ
	gluCylinder(left1, 0.5, 0.5, 2.0, 15, 5);
	glPopMatrix();
	glDisable(GL_TEXTURE_2D);
}

void conveyor::DrawConveyor2()
{
	//glEnable(GL_NORMALIZE);glScalef(0.5, 0.5, 0.5);
	//���ʹ�Բ��,��42
	glPushMatrix();
	glTranslatef(-4.5, 0, -1);
	Texture_Cylinder(21);
	Texture_Circle(20);
	glTranslatef(9, 0, 0);
	Texture_Cylinder(21);
	Texture_Circle(20);
	//ǰ��ҲҪ��������
	glTranslatef(0, 0, 2);
	Texture_Circle(20);
	glTranslatef(-9, 0, 0);
	Texture_Circle(20);
	glPopMatrix();

	//�м䲿�����ӵ�Ƥ��
	glPushMatrix();
	glTranslatef(0, 0.475, 0);
	glEnable(GL_NORMALIZE); glScalef(4.5, 0.05, 1);
	switch (count) {
	case 0: {Texture_cube(1, 25, 0, 0); break; }
	case 1: {Texture_cube(1, 24, 0, 0); break; }
	case 2: {Texture_cube(1, 23, 0, 0); break; }
	case 3: {Texture_cube(1, 22, 0, 0); break; }
	case 4: {Texture_cube(1, 21, 0, 0); break; }
	}
	glPopMatrix();
	glPushMatrix();
	glTranslatef(0, -0.475, 0);
	glEnable(GL_NORMALIZE); glScalef(4.5, 0.05, 1);
	switch (count) {
	case 0: {Texture_cube(1, 21, 0, 0); break; }
	case 1: {Texture_cube(1, 22, 0, 0); break; }
	case 2: {Texture_cube(1, 23, 0, 0); break; }
	case 3: {Texture_cube(1, 24, 0, 0); break; }
	case 4: {Texture_cube(1, 25, 0, 0); break; }
	}
	glPopMatrix();
}

void conveyor::draw()
{
	GLfloat mat_specular[] = { 1., 1., 1., 1.0 };	         // ���淴����ɫ
	GLfloat mat_shininess[] = { 50.0 };							// ���淴�����
	GLfloat lmodel_ambient[] = { 1., 1., 1., 1.0 };		// ɢ����ɫ
	GLfloat lmodel_emmision[] = { 0.0, 0.0, 0.0, 1.0 };

	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, lmodel_ambient);
	glMaterialfv(GL_FRONT, GL_EMISSION, lmodel_emmision);

	glPushMatrix();
	glEnable(GL_NORMALIZE); 
	glTranslatef(this->PositionX, this->PositionY, this->PositionZ);
	glTranslatef(0,0.2,0);//PositionYΪ0ʱ���ڵ�����
	glScalef(0.2, 0.2, 0.2);
	glRotatef(this->ConrotateX, 1, 0, 0);
	glRotatef(this->ConrotateY, 0, 1, 0);
	glRotatef(this->ConrotateZ, 0, 0, 1);
	DrawConveyor2();
	glPopMatrix();
}

//ģ�⴫�ʹ��˶�����һ����Ʒ���ڴ��ʹ�һ�ˣ�����t�������˶�����t���øú���
void conveyor::MoveShape() {

	this->move -= 0.03;
	this->MotionX = move;
}
