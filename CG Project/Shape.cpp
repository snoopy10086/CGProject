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
	//cout << "rx" << this->rotateX << endl;
	this->rotateX += dx;
	this->rotateY += dy;
	this->rotateZ += dz;
	
	//cout << "rotate" << endl;
}

void Shape::scaling(float scaleX, float scaleY, float scaleZ)
{
	if (scaleX <= 0|| scaleY <= 0|| scaleZ <= 0) {
		cout << "scale negative!" << endl;
		return;
	}
	else {
		this->scaleX *= scaleX;
		this->scaleY *= scaleY;
		this->scaleZ *= scaleZ;
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
	this->Texture = 33;
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
	
	glEnable(GL_NORMALIZE); 
	glTranslatef(this->globalX, this->globalY, this->globalZ);

	glScalef(0.2, 0.2, 0.2);//����Ϊ��Ĭ�ϻ�������shape��С��Ҫ̫����
	glScalef(this->scaleX, this->scaleY, this->scaleZ);
	glRotatef(this->rotateX, 1, 0, 0);
	glRotatef(this->rotateY, 0, 1, 0);
	glRotatef(this->rotateZ, 0, 0, 1);
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
	glTranslatef(this->globalX, this->globalY, this->globalZ);

	glScalef(0.2, 0.2, 0.2);
	glScalef(this->scaleX, this->scaleY, this->scaleZ);
	glRotatef(this->rotateX, 1, 0, 0);
	glRotatef(this->rotateY, 0, 1, 0);
	glRotatef(this->rotateZ, 0, 0, 1);
	//glScalef(0.2, 0.2, 0.2);

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
	glEnable(GL_NORMALIZE);	
	glTranslatef(this->globalX, this->globalY, this->globalZ);
	glTranslatef(0, 0.2 * this->scaleY, 0);//Ϊ��Ĭ��ʱ�ܻ��ڵذ���
	glScalef(0.2, 0.2, 0.2);
	glScalef(this->scaleX, this->scaleY, this->scaleZ);
	glRotatef(this->rotateX, 1, 0, 0);
	glRotatef(this->rotateY, 0, 1, 0);
	glRotatef(this->rotateZ, 0, 0, 1);
	
	Texture_cube(1, this->Texture, 0, 0);//�ú�������������һ��ԭ�������ģ������Ϊ2��������
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
	glEnable(GL_NORMALIZE); 
	glTranslatef(this->globalX, this->globalY, this->globalZ);

	glScalef(0.2, 0.2, 0.2);
	glScalef(this->scaleX, this->scaleY, this->scaleZ);
	glRotatef(this->rotateX, 1, 0, 0);
	glRotatef(this->rotateY, 0, 1, 0);
	glRotatef(this->rotateZ, 0, 0, 1);
	glRotatef(-90, 1, 0, 0);//Ϊ�˲�����rotateXYZ��ʱ���Ǽ�⳯�ϵ�
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
	this->Texture = 34;
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
	
	glEnable(GL_NORMALIZE); 
	glTranslatef(this->globalX, this->globalY, this->globalZ);

	glScalef(0.2, 0.2, 0.2);
	glScalef(this->scaleX, this->scaleY, this->scaleZ);
	glRotatef(this->rotateX, 1, 0, 0);
	glRotatef(this->rotateY, 0, 1, 0);
	glRotatef(this->rotateZ, 0, 0, 1);
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
	this->Texture2 = 1;
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
	
	glEnable(GL_NORMALIZE); 
	glTranslatef(this->globalX, this->globalY, this->globalZ);

	glScalef(this->scaleX, this->scaleY, this->scaleZ);
	glScalef(0.2, 0.2, 0.2);
	glRotatef(this->rotateX, 1, 0, 0);
	glRotatef(this->rotateY, 0, 1, 0);
	glRotatef(this->rotateZ, 0, 0, 1);
	glRotatef(-90, 1, 0, 0);
	Texture_CylinderCircle(this->Texture, this->Texture2);
	glPopMatrix();
}

void Cylinder::Texture_CylinderCircle(int i,int j)//���˷�ڵ�Բ����,i������
{
	glPushMatrix();
	Texture_Cylinder(i);
	glTranslatef(0, 0, 2);
	Texture_Circle(j, 0.5);
	glTranslatef(0, 0, -2);
	Texture_Circle(j, 0.5);
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
YueBingPi::YueBingPi(float globalX, float globalY, float globalZ) :Cylinder(globalX, globalY, globalZ) {
	this->Texture = 41;
	this->Texture2 = 41;
	this->scaling(0.8, 0.03, 0.8);
	this->Type = -2;// �±�Ƥ
}

YueBing::YueBing(float globalX, float globalY, float globalZ) :Cylinder(globalX, globalY, globalZ) {
	this->Texture = 35 + 3;
	this->Texture2 = 35;
	this->scaling(0.6, 0.125, 0.6);
	SetType(0);
}
YueBing::YueBing(float globalX, float globalY, float globalZ,int Type) :Cylinder(globalX, globalY, globalZ){
	this->Texture = 35 + Type - 10 + 3;
	this->Texture2 = 35 + Type - 10;
	this->scaling(0.6, 0.125, 0.6);
	SetType(Type);
}
void YueBing::SetType(int t) {
	this->Type = t;
}

Sphere::Sphere(float globalX, float globalY, float globalZ)
{
	this->globalX = globalX;
	this->globalY = globalY;
	this->globalZ = globalZ;
	this->Type = 0;
	this->scaling(0.1, 0.1, 0.15);
	this->rotate(0, 15, 15);
}
Sphere::Sphere(float globalX, float globalY, float globalZ,int Type)
{
	this->globalX = globalX;
	this->globalY = globalY;
	this->globalZ = globalZ;
	this->Type = Type;
	this->scaling(0.1, 0.1, 0.15);
	this->rotate(0, 15, 15);
}
void Sphere::Draw()//��
{
	glPushMatrix();
	glEnable(GL_NORMALIZE);
	glTranslatef(this->globalX, this->globalY, this->globalZ);
	glScalef(this->scaleX, this->scaleY, this->scaleZ);
	glScalef(0.2, 0.2, 0.2);
	glTranslatef(0, 0.5, 0);
	glRotatef(this->rotateX, 1, 0, 0);
	glRotatef(this->rotateY, 0, 1, 0);
	glRotatef(this->rotateZ, 0, 0, 1);
	Texture_Sphere(this->Type);
	glPopMatrix();
}

void Sphere::Texture_Sphere(int i)//���������ɫ
{
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texture[42+i]);  //ѡ������texture[1]
	GLfloat mat_specular[] = { 1., 1., 1., 1.0 };	         // ���淴����ɫ
	GLfloat mat_shininess[] = { 50.0 };							// ���淴�����
	GLfloat lmodel_ambient[] = { 1., 1., 1., 1.0 };		// ɢ����ɫ
	GLfloat lmodel_emmision[] = { 0.0, 0.0, 0.0, 1.0 };
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, lmodel_ambient);
	glMaterialfv(GL_FRONT, GL_EMISSION, lmodel_emmision);
	glPushMatrix();
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_TEXTURE_2D);

	GLUquadricObj* sphere = gluNewQuadric();
	gluQuadricNormals(sphere, GLU_SMOOTH);
	gluQuadricDrawStyle(sphere, GLU_FILL);
	gluQuadricTexture(sphere, GL_TRUE);
	gluSphere(sphere, 1.0, 50, 50);
	glPopMatrix();
	glDisable(GL_TEXTURE_2D);
}


LiWuHePingMian::LiWuHePingMian(float globalX, float globalY, float globalZ):Cube(globalX, globalY, globalZ)
{
	this->Type = 3;//3 or 4
	this->Texture = 42 + this->Type;
	this->scaling(0.3, 0.02, 0.3);
}
LiWuHePingMian::LiWuHePingMian(float globalX, float globalY, float globalZ, int Type) : Cube(globalX, globalY, globalZ)
{
	this->Type = Type;
	this->Texture = 42 + this->Type;
	this->scaling(0.3, 0.02, 0.3);
}

void LiWuHePingMian::Draw()//�����ƽ��
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
	glTranslatef(this->globalX, this->globalY, this->globalZ);
	glTranslatef(0, 0.2 * this->scaleY, 0);//Ϊ��Ĭ��ʱ�ܻ��ڵذ���
	glScalef(0.2, 0.2, 0.2);
	glScalef(this->scaleX, this->scaleY, this->scaleZ);
	glRotatef(this->rotateX, 1, 0, 0);
	glRotatef(this->rotateY, 0, 1, 0);
	glRotatef(this->rotateZ, 0, 0, 1);
	Texture_cube(1, this->Texture, 0, 0);//�ú�������������һ��ԭ�������ģ������Ϊ2��������
	glTranslatef(1.5, 0, 0);
	glScalef(0.5, 1, 1);
	Texture_cube(1, this->Texture, 0, 0);//�ú�������������һ��ԭ�������ģ������Ϊ2��������
	glTranslatef(-6, 0, 0);
	Texture_cube(1, this->Texture, 0, 0);//�ú�������������һ��ԭ�������ģ������Ϊ2��������
	glTranslatef(3, 0, 1.5);
	glScalef(2, 1, 0.5);
	Texture_cube(1, this->Texture, 0, 0);//�ú�������������һ��ԭ�������ģ������Ϊ2��������
	glTranslatef(0, 0, -6);
	Texture_cube(1, this->Texture, 0, 0);//�ú�������������һ��ԭ�������ģ������Ϊ2��������
	glScalef(1, 1, 2);
	glTranslatef(3, 0, 1.5);
	Texture_cube(1, this->Texture, 0, 0);//�ú�������������һ��ԭ�������ģ������Ϊ2��������
	glPopMatrix();
}


LiWuHe::LiWuHe(float globalX, float globalY, float globalZ) :Cube(globalX, globalY, globalZ)
{
	this->Type = 23;//23 or 24
	this->Texture = 44 + this->Type - 20;
	this->scaling(0.3, 0.3, 0.3);
}
LiWuHe::LiWuHe(float globalX, float globalY, float globalZ, int Type) : Cube(globalX, globalY, globalZ)
{
	this->Type = Type;
	this->Texture = 44 + this->Type - 20;
	this->scaling(0.3, 0.3, 0.3);
}

void LiWuHe::Draw()//�����
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
	glTranslatef(this->globalX, this->globalY, this->globalZ);
	glTranslatef(0, 0.2 * this->scaleY, 0);//Ϊ��Ĭ��ʱ�ܻ��ڵذ���
	glScalef(0.2, 0.2, 0.2);
	glScalef(this->scaleX, this->scaleY, this->scaleZ);
	glRotatef(this->rotateX, 1, 0, 0);
	glRotatef(this->rotateY, 0, 1, 0);
	glRotatef(this->rotateZ, 0, 0, 1);
	texture_LiWuHe(this->Texture);//�ú�������������һ��ԭ�������ģ������Ϊ2��������
	glTranslatef(0, 1, 0);
	glScalef(1.2, 0.4, 1.2);
	texture_LiWuHe(this->Texture);//�ú�������������һ��ԭ�������ģ������Ϊ2��������
	glTranslatef(0, 1.02, 0);
	glScalef(1, 0.02, 1);
	texture_LiWuHe(this->Texture + 2);//�ú�������������һ��ԭ�������ģ������Ϊ2��������
	glPopMatrix();
}


void LiWuHe::texture_LiWuHe(int i)
{
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texture[i]);  //ѡ������texture[1]
	glPushMatrix();

	glBegin(GL_QUADS);
	glNormal3f(0.0, 0.0, 1.0);
	glTexCoord2i(1, 1); glVertex3i(-1, 1, 1);
	glTexCoord2i(1, 0); glVertex3i(-1, -1, 1);
	glTexCoord2i(0, 0); glVertex3i(1, -1, 1);
	glTexCoord2i(0, 1); glVertex3i(1, 1, 1);

	glNormal3f(0.0, 0.0, -1.0);
	glTexCoord2i(1, 1); glVertex3i(-1, 1, -1);
	glTexCoord2i(1, 0); glVertex3i(-1, -1, -1);
	glTexCoord2i(0, 0); glVertex3i(1, -1, -1);
	glTexCoord2i(0, 1); glVertex3i(1, 1, -1);

	glNormal3f(1.0, 0.0, 0.0);
	glTexCoord2i(0, 1); glVertex3i(1, -1, 1);
	glTexCoord2i(1, 1); glVertex3i(1, -1, -1);
	glTexCoord2i(1, 0); glVertex3i(1, 1, -1);
	glTexCoord2i(0, 0); glVertex3i(1, 1, 1);

	glNormal3f(-1.0, 0.0, 0.0);
	glTexCoord2i(0, 1); glVertex3i(-1, -1, 1);
	glTexCoord2i(1, 1); glVertex3i(-1, -1, -1);
	glTexCoord2i(1, 0); glVertex3i(-1, 1, -1);
	glTexCoord2i(0, 0); glVertex3i(-1, 1, 1);

	glNormal3f(0.0, 1.0, 0.0);
	glTexCoord2i(1, 1); glVertex3i(-1, 1, 1);
	glTexCoord2i(1, 0); glVertex3i(-1, 1, -1);
	glTexCoord2i(0, 0); glVertex3i(1, 1, -1);
	glTexCoord2i(0, 1); glVertex3i(1, 1, 1);

	glNormal3f(0.0, -1.0, 0.0);
	glTexCoord2i(1, 1); glVertex3i(-1, -1, 1);
	glTexCoord2i(1, 0); glVertex3i(-1, -1, -1);
	glTexCoord2i(0, 0); glVertex3i(1, -1, -1);
	glTexCoord2i(0, 1); glVertex3i(1, -1, 1);

	glEnd();
	glPopMatrix();

	glDisable(GL_TEXTURE_2D);	//�ر�����texture[1]
}
