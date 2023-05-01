#include "Homing.h"

void C_Homing::Init()
{
	m_deg = 0;
	homingDelay = 40;
}

void C_Homing::Update()
{

	if (m_bAlive)m_bAlive = IsScreenOut();
	
	if (homingDelay-- < 0)
	{

		m_data.m_move = { cos(DirectX::XMConvertToRadians(m_deg))*-10.0f,sin(DirectX::XMConvertToRadians(m_deg))*-10.0f,0 };

	}

	m_data.m_pos += m_data.m_move;
	m_scaleMat = Math::Matrix::CreateScale(m_size);
	m_data.m_mat = m_scaleMat * Math::Matrix::CreateTranslation(m_data.m_pos);

}


void C_Homing::SetPlayerPos(Math::Vector3 a_pos)
{
	Math::Vector3 dist;


	dist = m_data.m_pos - a_pos;


	m_deg = DirectX::XMConvertToDegrees(atan2(dist.y, dist.x));


	if (m_deg < 0)
	{

		m_deg += 360;

	}
}
