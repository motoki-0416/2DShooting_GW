#include "Application/Object/Enemy/Boss/Cannon.h"
#include "Application/Scene.h"
#include "Application/Scene/Game/Scene_Game.h"
#include "Application/Object/Player/Player.h"
#include "Application/Particle/P_Bom.h"

void C_Cannon::Init()
{
	switch (m_cannonType)
	{
	case C_Cannon::CannonType::UL:
	case C_Cannon::CannonType::UR:
		m_data.SIZE = { 96,96 };
		break;
	case C_Cannon::CannonType::DL:
	case C_Cannon::CannonType::DR:
		m_data.SIZE = { 96,80 };
		break;
	}
	m_data.HALF_SIZE = m_data.SIZE / 2;

	damageDelay = 0;
	m_hp = 50;
}

void C_Cannon::Draw()
{
	for (int i = 0; i < m_particle.size(); i++)
	{
		m_particle[i]->Draw();
	}



	if (!m_bAlive)return;

	Math::Color color = { 1.0f,1.0f,1.0f,1.0f };

	if (damageDelay > 0)color = { 1.0f,0.5f,0.5f,1.0f };


	Math::Rectangle m_srcRect = { 96*(int)m_cannonType,0,(long)m_data.SIZE.x,(long)m_data.SIZE.y };


	SHADER.m_spriteShader.SetMatrix(m_data.m_mat);


	//ダメージによる描画変更
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

void C_Cannon::Update()
{
	for (int i = 0; i < m_particle.size(); i++)
	{
		m_particle[i]->Update();
	}


	if (m_bAlive)
	{
		//生存確認
		if (m_hp <= 0)
		{

			m_bAlive = false;

		}


	}

	//死亡時ボム作成
	else if (damageDelay > 0)
	{

		MakeBom();

	}

	if (damageDelay > 0)
	{

		damageDelay--;

	}

	DeleteManager();

}

void C_Cannon::SetPos(Math::Vector3 a_pos)
{
	switch (m_cannonType)
	{
	case C_Cannon::CannonType::UL:
		m_data.m_pos = { a_pos.x - 83.0f, a_pos.y + 23.0f,0.0f };
		break;
	case C_Cannon::CannonType::UR:
		m_data.m_pos = { a_pos.x + 83.0f, a_pos.y + 23.0f,0.0f };
		break;
	case C_Cannon::CannonType::DL:
		m_data.m_pos = { a_pos.x - 70.0f, a_pos.y - 100.0f,0.0f };
		break;
	case C_Cannon::CannonType::DR:
		m_data.m_pos = { a_pos.x + 70.0f,a_pos.y - 100.0f,0.0f };
		break;
	default:
		break;
	}


}

void C_Cannon::MakeBom()
{

	shared_ptr<C_PBom> tmpA = make_shared<C_PBom>();
	tmpA->Init();
	float X = m_data.m_pos.x + ((rand() % (long)m_data.SIZE.x) - m_data.HALF_SIZE.x);
	float Y = m_data.m_pos.y + ((rand() % (long)m_data.SIZE.y) - m_data.HALF_SIZE.y);
	tmpA->SetPos({ X,Y,m_data.m_pos.z });//座標
	tmpA->SetMove({ 0, m_data.m_move.y, 0 });//移動量
	tmpA->SetTex(m_pBomTex);	//画像
	m_particle.push_back(tmpA);

}

void C_Cannon::HitCheckBullet(C_SceneGame* a_pOwner)
{
	if (!m_bAlive)return;

	for (int i = 0; i < a_pOwner->GetPlayer()->GetBulletSize(); i++)
	{
		if (CircleCD(*a_pOwner->GetPlayer()->GetBulletData(i), m_data))
		{
			//ヒットパーティクル生成
			for (int z = 0; z < HIT_NUM; z++)
			{

				MakeHit(*a_pOwner->GetPlayer()->GetBulletData(i), { 2,2 });

			}

			damageDelay = 30;

			m_hp -= 1;

			a_pOwner->GetPlayer()->SetBulletAlive(false, i);

			a_pOwner->SetScore(1000);

		}
	}
}
