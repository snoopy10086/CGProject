# CGProject

This is a project of 2021 CG course in ZJU.

> ***Group Member***
>
> Zhang Liyu, Xu Zikai, Wang Fangyikang, Zhang Shenke, Zhong Peipei, Bao Dezheng

## Keboard Operation

![image-20211224025840151](README.assets/image-20211224025840151.png)

#### 视角变换

- `w` `s`：视角方向前后移动
- `a` `d`：视角方向在水平平面的投影的法线方向移动，即在同一个水平面里动
- `z` `c`：上下动

#### 机械臂操作

- `r`：控制机械臂1、2三个自由度；

#### 机械爪操作

- `e`：控制三个机械臂的机械爪抓取；

#### 传送带操作

- `t`：控制传送带转动（按一下动一下）;

#### 门窗控制

- `f` `g` ：控制两扇门的开与关;
- `v` `b` `n`：控制三扇窗开与关；

#### 光源控制

- `1` `2` `3` `4` `5` `6` `7` : 分别控制0-7号光源的开与关（视觉效果为灯的开关）；
- `8`：控制光的色温循环变化；

## Todo List

#### Stage 1 Week7-Thur
- 类之间的绑定与数据创建：wfyk 
- 光源变换（位置、颜色）、纹理变换：bdz 
- 机械臂动画效果：zly
- 不要走出房间-碰撞检测：zsk
- 体素添加（多面棱柱、多面棱台）：zpp

>2021.12.23:
>
>均Check, zly部分还未合并。由于我们的键盘操作***暂时做成的***针对的是全局变量，因此将wfyk写的push进队列的机器臂、传送带等暂时变成全局变量。
>
>另外关于列表内应当是对象还是对象指针，已经交由wfyk决定。

#### Stage 2 Week8-Tues

- 搭建一个默认流水线：zpp
- 放置物体：xzk
- 储存-导入导出：xzk
- 截屏+保存：zly



## Update History

#### 12.25 updated by xzk

1. 添加了鼠标选取的相关代码, 调整了参数, 其中启用选择模式后, 需要采用正视图视角选取物体, 否则鼠标选取的准确度很不准。选取结果有s_type标识选中的对象类型, s_id标识对象在vector中的下标。
2. 部分调整了main.cpp, 增加了函数的声明，略微规范了代码的写法，将list类转成了vector类方便random access 
3. 添加了鼠标放置的功能, 目前鼠标放置放置的是六棱柱, 效果为在鼠标指向位置放置一个六棱柱, 后续可以拓展(累了)
4. 添加了glm库 位于include目录下
5. 添加了model_view.h及model_view.cpp, 实现鼠标位置转化成世界坐标
6. 修改robot类, 修复bug
7. 修改了shape类, 保证类下的globalX,globalY, globalZ三个坐标与世界坐标相等
