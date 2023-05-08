#pragma once
#include "Application/Utility.h"
using namespace std;

class C_BaseUI;
class C_SceneGame;
class Scene;

class C_UI
{
public:

	C_UI() { Init(); }
	~C_UI(){}


	void Init();
	void Update(C_SceneGame* a_pOwner);
	void Draw();

	void SetTex(Scene* a_pOwner);


private:

	BASE m_hp= { {111,100,0},m_hp.SIZE / 2,{500,120,0},1.0f,{Math::Matrix::CreateTranslation(m_hp.m_pos)},nullptr};
	BASE m_score= { {211,100,0},m_score.SIZE / 2,{500,-50,0},1.0f,{Math::Matrix::CreateTranslation(m_score.m_pos)},nullptr };

	vector<shared_ptr<C_BaseUI>> m_uiList;

};