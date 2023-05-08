#pragma once
#include "Application/Scene/BaseScene.h"
#include "Application/Utility.h"

class Scene;
class C_ReturnButton;
class C_ResultNumber;

class C_SceneResult :public C_BaseScene
{
public:

	C_SceneResult() { scoreNum = 0; }
	~C_SceneResult() {};


	void Init(Scene* a_pOwner,bool a_flg)override;
	void Update()override;
	void Draw()override;

	void SetTex(Scene* a_pOwner)override;

	void SetResult(int a_score, int a_enemyNum) override;

	void RankUpdate();

private:

	vector<shared_ptr<C_ResultNumber>> m_number;
	shared_ptr<C_ReturnButton> m_button;
	static const int Y = 80;

	BASE m_total= { {400,Y,0},m_total.SIZE / 2,{-80,-90,0},1.0f,{ Math::Matrix::CreateScale(1.1) * Math::Matrix::CreateTranslation(m_total.m_pos)},{nullptr} };
	BASE m_bonus = { {400,Y,0},m_bonus.SIZE / 2,{160,160,0},1.0f,{ Math::Matrix::CreateScale(0.4) * Math::Matrix::CreateTranslation(m_bonus.m_pos)},{nullptr} };
	BASE m_score = { {211,Y,0},m_score.SIZE / 2,{0,160,0},1.0f,{Math::Matrix::CreateScale(0.7) * Math::Matrix::CreateTranslation(m_score.m_pos)},{nullptr} };
	BASE m_ded = { {490,Y,0},m_ded.SIZE / 2,{0,40,0},1.0f,{Math::Matrix::CreateScale(0.7) * Math::Matrix::CreateTranslation(m_ded.m_pos)},{nullptr} };
	BASE m_game = { {360,Y,0},m_game.SIZE / 2,{10,270,0},1.0f,{ Math::Matrix::CreateScale(1.5) * Math::Matrix::CreateTranslation(m_game.m_pos)},{nullptr} };
	
	int rankDelay;
	float srcRank;
	float rankSize;
	float sizeMove;
	Math::Matrix rankScaleMat;
	Math::Vector3 rankRGB;
	BASE m_rank = { {100,145,0},m_rank.SIZE / 2,{200,-120,0},0.0f,{ Math::Matrix::Identity},{nullptr} };



	Math::Matrix scaleMat;

	bool gameClearFlg;
	int scoreNum;

	Scene* m_pOwner;

	BASE m_back = { {640,912,0},m_back.SIZE / 2,{0,0,0},1.0f,{ Math::Matrix::CreateTranslation(m_back.m_pos)},{nullptr} };

};