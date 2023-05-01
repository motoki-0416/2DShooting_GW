#include "BaseObject.h"
#include "Application/Scene.h"
#include "Application/Object/Player/Player.h"
#include "Application/Object/Bullet/BaseBullet.h"

#include "Application/Particle/P_Bom.h"
#include "Application/Particle/P_Hit.h"


C_BaseObject::C_BaseObject()
{
	m_hp = 1;
	m_size = 1;
	animation = 0;
	m_data.m_move = { 0,MOVE_Y };
	m_bAlive = true;
}

C_BaseObject::~C_BaseObject()
{
	m_particle.clear();
	m_bullet.clear();
}

void C_BaseObject::Draw()
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

bool C_BaseObject::BoxCD(const OBJData a_Adata, const OBJData a_Bdata)
{
	//	Adataの矩形データ
	float ADLeft = a_Adata.m_pos.x - a_Adata.HALF_SIZE.x;
	float ADRight = a_Adata.m_pos.x + a_Adata.HALF_SIZE.x;
	float ADTop = a_Adata.m_pos.y + a_Adata.HALF_SIZE.y;
	float ADBottom = a_Adata.m_pos.y - a_Adata.HALF_SIZE.y;

	//	Bdataの矩形データ
	float BDLeft = a_Bdata.m_pos.x - a_Bdata.HALF_SIZE.x;
	float BDRight = a_Bdata.m_pos.x + a_Bdata.HALF_SIZE.x;
	float BDTop = a_Bdata.m_pos.y + a_Bdata.HALF_SIZE.y;
	float BDBottom = a_Bdata.m_pos.y - a_Bdata.HALF_SIZE.y;

	if ((ADLeft < BDRight && ADRight > BDLeft) && (ADTop > BDBottom && ADBottom < BDTop))
	{
		return true;
	}
	return false;
}

bool C_BaseObject::CircleCD(const OBJData a_Adata, const OBJData a_Bdata)
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

void C_BaseObject::PlayerCD(C_Player* a_player)
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
		m_bAlive = false;
		MakeBom();
		a_player->SetHP(1);
	}

}

void C_BaseObject::HitCheckBullet(C_Player* a_player)
{
	if (!m_bAlive)return;
	for (int i = 0; i < a_player->GetBulletSize(); i++)
	{
		if (CircleCD(*a_player->GetBulletData(i), m_data))
		{
			//ヒットパーティクル生成
			for (int j = 0; j < HIT_NUM; j++)
			{
				MakeHit( *a_player->GetBulletData(i));
			}
			MakeBom();
			m_bAlive = false;
			//当たっていたら敵と弾を消す
			a_player->SetBulletAlive(false, i);
		}
	}
}

void C_BaseObject::DeleteManager()
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

	
}

//	アニメ枚数	攻撃時に別のアニメがある場合
void C_BaseObject::Animetion(int AniCnt, bool AtkAni)
{
	/*if (delay-- > 0)return;
	if (animation >= AniCnt)animation = 0;
	delay = MAXDELAY;
	m_srcRect = { (int)(m_data.SIZE.x * animation),(int)(m_data.SIZE.y * AtkAni),(int)m_data.SIZE.x,(int)m_data.SIZE.y };
	animation++;*/
}


void C_BaseObject::SetTex(KdTexture* a_pTex, Scene* a_pOwner)
{
	m_data.m_pTex = a_pTex;
	m_pBulletTex = &a_pOwner->GetObjectTex()->bulletTex;
	m_pBomTex = &a_pOwner->GetObjectTex()->p_bomTex;
}


void C_BaseObject::MakeBom()
{
	shared_ptr<C_PBom> tmpA = make_shared<C_PBom>();
	tmpA->Init();
	tmpA->SetPos({ m_data.m_pos.x,m_data.m_pos.y,m_data.m_pos.z });//座標
	tmpA->SetMove({ 0, m_data.m_move.y, 0 });//移動量
	tmpA->SetTex(m_pBomTex);	//画像
	m_particle.push_back(tmpA);
}

void C_BaseObject::MakeHit(OBJData a_data, Math::Vector2 a_size)
{
	shared_ptr<C_PHit> tempHit = make_shared<C_PHit>();
	tempHit->Init();
	tempHit->SetTex(m_pBulletTex);
	tempHit->SetPos(a_data.m_pos);
	tempHit->SetMove({ (float)((rand() % 41 - 20) * 0.1), a_data.m_move.y * -1.0f * (rand() % 4 + 1) * 0.1f ,0 });
	tempHit->SetSize((rand() % 3 + 3 + a_size.x) * 0.1f, (rand() % 3 + 1 + a_size.y) * 0.013);
	m_particle.push_back(tempHit);
}
