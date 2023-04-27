#include "Player.h"
#include "Application/Scene.h"
#include "Application/Object/BaseObject.h"
#include "Application/Particle/P_Bom.h"
#include "Application/Object/Enemy/MiniBoss/MiniBoss.h"

C_Player::C_Player()
{
	Init();



}

C_Player::~C_Player()
{
	m_bullet.clear();//箱も中身もすべて削除
	m_bom.clear();
}

//初期化
void C_Player::Init()
{
	m_bullet.clear();
	m_bom.clear();

	//イベント
	bStartFlg = true;

	//自機
	m_bAlive = true;
	m_hp = MAX_HP;
	m_data.m_pos = { 0,-400,0 };

	//球
	bulletOffset = 0;
	bomCount = 0;
	bomDelay = 0;
}

void C_Player::Update(int a_eve)
{
	switch (a_eve)
	{
	case 1://スタート
		StartEvent();
		return;
		break;

	default:
		break;
	}


	if (m_bAlive)
	{
		Key();
	}
	else
	{
		m_data.m_move = {};
		DedAnime();
	}

	for (int b = 0; b < m_bullet.size(); b++)
	{
		m_bullet[b]->Update();
	}
	for (int i = 0; i < m_bom.size(); i++)
	{
		m_bom[i]->Update();
	}

	//削除
	DeleteManager();

	m_data.m_pos += m_data.m_move;
	m_data.m_mat = Math::Matrix::CreateTranslation(m_data.m_pos);
}

void C_Player::Draw()
{


	for (int i = 0; i < m_bullet.size(); i++)
	{
		m_bullet[i]->Draw();
	}

	if (bomCount < BOM_MAX)
	{
		SHADER.m_spriteShader.SetMatrix(m_data.m_mat);
		SHADER.m_spriteShader.DrawTex(m_data.m_pTex, Math::Rectangle(0, 0, m_data.SIZE.x, m_data.SIZE.y), 1.0f);
	}

	for (int i = 0; i < m_bom.size(); i++)
	{
		m_bom[i]->Draw();
	}


}


void C_Player::StartEvent()
{
	m_data.m_move.y = 1;
	m_data.m_pos += m_data.m_move;
	if (m_data.m_pos.y >= -200)
	{
		m_data.m_pos.y = -200;
	}

	m_data.m_mat = Math::Matrix::CreateTranslation(m_data.m_pos);
}

void C_Player::Key()
{
	m_data.m_move = {};

	//移動
	if (GetAsyncKeyState(VK_UP) & 0x8000)
	{
		m_data.m_move.y = 5;
	}
	if (GetAsyncKeyState(VK_DOWN) & 0x8000)
	{
		m_data.m_move.y = -5;
	}
	if (GetAsyncKeyState(VK_LEFT) & 0x8000)
	{
		m_data.m_move.x = -5;
	}
	if (GetAsyncKeyState(VK_RIGHT) & 0x8000)
	{
		m_data.m_move.x = 5;
	}

	//球の発射
	if (GetAsyncKeyState(VK_SPACE) & 0x8000)
	{
		if (shotCount < 0)
		{
			MakeBullet();
			bulletOffset ? bulletOffset = false : bulletOffset = true;
			shotCount = COUNT_NUM;
		}
		else
		{
			shotCount--;
		}
	}
	else
	{
		shotCount = 0;
	}
}

void C_Player::DedAnime()
{
	if (bomCount == BOM_MAX)
	{
		for (int i = 0; i < BOM_NUM; i++)
		{
			MakeBom({ m_data.m_pos.x + rand() % 100 - 50,m_data.m_pos.y + rand() % 100 - 50,m_data.m_pos.z }, (rand() % 10 * 0.1f) + 1.0f);
		}
		//終わらせる
		bomCount = 99;
	}
	//死亡時に爆破
	else if (bomCount < BOM_MAX && bomDelay <= 0)
	{
		MakeBom({ m_data.m_pos.x + rand() % 30 - 15,m_data.m_pos.y + rand() % 30 - 15,m_data.m_pos.z }, (rand() % 5 * 0.1f) + 0.8);
		bomCount++;
		bomDelay = DLEAY_MAX;
	}
	else
	{
		bomDelay--;
	}
}

void C_Player::DeleteManager()
{
	//球
	auto be = m_bullet.begin();
	while (be != m_bullet.end())
	{
		if (!(*be)->GetAlive())
		{
			be->reset();
			be = m_bullet.erase(be);
		}
		else
		{
			be++;
		}
	}

	//爆破パーティクル
	auto bo = m_bom.begin();
	while (bo != m_bom.end())
	{
		if (!(*bo)->GetAlive())
		{
			bo->reset();
			bo = m_bom.erase(bo);
		}
		else
		{
			bo++;
		}
	}
}



void C_Player::MakeBullet()
{
	shared_ptr<C_Bullet> tmpA = make_shared<C_Bullet>();
	tmpA->Init();
	tmpA->SetPos({ m_data.m_pos.x,m_data.m_pos.y + (7 * bulletOffset),m_data.m_pos.z });//座標
	tmpA->SetMove({ (float)((rand() % 31 - 15) * 0.1),BULLET_MOVE_Y,0 });//移動量
	tmpA->SetTex(m_pBulletTex);	//画像
	m_bullet.push_back(tmpA);
}

void C_Player::MakeBom(Math::Vector3 a_pos, float size, Math::Vector3 a_move)
{
	shared_ptr<C_PBom> tempBom = make_shared<C_PBom>();
	tempBom->Init();
	tempBom->SetTex(m_pBomTex);
	tempBom->SetPos(a_pos);
	tempBom->SetMove(a_move);
	tempBom->SetSize(size);
	m_bom.push_back(tempBom);
}

void C_Player::SetTex(KdTexture* a_pTex, Scene* a_pOwner)
{
	m_data.m_pTex = a_pTex;
	m_pBulletTex = &a_pOwner->GetObjectTex()->bulletTex;
	m_pHitTex = &a_pOwner->GetObjectTex()->p_hitTex;
	m_pBomTex = &a_pOwner->GetObjectTex()->p_bomTex;
}

void C_Player::SetHP(int a_hp)
{
	m_hp -= a_hp; 
	if (m_hp <= 0)m_bAlive = false; 
	MakeBom(m_data.m_pos);
}

bool C_Player::CircleCD(const OBJData a_Adata, const OBJData a_Bdata)
{
	float tx = a_Adata.m_pos.x - a_Bdata.m_pos.x;
	float ty = a_Adata.m_pos.y - a_Bdata.m_pos.y;
	float dist = sqrt(tx * tx + ty * ty);
	if (dist < a_Adata.HALF_SIZE.y + a_Bdata.HALF_SIZE.y)
	{
		return true;
	}
	return false;
}

