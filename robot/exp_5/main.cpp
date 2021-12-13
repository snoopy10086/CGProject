// glutEx1.cpp : �������̨Ӧ�ó������ڵ㡣

#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#pragma comment(lib, "glew32.lib")
#include "glew.h"
#include "gl/glut.h"
#include <math.h>
#include <assert.h>

#include "stanford_bunny.h"

float fTranslate;
float fScale = 1.0f;	// set inital scale value to 1.0f
float fDistance = 0.2f;
float angle = 0;
bool bAnim = false;
bool r1 = false;
bool r2 = false;
bool r3 = false;
bool forward2 = true;
bool forward3 = true;
bool bHu = false;
bool bDesk = false;
bool multi = true;
int wHeight = 0;
int wWidth = 0;
#define PI 3.1415926535
static int du = 90, OriX = -1, OriY = -1;   //du���ӵ��x��ļн�
static float r = 1.5, h = 0.0;   //r���ӵ���y��İ뾶��h���ӵ�߶ȼ���y���ϵ�����
static float c = PI / 180.0;    //���ȺͽǶ�ת������
unsigned int texture[5];
int hu = 0;
int mode = 0;

GLfloat rotate1 = 45;
GLfloat rotate2 = 0;
GLfloat rotate3 = 0;

enum {
	Robot = 1,  
};

#define BITMAP_ID 0x4D42
#define imageweight 128
#define imageheight 128
GLubyte image[imageheight][imageweight][3];


// �����ʾ�����飬������������ı�ʾ��
// ����: ͨ��ָ�룬����filename ָ����bitmap�ļ������ݡ�
// ͬʱҲ����bitmap��Ϣͷ.����֧��-bitλͼ��
unsigned char* LoadBitmapFile(char* filename, BITMAPINFOHEADER* bitmapInfoHeader)
{
	FILE* filePtr;	// �ļ�ָ��
	BITMAPFILEHEADER bitmapFileHeader;	// bitmap�ļ�ͷ
	unsigned char* bitmapImage;		// bitmapͼ������
	int	imageIdx = 0;		// ͼ��λ������
	unsigned char	tempRGB;	// ��������

								// �ԡ�������+����ģʽ���ļ�filename 
	fopen_s(&filePtr, filename, "rb");
	if (filePtr == NULL) return NULL;
	// ����bitmap�ļ�ͼ
	fread(&bitmapFileHeader, sizeof(BITMAPFILEHEADER), 1, filePtr);
	// ��֤�Ƿ�Ϊbitmap�ļ�
	if (bitmapFileHeader.bfType != BITMAP_ID) {
		fprintf(stderr, "Error in LoadBitmapFile: the file is not a bitmap file\n");
		return NULL;
	}

	// ����bitmap��Ϣͷ
	fread(bitmapInfoHeader, sizeof(BITMAPINFOHEADER), 1, filePtr);
	// ���ļ�ָ������bitmap����
	fseek(filePtr, bitmapFileHeader.bfOffBits, SEEK_SET);
	// Ϊװ��ͼ�����ݴ����㹻���ڴ�
	bitmapImage = new unsigned char[bitmapInfoHeader->biSizeImage];
	// ��֤�ڴ��Ƿ񴴽��ɹ�
	if (!bitmapImage) {
		fprintf(stderr, "Error in LoadBitmapFile: memory error\n");
		return NULL;
	}

	// ����bitmapͼ������
	fread(bitmapImage, 1, bitmapInfoHeader->biSizeImage, filePtr);
	// ȷ�϶���ɹ�
	if (bitmapImage == NULL) {
		fprintf(stderr, "Error in LoadBitmapFile: memory error\n");
		return NULL;
	}

	//����bitmap�б���ĸ�ʽ��BGR�����潻��R��B��ֵ���õ�RGB��ʽ
	for (imageIdx = 0;
		imageIdx < bitmapInfoHeader->biSizeImage; imageIdx += 3) {
		tempRGB = bitmapImage[imageIdx];
		bitmapImage[imageIdx] = bitmapImage[imageIdx + 2];
		bitmapImage[imageIdx + 2] = tempRGB;
	}
	// �ر�bitmapͼ���ļ�
	fclose(filePtr);
	return bitmapImage;
}

void texload(int i, char* filename)
{
	BITMAPINFOHEADER bitmapInfoHeader;                                 // bitmap��Ϣͷ
	unsigned char* bitmapData;                                       // ��������

	bitmapData = LoadBitmapFile(filename, &bitmapInfoHeader);
	glBindTexture(GL_TEXTURE_2D, texture[i]);
	// ָ����ǰ����ķŴ�/��С���˷�ʽ
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

	glTexImage2D(GL_TEXTURE_2D,
		0, 	    //mipmap���(ͨ��Ϊ0����ʾ���ϲ�) 
		GL_RGB,	//����ϣ���������к졢�̡�������
		bitmapInfoHeader.biWidth, //��������������n�����б߿�+2 
		bitmapInfoHeader.biHeight, //����߶ȣ�������n�����б߿�+2 
		0, //�߿�(0=�ޱ߿�, 1=�б߿�) 
		GL_RGB,	//bitmap���ݵĸ�ʽ
		GL_UNSIGNED_BYTE, //ÿ����ɫ���ݵ�����
		bitmapData);	//bitmap����ָ��  
}

void DrawRod(GLdouble baseR, GLdouble topR, GLdouble h);
void DrawRobot();

//������
void initCallList()
{
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
	
	glNewList(Robot, GL_COMPILE);
	glPushMatrix();

	DrawRobot();
	glPopMatrix();
	glEndList();
}

//����ȡ����
void drawScene()
{
	glPushName(1);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	//glRotatef(90, 0, 1, 0);
	DrawRobot();

	glPopName();

	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}

void init()
{
	//todo
	glGenTextures(1, texture);
	texload(0, (char*)"metal.bmp");



	/*glPixelStorei(GL_UNPACK_ALIGNMENT, 1); //�������ش洢ģʽ��������ȡ��ͼ�����ݵ��ж��뷽ʽ.�ڶ�������1��������Ч�ʣ���ͼƬһ�����������
	glTexImage2D(GL_TEXTURE_2D, 0, 3, imageweight, imageheight, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	*/

	const GLubyte* extensions = glGetString(GL_EXTENSIONS);
	bool multiTexturingSupported = strstr((const char*)extensions, "GL_ARB_multitexture ") != NULL;


	glMultiTexCoord1fARB = (PFNGLMULTITEXCOORD1FARBPROC)wglGetProcAddress("glMultiTexCoord1fARB");
	glMultiTexCoord2fARB = (PFNGLMULTITEXCOORD2FARBPROC)wglGetProcAddress("glMultiTexCoord2fARB");
	glMultiTexCoord3fARB = (PFNGLMULTITEXCOORD3FARBPROC)wglGetProcAddress("glMultiTexCoord3fARB");
	glMultiTexCoord4fARB = (PFNGLMULTITEXCOORD4FARBPROC)wglGetProcAddress("glMultiTexCoord4fARB");
	glActiveTextureARB = (PFNGLACTIVETEXTUREARBPROC)wglGetProcAddress("glActiveTextureARB");
	glClientActiveTextureARB = (PFNGLCLIENTACTIVETEXTUREARBPROC)wglGetProcAddress("glClientActiveTextureARB");

}

void HandleRotate()
{
	if (r1)
	{
		rotate1 += 0.4;
	}
	if (r2) 
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
			if (rotate2<0) {
				rotate2 = 0;
				forward2 = !forward2;
			}
		}
	}
	if (r3)
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

void DrawRod(GLdouble baseR, GLdouble topR, GLdouble h)
{
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texture[0]);  //ѡ������texture[1]
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
	glDisable(GL_TEXTURE_2D);	//�ر�����texture[1]

}

void DrawJoint()
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

void DrawRobot()
{
	HandleRotate();
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
				//��е��1
				glPushMatrix();
				glTranslatef(0, 4.2, 0.4);
				DrawRod(0.2, 0.2, 2);
				glPopMatrix();
			glPopMatrix();
			//�ؽ�2
			glPushMatrix();
			glTranslatef(0, 3.6, 0);
			DrawJoint();
			glPopMatrix();

			//��е��1
			glPushMatrix();
			glTranslatef(0, 1.6, 0);
			glRotatef(90, 0, 0, 1);
			glRotatef(90, 0, 1, 0);
			DrawRod(0.2, 0.2, 2);
			glPopMatrix();
		glPopMatrix();

		//�ؽ�1
		glPushMatrix();
		glTranslatef(0, 0.6, 0);
		DrawJoint();
		glPopMatrix();
	glPopMatrix();

	//����
	glPushMatrix();
	glRotatef(90, 0, 0, 1);
	glRotatef(90, 0, 1, 0);
	DrawRod(0.7, 0.5, 0.6);
	glPopMatrix();
	
}


void Mouse(int button, int state, int x, int y)
{
	if (state == GLUT_DOWN)  //��¼��갴��λ��
	{
		OriX = x, OriY = y;
	}
}

void onMouseMove(int x, int y)   //��������϶�
{
	du += x - OriX; //����ڴ���x�᷽���ϵ������ӵ��ӵ���x��ļн��ϣ��Ϳ�������ת
	h += 0.03 * (y - OriY);  //����ڴ���y�᷽���ϵĸı�ӵ��ӵ�y�������ϣ��Ϳ�������ת
	if (h > 1.5)   h = 1.5;  //���ӵ�y������һЩ���ƣ�����ʹ�ӵ�̫���
	else if (h < -1.5) h = -1.5;
	if (du > 180.0)   du = 180.0;  //�Զ�����һЩ���ƣ�ʹ�����ƶ��ǵ�����
	else if (du < 0.0) du = 0.0;
	OriX = x, OriY = y;  //����ʱ��������Ϊ��ֵ��Ϊ��һ�μ���������׼��
}

void updateView(int width, int height)
{
	glViewport(0, 0, width, height);						// Reset The Current Viewport

	glMatrixMode(GL_PROJECTION);						// Select The Projection Matrix
	glLoadIdentity();									// Reset The Projection Matrix

	float whRatio = (GLfloat)width / (GLfloat)height;

	gluPerspective(45.0f, whRatio, 0.1f, 100.0f);
	//glFrustum(-3, 3, -3, 3, 3,100);

	glMatrixMode(GL_MODELVIEW);							// Select The Modelview Matrix
}

void reshape(int width, int height)
{
	if (height == 0)										// Prevent A Divide By Zero By
	{
		height = 1;										// Making Height Equal One
	}

	wHeight = height;
	wWidth = width;

	updateView(wHeight, wWidth);
}

void idle()
{
	glutPostRedisplay();
}

float eye[] = { 0, 6, 10 };
float center[] = { 0, 0, 0 };

void key(unsigned char k, int x, int y)
{
	switch (k)
	{
	case 27:
	case 'q': {exit(0); break; }
	case 'm': {multi = !multi; break; }

	case 'a':
	{
		eye[0] -= fDistance;
		center[0] -= fDistance;
		break;
	}
	case 'd':
	{
		eye[0] += fDistance;
		center[0] += fDistance;
		break;
	}
	case 'w':
	{
		eye[1] += fDistance;
		center[1] += fDistance;
		break;
	}
	case 's':
	{
		eye[1] -= fDistance;
		center[1] -= fDistance;
		break;
	}
	case 'z':
	{
		eye[2] *= 0.95;
		break;
	}
	case 'c':
	{
		eye[2] *= 1.05;
		break;
	}
	case ' ':
	{
		bAnim = !bAnim;
		break;
	}
	case 'j':
	{
		r1 = !r1;
		break;
	}
	case 'k':
	{
		r2 = !r2;
		break;
	}
	case 'l':
	{
		r3 = !r3;
		break;
	}
	}
	updateView(wHeight, wWidth);
}

void redraw()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();									// Reset The Current Modelview Matrix

	gluLookAt(eye[0], eye[1], eye[2],
		center[0] - r * cos(c * du), center[1] - h, center[2] - r * sin(c * du),
		0, 1, 0);				// ������0��0��0�����ӵ����� (0,5,50)��Y������
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);
	GLfloat white[] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat light_pos[] = { 5,5,5,1 };

	glLightfv(GL_LIGHT0, GL_POSITION, light_pos);
	glLightfv(GL_LIGHT0, GL_AMBIENT, white);
	glEnable(GL_LIGHT0);
	 
	//glTranslatef(0.0f, -4.0f,-0.0f);			// Place the triangle at Center
	drawScene();

	glutSwapBuffers();
}

int main(int argc, char *argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DEPTH | GLUT_DOUBLE);
	glutInitWindowSize(480, 480);
	int windowHandle = glutCreateWindow("robot");
	init();
	initCallList();
	glutDisplayFunc(redraw);
	glutReshapeFunc(reshape);
	glutKeyboardFunc(key);
	glutIdleFunc(idle);
	glutMouseFunc(Mouse);
	glutMotionFunc(onMouseMove);
	
	glutMainLoop();
	return 0;
}
