
#include "Result_Number.h"
#include "Application/Scene.h"
#include "math.h"

void C_ResultNumber::Init(Scene* a_pOwner, int a_score)
{
	for (int i = 0; i < NUMBER_NUM; i++)
	{
		m_number[i] = { {32,32,0},m_number[i].SIZE / 2,{},1.0f,{Math::Matrix::Identity},nullptr };

		m_src[i].numSrc = 0;
	}

	scoreList = a_score;

	scaleMat = Math::Matrix::CreateScale(1.8);

	SetTex(a_pOwner);

}

void C_ResultNumber::Update()
{

	//スコア計算
	for (int i = 0; i < NUMBER_NUM; i++)
	{

		m_src[i].numSrc = scoreList / pow(10, i);
		m_src[i].numSrc %= 10;

		m_number[i].m_mat = scaleMat*Math::Matrix::CreateTranslation(m_number[i].m_pos);

	}

}

void C_ResultNumber::Draw()
{
	for (int i = 0; i < NUMBER_NUM; i++)
	{

		SHADER.m_spriteShader.SetMatrix(m_number[i].m_mat);

		SHADER.m_spriteShader.DrawTex(m_pNumberTex, Math::Rectangle{ (long)m_number[i].SIZE.x * m_src[i].numSrc,0,(long)m_number[i].SIZE.x,(long)m_number[i].SIZE.y }, 1.0f);

	}

}

void C_ResultNumber::SetTex(Scene* a_pOwner)
{

	m_pNumberTex = &a_pOwner->GetTex()->numberTex;

}

void C_ResultNumber::SetPos(Math::Vector3 a_pos)
{
	for (int i = 0; i < NUMBER_NUM; i++)
	{

		m_number[i].m_pos = { a_pos.x - (m_number[i].SIZE.x * i - i ),a_pos.y,a_pos.z };

	}
}
