#include "conveyor.h"

extern unsigned int texture[50];
void Texture_cube(int n, int i, int j, int k);

conveyor::conveyor(float PositionX, float PositionY, float MotionX, float MotionY)
{
	this->PositionX = PositionX;
	this->PositionY = PositionY;
	this->MotionX = MotionX;
	this->MotionY = MotionY;
}

bool conveyor::ifOntheConveyor(Shape* shape)
{
	float shapeZ = shape->getGlobalZ();
	if (shapeZ >= 1.0f || shapeZ <= -1.0f)	//not near the ground surface
		return false;
	float shapeX = shape->getGlobalX();
	float shapeY = shape->getGlobalY();
	
	if (shapeX<this->PositionX || shapeX > this->PositionX + EDGE)
		return false;
	if (shapeY<this->PositionY || shapeY > this->PositionY + EDGE)
		return false;
	return true;
}

void conveyor::AddMotion(Shape* shape)
{
	if (ifOntheConveyor(shape))
		shape->transfer(this->MotionX, this->MotionY, 0);
	else
		return;
}

//绘制带纹理的圆形，贴于传送带轮子上，i为为例编号
void conveyor::Texture_Circle(int i)
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
	gluDisk(frontface, 0, 0.5, 100, 2);
	glPopMatrix();
	glDisable(GL_TEXTURE_2D);
}

//绘制带纹理的圆柱面，i为为例编号
void conveyor::Texture_Cylinder(int i)
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

void conveyor::DrawConveyor2()
{
	//glEnable(GL_NORMALIZE);glScalef(0.5, 0.5, 0.5);
	//传送带圆柱,共4个
	GLfloat mat_specular[] = { 1., 1., 1., 1.0 };	         // 镜面反射颜色
	GLfloat mat_shininess[] = { 50.0 };							// 镜面反射参数
	GLfloat lmodel_ambient[] = { 1., 1., 1., 1.0 };		// 散射颜色
	GLfloat lmodel_emmision[] = { 0.0, 0.0, 0.0, 1.0 };

	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, lmodel_ambient);
	glMaterialfv(GL_FRONT, GL_EMISSION, lmodel_emmision);
	glPushMatrix();
	glTranslatef(-4.5, 0, -1);
	Texture_Cylinder(21);
	Texture_Circle(20);
	/*glTranslatef(3, 0, 0);
	Texture_Cylinder(15);
	Texture_Circle(16);;
	glTranslatef(3, 0, 0);
	Texture_Cylinder(15);
	Texture_Circle(16);*/
	glTranslatef(9, 0, 0);
	Texture_Cylinder(21);
	Texture_Circle(20);
	//前面也要贴上纹理
	glTranslatef(0, 0, 2);
	Texture_Circle(20);
	/*glTranslatef(-3, 0, 0);
	Texture_Circle(16);
	glTranslatef(-3, 0, 0);
	Texture_Circle(16);*/
	glTranslatef(-9, 0, 0);
	Texture_Circle(20);
	glPopMatrix();

	//中间部分连接的皮带
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
	glTranslatef(20, 1, 27);
	//glCallList(conveyorList);
	DrawConveyor2();
	glPopMatrix();
}

//模拟传送带运动：将一个物品放在传送带一端，按下t键向左运动
void conveyor::Move() {
	glPushMatrix();

	glEnable(GL_NORMALIZE); glScalef(0.1, 0.1, 0.1);
	glTranslatef(48 + move, 4, 54);

	//Texture_cube(1, 13, 0, 0);
	glPopMatrix();
}
