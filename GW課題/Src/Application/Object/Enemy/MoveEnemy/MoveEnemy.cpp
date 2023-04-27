#include "Application/Object/BaseObject.h"
#include "MoveEnemy.h"
#include "Application/bullet.h"
#include "Application/Particle/P_Bom.h"

void C_MoveEnemy::Init()
{
	m_size = 1.5;
	m_scaleMat = Math::Matrix::CreateScale(m_size);
	m_data.m_move = { 0,-1,0 };
}

void C_MoveEnemy::Update()
{

	//“®‚«
	Move();

	//¶‚«‚Ä‚¢‚ê‚Î
	if (m_bAlive)
	{
		//ƒ‰ƒ“ƒ_ƒ€‚Å‹…‚ğì‚é
		if (rand() % 60 <= 0)
		{
			MakeBullet();
		}
		m_data.m_pos += m_data.m_move;
		m_transMat = Math::Matrix::CreateTranslation(m_data.m_pos);
		
		m_data.m_mat = m_scaleMat * m_transMat;
	}

	//‹…‚Ìˆ—
	for (int i = 0; i < m_bullet.size(); i++)
	{
		m_bullet[i]->Update();
	}
	for (int i = 0; i < m_particle.size(); i++)
	{
		m_particle[i]->Update();
	}
	//‰æ–ÊŠOÁ‹
	if (m_data.m_pos.y < -HALF_HEIGHT - m_data.HALF_SIZE.y)
	{
		m_bAlive = false;
	}

	//‹…‚Ìíœ
	DeleteManager();
}


void C_MoveEnemy::Move()
{
	ang += 1.5;

	if (ang >= 360)
	{
		ang -= 360;
	}

	m_data.m_move.x=sin(DirectX::XMConvertToRadians(ang)) * 1.5;
}

void C_MoveEnemy::MakeBullet()
{
	shared_ptr<C_Bullet> tmpA = make_shared<C_Bullet>();
	tmpA->Init();
	tmpA->SetPos({ m_data.m_pos.x,m_data.m_pos.y,m_data.m_pos.z });//À•W
	tmpA->SetMove({ (float)((rand() % 31 - 15) * 0.1),BULLET_MOVE_Y,0 });//ˆÚ“®—Ê
	tmpA->SetTex(m_pBulletTex);	//‰æ‘œ
	m_bullet.push_back(tmpA);
}