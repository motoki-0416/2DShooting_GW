#include "BaseUI.h"
#include "Application/Scene/Game/Scene_Game.h"

void C_BaseUI::Init()
{
}

void C_BaseUI::Update(C_SceneGame* a_pOwner)
{
}

void C_BaseUI::Draw()
{
	SHADER.m_spriteShader.SetMatrix(m_data.m_mat);
	SHADER.m_spriteShader.DrawTex(m_data.m_pTex, Math::Rectangle{ 0,0,(long)m_data.SIZE.x,(long)m_data.SIZE.y }, 1.0f);
}
