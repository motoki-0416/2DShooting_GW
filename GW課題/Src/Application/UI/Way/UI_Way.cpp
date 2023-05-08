#include "UI_Way.h"
#include "Application/Scene/Game/Scene_Game.h"
#include "Application/Back/Back.h"
#include "Application/Scene.h"

void C_UIWay::Init()
{
	m_data.m_pos = { WAYPOS_X,200,0 };
	m_data.m_mat = Math::Matrix::CreateTranslation(m_data.m_pos);
	wayPos = { (float)WAYPOS_X,-182,0 };
}

void C_UIWay::Update(C_SceneGame* a_pOwner)
{

	wayPos.y = -146+(abs(a_pOwner->GetBackData()->GetPulsPos()) / 10);

}

void C_UIWay::Draw()
{
	SHADER.m_spriteShader.SetMatrix(Math::Matrix::Identity);

	Math::Color color = { 0.5f,0.5f,0.5f,0.3f };
	SHADER.m_spriteShader.DrawBox(WAYPOS_X, 0, 30, 170, &color, true);

	color = { 0.5f,0.5f,0.5f,1.0f };
	SHADER.m_spriteShader.DrawBox(WAYPOS_X, 0, 10, 146, &color, true);


	SHADER.m_spriteShader.SetMatrix(Math::Matrix::Identity);
	color = { 0.5f,1.0f,0.5f,1.0f };
	SHADER.m_spriteShader.DrawCircle(wayPos.x, wayPos.y, 10, &color, true);


	SHADER.m_spriteShader.SetMatrix(m_data.m_mat);
	SHADER.m_spriteShader.DrawTex(m_data.m_pTex, Math::Rectangle{ 0,0,(long)m_data.SIZE.x,(long)m_data.SIZE.y }, m_data.m_alpha);


}

void C_UIWay::SetTex(Scene* a_pOwner)
{

	m_data.m_pTex = &a_pOwner->GetTex()->bossIconTex;

}
