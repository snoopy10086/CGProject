#pragma once
#include <glm/glm.hpp>
#include <gl/glut.h>
extern int wWidth, wHeight;
glm::vec3 getViewPos(int x, int y, GLfloat* pro, GLfloat* view);
