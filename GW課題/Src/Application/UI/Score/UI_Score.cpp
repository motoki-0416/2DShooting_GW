#include "UI_Score.h"
#include "Application/Scene.h"
#include "Application/Scene/Game/Scene_Game.h"
#include "math.h"

void C_UIScore::Init()
{
	for (int i = 0; i < NUMBER_NUM; i++)
	{
		m_number[i] = {{32,32,0},m_number[i].SIZE / 2,{},1.0f,{Math::Matrix::Identity},nullptr};

		m_number[i].m_pos = { 600-(m_number[i].SIZE.x * i-i*12),0,0};

		m_src[i].numSrc = 0;
	}

}

void C_UIScore::Update(C_SceneGame* a_pOwner)
{

	scoreList = a_pOwner->GetScore();

	//スコア計算
	for (int i = 0; i < NUMBER_NUM; i++)
	{
		

		m_src[i].numSrc = scoreList / pow(10, i);
		m_src[i].numSrc %= 10;

		m_number[i].m_mat = Math::Matrix::CreateTranslation(m_number[i].m_pos);
	

	}

}

void C_UIScore::Draw()
{
	for (int i = 0; i < NUMBER_NUM; i++)
	{
	
		SHADER.m_spriteShader.SetMatrix(m_number[i].m_mat);
		
		SHADER.m_spriteShader.DrawTex(m_data.m_pTex, Math::Rectangle{(long) m_number[i].SIZE.x *m_src[i].numSrc,0,(long)m_number[i].SIZE.x,(long)m_number[i].SIZE.y}, 1.0f);
	
	}

}

void C_UIScore::SetTex(Scene* a_pOwner)
{

	m_data.m_pTex = &a_pOwner->GetTex()->numberTex;

}
