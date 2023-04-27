#include "Back.h"
#include "Application/Event/Start/Event_Start.h"
#include "Application/Scene.h"

void C_Back::Init()
{
	m_back.m_pos = { 0,m_back.HALF_SIZE.y-HALF_HEIGHT,0 };
	m_scalMat = Math::Matrix::CreateScale({ 1.2,1,1 });
	m_transMat = Math::Matrix::CreateTranslation(m_back.m_pos);
	m_back.m_mat = m_scalMat * m_transMat;
}

void C_Back::Update()
{

	m_back.m_pos += m_back.m_move;
	m_transMat= Math::Matrix::CreateTranslation(m_back.m_pos);
		
	m_back.m_mat = m_scalMat * m_transMat;
}

void C_Back::Draw()
{
	SHADER.m_spriteShader.SetMatrix(m_back.m_mat);
	SHADER.m_spriteShader.DrawTex(m_back.m_pTex, Math::Rectangle(0, 0, m_back.SIZE.x, m_back.SIZE.y), 1.0f);	
}

void C_Back::SetTex(KdTexture* a_pTex)
{
	m_back.m_pTex =a_pTex;
	
}
