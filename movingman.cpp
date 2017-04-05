#include<GL/glut.h>  
// ����������  
float a = 0.025f;
float a_2 = 0.05f;
float b = 0.075;
//a,a_2,b�������������趨���ó�����ĳ���
// ��������İ˸����㱣�浽һ����������   
//ͷ����������
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
//�첲�ʹ����ǳ�����
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
//С�ȵ�����
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
//����(��׵)������
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
//����ͼ�������
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
// ��Ҫʹ�õĶ������ű��浽һ����������   
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
// ����������  
void DrawCube(const float part[][3])//���������������߻������賤����
{
	int i, j;
	glBegin(GL_LINES);
	for (i = 0; i<12; ++i) // 12 ���߶�  
	{
		for (j = 0; j<2; ++j) // ÿ���߶� 2������  
		{
			glVertex3fv(part[index_list[i][j]]);//ÿ������֮������
		}
	}
	glEnd();
}
//�����ƶ�����
void movey() {
	static float move = 0;
	static int times1 = 0;
	times1+=2;//�ƶ�Ƶ��
	if (times1 > 20)
	{
		times1 = 0;
	}
	if (times1 % 20 == 0)
	{
		move -= 0.0004;//ÿ���ƶ��ľ���
	}
	glTranslatef(-move,move,0);//�ƶ�����
}
//�����ܶ�(����ת���)����
void selfRotateR() {
	static float rotateAngle = 0;
	static int times1 = 0;
	static int x = 1;
	times1+=2;//��תƵ��
	if (times1 > 20)
	{
		times1 = 0;
	}
	if (times1 % 20 == 0)
	{
		rotateAngle += 1.5;//ÿ����ת�Ƕ�
		if (rotateAngle > 20)
		{
			rotateAngle = -rotateAngle;//����
			x = -x;
		}
	}
	glRotatef(-rotateAngle, x, 0, 0);//��ת����rotate

}
//�Ұ���ܶ�(����ת���)����
void selfRotateL() {
	static float rotateAngle = 0;
	static int times1 = 0;
	static int x = 1;
	times1+=2;//Ƶ��
	if (times1 > 20)
	{
		times1 = 0;
	}
	if (times1 % 20 == 0)
	{
		rotateAngle -= 1.5;//ÿ����ת�Ƕ�
		if (rotateAngle < -20)
		{
			rotateAngle = -rotateAngle;//����
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

void main(int argc, char **argv)
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