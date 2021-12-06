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

//��ѩ��
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

//ѩ��ȡ����
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
GLuint selectBuf[BUFSIZE]; // ����һ��ѡ�񻺳���

void startPicking(int cursorX, int cursorY)
{
	GLint viewport[4]; //�ӿڴ�С���ĸ�ֵ��˳��Ϊx, y, width, height
	glSelectBuffer(BUFSIZE, selectBuf);
	glRenderMode(GL_SELECT); //ʰȡǰ����Ҫ����ѡ��ģʽ

	glMatrixMode(GL_PROJECTION); //ѡ��ͶӰ�����ж�����ͶӰ�ķ�ʽ���еġ�
	glPushMatrix(); //��״̬��ѹ��ͶӰ����
	glLoadIdentity(); //���þ���Ϊ�˹���ʰȡ����

	glGetIntegerv(GL_VIEWPORT, viewport);//���ص�ǰ�ӿڵ���ֵ��������viewport������
	gluPickMatrix(cursorX, viewport[3] - cursorY, 5, 5, viewport); //����ʰȡ����ǰ��������Ϊ����������cursorת��ΪOpenGL���꣬�������ĸ�������ѡ���Ĵ�С�����һ�������ӿڵ�λ�úʹ�С
	gluPerspective(45.0f, 1, 0.1, 100); //����һ���̶���ͶӰ���󡣵�ȻҲ���Ա仯���ͶӰ����
	glMatrixMode(GL_MODELVIEW);//������ͼ�任״̬
	glInitNames(); //��ʼ������ջ���������Ŀ�����������
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
	//drawSnowMans(); //�ú���������Ⱦ���壬Ҳ���ǻ����Լ���Ҫ���Ƶ����壬��������
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