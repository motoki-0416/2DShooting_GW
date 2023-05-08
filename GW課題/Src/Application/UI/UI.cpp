#include "UI.h"
#include "Application/UI/HP/UI_HP.h"
#include "Application/UI/Score/UI_Score.h"
#include "Application/UI/Way/UI_Way.h"
#include "Application/Scene.h"
#include "Application/Scene/Game/Scene_Game.h"

void C_UI::Init()
{
	shared_ptr<C_UIHP> hp = make_shared<C_UIHP>();
	m_uiList.push_back(hp);

	shared_ptr<C_UIScore> sc = make_shared<C_UIScore>();
	m_uiList.push_back(sc);

	shared_ptr<C_UIWay>wa = make_shared<C_UIWay>();
	m_uiList.push_back(wa);

}

void C_UI::Update(C_SceneGame* a_pOwner)
{

	for (int i = 0; i < m_uiList.size(); i++)
	{

		m_uiList[i]->Update(a_pOwner);
	
	}

}

void C_UI::Draw()
{

	for (int i = 0; i < m_uiList.size(); i++)
	{
	
		m_uiList[i]->Draw();

	}

	SHADER.m_spriteShader.SetMatrix(m_score.m_mat);
	SHADER.m_spriteShader.DrawTex(m_score.m_pTex, Math::Rectangle(0, 0, m_score.SIZE.x, m_score.SIZE.y), m_score.m_alpha);

	SHADER.m_spriteShader.SetMatrix(m_hp.m_mat);
	SHADER.m_spriteShader.DrawTex(m_hp.m_pTex, Math::Rectangle(0, 0, m_hp.SIZE.x, m_hp.SIZE.y), m_hp.m_alpha);

}

void C_UI::SetTex(Scene* a_pOwner)
{

	for (int i = 0; i < m_uiList.size(); i++)
	{
		m_uiList[i]->SetTex(a_pOwner);
	}

	m_hp.m_pTex = &a_pOwner->GetTex()->m_hpTex;
	m_score.m_pTex = &a_pOwner->GetTex()->m_scoreTex;
}
