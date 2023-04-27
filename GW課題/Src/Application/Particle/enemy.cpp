#include "enemy.h"


C_Enemy::C_Enemy()
{
	m_radius = 32;
	m_bAlive = true;
}

C_Enemy::~C_Enemy()
{
}

void C_Enemy::Init()
{
	
}

void C_Enemy::Update()
{
	if (m_bAlive)
	{
		m_data.m_pos.x += m_data.m_move.x;

		if (m_data.m_pos.x > Screen::HALF_WIDTH-m_radius || m_data.m_pos.x < -Screen::HALF_WIDTH-m_radius)
		{
			m_data.m_move.x *= -1;
		}

		m_data.m_mat = DirectX::XMMatrixTranslation(m_data.m_pos.x, m_data.m_pos.y, 0);
	}
}

void C_Enemy::Draw2D()
{
	if (m_bAlive)
	{
		SHADER.m_spriteShader.SetMatrix(m_data.m_mat);
		SHADER.m_spriteShader.DrawTex(m_data.m_pTex, Math::Rectangle(0, 0, 64, 64), 1.0f);
	}
}

void C_Enemy::SetTex(KdTexture* a_pTex)
{
	m_data.m_pTex = a_pTex;
}

void C_Enemy::Hit()
{
	m_bAlive = false;
}

const Math::Vector2 C_Enemy::GetPos()
{
	return m_data.m_pos;
}

const float C_Enemy::GetRadius()
{
	return m_radius;
}

const bool C_Enemy::GetAlive()
{
	return m_bAlive;
}
