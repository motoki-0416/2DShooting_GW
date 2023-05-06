#include "UI.h"
#include "Application/UI/HP/UI_HP.h"
#include "Application/UI/Score/UI_Score.h"
#include "Application/Scene/Game/Scene_Game.h"

void C_UI::Init()
{
	shared_ptr<C_UIHP> hp = make_shared<C_UIHP>();
	m_uiList.push_back(hp);

	shared_ptr<C_UIScore> sc = make_shared<C_UIScore>();
	m_uiList.push_back(sc);
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

}

void C_UI::SetTex(Scene* a_pOwner)
{

	for (int i = 0; i < m_uiList.size(); i++)
	{
		m_uiList[i]->SetTex(a_pOwner);
	}
}
