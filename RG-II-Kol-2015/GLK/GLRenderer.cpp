#include "StdAfx.h"
#include "GLRenderer.h"
#include "GL\gl.h"
#include "GL\glu.h"
#include "GL\glaux.h"
#include "GL\glut.h"
//#pragma comment(lib, "GL\\glut32.lib")

CGLRenderer::CGLRenderer(void)
{
	m_beta = 0.0;
	m_alpha = 0.0;
	m_bLight = false;
	m_dist = 10;
	m_moonRot =0.0;
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

	/////////// Teksture
	T[0] = LoadTexture("TSC0.jpg");
	T[1] = LoadTexture("TSC1.jpg");
	T[2] = LoadTexture("TSC2.jpg");
	T[3] = LoadTexture("TSC3.jpg");
	T[4] = LoadTexture("TSC4.jpg");
	T[5] = LoadTexture("TSC5.jpg");
	M[0] = LoadTexture("M0.jpg");
	M[1] = LoadTexture("M1.jpg");
	M[2] = LoadTexture("M2.jpg");
	M[3] = LoadTexture("M3.jpg");
	M[4] = LoadTexture("M4.jpg");
	M[5] = LoadTexture("M5.jpg");
	S[0] = LoadTexture("S0.jpg");
	S[1] = LoadTexture("S1.jpg");
	S[2] = LoadTexture("S2.jpg");
	S[3] = LoadTexture("S3.jpg");
	S[4] = LoadTexture("S4.jpg");
	S[5] = LoadTexture("S5.jpg");
	glEnable(GL_TEXTURE_2D);
	///////////////

	//---------------------------------
	wglMakeCurrent(NULL, NULL);
}

void CGLRenderer::DrawScene(CDC *pDC)
{
	wglMakeCurrent(pDC->m_hDC, m_hrc);
	//---------------------------------
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();

	gluLookAt(0.2, 0.0, 1.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
	//glLineWidth(2.0);
	
	/*glPointSize(10);
	glBegin(GL_TRIANGLES);
	glColor3f(0.5, 0.5, 1.0);
	glVertex2f(2.0, 1.0);
	glVertex2f(2.0, 0.0);
	glVertex2f(1.0, 1.0);
	glEnd();
	DrawPatch(3.0, 20);*/

	glDisable(GL_DEPTH_TEST);
	glDisable(GL_LIGHTING);
	glPushMatrix();
	glRotated(m_beta, 1.0, 0.0, 0.0);
	glRotated(m_alpha, 0.0, 1.0, 0.0);
	DrawSpace(1.0, 20);
	glPopMatrix();

	if (m_bLight)
	{
		glEnable(GL_LIGHTING);
		glEnable(GL_LIGHT0);
	}
	float light_ambient[] = { 0.0, 0.0, 0.0, 1.0 };
	float light_diffuse[] = { 1.0, 1.0, 1.0, 1.0 };
	float light_specular[] = { 1.0, 1.0, 1.0, 1.0 };
	glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
	glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
	GLfloat light_position[] = { 0.0, 0.0, 1.0, 0.0 };
	glEnable(GL_DEPTH_TEST);
	glTranslatef(0, 0, -m_dist);
	glRotated(m_beta, 1.0, 0.0, 0.0);
	glRotated(m_alpha, 0.0, 1.0, 0.0);
	glLightfv(GL_LIGHT0, GL_POSITION, light_position);
	DrawEarth(3.0, 20);
	glTranslatef(-50.0, 0.0, 0.0);
	glRotatef(m_moonRot, 0.0, 1.0, 0.0);
	DrawMoon(1.0, 20);

		
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

	glDeleteTextures(6, T);
	glDeleteTextures(6, M);
	glDeleteTextures(6, S);

	wglMakeCurrent(NULL,NULL); 
	if(m_hrc) 
	{
		wglDeleteContext(m_hrc);
		m_hrc = NULL;
	}
}

void CGLRenderer::DrawPatch(double R, int n)
{
	double delta = 2. / (double)n;
	double y = 1.0;
	for (int i = 0; i < n; i++)
	{
		glBegin(GL_TRIANGLE_STRIP);
		double x = -1.0;
		for (int j = 0; j < n + 1; j++)
		{
			double phi, theta;
			inverseTSC(x, y, phi, theta);
			double xd, yd, zd;
			xd = R * cos(theta) * sin(phi);
			yd = R * sin(theta);
			zd = R * cos(theta) * cos(phi);
			glNormal3f(xd / R, yd / R, zd / R);
			glTexCoord2f((x + 1.0) / 2.0,
				(-y + 1.0) / 2.0);
			glVertex3f(xd, yd, zd);
			inverseTSC(x, y - delta, phi, theta);
			xd = R * cos(theta) * sin(phi);
			yd = R * sin(theta);
			zd = R * cos(theta) * cos(phi);
			glNormal3f(xd / R, yd / R, zd / R);
			glTexCoord2f((x + 1.0) / 2.0,
				(-y + delta + 1.0) / 2.0);
			glVertex3f(xd, yd, zd);
			x += delta;
		}
		glEnd();
		y -= delta;
	}

}

void CGLRenderer::inverseTSC(double x, double y, double & phi, double & theta)
{
	phi = atan(x);
	theta = atan(y * cos(phi));
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

void CGLRenderer::DrawEarth(double R, int tes)
{
	glPushMatrix();
	for (int i = 0; i < 4; i++)
	{
		glBindTexture(GL_TEXTURE_2D, T[i]);
		DrawPatch(R, tes);
		glRotated(90, 0.0, 1.0, 0.0);
	}
	glPopMatrix();
	glPushMatrix();
	glRotated(-90, 1.0, 0.0, 0.0);
	glBindTexture(GL_TEXTURE_2D, T[4]);
	DrawPatch(R, tes);
	glPopMatrix();
	glPushMatrix();
	glRotated(90, 1.0, 0.0, 0.0);
	glBindTexture(GL_TEXTURE_2D, T[5]);
	DrawPatch(R, tes);
	glPopMatrix();
}

void CGLRenderer::DrawMoon(double R, int tes)
{
	glPushMatrix();
	for (int i = 0; i < 4; i++)
	{
		glBindTexture(GL_TEXTURE_2D, M[i]);
		DrawPatch(R, tes);
		glRotated(90, 0.0, 1.0, 0.0);
	}
	glPopMatrix();
	glPushMatrix();
	glRotated(-90, 1.0, 0.0, 0.0);
	glBindTexture(GL_TEXTURE_2D, M[4]);
	DrawPatch(R, tes);
	glPopMatrix();
	glPushMatrix();
	glRotated(90, 1.0, 0.0, 0.0);
	glBindTexture(GL_TEXTURE_2D, M[5]);
	DrawPatch(R, tes);
	glPopMatrix();
}

void CGLRenderer::DrawSpace(double R, int tes)
{
	glDisable(GL_CULL_FACE);
	glPushMatrix();
	for (int i = 0; i < 4; i++)
	{
		glBindTexture(GL_TEXTURE_2D, S[i]);
		DrawPatch(R, tes);
		glRotated(90, 0.0, 1.0, 0.0);
	}
	glPopMatrix();
	glPushMatrix();
	glRotated(-90, 1.0, 0.0, 0.0);
	glBindTexture(GL_TEXTURE_2D, S[4]);
	DrawPatch(R, tes);
	glPopMatrix();
	glPushMatrix();
	glRotated(90, 1.0, 0.0, 0.0);
	glBindTexture(GL_TEXTURE_2D, S[5]);
	DrawPatch(R, tes);
	glPopMatrix();
	glEnable(GL_CULL_FACE);
}
