#include <windows.h>
//#include <gl/gl.h>
//#include <gl/glu.h>
#include <gl/glut.h>
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>


enum {
	snowManHeadDL = 1, snowManBodyDL,
};

typedef enum {
	HEAD = 100, BODY,
} PickInfo;

PickInfo s_part;
int s_row, s_col;

//画雪人
void initSnowMans()
{
	GLUquadricObj* sphere, * cone, * base;
	static GLfloat sphere_mat[] =
	{ 1.f, .5f, 0.f, 1.f };
	static GLfloat cone_mat[] =
	{ 0.f, .5f, 1.f, 1.f };

	glNewList(snowManHeadDL, GL_COMPILE);
	cone = gluNewQuadric();
	base = gluNewQuadric();
	glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, cone_mat);
	glRotatef(-90.f, 1.f, 0.f, 0.f);
	gluDisk(base, 0., 0.2, 0.2, 1);
	gluCylinder(cone, 0.2, 0, 0.4, 10, 10);
	gluDeleteQuadric(cone);
	gluDeleteQuadric(base);
	glEndList();

	glNewList(snowManBodyDL, GL_COMPILE);
	sphere = gluNewQuadric();
	glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, sphere_mat);
	gluSphere(sphere, 0.2, 10, 10);
	gluDeleteQuadric(sphere);
	glEndList();

}

//雪人取名字
void drawSnowMans(bool picking)
{
	for (int i = -3; i < 3; i++)
	{
		glPushName(i);
		for (int j = -3; j < 3; j++) {


			glPushMatrix();

			glPushName(j);
			glTranslatef(i * 0.5, 0, j * 0.5);
			glPushName(HEAD);

			if (!picking && i == s_row && j == s_col && s_part == HEAD)
				glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
			else
				glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
			glCallList(snowManHeadDL);


			glLoadName(BODY);
			glPushMatrix();
			glTranslatef(0, 0, -0.2);

			if (!picking && i == s_row && j == s_col && s_part == BODY)
				glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
			else
				glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
			glCallList(snowManBodyDL);
			glPopMatrix();

			glPopName();
			glPopName();
			glPopMatrix();
		}
		glPopName();
	}

	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}

#define BUFSIZE 512
GLuint selectBuf[BUFSIZE]; // 设置一个选择缓冲区

void startPicking(int cursorX, int cursorY)
{
	GLint viewport[4]; //视口大小，四个值按顺序为x, y, width, height
	glSelectBuffer(BUFSIZE, selectBuf);
	glRenderMode(GL_SELECT); //拾取前，需要进入选择模式

	glMatrixMode(GL_PROJECTION); //选择投影矩阵。判断是以投影的方式进行的。
	glPushMatrix(); //向状态机压入投影矩阵
	glLoadIdentity(); //重置矩阵，为了构建拾取矩阵

	glGetIntegerv(GL_VIEWPORT, viewport);//返回当前视口的数值，并存入viewport数组中
	gluPickMatrix(cursorX, viewport[3] - cursorY, 5, 5, viewport); //建立拾取矩阵，前两个参数为将窗口坐标cursor转化为OpenGL坐标，第三、四个参数是选择框的大小，最后一个就是视口的位置和大小
	gluPerspective(45.0f, 1, 0.1, 100); //乘以一个固定的投影矩阵。当然也可以变化这个投影矩阵
	glMatrixMode(GL_MODELVIEW);//进入视图变换状态
	glInitNames(); //初始化名字栈，用来存放目标物体的名字
}

void processHits(GLint hits, GLuint buffer[])
{
	unsigned int i, j;
	GLuint names, * ptr, minZ, * ptrNames, numberOfNames;

	printf("hits = %d\n", hits);
	ptr = (GLuint*)buffer;
	ptrNames = (GLuint*)buffer;
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

	assert(numberOfNames == 3);
	s_row = ptrNames[0];
	s_col = ptrNames[1];
	s_part = (PickInfo)ptrNames[2];
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
}

//extern void drawScene(bool);


void pickSnowMans(int x, int y)
{
	startPicking(x, y);
	//drawSnowMans(); //该函数用来渲染物体，也就是绘制自己想要绘制的物体，包括名字
	initSnowMans();
	stopPicking();
}


int main(int argc, char* argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DEPTH | GLUT_DOUBLE);
	glutInitWindowSize(480, 480);
	int windowHandle = glutCreateWindow("picking and rolling");

	glutDisplayFunc(redraw);


	init();

	glutMainLoop();
	return 0;
}