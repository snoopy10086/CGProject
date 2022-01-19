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
/// class Prism:六棱柱类
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
	GLfloat mat_specular[] = { 1., 1., 1., 1.0 };	         // 镜面反射颜色
	GLfloat mat_shininess[] = { 50.0 };							// 镜面反射参数
	GLfloat lmodel_ambient[] = { 1., 1., 1., 1.0 };		// 散射颜色
	GLfloat lmodel_emmision[] = { 0.0, 0.0, 0.0, 1.0 };

	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, lmodel_ambient);
	glMaterialfv(GL_FRONT, GL_EMISSION, lmodel_emmision);
	glPushMatrix();
	
	glEnable(GL_NORMALIZE); 
	glTranslatef(this->globalX, this->globalY, this->globalZ);

	glScalef(0.2, 0.2, 0.2);//这是为了默认画出来的shape大小不要太夸张
	glScalef(this->scaleX, this->scaleY, this->scaleZ);
	glRotatef(this->rotateX, 1, 0, 0);
	glRotatef(this->rotateY, 0, 1, 0);
	glRotatef(this->rotateZ, 0, 0, 1);
	static GLfloat vtx[12][3] =  //棱柱顶点坐标
	{
		//0-5下层，
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
	//六棱柱下底面（其实想要多少面的棱柱都行，算数然后画就好了）
	glBegin(GL_POLYGON);
	glNormal3f(0.0, 0.0, 1.0);
	glTexCoord2i(0.75, 1); glVertex3fv(vtx[2]);
	glTexCoord2i(1, 0.5); glVertex3fv(vtx[0]);
	glTexCoord2i(0.75, 0); glVertex3fv(vtx[1]);
	glTexCoord2i(0.25, 0); glVertex3fv(vtx[3]);
	glTexCoord2i(0, 0.5); glVertex3fv(vtx[5]);
	glTexCoord2i(0.25, 1); glVertex3fv(vtx[4]);
	glEnd();

	//中间六个面
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

	//六棱柱上底面
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
/// class Trustum:六棱台类
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
	GLfloat mat_specular[] = { 1., 1., 1., 1.0 };	         // 镜面反射颜色
	GLfloat mat_shininess[] = { 50.0 };							// 镜面反射参数
	GLfloat lmodel_ambient[] = { 1., 1., 1., 1.0 };		// 散射颜色
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

	static GLfloat vtx[12][3] =  //棱台顶点坐标
	{
		//0-5下层，6-11上层
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
	//六棱台下底面（其实想要多少面的棱台都行，算数然后画就好了:）
	glBegin(GL_POLYGON);
	glNormal3f(0.0, 0.0, 1.0);
	glTexCoord2i(0.75, 1); glVertex3fv(vtx[2]);
	glTexCoord2i(1, 0.5); glVertex3fv(vtx[0]);
	glTexCoord2i(0.75, 0); glVertex3fv(vtx[1]);
	glTexCoord2i(0.25, 0); glVertex3fv(vtx[3]);
	glTexCoord2i(0, 0.5); glVertex3fv(vtx[5]);
	glTexCoord2i(0.25, 1); glVertex3fv(vtx[4]);
	glEnd();

	//中间六个面
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

	//六棱柱上底面
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
	glEnable(GL_NORMALIZE);	
	glTranslatef(this->globalX, this->globalY, this->globalZ);
	glTranslatef(0, 0.2 * this->scaleY, 0);//为了默认时能画在地板上
	glScalef(0.2, 0.2, 0.2);
	glScalef(this->scaleX, this->scaleY, this->scaleZ);
	glRotatef(this->rotateX, 1, 0, 0);
	glRotatef(this->rotateY, 0, 1, 0);
	glRotatef(this->rotateZ, 0, 0, 1);
	
	Texture_cube(1, this->Texture, 0, 0);//该函数画出来的是一个原点在中心，长宽高为2的立方体
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
	glEnable(GL_NORMALIZE); 
	glTranslatef(this->globalX, this->globalY, this->globalZ);

	glScalef(0.2, 0.2, 0.2);
	glScalef(this->scaleX, this->scaleY, this->scaleZ);
	glRotatef(this->rotateX, 1, 0, 0);
	glRotatef(this->rotateY, 0, 1, 0);
	glRotatef(this->rotateZ, 0, 0, 1);
	glRotatef(-90, 1, 0, 0);//为了不设置rotateXYZ的时候是尖尖朝上的
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
	this->Texture = 34;
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
	this->Texture2 = 1;
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

void Cylinder::Texture_CylinderCircle(int i,int j)//两端封口的圆柱体,i纹理编号
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
YueBingPi::YueBingPi(float globalX, float globalY, float globalZ) :Cylinder(globalX, globalY, globalZ) {
	this->Texture = 41;
	this->Texture2 = 41;
	this->scaling(0.8, 0.03, 0.8);
}

YueBing::YueBing(float globalX, float globalY, float globalZ) :Cylinder(globalX, globalY, globalZ) {
	this->Texture = 35 + 3;
	this->Texture2 = 35;
	this->scaling(0.6, 0.125, 0.6);
	SetType(0);
}
YueBing::YueBing(float globalX, float globalY, float globalZ,int Type) :Cylinder(globalX, globalY, globalZ){
	this->Texture = 35 + Type + 3;
	this->Texture2 = 35 + Type;
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
	this->Type = 0;//三种口味，分别是豆沙抹茶蓝莓？什么鬼畜月饼（x
	this->scaling(0.12, 0.1, 0.1);
}
Sphere::Sphere(float globalX, float globalY, float globalZ,int Type)
{
	this->globalX = globalX;
	this->globalY = globalY;
	this->globalZ = globalZ;
	this->Type = Type;
	this->scaling(0.12, 0.1, 0.1);
	this->rotate(15, 15, 15);
}
void Sphere::Draw()//球
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

void Sphere::Texture_Sphere(int i)//决定球的颜色
{
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texture[35]);  //选择纹理texture[1]
	GLfloat mat_specular[] = { .5, .5, .5, .5 };	         // 镜面反射颜色
	GLfloat mat_shininess[] = { 100.0 };							// 镜面反射参数
	GLfloat lmodel_ambient[] = { .5, .5, .5, .5 };		// 散射颜色
	GLfloat lmodel_emmision[] = { 0.0, 0.0, 0.0, 0.0 };
	mat_specular[this->Type] += 0.5;
	lmodel_ambient[this->Type] += 0.5;
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, lmodel_ambient);
	glMaterialfv(GL_FRONT, GL_EMISSION, lmodel_emmision);
	glPushMatrix();

	GLUquadricObj* left1 = gluNewQuadric();
	gluQuadricDrawStyle(left1, GLU_FILL);
	gluQuadricTexture(left1, GL_TRUE);//启用纹理，可以绑定不同的纹理进行贴图
	glutSolidSphere(1,100,100);
	glPopMatrix();
	glDisable(GL_TEXTURE_2D);
}