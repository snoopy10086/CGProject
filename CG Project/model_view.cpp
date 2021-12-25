#include "model_view.h"
#include <stdlib.h>


glm::vec3 getViewPos(int x, int y, GLfloat* pro, GLfloat* view)
{
    GLint viewPort[4];
    GLdouble modelView[16] = {
        view[0],view[1],view[2],view[3],
        view[4],view[5],view[6],view[7],
        view[8],view[9],view[10],view[11],
        view[12],view[13],view[14],view[15]
    };
    GLdouble projection[16] = {
        pro[0],pro[1],pro[2],pro[3],
        pro[4],pro[5],pro[6],pro[7],
        pro[8],pro[9],pro[10],pro[11],
        pro[12],pro[13],pro[14],pro[15]
    };
    //将glm::mat4类型转化为方法所需的数组类型

    GLfloat win_x, win_y, win_z;
    GLdouble object_x, object_y, object_z;
    int mouse_x = x;
    int mouse_y = y;
    glGetIntegerv(GL_VIEWPORT, viewPort);
    win_x = (float)mouse_x;
    win_y = (float)viewPort[3] - (float)mouse_y - 1.0f;
    glReadBuffer(GL_BACK);
    glReadPixels(mouse_x, int(win_x), 1, 1, GL_DEPTH_COMPONENT, GL_FLOAT, &win_z);
    gluUnProject((GLdouble)win_x, (GLdouble)win_y, (GLdouble)win_z, modelView, projection, viewPort, &object_x, &object_y, &object_z);
    //使用gluUnProject方法将结果传入object_x，object_y，object_z中

    glm::vec3 p = glm::vec3(object_x, object_y, object_z);
    return p;
    //返回vec3类型
}
//转换鼠标位置到3维空间