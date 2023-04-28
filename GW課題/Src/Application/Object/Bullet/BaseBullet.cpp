#include "BaseBullet.h"

C_BaseBullet::C_BaseBullet()
{
	m_size = 1;
	m_bAlive = true;
}

void C_BaseBullet::Init()
{
}

void C_BaseBullet::Update()
{
	if (m_bAlive)m_bAlive = IsScreenOut();
	//ˆÚ“®—Ê
	m_data.m_pos += m_data.m_move;
	m_scaleMat = Math::Matrix::CreateScale(m_size);
	m_data.m_mat = m_scaleMat*Math::Matrix::CreateTranslation(m_data.m_pos);
}

void C_BaseBullet::Draw()
{
	if (!m_bAlive)return;
	SHADER.m_spriteShader.SetMatrix(m_data.m_mat);
	SHADER.m_spriteShader.DrawTex(m_data.m_pTex, Math::Rectangle(0, 0, m_data.SIZE.x, m_data.SIZE.y), 1.0f);
}

const bool C_BaseBullet::IsScreenOut()
{
	if (m_data.m_pos.x < -388
		|| m_data.m_pos.x>388
		|| m_data.m_pos.y<-HALF_HEIGHT
		|| m_data.m_pos.y>HALF_HEIGHT)
	{
		return false;
	}
	else
	{
		return true;
	}
}