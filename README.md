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

#### 碰撞检测
- `v` : 开关能否走出房间的碰撞检测；

#### 机械臂操作

+ `9`：控制机械臂1传送；

- `i`：控制机械臂2传送；
- `k`：控制机械臂3传送；
- `m`：控制机械臂4传送；

#### 机械爪操作

- `e`：控制三个机械臂的机械爪抓取；

#### 传送带操作

- `r`：控制传送带1&2号转动（按一下动一下）;
- `t`：控制传送带3号转动（按一下动一下）;
- `h`：控制传送带4号转动（按一下动一下）;
- `j`：控制传送带5号转动（按一下动一下）;

#### 门窗控制

- `f` `g` ：控制两扇门的开与关; 其中`f`为传送带方向的门的开关，在开门时，如果传送带5末端有**礼物盒**，则礼物盒消失。
- `b` `n` `m` ：控制三扇窗开与关；

#### 光源控制

- `0` `1` `2` `3` `4` `5` `6` `7` : 分别控制0-7号光源的开与关（视觉效果为灯的开关）；
- `8`：控制光的色温循环变化；

#### 公告板纹理变换

- `u`：改动公告板;

#### 截图操作

+ `p`：按下截图（当前画面）

#### 退出程序

+ `q`：退出程序


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

#### 2021/12/25 updated by xzk

1. 添加了鼠标选取的相关代码, 调整了参数, 其中启用选择模式后, 需要采用正视图视角选取物体, 否则鼠标选取的准确度很不准。选取结果有s_type标识选中的对象类型, s_id标识对象在vector中的下标。
2. 部分调整了main.cpp, 增加了函数的声明，略微规范了代码的写法，将list类转成了vector类方便random access 
3. 添加了鼠标放置的功能, 目前鼠标放置放置的是六棱柱, 效果为在鼠标指向位置放置一个六棱柱, 后续可以拓展(累了)
4. 添加了glm库 位于include目录下
5. 添加了model_view.h及model_view.cpp, 实现鼠标位置转化成世界坐标
6. 修改robot类, 修复bug
7. 修改了shape类, 保证类下的globalX,globalY, globalZ三个坐标与世界坐标相等



#### 2021/12/28 by ZhongPeipei

##### 1，整理了shape类

+ 增加了draw函数里面增加了:

```c++
glScalef(this->scaleX, this->scaleY, this->scaleZ);
glRotatef(this->rotateX, 1, 0, 0);
glRotatef(this->rotateY, 0, 1, 0);
glRotatef(this->rotateZ, 0, 0, 1);
```

​	shape.h增加了scaleX, scaleY, scaleZ,

​	在main函数new一个shape的时候可以设置它的位置、大小、方向。

+ 在draw里面增加了`glTranslatef(0, 0.099, 0);	`，使得new一个shape的时候，globalY为0时b表示画在地板上。（地板应该有0.099的厚度）
+ 保证每个shape的globalY是底面的高度，便于判断是否在传送带上；globalY=0.2是在传送带上的条件之一

--------

1，new一个shape的时候它会在哪？

首先，房间是8\*8\*2：

![](README.assets\axis.png)

globalY=0的时候它就在地板上，globalY是每个物块的最低点。



2，new一个conveyor的时候它会在哪？

PositionY=0的时候它就在地板上。下面是场景中现有的传送带的示意。PositionX，PositionZ是传送带的中心位置。

![](README.assets\conveyor.png)



3，物块什么时候会随传送带运动？

conveyor.cpp中的ifOntheConveyor函数会做判断，满足以下条件物块就会随着传送带运动：

```c++
if (shapeY > 0.16 && shapeY<0.3 && shapeX > this->PositionX - 0.75 && shapeX< this->PositionX + 0.75 && shapeZ>this->PositionZ - 0.2 && shapeZ < this->PositionZ + 0.2)
	{ 
		
		return true;
	}
```

也就是通过物块和传送带的世界坐标进行判断。

------



##### 2，修改了conveyor类

+ 增加了PositionZ

+ new一个时，PositionY=0时是画在地板上

+ 修改了传送带和物块绑定的函数
  + 每次调用传送带移动函数时，判断它上面有没有物体，有则带着物体一起走
  + 遍历conveyorvector， shape vector看有没有shape在传送带上
  + 现在是当物体运动到传送带一端会停在那里，那么后面来的物体怎么处理？需要碰撞检测吗？（不然现在会重合在一起）
  
+ 目前是按下t之后是所有传送带都开始运动（是否需要分别控制？）

+ 传送带上的物体怎么才能和传送带一个方向运动：conveyor.cpp中

  ```c++
  void conveyor::AddMotion(Shape* shape)//若shape在传送带上就运动
  {
  	if (ifOntheConveyor(shape)) 
  	{
  		this->MotionX = -0.1 * cos(this->ConrotateY * K);
  		this->MotionZ = 0.1 * sin(this->ConrotateY * K);
  		shape->transfer(this->MotionX, 0, this->MotionZ);
  	}
  	return ;
  }
  ```

  ConrotateY是传送带绕y轴旋转的量，MotionX，MotionZ是物块在x轴，z轴上运动速度的分量，0.1表征物块运动的速度。所以现在检测到物块在传送带上，该物块就会随传送带运动。

#### 2022/1/19 updated by xzk

* 修正地板的y轴坐标, 原先地板y轴坐标为0.099, 因此将地板向下平移0.099, 同时需要将各个shape类的globalY以及场景中部分物体的Y坐标进行修正

* 修正屏幕坐标到世界坐标系转换函数, 使其更具鲁棒性

* 将鼠标选中shape对象的指针赋值给currentChooseShape全局变量, 具体逻辑见下

	```c
		if (s_type == NONE)/////改成__conveyor就是在传送带范围放东西;NONE是除传送带范围放置
		{
			glGetFloatv(GL_MODELVIEW_MATRIX, view);
			glGetFloatv(GL_PROJECTION_MATRIX, pro);
			res = getViewPos(x, y, pro, view);
			//printf("%f,%f,%f\n", eye[0], eye[1], eye[2]);
			Prism* p = new Prism(res[0], res[1] , res[2]);
			Shapes.push_back(p);
			cout << res[0] << " " << res[1] << " " << res[2] << " " << Shapes.size() << endl;
		}
		else
		{
			switch (s_type)
			{
			case __robot:
				CurrentChooseShape = NULL;
				break;
			case __shape:
				CurrentChooseShape = Shapes[s_id];
				break;
	        case __conveyor:
				CurrentChooseShape = NULL;
				break;
			default:
				CurrentChooseShape = NULL;
				break;
			}
		}
	```

	当当前选中物体为shape类时, 给**CurrentChooseShape**指针赋值, 同时 如果需要对robot或者conveyor对象进行操作也预留了对应的空间可以进行处理。

* k键用来测试current_choose_shape的功能, 当其不为null时 放大一倍, 可自行修改

#### 2022/1/20 updated by bdz & zsk
zsk:
- 做好了饼皮、馅料、月饼、礼物盒皮和礼物盒
- 增加了shape中的Type属性与RetType函数，说明如下：
+ 默认Type为-1

+ 饼皮Type为-2

+ 三种馅料Type为0 1 2

+ 三种月饼Type为10 11 12

+ 两种礼盒皮Type为3 4

+ 两种礼盒Type为23 24

  

  bdz:
- 做了碰撞函数mooncakeCollision，每次绘制场景前调用
- 碰撞要求比较苛刻：Y, Z坐标相同，X坐标相距小于0.03(传送带位移单位)，需要改条件可以找我。
- 碰撞检测为了降低复杂度，选择了先用sort进行排序再尽可能剪枝遍历。为此引入了shapeCompare函数。
- 目前已经测试过饼皮+馅料=月饼。月饼+礼物盒皮=礼物盒还没有测试，如果出问题可以找我。
- 可能出现的bug：Vector的erase函数与iterator结合使用不当导致越界



#### 2022/1/24 zpp

“游戏”说明：合成三个月饼盒:)

r,t,h,j对应1&2，3，4，5传送带，按下f，开门的同时如果检测到5号传送带末端有礼物盒，则礼物盒消失（表示被送出工厂）。



#### 2022/1/25 xzk

添加了鼠标选中后的反馈效果
