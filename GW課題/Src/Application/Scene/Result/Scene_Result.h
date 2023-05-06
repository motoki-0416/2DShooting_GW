#pragma once
#include "Application/Scene/BaseScene.h"
#include "Application/Utility.h"

class Scene;
class C_ReturnButton;
class C_ResultNumber;

class C_SceneResult :public C_BaseScene
{
public:

	C_SceneResult() {};
	~C_SceneResult() {};


	void Init(Scene* a_pOwner)override;
	void Update()override;
	void Draw()override;

	void SetTex(Scene* a_pOwner)override;

	void SetResult(int a_score, int a_enemyNum) override;


private:

	vector<shared_ptr<C_ResultNumber>> m_number;
	shared_ptr<C_ReturnButton> m_button;

	int scoreNum;

	Scene* m_pOwner;

	BASE m_back = { {640,912,0},m_back.SIZE / 2,{0,0,0},1.0f,{ Math::Matrix::CreateTranslation(m_back.m_pos)},{nullptr} };

};