#include "Event_Start.h"
#include "Application/Scene.h"

void C_EventStart::Init()
{
	m_data.SIZE = { 500,500,0 };
	m_data.HALF_SIZE = m_data.SIZE / 2;
	m_data.m_pos = { 0,100,0 };
	delay = 100;
	m_bFlg = false;
}

void C_EventStart::Update()
{
	if (!m_bFlg)
	{
		m_data.m_alpha += 0.01;
		if (m_data.m_alpha >= MAX_ALPHA)
		{
			if (delay <= 0)
			{
				m_bFlg = true;
			}
			else
			{
				delay--;
			}
		}
	}
	else
	{
		if (m_data.m_alpha > 0)
		{
			m_data.m_alpha -= 0.01;
		}
		else
		{
			m_bDeleteFlg = true;
		}
	}
	m_data.m_mat = Math::Matrix::CreateTranslation(m_data.m_pos);
	
	
}

void C_EventStart::Draw()
{
	SHADER.m_spriteShader.SetMatrix(m_data.m_mat);
	SHADER.m_spriteShader.DrawTex(m_data.m_pTex, Math::Rectangle(0, 0, m_data.SIZE.x, m_data.SIZE.y), m_data.m_alpha);
}


void C_EventStart::SetTex(Scene* a_pOwner)
{
	m_data.m_pTex = &a_pOwner->GetTex()->eventMissionTex;
	m_pOwner = a_pOwner;
}
