#include "Boss.h"
#include "Application/Scene.h"
#include "Application/bullet.h"
#include "Application/Particle/P_Bom.h"

void C_Boss::Init()
{
	for (int i = 0; i < CANNON_NUM; i++)
	{
		i <= UL ? m_cannon[i].obj = { {96,96,0},{},{},{},{Math::Matrix::Identity},nullptr } :
			m_cannon[i].obj = { {96,80,0},{},{},{},{Math::Matrix::Identity},nullptr };

		m_cannon[i].obj.HALF_SIZE = m_cannon[i].obj.SIZE / 2;

		m_cannon[i].cannonHP = MAX_CANNONHP;
		m_cannon[i].damageDelay = 0;
		m_cannon[i].m_bAlive = true;
	}
	m_bCannonFlg = false;

	m_hp = MAX_HP;
	m_data.m_move = { 0,-1,0 };
	m_data.SIZE = { 272,288,0 };
	m_data.HALF_SIZE = m_data.SIZE / 2;
	damageDelay = 0;
}

void C_Boss::Update()
{
	//cannonがすべて破壊されたか
	if (!m_bCannonFlg)CannonAlive();



	//生きていれば
	if (m_bAlive)
	{
		if (rand() % 60 <= 0)MakeBullet();
		if (damageDelay > 0)damageDelay--;
		if (m_data.m_pos.y <= 200)m_data.m_move = { };

		m_data.m_pos += m_data.m_move;
		m_data.m_mat = Math::Matrix::CreateTranslation(m_data.m_pos);

		m_cannon[UL].obj.m_pos = { m_data.m_pos.x - 83,m_data.m_pos.y + 23 };
		m_cannon[UR].obj.m_pos = { m_data.m_pos.x + 83,m_data.m_pos.y + 23 };
		m_cannon[DL].obj.m_pos = { m_data.m_pos.x - 70,m_data.m_pos.y - 100 };
		m_cannon[DR].obj.m_pos = { m_data.m_pos.x + 70,m_data.m_pos.y - 100 };
	}
	else if (damageDelay-- > 0)MakeBom(m_data);
	
	for (int i = 0; i < CANNON_NUM; i++)
	{
		m_cannon[i].obj.m_mat = Math::Matrix::CreateTranslation(m_cannon[i].obj.m_pos);
		if (m_cannon[i].cannonHP <= 0 && m_cannon[i].m_bAlive)
		{
			m_cannon[i].m_bAlive = false;
		}
		else if (m_cannon[i].damageDelay > 0&& !m_cannon[i].m_bAlive)
		{
			MakeBom(m_cannon[i].obj);
		}

		if (m_cannon[i].damageDelay > 0)m_cannon[i].damageDelay--;
	}

	for (int i = 0; i < m_bullet.size(); i++)
	{
		m_bullet[i]->Update();
	}
	for (int i = 0; i < m_particle.size(); i++)
	{
		m_particle[i]->Update();
	}
	DeleteManager();
}

void C_Boss::Draw()
{
	//ボス本体
	if (m_bAlive)
	{
		Math::Color color = { 1.0f,1.0f,1.0f,1.0f };
		if (damageDelay > 0)color = { 1.0f,0.5f,0.5f,1.0f };

		Math::Rectangle m_srcRect = { 0,0,(long)m_data.SIZE.x,(long)m_data.SIZE.y };

		SHADER.m_spriteShader.SetMatrix(m_data.m_mat);
		SHADER.m_spriteShader.DrawTex(m_data.m_pTex, Math::Rectangle{ 0,0,(long)m_data.SIZE.x,(long)m_data.SIZE.y }, 1.0f);
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

	//大砲
	for (int i = 0; i < CANNON_NUM; i++)
	{
		if (!m_cannon[i].m_bAlive)continue;
		Math::Color color = { 1.0f,1.0f,1.0f,1.0f };
		if (m_cannon[i].damageDelay > 0)color = { 1.0f,0.5f,0.5f,1.0f };

		Math::Rectangle m_srcRect = { 96 * i,0,(long)m_cannon[i].obj.SIZE.x,(long)m_cannon[i].obj.SIZE.y };

		SHADER.m_spriteShader.SetMatrix(m_cannon[i].obj.m_mat);
		//ダメージによる描画変更
		if (m_cannon[i].damageDelay > 0 && m_cannon[i].damageDelay % 3)
		{
			Math::Color a_color = { 1.0f,0.7f,0.7f,1.0f };
			SHADER.m_spriteShader.DrawTex(m_cannon[i].obj.m_pTex, 0, 0, m_cannon[i].obj.SIZE.x, m_cannon[i].obj.SIZE.x, &m_srcRect, &a_color, Math::Vector2(0.5f, 0.5f));
		}
		else
		{
			SHADER.m_spriteShader.DrawTex(m_cannon[i].obj.m_pTex, 0, 0, m_cannon[i].obj.SIZE.x, m_cannon[i].obj.SIZE.x, &m_srcRect, &color, Math::Vector2(0.5f, 0.5f));
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

void C_Boss::PlayerCD(C_Player* a_player)
{
	if (!a_player->GetAlive())return;
	//敵の球
	for (int i = 0; i < m_bullet.size(); i++)
	{
		if (CircleCD(*m_bullet[i]->GetData(), *a_player->GetData()) && m_bullet[i]->GetAlive())
		{
			//敵と接触で自機にダメージ
			m_bullet[i]->SetAlive(false);
			a_player->SetHP(1);
		}
	}
	if (!m_bAlive)return;
	//敵本体
	if (CircleCD(m_data, *a_player->GetData()) && m_bAlive)
	{
		//敵と接触で自機にダメージ
		MakeBom(*a_player->GetData());
		a_player->SetHP(1);
	}
}

void C_Boss::HitCheckBullet(C_Player* a_player)
{
	if (!m_bAlive)return;
	for (int i = 0; i < a_player->GetBulletSize(); i++)
	{
		if (!m_bCannonFlg)
		{
			for (int j = 0; j < CANNON_NUM; j++)
			{
				if (!m_cannon[j].m_bAlive)continue;
				if (CircleCD(*a_player->GetBulletData(i), m_cannon[j].obj))
				{
					//ヒットパーティクル生成
					for (int z = 0; z < HIT_NUM; z++)
					{
						MakeHit(*a_player->GetBulletData(i), { 2,2 });
					}
					m_cannon[j].damageDelay = 30;
					m_cannon[j].cannonHP -= 1;
					a_player->SetBulletAlive(false, i);
				}
			}
		}
		else
		{
			if (CircleCD(*a_player->GetBulletData(i), m_data))
			{
				//ヒットパーティクル生成
				for (int z = 0; z < HIT_NUM; z++)
				{
					MakeHit(*a_player->GetBulletData(i), { 2,2 });
				}
				SetHP(1);
				damageDelay = 30;
				//当たっていたら敵と弾を消す
				a_player->SetBulletAlive(false, i);
			}
		}
	}
}

void C_Boss::CannonAlive()
{
	for (int i = 0; i < CANNON_NUM; i++)
	{
		if (m_cannon[i].m_bAlive)return;
	}
	m_bCannonFlg = true;
}

void C_Boss::MakeBullet()
{
	shared_ptr<C_Bullet> tmpA = make_shared<C_Bullet>();
	tmpA->Init();
	tmpA->SetPos({ m_data.m_pos.x,m_data.m_pos.y,m_data.m_pos.z });//座標
	tmpA->SetMove({ (float)((rand() % 31 - 15) * 0.1),BULLET_MOVE_Y,0 });//移動量
	tmpA->SetTex(m_pBulletTex);	//画像
	m_bullet.push_back(tmpA);
}

void C_Boss::MakeBom(OBJData a_data, int num)
{
	for (int i = 0; i < num; i++)
	{
		shared_ptr<C_PBom> tmpA = make_shared<C_PBom>();
		tmpA->Init();
		float X = a_data.m_pos.x + ((rand() % (long)a_data.SIZE.x) - a_data.HALF_SIZE.x);
		float Y = a_data.m_pos.y + ((rand() % (long)a_data.SIZE.y) - a_data.HALF_SIZE.y);
		tmpA->SetPos({ X,Y,a_data.m_pos.z });//座標
		tmpA->SetMove({ 0, a_data.m_move.y, 0 });//移動量
		tmpA->SetTex(m_pBomTex);	//画像
		m_particle.push_back(tmpA);
	}
}

void C_Boss::SetTex(Scene* a_pOwner)
{
	m_data.m_pTex = &a_pOwner->GetBossTex()->bossTex;
	for (int i = 0; i < CANNON_NUM; i++)
	{
		if (i <= UR)
		{
			m_cannon[i].obj.m_pTex = &a_pOwner->GetBossTex()->cannonUTex;
		}
		else
		{
			m_cannon[i].obj.m_pTex = &a_pOwner->GetBossTex()->cannonDTex;
		}
	}
	m_pBulletTex = &a_pOwner->GetObjectTex()->bulletTex;
	m_pBomTex = &a_pOwner->GetObjectTex()->p_bomTex;
}