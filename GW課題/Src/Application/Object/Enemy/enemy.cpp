#include "enemy.h"
#include "Application/Scene.h"
#include "Application/bullet.h"
#include "Application/Particle/P_Bom.h"

void C_Enemy::Init()
{
	m_size = 1.5;
	m_scaleMat = Math::Matrix::CreateScale(m_size);

}

void C_Enemy::Update()
{


	//�����Ă����
	if (m_bAlive)
	{
		//�����_���ŋ������
		if (rand() % 60 <= 0)
		{
			MakeBullet();
		}
		m_data.m_pos += m_data.m_move;
		m_transMat= Math::Matrix::CreateTranslation(m_data.m_pos);
		m_data.m_mat = m_scaleMat * m_transMat;
	}

	//���̏���
	for (int i = 0; i < m_bullet.size(); i++)
	{
		m_bullet[i]->Update();
	}
	for (int i = 0; i < m_particle.size(); i++)
	{
		m_particle[i]->Update();
	}

	//��ʊO����
	if (m_data.m_pos.y < -HALF_HEIGHT - m_data.HALF_SIZE.y)
	{
		m_bAlive = false;
	}

	DeleteManager();
}

void C_Enemy::MakeBullet()
{
	shared_ptr<C_Bullet> tmpA = make_shared<C_Bullet>();
	tmpA->Init();
	tmpA->SetPos({ m_data.m_pos.x,m_data.m_pos.y,m_data.m_pos.z });//���W
	tmpA->SetMove({ (float)((rand() % 31 - 15) * 0.1),BULLET_MOVE_Y,0 });//�ړ���
	tmpA->SetTex(m_pBulletTex);	//�摜
	m_bullet.push_back(tmpA);
}
