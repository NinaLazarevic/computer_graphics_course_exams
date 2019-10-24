#include "StdAfx.h"
#include "GLRenderer.h"
#include "GL\gl.h"
#include "GL\glu.h"
#include "GL\glaux.h"
#include "GL\glut.h"
//#pragma comment(lib, "GL\\glut32.lib")

CGLRenderer::CGLRenderer(void)
{
	a = 0.0;
	b = 0.0;
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
	//glCullFace(GL_BACK);
	//glEnable(GL_CULL_FACE);

	brick = LoadTexture(CString("brick.png"));
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

	gluLookAt(3.0, 5.0, 5.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);

	/*glLineWidth(2.0);
	glPointSize(10);
	glBegin(GL_LINE_LOOP);
	glColor3f(0.0, 0.0, 0.0);
	glVertex3f(1.0, 0.0,-(1/sqrtf(2)));
	glVertex3f(0.0, 1.0, 1 / sqrtf(2));
	glVertex3f(0.0, -1.0, 1 / sqrtf(2));
	glEnd();*/


	//////07.07.2014
	//glColor3f(1.0, 0.0, 0.0);
	//glBindTexture(GL_TEXTURE_2D, brick);

	//glPushMatrix();

	//glRotatef(a, 0.0, 1.0, 0.0);
	//DrawFigure(8, 1.5, a, b, 0, CString("brick.png"));

	//glPopMatrix();

	////// 06.10.2015
	//DrawTetrahedron(3);

	////18.09.2017
	/*glColor3f(1.0, 0.0, 0.0);
	drawTorus2(0.08, 0.2, 16, 16, 0);*/

	//// 5.10.2011
	glColor3f(0.0, 0.0, 0.0);
	DrawGlobe(3.0);

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
	gluPerspective(45, (double)w / (double)h, 1, 100);
	glMatrixMode(GL_MODELVIEW);
	//---------------------------------
	wglMakeCurrent(NULL, NULL);
}

void CGLRenderer::DestroyScene(CDC *pDC)
{
	wglMakeCurrent(pDC->m_hDC, m_hrc);
	// ... 

	glDeleteTextures(1, &brick);

	wglMakeCurrent(NULL,NULL); 
	if(m_hrc) 
	{
		wglDeleteContext(m_hrc);
		m_hrc = NULL;
	}
}

UINT CGLRenderer::LoadTexture(CString fileName)
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


///// 07.07.2014
void CGLRenderer::DrawRoller(float r, float h, int n)
{
	//valjak (prizma) poluprecnkia r, visine h i br segmenata n
	float xx;
	float yy = h/2;
	float zz;

	float ugao = 0.0;
	float nn = 360.0 / (2.0 * n);
	zz = cosf(nn*toRad)*r;
	xx = sinf(nn*toRad)*r;

	///koordinate teksture
	float tacka1 = 0.0;
	float tacka2 = 1.0 /n;
	for (int i = 0; i < n; i++)
	{
		glPushMatrix();

		glRotated(ugao, 0.0, 1.0, 0.0);
		glBegin(GL_QUADS);
		glNormal3f(1.0, 0.0, 0.0);

		glTexCoord2f(tacka1, 1);
		glVertex3f(-xx, yy, zz);

		glTexCoord2f(tacka1, 0);
		glVertex3f(-xx, -yy, zz);

		glTexCoord2f(tacka2, 0);
		glVertex3f(xx, -yy, zz);

		glTexCoord2f(tacka2, 1);
		glVertex3f(xx, yy, zz);
		glEnd();

		glBegin(GL_TRIANGLES);
		glNormal3f(0.0, 1.0, 0.0);

		glVertex3f(-xx, yy, zz);
		glVertex3f(xx, yy, zz);
		glVertex3f(0.0, yy, 0.0);

		glEnd();


		glBegin(GL_TRIANGLES);
		glNormal3f(0.0, -1.0, 0.0);

		glVertex3f(-xx, -yy, zz);
		glVertex3f(xx, -yy, zz);
		glVertex3f(0.0, -yy, 0.0);

		glEnd();

		glPopMatrix();

		ugao += 360.0 / n;

		tacka1 += 1.0 / n;
		tacka2 += 1.0 / n;
	}

}

void CGLRenderer::DrawFigure(float h, float dx, float alpha, float beta, float dt, CString strTex)
{/*
		formira telo prikazano na slici 2 nakon vremena dt.Na vrhu tela se nalazi 
		osovina oblika valjka
		poluprečnika osnove dx i visine 0.2·h.Ispod je telo oblika valjka 10·dx×0.2·h.
		Na rastojanju
		od 7·dx od centra glave se nalaze četiri nosača koji su simetrično rapoređeni 
		i dimenzija su
		dx×h.Na dnu svakog nosača je glava oblika valjka dimenzija 2·dx×0.2·h.
		Pripremiti
		teksturu učitanu u prethodnoj tački iz datoteke strTex i primeniti
		na sve delove scene.Cela
		konstrukcija se rotira oko osovine kontantnom ugaonom brzinom alpha,
		dok se svaki od
		stubova rotira oko svoje ose ugaonom brzinom beta.*/

	//crtanje odozdo nagore
	// umesto ugaone brzine, samo su vrednosti uglova
	//teksturu ucitavam na pocetku

	float ugao = 0;
	glPushMatrix();

	for (int i = 0; i < 4; i++)
	{
		glPushMatrix();

		glRotatef(ugao, 0.0, 1.0, 0.0);
		glTranslatef(0.0, 0.0, 7*dx);

		glRotatef(beta, 0.0, 1.0, 0.0);

		DrawRoller(2*dx, 0.2*h, 32);
		
		glTranslatef(0.0, 0.1* h + h/2, 0.0);
		DrawRoller(dx, h, 32);

		glPopMatrix();
		ugao += 90;
	}

	glTranslatef(0.0, 0.2* h + h, 0.0);

	DrawRoller(10*dx, 0.2*h, 32);

	glTranslatef(0.0, 0.2* h, 0.0);

	DrawRoller(dx, 0.2*h, 32);

	glPopMatrix();
}

////// 06.10.2015

void CGLRenderer::Spherify(double x, double y, double z, double & phi, double & theta, double & R)
{
	//Dekartove coordinate (x,y,z) pretvara u polarne (phi theta, R)

	phi = atan(x);
	theta = atan(y*cos(phi));
	R = sqrt(x*x + y*y + z*z);
}

void CGLRenderer::Extrude(double & x, double & y, double & z, double R)
{
	//koristi prethodnu 
	//funkciju da Dekartove coordinate(x, y, z) pomeri radijalno od koordinatnog
	//početka na rastojanje R.

	double phi, theta, Rnow;
	Spherify(x, y, z, phi, theta, Rnow);

	x = R* cos(theta)*sin(phi);
	y = R*sin(theta);
	z = R*cos(theta)*cos(phi);

}

void CGLRenderer::DrawSide(double x1, double y1, double z1, double x2, double y2, double z2, double x3, double y3, double z3, int level, int maxLevel)
{
	//koja iscrtava trougao
	//	sa zadatim koordinatama, ako je level = maxLevel, u protivnom rekurzivno
	//	deli dati trougao na četiri nova i pomera temena tako da budu na opisanoj sferi

	if (level == maxLevel)
	{
		glLineWidth(2.0);
		glBegin(GL_LINE_LOOP);
		glColor3f(0.0, 0.0, 0.0);
		glVertex3f(x1, y1, z1);
		glVertex3f(x2, y2, z2);
		glVertex3f(x3, y3, z3);
		glEnd();

		return;
	}

	double x11 = (x1 + x2) / 2;  double y11 = (y1 + y2) / 2;	double z11 = (z1 + z2) / 2;
	double x22 = (x2 + x3) / 2;  double y22 = (y3 + y2) / 2;	double z22 = (z3 + z2) / 2;
	double x33 = (x1 + x3) / 2;	 double y33 = (y1 + y3) / 2;	double z33 = (z1 + z3) / 2;

	double RR = sqrt(3.0 / 2.0); //zbog pocetnih koordinata
	Extrude(x11, y11, z11, RR);
	Extrude(x22, y22, z22, RR);
	Extrude(x33, y33, z33, RR);
	level++;
	DrawSide(x11, y11, z11, x22, y22, z22, x33, y33, z33, level, maxLevel); //novi trougao
	DrawSide(x11, y11, z11, x1, y1, z1, x33, y33, z33, level, maxLevel);
	DrawSide(x11, y11, z11, x22, y22, z22, x2, y2, z2, level, maxLevel);
	DrawSide(x3, y3, z3, x22, y22, z22, x33, y33, z33, level, maxLevel);

}

void CGLRenderer::DrawTetrahedron(int maxLevel)
{
	//koja iscrtava čitavu figure, vršeći podelu do	zadatog nivoa.
	//Početne coordinate temena tetraedra su: ((+-)1, 0, -1/sqrt2), (0,(+-)1,1/sqrt2)

	DrawSide(1.0, 0.0, -(1 / sqrt(2.0)), -1.0, 0.0, -(1 / sqrt(2.0)), 0.0, 1.0, 1 / sqrt(2.0), 0, maxLevel);
	DrawSide(1.0, 0.0, -(1 / sqrt(2.0)), -1.0, 0.0, -(1 / sqrt(2.0)), 0.0, -1.0, 1 / sqrt(2.0), 0, maxLevel);
	DrawSide(-1.0, 0.0, -(1 / sqrt(2.0)), 0.0, 1.0, 1 / sqrt(2.0), 0.0, -1.0, 1 / sqrt(2.0), 0, maxLevel);
	DrawSide(1.0, 0.0, -(1 / sqrt(2.0)), 0.0, 1.0, 1 / sqrt(2.0), 0.0, -1.0, 1 / sqrt(2.0), 0, maxLevel);

}

////18.09.2017

void CGLRenderer::DrawThorus(double R, double r)
{
	//x = (R + r * cos) * sin
	//	y = r * sin
	//	z = (R + r * cos) * cos
	int t = 0; //indeksi za polje koordinata, temena i normala
	int n = 0;
	int k = 0;

	double x, y, z;
	double u, v;
	double length;

	for (int i = 0; i < 16; i++)
	{
		for (int j = 0; j < 16; j++)
		{
			x = (R + r*cos((double)j * (360.0 / 16.0)))*sin((double)j * (360.0 / 16.0));
			y = r*sin((double)j * (360.0 / 16.0));
			z = (R + r*cos((double)j * (360.0 / 16.0)))*cos((double)j * (360.0 / 16.0));

			ThorusKoord[k] = x;
			k++;
			ThorusKoord[k] = y;
			k++;
			ThorusKoord[k] = z;
			k++;

			u += (double)i*(1.0 / 16.0);
			v += (double)j*(1.0 / 16.0);

			ThorusTex[t] = u;
			t++;
			ThorusTex[t] = v;
			t++;
			
			length = sqrt(x*x + y*y + z*z);

			ThorusNorm[n] = x / length;
			n++;
			ThorusNorm[n] = y / length;
			n++;
			ThorusNorm[n] = z / length;
			n++;
		}
	}


}

void CGLRenderer::SetThorusMat()
{
}

void CGLRenderer::RotateThorus(double L)
{
}

void CGLRenderer::drawTorus2(double r, double c, int rSeg, int cSeg, int texture)
{
	glFrontFace(GL_CW);

	glBindTexture(GL_TEXTURE_2D, texture);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

	const double PI = 3.1415926535897932384626433832795;
	const double TAU = 2 * PI;

	for (int i = 0; i < rSeg; i++) {
		glBegin(GL_QUAD_STRIP);
		for (int j = 0; j <= cSeg; j++) {
			for (int k = 0; k <= 1; k++) {
				double s = (i + k) % rSeg + 0.5;
				double t = j % (cSeg + 1);

				double x = (c + r * cos(s * TAU / rSeg)) * cos(t * TAU / cSeg);
				double y = (c + r * cos(s * TAU / rSeg)) * sin(t * TAU / cSeg);
				double z = r * sin(s * TAU / rSeg);

				double u = (i + k) / (float)rSeg;
				double v = t / (float)cSeg;

				glTexCoord2d(u, v);
				glNormal3f(2 * x, 2 * y, 2 * z);
				glVertex3d(2 * x, 2 * y, 2 * z);
			}
		}
		glEnd();
	}

	glFrontFace(GL_CCW);
}

void CGLRenderer::DrawPatch(double R, double LonMin, double LatMin, double LonMax, double LatMax, double dLon, double dLat)
{
	double y = LatMax;
	int n = LatMax / dLat;

	for (int i = 0; i < n; i++)
	{
		glBegin(GL_TRIANGLE_STRIP);
		double x = LonMin;

		for (int j = 0; j < n + 1; j++)
		{
			double phi, theta;
			phi = atan(x);
			theta = atan(y * cos(phi));

			double xd, yd, zd;
			xd = R * cos(theta) * sin(phi);
			yd = R * sin(theta);
			zd = R * cos(theta) * cos(phi);

			glNormal3f(xd / R, yd / R, zd / R);
			glTexCoord2f((x + 1.0) / 2.0, (-y + 1.0) / 2.0);
			glVertex3f(xd, yd, zd);

			phi = atan(x);
			theta = atan((y-dLat) * cos(phi));

			xd = R * cos(theta) * sin(phi);
			yd = R * sin(theta);
			zd = R * cos(theta) * cos(phi);

			glNormal3f(xd / R, yd / R, zd / R);
			glTexCoord2f((x + 1.0) / 2.0,(-y + dLat + 1.0) / 2.0);
			glVertex3f(xd, yd, zd);
			x += dLon;

		}
		glEnd();
		y -= dLat;
	}

}

void CGLRenderer::DrawGlobe(double r)
{
	glPushMatrix();
	for (int i = 0; i < 4; i++)
	{
		DrawPatch(r, -45.0,-45.0,45.0,45.0,5.0,5.0);
		glRotated(90, 0.0, 1.0, 0.0);
	}
	glPopMatrix();
	glPushMatrix();
	glRotated(-90, 1.0, 0.0, 0.0);
	DrawPatch(r, -45.0, -45.0, 45.0, 45.0, 5.0, 5.0);
	glPopMatrix();
	glPushMatrix();
	glRotated(90, 1.0, 0.0, 0.0);
	DrawPatch(r, -45.0, -45.0, 45.0, 45.0, 5.0, 5.0);
	glPopMatrix();
}

