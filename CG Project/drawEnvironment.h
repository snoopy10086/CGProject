#ifndef	_PICK_H_
#define	_PICK_H_
#include <windows.h>
#pragma comment(lib, "glew32.lib") 
#include "glew.h"
#include <gl/gl.h>
#include <gl/glu.h>
#include <gl/glut.h>
#include <stdio.h>
#include <assert.h>
#include <iostream>
#include "Robot.h"
#include "conveyor.h"


#define BITMAP_ID 0x4D42
#define imageweight 128
#define imageheight 128
void InitList();
void draw();
void initTexture();
void initLightbulbList();
void drawLightbulb();
GLint initClosetList();
void drawCloset();
void drawonecloset();
void initNurbs();
void drawfans();
GLint initDoorList();
void drawOutsideDoor_1();
void drawOutsideDoor_2();
bool getRDoor_1();
bool getRDoor_2();
void drawDoor();
void initDesk();
void initTile();
void drawoneDesk();
void drawDesk();
GLint initWindowList();
void drawoneWindow(int i);
void Change_Window(int i);
void drawWindow();
GLint initGlassList();
void setWall();
void drawGlass();
void drawoneboard();
void drawBoard();
GLint initWallList();
void drawWall();
void Texture_cube(int n, int i, int j, int k);
void texload(int i, char* filename);
unsigned char* LoadBitmapFile(char* filename, BITMAPINFOHEADER* bitmapInfoHeader);
bool Change_Door_1();
void Change_Door_2();
void Change_Rust();
#endif
