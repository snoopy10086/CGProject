#include "Robot.h"

#include <iostream>
#include<cmath>
using namespace std;

extern unsigned int texture[50];

void Robot::Draw()
{
	cout << "Draw function that should never be called!" << endl;
}

//bool Robot::CollisionDetec(Shape* S)
//{
//	if (!this->enable)
//		return false;
//	float x1 = S->getGlobalX();
//	float y1 = S->getGlobalY();
//	float z1 = S->getGlobalZ();
//	float x2 = this->getGripperX();
//	float y2 = this->getGripperY();
//	float z2 = this->getGripperZ();
//	float distance = sqrt((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2) + (z1 - z2) * (z1 - z2));
//	if (distance < CollisionThreshold)
//		return true;
//	else
//		return false;
//}
void Robot::Draw_Claw(float angle)
{
	glPushMatrix();


	glPushMatrix();
	glTranslatef(1.4, 0, 0);
	glScalef(2.8, 0.5, 0.5);
#ifdef DEBUG
	glutWireCube(1);
#else
	glutSolidCube(1);
#endif
	glPopMatrix();

	glPushMatrix();
	glTranslatef(2.8, 0, 0);
#ifdef DEBUG
	glutWireSphere(0.35, 20, 20);
#else
	glutSolidSphere(0.35, 20, 20);
#endif
	glPopMatrix();

	glPushMatrix();
	glTranslatef(2.8, 0, 0);
	glRotatef(angle, 0, 0, 1);
	glTranslatef(0, -1.125, 0);

	glScalef(0.5, 2.25, 0.5);
#ifdef DEBUG
	glutWireCube(1);
#else
	glutSolidCube(1);
#endif
	glPopMatrix();

	glPopMatrix();
}
void Robot::Draw_Robot()
{
	glPushMatrix();

#ifdef DEBUG
	glutWireSphere(0.35, 20, 20);
#else
	glutSolidSphere(0.35, 20, 20);
#endif

	glPushMatrix();
	glRotatef(fCatch * 0.3 - 43.5, 0, 0, 1);
	this->Draw_Claw(fCatch);
	glPopMatrix();


	glPushMatrix();
	glRotatef(-fCatch * 0.3 + 223.5, 0, 0, 1);
	this->Draw_Claw(-fCatch + 180);
	glPopMatrix();

	glPushMatrix();
	glRotatef(90, 0, 1, 0);
	glRotatef(fCatch * 0.3 - 43.5, 0, 0, 1);
	this->Draw_Claw(fCatch);
	glPopMatrix();


	glPushMatrix();
	glRotatef(90, 0, 1, 0);
	glRotatef(-fCatch * 0.3 + 223.5, 0, 0, 1);
	this->Draw_Claw(-fCatch + 180);
	glPopMatrix();
	glPopMatrix();

}
void Robot::update()
{
	if (bCatch && fCatch > 0)
	{
		fCatch -= 0.05;

	}
	else if (!bCatch && fCatch < 45)
	{
		fCatch += 0.05;
	}
}
void Robot::not_catch()
{
	bCatch = !bCatch;
}

Robot_1::Robot_1(float PositionX, float PositionY, float PositionZ)
{
	this->GripperZ = PositionX;
	this->GripperY = PositionY;
	this->GripperZ = PositionZ;
}
void Robot_1::Draw()
{
	this->update();

	glPushMatrix();
	GLfloat mat_specular[] = { 1., 1., 1., 1.0 };	         // 镜面反射颜色
	GLfloat mat_shininess[] = { 50.0 };							// 镜面反射参数
	GLfloat lmodel_ambient[] = { 1., 1., 1., 1.0 };		// 散射颜色
	GLfloat lmodel_emmision[] = { 0.0, 0.0, 0.0, 1.0 };

	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, lmodel_ambient);
	glMaterialfv(GL_FRONT, GL_EMISSION, lmodel_emmision);
	glTranslatef(3, 2, 4);
	glEnable(GL_NORMALIZE); glScalef(0.2, 0.2, 0.2);
	glEnable(GL_NORMALIZE); glScalef(0.5, 0.5, 0.5);
	if (quad_obj == NULL)
		quad_obj = gluNewQuadric();
#ifdef DEBUG
	gluQuadricDrawStyle(quad_obj, GLU_LINE);
#else
	gluQuadricDrawStyle(quad_obj, GLU_FILL);
#endif
	gluQuadricNormals(quad_obj, GLU_SMOOTH);
	glPushMatrix();
	glTranslatef(GripperX,GripperY,GripperZ);

	glPushMatrix();
	glRotatef(90, 1, 0, 0);
	gluCylinder(quad_obj, 0.35, 0.35, length, 20, 20);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0, -length, 0);
	this->Draw_Robot();
	glPopMatrix();
	glPopMatrix();
	glPopMatrix();
	glPopMatrix();
}
void Robot_1::update()
{
	Robot::update();
}
void Robot_1::len_inc()
{
	length += 0.05;
}
void Robot_1::len_dec()
{
	length -= 0.05;
}

//绘制机械臂
//处理旋转的函数
Robot_2::Robot_2(float PositionX, float PositionY, float PositionZ)
{
	this->PositionX = PositionX;
	this->PositionY = PositionY+0.1;
	this->PositionZ = PositionZ;
}

void Robot_2::HandleRotate()
{
	if (Robot_2::Isrotate)
	{
		rotate1 += 0.4;
	}
	if (Robot_2::Isrotate)
	{
		if (forward2) {
			rotate2 += 0.1;
			if (rotate2 > 45) {
				rotate2 = 45;
				forward2 = !forward2;
			}
		}
		else {
			rotate2 -= 0.1;
			if (rotate2 < 0) {
				rotate2 = 0;
				forward2 = !forward2;
			}
		}
	}
	if (Isrotate)
	{
		if (forward3) {
			rotate3 += 0.1;
			if (rotate3 > 45) {
				rotate3 = 45;
				forward3 = !forward3;
			}
		}
		else {
			rotate3 -= 0.1;
			if (rotate3 < 0) {
				rotate3 = 0;
				forward3 = !forward3;
			}
		}
	}
}
//绘制杆
void Robot_2::DrawRod(GLdouble baseR, GLdouble topR, GLdouble h)
{
	GLfloat lmodel_emmision[] = { 0.0, 0.0, 0.0, 1.0 };
	glMaterialfv(GL_FRONT, GL_EMISSION, lmodel_emmision);
	glEnable(GL_TEXTURE_2D);

	glBindTexture(GL_TEXTURE_2D, texture[14]);  //选择纹理texture[1]
	glPushMatrix();
	glTranslatef(0, 0, h);
	GLUquadricObj* upface = gluNewQuadric();
	gluQuadricTexture(upface, true);
	gluQuadricDrawStyle(upface, GLU_FILL);
	gluDisk(upface, 0, topR, 100, 2);
	glPopMatrix();
	glPushMatrix();
	GLUquadricObj* diface = gluNewQuadric();
	gluQuadricTexture(diface, true);
	gluQuadricDrawStyle(diface, GLU_FILL);
	gluDisk(diface, 0, baseR, 100, 2);

	GLUquadricObj* ceface = gluNewQuadric();
	gluQuadricTexture(ceface, true);
	gluQuadricDrawStyle(ceface, GLU_FILL);
	gluCylinder(ceface, baseR, topR, h, 100, 2);

	glPopMatrix();
	glDisable(GL_TEXTURE_2D);	//关闭纹理texture[1]

}
//绘制关节
void Robot_2::DrawJoint()
{
	glPushMatrix();
	glRotatef(90, 0, 0, 1);
	glRotatef(90, 0, 1, 0);
	glScalef(0.9, 0.9, 0.4);
	DrawRod(0.4, 0.4, 1.2);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-0.36, 0.6, 0);
	glRotatef(90, 0, 1, 0);
	DrawRod(0.4, 0.4, 0.72);
	glPopMatrix();

}
//绘制主体
void Robot_2::Draw()
{	
	GLfloat mat_specular[] = { 1., 1., 1., 1.0 };	         // 镜面反射颜色
	GLfloat mat_shininess[] = { 50.0 };							// 镜面反射参数
	GLfloat lmodel_ambient[] = { 1., 1., 1., 1.0 };		// 散射颜色
	GLfloat lmodel_emmision[] = { 0.0, 0.0, 0.0, 1.0 };

	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, lmodel_ambient);
	glMaterialfv(GL_FRONT, GL_EMISSION, lmodel_emmision);
	this->HandleRotate();
	glPushMatrix();
	glTranslatef(PositionX, PositionY, PositionZ);
	glEnable(GL_NORMALIZE); glScalef(0.2f, 0.2f, 0.2f);
	glPushMatrix();
	glRotatef(rotate1, 0, 1, 0);
	glPushMatrix();
	glTranslatef(0, 1.2, 0);
	glRotatef(rotate2, 1, 0, 0);
	glTranslatef(0, -1.2, 0);
	glPushMatrix();
	glTranslatef(0, 3.8, 0);
	glRotatef(-rotate3, 1, 0, 0);
	glTranslatef(0, -3.8, 0);
	//机械臂1
	glPushMatrix();
	glTranslatef(0, 4.2, 0.4);
	DrawRod(0.2, 0.2, 2);
	glPopMatrix();
	glPopMatrix();
	//关节2
	glPushMatrix();
	glTranslatef(0, 3.6, 0);
	DrawJoint();
	glPopMatrix();

	//机械臂1
	glPushMatrix();
	glTranslatef(0, 1.6, 0);
	glRotatef(90, 0, 0, 1);
	glRotatef(90, 0, 1, 0);
	DrawRod(0.2, 0.2, 2);
	glPopMatrix();
	glPopMatrix();

	//关节1
	glPushMatrix();
	glTranslatef(0, 0.6, 0);
	DrawJoint();
	glPopMatrix();
	glPopMatrix();

	//底座
	glPushMatrix();
	glRotatef(90, 0, 0, 1);
	glRotatef(90, 0, 1, 0);
	DrawRod(0.7, 0.5, 0.6);
	glPopMatrix();
	glPopMatrix();
}
void Robot_2::setPositionX(float position) {
	this->PositionX = position;
}
void Robot_2::setPositionY(float position) {
	this->PositionY = position;
}
void Robot_2::setPositionZ(float position) {
	this->PositionZ = position;
}
