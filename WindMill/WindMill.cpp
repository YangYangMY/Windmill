
#include <Windows.h>
#include <gl/GL.h>
#include <math.h>

#pragma comment (lib, "OpenGL32.lib")

#define WINDOW_TITLE "OpenGL Window"


int qNo = 0;

float x = 0, y = 0; //Origin of circle
float x2 = 0, y2 = 0;  //Point of circle
float r = 0.5; //radius of circle
float PI = 3.1429; //PI
float NoOfTri = 36; //Number of triangle in a circle
float angle = 0;  //Angle
float circle_points = 100.0f;

//wind turbine
float speed = 0.0f;
float step_angle = -0.01f;
float center_x = 0.095;
float center_y = 0.594;

float pigx = -3.5;
float pigspeed1 = 0.0001, pigspeed2 = -0.0001;
boolean check = true;

LRESULT WINAPI WindowProcedure(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		break;

	case WM_KEYDOWN:
		if (wParam == VK_ESCAPE) PostQuitMessage(0);
		else if (wParam == VK_UP)
			step_angle += 0.05f;
		else if (wParam == VK_DOWN)
			step_angle -= 0.05f;
		else if (wParam == VK_LEFT)
			qNo--;
		else if (wParam == VK_RIGHT)
			qNo++;
		else if (wParam == 0x20)
			step_angle = 0, pigx = -3.5;
		else if (wParam == 0x41)
			pigx -= 0.1;
		else if (wParam == 0x44)
			pigx += 0.1;
		else if (wParam == 0x51)
			check = true;
		else if (wParam == 0x45)
			check = false;
		break;
	default:
		break;
	}

	if (qNo <= 0) {
		qNo = 1;
	}
	if (qNo >= 5) {
		qNo = 4;
	}

	return DefWindowProc(hWnd, msg, wParam, lParam);
}
//--------------------------------------------------------------------

bool initPixelFormat(HDC hdc)
{
	PIXELFORMATDESCRIPTOR pfd;
	ZeroMemory(&pfd, sizeof(PIXELFORMATDESCRIPTOR));

	pfd.cAlphaBits = 8;
	pfd.cColorBits = 32;
	pfd.cDepthBits = 24;
	pfd.cStencilBits = 0;

	pfd.dwFlags = PFD_DOUBLEBUFFER | PFD_SUPPORT_OPENGL | PFD_DRAW_TO_WINDOW;

	pfd.iLayerType = PFD_MAIN_PLANE;
	pfd.iPixelType = PFD_TYPE_RGBA;
	pfd.nSize = sizeof(PIXELFORMATDESCRIPTOR);
	pfd.nVersion = 1;

	// choose pixel format returns the number most similar pixel format available
	int n = ChoosePixelFormat(hdc, &pfd);

	// set pixel format returns whether it sucessfully set the pixel format
	if (SetPixelFormat(hdc, n, &pfd))
	{
		return true;
	}
	else
	{
		return false;
	}
}
//--------------------------------------------------------------------

void AnyaFace() {
	glTranslatef(0.095, 0.35, 0);
	glScalef(0.08, 0.08, 0);
	//FACE
	glColor3f(0.9843, 0.9137, 0.8588);
	glBegin(GL_TRIANGLE_FAN);
	glVertex2f(0, 0);
	for (angle = 0; angle <= 2 * PI; angle += (2 * PI) / NoOfTri) {
		x2 = x + r * cos(angle);
		y2 = x + r * sin(angle);
		glVertex2f(x2, y2);
	}
	glEnd();

	glColor3f(0, 0, 0);
	glBegin(GL_LINE_STRIP);
	glVertex2f(0.5, 0);
	for (angle = 0; angle <= 2 * PI; angle += (2 * PI) / NoOfTri) {
		x2 = x + 0.501 * cos(angle);
		y2 = x + 0.501 * sin(angle);
		glVertex2f(x2, y2);
	}
	glEnd();

	//Hair
	glLoadIdentity();
	glTranslatef(0.095, 0.35, 0);
	glScalef(0.08, 0.08, 0);
	glTranslatef(0, 0.001, 0);
	glColor3f(0.9647, 0.6745, 0.6313);
	glBegin(GL_TRIANGLE_FAN);
	glVertex2f(0, 0.4);
	for (float angle1 = 0; angle1 <= PI; angle1 += (PI) / NoOfTri) {
		x2 = x + 0.6 * cos(angle1);
		y2 = x + 0.6 * sin(angle1);
		glVertex2f(x2, y2);
	}
	glEnd();
	glColor3f(0, 0, 0);
	glBegin(GL_LINE_LOOP);
	glVertex2f(0, 0.4);
	for (float angle1 = 0; angle1 <= PI; angle1 += (PI) / NoOfTri) {
		x2 = x + 0.6 * cos(angle1);
		y2 = x + 0.6 * sin(angle1);
		glVertex2f(x2, y2);
	}
	glEnd();


	//SMALL LEAF HAIR
	glLoadIdentity();
	glTranslatef(0.095, 0.35, 0);
	glScalef(0.08, 0.08, 0);
	glRotatef(-10, 0, 0.0, 1);
	glTranslatef(-0.1, 0.65, 0);
	glColor3f(0.9647, 0.6745, 0.6313);
	glBegin(GL_TRIANGLE_FAN);
	glVertex2f(0, 0);
	for (angle = 0; angle <= 2 * PI; angle += (2 * PI) / NoOfTri) {
		x2 = x + 0.02 * cos(angle);
		y2 = x + 0.09 * sin(angle);
		glVertex2f(x2, y2);
	}
	glEnd();

	glColor3f(0, 0, 0);
	glBegin(GL_LINE_STRIP);
	glVertex2f(0.02, 0);
	for (angle = 0; angle <= 2 * PI; angle += (2 * PI) / NoOfTri) {
		x2 = x + 0.02 * cos(angle);
		y2 = x + 0.09 * sin(angle);
		glVertex2f(x2, y2);
	}
	glEnd();
	glLoadIdentity();
	glTranslatef(0.095, 0.35, 0);
	glScalef(0.08, 0.08, 0);
	//Right Side HAIR
	glColor3f(0.9647, 0.6745, 0.6313);
	glBegin(GL_POLYGON);
	glVertex2f(0.5, 0.15);
	glVertex2f(0.35, 0.4);
	glVertex2f(0.45, 0.2);
	glVertex2f(0.47, 0.12);
	glVertex2f(0.465, 0.09);
	glVertex2f(0.45, 0);
	glVertex2f(0.32, -0.5);
	glVertex2f(0.32, -0.7);
	glVertex2f(0.45, -0.6);
	glVertex2f(0.55, -0.5);
	glVertex2f(0.61, -0.4);
	glVertex2f(0.64, -0.3);
	glVertex2f(0.65, -0.1);
	glVertex2f(0.63, 0);
	glVertex2f(0.59, 0.1);
	glVertex2f(0.55, 0.2);
	glVertex2f(0.52, 0.29);
	glVertex2f(0.49, 0.34);
	glEnd();

	glColor3f(0, 0, 0);
	glBegin(GL_LINE_STRIP);
	glVertex2f(0.35, 0.4);
	glVertex2f(0.45, 0.2);
	glVertex2f(0.47, 0.10);
	glVertex2f(0.465, 0.08);
	glVertex2f(0.46, 0.04);
	glVertex2f(0.45, 0);
	glVertex2f(0.32, -0.5);
	glVertex2f(0.32, -0.7);
	glVertex2f(0.45, -0.6);
	glVertex2f(0.55, -0.5);
	glVertex2f(0.61, -0.4);
	glVertex2f(0.64, -0.3);
	glVertex2f(0.65, -0.1);
	glVertex2f(0.63, 0);
	glVertex2f(0.59, 0.1);
	glVertex2f(0.57, 0.2);
	glVertex2f(0.53, 0.29);
	glVertex2f(0.49, 0.34);
	glEnd();

	//Left Side HAIR
	glColor3f(0.9647, 0.6745, 0.6313);
	glBegin(GL_POLYGON);
	glVertex2f(-0.5, 0.15);
	glVertex2f(-0.35, 0.4);
	glVertex2f(-0.45, 0.2);
	glVertex2f(-0.47, 0.12);
	glVertex2f(-0.465, 0.09);
	glVertex2f(-0.45, 0);
	glVertex2f(-0.32, -0.5);
	glVertex2f(-0.32, -0.7);
	glVertex2f(-0.45, -0.6);
	glVertex2f(-0.55, -0.5);
	glVertex2f(-0.61, -0.4);
	glVertex2f(-0.64, -0.3);
	glVertex2f(-0.65, -0.1);
	glVertex2f(-0.63, 0);
	glVertex2f(-0.59, 0.1);
	glVertex2f(-0.55, 0.2);
	glVertex2f(-0.52, 0.29);
	glVertex2f(-0.49, 0.34);
	glEnd();

	glColor3f(0, 0, 0);
	glBegin(GL_LINE_STRIP);
	glVertex2f(-0.35, 0.4);
	glVertex2f(-0.45, 0.2);
	glVertex2f(-0.47, 0.12);
	glVertex2f(-0.465, 0.09);
	glVertex2f(-0.45, 0);
	glVertex2f(-0.32, -0.5);
	glVertex2f(-0.32, -0.7);
	glVertex2f(-0.45, -0.6);
	glVertex2f(-0.55, -0.5);
	glVertex2f(-0.61, -0.4);
	glVertex2f(-0.64, -0.3);
	glVertex2f(-0.65, -0.1);
	glVertex2f(-0.63, 0);
	glVertex2f(-0.59, 0.1);
	glVertex2f(-0.57, 0.2);
	glVertex2f(-0.53, 0.29);
	glVertex2f(-0.49, 0.34);
	glEnd();

	//FRONT HAIR 1
	glColor3f(0.9647, 0.6745, 0.6313);
	glBegin(GL_POLYGON);
	glVertex2f(-0.36, 0.30);
	glVertex2f(-0.37, 0.25);
	glVertex2f(-0.375, 0.2);
	glVertex2f(-0.36, 0.1);
	glVertex2f(-0.35, 0.08);
	glVertex2f(-0.33, 0.06);
	glVertex2f(-0.3, 0.04);
	glVertex2f(-0.30, 0.07);
	glVertex2f(-0.295, 0.1);
	glVertex2f(-0.285, 0.13);
	glVertex2f(-0.28, 0.16);
	glVertex2f(-0.27, 0.19);
	glVertex2f(-0.26, 0.22);
	glVertex2f(-0.25, 0.25);
	glVertex2f(-0.24, 0.28);
	glEnd();


	glColor3f(0, 0, 0);
	glBegin(GL_LINE_STRIP);
	glVertex2f(-0.34, 0.33);
	glVertex2f(-0.36, 0.30);
	glVertex2f(-0.37, 0.25);
	glVertex2f(-0.375, 0.2);
	glVertex2f(-0.36, 0.1);
	glVertex2f(-0.35, 0.08);
	glVertex2f(-0.33, 0.06);
	glVertex2f(-0.3, 0.04);
	glVertex2f(-0.30, 0.07);
	glVertex2f(-0.295, 0.1);
	glVertex2f(-0.285, 0.13);
	glVertex2f(-0.28, 0.16);
	glVertex2f(-0.27, 0.19);
	glVertex2f(-0.26, 0.22);
	glVertex2f(-0.25, 0.25);
	glVertex2f(-0.24, 0.28);
	glEnd();

	//FRONT HAIR 2
	glColor3f(0.9647, 0.6745, 0.6313);
	glBegin(GL_POLYGON);
	glVertex2f(-0.2, 0.45);
	glVertex2f(-0.21, 0.42);
	glVertex2f(-0.22, 0.39);
	glVertex2f(-0.23, 0.37);
	glVertex2f(-0.24, 0.28);
	glVertex2f(-0.23, 0.25);
	glVertex2f(-0.22, 0.22);
	glVertex2f(-0.21, 0.19);
	glVertex2f(-0.2, 0.16);
	glVertex2f(-0.15, 0.13);
	glVertex2f(-0.12, 0.11);
	glVertex2f(-0.115, 0.105);
	glVertex2f(-0.1, 0.1);
	glVertex2f(-0.12, 0.15);
	glVertex2f(-0.13, 0.18);
	glVertex2f(-0.14, 0.21);
	glVertex2f(-0.13, 0.18);
	glVertex2f(-0.12, 0.15);
	glVertex2f(-0.11, 0.125);
	glVertex2f(-0.1, 0.099);
	glVertex2f(-0.03, 0.06);
	glVertex2f(0.01, 0.04);
	glVertex2f(0.01, 0.07);
	glVertex2f(-0.0005, 0.085);
	glVertex2f(-0.001, 0.1);
	glVertex2f(-0.009, 0.15);
	glVertex2f(-0.05, 0.2);
	glVertex2f(-0.009, 0.15);
	glVertex2f(0.01, 0.1);
	glVertex2f(0.05, 0.05);
	glVertex2f(0.1, 0.025);
	glVertex2f(0.12, 0.025);
	glVertex2f(0.11, 0.04);
	glVertex2f(0.10, 0.08);
	glVertex2f(0.09, 0.12);
	glVertex2f(0.08, 0.15);
	glVertex2f(0.07, 0.19);
	glVertex2f(0.06, 0.24);
	glVertex2f(0.065, 0.27);
	glVertex2f(0.07, 0.3);
	glVertex2f(0.08, 0.35);
	glVertex2f(0.09, 0.39);
	glEnd();

	glColor3f(0, 0, 0);
	glBegin(GL_LINE_STRIP);
	glVertex2f(-0.2, 0.45);
	glVertex2f(-0.21, 0.42);
	glVertex2f(-0.22, 0.39);
	glVertex2f(-0.23, 0.37);
	glVertex2f(-0.24, 0.28);
	glVertex2f(-0.23, 0.25);
	glVertex2f(-0.22, 0.22);
	glVertex2f(-0.21, 0.19);
	glVertex2f(-0.2, 0.16);
	glVertex2f(-0.15, 0.13);
	glVertex2f(-0.1, 0.1);
	glVertex2f(-0.12, 0.15);
	glVertex2f(-0.13, 0.18);
	glVertex2f(-0.14, 0.21);
	glVertex2f(-0.13, 0.18);
	glVertex2f(-0.12, 0.15);
	glVertex2f(-0.1, 0.099);
	glVertex2f(-0.03, 0.06);
	glVertex2f(0.01, 0.04);
	glVertex2f(0.01, 0.07);
	glVertex2f(-0.0005, 0.085);
	glVertex2f(-0.001, 0.1);
	glVertex2f(-0.009, 0.15);
	glVertex2f(-0.05, 0.2);
	glVertex2f(-0.009, 0.15);
	glVertex2f(0.01, 0.1);
	glVertex2f(0.05, 0.05);
	glVertex2f(0.1, 0.025);
	glVertex2f(0.12, 0.025);
	glVertex2f(0.11, 0.04);
	glVertex2f(0.10, 0.08);
	glVertex2f(0.09, 0.12);
	glVertex2f(0.08, 0.15);
	glVertex2f(0.07, 0.19);
	glVertex2f(0.06, 0.24);
	glVertex2f(0.065, 0.27);
	glVertex2f(0.07, 0.3);
	glVertex2f(0.08, 0.35);
	glVertex2f(0.09, 0.39);
	glEnd();

	//FRONT HAIR 3 
	glColor3f(0.9647, 0.6745, 0.6313);
	glBegin(GL_POLYGON);
	glVertex2f(0.09, 0.39);
	glVertex2f(0.08, 0.35);
	glVertex2f(0.07, 0.3);
	glVertex2f(0.065, 0.27);
	glVertex2f(0.07, 0.25);
	glVertex2f(0.08, 0.22);
	glVertex2f(0.1, 0.18);
	glVertex2f(0.12, 0.14);
	glVertex2f(0.15, 0.1);
	glVertex2f(0.19, 0.08);
	glVertex2f(0.21, 0.07);
	glVertex2f(0.2, 0.11);
	glVertex2f(0.19, 0.15);
	glVertex2f(0.18, 0.19);
	glVertex2f(0.19, 0.23);
	glVertex2f(0.195, 0.26);
	glVertex2f(0.2, 0.29);
	glVertex2f(0.205, 0.31);
	glVertex2f(0.2, 0.29);
	glVertex2f(0.195, 0.26);
	glVertex2f(0.21, 0.22);
	glVertex2f(0.23, 0.19);
	glVertex2f(0.25, 0.16);
	glVertex2f(0.29, 0.13);
	glVertex2f(0.33, 0.1);
	glVertex2f(0.335, 0.12);
	glVertex2f(0.34, 0.16);
	glVertex2f(0.33, 0.19);
	glVertex2f(0.325, 0.21);
	glEnd();

	glBegin(GL_POLYGON);
	glVertex2f(0.33, 0.19);//go back down
	glVertex2f(0.34, 0.16);
	glVertex2f(0.335, 0.12);
	glVertex2f(0.325, 0.09);
	glVertex2f(0.32, 0.05);
	glVertex2f(0.34, 0.065);
	glVertex2f(0.36, 0.08);
	glVertex2f(0.38, 0.095);
	glVertex2f(0.4, 0.12);
	glVertex2f(0.42, 0.16);
	glVertex2f(0.425, 0.2);
	glVertex2f(0.43, 0.24);
	glEnd();


	glColor3f(0, 0, 0);
	glBegin(GL_LINE_STRIP);
	glVertex2f(0.09, 0.39);
	glVertex2f(0.08, 0.35);
	glVertex2f(0.07, 0.3);
	glVertex2f(0.065, 0.27);
	glVertex2f(0.07, 0.25);
	glVertex2f(0.08, 0.22);
	glVertex2f(0.1, 0.18);
	glVertex2f(0.12, 0.14);
	glVertex2f(0.15, 0.1);
	glVertex2f(0.19, 0.08);
	glVertex2f(0.21, 0.07);
	glVertex2f(0.2, 0.11);
	glVertex2f(0.19, 0.15);
	glVertex2f(0.18, 0.19);
	glVertex2f(0.19, 0.23);
	glVertex2f(0.195, 0.26);
	glVertex2f(0.2, 0.29);
	glVertex2f(0.205, 0.31);
	glVertex2f(0.2, 0.29);
	glVertex2f(0.195, 0.26);
	glVertex2f(0.21, 0.22);
	glVertex2f(0.23, 0.19);
	glVertex2f(0.25, 0.16);
	glVertex2f(0.29, 0.13);
	glVertex2f(0.33, 0.1);
	glVertex2f(0.335, 0.12);
	glVertex2f(0.34, 0.16);
	glVertex2f(0.33, 0.19);
	glVertex2f(0.325, 0.21);
	glVertex2f(0.33, 0.19);//go back down
	glVertex2f(0.34, 0.16);
	glVertex2f(0.335, 0.12);
	glVertex2f(0.325, 0.09);
	glVertex2f(0.32, 0.05);
	glVertex2f(0.34, 0.065);
	glVertex2f(0.36, 0.08);
	glVertex2f(0.38, 0.095);
	glVertex2f(0.4, 0.12);
	glVertex2f(0.42, 0.16);
	glVertex2f(0.425, 0.2);
	glVertex2f(0.43, 0.24);
	glEnd();


	//HAIR details 1 - TOP
	GLfloat circle_points = 100.0f;
	glLoadIdentity();
	glTranslatef(0.095, 0.35, 0);
	glScalef(0.08, 0.08, 0);
	glRotatef(25, 0, 0.0, 1);
	glTranslatef(0.12, 0.53, 0);
	glBegin(GL_LINE_STRIP);
	glColor3f(0, 0, 0);
	glVertex2f(0.1, 0);
	for (float angle1 = 0; angle1 <= PI; angle1 += (PI) / NoOfTri) {
		x2 = x + 0.2 * cos(angle1) / 2;
		y2 = x + 0.03 * sin(angle1) / 2;
		glVertex2f(x2, y2);
	}
	glEnd();
	glLoadIdentity();

	glLoadIdentity();
	glTranslatef(0.095, 0.35, 0);
	glScalef(0.08, 0.08, 0);
	glRotatef(-25, 0, 0.0, 1);
	glTranslatef(-0.15, 0.53, 0);
	glBegin(GL_LINE_STRIP);
	glColor3f(0, 0, 0);
	glVertex2f(0.05, 0);
	for (float angle1 = 0; angle1 <= PI; angle1 += (PI) / NoOfTri) {
		x2 = x + 0.1 * cos(angle1) / 2;
		y2 = x + 0.03 * sin(angle1) / 2;
		glVertex2f(x2, y2);
	}
	glEnd();
	glLoadIdentity();

	//HAIR details 2 - Left
	glLoadIdentity();
	glTranslatef(0.095, 0.35, 0);
	glScalef(0.08, 0.08, 0);
	glRotatef(115, 0, 0.0, 1);
	glTranslatef(0.05, 0.5, 0);
	glBegin(GL_LINE_STRIP);
	glColor3f(0, 0, 0);
	glVertex2f(0.27, 0);
	for (float angle1 = 0; angle1 <= PI; angle1 += (PI) / NoOfTri) {
		x2 = x + 0.53 * cos(angle1) / 2;
		y2 = x + 0.1 * sin(angle1) / 2;
		glVertex2f(x2, y2);
	}
	glEnd();
	glLoadIdentity();

	//HAIR details 2 - Right
	glLoadIdentity();
	glTranslatef(0.095, 0.35, 0);
	glScalef(0.08, 0.08, 0);
	glRotatef(-115, 0, 0.0, 1);
	glTranslatef(-0.05, 0.5, 0);
	glBegin(GL_LINE_STRIP);
	glColor3f(0, 0, 0);
	glVertex2f(0.27, 0);
	for (float angle1 = 0; angle1 <= PI; angle1 += (PI) / NoOfTri) {
		x2 = x + 0.53 * cos(angle1) / 2;
		y2 = x + 0.1 * sin(angle1) / 2;
		glVertex2f(x2, y2);
	}
	glEnd();
	glLoadIdentity();

	//hat
	glTranslatef(0.095, 0.35, 0);
	glScalef(0.08, 0.08, 0);
	glBegin(GL_TRIANGLES);
	glColor3f(0.1490, 0.1372, 0.11764);
	glVertex2f(-0.5, 0.34);
	glVertex2f(-0.6, 0.54);
	glVertex2f(-0.34, 0.5);

	glVertex2f(0.5, 0.34);
	glVertex2f(0.6, 0.54);
	glVertex2f(0.34, 0.5);
	glEnd();

	//yellow color band for hat
	glBegin(GL_POLYGON);
	glColor3f(0.7843, 0.7294, 0.4431);
	glVertex2f(-0.51, 0.36);
	glVertex2f(-0.53, 0.4);
	glVertex2f(-0.37, 0.505);
	glVertex2f(-0.4, 0.51);

	glEnd();

	glBegin(GL_POLYGON);
	glColor3f(0.7843, 0.7294, 0.4431);
	glVertex2f(0.51, 0.36);
	glVertex2f(0.53, 0.4);
	glVertex2f(0.37, 0.505);
	glVertex2f(0.4, 0.51);
	glEnd();
	glLoadIdentity();
}

void DrawBackground() {
	//1. GREEN FLOOR - MIDDLE
	glColor3f(0.54509, 0.70196, 0.22352);
	glBegin(GL_POLYGON);
	glVertex2f(-0.9, 0);
	glVertex2f(0.9, 0);
	glVertex2f(0.9, -0.1);
	glVertex2f(-0.9, -0.1);
	glEnd();

	//1. GREEN FLOOR - LEFT
	circle_points = 100.0f;
	glPushMatrix();
	glRotatef(90, 0, 0.0, 1);
	glTranslatef(-0.05, 0.9, 0);
	glBegin(GL_TRIANGLE_FAN);
	glColor3f(0.54509, 0.70196, 0.22352);
	glVertex2f(0.052, 0);
	for (float angle1 = 0; angle1 <= PI; angle1 += (PI) / NoOfTri) {
		x2 = x + 0.052 * cos(angle1);
		y2 = x + 0.052 * sin(angle1);
		glVertex2f(x2, y2);
	}
	glEnd();
	glPopMatrix();

	//1. GREEN FLOOR - RIGHT
	circle_points = 100.0f;
	glPushMatrix();
	glRotatef(-90, 0, 0.0, 1);
	glTranslatef(0.05, 0.9, 0);
	glBegin(GL_TRIANGLE_FAN);
	glColor3f(0.54509, 0.70196, 0.22352);
	glVertex2f(0.052, 0);
	for (float angle1 = 0; angle1 <= PI; angle1 += (PI) / NoOfTri) {
		x2 = x + 0.052 * cos(angle1);
		y2 = x + 0.052 * sin(angle1);
		glVertex2f(x2, y2);
	}
	glEnd();
	glPopMatrix();

	//1. Green Floor - GRASS LINE
	glLineWidth(4);
	glColor3f(0.40392, 0.56862, 0.20392);
	glBegin(GL_LINE_STRIP);
	glVertex2f(-0.945, -0.03);
	glVertex2f(-0.9, -0.07);
	glVertex2f(-0.855, -0.03);
	glVertex2f(-0.810, -0.07);
	glVertex2f(-0.765, -0.03);
	glVertex2f(-0.72, -0.07);
	glVertex2f(-0.675, -0.03);
	glVertex2f(-0.63, -0.07);
	glVertex2f(-0.585, -0.03);
	glVertex2f(-0.54, -0.07);
	glVertex2f(-0.495, -0.03);
	glVertex2f(-0.45, -0.07);
	glVertex2f(-0.405, -0.03);
	glVertex2f(-0.36, -0.07);
	glVertex2f(-0.315, -0.03);
	glVertex2f(-0.27, -0.07);
	glVertex2f(-0.225, -0.03);
	glVertex2f(-0.18, -0.07);
	glVertex2f(-0.135, -0.03);
	glVertex2f(-0.09, -0.07);
	glVertex2f(-0.045, -0.03);
	glVertex2f(0, -0.07);
	glVertex2f(0.045, -0.03);
	glVertex2f(0.09, -0.07);
	glVertex2f(0.135, -0.03);
	glVertex2f(0.18, -0.07);
	glVertex2f(0.225, -0.03);
	glVertex2f(0.27, -0.07);
	glVertex2f(0.315, -0.03);
	glVertex2f(0.36, -0.07);
	glVertex2f(0.405, -0.03);
	glVertex2f(0.45, -0.07);
	glVertex2f(0.495, -0.03);
	glVertex2f(0.54, -0.07);
	glVertex2f(0.585, -0.03);
	glVertex2f(0.63, -0.07);
	glVertex2f(0.675, -0.03);
	glVertex2f(0.72, -0.07);
	glVertex2f(0.765, -0.03);
	glVertex2f(0.81, -0.07);
	glVertex2f(0.855, -0.03);
	glVertex2f(0.9, -0.07);
	glVertex2f(0.945, -0.03);
	glEnd();

	//1.Green Floor - Dirt 1
	glColor3f(0.247058, 0.24705, 0.2);
	glBegin(GL_POLYGON);
	glVertex2f(-0.9, -0.1);
	glVertex2f(-0.45, -0.5);
	glVertex2f(0.8, -0.2);
	glVertex2f(0.9, -0.1);
	glEnd();

	//1.Green Floor - Dirt 2
	glColor3f(0.415686, 0.38431, 0.31764);
	glBegin(GL_POLYGON);
	glVertex2f(-0.88, -0.1);
	glVertex2f(-0.82, -0.15);
	glVertex2f(0.84, -0.13);
	glVertex2f(0.89, -0.1);
	glEnd();

	//1.Green Floor - Dirt 3
	glColor3f(0.2039215, 0.18823, 0.145098);
	glBegin(GL_POLYGON);
	glVertex2f(-0.68, -0.3);
	glVertex2f(0.15, -0.6);
	glVertex2f(0.8, -0.2);
	glEnd();

	//2. Background - SKY
	glPushMatrix();
	glColor3f(0.26274, 0.76078, 0.82745);
	glTranslatef(0, 0, 0);
	glBegin(GL_TRIANGLE_FAN);
	glVertex2f(0, 0);
	for (angle = 0; angle <= PI; angle += (PI) / NoOfTri) {
		x2 = x + 0.85 * cos(angle);
		y2 = x + 0.9 * sin(angle);
		glVertex2f(x2, y2);
	}
	glEnd();
	glPopMatrix();

	//2. Background - HILL 1
	glPushMatrix();
	glColor3f(0.17254, 0.45098, 0.223529);
	glTranslatef(-0.1, 0, 0);
	glBegin(GL_TRIANGLE_FAN);
	glVertex2f(0, 0);
	for (angle = 0; angle <= PI; angle += (PI) / NoOfTri) {
		x2 = x + 0.3 * cos(angle);
		y2 = x + 0.15 * sin(angle);
		glVertex2f(x2, y2);
	}
	glEnd();
	glPopMatrix();

	//2. Background - HILL 1
	glPushMatrix();
	glColor3f(0.341176, 0.541176, 0.2470588);
	glTranslatef(0.45, 0, 0);
	glBegin(GL_TRIANGLE_FAN);
	glVertex2f(0, 0);
	for (angle = 0; angle <= PI; angle += (PI) / NoOfTri) {
		x2 = x + 0.35 * cos(angle);
		y2 = x + 0.2 * sin(angle);
		glVertex2f(x2, y2);
	}
	glEnd();
	glPopMatrix();
}

void DrawBackground1() {
	//1. GREEN FLOOR - MIDDLE
	glColor3f(0.54509, 0.70196, 0.22352);
	glBegin(GL_POLYGON);
	glVertex2f(-0.9, 0);
	glVertex2f(0.9, 0);
	glVertex2f(0.9, -0.1);
	glVertex2f(-0.9, -0.1);
	glEnd();

	//1. GREEN FLOOR - LEFT
	circle_points = 100.0f;
	glPushMatrix();
	glRotatef(90, 0, 0.0, 1);
	glTranslatef(-0.05, 0.9, 0);
	glBegin(GL_TRIANGLE_FAN);
	glColor3f(0.54509, 0.70196, 0.22352);
	glVertex2f(0.052, 0);
	for (float angle1 = 0; angle1 <= PI; angle1 += (PI) / NoOfTri) {
		x2 = x + 0.052 * cos(angle1);
		y2 = x + 0.052 * sin(angle1);
		glVertex2f(x2, y2);
	}
	glEnd();
	glPopMatrix();

	//1. GREEN FLOOR - RIGHT
	circle_points = 100.0f;
	glPushMatrix();
	glRotatef(-90, 0, 0.0, 1);
	glTranslatef(0.05, 0.9, 0);
	glBegin(GL_TRIANGLE_FAN);
	glColor3f(0.54509, 0.70196, 0.22352);
	glVertex2f(0.052, 0);
	for (float angle1 = 0; angle1 <= PI; angle1 += (PI) / NoOfTri) {
		x2 = x + 0.052 * cos(angle1);
		y2 = x + 0.052 * sin(angle1);
		glVertex2f(x2, y2);
	}
	glEnd();
	glPopMatrix();

	//1. Green Floor - GRASS LINE
	glLineWidth(4);
	glColor3f(0.40392, 0.56862, 0.20392);
	glBegin(GL_LINE_STRIP);
	glVertex2f(-0.945, -0.03);
	glVertex2f(-0.9, -0.07);
	glVertex2f(-0.855, -0.03);
	glVertex2f(-0.810, -0.07);
	glVertex2f(-0.765, -0.03);
	glVertex2f(-0.72, -0.07);
	glVertex2f(-0.675, -0.03);
	glVertex2f(-0.63, -0.07);
	glVertex2f(-0.585, -0.03);
	glVertex2f(-0.54, -0.07);
	glVertex2f(-0.495, -0.03);
	glVertex2f(-0.45, -0.07);
	glVertex2f(-0.405, -0.03);
	glVertex2f(-0.36, -0.07);
	glVertex2f(-0.315, -0.03);
	glVertex2f(-0.27, -0.07);
	glVertex2f(-0.225, -0.03);
	glVertex2f(-0.18, -0.07);
	glVertex2f(-0.135, -0.03);
	glVertex2f(-0.09, -0.07);
	glVertex2f(-0.045, -0.03);
	glVertex2f(0, -0.07);
	glVertex2f(0.045, -0.03);
	glVertex2f(0.09, -0.07);
	glVertex2f(0.135, -0.03);
	glVertex2f(0.18, -0.07);
	glVertex2f(0.225, -0.03);
	glVertex2f(0.27, -0.07);
	glVertex2f(0.315, -0.03);
	glVertex2f(0.36, -0.07);
	glVertex2f(0.405, -0.03);
	glVertex2f(0.45, -0.07);
	glVertex2f(0.495, -0.03);
	glVertex2f(0.54, -0.07);
	glVertex2f(0.585, -0.03);
	glVertex2f(0.63, -0.07);
	glVertex2f(0.675, -0.03);
	glVertex2f(0.72, -0.07);
	glVertex2f(0.765, -0.03);
	glVertex2f(0.81, -0.07);
	glVertex2f(0.855, -0.03);
	glVertex2f(0.9, -0.07);
	glVertex2f(0.945, -0.03);
	glEnd();

	//1.Green Floor - Dirt 1
	glColor3f(0.247058, 0.24705, 0.2);
	glBegin(GL_POLYGON);
	glVertex2f(-0.9, -0.1);
	glVertex2f(-0.45, -0.5);
	glVertex2f(0.8, -0.2);
	glVertex2f(0.9, -0.1);
	glEnd();

	//1.Green Floor - Dirt 2
	glColor3f(0.415686, 0.38431, 0.31764);
	glBegin(GL_POLYGON);
	glVertex2f(-0.88, -0.1);
	glVertex2f(-0.82, -0.15);
	glVertex2f(0.84, -0.13);
	glVertex2f(0.89, -0.1);
	glEnd();

	//1.Green Floor - Dirt 3
	glColor3f(0.2039215, 0.18823, 0.145098);
	glBegin(GL_POLYGON);
	glVertex2f(-0.68, -0.3);
	glVertex2f(0.15, -0.6);
	glVertex2f(0.8, -0.2);
	glEnd();

	//2. Background - SKY
	glPushMatrix();
	glColor3f(0,0,0);
	glTranslatef(0, 0, 0);
	glBegin(GL_TRIANGLE_FAN);
	glVertex2f(0, 0);
	for (angle = 0; angle <= PI; angle += (PI) / NoOfTri) {
		x2 = x + 0.85 * cos(angle);
		y2 = x + 0.9 * sin(angle);
		glVertex2f(x2, y2);
	}
	glEnd();
	glPopMatrix();

	//2. Background - HILL 1
	glPushMatrix();
	glColor3f(0.17254, 0.45098, 0.223529);
	glTranslatef(-0.1, 0, 0);
	glBegin(GL_TRIANGLE_FAN);
	glVertex2f(0, 0);
	for (angle = 0; angle <= PI; angle += (PI) / NoOfTri) {
		x2 = x + 0.3 * cos(angle);
		y2 = x + 0.15 * sin(angle);
		glVertex2f(x2, y2);
	}
	glEnd();
	glPopMatrix();

	//2. Background - HILL 1
	glPushMatrix();
	glColor3f(0.341176, 0.541176, 0.2470588);
	glTranslatef(0.45, 0, 0);
	glBegin(GL_TRIANGLE_FAN);
	glVertex2f(0, 0);
	for (angle = 0; angle <= PI; angle += (PI) / NoOfTri) {
		x2 = x + 0.35 * cos(angle);
		y2 = x + 0.2 * sin(angle);
		glVertex2f(x2, y2);
	}
	glEnd();
	glPopMatrix();
}

void DrawStar() {
		glColor3f(1,1,0);


		glRotatef(0.1, 0.0, 0.0, 0.1); // 2. Rotate the object.


		glBegin(GL_TRIANGLES);
		//TOP MIDDLE

		glVertex2f(0, 0);
		glVertex2f(0, 0.5);
		glVertex2f(0.1, 0.2);
		glEnd();

		glBegin(GL_TRIANGLES);
		glVertex2f(0, 0);
		glVertex2f(0, 0.5);
		glVertex2f(-0.1, 0.2);
		glEnd();

		//RIGHT 
		glBegin(GL_TRIANGLES);
		glVertex2f(0, 0);
		glVertex2f(0.4, 0.2);
		glVertex2f(0.1, 0.2);
		glEnd();

		glBegin(GL_TRIANGLES);
		glVertex2f(0, 0);
		glVertex2f(0.4, 0.2);
		glVertex2f(0.15, -0.1);
		glEnd();

		//LEFT
		glBegin(GL_TRIANGLES);
		glVertex2f(0, 0);
		glVertex2f(-0.4, 0.2);
		glVertex2f(-0.1, 0.2);
		glEnd();

		glBegin(GL_TRIANGLES);
		glVertex2f(0, 0);
		glVertex2f(-0.4, 0.2);
		glVertex2f(-0.15, -0.1);
		glEnd();

		//RIGHT BOTTOM
		glBegin(GL_TRIANGLES);
		glVertex2f(0, 0);
		glVertex2f(0.25, -0.5);
		glVertex2f(0.15, -0.1);
		glEnd();

		glBegin(GL_TRIANGLES);
		glVertex2f(0, 0);
		glVertex2f(0.25, -0.5);
		glVertex2f(0, -0.2);
		glEnd();

		//LEFT BOTTOM
		glBegin(GL_TRIANGLES);
		glVertex2f(0, 0);
		glVertex2f(-0.25, -0.5);
		glVertex2f(-0.15, -0.1);
		glEnd();

		glBegin(GL_TRIANGLES);
		glVertex2f(0, 0);
		glVertex2f(-0.25, -0.5);
		glVertex2f(0, -0.2);
		glEnd();
}

void DrawMoon() {
	glPushMatrix();
	glScalef(0.2, 0.2, 0);
	glTranslatef(-2, 3, 0);

	glBegin(GL_TRIANGLE_FAN);
	glColor3f(0.968627, 0.7803, 0.113725);
	glVertex2f(0, 0);

	for (angle = 0; angle <= 2 * PI; angle += (2 * PI) / NoOfTri) {
		x2 = x + r * cos(angle);
		y2 = x + r * sin(angle);
		glVertex2f(x2, y2);
	}
	glEnd();
	glPopMatrix();
}

void DrawSun() {
	glPushMatrix();
	glScalef(0.2, 0.2,0);
	glTranslatef(-2,3, 0);

	glBegin(GL_TRIANGLE_FAN);
	glColor3f(0.968627, 0.7803, 0.113725);
	glVertex2f(0, 0);

	for (angle = 0; angle <= 2 * PI; angle += (2 * PI) / NoOfTri) {
		x2 = x + r * cos(angle);
		y2 = x + r * sin(angle);
		glVertex2f(x2, y2);
	}
	glEnd();
	glPopMatrix();
}

void DrawCloud() {
	//Row 1 starting from bottom
	glPushMatrix();
	glScalef(0.1, 0.1, 0);
	glTranslatef(-2, 5, 0);

	glBegin(GL_TRIANGLE_FAN);
	glColor3f(1,1,1);
	glVertex2f(0, 0);

	for (angle = 0; angle <= 2 * PI; angle += (2 * PI) / NoOfTri) {
		x2 = x + r * cos(angle);
		y2 = x + r * sin(angle);
		glVertex2f(x2, y2);
	}
	glEnd();
	glPopMatrix();

	glPushMatrix();
	glScalef(0.1, 0.1, 0);
	glTranslatef(-2.4,5, 0);

	glBegin(GL_TRIANGLE_FAN);
	glColor3f(1, 1, 1);
	glVertex2f(0, 0);

	for (angle = 0; angle <= 2 * PI; angle += (2 * PI) / NoOfTri) {
		x2 = x + r * cos(angle);
		y2 = x + r * sin(angle);
		glVertex2f(x2, y2);
	}
	glEnd();
	glPopMatrix();

	glPushMatrix();
	glScalef(0.1, 0.1, 0);
	glTranslatef(-2.8, 5, 0);

	glBegin(GL_TRIANGLE_FAN);
	glColor3f(1, 1, 1);
	glVertex2f(0, 0);

	for (angle = 0; angle <= 2 * PI; angle += (2 * PI) / NoOfTri) {
		x2 = x + r * cos(angle);
		y2 = x + r * sin(angle);
		glVertex2f(x2, y2);
	}
	glEnd();
	glPopMatrix();

	glPushMatrix();
	glScalef(0.1, 0.1, 0);
	glTranslatef(-3.2, 5, 0);

	glBegin(GL_TRIANGLE_FAN);
	glColor3f(1, 1, 1);
	glVertex2f(0, 0);

	for (angle = 0; angle <= 2 * PI; angle += (2 * PI) / NoOfTri) {
		x2 = x + r * cos(angle);
		y2 = x + r * sin(angle);
		glVertex2f(x2, y2);
	}
	glEnd();
	glPopMatrix();

	glPushMatrix();
	glScalef(0.1, 0.1, 0);
	glTranslatef(-3.6, 5, 0);

	glBegin(GL_TRIANGLE_FAN);
	glColor3f(1, 1, 1);
	glVertex2f(0, 0);

	for (angle = 0; angle <= 2 * PI; angle += (2 * PI) / NoOfTri) {
		x2 = x + r * cos(angle);
		y2 = x + r * sin(angle);
		glVertex2f(x2, y2);
	}
	glEnd();
	glPopMatrix();

	glPushMatrix();
	glScalef(0.1, 0.1, 0);
	glTranslatef(-4, 5, 0);

	glBegin(GL_TRIANGLE_FAN);
	glColor3f(1, 1, 1);
	glVertex2f(0, 0);

	for (angle = 0; angle <= 2 * PI; angle += (2 * PI) / NoOfTri) {
		x2 = x + r * cos(angle);
		y2 = x + r * sin(angle);
		glVertex2f(x2, y2);
	}
	glEnd();
	glPopMatrix();

	//Second Row
	glPushMatrix();
	glScalef(0.1, 0.1, 0);
	glTranslatef(-2, 5.1, 0);

	glBegin(GL_TRIANGLE_FAN);
	glColor3f(1, 1, 1);
	glVertex2f(0, 0);

	for (angle = 0; angle <= 2 * PI; angle += (2 * PI) / NoOfTri) {
		x2 = x + r * cos(angle);
		y2 = x + r * sin(angle);
		glVertex2f(x2, y2);
	}
	glEnd();
	glPopMatrix();

	glPushMatrix();
	glScalef(0.1, 0.1, 0);
	glTranslatef(-2.4, 5.1, 0);

	glBegin(GL_TRIANGLE_FAN);
	glColor3f(1, 1, 1);
	glVertex2f(0, 0);

	for (angle = 0; angle <= 2 * PI; angle += (2 * PI) / NoOfTri) {
		x2 = x + r * cos(angle);
		y2 = x + r * sin(angle);
		glVertex2f(x2, y2);
	}
	glEnd();
	glPopMatrix();

	glPushMatrix();
	glScalef(0.1, 0.1, 0);
	glTranslatef(-2.8, 5.1, 0);

	glBegin(GL_TRIANGLE_FAN);
	glColor3f(1, 1, 1);
	glVertex2f(0, 0);

	for (angle = 0; angle <= 2 * PI; angle += (2 * PI) / NoOfTri) {
		x2 = x + r * cos(angle);
		y2 = x + r * sin(angle);
		glVertex2f(x2, y2);
	}
	glEnd();
	glPopMatrix();

	glPushMatrix();
	glScalef(0.1, 0.1, 0);
	glTranslatef(-3.2, 5.1, 0);

	glBegin(GL_TRIANGLE_FAN);
	glColor3f(1, 1, 1);
	glVertex2f(0, 0);

	for (angle = 0; angle <= 2 * PI; angle += (2 * PI) / NoOfTri) {
		x2 = x + r * cos(angle);
		y2 = x + r * sin(angle);
		glVertex2f(x2, y2);
	}
	glEnd();
	glPopMatrix();

	glPushMatrix();
	glScalef(0.1, 0.1, 0);
	glTranslatef(-3.6, 5.1, 0);

	glBegin(GL_TRIANGLE_FAN);
	glColor3f(1, 1, 1);
	glVertex2f(0, 0);

	for (angle = 0; angle <= 2 * PI; angle += (2 * PI) / NoOfTri) {
		x2 = x + r * cos(angle);
		y2 = x + r * sin(angle);
		glVertex2f(x2, y2);
	}
	glEnd();
	glPopMatrix();

	glPushMatrix();
	glScalef(0.1, 0.1, 0);
	glTranslatef(-4, 5.1, 0);

	glBegin(GL_TRIANGLE_FAN);
	glColor3f(1, 1, 1);
	glVertex2f(0, 0);

	for (angle = 0; angle <= 2 * PI; angle += (2 * PI) / NoOfTri) {
		x2 = x + r * cos(angle);
		y2 = x + r * sin(angle);
		glVertex2f(x2, y2);
	}
	glEnd();
	glPopMatrix();

	//Row 3
	glPushMatrix();
	glScalef(0.1, 0.1, 0);
	glTranslatef(-2.4, 5.5, 0);

	glBegin(GL_TRIANGLE_FAN);
	glColor3f(1, 1, 1);
	glVertex2f(0, 0);

	for (angle = 0; angle <= 2 * PI; angle += (2 * PI) / NoOfTri) {
		x2 = x + r * cos(angle);
		y2 = x + r * sin(angle);
		glVertex2f(x2, y2);
	}
	glEnd();
	glPopMatrix();

	glPushMatrix();
	glScalef(0.1, 0.1, 0);
	glTranslatef(-2.8, 5.5, 0);

	glBegin(GL_TRIANGLE_FAN);
	glColor3f(1, 1, 1);
	glVertex2f(0, 0);

	for (angle = 0; angle <= 2 * PI; angle += (2 * PI) / NoOfTri) {
		x2 = x + r * cos(angle);
		y2 = x + r * sin(angle);
		glVertex2f(x2, y2);
	}
	glEnd();
	glPopMatrix();

	glPushMatrix();
	glScalef(0.1, 0.1, 0);
	glTranslatef(-3.2, 5.5, 0);

	glBegin(GL_TRIANGLE_FAN);
	glColor3f(1, 1, 1);
	glVertex2f(0, 0);

	for (angle = 0; angle <= 2 * PI; angle += (2 * PI) / NoOfTri) {
		x2 = x + r * cos(angle);
		y2 = x + r * sin(angle);
		glVertex2f(x2, y2);
	}
	glEnd();
	glPopMatrix();

	glPushMatrix();
	glScalef(0.1, 0.1, 0);
	glTranslatef(-3.6, 5.5, 0);

	glBegin(GL_TRIANGLE_FAN);
	glColor3f(1, 1, 1);
	glVertex2f(0, 0);

	for (angle = 0; angle <= 2 * PI; angle += (2 * PI) / NoOfTri) {
		x2 = x + r * cos(angle);
		y2 = x + r * sin(angle);
		glVertex2f(x2, y2);
	}
	glEnd();
	glPopMatrix();

	//row 4 (LAST BIG ONE)
	glPushMatrix();
	glScalef(0.15, 0.15, 0);
	glTranslatef(-2, 3.7, 0);

	glBegin(GL_TRIANGLE_FAN);
	glColor3f(1, 1, 1);
	glVertex2f(0, 0);

	for (angle = 0; angle <= 2 * PI; angle += (2 * PI) / NoOfTri) {
		x2 = x + r * cos(angle);
		y2 = x + r * sin(angle);
		glVertex2f(x2, y2);
	}
	glEnd();
	glPopMatrix();
}

void DrawOne() {
	//3a. WindMill - Bottom
	glLineWidth(3);
	glBegin(GL_LINE_LOOP);
	glColor3f(0.50980, 0.18823, 0.243137);
	glVertex2f(-0.1, 0);
	glVertex2f(0.3, 0);
	glVertex2f(0.25, 0.15);
	glVertex2f(-0.05, 0.15);
	glEnd();

	//3a. WindMill - Bottom Left
	glBegin(GL_POLYGON);
	glColor3f(0.69803, 0.721568, 0.70588);
	glVertex2f(-0.096, 0.004);
	glVertex2f(-0.01, 0.004);
	glVertex2f(0.025, 0.146);
	glVertex2f(-0.046, 0.146);
	glEnd();

	//3a. WindMill - Bottom Middle
	glBegin(GL_POLYGON);
	glColor3f(0.517647, 0.53725, 0.52156);
	glVertex2f(-0.01, 0.004);
	glVertex2f(0.025, 0.146);
	glVertex2f(0.175, 0.146);
	glVertex2f(0.216, 0.004);
	glEnd();


	//3a. WindMill - Bottom Right
	glBegin(GL_POLYGON);
	glColor3f(0.38823, 0.40784, 0.392156);
	glVertex2f(0.296, 0.004);
	glVertex2f(0.216, 0.004);
	glVertex2f(0.175, 0.146);
	glVertex2f(0.246, 0.146);
	glEnd();

	//3b. WindMill - Bottom up Bar
	glBegin(GL_LINE_LOOP);
	glColor3f(0.50980, 0.18823, 0.243137);
	glVertex2f(0.25, 0.15);
	glVertex2f(0.25, 0.2);
	glVertex2f(-0.05, 0.2);
	glVertex2f(-0.05, 0.15);
	glEnd();

	glBegin(GL_POLYGON);
	glColor3f(0.96470, 0.63529, 0.12156);
	glVertex2f(0.247, 0.154);
	glVertex2f(0.247, 0.196);
	glVertex2f(-0.047, 0.196);
	glVertex2f(-0.047, 0.154);
	glEnd();

	//3c. WindMill - Middle LINE
	glBegin(GL_LINE_LOOP);
	glColor3f(0.50980, 0.18823, 0.243137);
	glVertex2f(0.22, 0.201);
	glVertex2f(-0.03, 0.201);
	glVertex2f(0.02, 0.5);
	glVertex2f(0.17, 0.5);
	glEnd();

	//3c. WindMill - Middle LEFT
	glBegin(GL_POLYGON);
	glColor3f(0.69803, 0.721568, 0.70588);
	glVertex2f(0.036, 0.205);
	glVertex2f(-0.026, 0.205);
	glVertex2f(0.024, 0.496);
	glVertex2f(0.074, 0.496);
	glEnd();

	//3c. WindMill - Middle MIDDLE
	glBegin(GL_POLYGON);
	glColor3f(0.517647, 0.53725, 0.52156);
	glVertex2f(0.036, 0.205);
	glVertex2f(0.074, 0.496);
	glVertex2f(0.116, 0.496);
	glVertex2f(0.166, 0.205);
	glEnd();

	//3c. WindMill - Middle RIGHT
	glBegin(GL_POLYGON);
	glColor3f(0.38823, 0.40784, 0.392156);
	glVertex2f(0.216, 0.205);
	glVertex2f(0.166, 0.205);
	glVertex2f(0.116, 0.496);
	glVertex2f(0.166, 0.496);
	glEnd();


	//3d. WindMill - Middle Top Bar
	glLineWidth(3);
	glBegin(GL_LINE_LOOP);
	glColor3f(0.50980, 0.18823, 0.243137);
	glVertex2f(-0.02, 0.501);
	glVertex2f(-0.02, 0.551);
	glVertex2f(0.21, 0.551);
	glVertex2f(0.21, 0.501);
	glEnd();

	glBegin(GL_POLYGON);
	glColor3f(0.96470, 0.63529, 0.12156);
	glVertex2f(-0.017, 0.5006);
	glVertex2f(-0.017, 0.5506);
	glVertex2f(0.207, 0.5506);
	glVertex2f(0.207, 0.5006);
	glEnd();

	//3e. WindMill - Roof
	glLineWidth(6);
	glBegin(GL_LINE_LOOP);
	glColor3f(0.50980, 0.18823, 0.243137);
	glVertex2f(0, 0.555);
	glVertex2f(0.19, 0.555);
	glVertex2f(0.095, 0.65);
	glEnd();

	glBegin(GL_POLYGON);
	glColor3f(0.90588, 0.2, 0.16078);
	glVertex2f(0.004, 0.5546);
	glVertex2f(0.186, 0.5546);
	glVertex2f(0.095, 0.645);
	glEnd();

	//3f. WindMill - Door
	glBegin(GL_LINE_LOOP);
	glColor3f(0.50980, 0.18823, 0.243137);
	glVertex2f(0.075, 0);
	glVertex2f(0.15, 0);
	glVertex2f(0.15, 0.075);
	glVertex2f(0.075, 0.075);
	glEnd();

	circle_points = 100.0f;
	glPushMatrix();
	glTranslatef(0.112, 0.074, 0);
	glBegin(GL_LINE_STRIP);
	glColor3f(0.50980, 0.18823, 0.243137);
	glVertex2f(0.039, 0);
	for (float angle1 = 0; angle1 <= PI; angle1 += (PI) / NoOfTri) {
		x2 = x + 0.039 * cos(angle1);
		y2 = x + 0.039 * sin(angle1);
		glVertex2f(x2, y2);
	}
	glEnd();
	glPopMatrix();

	glBegin(GL_POLYGON);
	glColor3f(0.96470, 0.63529, 0.12156);
	glVertex2f(0.0754, 0.004);
	glVertex2f(0.146, 0.004);
	glVertex2f(0.146, 0.076);
	glVertex2f(0.0754, 0.076);
	glEnd();

	glPushMatrix();
	glTranslatef(0.112, 0.076, 0);
	glBegin(GL_TRIANGLE_FAN);
	glColor3f(0.96470, 0.63529, 0.12156);
	glVertex2f(0.036, 0);
	for (float angle1 = 0; angle1 <= PI; angle1 += (PI) / NoOfTri) {
		x2 = x + 0.036 * cos(angle1);
		y2 = x + 0.036 * sin(angle1);
		glVertex2f(x2, y2);
	}
	glEnd();
	glPopMatrix();

	//3f. WindMill - Door Middle LINE
	glLineWidth(2);
	glBegin(GL_LINE_STRIP);
	glColor3f(0.91372, 0.4196, 0.01568);
	glVertex2f(0.11, 0.11);
	glVertex2f(0.11, 0);
	glEnd();

	//3g. WindMill - (ANYA)
	AnyaFace();

	//3h. WindMill - Brown SpinCircle
	glPushMatrix();
	glTranslatef(0.095, 0.595, 0);
	glScalef(0.05, 0.05, 0);
	glColor3f(0.447058, 0.262745, 0.15686);
	glBegin(GL_TRIANGLE_FAN);
	glVertex2f(0, 0);
	for (angle = 0; angle <= 2 * PI; angle += (2 * PI) / NoOfTri) {
		x2 = x + r * cos(angle);
		y2 = x + r * sin(angle);
		glVertex2f(x2, y2);
	}
	glEnd();
	glPopMatrix();

	//3h. WindMill - Yellow SpinCircle
	glPushMatrix();
	glTranslatef(0.095, 0.595, 0);
	glScalef(0.04, 0.04, 0);
	glColor3f(0.96470, 0.63529, 0.12156);
	glBegin(GL_TRIANGLE_FAN);
	glVertex2f(0, 0);
	for (angle = 0; angle <= 2 * PI; angle += (2 * PI) / NoOfTri) {
		x2 = x + r * cos(angle);
		y2 = x + r * sin(angle);
		glVertex2f(x2, y2);
	}
	glEnd();
	glPopMatrix();

	//3i. WindMill - WING 1
	glPushMatrix();

	//rotation
	glTranslatef(center_x, center_y, 0.0f);
	glRotatef(speed, 0, 0, 1);
	speed += step_angle;
	glTranslatef(-center_x, -center_y, 0.0f);

	//first wing
	glTranslatef(0.12, 0.58, 0);
	glRotatef(0.1, 0, 0, 1);
	glBegin(GL_POLYGON);
	glColor3f(0.447058, 0.262745, 0.15686);
	glVertex2f(0, 0.025);
	glVertex2f(0.25, 0.025);
	glVertex2f(0.25, 0.01);
	glVertex2f(0, 0.01);
	glEnd();

	//White flag middle
	glBegin(GL_POLYGON);
	glColor3f(0.949019, 0.94117, 0.88235);
	glVertex2f(0.1, 0.01);
	glVertex2f(0.25, 0.01);
	glVertex2f(0.25, -0.035);
	glVertex2f(0.1, -0.035);
	glEnd();

	//Middle Horziontal Line
	glBegin(GL_LINE_STRIP);
	glColor3f(0.447058, 0.262745, 0.15686);
	glVertex2f(0.25, -0.0101);
	glVertex2f(0.1, -0.0101);
	glEnd();

	//Middle vertical Line 1
	glBegin(GL_LINE_STRIP);
	glColor3f(0.447058, 0.262745, 0.15686);
	glVertex2f(0.15, 0.01);
	glVertex2f(0.15, -0.0351);
	glEnd();

	//Middle vertical Line 2
	glBegin(GL_LINE_STRIP);
	glColor3f(0.447058, 0.262745, 0.15686);
	glVertex2f(0.2, 0.01);
	glVertex2f(0.2, -0.0351);
	glEnd();


	//Bottom Part wood
	glBegin(GL_LINE_STRIP);
	glColor3f(0.46666, 0.258823, 0.16862);
	glVertex2f(0.25, -0.0351);
	glVertex2f(0.1, -0.0351);
	glEnd();

	glPopMatrix();
}

void DrawTwo() {
	//3a. WindMill - Bottom
	glLineWidth(3);
	glBegin(GL_LINE_LOOP);
	glColor3f(0.50980, 0.18823, 0.243137);
	glVertex2f(-0.1, 0);
	glVertex2f(0.3, 0);
	glVertex2f(0.25, 0.15);
	glVertex2f(-0.05, 0.15);
	glEnd();

	//3a. WindMill - Bottom Left
	glBegin(GL_POLYGON);
	glColor3f(0.69803, 0.721568, 0.70588);
	glVertex2f(-0.096, 0.004);
	glVertex2f(-0.01, 0.004);
	glVertex2f(0.025, 0.146);
	glVertex2f(-0.046, 0.146);
	glEnd();

	//3a. WindMill - Bottom Middle
	glBegin(GL_POLYGON);
	glColor3f(0.517647, 0.53725, 0.52156);
	glVertex2f(-0.01, 0.004);
	glVertex2f(0.025, 0.146);
	glVertex2f(0.175, 0.146);
	glVertex2f(0.216, 0.004);
	glEnd();


	//3a. WindMill - Bottom Right
	glBegin(GL_POLYGON);
	glColor3f(0.38823, 0.40784, 0.392156);
	glVertex2f(0.296, 0.004);
	glVertex2f(0.216, 0.004);
	glVertex2f(0.175, 0.146);
	glVertex2f(0.246, 0.146);
	glEnd();

	//3b. WindMill - Bottom up Bar
	glBegin(GL_LINE_LOOP);
	glColor3f(0.50980, 0.18823, 0.243137);
	glVertex2f(0.25, 0.15);
	glVertex2f(0.25, 0.2);
	glVertex2f(-0.05, 0.2);
	glVertex2f(-0.05, 0.15);
	glEnd();

	glBegin(GL_POLYGON);
	glColor3f(0.96470, 0.63529, 0.12156);
	glVertex2f(0.247, 0.154);
	glVertex2f(0.247, 0.196);
	glVertex2f(-0.047, 0.196);
	glVertex2f(-0.047, 0.154);
	glEnd();

	//3c. WindMill - Middle LINE
	glBegin(GL_LINE_LOOP);
	glColor3f(0.50980, 0.18823, 0.243137);
	glVertex2f(0.22, 0.201);
	glVertex2f(-0.03, 0.201);
	glVertex2f(0.02, 0.5);
	glVertex2f(0.17, 0.5);
	glEnd();

	//3c. WindMill - Middle LEFT
	glBegin(GL_POLYGON);
	glColor3f(0.69803, 0.721568, 0.70588);
	glVertex2f(0.036, 0.205);
	glVertex2f(-0.026, 0.205);
	glVertex2f(0.024, 0.496);
	glVertex2f(0.074, 0.496);
	glEnd();

	//3c. WindMill - Middle MIDDLE
	glBegin(GL_POLYGON);
	glColor3f(0.517647, 0.53725, 0.52156);
	glVertex2f(0.036, 0.205);
	glVertex2f(0.074, 0.496);
	glVertex2f(0.116, 0.496);
	glVertex2f(0.166, 0.205);
	glEnd();

	//3c. WindMill - Middle RIGHT
	glBegin(GL_POLYGON);
	glColor3f(0.38823, 0.40784, 0.392156);
	glVertex2f(0.216, 0.205);
	glVertex2f(0.166, 0.205);
	glVertex2f(0.116, 0.496);
	glVertex2f(0.166, 0.496);
	glEnd();


	//3d. WindMill - Middle Top Bar
	glLineWidth(3);
	glBegin(GL_LINE_LOOP);
	glColor3f(0.50980, 0.18823, 0.243137);
	glVertex2f(-0.02, 0.501);
	glVertex2f(-0.02, 0.551);
	glVertex2f(0.21, 0.551);
	glVertex2f(0.21, 0.501);
	glEnd();

	glBegin(GL_POLYGON);
	glColor3f(0.96470, 0.63529, 0.12156);
	glVertex2f(-0.017, 0.5006);
	glVertex2f(-0.017, 0.5506);
	glVertex2f(0.207, 0.5506);
	glVertex2f(0.207, 0.5006);
	glEnd();

	//3e. WindMill - Roof
	glLineWidth(6);
	glBegin(GL_LINE_LOOP);
	glColor3f(0.50980, 0.18823, 0.243137);
	glVertex2f(0, 0.555);
	glVertex2f(0.19, 0.555);
	glVertex2f(0.095, 0.65);
	glEnd();

	glBegin(GL_POLYGON);
	glColor3f(0.90588, 0.2, 0.16078);
	glVertex2f(0.004, 0.5546);
	glVertex2f(0.186, 0.5546);
	glVertex2f(0.095, 0.645);
	glEnd();

	//3f. WindMill - Door
	glBegin(GL_LINE_LOOP);
	glColor3f(0.50980, 0.18823, 0.243137);
	glVertex2f(0.075, 0);
	glVertex2f(0.15, 0);
	glVertex2f(0.15, 0.075);
	glVertex2f(0.075, 0.075);
	glEnd();

	circle_points = 100.0f;
	glPushMatrix();
	glTranslatef(0.112, 0.074, 0);
	glBegin(GL_LINE_STRIP);
	glColor3f(0.50980, 0.18823, 0.243137);
	glVertex2f(0.039, 0);
	for (float angle1 = 0; angle1 <= PI; angle1 += (PI) / NoOfTri) {
		x2 = x + 0.039 * cos(angle1);
		y2 = x + 0.039 * sin(angle1);
		glVertex2f(x2, y2);
	}
	glEnd();
	glPopMatrix();

	glBegin(GL_POLYGON);
	glColor3f(0.96470, 0.63529, 0.12156);
	glVertex2f(0.0754, 0.004);
	glVertex2f(0.146, 0.004);
	glVertex2f(0.146, 0.076);
	glVertex2f(0.0754, 0.076);
	glEnd();

	glPushMatrix();
	glTranslatef(0.112, 0.076, 0);
	glBegin(GL_TRIANGLE_FAN);
	glColor3f(0.96470, 0.63529, 0.12156);
	glVertex2f(0.036, 0);
	for (float angle1 = 0; angle1 <= PI; angle1 += (PI) / NoOfTri) {
		x2 = x + 0.036 * cos(angle1);
		y2 = x + 0.036 * sin(angle1);
		glVertex2f(x2, y2);
	}
	glEnd();
	glPopMatrix();

	//3f. WindMill - Door Middle LINE
	glLineWidth(2);
	glBegin(GL_LINE_STRIP);
	glColor3f(0.91372, 0.4196, 0.01568);
	glVertex2f(0.11, 0.11);
	glVertex2f(0.11, 0);
	glEnd();

	//3g. WindMill - (ANYA)
	AnyaFace();

	//3h. WindMill - Brown SpinCircle
	glPushMatrix();
	glTranslatef(0.095, 0.595, 0);
	glScalef(0.05, 0.05, 0);
	glColor3f(0.447058, 0.262745, 0.15686);
	glBegin(GL_TRIANGLE_FAN);
	glVertex2f(0, 0);
	for (angle = 0; angle <= 2 * PI; angle += (2 * PI) / NoOfTri) {
		x2 = x + r * cos(angle);
		y2 = x + r * sin(angle);
		glVertex2f(x2, y2);
	}
	glEnd();
	glPopMatrix();

	//3h. WindMill - Yellow SpinCircle
	glPushMatrix();
	glTranslatef(0.095, 0.595, 0);
	glScalef(0.04, 0.04, 0);
	glColor3f(0.96470, 0.63529, 0.12156);
	glBegin(GL_TRIANGLE_FAN);
	glVertex2f(0, 0);
	for (angle = 0; angle <= 2 * PI; angle += (2 * PI) / NoOfTri) {
		x2 = x + r * cos(angle);
		y2 = x + r * sin(angle);
		glVertex2f(x2, y2);
	}
	glEnd();
	glPopMatrix();

	//3i. WindMill - WING 1
	glPushMatrix();

	//rotation
	glTranslatef(center_x, center_y, 0.0f);
	glRotatef(speed, 0, 0, 1);
	speed += step_angle;
	glTranslatef(-center_x, -center_y, 0.0f);

	//first wing
	glTranslatef(0.12, 0.58, 0);
	glRotatef(0.1, 0, 0, 1);
	glBegin(GL_POLYGON);
	glColor3f(0.447058, 0.262745, 0.15686);
	glVertex2f(0, 0.025);
	glVertex2f(0.25, 0.025);
	glVertex2f(0.25, 0.01);
	glVertex2f(0, 0.01);
	glEnd();

	//White flag middle
	glBegin(GL_POLYGON);
	glColor3f(0.949019, 0.94117, 0.88235);
	glVertex2f(0.1, 0.01);
	glVertex2f(0.25, 0.01);
	glVertex2f(0.25, -0.035);
	glVertex2f(0.1, -0.035);
	glEnd();

	//Middle Horziontal Line
	glBegin(GL_LINE_STRIP);
	glColor3f(0.447058, 0.262745, 0.15686);
	glVertex2f(0.25, -0.0101);
	glVertex2f(0.1, -0.0101);
	glEnd();

	//Middle vertical Line 1
	glBegin(GL_LINE_STRIP);
	glColor3f(0.447058, 0.262745, 0.15686);
	glVertex2f(0.15, 0.01);
	glVertex2f(0.15, -0.0351);
	glEnd();

	//Middle vertical Line 2
	glBegin(GL_LINE_STRIP);
	glColor3f(0.447058, 0.262745, 0.15686);
	glVertex2f(0.2, 0.01);
	glVertex2f(0.2, -0.0351);
	glEnd();


	//Bottom Part wood
	glBegin(GL_LINE_STRIP);
	glColor3f(0.46666, 0.258823, 0.16862);
	glVertex2f(0.25, -0.0351);
	glVertex2f(0.1, -0.0351);
	glEnd();

	glPopMatrix();

	//3i. WindMill - WING 2
	glPushMatrix();

	//rotation
	glTranslatef(center_x, center_y, 0.0f);
	glRotatef(speed, 0, 0, 1);
	speed += step_angle;
	glTranslatef(-center_x, -center_y, 0.0f);

	//Second wing
	glTranslatef(0.075, 0.58, 0);
	glRotatef(0.1, 0, 0, 1);
	glBegin(GL_POLYGON);
	glColor3f(0.447058, 0.262745, 0.15686);
	glVertex2f(-0, 0.025);
	glVertex2f(-0.25, 0.025);
	glVertex2f(-0.25, 0.01);
	glVertex2f(-0, 0.01);
	glEnd();

	//White flag middle
	glBegin(GL_POLYGON);
	glColor3f(0.949019, 0.94117, 0.88235);
	glVertex2f(-0.1, 0.01);
	glVertex2f(-0.25, 0.01);
	glVertex2f(-0.25, -0.035);
	glVertex2f(-0.1, -0.035);
	glEnd();

	//Middle Horziontal Line
	glBegin(GL_LINE_STRIP);
	glColor3f(0.447058, 0.262745, 0.15686);
	glVertex2f(-0.25, -0.0101);
	glVertex2f(-0.1, -0.0101);
	glEnd();

	//Middle vertical Line 1
	glBegin(GL_LINE_STRIP);
	glColor3f(0.447058, 0.262745, 0.15686);
	glVertex2f(-0.15, 0.01);
	glVertex2f(-0.15, -0.0351);
	glEnd();

	//Middle vertical Line 2
	glBegin(GL_LINE_STRIP);
	glColor3f(0.447058, 0.262745, 0.15686);
	glVertex2f(-0.2, 0.01);
	glVertex2f(-0.2, -0.0351);
	glEnd();


	//Bottom Part wood
	glBegin(GL_LINE_STRIP);
	glColor3f(-0.46666, 0.258823, 0.16862);
	glVertex2f(-0.25, -0.0351);
	glVertex2f(-0.1, -0.0351);
	glEnd();

	glPopMatrix();
}

void DrawThree() {
	//3a. WindMill - Bottom
	glLineWidth(3);
	glBegin(GL_LINE_LOOP);
	glColor3f(0.50980, 0.18823, 0.243137);
	glVertex2f(-0.1, 0);
	glVertex2f(0.3, 0);
	glVertex2f(0.25, 0.15);
	glVertex2f(-0.05, 0.15);
	glEnd();

	//3a. WindMill - Bottom Left
	glBegin(GL_POLYGON);
	glColor3f(0.69803, 0.721568, 0.70588);
	glVertex2f(-0.096, 0.004);
	glVertex2f(-0.01, 0.004);
	glVertex2f(0.025, 0.146);
	glVertex2f(-0.046, 0.146);
	glEnd();

	//3a. WindMill - Bottom Middle
	glBegin(GL_POLYGON);
	glColor3f(0.517647, 0.53725, 0.52156);
	glVertex2f(-0.01, 0.004);
	glVertex2f(0.025, 0.146);
	glVertex2f(0.175, 0.146);
	glVertex2f(0.216, 0.004);
	glEnd();


	//3a. WindMill - Bottom Right
	glBegin(GL_POLYGON);
	glColor3f(0.38823, 0.40784, 0.392156);
	glVertex2f(0.296, 0.004);
	glVertex2f(0.216, 0.004);
	glVertex2f(0.175, 0.146);
	glVertex2f(0.246, 0.146);
	glEnd();

	//3b. WindMill - Bottom up Bar
	glBegin(GL_LINE_LOOP);
	glColor3f(0.50980, 0.18823, 0.243137);
	glVertex2f(0.25, 0.15);
	glVertex2f(0.25, 0.2);
	glVertex2f(-0.05, 0.2);
	glVertex2f(-0.05, 0.15);
	glEnd();

	glBegin(GL_POLYGON);
	glColor3f(0.96470, 0.63529, 0.12156);
	glVertex2f(0.247, 0.154);
	glVertex2f(0.247, 0.196);
	glVertex2f(-0.047, 0.196);
	glVertex2f(-0.047, 0.154);
	glEnd();

	//3c. WindMill - Middle LINE
	glBegin(GL_LINE_LOOP);
	glColor3f(0.50980, 0.18823, 0.243137);
	glVertex2f(0.22, 0.201);
	glVertex2f(-0.03, 0.201);
	glVertex2f(0.02, 0.5);
	glVertex2f(0.17, 0.5);
	glEnd();

	//3c. WindMill - Middle LEFT
	glBegin(GL_POLYGON);
	glColor3f(0.69803, 0.721568, 0.70588);
	glVertex2f(0.036, 0.205);
	glVertex2f(-0.026, 0.205);
	glVertex2f(0.024, 0.496);
	glVertex2f(0.074, 0.496);
	glEnd();

	//3c. WindMill - Middle MIDDLE
	glBegin(GL_POLYGON);
	glColor3f(0.517647, 0.53725, 0.52156);
	glVertex2f(0.036, 0.205);
	glVertex2f(0.074, 0.496);
	glVertex2f(0.116, 0.496);
	glVertex2f(0.166, 0.205);
	glEnd();

	//3c. WindMill - Middle RIGHT
	glBegin(GL_POLYGON);
	glColor3f(0.38823, 0.40784, 0.392156);
	glVertex2f(0.216, 0.205);
	glVertex2f(0.166, 0.205);
	glVertex2f(0.116, 0.496);
	glVertex2f(0.166, 0.496);
	glEnd();


	//3d. WindMill - Middle Top Bar
	glLineWidth(3);
	glBegin(GL_LINE_LOOP);
	glColor3f(0.50980, 0.18823, 0.243137);
	glVertex2f(-0.02, 0.501);
	glVertex2f(-0.02, 0.551);
	glVertex2f(0.21, 0.551);
	glVertex2f(0.21, 0.501);
	glEnd();

	glBegin(GL_POLYGON);
	glColor3f(0.96470, 0.63529, 0.12156);
	glVertex2f(-0.017, 0.5006);
	glVertex2f(-0.017, 0.5506);
	glVertex2f(0.207, 0.5506);
	glVertex2f(0.207, 0.5006);
	glEnd();

	//3e. WindMill - Roof
	glLineWidth(6);
	glBegin(GL_LINE_LOOP);
	glColor3f(0.50980, 0.18823, 0.243137);
	glVertex2f(0, 0.555);
	glVertex2f(0.19, 0.555);
	glVertex2f(0.095, 0.65);
	glEnd();

	glBegin(GL_POLYGON);
	glColor3f(0.90588, 0.2, 0.16078);
	glVertex2f(0.004, 0.5546);
	glVertex2f(0.186, 0.5546);
	glVertex2f(0.095, 0.645);
	glEnd();

	//3f. WindMill - Door
	glBegin(GL_LINE_LOOP);
	glColor3f(0.50980, 0.18823, 0.243137);
	glVertex2f(0.075, 0);
	glVertex2f(0.15, 0);
	glVertex2f(0.15, 0.075);
	glVertex2f(0.075, 0.075);
	glEnd();

	circle_points = 100.0f;
	glPushMatrix();
	glTranslatef(0.112, 0.074, 0);
	glBegin(GL_LINE_STRIP);
	glColor3f(0.50980, 0.18823, 0.243137);
	glVertex2f(0.039, 0);
	for (float angle1 = 0; angle1 <= PI; angle1 += (PI) / NoOfTri) {
		x2 = x + 0.039 * cos(angle1);
		y2 = x + 0.039 * sin(angle1);
		glVertex2f(x2, y2);
	}
	glEnd();
	glPopMatrix();

	glBegin(GL_POLYGON);
	glColor3f(0.96470, 0.63529, 0.12156);
	glVertex2f(0.0754, 0.004);
	glVertex2f(0.146, 0.004);
	glVertex2f(0.146, 0.076);
	glVertex2f(0.0754, 0.076);
	glEnd();

	glPushMatrix();
	glTranslatef(0.112, 0.076, 0);
	glBegin(GL_TRIANGLE_FAN);
	glColor3f(0.96470, 0.63529, 0.12156);
	glVertex2f(0.036, 0);
	for (float angle1 = 0; angle1 <= PI; angle1 += (PI) / NoOfTri) {
		x2 = x + 0.036 * cos(angle1);
		y2 = x + 0.036 * sin(angle1);
		glVertex2f(x2, y2);
	}
	glEnd();
	glPopMatrix();

	//3f. WindMill - Door Middle LINE
	glLineWidth(2);
	glBegin(GL_LINE_STRIP);
	glColor3f(0.91372, 0.4196, 0.01568);
	glVertex2f(0.11, 0.11);
	glVertex2f(0.11, 0);
	glEnd();

	//3g. WindMill - (ANYA)
	AnyaFace();

	//3h. WindMill - Brown SpinCircle
	glPushMatrix();
	glTranslatef(0.095, 0.595, 0);
	glScalef(0.05, 0.05, 0);
	glColor3f(0.447058, 0.262745, 0.15686);
	glBegin(GL_TRIANGLE_FAN);
	glVertex2f(0, 0);
	for (angle = 0; angle <= 2 * PI; angle += (2 * PI) / NoOfTri) {
		x2 = x + r * cos(angle);
		y2 = x + r * sin(angle);
		glVertex2f(x2, y2);
	}
	glEnd();
	glPopMatrix();

	//3h. WindMill - Yellow SpinCircle
	glPushMatrix();
	glTranslatef(0.095, 0.595, 0);
	glScalef(0.04, 0.04, 0);
	glColor3f(0.96470, 0.63529, 0.12156);
	glBegin(GL_TRIANGLE_FAN);
	glVertex2f(0, 0);
	for (angle = 0; angle <= 2 * PI; angle += (2 * PI) / NoOfTri) {
		x2 = x + r * cos(angle);
		y2 = x + r * sin(angle);
		glVertex2f(x2, y2);
	}
	glEnd();
	glPopMatrix();

	//3i. WindMill - WING 1
	glPushMatrix();

	//rotation
	glTranslatef(center_x, center_y, 0.0f);
	glRotatef(speed, 0, 0, 1);
	speed += step_angle;
	glTranslatef(-center_x, -center_y, 0.0f);

	//first wing
	glTranslatef(0.12, 0.58, 0);
	glRotatef(0.1, 0, 0, 1);
	glBegin(GL_POLYGON);
	glColor3f(0.447058, 0.262745, 0.15686);
	glVertex2f(0, 0.025);
	glVertex2f(0.25, 0.025);
	glVertex2f(0.25, 0.01);
	glVertex2f(0, 0.01);
	glEnd();

	//White flag middle
	glBegin(GL_POLYGON);
	glColor3f(0.949019, 0.94117, 0.88235);
	glVertex2f(0.1, 0.01);
	glVertex2f(0.25, 0.01);
	glVertex2f(0.25, -0.035);
	glVertex2f(0.1, -0.035);
	glEnd();

	//Middle Horziontal Line
	glBegin(GL_LINE_STRIP);
	glColor3f(0.447058, 0.262745, 0.15686);
	glVertex2f(0.25, -0.0101);
	glVertex2f(0.1, -0.0101);
	glEnd();

	//Middle vertical Line 1
	glBegin(GL_LINE_STRIP);
	glColor3f(0.447058, 0.262745, 0.15686);
	glVertex2f(0.15, 0.01);
	glVertex2f(0.15, -0.0351);
	glEnd();

	//Middle vertical Line 2
	glBegin(GL_LINE_STRIP);
	glColor3f(0.447058, 0.262745, 0.15686);
	glVertex2f(0.2, 0.01);
	glVertex2f(0.2, -0.0351);
	glEnd();


	//Bottom Part wood
	glBegin(GL_LINE_STRIP);
	glColor3f(0.46666, 0.258823, 0.16862);
	glVertex2f(0.25, -0.0351);
	glVertex2f(0.1, -0.0351);
	glEnd();

	glPopMatrix();


	//3i. WindMill - WING 2
	glPushMatrix();

	//rotation
	glTranslatef(center_x, center_y, 0.0f);
	glRotatef(speed, 0, 0, 1);
	speed += step_angle;
	glTranslatef(-center_x, -center_y, 0.0f);

	//Second wing
	glTranslatef(0.075, 0.58, 0);
	glRotatef(0.1, 0, 0, 1);
	glBegin(GL_POLYGON);
	glColor3f(0.447058, 0.262745, 0.15686);
	glVertex2f(-0, 0.025);
	glVertex2f(-0.25, 0.025);
	glVertex2f(-0.25, 0.01);
	glVertex2f(-0, 0.01);
	glEnd();

	//White flag middle
	glBegin(GL_POLYGON);
	glColor3f(0.949019, 0.94117, 0.88235);
	glVertex2f(-0.1, 0.01);
	glVertex2f(-0.25, 0.01);
	glVertex2f(-0.25, -0.035);
	glVertex2f(-0.1, -0.035);
	glEnd();

	//Middle Horziontal Line
	glBegin(GL_LINE_STRIP);
	glColor3f(0.447058, 0.262745, 0.15686);
	glVertex2f(-0.25, -0.0101);
	glVertex2f(-0.1, -0.0101);
	glEnd();

	//Middle vertical Line 1
	glBegin(GL_LINE_STRIP);
	glColor3f(0.447058, 0.262745, 0.15686);
	glVertex2f(-0.15, 0.01);
	glVertex2f(-0.15, -0.0351);
	glEnd();

	//Middle vertical Line 2
	glBegin(GL_LINE_STRIP);
	glColor3f(0.447058, 0.262745, 0.15686);
	glVertex2f(-0.2, 0.01);
	glVertex2f(-0.2, -0.0351);
	glEnd();


	//Bottom Part wood
	glBegin(GL_LINE_STRIP);
	glColor3f(-0.46666, 0.258823, 0.16862);
	glVertex2f(-0.25, -0.0351);
	glVertex2f(-0.1, -0.0351);
	glEnd();

	glPopMatrix();

	//3i. WindMill - WING 3
	glPushMatrix();

	//rotation
	glTranslatef(center_x, center_y, 0.0f);
	glRotatef(speed, 0, 0, 1);
	speed += step_angle;
	glTranslatef(-center_x, -center_y, 0.0f);

	//Third wing
	glTranslatef(0.075, 0.57, 0);
	glRotatef(0.1, 0, 0, 1);

	glBegin(GL_POLYGON);
	glColor3f(0.447058, 0.262745, 0.15686);
	glVertex2f(0.025, 0);
	glVertex2f(0.025, -0.25);
	glVertex2f(0.01, -0.25);
	glVertex2f(0.01, 0);
	glEnd();

	//White flag middle
	glBegin(GL_POLYGON);
	glColor3f(0.949019, 0.94117, 0.88235);
	glVertex2f(0.01, -0.1);
	glVertex2f(0.01, -0.25);
	glVertex2f(-0.035, -0.25);
	glVertex2f(-0.035, -0.1);
	glEnd();

	//Middle Horziontal Line
	glBegin(GL_LINE_STRIP);
	glColor3f(0.447058, 0.262745, 0.15686);
	glVertex2f(-0.0101, -0.25);
	glVertex2f(-0.0101, -0.1);
	glEnd();

	//Middle vertical Line 1
	glBegin(GL_LINE_STRIP);
	glColor3f(0.447058, 0.262745, 0.15686);
	glVertex2f(0.01, -0.15);
	glVertex2f(-0.0351, -0.15);
	glEnd();

	//Middle vertical Line 2
	glBegin(GL_LINE_STRIP);
	glColor3f(0.447058, 0.262745, 0.15686);
	glVertex2f(0.01, -0.2);
	glVertex2f(-0.0351, -0.2);
	glEnd();


	//Bottom Part wood
	glBegin(GL_LINE_STRIP);
	glColor3f(-0.46666, 0.258823, 0.16862);
	glVertex2f(-0.0351, -0.25);
	glVertex2f(-0.0351, -0.1);
	glEnd();

	glPopMatrix();
}

void DrawFour() {
	//3a. WindMill - Bottom
	glLineWidth(3);
	glBegin(GL_LINE_LOOP);
	glColor3f(0.50980, 0.18823, 0.243137);
	glVertex2f(-0.1, 0);
	glVertex2f(0.3, 0);
	glVertex2f(0.25, 0.15);
	glVertex2f(-0.05, 0.15);
	glEnd();

	//3a. WindMill - Bottom Left
	glBegin(GL_POLYGON);
	glColor3f(0.69803, 0.721568, 0.70588);
	glVertex2f(-0.096, 0.004);
	glVertex2f(-0.01, 0.004);
	glVertex2f(0.025, 0.146);
	glVertex2f(-0.046, 0.146);
	glEnd();

	//3a. WindMill - Bottom Middle
	glBegin(GL_POLYGON);
	glColor3f(0.517647, 0.53725, 0.52156);
	glVertex2f(-0.01, 0.004);
	glVertex2f(0.025, 0.146);
	glVertex2f(0.175, 0.146);
	glVertex2f(0.216, 0.004);
	glEnd();


	//3a. WindMill - Bottom Right
	glBegin(GL_POLYGON);
	glColor3f(0.38823, 0.40784, 0.392156);
	glVertex2f(0.296, 0.004);
	glVertex2f(0.216, 0.004);
	glVertex2f(0.175, 0.146);
	glVertex2f(0.246, 0.146);
	glEnd();

	//3b. WindMill - Bottom up Bar
	glBegin(GL_LINE_LOOP);
	glColor3f(0.50980, 0.18823, 0.243137);
	glVertex2f(0.25, 0.15);
	glVertex2f(0.25, 0.2);
	glVertex2f(-0.05, 0.2);
	glVertex2f(-0.05, 0.15);
	glEnd();

	glBegin(GL_POLYGON);
	glColor3f(0.96470, 0.63529, 0.12156);
	glVertex2f(0.247, 0.154);
	glVertex2f(0.247, 0.196);
	glVertex2f(-0.047, 0.196);
	glVertex2f(-0.047, 0.154);
	glEnd();

	//3c. WindMill - Middle LINE
	glBegin(GL_LINE_LOOP);
	glColor3f(0.50980, 0.18823, 0.243137);
	glVertex2f(0.22, 0.201);
	glVertex2f(-0.03, 0.201);
	glVertex2f(0.02, 0.5);
	glVertex2f(0.17, 0.5);
	glEnd();

	//3c. WindMill - Middle LEFT
	glBegin(GL_POLYGON);
	glColor3f(0.69803, 0.721568, 0.70588);
	glVertex2f(0.036, 0.205);
	glVertex2f(-0.026, 0.205);
	glVertex2f(0.024, 0.496);
	glVertex2f(0.074, 0.496);
	glEnd();

	//3c. WindMill - Middle MIDDLE
	glBegin(GL_POLYGON);
	glColor3f(0.517647, 0.53725, 0.52156);
	glVertex2f(0.036, 0.205);
	glVertex2f(0.074, 0.496);
	glVertex2f(0.116, 0.496);
	glVertex2f(0.166, 0.205);
	glEnd();

	//3c. WindMill - Middle RIGHT
	glBegin(GL_POLYGON);
	glColor3f(0.38823, 0.40784, 0.392156);
	glVertex2f(0.216, 0.205);
	glVertex2f(0.166, 0.205);
	glVertex2f(0.116, 0.496);
	glVertex2f(0.166, 0.496);
	glEnd();


	//3d. WindMill - Middle Top Bar
	glLineWidth(3);
	glBegin(GL_LINE_LOOP);
	glColor3f(0.50980, 0.18823, 0.243137);
	glVertex2f(-0.02, 0.501);
	glVertex2f(-0.02, 0.551);
	glVertex2f(0.21, 0.551);
	glVertex2f(0.21, 0.501);
	glEnd();

	glBegin(GL_POLYGON);
	glColor3f(0.96470, 0.63529, 0.12156);
	glVertex2f(-0.017, 0.5006);
	glVertex2f(-0.017, 0.5506);
	glVertex2f(0.207, 0.5506);
	glVertex2f(0.207, 0.5006);
	glEnd();

	//3e. WindMill - Roof
	glLineWidth(6);
	glBegin(GL_LINE_LOOP);
	glColor3f(0.50980, 0.18823, 0.243137);
	glVertex2f(0, 0.555);
	glVertex2f(0.19, 0.555);
	glVertex2f(0.095, 0.65);
	glEnd();

	glBegin(GL_POLYGON);
	glColor3f(0.90588, 0.2, 0.16078);
	glVertex2f(0.004, 0.5546);
	glVertex2f(0.186, 0.5546);
	glVertex2f(0.095, 0.645);
	glEnd();

	//3f. WindMill - Door
	glBegin(GL_LINE_LOOP);
	glColor3f(0.50980, 0.18823, 0.243137);
	glVertex2f(0.075, 0);
	glVertex2f(0.15, 0);
	glVertex2f(0.15, 0.075);
	glVertex2f(0.075, 0.075);
	glEnd();

	circle_points = 100.0f;
	glPushMatrix();
	glTranslatef(0.112, 0.074, 0);
	glBegin(GL_LINE_STRIP);
	glColor3f(0.50980, 0.18823, 0.243137);
	glVertex2f(0.039, 0);
	for (float angle1 = 0; angle1 <= PI; angle1 += (PI) / NoOfTri) {
		x2 = x + 0.039 * cos(angle1);
		y2 = x + 0.039 * sin(angle1);
		glVertex2f(x2, y2);
	}
	glEnd();
	glPopMatrix();

	glBegin(GL_POLYGON);
	glColor3f(0.96470, 0.63529, 0.12156);
	glVertex2f(0.0754, 0.004);
	glVertex2f(0.146, 0.004);
	glVertex2f(0.146, 0.076);
	glVertex2f(0.0754, 0.076);
	glEnd();

	glPushMatrix();
	glTranslatef(0.112, 0.076, 0);
	glBegin(GL_TRIANGLE_FAN);
	glColor3f(0.96470, 0.63529, 0.12156);
	glVertex2f(0.036, 0);
	for (float angle1 = 0; angle1 <= PI; angle1 += (PI) / NoOfTri) {
		x2 = x + 0.036 * cos(angle1);
		y2 = x + 0.036 * sin(angle1);
		glVertex2f(x2, y2);
	}
	glEnd();
	glPopMatrix();

	//3f. WindMill - Door Middle LINE
	glLineWidth(2);
	glBegin(GL_LINE_STRIP);
	glColor3f(0.91372, 0.4196, 0.01568);
	glVertex2f(0.11, 0.11);
	glVertex2f(0.11, 0);
	glEnd();

	//3g. WindMill - (ANYA)
	AnyaFace();

	//3h. WindMill - Brown SpinCircle
	glPushMatrix();
	glTranslatef(0.095, 0.595, 0);
	glScalef(0.05, 0.05, 0);
	glColor3f(0.447058, 0.262745, 0.15686);
	glBegin(GL_TRIANGLE_FAN);
	glVertex2f(0, 0);
	for (angle = 0; angle <= 2 * PI; angle += (2 * PI) / NoOfTri) {
		x2 = x + r * cos(angle);
		y2 = x + r * sin(angle);
		glVertex2f(x2, y2);
	}
	glEnd();
	glPopMatrix();

	//3h. WindMill - Yellow SpinCircle
	glPushMatrix();
	glTranslatef(0.095, 0.595, 0);
	glScalef(0.04, 0.04, 0);
	glColor3f(0.96470, 0.63529, 0.12156);
	glBegin(GL_TRIANGLE_FAN);
	glVertex2f(0, 0);
	for (angle = 0; angle <= 2 * PI; angle += (2 * PI) / NoOfTri) {
		x2 = x + r * cos(angle);
		y2 = x + r * sin(angle);
		glVertex2f(x2, y2);
	}
	glEnd();
	glPopMatrix();

	//3i. WindMill - WING 1
	glPushMatrix();

	//rotation
	glTranslatef(center_x, center_y, 0.0f);
	glRotatef(speed, 0, 0, 1);
	speed += step_angle;
	glTranslatef(-center_x, -center_y, 0.0f);

	//first wing
	glTranslatef(0.12, 0.58, 0);
	glRotatef(0.1, 0, 0, 1);
	glBegin(GL_POLYGON);
	glColor3f(0.447058, 0.262745, 0.15686);
	glVertex2f(0, 0.025);
	glVertex2f(0.25, 0.025);
	glVertex2f(0.25, 0.01);
	glVertex2f(0, 0.01);
	glEnd();

	//White flag middle
	glBegin(GL_POLYGON);
	glColor3f(0.949019, 0.94117, 0.88235);
	glVertex2f(0.1, 0.01);
	glVertex2f(0.25, 0.01);
	glVertex2f(0.25, -0.035);
	glVertex2f(0.1, -0.035);
	glEnd();

	//Middle Horziontal Line
	glBegin(GL_LINE_STRIP);
	glColor3f(0.447058, 0.262745, 0.15686);
	glVertex2f(0.25, -0.0101);
	glVertex2f(0.1, -0.0101);
	glEnd();

	//Middle vertical Line 1
	glBegin(GL_LINE_STRIP);
	glColor3f(0.447058, 0.262745, 0.15686);
	glVertex2f(0.15, 0.01);
	glVertex2f(0.15, -0.0351);
	glEnd();

	//Middle vertical Line 2
	glBegin(GL_LINE_STRIP);
	glColor3f(0.447058, 0.262745, 0.15686);
	glVertex2f(0.2, 0.01);
	glVertex2f(0.2, -0.0351);
	glEnd();


	//Bottom Part wood
	glBegin(GL_LINE_STRIP);
	glColor3f(0.46666, 0.258823, 0.16862);
	glVertex2f(0.25, -0.0351);
	glVertex2f(0.1, -0.0351);
	glEnd();

	glPopMatrix();

	//3i. WindMill - WING 2
	glPushMatrix();

	//rotation
	glTranslatef(center_x, center_y, 0.0f);
	glRotatef(speed, 0, 0, 1);
	speed += step_angle;
	glTranslatef(-center_x, -center_y, 0.0f);

	//Second wing
	glTranslatef(0.075, 0.58, 0);
	glRotatef(0.1, 0, 0, 1);
	glBegin(GL_POLYGON);
	glColor3f(0.447058, 0.262745, 0.15686);
	glVertex2f(-0, 0.025);
	glVertex2f(-0.25, 0.025);
	glVertex2f(-0.25, 0.01);
	glVertex2f(-0, 0.01);
	glEnd();

	//White flag middle
	glBegin(GL_POLYGON);
	glColor3f(0.949019, 0.94117, 0.88235);
	glVertex2f(-0.1, 0.01);
	glVertex2f(-0.25, 0.01);
	glVertex2f(-0.25, -0.035);
	glVertex2f(-0.1, -0.035);
	glEnd();

	//Middle Horziontal Line
	glBegin(GL_LINE_STRIP);
	glColor3f(0.447058, 0.262745, 0.15686);
	glVertex2f(-0.25, -0.0101);
	glVertex2f(-0.1, -0.0101);
	glEnd();

	//Middle vertical Line 1
	glBegin(GL_LINE_STRIP);
	glColor3f(0.447058, 0.262745, 0.15686);
	glVertex2f(-0.15, 0.01);
	glVertex2f(-0.15, -0.0351);
	glEnd();

	//Middle vertical Line 2
	glBegin(GL_LINE_STRIP);
	glColor3f(0.447058, 0.262745, 0.15686);
	glVertex2f(-0.2, 0.01);
	glVertex2f(-0.2, -0.0351);
	glEnd();


	//Bottom Part wood
	glBegin(GL_LINE_STRIP);
	glColor3f(-0.46666, 0.258823, 0.16862);
	glVertex2f(-0.25, -0.0351);
	glVertex2f(-0.1, -0.0351);
	glEnd();

	glPopMatrix();




	//3i. WindMill - WING 3
	glPushMatrix();

	//rotation
	glTranslatef(center_x, center_y, 0.0f);
	glRotatef(speed, 0, 0, 1);
	speed += step_angle;
	glTranslatef(-center_x, -center_y, 0.0f);

	//Third wing
	glTranslatef(0.075, 0.57, 0);
	glRotatef(0.1, 0, 0, 1);

	glBegin(GL_POLYGON);
	glColor3f(0.447058, 0.262745, 0.15686);
	glVertex2f(0.025, 0);
	glVertex2f(0.025, -0.25);
	glVertex2f(0.01, -0.25);
	glVertex2f(0.01, 0);
	glEnd();

	//White flag middle
	glBegin(GL_POLYGON);
	glColor3f(0.949019, 0.94117, 0.88235);
	glVertex2f(0.01, -0.1);
	glVertex2f(0.01, -0.25);
	glVertex2f(-0.035, -0.25);
	glVertex2f(-0.035, -0.1);
	glEnd();

	//Middle Horziontal Line
	glBegin(GL_LINE_STRIP);
	glColor3f(0.447058, 0.262745, 0.15686);
	glVertex2f(-0.0101, -0.25);
	glVertex2f(-0.0101, -0.1);
	glEnd();

	//Middle vertical Line 1
	glBegin(GL_LINE_STRIP);
	glColor3f(0.447058, 0.262745, 0.15686);
	glVertex2f(0.01, -0.15);
	glVertex2f(-0.0351, -0.15);
	glEnd();

	//Middle vertical Line 2
	glBegin(GL_LINE_STRIP);
	glColor3f(0.447058, 0.262745, 0.15686);
	glVertex2f(0.01, -0.2);
	glVertex2f(-0.0351, -0.2);
	glEnd();


	//Bottom Part wood
	glBegin(GL_LINE_STRIP);
	glColor3f(-0.46666, 0.258823, 0.16862);
	glVertex2f(-0.0351, -0.25);
	glVertex2f(-0.0351, -0.1);
	glEnd();

	glPopMatrix();

	//3i. WindMill - WING 4
	glPushMatrix();

	//rotation
	glTranslatef(center_x, center_y, 0.0f);
	glRotatef(speed, 0, 0, 1);
	speed += step_angle;
	glTranslatef(-center_x, -center_y, 0.0f);

	//Fourth wing
	glTranslatef(0.075, 0.62, 0);
	glRotatef(0.1, 0, 0, 1);

	glBegin(GL_POLYGON);
	glColor3f(0.447058, 0.262745, 0.15686);
	glVertex2f(0.025, 0);
	glVertex2f(0.025, 0.25);
	glVertex2f(0.01, 0.25);
	glVertex2f(0.01, 0);
	glEnd();

	//White flag middle
	glBegin(GL_POLYGON);
	glColor3f(0.949019, 0.94117, 0.88235);
	glVertex2f(0.01, 0.1);
	glVertex2f(0.01, 0.25);
	glVertex2f(-0.035, 0.25);
	glVertex2f(-0.035, 0.1);
	glEnd();

	//Middle Horziontal Line
	glBegin(GL_LINE_STRIP);
	glColor3f(0.447058, 0.262745, 0.15686);
	glVertex2f(-0.0101, 0.25);
	glVertex2f(-0.0101, 0.1);
	glEnd();

	//Middle vertical Line 1
	glBegin(GL_LINE_STRIP);
	glColor3f(0.447058, 0.262745, 0.15686);
	glVertex2f(0.01, 0.15);
	glVertex2f(-0.0351, 0.15);
	glEnd();

	//Middle vertical Line 2
	glBegin(GL_LINE_STRIP);
	glColor3f(0.447058, 0.262745, 0.15686);
	glVertex2f(0.01, 0.2);
	glVertex2f(-0.0351, 0.2);
	glEnd();


	//Bottom Part wood
	glBegin(GL_LINE_STRIP);
	glColor3f(-0.46666, 0.258823, 0.16862);
	glVertex2f(-0.0351, 0.25);
	glVertex2f(-0.0351, 0.1);
	glEnd();

	glPopMatrix();
}

void DrawGreenTree() {
	glPushMatrix();
	glTranslatef(0.5, 0, 0);
	
	//Wood Trunck
	glBegin(GL_POLYGON);
	glColor3f(0.48235, 0.27058, 0.02745);
	glVertex2f(0.025, 0);
	glVertex2f(0.075, 0);
	glVertex2f(0.075, 0.15);
	glVertex2f(0.025, 0.15);
	glEnd();

	//Wood Leaf 1
	glBegin(GL_TRIANGLES);
	glColor3f(0.521568, 0.623529, 0.274509);
	glVertex2f(0.05, 0.15);
	glVertex2f(0.15, 0.05);
	glVertex2f(-0.05, 0.05);
	glEnd();

	//Wood Leaf 2
	glBegin(GL_TRIANGLES);
	glColor3f(0.466666, 0.55686, 0.231372);
	glVertex2f(0.05, 0.2);
	glVertex2f(0.14, 0.1);
	glVertex2f(-0.04, 0.1);
	glEnd();

	//Wood Leaf 3
	glBegin(GL_TRIANGLES);
	glColor3f(0.521568, 0.623529, 0.274509);
	glVertex2f(0.05, 0.26);
	glVertex2f(0.11, 0.17);
	glVertex2f(-0.01, 0.17);
	glEnd();

	glPopMatrix();
}

void DrawRedOrangeTree() {
	glPushMatrix();
	glTranslatef(0.5, 0, 0);

	//Wood Trunck
	glBegin(GL_POLYGON);
	glColor3f(0.48235, 0.27058, 0.02745);
	glVertex2f(0.025, 0);
	glVertex2f(0.075, 0);
	glVertex2f(0.075, 0.15);
	glVertex2f(0.025, 0.15);
	glEnd();

	//Wood Leaf 1
	glBegin(GL_TRIANGLES);
	glColor3f(0.87058, 0.27843, 0.00392);
	glVertex2f(0.05, 0.15);
	glVertex2f(0.15, 0.05);
	glVertex2f(-0.05, 0.05);
	glEnd();

	//Wood Leaf 2
	glBegin(GL_TRIANGLES);
	glColor3f(1, 0.513725, 0.007843);
	glVertex2f(0.05, 0.2);
	glVertex2f(0.14, 0.1);
	glVertex2f(-0.04, 0.1);
	glEnd();

	//Wood Leaf 3
	glBegin(GL_TRIANGLES);
	glColor3f(0.87058, 0.27843, 0.00392);
	glVertex2f(0.05, 0.26);
	glVertex2f(0.11, 0.17);
	glVertex2f(-0.01, 0.17);
	glEnd();

	glPopMatrix();
}

void DrawOrangeTree() {
	glPushMatrix();
	glTranslatef(0.5, 0, 0);

	//Wood Trunck
	glBegin(GL_POLYGON);
	glColor3f(0.48235, 0.27058, 0.02745);
	glVertex2f(0.025, 0);
	glVertex2f(0.075, 0);
	glVertex2f(0.075, 0.15);
	glVertex2f(0.025, 0.15);
	glEnd();

	//Wood Leaf 1
	glBegin(GL_TRIANGLES);
	glColor3f(1, 0.513725, 0.007843);
	glVertex2f(0.05, 0.15);
	glVertex2f(0.15, 0.05);
	glVertex2f(-0.05, 0.05);
	glEnd();

	//Wood Leaf 2
	glBegin(GL_TRIANGLES);
	glColor3f(0.87058, 0.27843, 0.00392);
	glVertex2f(0.05, 0.2);
	glVertex2f(0.14, 0.1);
	glVertex2f(-0.04, 0.1);
	glEnd();

	//Wood Leaf 3
	glBegin(GL_TRIANGLES);
	glColor3f(1, 0.513725, 0.007843);
	glVertex2f(0.05, 0.26);
	glVertex2f(0.11, 0.17);
	glVertex2f(-0.01, 0.17);
	glEnd();

	glPopMatrix();
}

void DrawPig() {
	glPushMatrix();
	glScalef(0.15, 0.15, 0);
	
	glTranslatef(pigx, 0.4, 0);




	//Ear 1
	glPushMatrix();
	glTranslatef(-0.4, 0.25, 0);
	glRotatef(45, 0, 0, 1);
	glScalef(1, 1, 0);
	glBegin(GL_TRIANGLES);
	glColor3f(0.980392, 0.717647, 0.78039);
	glVertex2f(0, 0);
	glVertex2f(0.1, 0.2);
	glVertex2f(0.2, 0);
	glEnd();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-0.4, 0.25, 0);
	glRotatef(45, 0, 0, 1);
	glScalef(0.9, 0.9, 0);
	glBegin(GL_TRIANGLES);
	glColor3f(0.92549, 0.55294, 0.631372);
	glVertex2f(0, 0);
	glVertex2f(0.1, 0.2);
	glVertex2f(0.2, 0);
	glEnd();
	glPopMatrix();

	//Ear 2
	glPushMatrix();
	glTranslatef(0.25, 0.4, 0);
	glRotatef(-45, 0, 0, 1);
	glScalef(1, 1, 0);
	glBegin(GL_TRIANGLES);
	glColor3f(0.980392, 0.717647, 0.78039);
	glVertex2f(0, 0);
	glVertex2f(0.1, 0.2);
	glVertex2f(0.2, 0);
	glEnd();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.26, 0.38, 0);
	glRotatef(-45, 0, 0, 1);
	glScalef(0.9, 0.9, 0);
	glBegin(GL_TRIANGLES);
	glColor3f(0.92549, 0.55294, 0.631372);
	glVertex2f(0, 0);
	glVertex2f(0.1, 0.2);
	glVertex2f(0.2, 0);
	glEnd();
	glPopMatrix();


	//Face
	glBegin(GL_TRIANGLE_FAN);
	glColor3f(0.980392, 0.717647, 0.78039);
	glVertex2f(0, 0);

	for (angle = 0; angle <= 2 * PI; angle += (2 * PI) / NoOfTri) {
		x2 = x + r * cos(angle);
		y2 = x + r * sin(angle);
		glVertex2f(x2, y2);
	}
	glEnd();

	//Nose
	glPushMatrix();
	glScalef(0.3, 0.3, 0);
	glTranslatef(0, -0.1, 0);
	glBegin(GL_TRIANGLE_FAN);
	glColor3f(0.92549, 0.55294, 0.631372);
	glVertex2f(0.6, 0);

	for (angle = 0; angle <= 2 * PI; angle += (2 * PI) / NoOfTri) {
		x2 = x + 0.6 * cos(angle);
		y2 = x + 0.4 * sin(angle);
		glVertex2f(x2, y2);
	}
	glEnd();
	glPopMatrix();

	//Nose Hole 1
	glPushMatrix();
	glTranslatef(-0.07, -0.08, 0);
	glBegin(GL_POLYGON);
	glColor3f(0, 0, 0);
	glVertex2f(0, 0);
	glVertex2f(0, 0.09);
	glVertex2f(0.02, 0.09);
	glVertex2f(0.02, 0);
	glEnd();
	glPopMatrix();

	//Nose Hole 2
	glPushMatrix();
	glTranslatef(0.05,-0.08,0);
	glBegin(GL_POLYGON);
	glColor3f(0, 0, 0);
	glVertex2f(0, 0);
	glVertex2f(0, 0.09);
	glVertex2f(0.02, 0.09);
	glVertex2f(0.02, 0);
	glEnd();
	glPopMatrix();

	//Eye 1
	glPushMatrix();
	glScalef(0.2, 0.2, 0);
	glTranslatef(-0.9, 0.9, 0);
	glBegin(GL_TRIANGLE_FAN);
	glColor3f(1,1,1);
	glVertex2f(0, 0);

	for (angle = 0; angle <= 2 * PI; angle += (2 * PI) / NoOfTri) {
		x2 = x + r * cos(angle);
		y2 = x + r * sin(angle);
		glVertex2f(x2, y2);
	}
	glEnd();
	glPopMatrix();

	// Eyeball 1
	glPushMatrix();
	glScalef(0.1, 0.1, 0);
	glTranslatef(-1.5, 1.5, 0);
	glBegin(GL_TRIANGLE_FAN);
	glColor3f(0.92549, 0.55294, 0.631372);
	glVertex2f(0, 0);

	for (angle = 0; angle <= 2 * PI; angle += (2 * PI) / NoOfTri) {
		x2 = x + r * cos(angle);
		y2 = x + r * sin(angle);
		glVertex2f(x2, y2);
	}
	glEnd();
	glPopMatrix();
	
	//Eye 2
	glPushMatrix();
	glScalef(0.2, 0.2, 0);
	glTranslatef(0.9, 0.9, 0);
	glBegin(GL_TRIANGLE_FAN);
	glColor3f(1, 1, 1);
	glVertex2f(0, 0);

	for (angle = 0; angle <= 2 * PI; angle += (2 * PI) / NoOfTri) {
		x2 = x + r * cos(angle);
		y2 = x + r * sin(angle);
		glVertex2f(x2, y2);
	}
	glEnd();
	glPopMatrix();

	// Eyeball 2
	glPushMatrix();
	glScalef(0.1, 0.1, 0);
	glTranslatef(1.5, 1.5, 0);
	glBegin(GL_TRIANGLE_FAN);
	glColor3f(0.92549, 0.55294, 0.631372);
	glVertex2f(0, 0);

	for (angle = 0; angle <= 2 * PI; angle += (2 * PI) / NoOfTri) {
		x2 = x + r * cos(angle);
		y2 = x + r * sin(angle);
		glVertex2f(x2, y2);
	}
	glEnd();
	glPopMatrix();

	glPopMatrix();
}


//WindMill Below

void OneWind() {
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);  //clear screen
	

	if (check == true) {
		//Background
		DrawBackground();

		//3j Sun
		DrawSun();
	}
	else {
		DrawBackground1();

		DrawMoon();

		glPushMatrix();
		glScalef(0.1, 0.05, 0);
		glTranslatef(5, 7, 0);
		DrawStar();
		glPopMatrix();

		glPushMatrix();
		glScalef(0.1, 0.05, 0);
		glTranslatef(-5, 6, 0);
		DrawStar();
		glPopMatrix();

		glPushMatrix();
		glScalef(0.1, 0.05, 0);
		glTranslatef(-0, 14, 0);
		DrawStar();
		glPopMatrix();
	}


	//cloud
	DrawCloud();

	//cloud 2 
	glPushMatrix();
	glScalef(0.6, 0.6, 0);
	glTranslatef(0.9, 0.5, 0);
	DrawCloud();
	glPopMatrix();

	//Draw One Wing WindMill
	DrawOne();

	
	//Draw Tree
	//tree 1
	glPushMatrix();
	glScalef(0.5, 0.5, 0);
	glTranslatef(0.2, 0.3, 0);
	DrawGreenTree();
	glPopMatrix();

	//tree 2
	glPushMatrix();
	glScalef(0.7, 0.7, 0);
	glTranslatef(0.3, 0.2, 0);
	DrawRedOrangeTree();
	glPopMatrix();

	//tree 3
	glPushMatrix();
	glScalef(0.7, 0.7, 0);
	glTranslatef(-0.8, 0.1, 0);
	DrawOrangeTree();
	glPopMatrix();

	//Pig
	glPushMatrix();



	pigx += pigspeed1;
	DrawPig();
	glPopMatrix();
}

void TwoWind() {
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);  //clear screen


	if (check == true) {
		//Background
		DrawBackground();

		//3j Sun
		DrawSun();
	}
	else {
		DrawBackground1();

		DrawMoon();

		glPushMatrix();
		glScalef(0.1, 0.05, 0);
		glTranslatef(5, 7, 0);
		DrawStar();
		glPopMatrix();

		glPushMatrix();
		glScalef(0.1, 0.05, 0);
		glTranslatef(-5, 6, 0);
		DrawStar();
		glPopMatrix();

		glPushMatrix();
		glScalef(0.1, 0.05, 0);
		glTranslatef(-0, 14, 0);
		DrawStar();
		glPopMatrix();
	}



	//3j Sun
	DrawSun();

	//cloud
	DrawCloud();

	//cloud 2 
	glPushMatrix();
	glScalef(0.6, 0.6, 0);
	glTranslatef(0.9, 0.5, 0);
	DrawCloud();
	glPopMatrix();

	//WindMill
	DrawTwo();

	//Draw Tree
	//tree 1
	glPushMatrix();
	glScalef(0.5, 0.5, 0);
	glTranslatef(0.2, 0.3, 0);
	DrawGreenTree();
	glPopMatrix();

	//tree 2
	glPushMatrix();
	glScalef(0.7, 0.7, 0);
	glTranslatef(0.3, 0.2, 0);
	DrawRedOrangeTree();
	glPopMatrix();

	//tree 3
	glPushMatrix();
	glScalef(0.7, 0.7, 0);
	glTranslatef(-0.8, 0.1, 0);
	DrawOrangeTree();
	glPopMatrix();

	//Pig
	glPushMatrix();

	pigx -= pigspeed1;
	DrawPig();
	glPopMatrix();
}

void ThreeWind() {
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);  //clear screen


	if (check == true) {
		//Background
		DrawBackground();

		//3j Sun
		DrawSun();
	}
	else {
		DrawBackground1();

		DrawMoon();

		glPushMatrix();
		glScalef(0.1, 0.05, 0);
		glTranslatef(5, 7, 0);
		DrawStar();
		glPopMatrix();

		glPushMatrix();
		glScalef(0.1, 0.05, 0);
		glTranslatef(-5, 6, 0);
		DrawStar();
		glPopMatrix();

		glPushMatrix();
		glScalef(0.1, 0.05, 0);
		glTranslatef(-0, 14, 0);
		DrawStar();
		glPopMatrix();
	}



	//3j Sun
	DrawSun();

	//cloud
	DrawCloud();

	//cloud 2 
	glPushMatrix();
	glScalef(0.6, 0.6, 0);
	glTranslatef(0.9, 0.5, 0);
	DrawCloud();
	glPopMatrix();

	//WindMill
	DrawThree();

	//Draw Tree
	//tree 1
	glPushMatrix();
	glScalef(0.5, 0.5, 0);
	glTranslatef(0.2, 0.3, 0);
	DrawGreenTree();
	glPopMatrix();

	//tree 2
	glPushMatrix();
	glScalef(0.7, 0.7, 0);
	glTranslatef(0.3, 0.2, 0);
	DrawRedOrangeTree();
	glPopMatrix();

	//tree 3
	glPushMatrix();
	glScalef(0.7, 0.7, 0);
	glTranslatef(-0.8, 0.1, 0);
	DrawOrangeTree();
	glPopMatrix();

	//Pig
	glPushMatrix();

	pigx -= pigspeed1;
	DrawPig();
	glPopMatrix();
}

void FourWind() {
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);  //clear screen


	if (check == true) {
		//Background
		DrawBackground();

		//3j Sun
		DrawSun();
	}
	else {
		DrawBackground1();

		DrawMoon();

		glPushMatrix();
		glScalef(0.1, 0.05, 0);
		glTranslatef(5, 7, 0);
		DrawStar();
		glPopMatrix();

		glPushMatrix();
		glScalef(0.1, 0.05, 0);
		glTranslatef(-5, 6, 0);
		DrawStar();
		glPopMatrix();

		glPushMatrix();
		glScalef(0.1, 0.05, 0);
		glTranslatef(-0, 14, 0);
		DrawStar();
		glPopMatrix();
	}



	//3j Sun
	DrawSun();

	//3k Cloud
	DrawCloud();

	//cloud 2 
	glPushMatrix();
	glScalef(0.6, 0.6, 0);
	glTranslatef(0.9, 0.5, 0);
	DrawCloud();
	glPopMatrix();

	//WindMill
	DrawFour();

	//Draw Tree
	//tree 1
	glPushMatrix();
	glScalef(0.5, 0.5, 0);
	glTranslatef(0.2, 0.3, 0);
	DrawGreenTree();
	glPopMatrix();

	//tree 2
	glPushMatrix();
	glScalef(0.7, 0.7, 0);
	glTranslatef(0.3, 0.2, 0);
	DrawRedOrangeTree();
	glPopMatrix();

	//tree 3
	glPushMatrix();
	glScalef(0.7, 0.7, 0);
	glTranslatef(-0.8, 0.1, 0);
	DrawOrangeTree();
	glPopMatrix();

	//Pig
	glPushMatrix();

	pigx += pigspeed1;

	DrawPig();
	glPopMatrix();
}

void display() {



	switch (qNo) {
	case 1:
		OneWind();
		break;
	case 2:
		TwoWind();
		break;
	case 3:
		ThreeWind();
		break;
	case 4:
		FourWind();
		break;
	default:
		OneWind();
		break;
	}

}


//--------------------------------------------------------------------

int WINAPI WinMain(HINSTANCE hInst, HINSTANCE, LPSTR, int nCmdShow)
{
	WNDCLASSEX wc;
	ZeroMemory(&wc, sizeof(WNDCLASSEX));

	wc.cbSize = sizeof(WNDCLASSEX);
	wc.hInstance = GetModuleHandle(NULL);
	wc.lpfnWndProc = WindowProcedure;
	wc.lpszClassName = WINDOW_TITLE;
	wc.style = CS_HREDRAW | CS_VREDRAW;

	if (!RegisterClassEx(&wc)) return false;

	HWND hWnd = CreateWindow(WINDOW_TITLE, WINDOW_TITLE, WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, CW_USEDEFAULT, 700, 700,
		NULL, NULL, wc.hInstance, NULL);

	//--------------------------------
	//	Initialize window for OpenGL
	//--------------------------------

	HDC hdc = GetDC(hWnd);

	//	initialize pixel format for the window
	initPixelFormat(hdc);

	//	get an openGL context
	HGLRC hglrc = wglCreateContext(hdc);

	//	make context current
	if (!wglMakeCurrent(hdc, hglrc)) return false;

	//--------------------------------
	//	End initialization
	//--------------------------------

	ShowWindow(hWnd, nCmdShow);

	MSG msg;
	ZeroMemory(&msg, sizeof(msg));

	while (true)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			if (msg.message == WM_QUIT) break;

			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

		display();

		SwapBuffers(hdc);
	}

	UnregisterClass(WINDOW_TITLE, wc.hInstance);

	return true;
}
//--------------------------------------------------------------------