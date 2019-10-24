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

	UINT LoadTexture(CString fileName);
	void FillVA(float* buff, float a, float b, float h);
	void FillVANorm(float* buff, float a, float b, float h);
	void FillVATex(float* buff, float x1, float x2);

protected:
	HGLRC	 m_hrc; //OpenGL Rendering 

public:
	UINT e1, e2, e3, e4;

	float ugaoDesno;

	float pi = 3.1415926/*535897932384626433832795*/;
	float toRad = pi / 180;

	float donjiDeoKoordinate[24];
	float donjiDeoTex[32];
	float donjiDeoNorm[72];

	float srednjiDeoKoordinate[24];
	float srednjiDeoTex[32];
	float srednjiDeoNorm[72];

	float gornjiDeoKoordinate[24];
	float gornjiDeoTex[32];
	float gornjiDeoNorm[72];

	float terasaKoordinate[24];
	float terasaTex[32];
	float terasaNorm[72];
};
