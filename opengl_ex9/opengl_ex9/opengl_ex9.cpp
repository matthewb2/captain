#include <stdio.h>;
#include <gl/glut.h>;
#include <iostream>

using namespace std;

#define ARCBALL_SENS 0.2f //Arcball 기능 마우스 감도 조절

void doDisplay();
void doReshape(GLsizei width, GLsizei height);
void doKeyboard(GLubyte key, GLint x, GLint y);
void doSpecialKey(GLint key, GLint x, GLint y);
void doMenu(GLint value);
void drawPyramid();
void drawGrid();

GLfloat angleX=-45, angleY, angleZ;
GLfloat transX = 0.f, transY = 0.f, transZ = 0.f;
GLfloat scale = 1.f;
GLsizei lastWidth, lastHeight;
GLuint displayID;
GLboolean bObject = GL_TRUE;


//Arcball 기능 관련 : 마우스 이벤트, 드래그 이벤트 
void doMouse(GLint button, GLint state, GLint x, GLint y);
void doMotion(GLint x, GLint y);
GLboolean bArcball = GL_FALSE; //좌클릭 버튼 드래그에 의한 화면 카메라 회전 기능
GLboolean bParallel = GL_FALSE; //휠 버튼 드래그에 의한 화면 카메라 평행이동 기능

//아크볼 기능에 의한 MV 회전 및 이동
GLfloat cameraRX = 0.f;
GLfloat cameraRY = 0.f;
GLfloat cameraTX = 0.f;
GLfloat cameraTY = 0.f;

//드래그 변수(변화 전 커서 위치, 현재 커서 위치) : 모션 벡터용
GLint preCursorX = 0;
GLint preCursorY = 0;
GLint nowCursorX = 0;
GLint nowCursorY = 0;

int main(int argc, char **argv)
{
	glutInit(&argc, argv);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(1000, 1000);
	glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH | GLUT_SINGLE);

	printf("Press 'Q W E A S D' Key is 3D Object Rotation.\nPress 'R' Key is Reset Position.\n\n");
	printf("Press '← → ↑ ↓' Key is 3D Object Translation.\nPress 'Home' Key is Reset Translation.\n\n");
	printf("Press '+/-' Key is 3D Object Zoom In/Out.\nPress 'Z' Key is Reset Scale.\n\n");
	
	glutCreateWindow("Arcball Test"); {
		displayID = glGenLists(1);
		glNewList(displayID, GL_COMPILE); {
			//drawPyramid();
			drawGrid();




		} glEndList();

		glutCreateMenu(doMenu); {
			glutAddMenuEntry("프로그램 종료", 0);
			glutAddMenuEntry("Model Pyramid", 1);
			glutAddMenuEntry("Model Cylinder", 2);
		} glutAttachMenu(GLUT_RIGHT_BUTTON);

		glEnable(GL_DEPTH_TEST);
		glutDisplayFunc(doDisplay);
		glutKeyboardFunc(doKeyboard);
		glutSpecialFunc(doSpecialKey);
		glutMouseFunc(doMouse);
		glutMotionFunc(doMotion);
		glutReshapeFunc(doReshape);
	} glutMainLoop();

	return 0;
}


void doKeyboard(GLubyte key, GLint x, GLint y) {
	//모델링 회전 변환 : 객체 자체를 회전 (R : 초기 각도로 리셋)
	switch (key) {
	case 27: exit(0); break;
	case 'A': case 'a': angleY -= 2; break;
	case 'D': case 'd': angleY += 2; break;
	case 'W': case 'w': angleX -= 2; break;
	case 'S': case 's': angleX += 2; break;
	case 'Q': case 'q': angleZ += 2; break;
	case 'E': case 'e': angleZ -= 2; break;
	case 'R': case 'r': angleX = angleY = angleZ = cameraRX = cameraRY = 0.f; break;

	//모델링 크기 변환 : 객체 자체를 확대/축소 (Z : 초기 크기로 리셋)
	case '+': scale += 0.005; break;
	case '-': scale -= 0.005; break;
	case 'Z': case 'z': scale = 1.0; break;
	}
		
	glutPostRedisplay();
}

void doSpecialKey(GLint key, GLint x, GLint y) {
	//모델링 이동 변환 : 객체 자체를 평행 이동 (Home : 초기 위치로 리셋)
	switch (key) {
	case GLUT_KEY_LEFT: transX -= 0.01; break;
	case GLUT_KEY_RIGHT: transX += 0.01; break;
	case GLUT_KEY_UP: transY += 0.01; break;
	case GLUT_KEY_DOWN: transY -= 0.01; break;
	case GLUT_KEY_HOME: transX = transY = transZ = cameraTX = cameraTY = 0.f; break;
	}

	
	glutPostRedisplay();
}

void doReshape(GLsizei width, GLsizei height) {
	lastWidth = width;
	lastHeight = height;

	glViewport(0, 0, width, height);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(40.0, (GLfloat)width / (GLfloat)height, 1.0, 10.0);
}

void doMenu(GLint value) {
	switch (value) {
	case 0:
		exit(0);
		break;
	case 1:
		bObject = GL_TRUE;
		break;
	case 2:
		bObject = GL_FALSE;
		break;
	}
	glutPostRedisplay();
}

void doMouse(GLint button, GLint state, GLint x, GLint y) {
	//Arcball Function : Left Drag = Camera Rotation
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) { //When First Pressed Button
		bArcball = GL_TRUE;
		preCursorX = nowCursorX = x;
		preCursorY = nowCursorY = y;
	}
	else {
		bArcball = GL_FALSE;
	}

	//Arcball Function : Wheel Drag = Camera Perallel Translation
	if (button == GLUT_MIDDLE_BUTTON && state == GLUT_DOWN) { //When First Pressed Button
		bParallel = GL_TRUE;
		preCursorX = nowCursorX = x;
		preCursorY = nowCursorY = y;
	}
	else {
		bParallel = GL_FALSE;
	}
}

void doMotion(GLint x, GLint y) {
	if (bArcball == GL_TRUE) { //좌클릭 버튼 드래그 시 회전 변환
		//현재 커서 위치
		nowCursorX = x;
		nowCursorY = y;

		//모션 벡터(현재 커서 - 이전 커서)만큼 MV 회전 각도 계산 
		if (nowCursorX != preCursorX || nowCursorY != preCursorY) {
			cameraRX += (nowCursorX - preCursorX)*ARCBALL_SENS;
			cameraRY += (nowCursorY - preCursorY)*ARCBALL_SENS;

			//현재 커서 위치 이전 커서 위치로 저장
			preCursorX = nowCursorX;
			preCursorY = nowCursorY;
		}
	}
	else if (bParallel == GL_TRUE) { //휠 버튼 드래그 시 평행이동 변환
		//현재 커서 위치
		nowCursorX = x;
		nowCursorY = y;

		//모션 벡터(현재 커서 - 이전 커서)만큼 MV 평행 이동거리 계산
		if (nowCursorX != preCursorX || nowCursorY != preCursorY) {
			cameraTX += (nowCursorX - preCursorX)*ARCBALL_SENS*0.01f;
			cameraTY -= (nowCursorY - preCursorY)*ARCBALL_SENS*0.01f;

			//현재 커서 위치 이전 커서 위치로 저장
			preCursorX = nowCursorX;
			preCursorY = nowCursorY;
		}
	}

	char titleInfo[128] = { 0 };
	//sprintf(titleInfo, "View R(%.1f, %.1f), T(%.f, %.f), S(%.1f)", cameraRX, cameraRY, cameraTX, cameraTY, scale);
	glutSetWindowTitle(titleInfo);

	glutPostRedisplay();
}

void drawGrid() {
	
	glColor3f(0.5, 0.5, 0.5);
	glBegin(GL_LINES);
	for (int i = 0; i <= 10; i++)
	{
		// horizontal
		glVertex3f(-1.0f + i * 0.2f, -1.0f, 0.0f);
		glVertex3f(-1.0f + i * 0.2f, 1.0f, 0.0f);

		// vertical
		glVertex3f(-1.0f, -1.0f + i * 0.2f, 0.0f);
		glVertex3f(1.0f, -1.0f + i * 0.2f, 0.0f);
	}
	glEnd();
	
}

void drawPyramid() {
	glShadeModel(GL_FLAT);

	//아랫면 흰 바닥
	glColor3f(1, 1, 1);
	glBegin(GL_QUADS); {
		glVertex2f(-0.3, 0.3);
		glVertex2f(0.3, 0.3);
		glVertex2f(0.3, -0.3);
		glVertex2f(-0.3, -0.3);
	} glEnd();

	glBegin(GL_TRIANGLE_FAN); {
		//위쪽 빨간 면
		glColor3f(1, 1, 1);
		glVertex3f(0.0, 0.0, 0.5);
		glColor3f(1, 0, 0);
		glVertex2f(0.3, 0.3);
		glVertex2f(-0.3, 0.3);

		//왼쪽 노란 면
		glColor3f(1, 1, 0);
		glVertex2f(-0.3, -0.3);

		//아래쪽 초록 면
		glColor3f(0, 1, 0);
		glVertex2f(0.3, -0.3);

		//오른쪽 파란 면
		glColor3f(0, 0, 1);
		glVertex2f(0.3, 0.3);
	} glEnd();
}

void doDisplay() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix(); { //마우스 UI 변환과 키보드 UI 변환 구분 주의
		//마우스 평행이동 변환
		glTranslatef(cameraTX, cameraTY, -2.f);

		//키보드 평행이동 변환
		glTranslatef(transX, transY, transZ);
		
		//Arcball 마우스 회전 변환
		glRotatef(cameraRX, 0.f, 1.f, 0.f);
		glRotatef(cameraRY, 1.f, 0.f, 0.f);
		
		glScalef(scale, scale, scale);
		glRotatef(angleX, 1.f, 0.f, 0.f);
		glRotatef(angleY, 0.f, 1.f, 0.f);
		glRotatef(angleZ, 0.f, 0.f, 1.f);

		if (bObject == GL_TRUE) {
			glCallList(displayID); //피라미드 객체
		}
		else {
			GLUquadricObj *pQuad;
			pQuad = gluNewQuadric(); {
				gluQuadricDrawStyle(pQuad, GLU_LINE);
				glTranslatef(0.f, 0.f, -0.6f);
				glColor3f(1.f, 1.f, 1.f);
				gluCylinder(pQuad, 0.3, 0.3, 1.2, 20, 20);
			} gluDeleteQuadric(pQuad);
		}
	} glPopMatrix();

	glFlush();
}