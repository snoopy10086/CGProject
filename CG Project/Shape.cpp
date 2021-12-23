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

Prism::Prism(float globalX, float globalY, float globalZ)
{
	this->globalX = globalX;
	this->globalY = globalY;
	this->globalZ = globalZ;
	this->Texture = 1;
}
void Prism::Draw()
{
	GLfloat mat_specular[] = { 1., 1., 1., 1.0 };	         // 镜面反射颜色
	GLfloat mat_shininess[] = { 50.0 };							// 镜面反射参数
	GLfloat lmodel_ambient[] = { 1., 1., 1., 1.0 };		// 散射颜色
	GLfloat lmodel_emmision[] = { 0.0, 0.0, 0.0, 1.0 };

	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, lmodel_ambient);
	glMaterialfv(GL_FRONT, GL_EMISSION, lmodel_emmision);
	glPushMatrix();
	
	glEnable(GL_NORMALIZE); glScalef(0.2, 0.2, 0.2);
	glTranslatef(this->globalX, this->globalY, this->globalZ);


	
	//Texture_cube(1, this->Texture, 0, 0);
	glPopMatrix();
}


/// <summary>
/// class Cube:立方体类
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
void Cube::Draw()//立方体
{
	GLfloat mat_specular[] = { 1., 1., 1., 1.0 };	         // 镜面反射颜色
	GLfloat mat_shininess[] = { 50.0 };							// 镜面反射参数
	GLfloat lmodel_ambient[] = { 1., 1., 1., 1.0 };		// 散射颜色
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
/// class Cone:圆锥类
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
void Cone::Draw()//圆锥
{
	GLfloat mat_specular[] = { 1., 1., 1., 1.0 };	         // 镜面反射颜色
	GLfloat mat_shininess[] = { 50.0 };							// 镜面反射参数
	GLfloat lmodel_ambient[] = { 1., 1., 1., 1.0 };		// 散射颜色
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

void Cone::Texture_Cone(int i)//圆锥
{
	glEnable(GL_TEXTURE_2D);
	glEnable(GL_TEXTURE_GEN_S); //enable texture coordinate generation
	glEnable(GL_TEXTURE_GEN_T);

	glBindTexture(GL_TEXTURE_2D, texture[i]);  //选择纹理texture[1]
	GLfloat mat_specular[] = { 1., 1., 1., 1.0 };	         // 镜面反射颜色
	GLfloat mat_shininess[] = { 50.0 };							// 镜面反射参数
	GLfloat lmodel_ambient[] = { 1., 1., 1., 1.0 };		// 散射颜色
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
/// class ConeCylinder:圆台类
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
void ConeCylinder::Draw()//圆台
{
	GLfloat mat_specular[] = { 1., 1., 1., 1.0 };	         // 镜面反射颜色
	GLfloat mat_shininess[] = { 50.0 };							// 镜面反射参数
	GLfloat lmodel_ambient[] = { 1., 1., 1., 1.0 };		// 散射颜色
	GLfloat lmodel_emmision[] = { 0.0, 0.0, 0.0, 1.0 };

	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, lmodel_ambient);
	glMaterialfv(GL_FRONT, GL_EMISSION, lmodel_emmision);
	glPushMatrix();
	
	glEnable(GL_NORMALIZE); glScalef(0.2, 0.2, 0.2);
	glTranslatef(this->globalX, this->globalY, this->globalZ);
	//glTranslatef(27, 0.5, 27);////不应该在这里位移
	glRotatef(-90, 1, 0, 0);
	Texture_ConeCylinder(this->Texture);
	glPopMatrix();
}

void ConeCylinder::Texture_ConeCylinder(int i)//圆台(已封底)
{
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texture[i]);  //选择纹理texture[1]
	GLfloat mat_specular[] = { 1., 1., 1., 1.0 };	         // 镜面反射颜色
	GLfloat mat_shininess[] = { 50.0 };							// 镜面反射参数
	GLfloat lmodel_ambient[] = { 1., 1., 1., 1.0 };		// 散射颜色
	GLfloat lmodel_emmision[] = { 0.0, 0.0, 0.0, 1.0 };

	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, lmodel_ambient);
	glMaterialfv(GL_FRONT, GL_EMISSION, lmodel_emmision);
	glPushMatrix();

	GLUquadricObj* left1 = gluNewQuadric();
	gluQuadricDrawStyle(left1, GLU_FILL);
	gluQuadricTexture(left1, GL_TRUE);//启用纹理，可以绑定不同的纹理进行贴图
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
	glBindTexture(GL_TEXTURE_2D, texture[i]);  //选择纹理texture[1]
	GLfloat mat_specular[] = { 1., 1., 1., 1.0 };	         // 镜面反射颜色
	GLfloat mat_shininess[] = { 50.0 };							// 镜面反射参数
	GLfloat lmodel_ambient[] = { 1., 1., 1., 1.0 };		// 散射颜色
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
/// class Cylinder圆柱类
/// </summary>
/// <param name="i"></param>
/// <param name="r"></param>
void Cylinder::Texture_Circle(int i, float r)
{
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texture[i]);  //选择纹理texture[1]
	GLfloat mat_specular[] = { 1., 1., 1., 1.0 };	         // 镜面反射颜色
	GLfloat mat_shininess[] = { 50.0 };							// 镜面反射参数
	GLfloat lmodel_ambient[] = { 1., 1., 1., 1.0 };		// 散射颜色
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
void Cylinder::Draw()//圆柱
{
	GLfloat mat_specular[] = { 1., 1., 1., 1.0 };	         // 镜面反射颜色
	GLfloat mat_shininess[] = { 50.0 };							// 镜面反射参数
	GLfloat lmodel_ambient[] = { 1., 1., 1., 1.0 };		// 散射颜色
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

void Cylinder::Texture_CylinderCircle(int i)//两端封口的圆柱体,i纹理编号
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
	glBindTexture(GL_TEXTURE_2D, texture[i]);  //选择纹理texture[1]
	GLfloat mat_specular[] = { 1., 1., 1., 1.0 };	         // 镜面反射颜色
	GLfloat mat_shininess[] = { 50.0 };							// 镜面反射参数
	GLfloat lmodel_ambient[] = { 1., 1., 1., 1.0 };		// 散射颜色
	GLfloat lmodel_emmision[] = { 0.0, 0.0, 0.0, 1.0 };

	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, lmodel_ambient);
	glMaterialfv(GL_FRONT, GL_EMISSION, lmodel_emmision);
	glPushMatrix();

	GLUquadricObj* left1 = gluNewQuadric();
	gluQuadricDrawStyle(left1, GLU_FILL);
	gluQuadricTexture(left1, GL_TRUE);//启用纹理，可以绑定不同的纹理进行贴图
	gluCylinder(left1, 0.5, 0.5, 2.0, 15, 5);
	glPopMatrix();
	glDisable(GL_TEXTURE_2D);
}
