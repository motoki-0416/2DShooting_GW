#pragma once
#include "Utility.h"

class C_Enemy
{

public:

	C_Enemy();    //コンストラクタ
	~C_Enemy();   //デストラクタ

	void Init();
	void Update();
	void Draw2D();

	void SetTex(KdTexture* a_pTex);//仮引数
	void SetPos(Math::Vector2 a_pos) { m_data.m_pos = a_pos; }
	void SetMove(Math::Vector2 a_move) { m_data.m_move = a_move; }
	void SetAlive(bool a_alive) { m_bAlive = a_alive; }
	
	void Hit();

	const OBJData* GetData() { return &m_data; }
	const Math::Vector2 GetPos();
	const float GetRadius();
	const bool GetAlive();

private:

	OBJData m_data = { {64,64},m_data.SIZE / 2,{0,0},{0,0},{}, {nullptr} };
	const int enemyMove = 10;
	float m_radius;
	bool m_bAlive;
};