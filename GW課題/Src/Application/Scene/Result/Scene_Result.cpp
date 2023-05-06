#include "Application/Scene/Result/Scene_Result.h"
#include "Application/Result/Number/Result_Number.h"
#include "Application/Result/Return/ReturnButton.h"
#include "Application/Scene.h"
#include "Application/BlackOut/BlackOut.h"
#include "Math.h"

void C_SceneResult::Init(Scene* a_pOwner)
{
	m_pOwner = a_pOwner;

	static const int NUMBER_POS = 110;

	shared_ptr<C_ResultNumber> tmpA = make_shared<C_ResultNumber>();
	tmpA->Init(a_pOwner,score );
	tmpA->SetPos({ NUMBER_POS,100,0 });
	m_number.push_back(tmpA);


	shared_ptr<C_ResultNumber> tmpB = make_shared<C_ResultNumber>();
	tmpB->Init(a_pOwner, enemyDedNum);
	tmpB->SetPos({ NUMBER_POS,0,0 });
	m_number.push_back(tmpB);


	shared_ptr<C_ResultNumber> tmpC = make_shared<C_ResultNumber>();
	tmpC->Init(a_pOwner, scoreNum);
	tmpC->SetPos({ NUMBER_POS,-100,0 });
	m_number.push_back(tmpC);

	m_button = make_shared<C_ReturnButton>();
	m_button->Init(a_pOwner);

	SetTex(a_pOwner);

}

void C_SceneResult::Update()
{
	static bool bSpace = false;

	for (int i = 0; i < m_number.size(); i++)
	{
	
		m_number[i]->Update();
	
	}

	if (m_button->Update(bSpace, this))
	{
		if (m_blackOut->ChangeAlpha(true))
		{
			sceneChange = true;
		}
	}
	else
	{
		m_blackOut->ChangeAlpha(false);
	}


	GetAsyncKeyState(VK_SPACE) & 0x8000 ? bSpace = true : bSpace = false;
}

void C_SceneResult::Draw()
{
	SHADER.m_spriteShader.SetMatrix(m_back.m_mat);
	SHADER.m_spriteShader.DrawTex(m_back.m_pTex, Math::Rectangle{ 0,0,(long)m_back.SIZE.x,(long)m_back.SIZE.y }, 1.0f);


	for (int i = 0; i < m_number.size(); i++)
	{
		m_number[i]->Draw();
	}

	m_button->Draw();

	Math::Color color = { 0,0,0,1 };
	SHADER.m_spriteShader.SetMatrix(Math::Matrix::Identity);
	SHADER.m_spriteShader.DrawBox(-480, 0, 160, 360, &color, true);
	SHADER.m_spriteShader.DrawBox(480, 0, 160, 360, &color, true);

	m_blackOut->Draw();

}

void C_SceneResult::SetTex(Scene* a_pOwner)
{

	m_back.m_pTex = &a_pOwner->GetTex()->resultTex;

}

void C_SceneResult::SetResult(int a_score, int a_enemyNum)
{

	score = a_score;

	enemyDedNum = a_enemyNum;

	scoreNum = score + (enemyDedNum * 10000);

}

