/* 
 *@author: Zhang Shenke，Bao Dezheng
 *@date: 2022/1/27  
 *@description: 绘制环境的相应函数
 */
#include "drawEnvironment.h"


GLubyte image[imageheight][imageweight][3];

unsigned int texture[50];
extern float move;
extern int count;
bool boardmode = true;
int boardnum;
int boardcounter;

extern GLfloat global_diffuse[];
extern bool global_light_enable[];
// 修改公告板的纹理
void  Change_Rust() {
	boardmode = !boardmode;
}
// 从数据文件中装载纹理数据
unsigned char* LoadBitmapFile(char* filename, BITMAPINFOHEADER* bitmapInfoHeader)
{
	FILE* fp;
	BITMAPFILEHEADER fh;	
	unsigned char* img;	
	int	imgidx = 0;	
	unsigned char tempRGB;
	fopen_s(&fp, filename, "rb");
	if (fp == NULL) return NULL;
	fread(&fh, sizeof(BITMAPFILEHEADER), 1, fp);
	if (fh.bfType != BITMAP_ID) {
		return NULL;
	}
	fread(bitmapInfoHeader, sizeof(BITMAPINFOHEADER), 1, fp);
	fseek(fp, fh.bfOffBits, SEEK_SET);
	img = new unsigned char[bitmapInfoHeader->biSizeImage];
	if (!img) {
		return NULL;
	}
	fread(img, 1, bitmapInfoHeader->biSizeImage, fp);
	if (img == NULL) {
		return NULL;
	}
	for (imgidx = 0;imgidx < bitmapInfoHeader->biSizeImage; imgidx += 3) {
		tempRGB = img[imgidx];
		img[imgidx] = img[imgidx + 2];
		img[imgidx + 2] = tempRGB;
	}
	fclose(fp);
	return img;
}
// 装载纹理
void texload(int i, char* filename)
{
	BITMAPINFOHEADER bitmapInfoHeader;    
	unsigned char* bitmapData;          
	bitmapData = LoadBitmapFile(filename, &bitmapInfoHeader);
	glBindTexture(GL_TEXTURE_2D, texture[i]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

	glTexImage2D(GL_TEXTURE_2D,
		0,
		GL_RGB,	
		bitmapInfoHeader.biWidth, 
		bitmapInfoHeader.biHeight, 
		0,
		GL_RGB,
		GL_UNSIGNED_BYTE, 
		bitmapData);
}
GLint wall[10] = { 5,6,7 };
GLint door[2] = { 27,9 };
GLint window[4] = { 10,23,24,25 };
GLint bulb[2] = { 11 };
GLint closet[3] = { 12,13,14 };
GLint desk[2] = { 26 };
GLint Robot = 15;
GLint outside[2] = { 17,18 };
GLint door_edge[4] = { 19,20,21,22 };
GLint nurbs[5] = { 28,29,30 };
GLint tile[64];
GLfloat r_door[2] = { -180,0 };
bool r_door_on[2] = { false,true };
float window_pos[3] = { -0.35,-0.35,-0.35 };
bool window_pos_on[3] = { false,false,false };
// 修改1号门开闭状态
bool Change_Door_1() {
	r_door_on[0] = !r_door_on[0];
	return r_door_on[0];
}
// 修改2号门开闭状态
void Change_Door_2() {
	r_door_on[1] = !r_door_on[1];
}
// 修改窗开闭状态
void Change_Window(int i) {
	window_pos_on[i] = !window_pos_on[i];
}
// 初始化列表
void InitList() {
	initTexture();
	initNurbs();
	initTile();
	initDesk();
	initDoorList();
	initLightbulbList();
	initWindowList();
	initWallList();
	initClosetList();
	boardnum = 0;
	boardcounter = 0;
}
// 初始化纹理
void initTexture() {
	glGenTextures(100, texture);
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
	texload(19, (char*)"./texture/box11.bmp");
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
	texload(32, (char*)"./texture/mk2.bmp");
	texload(33, (char*)"./texture/27.bmp");
	texload(34, (char*)"./texture/28.bmp");
	texload(35, (char*)"./texture/yb0.bmp");
	texload(36, (char*)"./texture/yb1.bmp");
	texload(37, (char*)"./texture/yb2.bmp");
	texload(38, (char*)"./texture/yb3.bmp");
	texload(39, (char*)"./texture/yb4.bmp");
	texload(40, (char*)"./texture/yb5.bmp");
	texload(41, (char*)"./texture/yb6.bmp");
	texload(42, (char*)"./texture/xl0.bmp");
	texload(43, (char*)"./texture/xl1.bmp");
	texload(44, (char*)"./texture/xl2.bmp");
	texload(45, (char*)"./texture/box0.bmp");
	texload(46, (char*)"./texture/box1.bmp");
	texload(47, (char*)"./texture/box00.bmp");
	texload(48, (char*)"./texture/box10.bmp");
	texload(49, (char*)"./texture/box01.bmp");
	texload(50, (char*)"./texture/box11.bmp");
	const GLubyte* extensions = glGetString(GL_EXTENSIONS);
	bool multiTexturingSupported = strstr((const char*)extensions, "GL_ARB_multitexture ") != NULL;

	GLint maxTextureUnits = 0;
	glGetIntegerv(GL_MAX_TEXTURE_UNITS_ARB, &maxTextureUnits);
	// 允许多重纹理映射
	glMultiTexCoord1fARB = (PFNGLMULTITEXCOORD1FARBPROC)wglGetProcAddress("glMultiTexCoord1fARB");
	glMultiTexCoord2fARB = (PFNGLMULTITEXCOORD2FARBPROC)wglGetProcAddress("glMultiTexCoord2fARB");
	glMultiTexCoord3fARB = (PFNGLMULTITEXCOORD3FARBPROC)wglGetProcAddress("glMultiTexCoord3fARB");
	glMultiTexCoord4fARB = (PFNGLMULTITEXCOORD4FARBPROC)wglGetProcAddress("glMultiTexCoord4fARB");
	glActiveTextureARB = (PFNGLACTIVETEXTUREARBPROC)wglGetProcAddress("glActiveTextureARB");
	glClientActiveTextureARB = (PFNGLCLIENTACTIVETEXTUREARBPROC)wglGetProcAddress("glClientActiveTextureARB");
}
// 绘制带纹理的立方体
void Texture_cube(int n, int i, int j, int k){
	if (n == 1) {
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, texture[i]); 
		glPushMatrix();
		glBegin(GL_QUADS);
		glNormal3f(0.0, 0.0, 1.0);
		// 将纹理绑定到各坐标上
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

		glDisable(GL_TEXTURE_2D);	
	}
	else {
		if (n == 3) {
			glActiveTextureARB(GL_TEXTURE0_ARB);
			glEnable(GL_TEXTURE_2D);
			glBindTexture(GL_TEXTURE_2D, texture[i]); 

			glActiveTextureARB(GL_TEXTURE1_ARB);
			glEnable(GL_TEXTURE_2D);
			glBindTexture(GL_TEXTURE_2D, texture[j]); 

			glActiveTextureARB(GL_TEXTURE1_ARB);
			glEnable(GL_TEXTURE_2D);
			glBindTexture(GL_TEXTURE_2D, texture[k]); 

			glPushMatrix();

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
			glBindTexture(GL_TEXTURE_2D, texture[i]); 

			glActiveTextureARB(GL_TEXTURE1_ARB);
			glEnable(GL_TEXTURE_2D);
			glBindTexture(GL_TEXTURE_2D, texture[j]); 

			glPushMatrix();

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
// 初始化灯泡列表
void initLightbulbList() {
	glNewList(bulb[0], GL_COMPILE);
	GLUquadricObj* sphere = gluNewQuadric();
	gluQuadricNormals(sphere, GLU_SMOOTH);
	gluQuadricDrawStyle(sphere, GLU_FILL);
	gluQuadricTexture(sphere, GL_TRUE);
	glPushMatrix();
	glEnable(GL_TEXTURE_2D);
	// 绑定所需纹理
	glBindTexture(GL_TEXTURE_2D, 0);  
	gluSphere(sphere, 0.2, 50, 50);
	glDisable(GL_TEXTURE_2D);
	glPopMatrix();
	glEndList();
}
// 初始化窗户列表
GLint initWindowList() {
	// 可移动窗玻璃
	glNewList(window[0], GL_COMPILE);
	glPushMatrix();
	glEnable(GL_NORMALIZE); 
	glScalef(0.0206f, 0.45f, 0.4f);
	Texture_cube(1, 6 - 1, 0, 0);
	glPopMatrix();
	glEndList();
	// 编号1窗体
	glNewList(window[1], GL_COMPILE);
	glPushMatrix();
	glEnable(GL_NORMALIZE); 
	glScalef(0.0205f, 0.5f, 0.8f);
	Texture_cube(1, 17, 0, 0);
	glPopMatrix();
	glEndList();
	// 编号2窗体
	glNewList(window[2], GL_COMPILE);
	glPushMatrix();
	glEnable(GL_NORMALIZE); glScalef(0.0205f, 0.5f, 0.8f);
	Texture_cube(1, 18, 0, 0);
	glPopMatrix();
	glEndList();
	// 编号3窗体
	glNewList(window[3], GL_COMPILE);
	glPushMatrix();
	glEnable(GL_NORMALIZE); glScalef(0.0205f, 0.5f, 0.8f);
	Texture_cube(1, 17, 0, 0);
	glPopMatrix();
	glEndList();
	return 0;
}
// 初始化门列表
GLint initDoorList() {
	// 1号门
	glNewList(door[0], GL_COMPILE);
	glPushMatrix();
	glEnable(GL_NORMALIZE); glScalef(0.0205f, 0.6f, 0.3f);
	Texture_cube(1, 4 - 1, 0, 0);
	glPopMatrix();
	glEndList();
	// 2号门
	glNewList(door[1], GL_COMPILE);
	glPushMatrix();
	glEnable(GL_NORMALIZE); glScalef(0.3f, 0.6f, 0.0205f);
	Texture_cube(1, 3 - 1, 0, 0);
	glPopMatrix();
	glEndList();
	// 1号门外走廊
	glNewList(outside[0], GL_COMPILE);
	glPushMatrix();
	glEnable(GL_NORMALIZE); glScalef(0.0202f, 0.6f, 0.3f);
	Texture_cube(1, 15, 0, 0);
	glPopMatrix();
	glEndList();
	// 2号门外走廊
	glNewList(outside[1], GL_COMPILE);
	glPushMatrix();
	glEnable(GL_NORMALIZE); glScalef(0.3f, 0.6f, 0.0202f);
	Texture_cube(1, 16, 0, 0);
	glPopMatrix();
	glEndList();
	// 1号两侧门框
	glNewList(door_edge[0], GL_COMPILE);
	glPushMatrix();
	glEnable(GL_NORMALIZE); glScalef(0.03f, 0.65f, 0.03f);
	Texture_cube(1, 13 - 1, 0, 0);
	glPopMatrix();
	glEndList();
	// 1号上方门框
	glNewList(door_edge[1], GL_COMPILE);
	glPushMatrix();
	glEnable(GL_NORMALIZE); glScalef(0.03f, 0.03f, 0.31f);
	Texture_cube(1, 10 - 1, 0, 0);
	glPopMatrix();
	glEndList();
	// 2号上方门框
	glNewList(door_edge[2], GL_COMPILE);
	glPushMatrix();
	glEnable(GL_NORMALIZE); glScalef(0.31f, 0.03f, 0.03f);
	Texture_cube(1, 11 - 1, 0, 0);
	glPopMatrix();
	glEndList();
	// 2号两侧门框
	glNewList(door_edge[3], GL_COMPILE);
	glPushMatrix();
	glEnable(GL_NORMALIZE); glScalef(0.03f, 0.65f, 0.03f);
	Texture_cube(1, 12 - 1, 0, 0);
	glPopMatrix();
	glEndList();
	return 0;
}
// 初始化墙列表
GLint initWallList() {
	// 把基本的墙面元放入列表
	static GLfloat wall_mat0[] =
	{ 1.f, .5f, 0.f, 1.f };
	static GLfloat wall_mat1[] =
	{ 0.f, .5f, 1.f, 1.f };
	static GLfloat wall_mat2[] =
	{ 1.f, .0f, 0.f, 1.f };


	glNewList(wall[0], GL_COMPILE);    // 地板
	glPushMatrix();
	GLfloat floor_mat_specular[] = { 0.90, 0.80, 0.60, 1.0 };	         // 镜面反射颜色
	GLfloat floor_mat_shininess[] = { 50.0 };    // 镜面反射参数
	GLfloat floor_lmodel_ambient[] = { 0.86, 0.73, 0.54, 1.0 };    // 散射颜色为220, 186, 138
	GLfloat floor_lmodel_emmision[] = { 0.0, 0.0, 0.0, 1.0 };

	glMaterialfv(GL_FRONT, GL_SPECULAR, floor_mat_specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, floor_mat_shininess);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, floor_lmodel_ambient);
	glMaterialfv(GL_FRONT, GL_EMISSION, floor_lmodel_emmision);
	glEnable(GL_NORMALIZE); glScalef(0.1f, 0.1f, 4.0f);
	Texture_cube(1, 1 - 1, 0, 0);
	glPopMatrix();
	glEndList();
	glNewList(wall[1], GL_COMPILE);    // 天花板
	glPushMatrix();
	GLfloat ceiling_mat_shininess[] = { 50.0 };    // 镜面反射参数
	GLfloat ceiling_lmodel_ambient[] = { 0.79, 0.79, 0.79, 1.0 };    // 散射颜色
	GLfloat ceiling_lmodel_emmision[] = { 0.0, 0.0, 0.0, 1.0 };

	glMaterialfv(GL_FRONT, GL_SPECULAR, ceiling_lmodel_emmision);	// 天花板不反光
	glMaterialfv(GL_FRONT, GL_SHININESS, ceiling_mat_shininess);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, ceiling_lmodel_ambient);
	glMaterialfv(GL_FRONT, GL_EMISSION, ceiling_lmodel_emmision);
	glEnable(GL_NORMALIZE); glScalef(0.1f, 0.1f, 4.0f);
	Texture_cube(1, 5 - 1, 0, 0);
	glPopMatrix();
	glEndList();

	glNewList(wall[2], GL_COMPILE); // 墙
	glPushMatrix();
	GLfloat wall_mat_specular[] = { 0.85, 0.85, 0.85, 1.0 };	         // 镜面反射颜色
	GLfloat wall_mat_shininess[] = { 50.0 };    // 镜面反射参数
	GLfloat wall_lmodel_ambient[] = { 0.79, 0.79, 0.79, 1.0 };    // 散射颜色
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
// 初始化柜子列表
GLint initClosetList() {
	// 柜子的正面
	glNewList(closet[0], GL_COMPILE);
	// 设置光照
	GLfloat closet_mat_specular[] = { 0.90, 0.90, 0.90, 1.0 };	         // 镜面反射颜色
	GLfloat closet_mat_shininess[] = { 50.0 };    // 镜面反射参数
	GLfloat closet_lmodel_ambient[] = { 0.85, 0.85, 0.85, 1.0 };    // 散射颜色
	GLfloat closet_lmodel_emmision[] = { 0.0, 0.0, 0.0, 1.0 };
	glMaterialfv(GL_FRONT, GL_SPECULAR, closet_mat_specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, closet_mat_shininess);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, closet_lmodel_ambient);
	glMaterialfv(GL_FRONT, GL_EMISSION, closet_lmodel_emmision);
	glEnable(GL_NORMALIZE); glScalef(0.02f, 0.8f, 0.6f);
	Texture_cube(1, 8 - 1, 0, 0);
	glEndList();
	// 柜子的侧面
	glNewList(closet[1], GL_COMPILE);

	glMaterialfv(GL_FRONT, GL_SPECULAR, closet_mat_specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, closet_mat_shininess);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, closet_lmodel_ambient);
	glMaterialfv(GL_FRONT, GL_EMISSION, closet_lmodel_emmision);
	glEnable(GL_NORMALIZE); glScalef(0.15f, 0.8f, 0.02f);
	Texture_cube(1, 9 - 1, 0, 0);
	glEndList();
	// 这个是柜子的上面
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
// 初始化桌面列表
void initDesk() {
	GLfloat desk_mat_specular[] = { 0.92, 0.65, 0.35, 1.0 };	         // 镜面反射颜色
	GLfloat desk_mat_shininess[] = { 50.0 };    // 镜面反射参数
	GLfloat desk_lmodel_ambient[] = { 0.84, 0.55, 0.25, 1.0 };    // 散射颜色
	GLfloat desk_lmodel_emmision[] = { 0.0, 0.0, 0.0, 1.0 };
	glNewList(desk[0], GL_COMPILE);
	glMaterialfv(GL_FRONT, GL_SPECULAR, desk_mat_specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, desk_mat_shininess);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, desk_lmodel_ambient);
	glMaterialfv(GL_FRONT, GL_EMISSION, desk_lmodel_emmision);
	Texture_cube(1, 2 - 1, 0, 0);
	glEndList();
}
// 绘制环境
void draw() {
	drawfans();
	drawWall();
	drawWindow();
	drawLightbulb();
	drawGlass();
	glTranslatef(0,-0.099,0);
	drawCloset();
	drawDoor();
	drawBoard();
	drawDesk();
	glTranslatef(0, 0.099, 0);
}
// 绘制一张桌子
void drawoneDesk() {
	glPushMatrix();
	glTranslatef(-0.25, 0.3, -0.15);
	glEnable(GL_NORMALIZE);
	glScalef(0.02f, 0.3f, 0.02f);
	glCallList(desk[0]);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-0.25, 0.3, 0.15);
	glEnable(GL_NORMALIZE);
	glScalef(0.02f, 0.3f, 0.02f);
	glCallList(desk[0]);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.25, 0.3, -0.15);
	glEnable(GL_NORMALIZE);
	glScalef(0.02f, 0.3f, 0.02f);
	glCallList(desk[0]);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.25, 0.3, 0.15);
	glEnable(GL_NORMALIZE);
	glScalef(0.02f, 0.3f, 0.02f);
	glCallList(desk[0]);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0, 0.6, 0);
	glEnable(GL_NORMALIZE);
	glScalef(0.3f, 0.01f, 0.2f);
	glCallList(desk[0]);
	glPopMatrix();
	glEndList();
}
// 在场景中绘制桌子
void drawDesk() {
	glPushMatrix();
	glTranslatef(7.5, 0, 2.5);
	glRotatef(90, 0, 1, 0);
	drawoneDesk();
	glPopMatrix();
}
// 绘制一块公告板
void drawoneboard() {
	glPushMatrix();
	GLfloat board_mat_specular[] = { 0.92, 0.65, 0.35, 1.0 };	         // 镜面反射颜色
	GLfloat board_mat_shininess[] = { 50.0 };    // 镜面反射参数
	GLfloat board_lmodel_ambient[] = { 0.84, 0.55, 0.25, 1.0 };    // 散射颜色
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
	GLfloat rabbit_mat_specular[] = { 0.80, 0.90, 0.98, 1.0 };	         // 镜面反射颜色
	GLfloat rabbit_mat_shininess[] = { 50.0 };    // 镜面反射参数
	GLfloat rabbit_lmodel_ambient[] = { 0.70, 0.82, 0.89, 1.0 };    // 散射颜色
	GLfloat rabbit_lmodel_emmision[] = { 0.0, 0.0, 0.0, 1.0 };

	glMaterialfv(GL_FRONT, GL_SPECULAR, rabbit_mat_specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, rabbit_mat_shininess);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, rabbit_lmodel_ambient);
	glMaterialfv(GL_FRONT, GL_EMISSION, rabbit_lmodel_emmision);
	glTranslatef(0, 0.55, -0.06);
	glEnable(GL_NORMALIZE); 
	glScalef(0.48f, 0.24f, 0.001f);
	if(boardmode)Texture_cube(1, 13, 0, 0);
	else {
		Texture_cube(1, 28 + boardnum, 0, 0);
		boardcounter += 1;
		if (boardcounter == 50) {
			boardnum += 1;
			boardcounter = 0;
		}
		if (boardnum == 4) {
			boardnum = 0;
			boardmode = true;
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
// 场景中绘制公告板
void drawBoard() {
	glPushMatrix();
	glTranslatef(1, 0.1, 2.5);
	drawoneboard();
	glPopMatrix();
}
// 绘制一块玻璃板
void drawGlass() {
	glPushMatrix();
	GLfloat mat_specular[] = { 1., 1., 1., 1.0 };	         // 镜面反射颜色
	GLfloat mat_shininess[] = { 50.0 };    // 镜面反射参数
	GLfloat lmodel_ambient[] = { 1., 1., 1., 1.0 };    // 散射颜色
	GLfloat lmodel_emmision[] = { 0.0, 0.0, 0.0, 1.0 };

	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, lmodel_ambient);
	glMaterialfv(GL_FRONT, GL_EMISSION, lmodel_emmision);
	glTranslatef(4.0, 1.0, 3.0);
	glEnable(GL_BLEND);    // 使创建的立方体可以产生半透明的效果
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glDepthMask(GL_FALSE);
	glDisable(GL_LIGHTING);    // 在绘制玻璃板的时候需要关闭灯光效果
	glColor4f(1.0, 1.0, 1.0, 0.2);
	glEnable(GL_NORMALIZE);    // 规格化向量
	glScalef(8.0, 2.0, 0.01);
	glutSolidCube(1.0);    // 绘制实心立方体
	glDisable(GL_BLEND);
	glEnable(GL_LIGHTING);    // 重新打开灯光
	glDepthMask(GL_TRUE);
	glPopMatrix();
}
// 绘制一个柜子
void drawonecloset() {
	// 这个是柜子的正面
	glPushMatrix();
	glTranslatef(0, 0.2, 0);
	glPushMatrix();
	glTranslatef(0.14, 0, 0);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glCallList(closet[0]);
	glPopMatrix();
	// 这个是柜子的背面
	glPushMatrix();
	glTranslatef(-0.14, 0, 0);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glCallList(closet[0]);
	glPopMatrix();
	// 这个是柜子的侧面
	glPushMatrix();
	glTranslatef(0, 0, 0.59);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glCallList(closet[1]);
	glPopMatrix();
	// 这个是柜子的侧面
	glPushMatrix();
	glTranslatef(0, 0, -0.59);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glCallList(closet[1]);
	glPopMatrix();
	// 这个是柜子的上面
	glPushMatrix();
	glTranslatef(0, 0.79, 0);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glCallList(closet[2]);
	glPopMatrix();
	glPopMatrix();
}
// 在场景中绘制柜子
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
// 绘制灯泡
void drawLightbulb() {
	glPushMatrix();
	glTranslatef(1.6, 2., 1.6);
	for (int i = 0; i < 4; i++) {
		glPushMatrix();
		glTranslatef(1.6 * i, 0, 0);
		for (int k = 0; k < 4; k++) {
			glPushMatrix();
			if ((k == i && global_light_enable[k]) ||		// 主对角线上的灯
					(k + i == 3 && global_light_enable[i + 4])) {	// 主对角线上的聚光灯
				glMaterialfv(GL_FRONT, GL_EMISSION, global_diffuse);
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
// 绘制一扇窗
void drawoneWindow(int i) {
	glCallList(window[i + 1]);
	glPushMatrix();
	glTranslatef(0, 0.0043, window_pos[i]);    // 利用window_pos[i]变量表示窗玻璃当前坐标
	glCallList(window[0]);
	glPopMatrix();
}
// 在场景中绘制窗
void drawWindow() {
	glPushMatrix();
	glTranslatef(8.0, 1.0, 2.0);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	drawoneWindow(0);    // 依次绘制三扇窗
	if (window_pos[0] <= 0.35 && window_pos_on[0]) window_pos[0] += 0.002;    // 如果窗户处于开启状态,且当前并未达到完全开启,那么将玻璃向右移动
	if (window_pos[0] >= -0.35 && !window_pos_on[0]) window_pos[0] -= 0.002;    // 如果窗户处于关闭状态,且当前并未达到完全闭合,那么将玻璃向左移动
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
// 绘制1号门框
void drawOutsideDoor_1() {
	glPushMatrix();
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glCallList(outside[0]);
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
// 绘制2号门框
void drawOutsideDoor_2() {
	glPushMatrix();
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glCallList(outside[1]);
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
// 返回1号门的状态
bool getRDoor_1() {
	return r_door_on[0];
}
// 返回2号门的状态
bool getRDoor_2() {
	return r_door_on[1];
}
// 在场景中绘制门
void drawDoor() {
	glPushMatrix();
	glTranslatef(0.0, 0.7, 6);    // 移动到1号门的位置
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	drawOutsideDoor_1();    // 绘制1号门框
	glPopMatrix();

	glPushMatrix();
	glTranslatef(1.3, 0.7, 0.0);    // 移动到2号门的位置
	drawOutsideDoor_2();    // 移动到2号门的位置
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.02, 0.7, 5.7);
	glRotatef(r_door[0], 0, 1, 0);    // 旋转门板
	if (r_door[0] < -45 && r_door_on[0]) r_door[0]++;    // 如果门正在开启,增大门板的夹角
	if (r_door[0] >= -180 && !r_door_on[0]) r_door[0]--;    // 如果门正在关闭,减小门板的夹角
	glTranslatef(0.0, 0.0, -0.3);
	glCallList(door[0]);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(1.0, 0.7, 0.02);
	glRotatef(r_door[1], 0, 1, 0);    // -180~-90
	if (r_door[1] < 0 && r_door_on[1]) r_door[1]++;
	if (r_door[1] >= -135 && !r_door_on[1]) r_door[1]--;
	glTranslatef(0.3, 0.0, 0.0);
	glCallList(door[1]);
	glPopMatrix();
}
// 设置墙相关材质系数
void setWall() {
	GLfloat mat_specular[] = { 0.82, 0.93, 0.95, 1.0 };    // 镜面反射颜色
	GLfloat mat_shininess[] = { 50.0 };    // 镜面反射参数
	GLfloat lmodel_ambient[] = { 0.84, 0.91, 0.92, 1.0 };    // 散射颜色为浅蓝色
	GLfloat lmodel_emmision[] = { 0.0, 0.0, 0.0, 1.0 };

	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, lmodel_ambient);
	glMaterialfv(GL_FRONT, GL_EMISSION, lmodel_emmision);
}

GLUnurbsObj* theNurb1;
GLUnurbsObj* theNurb2;
GLUnurbsObj* theNurb3;
GLUnurbsObj* theNurb4;
GLfloat ctrlpoints[5][5][3] = {// 控制点
{{1  ,0  , 1  },{2,0.2, 2},{3,0.2, 2},{4,0.2, 1  },{5,0, 0.2}},
{{0.8,0.1, 0.8},{2,0.2, 1},{3,0.2, 1},{4,0.2, 0.5},{5,0, 0.1}},
{{0.6,0.2, 0  },{2,0.2, 0},{3,0.3, 0},{4,0.4, 0  },{5,0, 0  }},
{{0.8,0.1,-0.8},{2,0.2,-1},{3,0.4,-1},{4,0.5,-0.5},{5,0,-0.1}},
{{1  ,0  ,-1  },{2,0.2,-2},{3,0.4,-2},{4,0.6,-1  },{5,0,-0.2}} };

GLfloat knot_2[8] = { 0, 0, 0, 0, 1, 1, 1, 1 };
GLfloat knots[10] = { 0.0,0.0,0.0,0.0,0.0,1.0,1.0,1.0,1.0,1.0 };

GLfloat ctlpoints_2[4][4][3] = {// 控制点
	{ { 0., 3., 0. },{ 1., 3., 0. },{ 2., 3., 0 },{ 3., 3., 0. } },
	{ { 0., 2., 0. },{ 1., 2., 0. },{ 2., 2., 0 },{ 3., 2., 0. } },
	{ { 0., 1., 0. },{ 1., 1., 0. },{ 2., 1., 0 },{ 3., 1., 0. } },
	{ { 0., 0., 0. },{ 1., 0., 0. },{ 2., 0., 0 },{ 3., 0., 0. } }
};
// 初始化条带列表
void initTile() {
	for (int k = 0; k < 64; k++) {
		tile[k] = 100 + k;
		for (int i = 1; i < 4; i++)
			for (int j = 0; j < 4; j++)
				ctlpoints_2[i][j][2] = 2 * sin((GLfloat)i + k * 0.1);    // 根据条带飘动的角度不同，修改控制点
		glNewList(tile[k], GL_COMPILE);
		// 添加Nurbs曲面到列表中
		gluBeginSurface(theNurb4);
		gluNurbsSurface(theNurb4, 8, knot_2, 8, knot_2,    
			3 * 4, 3,
			&ctlpoints_2[0][0][0], 4, 4, GL_MAP2_VERTEX_3);
		gluEndSurface(theNurb4);
		glEndList();
	}
}
// 初始化扇叶列表
void initNurbs() {
	glPushMatrix();
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	GLfloat mat_diffuse[] = { 0.5,0.5,0.1,0.4 };
	GLfloat mat_specular[] = { 0.5,0.5,1.0,0.7 };
	GLfloat mat_shininess[] = { 50.0 };
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
	// 设置特殊效果
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glHint(GL_LINE_SMOOTH_HINT, GL_DONT_CARE);
	glEnable(GL_BLEND);
	glFrontFace(GL_CW);
	glShadeModel(GL_SMOOTH);
	glEnable(GL_LINE_SMOOTH);
	// 添加Nurbs曲面到列表中
	glNewList(nurbs[0], GL_COMPILE);
	// 创建Nurbs曲面的对象
	theNurb1 = gluNewNurbsRenderer();
	gluNurbsProperty(theNurb1, GLU_SAMPLING_TOLERANCE, 25.0);
	gluNurbsProperty(theNurb1, GLU_DISPLAY_MODE, GLU_FILL);
	gluBeginSurface(theNurb1);
	gluNurbsSurface(theNurb1, 10, knots, 10, knots, 5 * 3, 3, &ctrlpoints[0][0][0], 5, 5, GL_MAP2_VERTEX_3);
	gluEndSurface(theNurb1);
	glEndList();
	glNewList(nurbs[1], GL_COMPILE);
	theNurb2 = gluNewNurbsRenderer();
	gluNurbsProperty(theNurb2, GLU_SAMPLING_TOLERANCE, 25.0);
	gluNurbsProperty(theNurb2, GLU_DISPLAY_MODE, GLU_FILL);
	gluBeginSurface(theNurb2);
	gluNurbsSurface(theNurb2, 10, knots, 10, knots, 5 * 3, 3, &ctrlpoints[0][0][0], 5, 5, GL_MAP2_VERTEX_3);
	gluEndSurface(theNurb2);
	glEndList();
	glNewList(nurbs[2], GL_COMPILE);
	theNurb3 = gluNewNurbsRenderer();
	gluNurbsProperty(theNurb3, GLU_SAMPLING_TOLERANCE, 25.0);
	gluNurbsProperty(theNurb3, GLU_DISPLAY_MODE, GLU_FILL);
	gluBeginSurface(theNurb3);
	gluNurbsSurface(theNurb3, 10, knots, 10, knots, 5 * 3, 3, &ctrlpoints[0][0][0], 5, 5, GL_MAP2_VERTEX_3);
	gluEndSurface(theNurb3);
	glEndList();
	glNewList(nurbs[3], GL_COMPILE);
	theNurb4 = gluNewNurbsRenderer();
	gluNurbsProperty(theNurb3, GLU_SAMPLING_TOLERANCE, 25.0);
	gluNurbsProperty(theNurb3, GLU_DISPLAY_MODE, GLU_FILL);
}

GLfloat fan_r = 0;
GLint tile_r = 0;

// 绘制电扇
void drawfans() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glPushMatrix();
	glTranslatef(4, 1.9, 4);
	glScalef(0.005, 0.2, 0.005);
	Texture_cube(2, 8, 22, 0);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(4, 1.7, 4);
	// 利用fan_r表现电风扇叶的旋转效果
	glRotatef(fan_r++, 0, 1, 0);
	glTranslatef(-0.5, 0, 0);
	glScalef(0.1, 0.05, 0.05);
	glCallList(nurbs[0]);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(4, 1.7, 4);
	glRotatef(fan_r + 120, 0, 1, 0);
	glTranslatef(-0.5, 0, 0);
	glScalef(0.1, 0.05, 0.05);
	glCallList(nurbs[1]);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(4, 1.7, 4);
	glRotatef(fan_r + 240, 0, 1, 0);
	glTranslatef(-0.5, 0, 0);
	glScalef(0.1, 0.05, 0.05);
	glCallList(nurbs[2]);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(3.99, 1.4, 4);
	glScalef(0.005, 0.1, 0.025);
	glCallList(tile[tile_r++]);
	glPopMatrix();
	if (tile_r == 64)tile_r = 0;
}

// 绘制墙面
void drawWall() {
	glPushMatrix();
	glTranslatef(0, 1, 0);
	glPushMatrix();
	glTranslatef(0, 0, 4);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glScalef(1, 1, 200);
	glCallList(wall[2]);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(4, 0, 0);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glScalef(200, 1, 1);
	glCallList(wall[2]);
	glPopMatrix();
	glTranslatef(8.0, 0.0, 8.0);
	glPushMatrix();
	glTranslatef(0, 0, -4);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glScalef(1, 1, 200);
	glCallList(wall[2]);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(-4, 0, 0);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glScalef(200, 1, 1);
	glCallList(wall[2]);
	glPopMatrix();
	glTranslatef(-8.0, -1.099, -4.0);
	glPushMatrix();
	glTranslatef(4, 0, 0);
	glScalef(40, 1, 1);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glCallList(wall[0]);
	glPopMatrix();
	glTranslatef(0.0, 2.099, 0.0);
	glPushMatrix();
	glTranslatef(4, 0, 0);
	glScalef(40, 1, 1);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glCallList(wall[1]);
	glPopMatrix();
	glPopMatrix();
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}

