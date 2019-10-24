#include "StdAfx.h"
#include "GLRenderer.h"
#include "GL\gl.h"
#include "GL\glu.h"
#include "GL\glaux.h"
#include "GL\glut.h"
//#pragma comment(lib, "GL\\glut32.lib")

CGLRenderer::CGLRenderer(void)
{
	ugaoDesno = 0.0;
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
	
	glClearColor(0.9019, 0.9019, 0.9803, 1.0);
	glEnable(GL_DEPTH_TEST);
	glCullFace(GL_BACK);
	glEnable(GL_CULL_FACE);

	e1 = LoadTexture(CString("Eiffel-1a.bmp"));
	e2 = LoadTexture(CString("Eiffel-2a.bmp"));
	e3 = LoadTexture(CString("Eiffel-3a.bmp"));
	e4 = LoadTexture(CString("Eiffel-4a.BMP"));
	glEnable(GL_TEXTURE_2D);

	FillVA(donjiDeoKoordinate, 4.0, 2.4, 1.5);
	FillVA(srednjiDeoKoordinate, 2.4, 1.2, 1.5);
	FillVA(gornjiDeoKoordinate, 1.08, 0.08, 8.0);
	FillVA(terasaKoordinate, 2.4, 2.64, 0.25);

	FillVATex(donjiDeoTex, 0.215, 0.0);
	FillVATex(srednjiDeoTex, 0.215, 0.0);
	FillVATex(gornjiDeoTex, 0.45, 0.05);
	FillVATex(terasaTex, 0.0, 0.0);

	FillVANorm(donjiDeoNorm, 4.0, 2.4, 1.5);
	FillVANorm(srednjiDeoNorm, 2.4, 1.2, 1.5);
	FillVANorm(gornjiDeoNorm, 1.08, 0.08, 8.0);
	FillVANorm(terasaNorm, 2.4, 2.64, 0.25);

	//---------------------------------
	wglMakeCurrent(NULL, NULL);
}

void CGLRenderer::DrawScene(CDC *pDC)
{
	wglMakeCurrent(pDC->m_hDC, m_hrc);
	//---------------------------------
	
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();

	gluLookAt(13.0, 5.0, 13.0, 0.0, 6.0, 0.0, 0.0, 1.0, 0.0);

	/*glLineWidth(2.0);
	glPointSize(10);
	glBegin(GL_TRIANGLES);
	glColor3f(1.0, 0.0, 0.0);
	glVertex2f(2.0, 1.0);
	glVertex2f(2.0, 0.0);
	glVertex2f(1.0, 1.0);
	glEnd();*/

	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	float light_ambient[] = { 0.1, 0.1, 0.1, 1.0 };
	float light_diffuse[] = { 1.0, 1.0, 1.0, 1.0 };
	float light_specular[] = { 1.0, 1.0, 1.0, 1.0 };
	glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
	glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
	GLfloat light_position[] = { 10.0, 15.0, 10.0, 0.0 };

	glLightfv(GL_LIGHT0, GL_POSITION, light_position);

	glEnable(GL_NORMALIZE);
	
	glBindTexture(GL_TEXTURE_2D, e1);
	glVertexPointer(3, GL_FLOAT, 0, donjiDeoKoordinate);
	glTexCoordPointer(2, GL_FLOAT, 0, donjiDeoTex);
	glNormalPointer(GL_FLOAT, 0, donjiDeoNorm);

	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	glEnableClientState(GL_NORMAL_ARRAY);
	
	int ind[24];
	ind[0] = 0; ind[1] = 1; ind[2] = 2; ind[3] = 3;
	ind[4] = 3; ind[5] = 2; ind[6] = 5; ind[7] = 4;
	ind[8] = 4; ind[9] = 5; ind[10] = 6; ind[11] = 7;
	ind[12] = 7; ind[13] = 6; ind[14] = 1; ind[15] = 0;
	ind[16] = 7; ind[17] = 0; ind[18] = 3; ind[19] = 4;
	ind[20] = 6; ind[21] = 1; ind[22] = 2; ind[23] = 5;

	glPushMatrix();

	glRotatef(ugaoDesno, 0.0, 1.0, 0.0);
	//donji deo
	glDrawElements(GL_QUADS, 24, GL_UNSIGNED_INT, ind);

	//terasa
	glBindTexture(GL_TEXTURE_2D, e4);
	glVertexPointer(3, GL_FLOAT, 0, terasaKoordinate);
	glTexCoordPointer(2, GL_FLOAT, 0, terasaTex);
	glNormalPointer(GL_FLOAT, 0, terasaNorm);

	glTranslatef(0.0, 1.5, 0.0);

	glDrawElements(GL_QUADS, 24, GL_UNSIGNED_INT, ind);

	//srednji deo
	glBindTexture(GL_TEXTURE_2D, e2);
	glVertexPointer(3, GL_FLOAT, 0, srednjiDeoKoordinate);
	glTexCoordPointer(2, GL_FLOAT, 0, srednjiDeoTex);
	glNormalPointer(GL_FLOAT, 0, srednjiDeoNorm);

	glTranslatef(0.0, 0.25, 0.0);

	glDrawElements(GL_QUADS, 24, GL_UNSIGNED_INT, ind);

	//terasa 2
	glBindTexture(GL_TEXTURE_2D, e4);
	glVertexPointer(3, GL_FLOAT, 0, terasaKoordinate);
	glTexCoordPointer(2, GL_FLOAT, 0, terasaTex);
	glNormalPointer(GL_FLOAT, 0, terasaNorm);

	glTranslatef(0.0, 1.5, 0.0);

	glPushMatrix();

	glScalef(0.5, 1.0, 0.5);
	glDrawElements(GL_QUADS, 24, GL_UNSIGNED_INT, ind);
	glPopMatrix();

	//gornj deo

	glBindTexture(GL_TEXTURE_2D, e3);
	glVertexPointer(3, GL_FLOAT, 0, gornjiDeoKoordinate);
	glTexCoordPointer(2, GL_FLOAT, 0, gornjiDeoTex);
	glNormalPointer(GL_FLOAT, 0, gornjiDeoNorm);

	glTranslatef(0.0, 0.25, 0.0);

	glDrawElements(GL_QUADS, 24, GL_UNSIGNED_INT, ind);

	glPopMatrix();

	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);
	glDisableClientState(GL_NORMAL_ARRAY);
	
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
	glDeleteTextures(1, &e1);
	glDeleteTextures(1, &e2);
	glDeleteTextures(1, &e3);
	glDeleteTextures(1, &e4);

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

void CGLRenderer::FillVA(float * buff, float a, float b, float h)
{
	//prednja strana
	//x                          //y                     //z
	//buff[0] = -b / (float)2;   buff[1] = h;          buff[2] = (b / (float)2) / tanf((float)45 * toRad);
	//buff[3] = -a / (float)2;   buff[4] = (float)0;   buff[5] = (a / (float)2) / tanf((float)45 * toRad);
	//buff[6] = a / (float)2;    buff[7] = (float)0;   buff[8] = (a / (float)2) / tanf((float)45 * toRad);
	//buff[9] = b / (float)2;    buff[10] = h;         buff[11] = (b / (float)2) / tanf((float)45 * toRad);

	////desna strana
	//buff[12] = b / (float)2;  buff[13] = h;         buff[14] = (b / (float)2) / tanf((float)45 * toRad);
	//buff[15] = a / (float)2;  buff[16] = (float)0;  buff[17] = (a / (float)2) / tanf((float)45 * toRad);
	//buff[18] = a / (float)2;  buff[19] = (float)0;  buff[20] = -(a / (float)2) / tanf((float)45 * toRad);
	//buff[21] = b / (float)2;  buff[22] = h;         buff[23] = -(b / (float)2) / tanf((float)45 * toRad);

	////zadnja strana
	//buff[24] = b / (float)2;  buff[25] = h;         buff[26] = -(b / (float)2) / tanf((float)45 * toRad);
	//buff[27] = a / (float)2;  buff[28] = (float)0;  buff[29] = -(a / (float)2) / tanf((float)45 * toRad);
	//buff[30] = -a / (float)2; buff[31] = (float)0;  buff[32] = -(a / (float)2) / tanf((float)45 * toRad);
	//buff[33] = -b / (float)2; buff[34] = h;         buff[35] = -(b / (float)2) / tanf((float)45 * toRad);

	////leva strana
	//buff[36] = -b / (float)2; buff[37] = h;         buff[38] = -(b / (float)2) / tanf((float)45 * toRad);
	//buff[39] = -a / (float)2; buff[40] = (float)0;  buff[41] = -(a / (float)2) / tanf((float)45 * toRad);
	//buff[42] = a / (float)2;  buff[43] = (float)0;  buff[44] = (a / (float)2) / tanf((float)45 * toRad);
	//buff[45] = b / (float)2;  buff[46] = h;         buff[47] = (b / (float)2) / tanf((float)45 * toRad);

	////gornja strana
	//buff[48] = -b / (float)2; buff[49] = h;         buff[50] = -(b / (float)2) / tanf((float)45 * toRad);
	//buff[51] = -b / (float)2; buff[52] = h;         buff[53] = (b / (float)2) / tanf((float)45 * toRad);
	//buff[54] = b / (float)2;  buff[55] = h;			buff[56] = (b / (float)2) / tanf((float)45 * toRad);
	//buff[57] = b / (float)2;  buff[58] = h;         buff[59] = -(b / (float)2) / tanf((float)45 * toRad);

	////donja strana
	//buff[60] = -a / (float)2; buff[61] = (float)0;  buff[62] = -(a / (float)2) / tanf((float)45 * toRad);
	//buff[63] = -a / (float)2; buff[64] = (float)0;  buff[65] = (a / (float)2) / tanf((float)45 * toRad);
	//buff[66] = a / (float)2;  buff[67] = (float)0;	buff[68] = (a / (float)2) / tanf((float)45 * toRad);
	//buff[69] = a / (float)2;  buff[70] = (float)0;  buff[71] = -(a / (float)2) / tanf((float)45 * toRad);

	///////////
	//tan(45) = 1

	buff[0] = -(b /2);   buff[1] = h;   buff[2] = (b / 2); //vert 1
	buff[3] = -(a /2);   buff[4] = 0;   buff[5] = (a / 2); //vert 2
	buff[6] = a / 2;     buff[7] = 0;   buff[8] = (a / 2); //vert 3
	buff[9] = b / 2;     buff[10] = h;  buff[11] = (b / 2); //vert 4

	
	buff[12] = b / 2;    buff[13] = h;  buff[14] = -(b / 2); //vert 5
	buff[15] = a / 2;    buff[16] = 0;  buff[17] = -(a / 2); //vert 6
	buff[18] = -(a / 2); buff[19] = 0;  buff[20] = -(a / 2);//vert 7
	buff[21] = -(b / 2); buff[22] = h;  buff[23] = -(b / 2);//vert 8

}

void CGLRenderer::FillVANorm(float * buff, float a, float b, float h)
{
	//prednja strana
	//x                          //y                     //z
	buff[0] = 0;   buff[1] = 0;   buff[2] = 1;
	buff[3] = 0;   buff[4] = 0;   buff[5] = 1;
	buff[6] = 0;   buff[7] = 0;   buff[8] = 1;
	buff[9] = 0;   buff[10] = 0;  buff[11] = 1;

	//desna strana
	buff[12] = 1;  buff[13] = 0;  buff[14] = 0;
	buff[15] = 1;  buff[16] = 0;  buff[17] = 0;
	buff[18] = 1;  buff[19] = 0;  buff[20] = 0;
	buff[21] = 1;  buff[22] = 0;  buff[23] = 0;

	//zadnja strana
	buff[24] = 0;  buff[25] = 0;  buff[26] = -1;
	buff[27] = 0;  buff[28] = 0;  buff[29] = -1;
	buff[30] = 0;  buff[31] = 0;  buff[32] = -1;
	buff[33] = 0;  buff[34] = 0;  buff[35] = -1;

	//leva strana
	buff[36] = -1;  buff[37] = 0;  buff[38] = 0;
	buff[39] = -1;  buff[40] = 0;  buff[41] = 0;
	buff[42] = -1;  buff[43] = 0;  buff[44] = 0;
	buff[45] = -1;  buff[46] = 0;  buff[47] = 0;

	//gornja strana
	buff[48] = 0; buff[49] = 1;         buff[50] = 0;
	buff[51] = 0; buff[52] = 1;         buff[53] = 0;
	buff[54] = 0; buff[55] = 1;			buff[56] = 0;
	buff[57] = 0; buff[58] = 1;         buff[59] = 0;

	//donja strana
	buff[60] = 0;  buff[61] = -1;  buff[62] = 0;
	buff[63] = 0;  buff[64] = -1;  buff[65] = 0;
	buff[66] = 0;  buff[67] = -1;  buff[68] = 0;
	buff[69] = 0;  buff[70] = -1;  buff[71] = 0;

}

void CGLRenderer::FillVATex(float * buff, float x1, float x2)
{ 
	buff[0] = 0 + x1;			   buff[1] = 0;
	buff[2] = 0 + x2;			   buff[3] = 1;
	buff[4] = 1 - x2;			   buff[5] = 1;
	buff[6] = 1 - x1;              buff[7] = 0;

	buff[8] = 0 + x1;			   buff[9] = 0;
	buff[10] = 0 + x2;			   buff[11] = 1;
	buff[12] = 1 - x2;			   buff[13] = 1;
	buff[14] = 1 - x1;             buff[15] = 0;

	buff[16] = 0 + x1;			   buff[17] = 0;
	buff[18] = 0 + x2;			   buff[19] = 1;
	buff[20] = 1 - x2;			   buff[21] = 1;
	buff[22] = 1 - x1;             buff[23] = 0;

	buff[24] = 0 + x1;			   buff[25] = 0;
	buff[26] = 0 + x2;			   buff[27] = 1;
	buff[28] = 1 - x2;			   buff[29] = 1;
	buff[30] = 1 - x1;             buff[31] = 0;
}
