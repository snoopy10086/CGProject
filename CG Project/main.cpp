#pragma once
#include "drawEnvironment.h"
#include "Robot.h"
#include "Shape.h"
#include "conveyor.h"
#include <math.h>
#define PI 3.1415926535
static int du = 90, OriX = -1, OriY = -1, Px = -1, Py = -1;   //du是视点和x轴的夹角
static float r = 8, h = 0.0;   //r是视点绕y轴的半径，h是视点高度即在y轴上的坐标
static float c = PI / 180.0;    //弧度和角度转换参数

float eye[] = { 4,1,4 };//{ 6, 1, 6 }

float d[] = { 0,0,0 };

float screenrate_x = -PI / 2, screenrate_y = 0;//鼠标屏幕坐标相对于中心点移动的比例
float step = 0.05;
int wWidth = 600, wHeight = 600;
int wPosW = 100;
int wPosH = 100;


//定义各种物体
Robot_2 robot21(3.5, 0, 4.8);
Robot_2 robot22(4.5, 0, 4.8);
Robot_1 robot1(0, 0, 0);
conveyor conv1(0, 0, 0, 0);
Cylinder s1(0,0,0);
ConeCylinder s2(0, 0, 0);
Cone s3(0, 0, 0);
Cube s4(0, 0, 0);
void renderScene(void);
float move = 0;
int count = 0;

void key(unsigned char k, int x, int y)
{
	switch (k)
	{
	case 27:
	case 'q': {exit(0); break; }
	case 'a': {//todo, hint: eye[] and center[] are the keys to solve the problems
		eye[0] += step * cos(screenrate_x - PI / 2);
		eye[2] += step * sin(screenrate_x - PI / 2);
		break;
	}
	case 'd': {//todo
		eye[0] -= step * cos(screenrate_x - PI / 2);
		eye[2] -= step * sin(screenrate_x - PI / 2);


		break;
	}
	case 'w': {//todo
		//eye[2] -= 0.1;
		eye[1] += step * sin(screenrate_y);
		eye[0] += step * cos(screenrate_y) * cos(screenrate_x);
		eye[2] += step * cos(screenrate_y) * sin(screenrate_x);
		break;
	}
	case 's': {//todo
		eye[1] -= step * sin(screenrate_y);
		eye[0] -= step * cos(screenrate_y) * cos(screenrate_x);
		eye[2] -= step * cos(screenrate_y) * sin(screenrate_x);
		break;
	}
	case 'z': {//todo
		eye[1] += 0.1;

		break;
	}
	case 'c': {//todo
		eye[1] -= 0.1;
		break;
	}
	case 'r':
	{
		robot21.Isrotate = !robot21.Isrotate;
		break;
	}
	case 'y':
	{
		robot22.Isrotate = !robot22.Isrotate;
		break;
	}
	case 'i':
	{
		robot1.len_inc();
		break;
	}
	case 'k':
	{
		robot1.len_dec();
		break;
	}
	case 'e':
	{
		robot1.not_catch();
		break;
	}
	case 't':
	{
		conv1.move = conv1.move - 0.3;
		conv1.count = (conv1.count + 1) % 5;
		//printf("%d\n", count);
		break;
	}
	case '1':
	{
		Change_Door_1();
		break;
	}
	case '2':
	{
		Change_Door_2();
		break;
	}
	case '3':
	{
		Change_Window(0);
		break;
	}
	case '4':
	{
		Change_Window(1);
		break;
	}
	case '5':
	{
		Change_Window(2);
		break;
	}
	case 'u': 
	{
		Change_Rust();
	}
	}
}

void renderScene(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	//点光源 1
	GLfloat white_ambient[] = { 0., 0., 0., 1.0 };
	GLfloat white_diffuse[] = { 1., 1., 1., 1.0 };
	GLfloat white_specular[] = { 1., 1., 1., 1.0 };

	GLfloat light_pos0[] = { 1.6, 1.0, 1.6, 1 };
	glLightfv(GL_LIGHT0, GL_POSITION, light_pos0);
	glLightfv(GL_LIGHT0, GL_AMBIENT, white_ambient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, white_diffuse);
	glLightfv(GL_LIGHT0, GL_SPECULAR, white_specular);
	glLightf(GL_LIGHT0, GL_CONSTANT_ATTENUATION, 0.4f);
	glEnable(GL_LIGHT0);

	GLfloat light_pos1[] = { 3.2, 1., 3.2, 1 };
	glLightfv(GL_LIGHT1, GL_POSITION, light_pos1);
	glLightfv(GL_LIGHT1, GL_AMBIENT, white_ambient);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, white_diffuse);
	glLightfv(GL_LIGHT1, GL_SPECULAR, white_specular);
	glLightf(GL_LIGHT1, GL_CONSTANT_ATTENUATION, 0.4f);
	//glEnable(GL_LIGHT1);
	//点光源 2
	GLfloat light_pos2[] = { 4.8, 1., 4.8, 1 };
	glLightfv(GL_LIGHT2, GL_POSITION, light_pos2);
	glLightfv(GL_LIGHT2, GL_AMBIENT, white_ambient);
	glLightfv(GL_LIGHT2, GL_DIFFUSE, white_diffuse);
	glLightfv(GL_LIGHT2, GL_SPECULAR, white_specular);
	glLightf(GL_LIGHT2, GL_CONSTANT_ATTENUATION, 0.4f);
	//glEnable(GL_LIGHT2);
	//点光源 3
	GLfloat light_pos3[] = { 6.4, 1., 6.4, 1 };
	glLightfv(GL_LIGHT3, GL_POSITION, light_pos3);
	glLightfv(GL_LIGHT3, GL_AMBIENT, white_ambient);
	glLightfv(GL_LIGHT3, GL_DIFFUSE, white_diffuse);
	glLightfv(GL_LIGHT3, GL_SPECULAR, white_specular);
	glLightf(GL_LIGHT3, GL_CONSTANT_ATTENUATION, 0.8f);
	glEnable(GL_LIGHT3);
	// 点光源 4
	GLfloat light_pos4[] = { 6.4, 1., 6.4, 1 };
	glLightfv(GL_LIGHT4, GL_POSITION, light_pos4);
	glLightfv(GL_LIGHT4, GL_AMBIENT, white_ambient);
	glLightfv(GL_LIGHT4, GL_DIFFUSE, white_diffuse);
	glLightfv(GL_LIGHT4, GL_SPECULAR, white_specular);
	//glEnable(GL_LIGHT4);
	//点光源 5
	GLfloat light_pos5[] = { 1.6, 1., 6.4, 1 };
	glLightfv(GL_LIGHT5, GL_POSITION, light_pos4);
	glLightfv(GL_LIGHT5, GL_AMBIENT, white_ambient);
	glLightfv(GL_LIGHT5, GL_DIFFUSE, white_diffuse);
	glLightfv(GL_LIGHT5, GL_SPECULAR, white_specular);
	//glEnable(GL_LIGHT5);
	//点光源 6
	GLfloat light_pos6[] = { 6.4, 1., 3.2, 1 };
	glLightfv(GL_LIGHT6, GL_POSITION, light_pos4);
	glLightfv(GL_LIGHT6, GL_AMBIENT, white_ambient);
	glLightfv(GL_LIGHT6, GL_DIFFUSE, white_diffuse);
	glLightfv(GL_LIGHT6, GL_SPECULAR, white_specular);
	//glEnable(GL_LIGHT6);
	//点光源 7
	GLfloat light_pos7[] = { 6.4, 1., 3.2, 1 };
	glLightfv(GL_LIGHT7, GL_POSITION, light_pos4);
	glLightfv(GL_LIGHT7, GL_AMBIENT, white_ambient);
	glLightfv(GL_LIGHT7, GL_DIFFUSE, white_diffuse);
	glLightfv(GL_LIGHT7, GL_SPECULAR, white_specular);
	//glEnable(GL_LIGHT7);
	glLoadIdentity();
	gluLookAt(eye[0], eye[1], eye[2],
		eye[0] + r * cos(screenrate_x) * cos(screenrate_y), eye[1] + r * sin(screenrate_y), eye[2] + r * cos(screenrate_y) * sin(screenrate_x),
		0, 1, 0);				// 场景（0，0，0）的视点中心 (0,5,50)，Y轴向上
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);

	//glColor3f(1.0, 0.0, 0.0);
	draw();
	//drawSnowMans(true);
	//pickSnowMans(Px,Py);
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
