#include "StdAfx.h"
#include "GLRenderer.h"
#include "GL\gl.h"
#include "GL\glu.h"
#include "GL\glaux.h"
#include "GL\glut.h"
//#pragma comment(lib, "GL\\glut32.lib")

CGLRenderer::CGLRenderer(void)
{
	ugaoVetrenjace = 0;
	ugaoLevo = 0;
	ugaoGore = 0;
}

CGLRenderer::~CGLRenderer(void)
{
}

bool CGLRenderer::CreateGLContext(CDC* pDC)
{
	PIXELFORMATDESCRIPTOR pfd ;
   	memset(&pfd, 0, sizeof(PIXELFORMATDESCRIPTOR));
   	pfd.nSize  = sizeof(PIXELFORMATDESCRIPTOR);
   	pfd.nVersion   = 1; 
   	pfd.dwFlags    = PFD_DOUBLEBUFFER | PFD_SUPPORT_OPENGL | PFD_DRAW_TO_WINDOW;   
   	pfd.iPixelType = PFD_TYPE_RGBA; 
   	pfd.cColorBits = 32;
   	pfd.cDepthBits = 24; 
   	pfd.iLayerType = PFD_MAIN_PLANE;
	
	int nPixelFormat = ChoosePixelFormat(pDC->m_hDC, &pfd);
	
	if (nPixelFormat == 0) return false; 

	BOOL bResult = SetPixelFormat (pDC->m_hDC, nPixelFormat, &pfd);
  	
	if (!bResult) return false; 

   	m_hrc = wglCreateContext(pDC->m_hDC); 

	if (!m_hrc) return false; 

	return true;	
}

void CGLRenderer::PrepareScene(CDC *pDC)
{
	wglMakeCurrent(pDC->m_hDC, m_hrc);
	//---------------------------------
	
	glClearColor(1.0, 1.0, 1.0, 1.0);
	glEnable(GL_DEPTH_TEST);
	glCullFace(GL_BACK);
	glEnable(GL_CULL_FACE);

	brick = LoadTexture("brick.png");
	env = LoadTexture("env.png");
	glEnable(GL_TEXTURE_2D);

	//---------------------------------
	wglMakeCurrent(NULL, NULL);
}

void CGLRenderer::DrawScene(CDC *pDC)
{
	wglMakeCurrent(pDC->m_hDC, m_hrc);
	//---------------------------------
	
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();

	gluLookAt(0.2, 0.0, 8.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);

	//glLineWidth(2.0);
	//glPointSize(10);
	//glBegin(GL_TRIANGLES);
	//glColor3f(0.764, 0.764, 0.764);
	//glVertex2f(2.0, 1.0);
	//glVertex2f(2.0, 0.0);
	//glVertex2f(1.0, 1.0);
	//glEnd();

	glDisable(GL_DEPTH_TEST);
	//glDisable(GL_CULL_FACE);
	glDisable(GL_LIGHTING);
	glPushMatrix();
	glRotated(ugaoGore, 1.0, 0.0, 0.0);
	glRotated(ugaoLevo, 0.0, 1.0, 0.0);
	glBindTexture(GL_TEXTURE_2D, env);
	DrawCube(10);
	glPopMatrix();
	glEnable(GL_LIGHTING);
	//glEnable(GL_CULL_FACE);
	glEnable(GL_DEPTH_TEST);

	glEnable(GL_LIGHT0);
	float light_ambient[] = { 0.0, 0.0, 0.0, 1.0 };
	float light_diffuse[] = { 1.0, 1.0, 1.0, 1.0 };
	float light_specular[] = { 1.0, 1.0, 1.0, 1.0 };
	glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
	glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
	GLfloat light_position[] = { 1.0, 1.0, 0.5, 0.0 };

	glLightfv(GL_LIGHT0, GL_POSITION, light_position);

	glColor3f(1.0, 0.388, 0.278);
	glPushMatrix();
	glTranslatef(0.0, -4.0, -12.0);
	glBindTexture(GL_TEXTURE_2D, brick);
	DrawTube(2.5, 3.5, 10.0, 32);
	glPopMatrix();

	glColor3f(0.764, 0.764, 0.764);
	glPushMatrix();
	glTranslatef(0.0, 0.9, -12.0);
	DrawCone(3.8, 2.0, 32);

	glDisable(GL_DEPTH_TEST);

	for (int i = 0; i < 4; i++)
	{
		glPushMatrix();
		glRotatef(ugaoVetrenjace, 0.0, 0.0, 1.0);
		DrawPaddle(8.0, 1.5);
		ugaoVetrenjace += 90.0;
		glPopMatrix();
	}
	glEnable(GL_DEPTH_TEST);
	glPopMatrix();



	glFlush();
	SwapBuffers(pDC->m_hDC);
	//---------------------------------
	wglMakeCurrent(NULL, NULL);
}

void CGLRenderer::Reshape(CDC *pDC, int w, int h)
{
	wglMakeCurrent(pDC->m_hDC, m_hrc);
	//---------------------------------
	
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(40, (double)w / (double)h, 1, 100);
	glMatrixMode(GL_MODELVIEW);

	//---------------------------------
	wglMakeCurrent(NULL, NULL);
}

void CGLRenderer::DestroyScene(CDC *pDC)
{
	wglMakeCurrent(pDC->m_hDC, m_hrc);
	// ... 

	glDeleteTextures(1, &brick);
	glDeleteTextures(1, &env);

	wglMakeCurrent(NULL,NULL); 
	if(m_hrc) 
	{
		wglDeleteContext(m_hrc);
		m_hrc = NULL;
	}
}

UINT CGLRenderer::LoadTexture(char * fileName)
{
	UINT texID;
	DImage img;
	img.Load(CString(fileName));
	glPixelStorei(GL_UNPACK_ALIGNMENT, 4);

	glGenTextures(1, &texID);
	glBindTexture(GL_TEXTURE_2D, texID);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);

	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGBA, img.Width(), img.Height(), GL_BGRA_EXT, GL_UNSIGNED_BYTE, img.GetDIBBits());

	return texID;
}

void CGLRenderer::DrawCube(double a)
{
	glBegin(GL_QUADS);

	//// prednja strana kocke je na 1/3 od visine slike, a na 1/4 od sirine

	//Prednja stranica
	glNormal3f(0.0, 0.0, 1.0);
	glTexCoord2f(0.25, 0.333333);
	//glTexCoord2f(0.0, 1.0);
	glVertex3f(-a / 2, a / 2, a / 2);
	glTexCoord2f(0.25, 0.666666);
	//glTexCoord2f(0.0, 0.0);
	glVertex3f(-a / 2, -a / 2, a / 2);
	glTexCoord2f(0.5, 0.666666);
	//glTexCoord2f(1.0, 0.0);
	glVertex3f(a / 2, -a / 2, a / 2);
	glTexCoord2f(0.5, 0.333333);
	//glTexCoord2f(1.0, 1.0);
	glVertex3f(a / 2, a / 2, a / 2);

	//Desna stranica
	glNormal3f(1.0, 0.0, 0.0);
	glTexCoord2f(0.5, 0.333333);
	glVertex3f(a / 2, a / 2, a / 2);
	glTexCoord2f(0.5, 0.666666);
	glVertex3f(a / 2, -a / 2, a / 2);
	glTexCoord2f(0.75, 0.666666);
	glVertex3f(a / 2, -a / 2, -a / 2);
	glTexCoord2f(0.75, 0.333333);
	glVertex3f(a / 2, a / 2, -a / 2);

	//Zadnja stranica
	glNormal3f(0.0, 0.0, -1.0);
	glTexCoord2f(0.75, 0.333333);
	glVertex3f(a / 2, a / 2, -a / 2);
	glTexCoord2f(0.75, 0.666666);
	glVertex3f(a / 2, -a / 2, -a / 2);
	glTexCoord2f(1.0, 0.666666);
	glVertex3f(-a / 2, -a / 2, -a / 2);
	glTexCoord2f(1.0, 0.333333);
	glVertex3f(-a / 2, a / 2, -a / 2);

	//Leva stranica
	glNormal3f(-1.0, 0.0, 0.0);
	glTexCoord2f(0.0, 0.333333);
	glVertex3f(-a / 2, a / 2, -a / 2);
	glTexCoord2f(0.0, 0.666666);
	glVertex3f(-a / 2, -a / 2, -a / 2);
	glTexCoord2f(0.25, 0.666666);
	glVertex3f(-a / 2, -a / 2, a / 2);
	glTexCoord2f(0.25, 0.333333);
	glVertex3f(-a / 2, a / 2, a / 2);

	//Gornja stranica
	glNormal3f(0.0, 1.0, 0.0);
	glTexCoord2f(0.25, 0.333333);
	glVertex3f(-a / 2, a / 2, a / 2);
	glTexCoord2f(0.5, 0.333333);
	glVertex3f(a / 2, a / 2, a / 2);
	glTexCoord2f(0.5, 0.0);
	glVertex3f(a / 2, a / 2, -a / 2);
	glTexCoord2f(0.25, 0.0);
	glVertex3f(-a / 2, a / 2, -a / 2);

	//Donja stranica
	glNormal3f(0.0, -1.0, 0.0);
	glTexCoord2f(0.5, 1.0);
	glVertex3f(-a / 2, -a / 2, -a / 2);
	glTexCoord2f(0.25, 1.0);
	glVertex3f(a / 2, -a / 2, -a / 2);
	glTexCoord2f(0.25, 0.666666);
	glVertex3f(a / 2, -a / 2, a / 2);
	glTexCoord2f(0.5, 0.666666);
	glVertex3f(-a / 2, -a / 2, a / 2);

	glEnd();
}

void CGLRenderer::DrawTube(double r1, double r2, double h, int n)
{
	//valjak (prizma) sa poluprecnicima r1 i r2, visine h i sa n segmenata

	double xx1;
	double xx2;
	double yy1 = h / 2;
	double yy2 = - h / 2;
	double zz1;
	double zz2;
	double ugao = 0.0;
	double nn = 360.0 / (2.0 * (double)n);
	double cc = cos(nn*toRad);
	double ss = sin(nn*toRad);
	zz1 = cc * r1;
	zz2 = cc * r2;

	xx1 = ss * r1;
	xx2 = ss * r2;
	
	double tacka1 = 0.0;
	double tacka2 = 1.0/(double)n;

	for (int i = 0; i < n; i++)
	{
		glPushMatrix();

		glRotated(ugao, 0.0, 1.0, 0.0);

		glBegin(GL_QUADS);
		double v1[3] = { -xx1, yy1, zz1 };
		double v2[3] = { -xx2, yy2, zz2 };
		double v3[3] = { xx2, yy2, zz2 };
		glNormal3dv(calculate(v1, v2, v3));
		glTexCoord2f(tacka1, 1.0);
		glVertex3d(-xx1, yy1, zz1);
		glTexCoord2f(tacka1, 0.0);
		glVertex3d(-xx2, yy2, zz2);
		glTexCoord2f(tacka2, 0.0);
		glVertex3d(xx2, yy2, zz2);
		glTexCoord2f(tacka2, 1.0);
		glVertex3d(xx1, yy1, zz1);
		glEnd();

		ugao += 360.0/(double)n;

		tacka1 += 1.0 / (double)n;
		tacka2 += 1.0 /(double)n;

		glPopMatrix();
	}
}

void CGLRenderer::DrawCone(double r, double h, int n)
{
	//kupa(piramida) poluprecnika r i visine h, n segmenata

	double xx;
	double zz;
	double yy = h;
	double nn = 360.0 / (2.0 * (double)n);
	double cc = cos(nn*toRad);
	double ss = sin(nn*toRad);
	xx = ss*r;
	zz = cc*r;

	double ugao = 0.0;
	for (int i = 0; i < n; i++)
	{
		glPushMatrix();
		glRotated(ugao, 0.0, 1.0, 0.0);

		glBegin(GL_TRIANGLES);

		double v1[3] = { 0.0,yy,0.0 };
		double v2[3] = { -xx,0.0,zz };
		double v3[3] = { xx,0.0,zz };
		glNormal3dv(calculate(v1, v2, v3));
		glVertex3dv(v1);
		glVertex3dv(v2);
		glVertex3dv(v3);
		glEnd();
		ugao += 360.0 / (double)n;
		glPopMatrix();
	}
}

void CGLRenderer::DrawPaddle(double length, double width)
{
	//krilo vetrenjace

	glBegin(GL_QUADS);
	double v1[3] = { 0.0, width / (double)8, 0.0 };
	double v2[3] = { 0.0, 0.0, 0.0 };
	double v3[3] = { length, 0.0, 0.0 };
	glNormal3dv(calculate(v1, v2, v3));
	glVertex3f(0.0, width / (double)8, 0.0);
	glVertex3f(0.0, 0.0, 0.0);
	glVertex3f(length, 0.0, 0.0);
	glVertex3f(length, width / (double)8, 0.0);
	glEnd();

	glBegin(GL_TRIANGLES);
	double v11[3] = { length/8.0, 0.0, 0.0 };
	double v22[3] = { (double)2 * length / (double)8, -(double)7 * width / (double)8, 0.0 };
	double v33[3] = { (double)2 * length / (double)8, 0.0, 0.0 };
	glNormal3dv(calculate(v11, v22, v33));
	glVertex3f(length/(double)8, 0.0, 0.0);
	glVertex3f((double)2*length / (double)8, -(double)7 * width / (double)8, 0.0);
	glVertex3f((double)2 * length / (double)8, 0.0, 0.0);
	glEnd();

	glBegin(GL_QUADS);
	double v111[3] = { (double)2 * length / (double)8, 0.0, 0.0 };
	double v222[3] = { (double)2 * length / (double)8, -(double)7 * width / (double)8, 0.0 };
	double v333[3] = { length, -(double)7 * width / (double)8, 0.0 };
	glNormal3dv(calculate(v111, v222, v333));
	glVertex3f((double)2 * length / (double)8, 0.0, 0.0);
	glVertex3f((double)2 * length / (double)8, -(double)7 * width / (double)8, 0.0);
	glVertex3f(length, -(double)7 * width / (double)8, 0.0);
	glVertex3f(length,0.0, 0.0);
	glEnd();
}

double * CGLRenderer::calculate(double * a, double * b, double * c)
{
	double x[] = { b[0] - a[0],b[1] - a[1],b[2] - a[2] };
	double y[] = { c[0] - a[0],c[1] - a[1],c[2] - a[2] };

	double *result = cross_product(x, y);
	return result;
}

double * CGLRenderer::cross_product(double * v1, double * v2)
{
	double result[] = { v1[1] * v2[2] - v1[2] * v1[1], v1[0] * v2[1] - v1[1] * v2[0], v1[2] * v2[0] - v1[0] * v2[2] };

	normalize(result);

	return result;
}

void CGLRenderer::normalize(double * v)
{
	double length = sqrt(v[0] * v[0] + v[1] * v[1] + v[2] * v[2]);
	v[0] /= length;
	v[1] /= length;
	v[2] /= length;
}




