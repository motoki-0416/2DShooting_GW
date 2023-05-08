#include "Boss.h"
#include "Application/Scene.h"
#include "Application/Scene/Game/Scene_Game.h"

#include "Application/Object/Enemy/Boss/Cannon.h"

#include "Application/Object/Bullet/bullet.h"
#include "Application/Object/Bullet/Missile/Homing.h"


#include "Application/Particle/P_Bom.h"
#include "Application/Particle/volt/volt.h"

void C_Boss::Init()
{
	//攻撃変数
	atkDelay = 100;
	m_atk = Atk_Missile;

	m_hp = MAX_HP;

	m_data.m_move = { 0,-1,0 };

	m_data.SIZE = { 272,288,0 };

	m_data.HALF_SIZE = m_data.SIZE / 2;

	damageDelay = 0;

	moveDeg = 180;

	startFlg = false;
}



//処理
void C_Boss::Update()
{
	if (!startFlg)
	{

		if (m_data.m_pos.y <= 200)
		{
			startFlg = true;
		}
	}
	else
	{


		if (damageDelay > 0)damageDelay--;	//ダメージを食らっていたら

		if (m_bAlive)
		{

			Move();								//動き

			AtkSelect();						//攻撃

		}
		else
		{
			//m_pOwner->SetSlow();

			if (damageDelay < 0)damageDelay = 30;

			m_data.m_move = {};

			MakeBom(m_data);

		}
	}

	if (rand() % 20 <= 0)MakeVolt();	//パーティクル

	for (int i = 0; i < m_cannonList.size(); i++)
	{
		m_cannonList[i]->SetPos(m_data.m_pos);
		m_cannonList[i]->Update();
	}

	for (int i = 0; i < m_bullet.size(); i++)
	{
		if(!m_bAlive)m_bullet[i]->SetAlpha(0.03);
		m_bullet[i]->Update();

	}

	for (int i = 0; i < m_particle.size(); i++)
	{

		m_particle[i]->Update();

	}

	DeleteManager();

}



//描画
void C_Boss::Draw()
{
	//ボス本体

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


	//大砲
	for (int i = 0; i < m_cannonList.size(); i++)
	{
		m_cannonList[i]->Draw();
	}


	D3D.SetBlendState(BlendMode::Add);

	for (int i = 0; i < m_bullet.size(); i++)
	{

		m_bullet[i]->Draw();

	}
	D3D.SetBlendState(BlendMode::Alpha);

	for (int i = 0; i < m_particle.size(); i++)
	{

		m_particle[i]->Draw();

	}
}



//自機との当たり判定
void C_Boss::PlayerCD(C_Player& a_player)
{
	if (!a_player.GetAlive())return;
	if (!m_bAlive)return;

	//敵の球
	for (int i = 0; i < m_bullet.size(); i++)
	{

		if (CircleCD(*m_bullet[i]->GetData(), *a_player.GetData()) && m_bullet[i]->GetAlive())
		{
			//敵と接触で自機にダメージ
			m_bullet[i]->SetAlive(false);
			a_player.SetHP(1);

		}

	}

	//敵本体
	if (CircleCD(m_data, *a_player.GetData()) && m_bAlive)
	{

		//敵と接触で自機にダメージ
		MakeBom(*a_player.GetData());

		a_player.SetHP(1);

	}

	playerPos = a_player.GetPos();
}



//球の当たり判定
void C_Boss::HitCheckBullet(C_SceneGame* a_pOwner)
{
	if (!m_bAlive)return;

	if (m_cannonList.size() > 0)
	{
		for (int i = 0; i < m_cannonList.size(); i++)
		{
			m_cannonList[i]->HitCheckBullet(a_pOwner);
		}
	}
	else
	{

		for (int i = 0; i < a_pOwner->GetPlayer()->GetBulletSize(); i++)
		{

			if (CircleCD(*a_pOwner->GetPlayer()->GetBulletData(i), m_data))
			{
				//ヒットパーティクル生成
				for (int z = 0; z < HIT_NUM; z++)
				{
					MakeHit(*a_pOwner->GetPlayer()->GetBulletData(i), { 2,2 });
				}

				SetHP(1);

				damageDelay = 30;

				//当たっていたら敵と弾を消す
				a_pOwner->GetPlayer()->SetBulletAlive(false, i);

				a_pOwner->SetScore(1000);

			}
		}
	}
}



//攻撃選択
void C_Boss::AtkSelect()
{
	if (atkDelay-- > 0)return;

	switch (m_atk)
	{

	case Atk_Missile:
		AtkMissile();
		break;

	case Atk_Rotate:
		AtkRotate();
		break;

	case Atk_Homing:
		AtkHoming();
		break;

	default:
		break;
	}
}



//扇攻撃
void C_Boss::AtkMissile()
{
	static int oDelay = 0;
	static int oCount;

	if (oDelay <= 0)
	{

		MakeMissile();

		oDelay = 30;

		oCount++;
	}
	else
	{

		oDelay--;

	}

	if (oCount > 5)
	{

		oDelay = 0;

		oCount = 0;

		atkDelay = 100;

		m_atk = Atk_Rotate;

	}
}



//回転攻撃
void C_Boss::AtkRotate()
{
	static int hDelay = 0;

	hDelay++;

	if (hDelay % 2)
	{

		MakeBullet();

	}

	if (hDelay > 100)
	{

		hDelay = 0;

		atkDelay = 100;

		m_atk = Atk_Homing;

	}
}



//ホーミングの作成
void C_Boss::AtkHoming()
{

	static int hDelay = 0;
	static int hCount;

	if (hDelay <= 0)
	{

		MakeHoming();

		hDelay = 3;

		hCount++;
	}
	else
	{

		hDelay--;

	}

	if (hCount > 30)
	{

		hDelay = 0;

		hCount = 0;

		atkDelay = 100;

		m_atk = Atk_Missile;

	}
}



//球の作成
void C_Boss::MakeBullet()
{
	static int m_deg = 0;

	for (int i = 1; i < 3; i++)
	{
		m_deg = rand() % 360;;
		shared_ptr<C_Bullet> tmpA = make_shared<C_Bullet>();
		tmpA->Init();
		tmpA->SetPos({ m_data.m_pos.x,m_data.m_pos.y - 20,m_data.m_pos.z });//座標
		tmpA->SetMove({ cos(DirectX::XMConvertToRadians(m_deg)) * 5.0f,sin(DirectX::XMConvertToRadians(m_deg)) * 5.0f,0 });//移動量
		tmpA->SetSize(2);
		tmpA->SetTex(m_pBulletTex);	//画像
		m_bullet.push_back(tmpA);
	}

	m_deg = 0;

}



//球の作成
void C_Boss::MakeVolt()
{
	shared_ptr<C_PVolt> tmpA = make_shared<C_PVolt>();
	tmpA->Init();
	float X = m_data.m_pos.x;
	float Y = m_data.m_pos.y - 10;
	tmpA->SetPos({ X,Y,m_data.m_pos.z });//座標
	tmpA->SetTex(m_pVoltTex);	//画像
	m_particle.push_back(tmpA);
}




//扇状の作成
void C_Boss::MakeMissile()
{
	for (int i = 0; i < 5; ++i)
	{

		shared_ptr<C_Bullet> tmpA = make_shared<C_Bullet>();
		tmpA->Init();
		tmpA->SetPos({ m_data.m_pos.x,m_data.m_pos.y - 20,m_data.m_pos.z });
		tmpA->SetMove({ 4.0f - i * 2,-7.0f,0.0f });
		tmpA->SetSize(1.5);
		tmpA->SetTex(m_pBulletTex);
		m_bullet.push_back(tmpA);

	}
}



//ホーミング球の作成
void C_Boss::MakeHoming()
{
	shared_ptr<C_Homing> tmpA = make_shared<C_Homing>();
	tmpA->Init();
	tmpA->SetPos({ m_data.m_pos.x,m_data.m_pos.y - 20,m_data.m_pos.z });
	tmpA->SetMove({ rand() % 10 - 5.0f, rand() % 2 + 1.0f,0.0f });
	tmpA->SetPlayerPos(playerPos);
	tmpA->SetSize(1.5);
	tmpA->SetTex(m_pBulletTex);
	m_bullet.push_back(tmpA);
}



//ボムの作成
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



//ボスの移動
void C_Boss::Move()
{

	m_data.m_move.y = 0;

	if (moveDeg++ > 360)
	{

		moveDeg -= 360;

	}

	m_data.m_move.x = cos(DirectX::XMConvertToRadians(moveDeg)) * 3;

	m_data.m_move.y = cos(DirectX::XMConvertToRadians(moveDeg * 2)) * 0.5;

}


//画像のセット
void C_Boss::SetTex(Scene* a_pOwner)
{
	m_data.m_pTex = &a_pOwner->GetTex()->bossTex;
	m_pBulletTex = &a_pOwner->GetTex()->bulletTex;
	m_pBomTex = &a_pOwner->GetTex()->p_bomTex;
	m_pVoltTex = &a_pOwner->GetTex()->voltTex;
	m_pMissileTex = &a_pOwner->GetTex()->missileTex;

	//大砲の作成
	for (int i = 0; i < CANNON_NUM; i++)
	{
		shared_ptr<C_Cannon> tmpA = make_shared<C_Cannon>();
		tmpA->SetCannonType(i);
		i < CANNON_NUM / 2 ? tmpA->SetTex(&a_pOwner->GetTex()->cannonUTex, a_pOwner) : tmpA->SetTex(&a_pOwner->GetTex()->cannonDTex, a_pOwner);
		tmpA->Init();
		tmpA->SetPos(m_data.m_pos);
		m_cannonList.push_back(tmpA);
	}

	m_pOwner = a_pOwner;

}



void C_Boss::CommitPos(Math::Vector3 a_move)
{
	m_data.m_pos += (m_data.m_move + a_move);
	m_scaleMat = Math::Matrix::CreateScale(m_size);
	m_transMat = Math::Matrix::CreateTranslation(m_data.m_pos);
	m_data.m_mat = m_scaleMat * m_transMat;

	for (int i = 0; i < m_cannonList.size(); i++)
	{
		m_cannonList[i]->CommitPos(a_move);
	}

	for (int i = 0; i < m_bullet.size(); i++)
	{
		m_bullet[i]->CommitPos(a_move);
	}


	for (int i = 0; i < m_particle.size(); i++)
	{
		m_particle[i]->CommitPos(a_move);
	}
}



void C_Boss::DeleteManager()
{
	//球
	auto be = m_bullet.begin();
	while (be != m_bullet.end())
	{
		if (!(*be)->GetAlive())
		{
			be = m_bullet.erase(be);
		}
		else
		{
			be++;
		}
	}

	//パーティクル
	auto hi = m_particle.begin();
	while (hi != m_particle.end())
	{
		if (!(*hi)->GetAlive())
		{
			hi = m_particle.erase(hi);
		}
		else
		{
			hi++;
		}
	}

	//大砲
	auto ti = m_cannonList.begin();
	while (ti != m_cannonList.end())
	{
		if (!(*ti)->GetAlive() && (*ti)->GetSize() <= 0)
		{
			ti = m_cannonList.erase(ti);
		}
		else
		{
			ti++;
		}
	}
}
