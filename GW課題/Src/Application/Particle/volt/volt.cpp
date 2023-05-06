#include "volt.h"

void C_PVolt::Init()
{
	m_size = (rand() % 2+2)*0.1;
	m_data.m_move = { rand() % 4 - 2.0f,rand() % 4 - 2.0f ,0 };
}

void C_PVolt::Update()
{
	m_data.m_alpha -= 0.008;
	if (m_data.m_alpha <= 0)
	{
		m_bAlive = false;
	}
}

void C_PVolt::Draw()
{
	if (!m_bAlive)return;
	SHADER.m_spriteShader.SetMatrix(m_data.m_mat);
	Math::Rectangle srcRect = { 0,0,(long)m_data.SIZE.x,(long)m_data.SIZE.x };
	SHADER.m_spriteShader.DrawTex(m_data.m_pTex, 0, 0, m_data.SIZE.x, m_data.SIZE.y, &srcRect, &m_color);
}
