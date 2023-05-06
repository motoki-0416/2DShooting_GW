#pragma once
#include "Application/Utility.h"
using namespace std;
using namespace Screen;
using namespace Alpha;

class Scene;

class C_Back
{

public:
	C_Back(){};
	~C_Back() {}

	void Init();
	void Update();
	void Draw();

	//セッター
	void SetTex(Scene* a_pOwner);
	void SetMove(Math::Vector3 a_move) { m_back.m_move = a_move; }
	void SetMove(float a_move) { m_back.m_move.y = a_move; }
	void SetStopFlg(bool a_flg) { stopFlg = a_flg; }

	const Math::Vector3 GetMove() { return m_back.m_move; }

	//ゲッター
	const Math::Vector3 GetPos() { return m_back.m_pos; }
	const OBJData GetData() { return m_back; }


private:
	
	OBJData m_back = { {640, 3648, 0}, m_back.SIZE / 2, {0,0,0}, {0,-1,0}, 1.0f,{Math::Matrix::Identity}, {nullptr} };;
	
	bool stopFlg;

	Math::Matrix m_transMat;
	Math::Matrix m_scalMat;

};