#include "Shape.h"
#include <stdlib.h>
#include <gl/glut.h>
#include <stdio.h>
#include <string.h>
#include <iostream>
using namespace std;
extern unsigned int texture[50];
void Texture_cube(int n, int i, int j, int k);

void Shape::transfer(double dx, double dy, double dz)
{
	this->globalX += dx;
	this->globalY += dy;
	this->globalZ += dz;
}

void Shape::rotate(double dx, double dy, double dz)
{
	this->rotateX += dx;
	this->rotateY += dy;
	this->rotateZ += dz;
}

void Shape::Scaling(float scale)
{
	if (scale <= 0) {
		cout << "scale negative!" << endl;
		return;
	}
	else {
		this->scale *= scale;
	}
}

void Shape::Draw()
{
	//this->Draw();
	cout << "Draw() of Shape class!" << endl;

}

/// <summary>
/// class Prism:��������
/// </summary>
/// <param name="globalX"></param>
/// <param name="globalY"></param>
/// <param name="globalZ"></param>
Prism::Prism(float globalX, float globalY, float globalZ)
{
	this->globalX = globalX;
	this->globalY = globalY;
	this->globalZ = globalZ;
	this->Texture = 1;
}
void Prism::Draw()
{	
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texture[this->Texture]);
	GLfloat mat_specular[] = { 1., 1., 1., 1.0 };	         // ���淴����ɫ
	GLfloat mat_shininess[] = { 50.0 };							// ���淴�����
	GLfloat lmodel_ambient[] = { 1., 1., 1., 1.0 };		// ɢ����ɫ
	GLfloat lmodel_emmision[] = { 0.0, 0.0, 0.0, 1.0 };

	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, lmodel_ambient);
	glMaterialfv(GL_FRONT, GL_EMISSION, lmodel_emmision);
	glPushMatrix();
	
	glEnable(GL_NORMALIZE); glScalef(0.2, 0.2, 0.2);
	glTranslatef(this->globalX, this->globalY, this->globalZ);

	static GLfloat vtx[12][3] =  //������������
	{
		//0-5�²㣬
		{-0.5f,0.0f,0.0f},//0
		{-0.25f,0.0f,static_cast<GLfloat>(sqrt(3.0f) / 4)},//1
		{-0.25f,0.0f,-static_cast<GLfloat>(sqrt(3.0f) / 4)},//2
		{0.25f,0.0f,static_cast<GLfloat>(sqrt(3.0f) / 4)},//3
		{0.25f,0.0f,-static_cast<GLfloat>(sqrt(3.0f) / 4)},//4
		{0.5f,0.0f,0.0f},//5
		{-0.5f,0.5f,0.0f},//6
		{-0.25f,0.5f,static_cast<GLfloat>(sqrt(3.0f) / 4)},//7
		{-0.25f,0.5f,-static_cast<GLfloat>(sqrt(3.0f) / 4)},//8
		{0.25f,0.5f,static_cast<GLfloat>(sqrt(3.0f) / 4)},//9
		{0.25f,0.5f,-static_cast<GLfloat>(sqrt(3.0f) / 4)},//10
		{0.5f,0.5f,0.0f},//11
	};
	//�������µ��棨��ʵ��Ҫ��������������У�����Ȼ�󻭾ͺ��ˣ�
	glBegin(GL_POLYGON);
	glNormal3f(0.0, 0.0, 1.0);
	glTexCoord2i(0.75, 1); glVertex3fv(vtx[2]);
	glTexCoord2i(1, 0.5); glVertex3fv(vtx[0]);
	glTexCoord2i(0.75, 0); glVertex3fv(vtx[1]);
	glTexCoord2i(0.25, 0); glVertex3fv(vtx[3]);
	glTexCoord2i(0, 0.5); glVertex3fv(vtx[5]);
	glTexCoord2i(0.25, 1); glVertex3fv(vtx[4]);
	glEnd();

	//�м�������
	glBegin(GL_QUADS);
	glNormal3f(0.0, 0.0, 1.0);
	glTexCoord2i(1, 1); glVertex3fv(vtx[10]);
	glTexCoord2i(1, 0); glVertex3fv(vtx[4]);
	glTexCoord2i(0, 0); glVertex3fv(vtx[8]);
	glTexCoord2i(0, 1); glVertex3fv(vtx[2]);

	glNormal3f(0.0, 0.0, 1.0);
	glTexCoord2i(1, 1); glVertex3fv(vtx[8]);
	glTexCoord2i(1, 0); glVertex3fv(vtx[2]);
	glTexCoord2i(0, 0); glVertex3fv(vtx[0]);
	glTexCoord2i(0, 1); glVertex3fv(vtx[6]);

	glNormal3f(0.0, 0.0, 1.0);
	glTexCoord2i(1, 1); glVertex3fv(vtx[11]);
	glTexCoord2i(1, 0); glVertex3fv(vtx[5]);
	glTexCoord2i(0, 0); glVertex3fv(vtx[4]);
	glTexCoord2i(0, 1); glVertex3fv(vtx[10]);

	glNormal3f(0.0, 0.0, 1.0);
	glTexCoord2i(1, 1); glVertex3fv(vtx[6]);
	glTexCoord2i(1, 0); glVertex3fv(vtx[0]);
	glTexCoord2i(0, 0); glVertex3fv(vtx[1]);
	glTexCoord2i(0, 1); glVertex3fv(vtx[7]);

	glNormal3f(0.0, 0.0, 1.0);
	glTexCoord2f(1.0, 1.0); glVertex3fv(vtx[7]);
	glTexCoord2f(1.0, 0.0); glVertex3fv(vtx[1]);
	glTexCoord2f(0.0, 0.0); glVertex3fv(vtx[3]);
	glTexCoord2f(0.0, 1.0); glVertex3fv(vtx[9]);

	glNormal3f(0.0, 0.0, 1.0);
	glTexCoord2i(1, 1); glVertex3fv(vtx[9]);
	glTexCoord2i(1, 0); glVertex3fv(vtx[3]);
	glTexCoord2i(0, 0); glVertex3fv(vtx[5]);
	glTexCoord2i(0, 1); glVertex3fv(vtx[11]);
	glEnd();

	//�������ϵ���
	glBegin(GL_POLYGON);
	glNormal3f(0.0, 0.0, 1.0);
	glTexCoord2i(0.75, 1); glVertex3fv(vtx[8]);
	glTexCoord2i(1, 0.5); glVertex3fv(vtx[6]);
	glTexCoord2i(0.75, 0); glVertex3fv(vtx[7]);
	glTexCoord2i(0.25, 0); glVertex3fv(vtx[9]);
	glTexCoord2i(0, 0.5); glVertex3fv(vtx[11]);
	glTexCoord2i(0.25, 1); glVertex3fv(vtx[10]);
	glEnd();
	
	//Texture_cube(1, this->Texture, 0, 0);
	glPopMatrix();
	glDisable(GL_TEXTURE_2D);
}


/// <summary>
/// class Trustum:����̨��
/// </summary>
/// <param name="globalX"></param>
/// <param name="globalY"></param>
/// <param name="globalZ"></param>
Trustum::Trustum(float globalX, float globalY, float globalZ)
{
	this->globalX = globalX;
	this->globalY = globalY;
	this->globalZ = globalZ;
	this->Texture = 1;
}
void Trustum::Draw()
{
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texture[this->Texture]);
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
	glScalef(0.2, 0.2, 0.2);//֮����û�����ŵ��������ԭ��
	glTranslatef(this->globalX, this->globalY, this->globalZ);

	static GLfloat vtx[12][3] =  //��̨��������
	{
		//0-5�²㣬6-11�ϲ�
		{-0.5f,0.0f,0.0f},//0
		{-0.25f,0.0f,static_cast<GLfloat>(sqrt(3.0f) / 4)},//1
		{-0.25f,0.0f,-static_cast<GLfloat>(sqrt(3.0f) / 4)},//2
		{0.25f,0.0f,static_cast<GLfloat>(sqrt(3.0f) / 4)},//3
		{0.25f,0.0f,-static_cast<GLfloat>(sqrt(3.0f) / 4)},//4
		{0.5f,0.0f,0.0f},//5
		{-0.25f,0.5f,0.0f},//6
		{-0.125f,0.5f,static_cast<GLfloat>(sqrt(3.0f) / 8)},//7
		{-0.125f,0.5f,-static_cast<GLfloat>(sqrt(3.0f) / 8)},//8
		{0.125f,0.5f,static_cast<GLfloat>(sqrt(3.0f) / 8)},//9
		{0.125f,0.5f,-static_cast<GLfloat>(sqrt(3.0f) / 8)},//10
		{0.25f,0.5f,0.0f},//11
	};
	//����̨�µ��棨��ʵ��Ҫ���������̨���У�����Ȼ�󻭾ͺ���:��
	glBegin(GL_POLYGON);
	glNormal3f(0.0, 0.0, 1.0);
	glTexCoord2i(0.75, 1); glVertex3fv(vtx[2]);
	glTexCoord2i(1, 0.5); glVertex3fv(vtx[0]);
	glTexCoord2i(0.75, 0); glVertex3fv(vtx[1]);
	glTexCoord2i(0.25, 0); glVertex3fv(vtx[3]);
	glTexCoord2i(0, 0.5); glVertex3fv(vtx[5]);
	glTexCoord2i(0.25, 1); glVertex3fv(vtx[4]);
	glEnd();

	//�м�������
	glBegin(GL_QUADS);
	glNormal3f(0.0, 0.0, 1.0);
	glTexCoord2i(1, 1); glVertex3fv(vtx[10]);
	glTexCoord2i(1, 0); glVertex3fv(vtx[4]);
	glTexCoord2i(0, 0); glVertex3fv(vtx[8]);
	glTexCoord2i(0, 1); glVertex3fv(vtx[2]);

	glNormal3f(0.0, 0.0, 1.0);
	glTexCoord2i(1, 1); glVertex3fv(vtx[8]);
	glTexCoord2i(1, 0); glVertex3fv(vtx[2]);
	glTexCoord2i(0, 0); glVertex3fv(vtx[0]);
	glTexCoord2i(0, 1); glVertex3fv(vtx[6]);

	glNormal3f(0.0, 0.0, 1.0);
	glTexCoord2i(1, 1); glVertex3fv(vtx[11]);
	glTexCoord2i(1, 0); glVertex3fv(vtx[5]);
	glTexCoord2i(0, 0); glVertex3fv(vtx[4]);
	glTexCoord2i(0, 1); glVertex3fv(vtx[10]);

	glNormal3f(0.0, 0.0, 1.0);
	glTexCoord2i(1, 1); glVertex3fv(vtx[6]);
	glTexCoord2i(1, 0); glVertex3fv(vtx[0]);
	glTexCoord2i(0, 0); glVertex3fv(vtx[1]);
	glTexCoord2i(0, 1); glVertex3fv(vtx[7]);

	glNormal3f(0.0, 0.0, 1.0);
	glTexCoord2f(1.0, 1.0); glVertex3fv(vtx[7]);
	glTexCoord2f(1.0, 0.0); glVertex3fv(vtx[1]);
	glTexCoord2f(0.0, 0.0); glVertex3fv(vtx[3]);
	glTexCoord2f(0.0, 1.0); glVertex3fv(vtx[9]);

	glNormal3f(0.0, 0.0, 1.0);
	glTexCoord2i(1, 1); glVertex3fv(vtx[9]);
	glTexCoord2i(1, 0); glVertex3fv(vtx[3]);
	glTexCoord2i(0, 0); glVertex3fv(vtx[5]);
	glTexCoord2i(0, 1); glVertex3fv(vtx[11]);
	glEnd();

	//�������ϵ���
	glBegin(GL_POLYGON);
	glNormal3f(0.0, 0.0, 1.0);
	glTexCoord2i(0.75, 1); glVertex3fv(vtx[8]);
	glTexCoord2i(1, 0.5); glVertex3fv(vtx[6]);
	glTexCoord2i(0.75, 0); glVertex3fv(vtx[7]);
	glTexCoord2i(0.25, 0); glVertex3fv(vtx[9]);
	glTexCoord2i(0, 0.5); glVertex3fv(vtx[11]);
	glTexCoord2i(0.25, 1); glVertex3fv(vtx[10]);
	glEnd();

	//Texture_cube(1, this->Texture, 0, 0);
	glPopMatrix();
	glDisable(GL_TEXTURE_2D);
}


/// <summary>
/// class Cube:��������
/// </summary>
/// <param name="globalX"></param>
/// <param name="globalY"></param>
/// <param name="globalZ"></param>
Cube::Cube(float globalX, float globalY, float globalZ)
{
	this->globalX = globalX;
	this->globalY = globalY;
	this->globalZ = globalZ;
	this->Texture = 1;
}
void Cube::Draw()//������
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
	
	glEnable(GL_NORMALIZE); glScalef(0.2, 0.2, 0.2);
	glTranslatef(this->globalX, this->globalY, this->globalZ);
	//glTranslatef(30, 2, 22);
	Texture_cube(1, this->Texture, 0, 0);
	glPopMatrix();
}

/// <summary>
/// class Cone:Բ׶��
/// </summary>
/// <param name="globalX"></param>
/// <param name="globalY"></param>
/// <param name="globalZ"></param>
Cone::Cone(float globalX, float globalY, float globalZ)
{
	this->globalX = globalX;
	this->globalY = globalY;
	this->globalZ = globalZ;
	this->Texture = 1;
}
void Cone::Draw()//Բ׶
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
	glEnable(GL_NORMALIZE); glScalef(0.2, 0.2, 0.2);
	glTranslatef(this->globalX, this->globalY, this->globalZ);
	//glTranslatef(30, 0.6, 27);
	glRotatef(-90, 1, 0, 0);
	Texture_Cone(this->Texture);
	glPopMatrix();
}

void Cone::Texture_Cone(int i)//Բ׶
{
	glEnable(GL_TEXTURE_2D);
	glEnable(GL_TEXTURE_GEN_S); //enable texture coordinate generation
	glEnable(GL_TEXTURE_GEN_T);

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
	glutSolidCone(1, 1.2, 15, 5);
	glPopMatrix();

	glDisable(GL_TEXTURE_GEN_S); //enable texture coordinate generation
	glDisable(GL_TEXTURE_GEN_T);

	glDisable(GL_TEXTURE_2D);
}

/// <summary>
/// class ConeCylinder:Բ̨��
/// </summary>
/// <param name="globalX"></param>
/// <param name="globalY"></param>
/// <param name="globalZ"></param>
ConeCylinder::ConeCylinder(float globalX, float globalY, float globalZ)
{
	this->globalX = globalX;
	this->globalY = globalY;
	this->globalZ = globalZ;
	this->Texture = 1;
}
void ConeCylinder::Draw()//Բ̨
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
	
	glEnable(GL_NORMALIZE); glScalef(0.2, 0.2, 0.2);
	glTranslatef(this->globalX, this->globalY, this->globalZ);
	//glTranslatef(27, 0.5, 27);////��Ӧ��������λ��
	glRotatef(-90, 1, 0, 0);
	Texture_ConeCylinder(this->Texture);
	glPopMatrix();
}

void ConeCylinder::Texture_ConeCylinder(int i)//Բ̨(�ѷ��)
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
	gluCylinder(left1, 1.0, 0.5, 1.0, 15, 5);
	Texture_Circle(i, 1);
	glTranslatef(0, 0, 1);
	Texture_Circle(i, 0.5);
	glPopMatrix();
	glDisable(GL_TEXTURE_2D);

}

void ConeCylinder::Texture_Circle(int i, float r)
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
	gluDisk(frontface, 0, r, 100, 2);
	glPopMatrix();
	glDisable(GL_TEXTURE_2D);
}

/// <summary>
/// class CylinderԲ����
/// </summary>
/// <param name="i"></param>
/// <param name="r"></param>
void Cylinder::Texture_Circle(int i, float r)
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
	gluDisk(frontface, 0, r, 100, 2);
	glPopMatrix();
	glDisable(GL_TEXTURE_2D);
}

Cylinder::Cylinder(float globalX, float globalY, float globalZ)
{
	this->globalX = globalX;
	this->globalY = globalY;
	this->globalZ = globalZ;
	this->Texture = 1;
}
void Cylinder::Draw()//Բ��
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
	
	glEnable(GL_NORMALIZE); glScalef(0.2, 0.2, 0.2);
	glTranslatef(this->globalX, this->globalY, this->globalZ);
	//glTranslatef(27, 1, 22);
	Texture_CylinderCircle(this->Texture);
	glPopMatrix();
}

void Cylinder::Texture_CylinderCircle(int i)//���˷�ڵ�Բ����,i������
{
	glPushMatrix();
	Texture_Cylinder(i);
	glTranslatef(0, 0, 2);
	Texture_Circle(i, 0.5);
	glTranslatef(0, 0, -2);
	Texture_Circle(i, 0.5);
	glPopMatrix();
}

void Cylinder::Texture_Cylinder(int i)
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
