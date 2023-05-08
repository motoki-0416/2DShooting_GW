#include "Back.h"
#include "Application/Event/Start/Event_Start.h"
#include "Application/Scene.h"

void C_Back::Init()
{
	plusPosY = 0;
	m_back.m_pos = { 0,m_back.HALF_SIZE.y-HALF_HEIGHT,0 };
	m_scalMat = Math::Matrix::CreateScale({1.1,1,1 });
	m_transMat = Math::Matrix::CreateTranslation(m_back.m_pos);
	m_back.m_mat = m_scalMat * m_transMat;

	stopFlg = false;
}

void C_Back::Update()
{
	if (stopFlg)return;
	m_back.m_move.x = 0;

	if (GetAsyncKeyState(VK_LEFT) & 0x8000)
	{
		m_back.m_move.x = 1;
		if (m_back.m_pos.x >= 20)
		{
			m_back.m_move.x = 0;
			m_back.m_pos.x = 20;
		}
	}
	else if (GetAsyncKeyState(VK_RIGHT) & 0x8000)
	{
		m_back.m_move.x = -1;
		if (m_back.m_pos.x <=-20)
		{
			m_back.m_move.x = 0;
			m_back.m_pos.x = -20;
		}
	}
	
	m_back.m_pos += m_back.m_move;
	plusPosY += m_back.m_move.y;

	if (m_back.m_pos.y <-m_back.HALF_SIZE.y + HALF_HEIGHT)
	{
		m_back.m_move = {};
		m_back.m_pos.y = -m_back.HALF_SIZE.y + HALF_HEIGHT;
	}

	m_transMat= Math::Matrix::CreateTranslation(m_back.m_pos);
		
	m_back.m_mat = m_scalMat * m_transMat;
}

void C_Back::Draw()
{
	SHADER.m_spriteShader.SetMatrix(m_back.m_mat);
	SHADER.m_spriteShader.DrawTex(m_back.m_pTex, Math::Rectangle(0, 0, m_back.SIZE.x, m_back.SIZE.y), m_back.m_alpha);	
}

void C_Back::SetTex(Scene* a_pOwner)
{
	m_back.m_pTex =&a_pOwner->GetTex()->backTex;
	
}
