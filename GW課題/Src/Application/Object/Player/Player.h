#pragma once
#include "Application/Utility.h"
#include "Application/Object/Bullet/BaseBullet.h"
using namespace std;

class Scene;
class C_SceneGame;
class C_PBom;
class C_BaseBullet;
class C_BaseObject;

class C_Player
{
public:

	//関数
	C_Player();    //コンストラクタ
	~C_Player();   //デストラクタ

	void Init();  //初期化
	void Update(int a_eve);//更新
	void Draw();//描画

	//プレイヤー
	void StartEvent();
	void Key();
	void DedAnime();

	void MakeBullet();
	void DeleteManager();
	void ScreenOut();

	//パーティクル作成
	void MakeBom(Math::Vector3 a_pos,float size = 1,Math::Vector3 a_move = { 0,0,0});

	//セッター
	void SetTex(Scene* a_pOwner);//仮引数
	void SetOwner(C_SceneGame* a_pOwner) { m_pOwner = a_pOwner; }
	void SetPos(Math::Vector3 a_pos) { m_data.m_pos = a_pos; m_data.m_mat = Math::Matrix::CreateTranslation(m_data.m_pos); }
	void SetHP(int a_hp);
	void SetAlive(bool a_alive) { m_bAlive = a_alive; }
	void SetBulletAlive(bool a_alive, int i) { m_bullet[i]->SetAlive(a_alive); }

	//ゲッター
	const bool GetAlive() { return m_bAlive; }
	const int GetHP() { return m_hp; }
	const OBJData* GetData() { return &m_data; }
	const OBJData* GetBulletData(int i) { return m_bullet[i]->GetData(); }
	const Math::Vector3 GetPos() { return m_data.m_pos; }
	const int GetBulletSize() { return m_bullet.size(); }

	bool CircleCD(const OBJData a_Adata, const OBJData a_Bdata);
	
	void Animation();

private:

	C_SceneGame* m_pOwner;
	OBJData m_data = { {64,80,0},m_data.SIZE / 2,{0,0,0},{0,0,0},1.0f,{Math::Matrix::Identity},nullptr };
	static const int MAX_HP = 80;
	int m_hp;
	bool m_bAlive;

	//イベント
	bool bStartFlg;
	
	//セッター画像
	KdTexture* m_pHitTex;
	KdTexture* m_pBomTex;

	//球
	KdTexture* m_pBulletTex;
	vector<shared_ptr<C_BaseBullet>> m_bullet;
	static const int BULLET_MOVE_Y = 13;
	static const int COUNT_NUM = 1;
	int shotCount;
	bool bulletOffset;

	//爆破のパーティクル
	vector<shared_ptr<C_PBom>> m_bom;
	static const int BOM_MAX=10;
	static const int BOM_NUM = 4;
	static const int DLEAY_MAX = 4;
	int bomCount;
	int bomDelay;

	//自機変数
	static const int ANIMATION_NUM = 3;
	int animation;
};