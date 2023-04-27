#pragma once
#include "Utility.h"
using namespace Screen;

class C_Bullet
{
public:

	C_Bullet();    //コンストラクタ
	~C_Bullet();   //デストラクタ

	void Init();
	void Update();
	void Draw();

	//関数


	//セッター
	void SetAlive(bool a_alive) { m_bAlive = a_alive; }
	void SetTex(KdTexture* a_pTex) { m_data.m_pTex = a_pTex; }
	void SetPos(Math::Vector3 a_pos) { m_data.m_pos = a_pos; }
	void SetMove(Math::Vector3 a_move) { m_data.m_move = a_move; }

	//ゲッター
	const bool GetAlive() { return m_bAlive; }
	const Math::Vector3 GetPos() { return m_data.m_pos; }
	const Math::Vector3 GetMove() { return m_data.m_move; }
	const OBJData* GetData() { return &m_data; }

private:

	OBJData m_data = { {16,16,0},m_data.SIZE / 2,{0,0,0},{0,0,0},{ Math::Matrix::Identity}, {nullptr} };
	bool m_bAlive;
	
	//弾が画面が外に出たか
	const bool IsScreenOut();
};