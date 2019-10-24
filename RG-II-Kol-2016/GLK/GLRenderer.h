#pragma once
#include "DImage.h"

class CGLRenderer
{
public:
	CGLRenderer(void);
	virtual ~CGLRenderer(void);
		
	bool CreateGLContext(CDC* pDC);			// kreira OpenGL Rendering Context
	void PrepareScene(CDC* pDC);			// inicijalizuje scenu,
	void Reshape(CDC* pDC, int w, int h);	// kod koji treba da se izvrsi svaki put kada se promeni velicina prozora ili pogleda i
	void DrawScene(CDC* pDC);				// iscrtava scenu
	void DestroyScene(CDC* pDC);			// dealocira resurse alocirane u drugim funkcijama ove klase,

	UINT CGLRenderer::LoadTexture(char* fileName);
	void CGLRenderer::DrawCube(double a);
	void CGLRenderer::DrawTube(double r1, double r2, double h, int n);
	void CGLRenderer::DrawCone(double r, double h, int n);
	void CGLRenderer::DrawPaddle(double length, double width);

	// izracunavanje normale
	double* calculate(double *a, double *b, double *c);
	double* cross_product(double *v1, double *v2);
	void normalize(double *v);

protected:
	HGLRC	 m_hrc; //OpenGL Rendering Context 

public:
	UINT brick;
	UINT env;

	double pi = 3.1415926535897932384626433832795;
	double toRad = pi / 180;

	double ugaoVetrenjace;
	double ugaoLevo;
	double ugaoGore;

};
