#include "BaseBullet.h"

C_BaseBullet::C_BaseBullet()
{
	m_size = 1;
	srcFlg = true;
	m_bAlive = true;
}

void C_BaseBullet::Init()
{
}

void C_BaseBullet::Update()
{
	if (m_bAlive)m_bAlive = IsScreenOut();
}

void C_BaseBullet::Draw()
{
	if (!m_bAlive)return;
	SHADER.m_spriteShader.SetMatrix(m_data.m_mat);
	SHADER.m_spriteShader.DrawTex(m_data.m_pTex, Math::Rectangle(m_data.SIZE.x*srcFlg, 0, m_data.SIZE.x, m_data.SIZE.y), m_data.m_alpha);
}

void C_BaseBullet::SetAlpha(float i)
{
	m_data.m_alpha -= i;

	if (m_data.m_alpha <= 0.0f)
	{

		m_bAlive = false;

	}
}

void C_BaseBullet::CommitPos(Math::Vector3 a_move)
{
	m_data.m_pos += m_data.m_move+a_move;
	m_scaleMat = Math::Matrix::CreateScale(m_size);
	m_data.m_mat = m_scaleMat * Math::Matrix::CreateTranslation(m_data.m_pos);
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