#include "Robot.h"
#include <iostream>
#include<cmath>
using namespace std;

extern unsigned int texture[50];
extern vector<Shape*> Shapes;						//collections of shapes
#define PI 3.1415926535
static float c = PI / 180.0;    //弧度和角度转换参数
void Robot::Draw()
{
	cout << "Draw function that should never be called!" << endl;
}

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
	glTranslatef(3 + GripperX, 2 + GripperY, 4 + GripperZ);
	glEnable(GL_NORMALIZE); glScalef(0.1, 0.1, 0.1);

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
	//this->TheShape->globalX = this->BindPositionX;
	//this->TheShape->globalY = this->BindPositionY;
	//this->TheShape->globalZ = this->BindPositionZ;
	GLfloat r1_0 = 90;
	GLfloat r2_0 = 0;
	GLfloat r3_0 = 45;
	GLfloat r4_0 = 90;

	GLfloat r1_1 = 135;
	GLfloat r2_1 = 0;
	GLfloat r3_1 = 90;
	GLfloat r4_1 = 90;

	GLfloat r1_2 = 45;
	GLfloat r2_2 = 0;
	GLfloat r3_2 = 90;
	GLfloat r4_2 = 90;

	int T = 100;
	if (this->IsBind)
	{
		if (this->timeflag == T * 4.5) {
			this->IsBind = false;
			this->timeflag = -1;
			this->fCatch = 45;
		}
		else {
			this->timeflag += 1;
			if (this->timeflag >= 0 && this->timeflag < 1 * T) {
				this->rotate1 += (r1_1 - r1_0) / float(T);
				this->rotate2 += (r2_1 - r2_0) / float(T);
				this->rotate3 += (r3_1 - r3_0) / float(T);
				this->rotate4 += (r4_1 - r4_0) / float(T);
			}

			if (this->timeflag >= 1 * T && this->timeflag < 2 * T) {
				this->fCatch -= 0.35;
			}
			if (this->timeflag >= 2 * T && this->timeflag < 3 * T) {
				this->rotate1 += (r1_2 - r1_1) / float(T);
				this->rotate2 += (r2_2 - r2_1) / float(T);
				this->rotate3 += (r3_2 - r3_1) / float(T);
				this->rotate4 += (r4_2 - r4_1) / float(T);
				SetBindPosition();
			}

			if (this->timeflag >= 3 * T && this->timeflag < 3.5 * T) {
				this->fCatch += 0.35;
			}


			if (this->timeflag >= 3.5 * T && this->timeflag < 4.5 * T) {
				this->rotate1 += (r1_0 - r1_2) / float(T);
				this->rotate2 += (r2_0 - r2_2) / float(T);
				this->rotate3 += (r3_0 - r3_2) / float(T);
				this->rotate4 += (r4_0 - r4_2) / float(T);
			}
		}
	}
	else if(this->Check){
		GLfloat dis = sqrt(0.5 * 0.5 + 0.5 * 0.5);
		GLfloat angle = PI / 2 - atan(0.5 / 0.5);
		GLfloat TargetX = this->PositionX + dis * cos(angle - (this->rotate1) * c);
		GLfloat TargetZ = this->PositionZ + dis * sin(angle - (this->rotate1) * c);
		vector<Shape*>::iterator Siter;
		for (Siter = Shapes.begin(); Siter != Shapes.end(); Siter++) {
			if (((*Siter)->globalX >= TargetX-1e-1 && (*Siter)->globalX <= TargetX + 1e-1) && ((*Siter)->globalZ >= TargetZ - 1e-1 && (*Siter)->globalZ <= TargetZ + 1e-1)) {
				this->IsBind = true;
				this->TheShape = (*Siter);
				break;
			}
		}
		this->Check = false;
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
	this->update();
	glPushMatrix();
	glTranslatef(PositionX, PositionY - 0.099, PositionZ);
	glEnable(GL_NORMALIZE); glScalef(1.0/6.0 * ZoomIndex, 1.0 / 6.0 * ZoomIndex, 1.0 / 6.0 * ZoomIndex);
	glPushMatrix();
	glRotatef(rotate1, 0, 1, 0);
	glPushMatrix();
	glTranslatef(0, 1.2, 0);
	glRotatef(rotate2, 1, 0, 0);
	glTranslatef(0, -1.2, 0);
	glPushMatrix();
	glTranslatef(0, 4.2, 0);
	glRotatef(rotate3, 1, 0, 0);
	glTranslatef(0, -4.2, 0);
	glPushMatrix();
	glTranslatef(0, 8, 0);
	glRotatef(rotate4, 1, 0, 0);
	glTranslatef(0, -8, 0);

	//机械臂3
	glPushMatrix();
	glTranslatef(0, 8, 0);
	glRotatef(90, 0, 0, 1);
	glRotatef(90, 0, 1, 0);
	DrawRod(0.2, 0.1, 2);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0, 10, 0);
	glRotatef(180, 1, 0, 0);
	glScalef(0.25, 0.25, 0.25);
	Draw_Robot();
	glPopMatrix();

	glPopMatrix();

	//关节3
	glPushMatrix();
	//glRotatef(-90, 1, 0, 0);
	glTranslatef(0, 7.4, 0);
	DrawJoint();
	glPopMatrix();

	//机械臂2
	glPushMatrix();
	glTranslatef(0, 4.6, 0);
	glRotatef(90, 0, 0, 1);
	glRotatef(90, 0, 1, 0);
	DrawRod(0.2, 0.2, 2.8);
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

void Robot_2::SetBindPosition(void)
{
	float l2 = 0.5/1.2 * ZoomIndex;
	float l1 = 0.28 / 1.2 * ZoomIndex;
	float l3 = 0.8 / 1.2 * ZoomIndex;
	float l4 = 0.8 / 1.2*ZoomIndex;
	BindPositionX = -l2 * sin(rotate2 * c) - l3 * sin((rotate2 + rotate3) * c) - l4 * sin((rotate2 + rotate3 + rotate4) * c);
	BindPositionY = 0.099 -l1 - l2 * cos(rotate2 * c) - l3 * cos((rotate2 + rotate3) * c) - l4 * cos((rotate2 + rotate3 + rotate4) * c);;

	float temp = BindPositionX;
	BindPositionX = temp * cos(-(rotate1 + 90) * c);
	BindPositionZ = temp * sin(-(rotate1 + 90) * c);
	if (TheShape != NULL)
	{
		this->TheShape->globalX = this->BindPositionX + this->PositionX;
		this->TheShape->globalY = this->BindPositionY + this->PositionY;
		this->TheShape->globalZ = this->BindPositionZ + this->PositionZ;
	}
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
void Robot_2::update()
{
	Robot::update();
}
void Robot_2::not_is_bind()
{
	IsBind = !IsBind;
}