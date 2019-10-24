#pragma once

#include "DImage.h"
#include "GLMaterial.h"

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

	UINT LoadTexture(CString fileName);

	//// 07.07.2014
	void DrawRoller(float r, float h, int n);
	void DrawFigure(float h, float dx, float alpha, float beta, float dt, CString strTex);

	////// 06.10.2015
	void Spherify(double x, double y, double z, double& phi, double& theta, double &R);
	void Extrude(double& x, double& y, double& z, double R);
	void DrawSide(double x1, double y1, double z1, double x2, double y2, double z2, double x3, double y3, double z3, int level, int maxLevel);
	void DrawTetrahedron(int maxLevel);

	////18.09.2017
	void DrawThorus(double R, double r);
	void SetThorusMat();
	void RotateThorus(double L);

	void drawTorus2(double r, double c, int rSeg, int cSeg, int texture);

	//// 5.10.2011
	void DrawPatch(double r, double LonMin, double LatMin, double LonMax, double LatMax, double dLon, double dLat);
	void DrawGlobe(double r);

protected:
	HGLRC	 m_hrc; //OpenGL Rendering Context 

public:
	float pi = 3.1415926/*535897932384626433832795*/;
	float toRad = pi / 180;

	//07.07.2014
	UINT brick;
	//uglovi rotacije stubova
	float a;
	float b;

	////// 06.10.2015
	double phi;
	double theta;
	double R;

	////18.09.2017

	//Neka torus ima 16 segmenta pravougaonika i 16 segmenta prstena ?????
	double ThorusKoord[256 * 3];
	double ThorusNorm[256 * 3];
	double ThorusTex[256 * 2];

};
