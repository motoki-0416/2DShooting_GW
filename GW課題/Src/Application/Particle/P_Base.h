#pragma once
#include "Application/Utility.h"

class C_Player;

using namespace std;
using namespace Screen;

class C_BaseParticle
{
public:
	C_BaseParticle();
	virtual ~C_BaseParticle() {}

	virtual void Init(){};
	virtual void Update() {};
	virtual void Draw();

	virtual void SetTex(KdTexture* a_pTex){ m_data.m_pTex = a_pTex; }
	virtual void SetPos(Math::Vector3 a_pos) { m_data.m_pos = a_pos; m_data.m_mat = Math::Matrix::CreateTranslation(m_data.m_pos); }
	virtual void SetMove(Math::Vector3 a_move) { m_data.m_move = a_move; }

	const bool GetAlive() { return m_bAlive; }
	
protected:

	bool m_bAlive;
	float m_alpha;
	float m_size;

	OBJData m_data = { {16,16,0},m_data.SIZE / 2,{0,0,0},{0,0,0},{Math::Matrix::Identity},nullptr };

	Math::Matrix m_transMat;
	Math::Matrix m_scaleMat;
	Math::Color m_color;
};