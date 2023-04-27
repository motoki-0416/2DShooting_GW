#include "Title.h"
#include"Application/Scene.h"

void C_Title::Init()
{
	sceneTitle = Name;
	m_menu.Init();
	m_name.Init();
}

void C_Title::Draw()
{
	DrawTitle();

	switch (sceneTitle)
	{
	case Name:
		m_name.Draw();
		break;

	case Menu:
		m_menu.Draw();
		break;

	default:
		break;
	}	
}

void C_Title::DrawTitle()
{
	SHADER.m_spriteShader.SetMatrix(m_back.m_mat);
	SHADER.m_spriteShader.DrawTex(m_back.m_pTex, Math::Rectangle(0, 0, m_back.SIZE.x, m_back.SIZE.y), m_back.m_alpha);
}


bool C_Title::Update(bool a_bSpace)
{
	switch (sceneTitle)
	{
	case Name:
		if (m_name.Update(a_bSpace))
		{
			sceneTitle = Menu;
		}
		break;
	case Menu:
		if (m_menu.Update(a_bSpace))return true;
		break;
	default:
		break;
	}

	return NULL;
}

void C_Title::SetTex(Scene* a_pOwner)
{
	m_back.m_pTex = &a_pOwner->GetTitleTex()->titleBackGroundTex;
	m_name.SetTex(a_pOwner);
	m_menu.SetTex(a_pOwner);
}
