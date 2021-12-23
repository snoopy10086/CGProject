#include "drawEnvironment.h"


GLubyte image[imageheight][imageweight][3];

unsigned int texture[50];
extern float move;
extern int count;
bool boardmode = false;
int boardnum = 0;
int boardcounter = 0;
void  Change_Rust() {
	boardmode = !boardmode;
}
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
enum {
	snowManHeadDL = 1, snowManBodyDL = 2, snowManHeadDL2 = 3, snowManBodyDL2 = 4,
};
GLint wall[10] = { 5,6,7 };
GLint door[2] = { 8,9 };
GLint window[4] = { 10,23,24,25 };
GLint bulb[2] = { 11 };
GLint closet[3] = { 12,13,14 };
GLint desk[2] = { 26,27 };
GLint Robot = 15;
GLint outside[2] = { 17,18 };
GLint door_edge[4] = { 19,20,21,22 };
GLint nurbs[2] = { 26 };
GLfloat r_door[2] = { -180,0 };
bool r_door_on[2] = { false,false };
float window_pos[3] = { -0.35,-0.35,-0.35 };
bool window_pos_on[3] = { false,false,false };
typedef enum {
	HEAD = 100, BODY,
} PickInfo;
extern bool r1;
extern bool r2;
extern bool r3;
extern Cylinder s1;
extern ConeCylinder s2;
extern Cone s3;
extern Cube s4;
extern conveyor conv1;
extern Robot_2 robot21;
extern Robot_2 robot22;
extern Robot_1 robot1;


GLfloat rotate1 = 45;
GLfloat rotate2 = 0;
GLfloat rotate3 = 0;

bool forward2 = true;
bool forward3 = true;


#define BUFSIZE 512
GLuint selectBuf[BUFSIZE]; // ����һ��ѡ�񻺳���

PickInfo s_part;
int s_row, s_col;

void Change_Door_1() {
	r_door_on[0] = !r_door_on[0];
}
void Change_Door_2() {
	r_door_on[1] = !r_door_on[1];
}
void Change_Window(int i) {
	window_pos_on[i] = !window_pos_on[i];
}

void InitList() {
	initTexture();
	initNurbs();
	initDoorList();
	initLightbulbList();
	initWindowList();
	initWallList();
	initClosetList();
	initGlassList();
}

void initTexture() {
	glGenTextures(50, texture);
	texload(0, (char*)"./texture/1.bmp");
	texload(1, (char*)"./texture/2.bmp");
	texload(2, (char*)"./texture/3.bmp");
	texload(3, (char*)"./texture/4.bmp");
	texload(4, (char*)"./texture/5.bmp");
	texload(5, (char*)"./texture/6.bmp");
	texload(6, (char*)"./texture/7.bmp");
	texload(7, (char*)"./texture/8.bmp");
	texload(8, (char*)"./texture/9.bmp");
	texload(9, (char*)"./texture/10.bmp");
	texload(10, (char*)"./texture/11.bmp");
	texload(11, (char*)"./texture/12.bmp");
	texload(12, (char*)"./texture/13.bmp");
	texload(13, (char*)"./texture/14.bmp");
	texload(14, (char*)"./texture/metal.bmp");
	texload(15, (char*)"./texture/15.bmp");
	texload(16, (char*)"./texture/16.bmp");
	texload(17, (char*)"./texture/17.bmp");
	texload(18, (char*)"./texture/18.bmp");
	texload(19, (char*)"./texture/19.bmp");
	texload(20, (char*)"./texture/c1.bmp");
	texload(21, (char*)"./texture/m1.bmp");
	texload(22, (char*)"./texture/m2.bmp");
	texload(23, (char*)"./texture/m3.bmp");
	texload(24, (char*)"./texture/m4.bmp");
	texload(25, (char*)"./texture/m5.bmp");
	texload(26, (char*)"./texture/21.bmp");
	texload(27, (char*)"./texture/22.bmp");
	texload(28, (char*)"./texture/23.bmp");
	texload(29, (char*)"./texture/24.bmp");
	texload(30, (char*)"./texture/25.bmp");
	texload(31, (char*)"./texture/26.bmp");
	const GLubyte* extensions = glGetString(GL_EXTENSIONS);
	bool multiTexturingSupported = strstr((const char*)extensions, "GL_ARB_multitexture ") != NULL;

	GLint maxTextureUnits = 0;
	glGetIntegerv(GL_MAX_TEXTURE_UNITS_ARB, &maxTextureUnits);

	glMultiTexCoord1fARB = (PFNGLMULTITEXCOORD1FARBPROC)wglGetProcAddress("glMultiTexCoord1fARB");
	glMultiTexCoord2fARB = (PFNGLMULTITEXCOORD2FARBPROC)wglGetProcAddress("glMultiTexCoord2fARB");
	glMultiTexCoord3fARB = (PFNGLMULTITEXCOORD3FARBPROC)wglGetProcAddress("glMultiTexCoord3fARB");
	glMultiTexCoord4fARB = (PFNGLMULTITEXCOORD4FARBPROC)wglGetProcAddress("glMultiTexCoord4fARB");
	glActiveTextureARB = (PFNGLACTIVETEXTUREARBPROC)wglGetProcAddress("glActiveTextureARB");
	glClientActiveTextureARB = (PFNGLCLIENTACTIVETEXTUREARBPROC)wglGetProcAddress("glClientActiveTextureARB");
}

GLint initGlassList() {
	return 0;
}
//������������ƴ�����ĳ�����,n��ʾ�������������,��������������

void Texture_cube(int n, int i, int j, int k)
{
	if (n == 1) {
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, texture[i]);  //ѡ������texture[1]
		glPushMatrix();

		//������
		//�����ĳ�ı��Σ��������趨�������꣬������ʾ���������Ҫ�˲�
		glBegin(GL_QUADS);
		glNormal3f(0.0, 0.0, 1.0);
		glTexCoord2i(1, 1); glVertex3i(-1, 1, 1);
		glTexCoord2i(1, 0); glVertex3i(-1, -1, 1);
		glTexCoord2i(0, 0); glVertex3i(1, -1, 1);
		glTexCoord2i(0, 1); glVertex3i(1, 1, 1);

		glNormal3f(0.0, 0.0, -1.0);
		glTexCoord2i(1, 1); glVertex3i(-1, 1, -1);
		glTexCoord2i(1, 0); glVertex3i(-1, -1, -1);
		glTexCoord2i(0, 0); glVertex3i(1, -1, -1);
		glTexCoord2i(0, 1); glVertex3i(1, 1, -1);

		glNormal3f(1.0, 0.0, 0.0);
		glTexCoord2i(1, 1); glVertex3i(1, -1, 1);
		glTexCoord2i(1, 0); glVertex3i(1, -1, -1);
		glTexCoord2i(0, 0); glVertex3i(1, 1, -1);
		glTexCoord2i(0, 1); glVertex3i(1, 1, 1);

		glNormal3f(-1.0, 0.0, 0.0);
		glTexCoord2i(1, 1); glVertex3i(-1, -1, 1);
		glTexCoord2i(1, 0); glVertex3i(-1, -1, -1);
		glTexCoord2i(0, 0); glVertex3i(-1, 1, -1);
		glTexCoord2i(0, 1); glVertex3i(-1, 1, 1);

		glNormal3f(0.0, 1.0, 0.0);
		glTexCoord2i(1, 1); glVertex3i(-1, 1, 1);
		glTexCoord2i(1, 0); glVertex3i(-1, 1, -1);
		glTexCoord2i(0, 0); glVertex3i(1, 1, -1);
		glTexCoord2i(0, 1); glVertex3i(1, 1, 1);

		glNormal3f(0.0, -1.0, 0.0);
		glTexCoord2i(1, 1); glVertex3i(-1, -1, 1);
		glTexCoord2i(1, 0); glVertex3i(-1, -1, -1);
		glTexCoord2i(0, 0); glVertex3i(1, -1, -1);
		glTexCoord2i(0, 1); glVertex3i(1, -1, 1);

		glEnd();
		glPopMatrix();

		glDisable(GL_TEXTURE_2D);	//�ر�����texture[1]
	}
	else {
		if (n == 3) {
			glActiveTextureARB(GL_TEXTURE0_ARB);
			glEnable(GL_TEXTURE_2D);
			glBindTexture(GL_TEXTURE_2D, texture[i]);  //ѡ������texture[1]

			glActiveTextureARB(GL_TEXTURE1_ARB);
			glEnable(GL_TEXTURE_2D);
			glBindTexture(GL_TEXTURE_2D, texture[j]);  //ѡ������texture[2]

			glActiveTextureARB(GL_TEXTURE1_ARB);
			glEnable(GL_TEXTURE_2D);
			glBindTexture(GL_TEXTURE_2D, texture[k]);  //ѡ������texture[2]

			glPushMatrix();

			//������
			//�����ĳ�ı��Σ��������趨�������꣬������ʾ���������Ҫ�˲�
			glBegin(GL_QUADS);
			glNormal3f(0.0, 0.0, 1.0);
			glMultiTexCoord2fARB(GL_TEXTURE0_ARB, 1, 1);
			glMultiTexCoord2fARB(GL_TEXTURE1_ARB, 1, 1); glVertex3i(-1, 1, 1);
			glMultiTexCoord2fARB(GL_TEXTURE0_ARB, 1, 0);
			glMultiTexCoord2fARB(GL_TEXTURE1_ARB, 1, 0); glVertex3i(-1, -1, 1);
			glMultiTexCoord2fARB(GL_TEXTURE0_ARB, 0, 0);
			glMultiTexCoord2fARB(GL_TEXTURE1_ARB, 0, 0); glVertex3i(1, -1, 1);
			glMultiTexCoord2fARB(GL_TEXTURE0_ARB, 0, 1);
			glMultiTexCoord2fARB(GL_TEXTURE1_ARB, 0, 1); glVertex3i(1, 1, 1);

			glNormal3f(0.0, 0.0, -1.0);
			glMultiTexCoord2fARB(GL_TEXTURE0_ARB, 1, 1);
			glMultiTexCoord2fARB(GL_TEXTURE1_ARB, 1, 1);  glVertex3i(-1, 1, -1);
			glMultiTexCoord2fARB(GL_TEXTURE0_ARB, 1, 0);
			glMultiTexCoord2fARB(GL_TEXTURE1_ARB, 1, 0); glVertex3i(-1, -1, -1);
			glMultiTexCoord2fARB(GL_TEXTURE0_ARB, 0, 0);
			glMultiTexCoord2fARB(GL_TEXTURE1_ARB, 0, 0); glVertex3i(1, -1, -1);
			glMultiTexCoord2fARB(GL_TEXTURE0_ARB, 0, 1);
			glMultiTexCoord2fARB(GL_TEXTURE1_ARB, 0, 1); glVertex3i(1, 1, -1);

			glNormal3f(1.0, 0.0, 0.0);
			glMultiTexCoord2fARB(GL_TEXTURE0_ARB, 1, 1);
			glMultiTexCoord2fARB(GL_TEXTURE1_ARB, 1, 1);  glVertex3i(1, -1, 1);
			glMultiTexCoord2fARB(GL_TEXTURE0_ARB, 1, 0);
			glMultiTexCoord2fARB(GL_TEXTURE1_ARB, 1, 0); glVertex3i(1, -1, -1);
			glMultiTexCoord2fARB(GL_TEXTURE0_ARB, 0, 0);
			glMultiTexCoord2fARB(GL_TEXTURE1_ARB, 0, 0); glVertex3i(1, 1, -1);
			glMultiTexCoord2fARB(GL_TEXTURE0_ARB, 0, 1);
			glMultiTexCoord2fARB(GL_TEXTURE1_ARB, 0, 1); glVertex3i(1, 1, 1);

			glNormal3f(-1.0, 0.0, 0.0);
			glMultiTexCoord2fARB(GL_TEXTURE0_ARB, 1, 1);
			glMultiTexCoord2fARB(GL_TEXTURE1_ARB, 1, 1); glVertex3i(-1, -1, 1);
			glMultiTexCoord2fARB(GL_TEXTURE0_ARB, 1, 0);
			glMultiTexCoord2fARB(GL_TEXTURE1_ARB, 1, 0); glVertex3i(-1, -1, -1);
			glMultiTexCoord2fARB(GL_TEXTURE0_ARB, 0, 0);
			glMultiTexCoord2fARB(GL_TEXTURE1_ARB, 0, 0); glVertex3i(-1, 1, -1);
			glMultiTexCoord2fARB(GL_TEXTURE0_ARB, 0, 1);
			glMultiTexCoord2fARB(GL_TEXTURE1_ARB, 0, 1); glVertex3i(-1, 1, 1);

			glNormal3f(0.0, 1.0, 0.0);
			glMultiTexCoord2fARB(GL_TEXTURE0_ARB, 1, 1);
			glMultiTexCoord2fARB(GL_TEXTURE1_ARB, 1, 1); glVertex3i(-1, 1, 1);
			glMultiTexCoord2fARB(GL_TEXTURE0_ARB, 1, 0);
			glMultiTexCoord2fARB(GL_TEXTURE1_ARB, 1, 0); glVertex3i(-1, 1, -1);
			glMultiTexCoord2fARB(GL_TEXTURE0_ARB, 0, 0);
			glMultiTexCoord2fARB(GL_TEXTURE1_ARB, 0, 0); glVertex3i(1, 1, -1);
			glMultiTexCoord2fARB(GL_TEXTURE0_ARB, 0, 1);
			glMultiTexCoord2fARB(GL_TEXTURE1_ARB, 0, 1); glVertex3i(1, 1, 1);

			glNormal3f(0.0, -1.0, 0.0);
			glMultiTexCoord2fARB(GL_TEXTURE0_ARB, 1, 1);
			glMultiTexCoord2fARB(GL_TEXTURE1_ARB, 1, 1); glVertex3i(-1, -1, 1);
			glMultiTexCoord2fARB(GL_TEXTURE0_ARB, 1, 0);
			glMultiTexCoord2fARB(GL_TEXTURE1_ARB, 1, 0); glVertex3i(-1, -1, -1);
			glMultiTexCoord2fARB(GL_TEXTURE0_ARB, 0, 0);
			glMultiTexCoord2fARB(GL_TEXTURE1_ARB, 0, 0); glVertex3i(1, -1, -1);
			glMultiTexCoord2fARB(GL_TEXTURE0_ARB, 0, 1);
			glMultiTexCoord2fARB(GL_TEXTURE1_ARB, 0, 1); glVertex3i(1, -1, 1);

			glEnd();

			glPopMatrix();

			glActiveTextureARB(GL_TEXTURE1_ARB);
			glDisable(GL_TEXTURE_2D);
			glActiveTextureARB(GL_TEXTURE0_ARB);
			glDisable(GL_TEXTURE_2D);
		}
		else {
			glActiveTextureARB(GL_TEXTURE0_ARB);
			glEnable(GL_TEXTURE_2D);
			glBindTexture(GL_TEXTURE_2D, texture[i]);  //ѡ������texture[1]

			glActiveTextureARB(GL_TEXTURE1_ARB);
			glEnable(GL_TEXTURE_2D);
			glBindTexture(GL_TEXTURE_2D, texture[j]);  //ѡ������texture[2]

			glPushMatrix();

			//������
			//�����ĳ�ı��Σ��������趨�������꣬������ʾ���������Ҫ�˲�
			glBegin(GL_QUADS);
			glNormal3f(0.0, 0.0, 1.0);
			glMultiTexCoord2fARB(GL_TEXTURE0_ARB, 1, 1);
			glMultiTexCoord2fARB(GL_TEXTURE1_ARB, 1, 1); glVertex3i(-1, 1, 1);
			glMultiTexCoord2fARB(GL_TEXTURE0_ARB, 1, 0);
			glMultiTexCoord2fARB(GL_TEXTURE1_ARB, 1, 0); glVertex3i(-1, -1, 1);
			glMultiTexCoord2fARB(GL_TEXTURE0_ARB, 0, 0);
			glMultiTexCoord2fARB(GL_TEXTURE1_ARB, 0, 0); glVertex3i(1, -1, 1);
			glMultiTexCoord2fARB(GL_TEXTURE0_ARB, 0, 1);
			glMultiTexCoord2fARB(GL_TEXTURE1_ARB, 0, 1); glVertex3i(1, 1, 1);

			glNormal3f(0.0, 0.0, -1.0);
			glMultiTexCoord2fARB(GL_TEXTURE0_ARB, 1, 1);
			glMultiTexCoord2fARB(GL_TEXTURE1_ARB, 1, 1);  glVertex3i(-1, 1, -1);
			glMultiTexCoord2fARB(GL_TEXTURE0_ARB, 1, 0);
			glMultiTexCoord2fARB(GL_TEXTURE1_ARB, 1, 0); glVertex3i(-1, -1, -1);
			glMultiTexCoord2fARB(GL_TEXTURE0_ARB, 0, 0);
			glMultiTexCoord2fARB(GL_TEXTURE1_ARB, 0, 0); glVertex3i(1, -1, -1);
			glMultiTexCoord2fARB(GL_TEXTURE0_ARB, 0, 1);
			glMultiTexCoord2fARB(GL_TEXTURE1_ARB, 0, 1); glVertex3i(1, 1, -1);

			glNormal3f(1.0, 0.0, 0.0);
			glMultiTexCoord2fARB(GL_TEXTURE0_ARB, 1, 1);
			glMultiTexCoord2fARB(GL_TEXTURE1_ARB, 1, 1);  glVertex3i(1, -1, 1);
			glMultiTexCoord2fARB(GL_TEXTURE0_ARB, 1, 0);
			glMultiTexCoord2fARB(GL_TEXTURE1_ARB, 1, 0); glVertex3i(1, -1, -1);
			glMultiTexCoord2fARB(GL_TEXTURE0_ARB, 0, 0);
			glMultiTexCoord2fARB(GL_TEXTURE1_ARB, 0, 0); glVertex3i(1, 1, -1);
			glMultiTexCoord2fARB(GL_TEXTURE0_ARB, 0, 1);
			glMultiTexCoord2fARB(GL_TEXTURE1_ARB, 0, 1); glVertex3i(1, 1, 1);

			glNormal3f(-1.0, 0.0, 0.0);
			glMultiTexCoord2fARB(GL_TEXTURE0_ARB, 1, 1);
			glMultiTexCoord2fARB(GL_TEXTURE1_ARB, 1, 1); glVertex3i(-1, -1, 1);
			glMultiTexCoord2fARB(GL_TEXTURE0_ARB, 1, 0);
			glMultiTexCoord2fARB(GL_TEXTURE1_ARB, 1, 0); glVertex3i(-1, -1, -1);
			glMultiTexCoord2fARB(GL_TEXTURE0_ARB, 0, 0);
			glMultiTexCoord2fARB(GL_TEXTURE1_ARB, 0, 0); glVertex3i(-1, 1, -1);
			glMultiTexCoord2fARB(GL_TEXTURE0_ARB, 0, 1);
			glMultiTexCoord2fARB(GL_TEXTURE1_ARB, 0, 1); glVertex3i(-1, 1, 1);

			glNormal3f(0.0, 1.0, 0.0);
			glMultiTexCoord2fARB(GL_TEXTURE0_ARB, 1, 1);
			glMultiTexCoord2fARB(GL_TEXTURE1_ARB, 1, 1); glVertex3i(-1, 1, 1);
			glMultiTexCoord2fARB(GL_TEXTURE0_ARB, 1, 0);
			glMultiTexCoord2fARB(GL_TEXTURE1_ARB, 1, 0); glVertex3i(-1, 1, -1);
			glMultiTexCoord2fARB(GL_TEXTURE0_ARB, 0, 0);
			glMultiTexCoord2fARB(GL_TEXTURE1_ARB, 0, 0); glVertex3i(1, 1, -1);
			glMultiTexCoord2fARB(GL_TEXTURE0_ARB, 0, 1);
			glMultiTexCoord2fARB(GL_TEXTURE1_ARB, 0, 1); glVertex3i(1, 1, 1);

			glNormal3f(0.0, -1.0, 0.0);
			glMultiTexCoord2fARB(GL_TEXTURE0_ARB, 1, 1);
			glMultiTexCoord2fARB(GL_TEXTURE1_ARB, 1, 1); glVertex3i(-1, -1, 1);
			glMultiTexCoord2fARB(GL_TEXTURE0_ARB, 1, 0);
			glMultiTexCoord2fARB(GL_TEXTURE1_ARB, 1, 0); glVertex3i(-1, -1, -1);
			glMultiTexCoord2fARB(GL_TEXTURE0_ARB, 0, 0);
			glMultiTexCoord2fARB(GL_TEXTURE1_ARB, 0, 0); glVertex3i(1, -1, -1);
			glMultiTexCoord2fARB(GL_TEXTURE0_ARB, 0, 1);
			glMultiTexCoord2fARB(GL_TEXTURE1_ARB, 0, 1); glVertex3i(1, -1, 1);

			glEnd();

			glPopMatrix();

			glActiveTextureARB(GL_TEXTURE1_ARB);
			glDisable(GL_TEXTURE_2D);
			glActiveTextureARB(GL_TEXTURE0_ARB);
			glDisable(GL_TEXTURE_2D);
		}



	}

}


void initLightbulbList() {
	glNewList(bulb[0], GL_COMPILE);
	GLUquadricObj* sphere = gluNewQuadric();
	gluQuadricNormals(sphere, GLU_SMOOTH);
	gluQuadricDrawStyle(sphere, GLU_FILL);
	gluQuadricTexture(sphere, GL_TRUE);
	glPushMatrix();
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, 0);  //ѡ������texture[1]
	gluSphere(sphere, 0.2, 50, 50);
	glDisable(GL_TEXTURE_2D);
	glPopMatrix();
	glEndList();
}

GLint initWindowList() {
	glNewList(window[0], GL_COMPILE);
	glPushMatrix();
	glEnable(GL_NORMALIZE); glScalef(0.0206f, 0.45f, 0.4f);
	Texture_cube(1, 6 - 1, 0, 0);
	glPopMatrix();
	glEndList();
	glNewList(window[1], GL_COMPILE);
	glPushMatrix();
	glEnable(GL_NORMALIZE); glScalef(0.0205f, 0.5f, 0.8f);
	Texture_cube(1, 17, 0, 0);
	glPopMatrix();
	glEndList();
	glNewList(window[2], GL_COMPILE);
	glPushMatrix();
	glEnable(GL_NORMALIZE); glScalef(0.0205f, 0.5f, 0.8f);
	Texture_cube(1, 18, 0, 0);
	glPopMatrix();
	glEndList();
	glNewList(window[3], GL_COMPILE);
	glPushMatrix();
	glEnable(GL_NORMALIZE); glScalef(0.0205f, 0.5f, 0.8f);
	Texture_cube(1, 17, 0, 0);
	glPopMatrix();
	glEndList();
	return 0;
}

//�ѻ������ŷ����б�,�������������
GLint initDoorList() {
	glNewList(door[0], GL_COMPILE);
	glPushMatrix();
	glEnable(GL_NORMALIZE); glScalef(0.0205f, 0.6f, 0.3f);
	Texture_cube(1, 4 - 1, 0, 0);
	glPopMatrix();
	glEndList();
	glNewList(door[1], GL_COMPILE);
	glPushMatrix();
	glEnable(GL_NORMALIZE); glScalef(0.3f, 0.6f, 0.0205f);
	Texture_cube(1, 3 - 1, 0, 0);
	glPopMatrix();
	glEndList();
	glNewList(outside[0], GL_COMPILE);
	glPushMatrix();
	glEnable(GL_NORMALIZE); glScalef(0.0202f, 0.6f, 0.3f);
	Texture_cube(1, 15, 0, 0);
	glPopMatrix();
	glEndList();
	glNewList(outside[1], GL_COMPILE);
	glPushMatrix();
	glEnable(GL_NORMALIZE); glScalef(0.3f, 0.6f, 0.0202f);
	Texture_cube(1, 16, 0, 0);
	glPopMatrix();
	glEndList();
	glNewList(door_edge[0], GL_COMPILE);
	glPushMatrix();
	glEnable(GL_NORMALIZE); glScalef(0.03f, 0.65f, 0.03f);
	Texture_cube(1, 13 - 1, 0, 0);
	glPopMatrix();
	glEndList();
	glNewList(door_edge[1], GL_COMPILE);
	glPushMatrix();
	glEnable(GL_NORMALIZE); glScalef(0.03f, 0.03f, 0.31f);
	Texture_cube(1, 10 - 1, 0, 0);
	glPopMatrix();
	glEndList();
	glNewList(door_edge[2], GL_COMPILE);
	glPushMatrix();
	glEnable(GL_NORMALIZE); glScalef(0.31f, 0.03f, 0.03f);
	Texture_cube(1, 11 - 1, 0, 0);
	glPopMatrix();
	glEndList();
	glNewList(door_edge[3], GL_COMPILE);
	glPushMatrix();
	glEnable(GL_NORMALIZE); glScalef(0.03f, 0.65f, 0.03f);
	Texture_cube(1, 12 - 1, 0, 0);
	glPopMatrix();
	glEndList();
	return 0;
}

//ǽ���б�
GLint initWallList() {//�ѻ�����ǽ��Ԫ�����б�
	static GLfloat wall_mat0[] =
	{ 1.f, .5f, 0.f, 1.f };
	static GLfloat wall_mat1[] =
	{ 0.f, .5f, 1.f, 1.f };
	static GLfloat wall_mat2[] =
	{ 1.f, .0f, 0.f, 1.f };


	glNewList(wall[0], GL_COMPILE);//�ذ�
	glPushMatrix();
	GLfloat floor_mat_specular[] = { 0.90, 0.80, 0.60, 1.0 };	         // ���淴����ɫ
	GLfloat floor_mat_shininess[] = { 50.0 };							// ���淴�����
	GLfloat floor_lmodel_ambient[] = { 0.86, 0.73, 0.54, 1.0 };		// ɢ����ɫΪ220, 186, 138
	GLfloat floor_lmodel_emmision[] = { 0.0, 0.0, 0.0, 1.0 };

	glMaterialfv(GL_FRONT, GL_SPECULAR, floor_mat_specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, floor_mat_shininess);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, floor_lmodel_ambient);
	glMaterialfv(GL_FRONT, GL_EMISSION, floor_lmodel_emmision);
	glEnable(GL_NORMALIZE); glScalef(0.1f, 0.1f, 4.0f);
	Texture_cube(1, 1 - 1, 0, 0);
	glPopMatrix();
	glEndList();
	glNewList(wall[1], GL_COMPILE);//�컨��
	glPushMatrix();
	GLfloat ceiling_mat_specular[] = { 0.85, 0.85, 0.85, 1.0 };	         // ���淴����ɫ
	GLfloat ceiling_mat_shininess[] = { 50.0 };							// ���淴�����
	GLfloat ceiling_lmodel_ambient[] = { 0.79, 0.79, 0.79, 1.0 };		// ɢ����ɫ
	GLfloat ceiling_lmodel_emmision[] = { 0.0, 0.0, 0.0, 1.0 };

	glMaterialfv(GL_FRONT, GL_SPECULAR, ceiling_mat_specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, ceiling_mat_shininess);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, ceiling_lmodel_ambient);
	glMaterialfv(GL_FRONT, GL_EMISSION, ceiling_lmodel_emmision);
	glEnable(GL_NORMALIZE); glScalef(0.1f, 0.1f, 4.0f);
	Texture_cube(1, 5 - 1, 0, 0);
	glPopMatrix();
	glEndList();

	glNewList(wall[2], GL_COMPILE); // ǽ
	glPushMatrix();
	GLfloat wall_mat_specular[] = { 0.85, 0.85, 0.85, 1.0 };	         // ���淴����ɫ
	GLfloat wall_mat_shininess[] = { 50.0 };							// ���淴�����
	GLfloat wall_lmodel_ambient[] = { 0.79, 0.79, 0.79, 1.0 };		// ɢ����ɫ
	GLfloat wall_lmodel_emmision[] = { 0.0, 0.0, 0.0, 1.0 };

	glMaterialfv(GL_FRONT, GL_SPECULAR, wall_mat_specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, wall_mat_shininess);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, wall_lmodel_ambient);
	glMaterialfv(GL_FRONT, GL_EMISSION, wall_lmodel_emmision);
	glEnable(GL_NORMALIZE); glScalef(0.02f, 1.0f, 0.02f);
	Texture_cube(1, 5 - 1, 0, 0);
	glPopMatrix();
	glEndList();
	return wall[0];
}

//void initEnvironment()
//{
//	GLUquadricObj* sphere, * cone, * base;
//	static GLfloat sphere_mat[] =
//	{ 1.f, .5f, 0.f, 1.f };
//	static GLfloat cone_mat[] =
//	{ 0.f, .5f, 1.f, 1.f };
//	static GLfloat sphere_mat2[] =
//	{ 1.f, .0f, 0.f, 1.f };
//	static GLfloat cone_mat2[] =
//	{ 1.f, .0f, 0.f, 1.f };
//
//	glNewList(snowManHeadDL, GL_COMPILE);
//	cone = gluNewQuadric();
//	base = gluNewQuadric();
//	glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, cone_mat);
//	glRotatef(-90.f, 1.f, 0.f, 0.f);
//	gluDisk(base, 0., 0.2, 0.2, 1);
//	gluCylinder(cone, 0.2, 0, 0.4, 10, 10);
//	gluDeleteQuadric(cone);
//	gluDeleteQuadric(base);
//	glEndList();
//
//	glNewList(snowManBodyDL, GL_COMPILE);
//	sphere = gluNewQuadric();
//	glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, sphere_mat);
//	gluSphere(sphere, 0.2, 10, 10);
//	gluDeleteQuadric(sphere);
//	glEndList();
//
//	glNewList(snowManHeadDL2, GL_COMPILE);
//	cone = gluNewQuadric();
//	base = gluNewQuadric();
//	glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, cone_mat2);
//	glRotatef(-90.f, 1.f, 0.f, 0.f);
//	gluDisk(base, 0., 0.2, 0.2, 1);
//	gluCylinder(cone, 0.2, 0, 0.4, 10, 10);
//	gluDeleteQuadric(cone);
//	gluDeleteQuadric(base);
//	glEndList();
//
//	glNewList(snowManBodyDL2, GL_COMPILE);
//	sphere = gluNewQuadric();
//	glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, sphere_mat2);
//	gluSphere(sphere, 0.2, 10, 10);
//	gluDeleteQuadric(sphere);
//	glEndList();
//
//}

//���ӵ��б�
GLint initClosetList() {
	//����ǹ��ӵ�����
	glNewList(closet[0], GL_COMPILE);
	GLfloat closet_mat_specular[] = { 0.90, 0.90, 0.90, 1.0 };	         // ���淴����ɫ
	GLfloat closet_mat_shininess[] = { 50.0 };							// ���淴�����
	GLfloat closet_lmodel_ambient[] = { 0.85, 0.85, 0.85, 1.0 };		// ɢ����ɫ
	GLfloat closet_lmodel_emmision[] = { 0.0, 0.0, 0.0, 1.0 };

	glMaterialfv(GL_FRONT, GL_SPECULAR, closet_mat_specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, closet_mat_shininess);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, closet_lmodel_ambient);
	glMaterialfv(GL_FRONT, GL_EMISSION, closet_lmodel_emmision);
	glEnable(GL_NORMALIZE); glScalef(0.02f, 0.8f, 0.6f);
	Texture_cube(1, 8 - 1, 0, 0);
	glEndList();
	//����ǹ��ӵĲ���
	glNewList(closet[1], GL_COMPILE);

	glMaterialfv(GL_FRONT, GL_SPECULAR, closet_mat_specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, closet_mat_shininess);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, closet_lmodel_ambient);
	glMaterialfv(GL_FRONT, GL_EMISSION, closet_lmodel_emmision);
	glEnable(GL_NORMALIZE); glScalef(0.15f, 0.8f, 0.02f);
	Texture_cube(1, 9 - 1, 0, 0);
	glEndList();
	//����ǹ��ӵ�����
	glNewList(closet[2], GL_COMPILE);
	glMaterialfv(GL_FRONT, GL_SPECULAR, closet_mat_specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, closet_mat_shininess);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, closet_lmodel_ambient);
	glMaterialfv(GL_FRONT, GL_EMISSION, closet_lmodel_emmision);
	glEnable(GL_NORMALIZE); glScalef(0.15f, 0.02f, 0.6f);
	Texture_cube(1, 9 - 1, 0, 0);
	glEndList();
	return 0;
}

void DrawRobot1(Robot_2* robot);
void DrawRobot2(Robot_1* robot);

void draw() {
	drawNurbs(7.5, 0, 2.5);
	drawWall();
	drawDoor();
	drawWindow();
	drawLightbulb();
	drawCloset();
	drawGlass();
	drawBoard();
	//drawDesk();/////////////////////////////////////////��ʱע�͵������ӣ����ᵼ�º���Ļ�е�ۻ���������bug�����
	robot21.Draw();
	robot22.Draw();
	//conv1.draw();
	//conv1.Move();

	
	robot1.Draw();

	//shape
	//s1.Draw();
	//s2.Draw();
	//s3.Draw();
	//s4.Draw();
}
void drawoneDesk() {
	glPushMatrix();
	GLfloat desk_mat_specular[] = { 0.92, 0.65, 0.35, 1.0 };	         // ���淴����ɫ
	GLfloat desk_mat_shininess[] = { 50.0 };							// ���淴�����
	GLfloat desk_lmodel_ambient[] = { 0.84, 0.55, 0.25, 1.0 };		// ɢ����ɫ
	GLfloat desk_lmodel_emmision[] = { 0.0, 0.0, 0.0, 1.0 };

	glMaterialfv(GL_FRONT, GL_SPECULAR, desk_mat_specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, desk_mat_shininess);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, desk_lmodel_ambient);
	glMaterialfv(GL_FRONT, GL_EMISSION, desk_lmodel_emmision);
	glTranslatef(-0.25, 0.3, -0.15);
	glEnable(GL_NORMALIZE);
	glScalef(0.02f, 0.3f, 0.02f);
	Texture_cube(1, 2 - 1, 0, 0);
	glPopMatrix();

	glPushMatrix();
	glMaterialfv(GL_FRONT, GL_SPECULAR, desk_mat_specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, desk_mat_shininess);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, desk_lmodel_ambient);
	glMaterialfv(GL_FRONT, GL_EMISSION, desk_lmodel_emmision);
	glTranslatef(-0.25, 0.3, 0.15);
	glEnable(GL_NORMALIZE);
	glScalef(0.02f, 0.3f, 0.02f);
	Texture_cube(1, 2 - 1, 0, 0);
	glPopMatrix();

	glPushMatrix();
	glMaterialfv(GL_FRONT, GL_SPECULAR, desk_mat_specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, desk_mat_shininess);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, desk_lmodel_ambient);
	glMaterialfv(GL_FRONT, GL_EMISSION, desk_lmodel_emmision);
	glTranslatef(0.25, 0.3, -0.15);
	glEnable(GL_NORMALIZE);
	glScalef(0.02f, 0.3f, 0.02f);
	Texture_cube(1, 2 - 1, 0, 0);
	glPopMatrix();

	glPushMatrix();
	glMaterialfv(GL_FRONT, GL_SPECULAR, desk_mat_specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, desk_mat_shininess);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, desk_lmodel_ambient);
	glMaterialfv(GL_FRONT, GL_EMISSION, desk_lmodel_emmision);
	glTranslatef(0.25, 0.3, 0.15);
	glEnable(GL_NORMALIZE);
	glScalef(0.02f, 0.3f, 0.02f);
	Texture_cube(1, 2 - 1, 0, 0);
	glPopMatrix();

	glPushMatrix();
	glMaterialfv(GL_FRONT, GL_SPECULAR, desk_mat_specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, desk_mat_shininess);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, desk_lmodel_ambient);
	glMaterialfv(GL_FRONT, GL_EMISSION, desk_lmodel_emmision);
	glTranslatef(0, 0.6, 0);
	glEnable(GL_NORMALIZE);	
	glScalef(0.3f, 0.01f, 0.2f);
	Texture_cube(1, 2 - 1, 0, 0);
	glPopMatrix();

	glPushMatrix();
}
void drawDesk() {
	glPushMatrix();
	glTranslatef(7.5, 0, 2.5);
	glRotatef(90, 0, 1, 0);
	drawoneDesk();
	glPopMatrix();
}
//����һ�����
void drawoneboard() {
	glPushMatrix();
	GLfloat board_mat_specular[] = { 0.92, 0.65, 0.35, 1.0 };	         // ���淴����ɫ
	GLfloat board_mat_shininess[] = { 50.0 };							// ���淴�����
	GLfloat board_lmodel_ambient[] = { 0.84, 0.55, 0.25, 1.0 };		// ɢ����ɫ
	GLfloat board_lmodel_emmision[] = { 0.0, 0.0, 0.0, 1.0 };

	glMaterialfv(GL_FRONT, GL_SPECULAR, board_mat_specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, board_mat_shininess);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, board_lmodel_ambient);
	glMaterialfv(GL_FRONT, GL_EMISSION, board_lmodel_emmision);
	glTranslatef(0, 0.55, 0);
	glEnable(GL_NORMALIZE); glScalef(0.5f, 0.25f, 0.05f);
	Texture_cube(1, 2 - 1, 0, 0);
	glPopMatrix();
	glPushMatrix();
	GLfloat rabbit_mat_specular[] = { 0.80, 0.90, 0.98, 1.0 };	         // ���淴����ɫ
	GLfloat rabbit_mat_shininess[] = { 50.0 };							// ���淴�����
	GLfloat rabbit_lmodel_ambient[] = { 0.70, 0.82, 0.89, 1.0 };		// ɢ����ɫ
	GLfloat rabbit_lmodel_emmision[] = { 0.0, 0.0, 0.0, 1.0 };

	glMaterialfv(GL_FRONT, GL_SPECULAR, rabbit_mat_specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, rabbit_mat_shininess);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, rabbit_lmodel_ambient);
	glMaterialfv(GL_FRONT, GL_EMISSION, rabbit_lmodel_emmision);
	glTranslatef(0, 0.55, -0.06);
	glEnable(GL_NORMALIZE); 
	glScalef(0.48f, 0.24f, 0.001f);
	if(!boardmode)Texture_cube(1, 13, 0, 0);
	else {
		Texture_cube(1, 28 + boardnum, 0, 0);
		boardcounter += 1;
		if (boardcounter == 100) {
			boardnum += 1;
			boardcounter = 0;
		}
		if (boardnum == 4) {
			boardnum = 0;
			boardmode = false;
		}
	}
	glPopMatrix();
	glPushMatrix();
	glMaterialfv(GL_FRONT, GL_SPECULAR, board_mat_specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, board_mat_shininess);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, board_lmodel_ambient);
	glMaterialfv(GL_FRONT, GL_EMISSION, board_lmodel_emmision);
	glTranslatef(0, 0.2, 0);
	glEnable(GL_NORMALIZE); glScalef(0.05f, 0.15f, 0.04f);
	Texture_cube(1, 2 - 1, 0, 0);
	glPopMatrix();
	glMaterialfv(GL_FRONT, GL_SPECULAR, board_mat_specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, board_mat_shininess);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, board_lmodel_ambient);
	glMaterialfv(GL_FRONT, GL_EMISSION, board_lmodel_emmision);
	glTranslatef(0, 0.05, 0);
	glEnable(GL_NORMALIZE); glScalef(0.15f, 0.05f, 0.05f);
	Texture_cube(1, 2 - 1, 0, 0);
	glPopMatrix();
}

//�����л��ƹ���
void drawBoard() {
	glPushMatrix();
	glTranslatef(1, 0.1, 2.5);
	drawoneboard();
	glPopMatrix();
}

//����һ�鲣����
void drawGlass() {
	glPushMatrix();
	GLfloat mat_specular[] = { 1., 1., 1., 1.0 };	         // ���淴����ɫ
	GLfloat mat_shininess[] = { 50.0 };							// ���淴�����
	GLfloat lmodel_ambient[] = { 1., 1., 1., 1.0 };		// ɢ����ɫ
	GLfloat lmodel_emmision[] = { 0.0, 0.0, 0.0, 1.0 };

	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, lmodel_ambient);
	glMaterialfv(GL_FRONT, GL_EMISSION, lmodel_emmision);
	glTranslatef(4.0, 1.0, 3.0);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glDepthMask(GL_FALSE);
	glDisable(GL_LIGHTING);
	glColor4f(1.0, 1.0, 1.0, 0.2);
	glEnable(GL_NORMALIZE); glScalef(8.0, 2.0, 0.01);
	glutSolidCube(1.0);
	glDisable(GL_BLEND);
	glEnable(GL_LIGHTING);
	glDepthMask(GL_TRUE);
	glPopMatrix();
}

//����һ������
void drawonecloset() {
	//����ǹ��ӵ�����
	glPushMatrix();
	glTranslatef(0, 0.2, 0);
	glPushMatrix();
	glTranslatef(0.14, 0, 0);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glCallList(closet[0]);
	glPopMatrix();
	//����ǹ��ӵı���
	glPushMatrix();
	glTranslatef(-0.14, 0, 0);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glCallList(closet[0]);
	glPopMatrix();
	//����ǹ��ӵĲ���
	glPushMatrix();
	glTranslatef(0, 0, 0.59);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glCallList(closet[1]);
	glPopMatrix();
	//����ǹ��ӵĲ���
	glPushMatrix();
	glTranslatef(0, 0, -0.59);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glCallList(closet[1]);
	glPopMatrix();
	//����ǹ��ӵ�����
	glPushMatrix();
	glTranslatef(0, 0.79, 0);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glCallList(closet[2]);
	glPopMatrix();
	glPopMatrix();
}

//�ڳ����л��ƹ���
void drawCloset() {
	glPushMatrix();
	glTranslatef(3.7f, 0.7f, 1.0f);
	drawonecloset();
	glTranslatef(0.7f, 0, 0);
	drawonecloset();
	glTranslatef(0.7f, 0, 0);
	drawonecloset();
	glTranslatef(0.7f, 0, 0);
	drawonecloset();
	glTranslatef(0.7f, 0, 0);
	drawonecloset();
	glTranslatef(0.7f, 0, 0);
	drawonecloset();
	glTranslatef(0.7f, 0, 0);
	drawonecloset();
	glPopMatrix();
}

//���Ƶ���
void drawLightbulb() {
	glPushMatrix();
	glTranslatef(1.6, 2., 1.6);
	for (int i = 0; i < 4; i++) {
		glPushMatrix();
		glTranslatef(1.6 * i, 0, 0);
		for (int k = 0; k < 4; k++) {
			glPushMatrix();
			if (k == i) {
				GLfloat lmodel_emmision[] = { 1.0, 1.0, 1.0, 1.0 };
				glMaterialfv(GL_FRONT, GL_EMISSION, lmodel_emmision);
			}
			else {
				GLfloat lmodel_emmision[] = { 0.0, 0.0, 0.0, 1.0 };
				glMaterialfv(GL_FRONT, GL_EMISSION, lmodel_emmision);
			}
			glTranslatef(0, 0, k * 1.6);
			glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
			glCallList(bulb[0]);
			glPopMatrix();
		}
		glPopMatrix();
	}
	glPopMatrix();
	GLfloat lmodel_emmision[] = { 0.0, 0.0, 0.0, 1.0 };
	glMaterialfv(GL_FRONT, GL_EMISSION, lmodel_emmision);
}

//���ƴ�
void drawoneWindow(int i) {
	glCallList(window[i + 1]);
	glPushMatrix();
	glTranslatef(0, 0.0043, window_pos[i]);
	glCallList(window[0]);
	glPopMatrix();
}
void drawWindow() {
	glPushMatrix();
	glTranslatef(8.0, 1.0, 2.0);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	drawoneWindow(0);
	if (window_pos[0] <= 0.35 && window_pos_on[0]) window_pos[0] += 0.002;
	if (window_pos[0] >= -0.35 && !window_pos_on[0]) window_pos[0] -= 0.002;
	glTranslatef(0.0, 0.0, 2.0);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	drawoneWindow(1);
	if (window_pos[1] <= 0.35 && window_pos_on[1]) window_pos[1] += 0.002;
	if (window_pos[1] >= -0.35 && !window_pos_on[1])window_pos[1] -= 0.002;
	glTranslatef(0.0, 0.0, 2.0);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	drawoneWindow(2);
	if (window_pos[2] <= 0.35 && window_pos_on[2]) window_pos[2] += 0.002;
	if (window_pos[2] >= -0.35 && !window_pos_on[2])window_pos[2] -= 0.002;
	glPopMatrix();
}

void drawOutsideDoor_1() {
	glPushMatrix();
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glCallList(outside[0]);//0.02,0.6,0.3
	glPopMatrix();
	glPushMatrix();
	glTranslatef(0, 0, -0.32);
	glCallList(door_edge[0]);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(0, 0, 0.32);
	glCallList(door_edge[0]);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(0, 0.62, 0);
	glCallList(door_edge[1]);
	glPopMatrix();
}

void drawOutsideDoor_2() {
	glPushMatrix();
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glCallList(outside[1]);//0.02,0.6,0.3
	glPopMatrix();
	glPushMatrix();
	glTranslatef(-0.32, 0, 0);
	glCallList(door_edge[3]);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(0.32, 0, 0);
	glCallList(door_edge[3]);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(0, 0.62, 0);
	glCallList(door_edge[2]);
	glPopMatrix();
}

//������
void drawDoor() {
	glPushMatrix();
	glTranslatef(0.0, 0.7, 5.3);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	drawOutsideDoor_1();
	glPopMatrix();
	glPushMatrix();
	glTranslatef(1.3, 0.7, 0.0);
	drawOutsideDoor_2();
	glPopMatrix();
	glPushMatrix();
	glTranslatef(0.02, 0.7, 5.0);
	glRotatef(r_door[0], 0, 1, 0);//-180~-90
	if (r_door[0] < -45 && r_door_on[0]) r_door[0]++;
	if (r_door[0] >= -180 && !r_door_on[0]) r_door[0]--;
	glTranslatef(0.0, 0.0, -0.3);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glCallList(door[0]);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(1.0, 0.7, 0.02);
	glRotatef(r_door[1], 0, 1, 0);//-180~-90
	if (r_door[1] < 0 && r_door_on[1]) r_door[1]++;
	if (r_door[1] >= -135 && !r_door_on[1]) r_door[1]--;
	glTranslatef(0.3, 0.0, 0.0);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glCallList(door[1]);
	glPopMatrix();
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}

void setWall() {
	GLfloat mat_specular[] = { 0.82, 0.93, 0.95, 1.0 };         // ���淴����ɫ
	GLfloat mat_shininess[] = { 50.0 };							// ���淴�����
	GLfloat lmodel_ambient[] = { 0.84, 0.91, 0.92, 1.0 };		// ɢ����ɫΪǳ��ɫ
	GLfloat lmodel_emmision[] = { 0.0, 0.0, 0.0, 1.0 };

	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, lmodel_ambient);
	glMaterialfv(GL_FRONT, GL_EMISSION, lmodel_emmision);
}
GLUnurbsObj* theNurb1;
GLUnurbsObj* theNurb2;
GLfloat ctrlpoints[5][5][3] = { 
{{1.5,-3.5, 2},{2,-1.5, 2},{1,-2, 2},{4,1, 2},{-2,0, 2}},
{{1.5,-3.5, 1},{2,-1.5, 1},{1,-2, 1},{4,1, 1},{-2,0, 1}},
{{1.5,-3.5, 0},{2,-1.5, 0},{1,-2, 0},{4,1, 0},{-2,0, 0}},
{{1.5,-3.5,-1},{2,-1.5,-1},{1,-2,-1},{4,1,-1},{-2,0,-1}},
{{1.5,-3.5,-2},{2,-1.5,-2},{1,-2,-2},{4,1,-2},{-2,0,-2}} };//���Ƶ�

void initNurbs() {
	glPushMatrix();
	glClearColor(1.0, 1.0, 1.0, 0.0);//���ñ���ɫ
	glNewList(nurbs[0], GL_COMPILE);
 /*Ϊ����ģ��ָ�����ʲ���*/
	GLfloat mat_diffuse[] = { 1.0,0.5,0.1,1.0 };
	GLfloat mat_specular[] = { 1.0,1.0,1.0,1.0 };
	GLfloat mat_shininess[] = { 100.0 };
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
	/*��������Ч��*/
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glHint(GL_LINE_SMOOTH_HINT, GL_DONT_CARE);
	glEnable(GL_BLEND);
	glFrontFace(GL_CW);
	glShadeModel(GL_SMOOTH);
	glEnable(GL_LINE_SMOOTH);
	theNurb1 = gluNewNurbsRenderer();//����NURBS����theNurb1
	gluNurbsProperty(theNurb1, GLU_SAMPLING_TOLERANCE, 25.0);
	glLineWidth(2.0);
	gluNurbsProperty(theNurb1, GLU_DISPLAY_MODE, GLU_OUTLINE_POLYGON);
	theNurb2 = gluNewNurbsRenderer();//����NURBS����theNurb2
	gluNurbsProperty(theNurb2, GLU_SAMPLING_TOLERANCE, 25.0);
	gluNurbsProperty(theNurb2, GLU_DISPLAY_MODE, GLU_FILL);
	GLfloat knots[10] = { 0.0,0.0,0.0,0.0,0.0,1.0,1.0,1.0,1.0,1.0 };
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	/*��һ������*/
	gluBeginSurface(theNurb1);
	/*����������״*/
	gluNurbsSurface(theNurb1, 10, knots, 10, knots, 5 * 3, 3, &ctrlpoints[0][0][0], 5, 5, GL_MAP2_VERTEX_3);
	gluEndSurface(theNurb1);
	glPopMatrix();
	glEndList();
}
void drawNurbs(float x,float y,float z) {
	glPushMatrix();
	glTranslatef(x,y,z);
	glTranslatef(0.1, 0.62, 0.15);
	glRotatef(270, 0, 1, 0);
	glScalef(0.1, 0.05, 0.05);
	glCallList(nurbs[0]);
	glPopMatrix();
}

//����ǽ��
void drawWall() {
	glPushMatrix();
	glTranslatef(0, 1, 0);
	for (int k = 0; k < 200; k++) {
		glPushMatrix();
		glTranslatef(0, 0, k * 0.04);
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		glCallList(wall[2]);
		glPopMatrix();
	}
	for (int k = 0; k < 200; k++) {
		glPushMatrix();
		glTranslatef(k * 0.04, 0, 0);
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		glCallList(wall[2]);
		glPopMatrix();
	}
	glTranslatef(8.0, 0.0, 8.0);
	for (int k = 0; k < 200; k++) {
		glPushMatrix();
		glTranslatef(0, 0, -k * 0.04);
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		glCallList(wall[2]);
		glPopMatrix();
	}
	for (int k = 0; k < 200; k++) {
		glPushMatrix();
		glTranslatef(-k * 0.04, 0, 0);
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		glCallList(wall[2]);
		glPopMatrix();
	}
	glTranslatef(-8.0, -1.0, -4.0);
	for (int k = 0; k < 40; k++) {//�ذ�
		glPushMatrix();
		glTranslatef(k * 0.2, 0, 0);
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		glCallList(wall[0]);
		glPopMatrix();
	}
	glTranslatef(0.0, 2.0, 0.0);
	for (int k = 0; k < 40; k++) {//�컨��
		glPushMatrix();
		glTranslatef(k * 0.2, 0, 0);
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		glCallList(wall[1]);
		glPopMatrix();
	}
	glPopMatrix();
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}

//��е��2
void DrawRobot2(Robot_1* robot)
{
	robot->update();

	glPushMatrix();
	GLfloat mat_specular[] = { 1., 1., 1., 1.0 };	         // ���淴����ɫ
	GLfloat mat_shininess[] = { 50.0 };							// ���淴�����
	GLfloat lmodel_ambient[] = { 1., 1., 1., 1.0 };		// ɢ����ɫ
	GLfloat lmodel_emmision[] = { 0.0, 0.0, 0.0, 1.0 };

	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, lmodel_ambient);
	glMaterialfv(GL_FRONT, GL_EMISSION, lmodel_emmision);
	glTranslatef(3, 2, 4);
	glEnable(GL_NORMALIZE); glScalef(0.2, 0.2, 0.2);
	glEnable(GL_NORMALIZE); glScalef(0.5, 0.5, 0.5);
	robot->Draw();
	glPopMatrix();
	glPopMatrix();
}
