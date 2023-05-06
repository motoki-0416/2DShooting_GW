#include "MiniBoss.h"
#include "Application/Scene.h"
#include "Application/Scene/Game/Scene_Game.h"
#include "Application/Object/Bullet/bullet.h"
#include "Application/Particle/P_Bom.h"
#include "Application/Object/Player/Player.h"

void C_MiniBoss::Init()
{
	startFlg = false;
	atkDelay = 0;
	damageDelay = 0;
	m_hp = MAX_HP;
	m_data.m_move = { 0,-1,0 };
	m_data.SIZE = { 176,80,0 };
	m_data.HALF_SIZE = m_data.SIZE / 2;
	m_size = 1.4f;
	m_data.HALF_SIZE = m_data.SIZE / 2;
	m_scaleMat = Math::Matrix::CreateScale(m_size);
}

void C_MiniBoss::Update()
{

	if (damageDelay > 0)damageDelay--;	//ダメージを食らっていたら


	if (!startFlg)
	{

		if (m_data.m_pos.y <= 200)
		{
		
			startFlg = true;
		
		}

	}
	//生きていれば
	else if (m_bAlive)
	{

		if (atkDelay<=0)
		{

			MakeBullet();

		}


		if (atkDelay > 0)
		{

			atkDelay--;

		}


		Move();

	}
	else if (damageDelay > 0)
	{

		MakeBom();
	
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


	//球の削除
	DeleteManager();


}

void C_MiniBoss::Draw()
{
	if (m_bAlive)
	{
		Math::Color color = { 1.0f,1.0f,1.0f,1.0f };
		if (damageDelay > 0)color = { 1.0f,0.5f,0.5f,1.0f };

		Math::Rectangle m_srcRect = { 0,0,(long)m_data.SIZE.x,(long)m_data.SIZE.y };

		SHADER.m_spriteShader.SetMatrix(m_data.m_mat);

		if (damageDelay > 0 && damageDelay % 3)
		{

			Math::Color a_color = { 1.0f,0.7f,0.7f,1.0f };
			SHADER.m_spriteShader.DrawTex(m_data.m_pTex, 0, 0, m_data.SIZE.x, m_data.SIZE.y, &m_srcRect, &a_color, Math::Vector2(0.5f, 0.5f));

		}
		else
		{

			SHADER.m_spriteShader.DrawTex(m_data.m_pTex, 0, 0, m_data.SIZE.x, m_data.SIZE.y, &m_srcRect, &color, Math::Vector2(0.5f, 0.5f));

		}
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


void C_MiniBoss::Move()
{

	m_data.m_move.y = 0;

	static float m_deg = 180;

	if (m_deg++ > 360)
	{

		m_deg -= 360;

	}

	m_data.m_move.x = cos(DirectX::XMConvertToRadians(m_deg)) * 1.5;

}

void C_MiniBoss::MakeBom()
{
	shared_ptr<C_PBom> tmpA = make_shared<C_PBom>();
	tmpA->Init();
	tmpA->SetPos({ m_data.m_pos.x+(rand()%(int)m_data.SIZE.x-m_data.HALF_SIZE.x),m_data.m_pos.y + (rand() % (int)m_data.SIZE.y - m_data.HALF_SIZE.y),m_data.m_pos.z});//座標
	tmpA->SetMove({ 0, m_data.m_move.y, 0 });//移動量
	tmpA->SetTex(m_pBomTex);	//画像
	m_particle.push_back(tmpA);
}



void C_MiniBoss::MakeBullet()
{
	for (int i = 0; i < 3; i++)
	{

		shared_ptr<C_Bullet> tmpA = make_shared<C_Bullet>();
		tmpA->Init();
		tmpA->SetPos({ m_data.m_pos.x,m_data.m_pos.y,m_data.m_pos.z });//座標
		tmpA->SetMove({ 3.0f-i*3,BULLET_MOVE_Y,0 });//移動量
		tmpA->SetSize(1.8);
		tmpA->SetTex(m_pBulletTex);	//画像
		m_bullet.push_back(tmpA);
	
	}

	atkDelay = 60;

}

void C_MiniBoss::HitCheckBullet(C_SceneGame* a_pOwner)
{
	if (!m_bAlive)return;
	for (int i = 0; i < a_pOwner->GetPlayer()->GetBulletSize(); i++)
	{
		if (BoxCD(*a_pOwner->GetPlayer()->GetBulletData(i), m_data))
		{
			//ヒットパーティクル生成
			for (int j = 0; j < HIT_NUM; j++)
			{
				MakeHit(*a_pOwner->GetPlayer()->GetBulletData(i), {2,2});
			}

			damageDelay = 30;

			SetHP(1);

			//当たっていたら敵と弾を消す
			a_pOwner->GetPlayer()->SetBulletAlive(false, i);

			a_pOwner->SetScore(1000);
		}
	}
}