#include<gl/glut.h>
#include<math.h>
#include <stdlib.h>
#include <stdio.h>

/*동작 관련 변수*/
static double time = 0; //Run_time 변수
static double time2 = 0; //Jap_time 변수
static double time3 = 0; //Rocket_time 변수
static double time4 = 0;   //ground_time 변수

int flag = 1;

/*곰돌이 그리기 변수*/
GLfloat R_Arm_x = 0;  //오른쪽 어깨
GLfloat R_Arm_y = 0;  //오른 팔
GLfloat L_Arm_x = 0;  //왼쪽 어깨
GLfloat L_Arm_y = 0; //왼발

GLfloat R_Leg_x = 0; //오른쪽 허벅지
GLfloat R_Leg_y = 0; //오른쪽 종아리
GLfloat L_Leg_x = 0;  //왼쪽 허벅지
GLfloat L_Leg_y = 0; //왼쪽 종아리

					 /*JAP 관련 변수*/
GLfloat L = 0; //왼쪽  
GLfloat R = 0; //오른쪽 

GLUquadricObj* cyl; //실린더 객체

					/*회전 관련 변수*/
int a = 0; //x축 기준(값이 1일때, x축을 기준으로 회전)
int b = 0; //y축 기준(값이 1일때,yx축을 기준으로 회전)
int c = 0; //z축 기준(값이 1일때, z축을 기준으로 회전)
float r = 1.0, g = 0.0, b1 = 0.0;

static int key = 0; //동작 모드

					/*MODE 변경*/
#define RUN 1
#define JAP 2
#define ROCKET 3
#define SKATE 4
#define SOCCER 5

void drawCloud(float a) {
	glColor3f(1.0, 1.0, 1.0);
	glutSolidSphere(a, 30, 17);
	glTranslated(0.5f*a, -0.2f*a, -0.5f*a);
	glPushMatrix();
	glTranslated(0.5f*a, -0.2f*a, -0.15f*a);
	glutSolidSphere(a, 30, 17);
	glPopMatrix();
	glPushMatrix();
	glTranslated(8.0f*a, 2.5f*a, 2.0f*a);
	glutSolidSphere(a, 30, 17);
	glPopMatrix();
}

void init(void) {
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_NORMALIZE);
	glEnable(GL_LIGHTING);

	GLfloat ambientLight[] = { 0.3f,0.3f,0.3f,1.0f };
	GLfloat diffuseLight[] = { 0.7f,0.7f,0.7f,1.0f };
	GLfloat specular[] = { 1.0f,1.0f,1.0f,1.0f };
	GLfloat specef[] = { 1.0f,1.0f,1.0f,1.0f };
	GLfloat position[] = { 400.0,300.0,-700.0,1.0 };

	glLightfv(GL_LIGHT0, GL_AMBIENT, ambientLight);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuseLight);
	glLightfv(GL_LIGHT0, GL_SPECULAR, specular);
	glLightfv(GL_LIGHT0, GL_POSITION, position);
	glEnable(GL_LIGHT0);
	glEnable(GL_COLOR_MATERIAL);
	glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
	glMateriali(GL_FRONT, GL_SHININESS, 128);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	glClearColor(1.0, 1.0, 1.0, 1.0);
	glFrustum(-2.0, 2.0, -2.0, 2.0, 2.0, 20.0);

	glColor3f(0.933, 0.866, 0.509);

	glOrtho(-1.0, 1.0, -1.0, 1.0, -1.0, 1.0);
}

void DrawL_Arm(int x, int a, int b, int c) {
	glPushMatrix();
	glColor3f(r, g, b1);
	cyl = gluNewQuadric();
	glRotatef(x, a, b, c);
	glRotatef(90.0, 1.0, 0.0, 0.0);

	glTranslatef(0.25, 0.0, 0.0);
	glRotatef(15.0, 0.0, 1.0, 0.0);
	gluCylinder(cyl, 0.05, 0.05, 0.2, 50, 1);
}

void DrawL_Hand(int y, int a, int b, int c) {
	glPushMatrix();
	glColor3f(0.97, 0.75, 0.11);
	cyl = gluNewQuadric();
	glTranslatef(0.0, 0.0, 0.22);
	glRotatef(y, a, b, c);
	if (key == SKATE)
		gluCylinder(cyl, 0.05, 0.02, 0.2, 15, 1);
	else
		gluCylinder(cyl, 0.05, 0.05, 0.2, 15, 1);
	glPopMatrix();
}

void DrawL_HandRocket() {
	glPushMatrix();
	glColor3f(0.97, 0.75, 0.11);
	cyl = gluNewQuadric();
	glTranslatef(0, 0, L);
	gluCylinder(cyl, 0.05, 0.05, 0.2, 50, 1);
	glPopMatrix();
}

void DrawR_Arm(int x, int a, int b, int c) {
	glPushMatrix();
	glColor3f(r, g, b1);
	cyl = gluNewQuadric();
	glRotatef(x, a, b, c);
	glRotatef(90.0, 1.0, 0.0, 0.0);

	glTranslatef(-0.25, 0.0, 0.0);
	glRotatef(-15.0, 0.0, 1.0, 0.0);
	gluCylinder(cyl, 0.05, 0.05, 0.2, 50, 1);
}

void DrawR_Hand(int y, int a, int b, int c) {
	glPushMatrix();
	glColor3f(0.97, 0.75, 0.11);
	cyl = gluNewQuadric();
	glTranslatef(0.0, 0.0, 0.22);
	glRotatef(y, a, b, c);
	if (key == SKATE)
		gluCylinder(cyl, 0.05, 0.02, 0.2, 15, 1);
	else
		gluCylinder(cyl, 0.05, 0.05, 0.2, 15, 1);
	glPopMatrix();
}

void DrawR_HandRocket() {
	glPushMatrix();
	glColor3f(0.97, 0.75, 0.11);
	cyl = gluNewQuadric();
	glTranslatef(0, 0, R);
	gluCylinder(cyl, 0.05, 0.05, 0.2, 50, 1);
	glPopMatrix();
}

void DrawBody(int x, int a, int b, int c) {
	glPushMatrix();
	glColor3f(r, g, b1);
	cyl = gluNewQuadric();
	glRotatef(90.0, 1.0, 0.0, 0.0);
	glRotatef(x, a, b, c);
	gluCylinder(cyl, 0.2, 0.2, 0.45, 50, 1);
	glPopMatrix();
}

void DrawL_Legs(int x, int a, int b, int c) {
	glPushMatrix();
	glColor3f(0.97, 0.75, 0.11);
	cyl = gluNewQuadric();
	glRotatef(90.0, 1.0, 0.0, 0.0);

	glTranslatef(0.1, 0.0, 0.42);
	glRotatef(x, a, b, c);
	gluCylinder(cyl, 0.05, 0.05, 0.15, 50, 1);
}

void DrawL_foot(int y, int a, int b, int c) {
	glPushMatrix();
	glColor3f(0.98, 0.93, 0.77);
	cyl = gluNewQuadric();
	glTranslatef(0.0, 0.0, 0.18);
	if (key == SKATE)
		gluCylinder(cyl, 0.05, 0.02, 0.2, 15, 1);
	else
		gluCylinder(cyl, 0.05, 0.05, 0.2, 15, 1);
	glPopMatrix();
}

void DrawR_Legs(int x, int a, int b, int c) {
	glPushMatrix();
	glColor3f(0.97, 0.75, 0.11);
	cyl = gluNewQuadric();
	glRotatef(90.0, 1.0, 0.0, 0.0);
	glTranslatef(-0.1, 0.0, 0.42);
	glRotatef(x, a, b, c);

	gluCylinder(cyl, 0.05, 0.05, 0.15, 120, 1);
}

void DrawR_foot(int y, int a, int b, int c) {
	glPushMatrix();
	glColor3f(0.98, 0.93, 0.77);
	cyl = gluNewQuadric();
	glTranslatef(0.0, 0.0, 0.18);
	glRotatef(y, a, b, c);
	if (key == SKATE)
		gluCylinder(cyl, 0.05, 0.02, 0.2, 15, 1);
	else
		gluCylinder(cyl, 0.05, 0.05, 0.2, 15, 1);
	glPopMatrix();
}

void DrawNeck() {
	glPushMatrix();
	glColor3f(0.97, 0.75, 0.11);
	cyl = gluNewQuadric();
	glRotatef(90.0, 1.0, 0.0, 0.0);

	glTranslatef(0.0, 0.0, -0.045);
	gluCylinder(cyl, 0.2, 0.2, 0.025, 100, 1);
	glPopMatrix();
}

void DrawGround() {
	glColor3f(0.67, 0.95, 0.0);
	glTranslatef(0.0, -2.73, 0.0);
	glRotatef(45.0, 0, 1, 0);
	glRotatef(0.0 + time4 - 15, 0.0, 0.0, 1);
	gluSphere(cyl, 2.5, 30, 90);
}

void DrawHead() {
	glTranslatef(0.0, 0.02, 0.0);
	glPushMatrix();
	cyl = gluNewQuadric();

	gluSphere(cyl, 0.20, 30, 10);

	/*귀*/
	glScalef(2, 2, 1);
	glTranslatef(-0.1, 0.075, 0.03);
	glColor3f(0.97, 0.75, 0.11);
	gluSphere(cyl, 0.03, 10, 10);
	glPopMatrix();
	glPushMatrix();

	glScalef(2, 2, 1);
	glTranslatef(0.1, 0.075, 0.03);
	gluSphere(cyl, 0.03, 10, 10);
	glPopMatrix();
	glPushMatrix();

	/*눈 그리기*/
	glTranslatef(-0.1, 0.1, 0.13);
	glColor3f(0.0, 0.0, 0.0);
	gluSphere(cyl, 0.03, 10, 10);
	glPopMatrix();
	glPushMatrix();

	glTranslatef(0.1, 0.1, 0.13);
	gluSphere(cyl, 0.03, 10, 10);
	glPopMatrix();
	glPushMatrix();

	/*코*/
	glTranslatef(-0.03, 0.05, 0.18);
	glColor3f(1.0, 0.0, 0.0);
	gluSphere(cyl, 0.03, 10, 10);
	glPopMatrix();
	glPushMatrix();
}

void DrawBall()
{
	glTranslatef(-0.2, -0.7, 0.35);
	glColor3f(0.5, 0.3, 0.1);
	gluSphere(cyl, 0.12, 10, 10);
	glPopMatrix();
	glPushMatrix();
}

void DrawAndroid() {
	DrawBody(0, 0, 0, 0);
	DrawNeck();
	DrawHead();

	glTranslatef(0.9, 0.3, 0.13);
	drawCloud(0.1);
	glPushMatrix();

	DrawR_Arm(R_Arm_x, 1, 0, 0);
	if (key == ROCKET)
		DrawR_HandRocket();
	else
		DrawR_Hand(R_Arm_y, 1, 0, 0);
	DrawL_Arm(L_Arm_x, 1, 0, 0);
	if (key == ROCKET)
		DrawL_HandRocket();
	else
		DrawL_Hand(L_Arm_y, 1, 0, 0);
	DrawL_Legs(L_Leg_x, 1, 0, 0);
	DrawL_foot(L_Leg_y, 1, 0, 0);
	DrawR_Legs(R_Leg_x, 1, 0, 0);
	DrawR_foot(R_Leg_y, 1, 0, 0);
}
void Run() {
	glLoadIdentity();

	L_Arm_x = sin(time) * 80;
	R_Arm_x = -L_Arm_x;
	R_Arm_y = -abs(sin(time) * 60 + 50);
	L_Arm_y = -abs(-sin(time) * 60 + 50);

	R_Leg_y = abs(-sin(time) * 30 - 30);
	L_Leg_y = abs(sin(time) * 30 - 30);
	R_Leg_x = sin(time) * 60;
	L_Leg_x = -R_Leg_x;

	cyl = gluNewQuadric();
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	DrawGround();
	glLoadIdentity();

	glRotatef(-230.0, 0, 1, 0);
	glRotatef(abs(sin(time) * 16), 1, 0, 0);
	glRotatef(sin(time) * 16, 0, 1, 0);

	float i = 0;
	i = abs(sin(time)*0.08);
	glPushMatrix();
	glTranslatef(0.0, i, 0);
	glTranslatef(0.0, 0.5, 0.0);
	DrawAndroid();
	glutSwapBuffers();
}

void Soccer() {
	glLoadIdentity();
	L_Arm_x = sin(time) * 80;
	R_Arm_x = -L_Arm_x;
	R_Arm_y = -abs(sin(time) * 60 + 50);
	L_Arm_y = -abs(-sin(time) * 60 + 50);

	R_Leg_y = abs(-sin(time) * 30 - 30);
	L_Leg_y = abs(sin(time) * 30 - 30);
	R_Leg_x = sin(time) * 60;
	L_Leg_x = -R_Leg_x;

	cyl = gluNewQuadric();
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	DrawGround();
	glLoadIdentity();

	glRotatef(-230.0, 0, 1, 0);
	glRotatef(abs(sin(time) * 16), 1, 0, 0);
	glRotatef(sin(time) * 16, 0, 1, 0);

	float i = 0;
	i = abs(sin(time)*0.08);
	glPushMatrix();
	glTranslatef(0.0, i, 0);
	glTranslatef(0.0, 0.5, 0.0);
	DrawAndroid();
	DrawBall();
	glutSwapBuffers();
}

void Jap() {
	glLoadIdentity();
	glClearColor(0.95, 0.37, 0.37, 1.0);

	L_Arm_x = (-40) + sin(time2) * 60;

	R_Arm_x = (-80) - L_Arm_x;

	R_Arm_y = -abs(cos(time2) * 80);

	L_Arm_y = -abs(-cos(time2) * 80);
	R_Leg_y = abs(-sin(time) * 30 - 20);

	L_Leg_y = abs(sin(time) * 30 - 20);
	R_Leg_x = sin(time) * 30;

	L_Leg_x = -R_Leg_x;

	cyl = gluNewQuadric();
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);

	DrawGround();
	glLoadIdentity();
	glRotatef(-230.0, 0, 1, 0);
	glRotatef(sin(time) * 10, 0, 0, 1);

	float j = 0;
	j = abs(sin(time2)*0.085);
	glPushMatrix();
	glTranslatef(0.0, j, 0);
	glTranslatef(0.0, 0.5, 0.0);
	DrawAndroid();
	glutSwapBuffers();
}

void Show() {
	glLoadIdentity();

	L_Arm_x = (-40) + sin(time2) * 60;
	R_Arm_x = (-80) - L_Arm_x;
	R_Arm_y = -abs(cos(time2) * 10);
	L_Arm_y = -abs(-cos(time2) * 10);
	R_Leg_y = abs(-sin(time) * 30 - 30);
	L_Leg_y = abs(sin(time) * 30 - 30);
	R_Leg_x = sin(time) * 60;
	L_Leg_x = -R_Leg_x;

	cyl = gluNewQuadric();
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);

	DrawGround();
	glLoadIdentity();
	glRotatef(-230.0, 0, 1, 0);

	glRotatef(sin(time) * 7, 0, 0, 1);
	glRotatef(sin(time) * 7, 0, 1, 0);

	glTranslatef(0.0, 0.18, 0.0);
	glRotatef(80, 1, 0, 0);
	glTranslatef(0.0, 0.5, 0.0);
	glPushMatrix();
	DrawBody(0, 0, 0, 0);
	glPopMatrix();
	glPushMatrix();

	DrawNeck();
	glPopMatrix();
	glPushMatrix();

	glRotatef(-75, 1, 0, 0);
	glTranslatef(0.0, -0.02, 0.0);
	DrawHead();
	glPopMatrix();
	glPushMatrix();

	DrawR_Arm((R_Arm_y + 30), 1, 0, 0);
	DrawR_Hand(-(R_Arm_y - 15), 1, 0, 0);
	glPopMatrix();
	glPushMatrix();

	glTranslatef(0.0, -0.16, -0.04);
	glRotatef(40, 0, 0, 1);
	DrawL_Arm((L_Arm_y + 30), 1, 0, 0);
	DrawL_Hand(-(L_Arm_y - 15), 1, 0, 0);
	glPopMatrix();
	glPushMatrix();

	glTranslatef(0.0, -0.45, -0.25);
	glRotatef(-90, 1, 0, 0);
	DrawL_Legs(-30, 1, 0, 0);
	DrawL_foot(10, 1, 0, 0);
	glPopMatrix();
	glPushMatrix();

	glTranslatef(0.0, -0.5, -0.5);
	glRotatef(-90, 1, 0, 0);
	DrawR_Legs(160, 1, 0, 0);
	DrawR_foot(R_Leg_y, 1, 0, 0);
	glPopMatrix();
	glPushMatrix();
	glutSwapBuffers();
}

void Rocket() {
	glLoadIdentity();
	glClearColor(0.16, 0.0, 0.4, 1.0);
	L_Arm_x = -90;
	R_Arm_x = -90;
	L = 2 * abs(-sin(time2)*0.2 - 0.2) + 0.2;

	R = 2 * abs(sin(time2)*0.2 - 0.2) + 0.2;
	R_Leg_y = abs(-sin(time) * 30 - 30);
	L_Leg_y = abs(sin(time) * 30 - 30);
	R_Leg_x = sin(time) * 60;
	L_Leg_x = -R_Leg_x;

	cyl = gluNewQuadric();
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);

	DrawGround();
	glLoadIdentity();
	glPushMatrix();
	glRotatef(-230.0, 0, 1, 0);

	glRotatef(-abs(sin(time) * 8), 1, 0, 0);
	glRotatef(sin(time) * 7, 0, 0, 1);

	float i = 0;
	i = abs(sin(time) * 7);
	glTranslatef(0.0, i, 0);
	glTranslatef(0.0, 0.5, 0.0);
	DrawAndroid();
	glutSwapBuffers();
}

void Skate() {
	glLoadIdentity();

	L_Arm_x = (-40) + sin(time2) * 60;
	R_Arm_x = (-80) - L_Arm_x;
	R_Arm_y = -abs(cos(time2) * 10);
	L_Arm_y = -abs(-cos(time2) * 10);
	R_Leg_y = abs(-sin(time) * 30 - 30);
	L_Leg_y = abs(sin(time) * 30 - 30);
	R_Leg_x = sin(time) * 60;
	L_Leg_x = -R_Leg_x;

	cyl = gluNewQuadric();
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);

	DrawGround();
	glLoadIdentity();
	glRotatef(-230.0, 0, 1, 0);

	glRotatef(sin(time) * 7, 0, 0, 1);
	glRotatef(sin(time) * 7, 0, 1, 0);

	glTranslatef(0.0, 0.18, 0.0);
	glRotatef(80, 1, 0, 0);
	glTranslatef(0.0, 0.5, 0.0);
	glPushMatrix();
	DrawBody(0, 0, 0, 0);
	glPopMatrix();
	glPushMatrix();

	DrawNeck();
	glPopMatrix();
	glPushMatrix();

	glRotatef(-75, 1, 0, 0);
	glTranslatef(0.0, -0.02, 0.0);
	DrawHead();
	glPopMatrix();
	glPushMatrix();

	DrawR_Arm((R_Arm_y + 30), 1, 0, 0);
	DrawR_Hand(-(R_Arm_y - 15), 1, 0, 0);
	glPopMatrix();
	glPushMatrix();

	glTranslatef(0.0, -0.16, -0.04);
	glRotatef(40, 0, 0, 1);
	DrawL_Arm((L_Arm_y + 30), 1, 0, 0);
	DrawL_Hand(-(L_Arm_y - 15), 1, 0, 0);
	glPopMatrix();
	glPushMatrix();

	glTranslatef(0.0, -0.45, -0.25);
	glRotatef(-90, 1, 0, 0);
	DrawL_Legs(-30, 1, 0, 0);
	DrawL_foot(10, 1, 0, 0);
	glPopMatrix();
	glPushMatrix();

	glTranslatef(0.0, -0.5, -0.5);
	glRotatef(-90, 1, 0, 0);
	DrawR_Legs(160, 1, 0, 0);
	DrawR_foot(R_Leg_y, 1, 0, 0);
	glPopMatrix();
	glPushMatrix();
	glutSwapBuffers();
}


void keyboard_handler(unsigned char Keyboard, int x, int y)
{
	switch (Keyboard) {
	case 'a':
		key = RUN;
		break;
	case 'd':
		key = JAP;
		break;

	case 'w':
		key = ROCKET;
		break;
	case 's':
		key = SKATE;
		break;
	case 'c':
		if (flag == 1) {
			r = 0.0, g = 0.0, b1 = 1.0;
			flag = 2;
		}
		else if (flag == 2) {
			r = 0.4, g = 0.0, b1 = 1.0;
			flag = 3;
		}
		else if (flag == 3) {
			r = 1.0, g = 0.5, b = 0.5;
			flag = 1;
		}
		break;
	case 'v':
		r = 1.0, g = 0.0, b1 = 0.0;
		break;
	case 'b':
		key = SOCCER;
		break;
	}
}


void display() {
	// clear background
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(0.83, 0.96, 0.98, 1.0);
	if (key == RUN) {
		Run();
		glPopMatrix();

	}
	else if (key == JAP) {
		Jap();
		glPopMatrix();
	}
	else if (key == ROCKET) {
		Rocket();
		glPopMatrix();
	}
	else if (key == SKATE) {
		Skate();
		glPopMatrix();
	}
	else if (key == SOCCER) {
		Soccer();
		glPopMatrix();
	}
}

void timer(int Value)
{
	time = time + 0.1;
	time2 = time2 + 0.5;
	time3 = time3 + 0.01;

	time4 = time4 + 1.0;
	glutPostRedisplay();
	glutTimerFunc(40, timer, 1);
}

int main(int argc, char ** argv) {
	// GLUT initialization
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
	glutInitWindowSize(500, 500);
	glutCreateWindow("Let's move!");
	glutInitWindowPosition(0, 0);

	// call-back functions
	glutKeyboardFunc(keyboard_handler);
	glutTimerFunc(40, timer, 1);
	glutDisplayFunc(display);
	init();
	glutMainLoop();

	system("pause");

	return 0;
}
