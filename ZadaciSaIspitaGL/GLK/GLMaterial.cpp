#include "stdafx.h"
#include "GLMaterial.h"
#include <gl\GL.h>

#pragma region LAB5

CGLMaterial::CGLMaterial()
{
	m_vAmbient[0] = 0.2f;
	m_vAmbient[1] = 0.2f;
	m_vAmbient[2] = 0.2f;
	m_vAmbient[3] = 1.0f;

	m_vDiffuse[0] = 0.8f;
	m_vDiffuse[1] = 0.8f;
	m_vDiffuse[2] = 0.8f;
	m_vDiffuse[3] = 1.0f;

	m_vSpecular[0] = 1.0f;
	m_vSpecular[1] = 1.0f;
	m_vSpecular[2] = 1.0f;
	m_vSpecular[3] = 1.0f;

	m_vEmission[0] = 0.0f;
	m_vEmission[1] = 0.0f;
	m_vEmission[2] = 0.0f;
	m_vEmission[3] = 1.0f;

	m_fShininess = 64.0f;
}

CGLMaterial::~CGLMaterial()
{
}

void CGLMaterial::Select()
{
	glMaterialfv(GL_FRONT, GL_AMBIENT, m_vAmbient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, m_vDiffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, m_vSpecular);
	glMaterialfv(GL_FRONT, GL_EMISSION, m_vEmission);
	glMaterialf(GL_FRONT, GL_SHININESS, m_fShininess);
}

void CGLMaterial::SetAmbient(float r, float g, float b, float a)
{
	m_vAmbient[0] = r;
	m_vAmbient[1] = g;
	m_vAmbient[2] = b;
	m_vAmbient[3] = a;
}

void CGLMaterial::SetDiffuse(float r, float g, float b, float a)
{
	m_vDiffuse[0] = r;
	m_vDiffuse[1] = g;
	m_vDiffuse[2] = b;
	m_vDiffuse[3] = a;
}

void CGLMaterial::SetSpecular(float r, float g, float b, float a)
{
	m_vSpecular[0] = r;
	m_vSpecular[1] = g;
	m_vSpecular[2] = b;
	m_vSpecular[3] = a;
}

void CGLMaterial::SetEmission(float r, float g, float b, float a)
{
	m_vEmission[0] = r;
	m_vEmission[1] = g;
	m_vEmission[2] = b;
	m_vEmission[3] = a;
}

void CGLMaterial::SetShininess(float s)
{
	if (s < 0.0f)
		m_fShininess = 0.0;
	else if (s > 128.0f)
		m_fShininess = 128.0f;
	else
		m_fShininess = s;
}

#pragma endregion
