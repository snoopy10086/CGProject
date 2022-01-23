#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include "drawEnvironment.h"
#include "model_view.h"
#include "Robot.h"
#include "Shape.h"
#include "conveyor.h"
#include "model_view.h"
#include <math.h>
#include <time.h>
#include <string.h>
#include <vector>
#include<algorithm>
using namespace std;
#define PI 3.1415926535
#define BMP_Header_Length 54
#define BUFSIZE 512
static int du = 90, OriX = -1, OriY = -1, Px = -1, Py = -1;   //du是视点和x轴的夹角
static float r = 8, h = 0.0;   //r是视点绕y轴的半径，h是视点高度即在y轴上的坐标
static float c = PI / 180.0;    //弧度和角度转换参数
bool is_visitor = false;//开启碰撞检测
float eye[] = { 4,1,4 };//{ 6, 1, 6 }
float origin_eye[3];

float d[] = { 0,0,0 };

float screenrate_x = -PI / 2, screenrate_y = 0;//鼠标屏幕坐标相对于中心点移动的比例
float step = 0.05;
int wWidth = 1536, wHeight = 846;
//int wWidth = 846, wHeight = 846;
int wPosW = 0;// 原为（100，100），这样方便调试的时候能看到控制台输出:)
int wPosH = 0;
int centerpoint_x = wWidth / 2, centerpoint_y = wHeight / 2;
static float cons = 89 * c;
// 光照全局变量
GLfloat global_light_color[][4] = { { 1., 0.46, 0.14, 1.0 }, { 1., 0.78, 0.62, 1.0 }, { 1., 1., 1., 1.0 }, { 0.76, 0.81, 1., 1.0 }, { 0.51, 0.65, 1., 1.0 } };
int light_switch = 2;
GLfloat global_ambient[] = { 0., 0., 0., 1.0 };
GLfloat global_diffuse[] = { 1., 1., 1., 1.0 };
GLfloat global_specular[] = { 1., 1., 1., 1.0 };
bool global_light_enable[] = { true, false, false, true, false, false, false, false };

// 定义各种物体
void renderScene(void);
void reshape(int w, int h);
void set_eye();
void modify_eye();
int BindShapeRobot(Robot* R, Shape* S);
int UnbindShapeRobot(Robot* R, Shape* S);
void AddMotionToShapes();
void InitialThings();
void drawRobots();
void drawConveyors();
void drawShapes();
void key(unsigned char k, int x, int y);
void setLight();
void startPicking(int cursorX, int cursorY);
void processHits(GLint hits, GLuint buffer[]);
void stopPicking();
void Mouse(int button, int state, int x, int y);
void onMouseMove(int x, int y);
void mouse_move(int mx, int my);
void init();
void reshape(int w, int h);
void mooncakeCollision();
bool shapeCompare(const Shape* a, const Shape* b);

float move = 0;
int count = 0;

//collections
vector<Shape*> Shapes;						//collections of shapes
Shape* CurrentChooseShape = NULL;		//now choosen shape
vector<conveyor*> Conveyors;				//collections of conveyors
vector<Robot*> Robots;				//collections of robots
vector<Prism> Prisms;

typedef enum {
	__robot = 100, __shape, __conveyor, NONE
}TYPE;
GLuint selectBuf[BUFSIZE]; // 设置一个选择缓冲区
TYPE s_type;
int s_id;

void set_eye() {
	origin_eye[0] = eye[0];
	origin_eye[1] = eye[1];
	origin_eye[2] = eye[2];
}

void modify_eye() {
	//wall
	if (eye[0] >= 7.8)eye[0] = 7.8;
	if (eye[1] >= 1.6)eye[1] = 1.6;
	if (is_visitor) {
		if (eye[2] >= 2.9)eye[2] = 2.9;
	}
	else {
		if (eye[2] >= 7.8)eye[2] = 7.8;
	}
	if (eye[0] <= 0.2)eye[0] = 0.2;
	if (eye[1] <= 0.4)eye[1] = 0.4;
	if (eye[2] <= 0.2)eye[2] = 0.2;
	if (is_visitor) {

		//board
		if (eye[0] >= 0.3 && eye[0] <= 1.9 && eye[1] >= 0.2 && eye[1] <= 1.2 && eye[2] >= 2.3 && eye[2] <= 2.6) {
			eye[0] = origin_eye[0];
			eye[1] = origin_eye[1];
			eye[2] = origin_eye[2];
		}
		//door
		if (getRDoor_2 && eye[0] >= 0.3 && eye[0] <= 1.0 && eye[1] >= 0.2 && eye[1] <= 1.4 && eye[2] >= 0.2 && eye[2] <= 0.7) {
			eye[0] = origin_eye[0];
			eye[1] = origin_eye[1];
			eye[2] = origin_eye[2];
		}
		//Closet
		if ((eye[0] >= 3.45 && eye[0] <= 3.75 || eye[0] >= 4.15 && eye[0] <= 4.45 || eye[0] >= 4.85 && eye[0] <= 5.15 || eye[0] >= 5.55 && eye[0] <= 5.85 || eye[0] >= 6.25 && eye[0] <= 6.55 || eye[0] >= 6.95 && eye[0] <= 7.25) && eye[2] >= 0.4 && eye[2] <= 1.8) {
			eye[0] = origin_eye[0];
			eye[1] = origin_eye[1];
			eye[2] = origin_eye[2];
		}
		//Desk
		if (eye[0] >= 7.2 && eye[0] <= 7.8 && eye[1] >= 0.2 && eye[1] <= 0.7 && eye[2] >= 2.1 && eye[2] <= 2.7) {
			eye[0] = origin_eye[0];
			eye[1] = origin_eye[1];
			eye[2] = origin_eye[2];
		}
	}
}

int BindShapeRobot(Robot* R, Shape* S) {
	if (R->enable == false || R->TheShape != NULL) {
		return 0;
	}
	R->TheShape = S;
	//S->TheRobot = R;
	return 1;
}

//unbind a shape from a robot
int UnbindShapeRobot(Robot* R, Shape* S) {
	R->TheShape = NULL;
	//S->TheRobot = NULL;
	return 1;
}

//called once each update
//every conyors in collections add motion to shapes
void AddMotionToShapes() {
	vector<conveyor*>::iterator Citer;
	for (Citer = Conveyors.begin(); Citer != Conveyors.end(); Citer++) {
		vector<Shape*>::iterator Siter;
		for (Siter = Shapes.begin(); Siter != Shapes.end(); Siter++) {
			(*Citer)->AddMotion((*Siter));
		}
	}
}

//传送带和月饼原料位置参数
float dis = 0.6,cx1 = 3, cx2 = cx1+dis+2, cz1 = 4, cz2 = cz1+dis+0.4;
void InitialThings() {
	//机械臂
	Robot_2* robot21 = new Robot_2(cx1+1+dis/2+1, 0, (cz1+cz2)/2);    
	Robot_2* robot22 = new Robot_2(cx1 + 1 + dis / 2, 0, cz1-0.5);
	Robot_2* robot23 = new Robot_2(1.65, 0, (cz1 + cz2) / 2);
	Robot_2* robot24 = new Robot_2(1.65, 0, cz2+0.4);
	robot21->rotate1 += 180;
	robot22->rotate1 += 270;
	Robot_1* robot1 = new Robot_1(0,0,0);
	Robots.push_back(robot21);
	Robots.push_back(robot22);
	Robots.push_back(robot23);
	Robots.push_back(robot24);
	Robots.push_back(robot1);
	//传送带
	conveyor* conv1 = new conveyor(cx2, 0, cz2, 1, 0);
	conveyor* conv2 = new conveyor(cx2, 0, cz1, 1, 0);
	conveyor* conv3 = new conveyor(cx1, 0, cz2, 1, 0);
	conveyor* conv4 = new conveyor(cx1, 0, cz1, 1, 0);	
	//conv2->rotate(0, 180, 0);
	Conveyors.push_back(conv1);
	Conveyors.push_back(conv2);
	Conveyors.push_back(conv3);
	Conveyors.push_back(conv4);
	//月饼皮、馅料、礼物盒
	Sphere* b1 = new Sphere(cx2+0.8, 0.2, cz2,0);//馅料0，放到传送带1上
	printf("B1 HAS A TYPE %d\n", b1->RetType());
	//YueBing* c1 = new YueBing(cx2 + 0.8, 0.2, cz1, b1->RetType() + 10);//月饼10，放到传送带上4.70.25.2
	//printf("C1 HAS A TYPE %d\n", c1->RetType());
	//Sphere* b2 = new Sphere(cx2 + 0.6, 0.2, cz2,1);//馅料1，放到传送带上4.70.25.2
	//printf("B2 HAS A TYPE %d\n", b2->RetType());
	//YueBing* c2 = new YueBing(4.4, 0.2, 4.6, b2->RetType() + 10);//月饼11，用这个rettype函数就可以创建馅料类型对应的月饼类型
	//printf("C2 HAS A TYPE %d\n", c2->RetType());
	//Sphere* b3 = new Sphere(3.2, 0.2, 4.6, 2);//馅料2，放到传送带上4.70.25.2
	//printf("B3 HAS A TYPE %d\n", b3->RetType());
	//YueBing* c3 = new YueBing(4.2, 0.2, 4.6, b3->RetType() + 10);//月饼12，放到传送带上4.70.25.2
	//printf("C3 HAS A TYPE %d\n", c3->RetType());
	//YueBingPi* c4 = new YueBingPi(cx2 + 0.5, 0.2, cz2);//月饼皮-2，放到传送带2上
	YueBingPi* c4 = new YueBingPi(cx2 + 0.8, 0.2, cz1);//月饼皮-2，放到传送带2上
	YueBingPi* c41 = new YueBingPi(cx2 + 0.8, 0.2, cz1);//月饼皮-2，放到传送带2上
	LiWuHePingMian* l1 = new LiWuHePingMian(cx1 + 0.75, 0.2, cz2, 3);	//礼物盒皮3,传送带3：2.98, 0, 4.6
	//LiWuHePingMian* l2 = new LiWuHePingMian(3.6, 0.2, 5.8, 4);	//礼物盒皮4
	//LiWuHe* l3 = new LiWuHe(cx2 + 0.6, 0.2, cz2, 23);	//礼物盒23
	//LiWuHe* l4 = new LiWuHe(3.3, 0.2, 5.8, 24); //礼物盒24
	//平台，放做好的月饼
	Cube* table = new Cube(cx1-1, 0, cz2+0.6+dis);
	table->scaling(1.2, 0.5, 1.2);
	//闲置的shape，展示我们实现了这些立方体=.=
	Cylinder* s1 = new Cylinder(3, 0, 4);
	s1->scaling(0.5, 0.125, 0.5);
	ConeCylinder* s2 = new ConeCylinder(3, 0, 2.5);
	Cone* s3 = new Cone(2, 0, 1);
	Cube* s4 = new Cube(3, 0, 1);
	Prism* s5 = new Prism(3.5, 0, 2);
	Trustum* s6 = new Trustum(3, 0, 2);
	//Shapes.push_back(l4);
	//Shapes.push_back(l3);
	//Shapes.push_back(l2);
	Shapes.push_back(b1);
	Shapes.push_back(l1);
	Shapes.push_back(c4);
	//Shapes.push_back(c1);
	/*Shapes.push_back(b3);
	Shapes.push_back(c3);
	
	Shapes.push_back(c2);*/
	//Shapes.push_back(l3);
	/*
	Shapes.push_back(c2);
	Shapes.push_back(c3);*/
	//Shapes.push_back(c41);
	Shapes.push_back(s1);
	Shapes.push_back(s2);
	Shapes.push_back(s3);
	Shapes.push_back(s4);
	Shapes.push_back(s5);
	Shapes.push_back(s6);
	Shapes.push_back(table);	
}

void drawRobots() {
	vector<Robot*>::iterator Riter;
	int i = 0;
	glPushName(__robot);
	glPushName(0);
	for (Riter = Robots.begin(); Riter != Robots.end(); Riter++) {
		glLoadName(i);
		i++;
		(*Riter)->Draw();
	}
	glPopName();
	glPopName();
}

void drawShapes() {
	vector<Shape*>::iterator Siter;
	int i = 0;
	glPushName(__shape);
	glPushName(0);
	for (Siter = Shapes.begin(); Siter != Shapes.end(); Siter++) {
		glLoadName(i);
		i++;
		(*Siter)->Draw();
	}
	glPopName();
	glPopName();
}

void drawConveyors() {
	vector<conveyor*>::iterator Citer;
	int i = 0;
	glPushName(__conveyor);
	glPushName(0);
	for (Citer = Conveyors.begin(); Citer != Conveyors.end(); Citer++) {
		
		glLoadName(i);
		i++;
		(*Citer)->draw();

	}
	glPopName();
	glPopName();
}

void TakePicture(void)
{
	FILE* DummyFile;
	FILE* SaveFile;
	GLubyte* PixelData;
	GLubyte  BMP_Header[BMP_Header_Length];
	GLint i, j;
	GLint DataLength;
	time_t t = time(0);
	char NowTime[64];
	strftime(NowTime, sizeof(NowTime), "%Y_%m_%d_%H_%M_%S", localtime(&t));

	i = wWidth * 3;
	while (i % 4 != 0)
		++i;
	DataLength = i * wHeight;

	PixelData = (GLubyte*)malloc(DataLength);
	if (PixelData == 0)
		exit(0);

	DummyFile = fopen("picture//test.bmp", "rb");
	if (DummyFile == 0)
		exit(0);

	char FileName[50] = "picture//CGProject_";
	strcat(strcat(FileName, NowTime), ".bmp");
	SaveFile = fopen(FileName, "wb"); //只写
	if (SaveFile == 0)
		exit(0);

	fread(BMP_Header, sizeof(BMP_Header), 1, DummyFile);
	fwrite(BMP_Header, sizeof(BMP_Header), 1, SaveFile);

	fseek(SaveFile, 0x0012, SEEK_SET); 
	i = wWidth;
	j = wHeight;
	fwrite(&i, sizeof(i), 1, SaveFile);
	fwrite(&j, sizeof(j), 1, SaveFile);

	glPixelStorei(GL_UNPACK_ALIGNMENT, 4);  
	glReadPixels(0, 0, wWidth, wHeight,
		GL_BGR_EXT, GL_UNSIGNED_BYTE, PixelData);

	// 写入像素数据
	fseek(SaveFile, 0, SEEK_END);
	fwrite(PixelData, DataLength, 1, SaveFile);

	// 释放内存和关闭文件
	fclose(DummyFile);
	fclose(SaveFile);
	free(PixelData);

}

void key(unsigned char k, int x, int y)
{
	switch (k)
	{
	case 27:
	case 'q': {exit(0); break; }
	case 'a': {
		set_eye();
		eye[0] += step * cos(screenrate_x - PI / 2);
		eye[2] += step * sin(screenrate_x - PI / 2);
		modify_eye();
		break;
	}
	case 'd': {
		set_eye();
		eye[0] -= step * cos(screenrate_x - PI / 2);
		eye[2] -= step * sin(screenrate_x - PI / 2);
		modify_eye();
		break;
	}
	case 'w': {
		set_eye();
		eye[1] += step * sin(screenrate_y);
		eye[0] += step * cos(screenrate_y) * cos(screenrate_x);
		eye[2] += step * cos(screenrate_y) * sin(screenrate_x);
		modify_eye();
		break;
	}
	case 's': {
		set_eye();
		eye[1] -= step * sin(screenrate_y);
		eye[0] -= step * cos(screenrate_y) * cos(screenrate_x);
		eye[2] -= step * cos(screenrate_y) * sin(screenrate_x);
		modify_eye();
		break;
	}
	case 'z': {
		set_eye();
		eye[1] += 0.1;
		modify_eye();
		break;
	}
	case 'c': {
		set_eye();
		eye[1] -= 0.1;
		modify_eye();
		break;
	}
	case '9':
	{
		((Robot_2*)Robots[0])->Check = true;
		break;

	} 
	case 'i':
	{
		((Robot_2*)Robots[1])->Check = true;
		break;
	}
	case 'k':
	{
		((Robot_2*)Robots[2])->Check = true;
		break;
	}
	case 'm':
	{
		((Robot_2*)Robots[3])->Check = true;
		break;
	}
	case 'y':
	{
		if (CurrentChooseShape != NULL)
		{
			CurrentChooseShape->scaling(2, 2, 2);
		}
		break;
	}
	case 'e':
	{
		Robots[0]->not_catch();
		Robots[1]->not_catch();
		Robots[2]->not_catch();
		break;
	}
	case 't':
	{
		vector<conveyor*>::iterator Citer;
		for (Citer = Conveyors.begin(); Citer != Conveyors.end(); Citer++) {
			//(*Citer)->move = (*Citer)->move - 0.03;
			(*Citer)->count = ((*Citer)->count + 1) % 5;
		}
		AddMotionToShapes();
		break;
	}
	case 'f':
	{
		Change_Door_1();
		break;
	}
	case 'g':
	{
		Change_Door_2();
		break;
	}
	case 'v':
	{
		Change_Window(0);
		break;
	}
	case 'b':
	{
		Change_Window(1);
		break;
	}
	case 'n':
	{
		Change_Window(2);
		break;
	}
	case 'u': 
	{
		Change_Rust();
		break;
	}
	case 'p':
	{
		TakePicture();
	}
	case '0':	case '1':	case '2':	case '3':	case '4':	case '5':	case '6':	case '7':
	{
		global_light_enable[k - '0'] = !global_light_enable[k - '0'];
		break;
	}
	case '8':
	{
		light_switch = (light_switch + 1) % 5;
		for (int i = 0; i < 3; i++) {
			global_diffuse[i] = global_specular[i] = global_light_color[light_switch][i];
		}
		break;
	}
	}
}

void setLight() {
	//点光源 0
	GLfloat light_pos0[] = { 1.6, 1.0, 1.6, 1 };
	glLightfv(GL_LIGHT0, GL_POSITION, light_pos0);
	glLightfv(GL_LIGHT0, GL_AMBIENT, global_ambient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, global_diffuse);
	glLightfv(GL_LIGHT0, GL_SPECULAR, global_specular);
	glLightf(GL_LIGHT0, GL_CONSTANT_ATTENUATION, 0.4f);
	if (global_light_enable[0]) glEnable(GL_LIGHT0);
	else glDisable(GL_LIGHT0);

	//点光源 1
	GLfloat light_pos1[] = { 3.2, 1., 3.2, 1 };
	glLightfv(GL_LIGHT1, GL_POSITION, light_pos1);
	glLightfv(GL_LIGHT1, GL_AMBIENT, global_ambient);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, global_diffuse);
	glLightfv(GL_LIGHT1, GL_SPECULAR, global_specular);
	glLightf(GL_LIGHT1, GL_CONSTANT_ATTENUATION, 0.4f);
	if (global_light_enable[1]) glEnable(GL_LIGHT1);
	else glDisable(GL_LIGHT1);

	//点光源 2
	GLfloat light_pos2[] = { 4.8, 1., 4.8, 1 };
	glLightfv(GL_LIGHT2, GL_POSITION, light_pos2);
	glLightfv(GL_LIGHT2, GL_AMBIENT, global_ambient);
	glLightfv(GL_LIGHT2, GL_DIFFUSE, global_diffuse);
	glLightfv(GL_LIGHT2, GL_SPECULAR, global_specular);
	glLightf(GL_LIGHT2, GL_CONSTANT_ATTENUATION, 0.4f);
	if (global_light_enable[2]) glEnable(GL_LIGHT2);
	else glDisable(GL_LIGHT2);

	//点光源 3
	GLfloat light_pos3[] = { 6.4, 1., 6.4, 1 };
	glLightfv(GL_LIGHT3, GL_POSITION, light_pos3);
	glLightfv(GL_LIGHT3, GL_AMBIENT, global_ambient);
	glLightfv(GL_LIGHT3, GL_DIFFUSE, global_diffuse);
	glLightfv(GL_LIGHT3, GL_SPECULAR, global_specular);
	glLightf(GL_LIGHT3, GL_CONSTANT_ATTENUATION, 0.8f);
	if (global_light_enable[3]) glEnable(GL_LIGHT3);
	else glDisable(GL_LIGHT3);

	// 点光源 4
	GLfloat light_pos4[] = { 1.6, 1., 6.4, 1 };
	glLightfv(GL_LIGHT4, GL_POSITION, light_pos4);
	glLightfv(GL_LIGHT4, GL_AMBIENT, global_ambient);
	glLightfv(GL_LIGHT4, GL_DIFFUSE, global_diffuse);
	glLightfv(GL_LIGHT4, GL_SPECULAR, global_specular);
	if (global_light_enable[4]) glEnable(GL_LIGHT4);
	else glDisable(GL_LIGHT4);

	//点光源 5
	GLfloat light_pos5[] = { 3.2, 1., 4.8, 1 };
	glLightfv(GL_LIGHT5, GL_POSITION, light_pos5);
	glLightfv(GL_LIGHT5, GL_AMBIENT, global_ambient);
	glLightfv(GL_LIGHT5, GL_DIFFUSE, global_diffuse);
	glLightfv(GL_LIGHT5, GL_SPECULAR, global_specular);
	if (global_light_enable[5]) glEnable(GL_LIGHT5);
	else glDisable(GL_LIGHT5);

	//点光源 6
	GLfloat light_pos6[] = { 4.8, 1., 3.2, 1 };
	glLightfv(GL_LIGHT6, GL_POSITION, light_pos6);
	glLightfv(GL_LIGHT6, GL_AMBIENT, global_ambient);
	glLightfv(GL_LIGHT6, GL_DIFFUSE, global_diffuse);
	glLightfv(GL_LIGHT6, GL_SPECULAR, global_specular);
	if (global_light_enable[6]) glEnable(GL_LIGHT6);
	else glDisable(GL_LIGHT6);

	//点光源 7
	GLfloat light_pos7[] = { 6.4, 1., 1.6, 1 };
	glLightfv(GL_LIGHT7, GL_POSITION, light_pos7);
	glLightfv(GL_LIGHT7, GL_AMBIENT, global_ambient);
	glLightfv(GL_LIGHT7, GL_DIFFUSE, global_diffuse);
	glLightfv(GL_LIGHT7, GL_SPECULAR, global_specular);
	if (global_light_enable[7]) glEnable(GL_LIGHT7);
	else glDisable(GL_LIGHT7);
}

void renderScene(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	setLight();
	glLoadIdentity();
	gluLookAt(eye[0], eye[1], eye[2],
		eye[0] + r * cos(screenrate_x) * cos(screenrate_y), eye[1] + r * sin(screenrate_y), eye[2] + r * cos(screenrate_y) * sin(screenrate_x),
		0, 1, 0);				// 场景（0，0，0）的视点中心 (0,5,50)，Y轴向上
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);
	mooncakeCollision();
	draw();
	drawConveyors();
	drawShapes();
	drawRobots();
	glutSwapBuffers();                                      //交换两个缓冲区指针
}
void startPicking(int cursorX, int cursorY)
{
	GLint viewport[4]; //视口大小，四个值按顺序为x, y, width, height

	glRenderMode(GL_SELECT); //拾取前，需要进入选择模式

	glMatrixMode(GL_PROJECTION); //选择投影矩阵。判断是以投影的方式进行的。
	glPushMatrix(); //向状态机压入投影矩阵
	glLoadIdentity(); //重置矩阵，为了构建拾取矩阵

	glGetIntegerv(GL_VIEWPORT, viewport);//返回当前视口的数值，并存入viewport数组中
	gluPickMatrix(cursorX, viewport[3] - cursorY, 0.5, 0.5, viewport); //建立拾取矩阵，前两个参数为将窗口坐标cursor转化为OpenGL坐标，第三、四个参数是选择框的大小，最后一个就是视口的位置和大小
	glOrtho(-10, 10, -10, 10, -10, 10);
	glMatrixMode(GL_MODELVIEW);//进入视图变换状态
	glInitNames(); //初始化名字栈，用来存放目标物体的名字
}

void processHits(GLint hits, GLuint buffer[])
{
	unsigned int i, j;
	GLuint names, * ptr, minZ, * ptrNames = NULL, numberOfNames;

	printf("hits = %d\n", hits);
	ptr = (GLuint*)buffer;
	minZ = 0xffffffff;

	for (i = 0; i < hits; i++) {
		names = *ptr;
		ptr++;

		if (*ptr < minZ) {
			numberOfNames = names;
			minZ = *ptr;
			ptrNames = ptr + 2;
		}

		ptr += names + 2;
	}

	printf("The closest hit names are ");
	ptr = ptrNames;
	for (j = 0; j < numberOfNames; j++, ptr++) {
		printf("%d ", *ptr);
	}
	printf("\n");

	s_type = (TYPE)ptrNames[0];
	s_id = ptrNames[1];
}

void stopPicking() {
	int hits;

	// restoring the original projection matrix
	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);
	glFlush();

	// returning to normal rendering model
	hits = glRenderMode(GL_RENDER);

	// if there are hits process them
	if (hits != 0)
		processHits(hits, selectBuf);
	else
		s_type = NONE;
}

void Mouse(int button, int state, int x, int y)
{
	if (state == GLUT_DOWN)  //记录鼠标按下位置
	{
		GLfloat view[16], pro[16];
		glm::vec3 res;
		OriX = x, OriY = y;
		startPicking(x, y);
		drawConveyors();
		drawShapes();
		drawRobots();
		stopPicking();
		if (s_type == NONE)/////改成__conveyor就是在传送带范围放东西;NONE是除传送带范围放置
		{
			glGetFloatv(GL_MODELVIEW_MATRIX, view);
			glGetFloatv(GL_PROJECTION_MATRIX, pro);
			res = getViewPos(x, y, pro, view);
			//printf("%f,%f,%f\n", eye[0], eye[1], eye[2]);
			Prism* p = new Prism(res[0], res[1] , res[2]);
			Shapes.push_back(p);
			cout << res[0] << " " << res[1] << " " << res[2] << " " << Shapes.size() << endl;
		}
		else
		{
			switch (s_type)
			{
			case __robot:
				CurrentChooseShape = NULL;
				break;
			case __shape:
				CurrentChooseShape = Shapes[s_id];
				break;
			case __conveyor:
				CurrentChooseShape = NULL;
				break;
			default:
				CurrentChooseShape = NULL;
				break;
			}
		}
	}
	if (state == GLUT_UP)  //记录鼠标按下位置
		Px = x, Py = y;
	renderScene();
}

void onMouseMove(int x, int y)   //处理鼠标拖动
{
	du += (x - OriX) * 0.8; //鼠标在窗口x轴方向上的增量加到视点与x轴的夹角上，就可以左右转
	h += 0.03 * (y - OriY) * 0.15;  //鼠标在窗口y轴方向上的改变加到视点y的坐标上，就可以上下转
	if (h > 1.0)   h = 1.0;  //对视点y坐标作一些限制，不会使视点太奇怪
	else if (h < -1.0) h = -1.0;
	OriX = x, OriY = y;  //将此时的坐标作为旧值，为下一次计算增量做准备
}

void mouse_move(int mx, int my)
{
	float offsetx = mx - OriX;
	float offsety = my - OriY;
	POINT p;
	screenrate_x = screenrate_x + (offsetx / 2 / centerpoint_x * PI);

	screenrate_y = screenrate_y + (-offsety / 2 / centerpoint_y * PI);
	screenrate_y = screenrate_y < -cons ? -cons : (screenrate_y > cons ? cons : screenrate_y);

	SetCursorPos(wPosW + centerpoint_x + 8, wPosH + centerpoint_y + 31);
	OriX = centerpoint_x;
	OriY = centerpoint_y;
}

void init()
{
	//initEnvironment();
	InitList();
	glEnable(GL_DEPTH_TEST);    //启用深度，根据坐标的远近自动隐藏被遮住的图形（材料）
	InitialThings();
}

void reshape(int w, int h)
{
	cout << "12312312" << endl;
	glViewport(0, 0, w, h);    //截图;1、2为视口的左下角;3、4为视口的宽度和高度
	glMatrixMode(GL_PROJECTION);    //将当前矩阵指定为投影矩阵
	glLoadIdentity();
	wWidth = w;
	wHeight = h;
	gluPerspective(45, (float)w / h, 0.1, 1000.0); //1、视野在Y-Z平面的角度[0,180];2、投影平面宽度与高度的比率;3、近截剪面到视点的距离;4、远截剪面到视点的距离
	glMatrixMode(GL_MODELVIEW);     //对模型视景矩阵堆栈应用随后的矩阵操作.
}

int main(int argc, char* argv[])
{
	glutInit(&argc, argv);                                          //初始化glut库
	//wWidth = glutGet(GLUT_SCREEN_WIDTH);
	//wHeight = glutGet(GLUT_SCREEN_HEIGHT);
	//cout << wWidth << wHeight;
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);      //设置初始显示模式
	glutInitWindowPosition(wPosW, wPosH);
	glutInitWindowSize(wWidth, wHeight);
	glutCreateWindow("CG Project");
	glSelectBuffer(BUFSIZE, selectBuf);
	init();
	glutReshapeFunc(reshape);       //
	glutDisplayFunc(renderScene);           //
	glutIdleFunc(renderScene);          //设置不断调用显示函数
	glutMouseFunc(Mouse);
	glutMotionFunc(mouse_move);
	glutPassiveMotionFunc(mouse_move);
	glutKeyboardFunc(key);
	glutSetCursor(GLUT_CURSOR_DESTROY);
	glutMainLoop();//enters the GLUT event processing loop.
	return 0;
}

// 检测并处理是否有月饼馅料与月饼皮、月饼与礼盒包装的碰撞
void mooncakeCollision() {
	vector<Shape*> Shapes2;//复制一份到Shapes2用于sort，不动原来的Shapes
	Shapes2.assign ( Shapes.begin(), Shapes.end());
	vector<Shape*>::iterator Siter;
	vector<Shape*>::iterator subSiter;
	int i = 0;
	sort(Shapes2.begin(), Shapes2.end(), shapeCompare);
	bool collisionFlag = false;
	for (Siter = Shapes2.begin(); Siter + 1 != Shapes2.end();) {
		collisionFlag = false;
		for (subSiter = Siter + 1; subSiter != Shapes2.end(); subSiter++) {
			if (((*subSiter)->RetType() == 0 && (*Siter)->RetType() == -2) || ((*subSiter)->RetType() == -2 && (*Siter)->RetType() == 0)) {
				// cout << "#bx:" << (*Siter)->getGlobalX() << "#by:" << (*Siter)->getGlobalY() << "#bz:" << (*Siter)->getGlobalZ() << endl;
				// cout << "#cx:" << (*subSiter)->getGlobalX() << "#cy:" << (*subSiter)->getGlobalY() << "#cz:" << (*subSiter)->getGlobalZ() << endl;
			}
			if (abs((*Siter)->getGlobalX() - (*subSiter)->getGlobalX()) > 0.019) {
				break;
			}
			else if (abs((*Siter)->getGlobalZ() - (*subSiter)->getGlobalZ()) > 0.056
				|| abs((*Siter)->getGlobalY() - (*subSiter)->getGlobalY()) > 0.016) {
				// cout << "p" << endl;
				continue;
			}
			else {
				if (((*Siter)->RetType() == -2 && (*subSiter)->RetType() >= 0 && (*subSiter)->RetType() <= 2)
					|| ((*subSiter)->RetType() == -2 && (*Siter)->RetType() >= 0 && (*Siter)->RetType() <= 2)) {
					// 馅料与饼皮相撞得月饼
					YueBing* mooncake = new YueBing((*Siter)->getGlobalX(), (*Siter)->getGlobalY(), (*Siter)->getGlobalZ(), 
						(*Siter)->RetType() == -2 ? (*subSiter)->RetType() + 10  : (*Siter)->RetType() + 10);
					Shapes.push_back(mooncake);//在原Shapes上进行改动
					collisionFlag = true;
					break;
				}
				else if (((*Siter)->RetType() >= 10 && (*Siter)->RetType() <= 12 && (*subSiter)->RetType() == 3 && (*subSiter)->RetType() == 4)
					|| ((*subSiter)->RetType() >= 10 && (*subSiter)->RetType() <= 12 && (*Siter)->RetType() == 3 && (*Siter)->RetType() == 4)) {
					// 月饼与礼品盒皮相撞得礼盒
					LiWuHe* gift = new LiWuHe((*Siter)->getGlobalX(), (*Siter)->getGlobalY(), (*Siter)->getGlobalZ(),
						(*Siter)->RetType() >= 10 ? (*subSiter)->RetType() + 20 : (*Siter)->RetType() + 20);					
					Shapes.push_back(gift);
					collisionFlag = true;
					break;
				}
			}
		}
		if (collisionFlag) {	// 有相撞发生
			vector<Shape*>::iterator tempIter;
			for (tempIter = Shapes.begin(); tempIter != Shapes.end();) {
				if ((*tempIter) == (*Siter) || (*tempIter) == (*subSiter)) {
					// cout << "*Siter:" << *Siter << ", * subSiter:" << *subSiter << ", tempIter:" << *tempIter << endl;
					tempIter = Shapes.erase(tempIter);
					cout << "Successfully erase" << endl;
				}
				else {
					tempIter++;
				}
			}
			int bias = subSiter - Siter;
			Siter = Shapes2.erase(Siter);
			Shapes2.erase(Siter + bias - 1);
			break;
		}
		else {
			Siter++;
		}
	}
}

bool shapeCompare(const Shape* a, const Shape* b) {
	return a->globalX < b->globalX || (a->globalX == b->globalX && a->globalY < b->globalY)
		|| (a->globalX == b->globalX && a->globalY == b->globalY && a->globalZ < b->globalZ);
}