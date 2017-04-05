---
layout:     post
title: "计算机图形学2017年春季作业一"
subtitle:"使用opengl制作移动的小人"
date:2017-04-01 12:00:00
author:"slientuill-余沛然"
header-img: "img/post-bg-nextgen-web-pwa.jpg"
header-mask: 0.3
catalog:    true
tags:
    - 图形学
    - c++
    - moving man
---



> 


## 代码
    #include<GL/glut.h>  
// 绘制立方体  
float a = 0.025f;
float a_2 = 0.05f;
float b = 0.075;
//a,a_2,b三个参数用来设定所用长方体的长度
// 将立方体的八个顶点保存到一个数组里面   
//头部是正方体
static const float vertex_head[][3] =
{
	-a_2, -a_2, -a_2,
	a_2, -a_2, -a_2,
	-a_2, a_2, -a_2,
	a_2, a_2, -a_2,
	-a_2, -a_2, a_2,
	a_2, -a_2, a_2,
	-a_2, a_2, a_2,
	a_2, a_2, a_2,
};
//胳膊和大腿是长方体
static const float vertex_longRec[][3] =
{
	-a, -a-0.2, -a,
	a, -a-0.2, -a,
	-a, a, -a,
	a, a, -a,
	-a, -a-0.2, a,
	a, -a-0.2, a,
	-a, a, a,
	a, a, a,
};
//小腿的数据
static const float vertex_longLeg[][3] =
{
	-a, -a - 0.3, -a,
	a, -a - 0.3, -a,
	-a, a, -a,
	a, a, -a,
	-a, -a - 0.3, a,
	a, -a - 0.3, a,
	-a, a, a,
	a, a, a,
};
//身体(脊椎)的数据
static const float vertex_body[][3] =
{
	-a, -a-0.3, -a,
	a, -a-0.3, -a,
	-a, a, -a,
	a, a, -a,
	-a, -a-0.3, a,
	a, -a-0.3, a,
	-a, a, a,
	a, a, a,
};
//腰宽和肩宽的数据
static const float vertex_width[][3] =
{
	-a-b, -a, -a,
	a+b, -a, -a,
	-a-b, a, -a,
	a+b, a, -a,
	-a-b, -a, a,
	a+b, -a, a,
	-a-b, a, a,
	a+b, a, a,
};
// 将要使用的顶点的序号保存到一个数组里面   
static const GLint index_list[][2] =
{
	{ 0, 1 },
	{ 2, 3 },
	{ 4, 5 },
	{ 6, 7 },
	{ 0, 2 },
	{ 1, 3 },
	{ 4, 6 },
	{ 5, 7 },
	{ 0, 4 },
	{ 1, 5 },
	{ 7, 3 },
	{ 2, 6 }
};
// 绘制立方体  
void DrawCube(const float part[][3])//传入矩阵参数，连线画得所需长方体
{
	int i, j;
	glBegin(GL_LINES);
	for (i = 0; i<12; ++i) // 12 条线段  
	{
		for (j = 0; j<2; ++j) // 每条线段 2个顶点  
		{
			glVertex3fv(part[index_list[i][j]]);//每两个点之间连线
		}
	}
	glEnd();
}
//整体移动函数
void movey() {
	static float move = 0;
	static int times1 = 0;
	times1+=2;//移动频率
	if (times1 > 20)
	{
		times1 = 0;
	}
	if (times1 % 20 == 0)
	{
		move -= 0.0004;//每次移动的距离
	}
	glTranslatef(-move,move,0);//移动函数
}
//左半边跑动(即旋转大臂)函数
void selfRotateR() {
	static float rotateAngle = 0;
	static int times1 = 0;
	static int x = 1;
	times1+=2;//旋转频率
	if (times1 > 20)
	{
		times1 = 0;
	}
	if (times1 % 20 == 0)
	{
		rotateAngle += 1.5;//每次旋转角度
		if (rotateAngle > 20)
		{
			rotateAngle = -rotateAngle;//回旋
			x = -x;
		}
	}
	glRotatef(-rotateAngle, x, 0, 0);//旋转函数rotate

}
//右半边跑动(即旋转大臂)函数
void selfRotateL() {
	static float rotateAngle = 0;
	static int times1 = 0;
	static int x = 1;
	times1+=2;//频率
	if (times1 > 20)
	{
		times1 = 0;
	}
	if (times1 % 20 == 0)
	{
		rotateAngle -= 1.5;//每次旋转角度
		if (rotateAngle < -20)
		{
			rotateAngle = -rotateAngle;//回旋
			x = -x;
		}
	}
	glRotatef(-rotateAngle, x, 0, 0);
}
void renderScene(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	//head
	glPushMatrix();
	glColor3f(0, 1, 1);
	glTranslatef(0, 0.8, 0);
	movey();
	glRotatef(15, 0, 1, 0);
	glRotatef(15, 1, 0, 0);
	DrawCube(vertex_head);
	glPopMatrix();
	//leftarm
	glPushMatrix();
	glTranslatef(-0.125,0.725, 0);
	glColor3f(1, 0, 1);
	selfRotateL();
	movey();
	glRotatef(15, 0, 1, 0);
	glRotatef(15, 1, 0, 0);
	DrawCube(vertex_longRec);
	//leftarm2
	glTranslatef(0, -0.2, 0);
	glColor3f(1, 0, 1);
	selfRotateL();
	glRotatef(15, 0, -1, 0);
	glRotatef(95, 1, 0, 0);
	DrawCube(vertex_longRec);
	glPopMatrix();
	//upperwidth
	glPushMatrix();
	glTranslatef(0, 0.725, 0);
	glColor3f(0, 0, 1);
	movey();
	glRotatef(15, 0, 1, 0);
	glRotatef(15, 1, 0, 0);
	DrawCube(vertex_width);
	glPopMatrix();
	//body
	glPushMatrix();
	glTranslatef(0, 0.675, 0);
	glColor3f(1, 0, 0);
	movey();
	glRotatef(15, 0, 1, 0);
	glRotatef(15, 1, 0, 0);
	DrawCube(vertex_body);
	glPopMatrix();
	//rightArm
	glPushMatrix();
	glTranslatef(0.125, 0.725, 0);
	glColor3f(1, 1, 1);
	selfRotateR();
	movey();
	glRotatef(15, 0, 1, 0);
	glRotatef(15, 1, 0, 0);
	DrawCube(vertex_longRec);
	//rightarm2
	glTranslatef(0, -0.2, 0);
	glColor3f(1, 1, 1);
	selfRotateR();
	//movey();
	glRotatef(15, 0, -1, 0);
	glRotatef(95, 1, 0, 0);
	DrawCube(vertex_longRec);
	glPopMatrix();
	//underwidth
	glPushMatrix();	
	glTranslatef(0, 0.345, 0);
	glColor3f(0, 0, 1);
	movey();
	glRotatef(15, 0, 1, 0);
	glRotatef(15, 1, 0, 0);
	DrawCube(vertex_width);
	glPopMatrix();
	//leftleg
	glPushMatrix();
	glColor3f(0, 0.85, 1);
	glTranslatef(0.075,0.315, 0);
	selfRotateL();
	movey();
	glRotatef(15, 0, 1, 0);
	glRotatef(15, 1, 0, 0);
	DrawCube(vertex_longRec);
	//leftleg2
	glColor3f(0, 0.85, 1);
	glTranslatef(0, -0.2, 0);
	selfRotateL();
	glRotatef(10, 0, -1, 0);
	glRotatef(60, -1, 0, 0);
	DrawCube(vertex_longLeg);
	glPopMatrix();
	//rightleg
	glPushMatrix();
	glTranslatef(-0.075, 0.315, 0);
	glColor3f(1, 1, 1);
	selfRotateR();
	movey();
	glRotatef(15, 0, 1, 0);
	glRotatef(15, 1, 0, 0);
	DrawCube(vertex_longRec);
	//rightleg2
	glTranslatef(0, -0.2, 0);
	glColor3f(1, 1, 1);
	selfRotateR();
	glRotatef(10, 0, -1, 0);
	glRotatef(60, -1, 0, 0);
	DrawCube(vertex_longLeg);
	glPopMatrix();

	glutSwapBuffers();
}
void main(int argc, char ****argv)//这里只有两个*，由于markdown文本的影响，这里标记了四个*
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(200, 100);
	glutInitWindowSize(1000, 1000);
	glutCreateWindow("GLDemo");
	glutDisplayFunc(renderScene);
	glutIdleFunc(renderScene);
	glutMainLoop();
}

##简单思路
 首先，使用opengl提供的连线函数，对于设定好的长方体八个顶点的矩阵数据进行逐一连线（drawcube函数），形成构建小人所需的基本部件（头部，躯干，肩部，四肢）
  使用gltranslate函数对各个部位进行摆放，形成小人的雏形，期间，使用pushmatrix和popmatrix函数，将各个部位隔离开来，同时，记得所有的translate函数rotate的函数要在drawcube方法前调用，否则摆放的位置将会形成错乱，需要注意的一点是小人的大臂和小臂属于同一结构，虽然使用了两个长方体，但中间不使用pop和push将其隔离，并且在后续的移动函数中，可以通过大臂来带动小臂旋转
  使用move函数和selfrotate函数来形成小人的移动以及手臂和腿的旋转
   move：通过times的叠加，使得translate函数中x和y轴的参变量逐步增大，在所有的部件中调用（大小臂只调用一次）实现小人的整体移动
   selfrotate：通过times的叠加，使得rotate函数中的rotateangle参数在逐步增大，并在达到临界值时反向，以达到回旋的效果， 其中小人的左半部和右半部分别使用两个参数相反的函数（selfrotateR和selfrotateL）从而实现正确的步姿
  ##简单演示
   等待更新中
