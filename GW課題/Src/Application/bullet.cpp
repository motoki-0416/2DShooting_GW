#include "bullet.h"

C_Bullet::C_Bullet()
{
	m_bAlive = true;
}

C_Bullet::~C_Bullet()
{

}

void C_Bullet::Init()
{
}


void C_Bullet::Update()
{
	if(m_bAlive)m_bAlive = IsScreenOut();
	
	//ˆÚ“®—Ê
	m_data.m_pos += m_data.m_move;
	m_data.m_mat = Math::Matrix::CreateTranslation(m_data.m_pos);
}

void C_Bullet::Draw()
{
	if (!m_bAlive)return;
	SHADER.m_spriteShader.SetMatrix(m_data.m_mat);
    SHADER.m_spriteShader.DrawTex(m_data.m_pTex, Math::Rectangle(0, 0, m_data.SIZE.x, m_data.SIZE.y), 1.0f);
}

const bool C_Bullet::IsScreenOut()
{
	if (m_data.m_pos.x<-388
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

/*for (int h = 0; h < m_bullet.size(); h++)
			{
				m_bullet[h].m_speed = 10;
				m_bullet[h].m_moveX = cos(DirectX::XMConvertToRadians(deg)) * m_bullet[h].m_speed;
				m_bullet[h].m_moveY = sin(DirectX::XMConvertToRadians(deg)) * m_bullet[h].m_speed;

				shotCount = COUNT_NUM;
			}*/

