#pragma once
#include "Application/Utility.h"

enum EnemyType
{
	enemyNormal=1,
	enemyMiniBoss,
	enemyBoss,
};

using namespace std;
using namespace Screen;

class C_BaseBullet;
class C_BaseParticle;
class C_Player;
class Scene;
class C_SceneGame;

class C_BaseObject
{
public:
	C_BaseObject();
	virtual ~C_BaseObject();

	virtual void Init() {};
	virtual void Update() {};
	virtual void Draw();

	virtual void SetPos(Math::Vector3 a_pos) { m_data.m_pos = a_pos; m_data.m_mat = Math::Matrix::CreateTranslation(m_data.m_pos); }
	virtual void SetMove(Math::Vector3 a_move) { m_data.m_move =a_move; }
	void SetAlpha(float a_alpha);
	void SetAlive(bool a_alive) { m_bAlive = a_alive; }
	virtual void SetTex(KdTexture* a_pTex, Scene* a_pOwner);
	virtual void SetType(EnemyType i) { m_type = i; }
	void SetHP(int i) { m_hp -= i; if (m_hp <= 0) {
		MakeBom(); m_bAlive = false; } }
	void SetCDFlg(bool i) { cdFlg = i; }

	virtual const bool GetAlive() { return m_bAlive; }
	const OBJData* GetData() { return &m_data; }
	const Math::Vector3 GetPos() { return m_data.m_pos; }
	const Math::Vector3 GetMove() { return m_data.m_move; }
	const int  GetSize() { return m_bullet.size() + m_particle.size(); }
	const EnemyType GetType() { return m_type; }

	virtual bool BoxCD(const OBJData a_Adata, const OBJData a_Bdata);
	virtual bool CircleCD(const OBJData a_Adata, const OBJData a_Bdata);
	virtual void PlayerCD(C_Player& a_player);
	virtual void HitCheckBullet(C_SceneGame* a_pOwner);

	virtual void MakeBom();
	void MakeHit(OBJData a_data, Math::Vector2 a_size = { 0,0 });

	virtual void CommitPos(Math::Vector3 a_move);
	virtual  void DeleteManager();

protected:

	bool cdFlg;

	OBJData m_data = { {32,32,0},m_data.SIZE / 2,{0,0,0},{0,0,0},1.0f,{Math::Matrix::Identity},nullptr };
	EnemyType m_type;
	bool m_bAlive;
	float m_size;

	static const int MAX_DELAY = 30;
	int damageDelay;

	static const int MOVE_Y = -1;

	int m_hp;

	//��
	KdTexture* m_pBulletTex;
	vector<shared_ptr<C_BaseBullet>> m_bullet;

	//���̃p�[�e�B�N��
	vector<shared_ptr<C_BaseParticle>>m_particle;
	static const int HIT_NUM = 7;

	//���j
	KdTexture* m_pBomTex;

	Math::Matrix m_transMat;
	Math::Matrix m_scaleMat;

};