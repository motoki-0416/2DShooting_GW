#include "Application/Object/BaseObject.h"
#include "widthEnemy.h"
#include "Application/Object/Bullet/bullet.h"
#include "Application/Particle/P_Bom.h"

void C_WidthEnemy::Init()
{
	m_hp = 2;
	m_data.SIZE = { 48,48,0 };
	m_data.HALF_SIZE = m_data.SIZE / 2;;

	if (m_data.m_pos.x > 0)
	{
		m_data.m_move = { -1,0,0 };
	}
	else
	{
		m_data.m_move = { 1,0,0 };
	}

	ang = 0;

}

void C_WidthEnemy::Update()
{

	if (damageDelay > 0)damageDelay--;	//ダメージを食らっていたら

	//生きていれば
	if (m_bAlive)
	{
		//ランダムで球を作る
		if (rand() % 60 <= 0)MakeBullet();

		Move();
	}

	//球の処理
	for (int i = 0; i < m_bullet.size(); i++)
	{
		m_bullet[i]->Update();
	}
	for (int i = 0; i < m_particle.size(); i++)
	{
		m_particle[i]->Update();
	}
	//画面外消去
	if (m_data.m_pos.y < -HALF_HEIGHT - m_data.HALF_SIZE.y)
	{
		m_bAlive = false;
	}

	//球の削除
	DeleteManager();
}

void C_WidthEnemy::CommitPos(Math::Vector3 a_move)
{

	m_data.m_pos += (m_data.m_move + a_move);
	m_scaleMat = Math::Matrix::CreateScale(m_size);
	m_transMat = Math::Matrix::CreateTranslation(m_data.m_pos);
	m_data.m_mat = m_scaleMat * m_transMat;

	for (int i = 0; i < m_bullet.size(); i++)
	{
		m_bullet[i]->CommitPos(a_move);
	}


	for (int i = 0; i < m_particle.size(); i++)
	{
		m_particle[i]->CommitPos(a_move);
	}

}


void C_WidthEnemy::MakeBullet()
{
	shared_ptr<C_Bullet> tmpA = make_shared<C_Bullet>();
	tmpA->Init();
	tmpA->SetPos({ m_data.m_pos.x,m_data.m_pos.y,m_data.m_pos.z });//座標
	tmpA->SetMove({ (float)((rand() % 31 - 15) * 0.1),BULLET_MOVE_Y,0 });//移動量
	tmpA->SetTex(m_pBulletTex);	//画像
	m_bullet.push_back(tmpA);
}

void C_WidthEnemy::Move()
{

	ang += 3;
	if (ang >= 360)ang -= 360;
	m_data.m_move.y = cos(DirectX::XMConvertToRadians(ang)) *0.8;

}
