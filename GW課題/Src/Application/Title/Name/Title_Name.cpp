#include "Title_Name.h"
#include "Application/Scene.h"

void C_TitleName::Init()
{
	delay = MAX_DELAY;
	m_bAlpha = false;
}

void C_TitleName::Draw()
{
	SHADER.m_spriteShader.SetMatrix(m_name.m_mat);
	SHADER.m_spriteShader.DrawTex(m_name.m_pTex, Math::Rectangle(0, 0, m_name.SIZE.x, m_name.SIZE.y), m_name.m_alpha);
}

bool C_TitleName::Update(bool a_bSpace)
{
	//アルファ値の変更
	if (m_bAlpha)
	{
		if (m_name.m_alpha <= MIN_ALPHA)
		{
			//タイトル終了
			return true;
		}
		else
		{
			m_name.m_alpha -= CHANGE_ALPHA;
		}
	}
	else
	{
		if (m_name.m_alpha < MAX_ALPHA&& delay<=MIN_ALPHA)
		{
			m_name.m_alpha += CHANGE_ALPHA;
		}
		else
		{
			delay--;
		}
	}

	//スペースを押したらアルファ値を1に/タイトルを終わる
	if (!a_bSpace && GetAsyncKeyState(VK_SPACE) & 0x8000&&!m_bAlpha)
	{
		if (m_name.m_alpha < MAX_ALPHA)
		{
			m_name.m_alpha = MAX_ALPHA;
		}
		else
		{
			m_bAlpha = true;
		}
		a_bSpace = true;
	}

	

	return NULL;
}

void C_TitleName::SetTex(Scene* a_pOwner)
{
	m_name.m_pTex = &a_pOwner->GetTitleTex()->titleNameTex;
}
