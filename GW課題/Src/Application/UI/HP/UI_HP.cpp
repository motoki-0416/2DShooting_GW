#include "UI_HP.h"
#include "Application/Scene/Game/Scene_Game.h"
#include "Application/Scene.h"

void C_UIHP::Update(C_SceneGame* a_pOwner)
{

	m_width=a_pOwner->GetPlayer()->GetHP();

}

void C_UIHP::Draw()
{

	SHADER.m_spriteShader.SetMatrix(Math::Matrix::Identity);

	Math::Color color = { 0.3f,0.3f,0.3f,1.0f };

	SHADER.m_spriteShader.DrawBox(500, 200, m_width, 20, &color, true);

	color = { 1.0f, 1.0f, 1.0f, 1.0f };

	SHADER.m_spriteShader.DrawBox(500, 200, 100, 20, &color, false);
	
}
