#pragma once
#include "drawEnvironment.h"
#include "Robot.h"
#include "Shape.h"
#include "conveyor.h"
#include <math.h>
#include <vector>
using namespace std;
#define PI 3.1415926535
static int du = 90, OriX = -1, OriY = -1, Px = -1, Py = -1;   //du是视点和x轴的夹角
static float r = 8, h = 0.0;   //r是视点绕y轴的半径，h是视点高度即在y轴上的坐标
static float c = PI / 180.0;    //弧度和角度转换参数
bool is_visitor = false;//开启碰撞检测
float eye[] = { 4,1,4 };//{ 6, 1, 6 }
float origin_eye[3];

float d[] = { 0,0,0 };

float screenrate_x = -PI / 2, screenrate_y = 0;//鼠标屏幕坐标相对于中心点移动的比例
float step = 0.05;
int wWidth = 600, wHeight = 600;
int wPosW = 100;
int wPosH = 100;

// 光照全局变量
GLfloat global_light_color[][4] = { { 1., 0.46, 0.14, 1.0 }, { 1., 0.78, 0.62, 1.0 }, { 1., 1., 1., 1.0 }, { 0.76, 0.81, 1., 1.0 }, { 0.51, 0.65, 1., 1.0 } };
int light_switch = 2;
GLfloat global_ambient[] = { 0., 0., 0., 1.0 };
GLfloat global_diffuse[] = { 1., 1., 1., 1.0 };
GLfloat global_specular[] = { 1., 1., 1., 1.0 };
bool global_light_enable[] = { true, false, false, true, false, false, false, false };

// 定义各种物体

conveyor* conv1 = new conveyor(0, 0, 1, 0);


void renderScene(void);
float move = 0;
int count = 0;

//collections
vector<Shape*> Shapes;						//collections of shapes
Shape* CurrentChooseShape = NULL;		//now choosen shape
vector<conveyor*> Conveyors;				//collections of conyors
vector<Robot*> Robots;				//collections of robots
vector<Prism> Prisms;

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

void InitialThings() {
	// 20211224 BDZ: 按照现在的键盘操作，如果设计成局部变量没有办法操作改变状态
	// 
	Robot_2* robot21 = new Robot_2(3.5, 0, 4.8);
	Robot_2* robot22 = new Robot_2(4.5, 0, 4.8);
	Robot_1* robot1 = new Robot_1(0,0,0);
	Robots.push_back(robot21);
	Robots.push_back(robot22);
	Robots.push_back(robot1);

	//conveyor* conv1 = new conveyor(0, 0, 1, 0);
	Conveyors.push_back(conv1);

	Cylinder* s1 = new Cylinder(27, 1, 22);
	ConeCylinder* s2 = new ConeCylinder(27, 0.5, 27);
	Cone* s3 = new Cone(30, 0.6, 27);
	Cube* s4 = new Cube(30, 2, 22);
	Prism* s5 = new Prism(27, 1, 18);
	Trustum* s6 = new Trustum(30, 1, 20);
	Shapes.push_back(s1);
	Shapes.push_back(s2);
	Shapes.push_back(s3);
	Shapes.push_back(s4);
	Shapes.push_back(s5);
	Shapes.push_back(s6);
}

void drawRobots() {
	vector<Robot*>::iterator Riter;
	for (Riter = Robots.begin(); Riter != Robots.end(); Riter++) {
		(*Riter)->Draw();
	}
}

void drawShapes() {
	vector<Shape*>::iterator Siter;
	for (Siter = Shapes.begin(); Siter != Shapes.end(); Siter++) {
		(*Siter)->Draw();
	}
}

void drawConveyors() {
	vector<conveyor*>::iterator Citer;
	for (Citer = Conveyors.begin(); Citer != Conveyors.end(); Citer++) {
		(*Citer)->draw();
	}
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
	case 'r':
	{
		((Robot_2*)Robots[0])->not_is_bind();
		((Robot_2*)Robots[1])->not_is_bind();
		break;
	}
	case 'y':
	{

		break;
	}
	case 'i':
	{

		break;
	}
	case 'k':
	{

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
		conv1->move = conv1->move - 0.3;
		conv1->count = (conv1->count + 1) % 5;
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

	//glColor3f(1.0, 0.0, 0.0);
	draw();
	drawConveyors();
	drawShapes();
	drawRobots();
	glutSwapBuffers();                                      //交换两个缓冲区指针
}

void Mouse(int button, int state, int x, int y)
{
	if (state == GLUT_DOWN)  //记录鼠标按下位置
		OriX = x, OriY = y;
	if (state == GLUT_UP)  //记录鼠标按下位置
		Px = x, Py = y;
}

void onMouseMove(int x, int y)   //处理鼠标拖动
{
	du += (x - OriX) * 0.8; //鼠标在窗口x轴方向上的增量加到视点与x轴的夹角上，就可以左右转
	h += 0.03 * (y - OriY) * 0.15;  //鼠标在窗口y轴方向上的改变加到视点y的坐标上，就可以上下转
	if (h > 1.0)   h = 1.0;  //对视点y坐标作一些限制，不会使视点太奇怪
	else if (h < -1.0) h = -1.0;
	OriX = x, OriY = y;  //将此时的坐标作为旧值，为下一次计算增量做准备
}
int centerpoint_x = wWidth / 2, centerpoint_y = wHeight / 2;
static float cons = 89 * c;
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
	glViewport(0, 0, w, h);    //截图;1、2为视口的左下角;3、4为视口的宽度和高度
	glMatrixMode(GL_PROJECTION);    //将当前矩阵指定为投影矩阵
	glLoadIdentity();
	gluPerspective(45, (float)w / h, 0.1, 100.0); //1、视野在Y-Z平面的角度[0,180];2、投影平面宽度与高度的比率;3、近截剪面到视点的距离;4、远截剪面到视点的距离
	glMatrixMode(GL_MODELVIEW);     //对模型视景矩阵堆栈应用随后的矩阵操作.
}

int main(int argc, char* argv[])
{
	glutInit(&argc, argv);                                          //初始化glut库
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);      //设置初始显示模式
	glutInitWindowPosition(wPosW, wPosH);
	glutInitWindowSize(wWidth, wHeight);
	glutCreateWindow("CG Project");
	init();
	glutReshapeFunc(reshape);       //
	glutDisplayFunc(renderScene);           //
	glutIdleFunc(renderScene);          //设置不断调用显示函数
	glutMouseFunc(Mouse);
	glutMotionFunc(onMouseMove);
	glutPassiveMotionFunc(mouse_move);
	glutKeyboardFunc(key);
	glutMainLoop();//enters the GLUT event processing loop.
	return 0;
}
