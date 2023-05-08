#include "UI_HP.h"
#include "Application/Scene/Game/Scene_Game.h"
#include "Application/Scene.h"

void C_UIHP::Init()
{
	color = { 0.1f,1.0f,0.1f,1.0f };
}

void C_UIHP::Update(C_SceneGame* a_pOwner)
{
	int a_hp = a_pOwner->GetPlayer()->GetHP();

	m_width=a_hp;
	if (a_hp < 10)
	{
		color = { 1.0f,0.1f,0.1f,1.0f };
	}
	else 	if (a_hp < 30)
	{
		color = { 1.0f,1.0f,0.1f,1.0f };
	}


}

void C_UIHP::Draw()
{

	SHADER.m_spriteShader.SetMatrix(Math::Matrix::Identity);

	SHADER.m_spriteShader.DrawBox(500, 50, m_width, 20, &color, true);

	Math::Color flamecolor = { 1.0f, 1.0f, 1.0f, 1.0f };

	SHADER.m_spriteShader.DrawBox(500, 50, 80, 20, &flamecolor, false);
	
}
