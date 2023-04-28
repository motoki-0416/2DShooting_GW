#include "MiniBoss.h"
#include "Application/Object/Bullet/bullet.h"
#include "Application/Particle/P_Bom.h"
#include "Application/Object/Player/Player.h"

void C_MiniBoss::Init()
{
	m_hp = MAX_HP;
	m_data.m_move = { 0,-1,0 };
	m_data.SIZE = { 64,64,0 };
	m_size = 2.0f;
	m_data.HALF_SIZE = m_data.SIZE / 2;
	m_scaleMat = Math::Matrix::CreateScale(m_size);
}

void C_MiniBoss::Update()
{
	//生きていれば
	if (m_bAlive)
	{
		//ランダムで球を作る
		if (rand() % 60 <= 0)
		{
			MakeBullet();
		}
		m_data.m_pos += m_data.m_move;
		m_transMat = Math::Matrix::CreateTranslation(m_data.m_pos);
		m_data.m_mat = m_scaleMat * m_transMat;
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

	if (m_data.m_pos.y <= 200)
	{
		m_data.m_move = { };
	}
	//球の削除
	DeleteManager();
}

void C_MiniBoss::Draw()
{
	if (m_bAlive)
	{
		SHADER.m_spriteShader.SetMatrix(m_data.m_mat);
		SHADER.m_spriteShader.DrawTex(m_data.m_pTex, Math::Rectangle{ 0,0,(long)m_data.SIZE.x,(long)m_data.SIZE.y }, 1.0f);
	}

	for (int i = 0; i < m_bullet.size(); i++)
	{
		m_bullet[i]->Draw();
	}

	for (int i = 0; i < m_particle.size(); i++)
	{
		m_particle[i]->Draw();
	}
}

void C_MiniBoss::MakeBullet()
{
	shared_ptr<C_Bullet> tmpA = make_shared<C_Bullet>();
	tmpA->Init();
	tmpA->SetPos({ m_data.m_pos.x,m_data.m_pos.y,m_data.m_pos.z });//座標
	tmpA->SetMove({ (float)((rand() % 31 - 15) * 0.1),BULLET_MOVE_Y,0 });//移動量
	tmpA->SetTex(m_pBulletTex);	//画像
	m_bullet.push_back(tmpA);
}

void C_MiniBoss::HitCheckBullet(C_Player* a_player)
{
	if (!m_bAlive)return;
	for (int i = 0; i < a_player->GetBulletSize(); i++)
	{
		if (CircleCD(*a_player->GetBulletData(i), m_data))
		{
			//ヒットパーティクル生成
			for (int j = 0; j < HIT_NUM; j++)
			{
				MakeHit(*a_player->GetBulletData(i), { 2,2 });
			}
			SetHP(1);
			MakeBom();
			//当たっていたら敵と弾を消す
			a_player->SetBulletAlive(false, i);
		}
	}
}