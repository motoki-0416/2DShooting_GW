#include "Title_Menu.h"
#include "Application/Scene.h"

void C_TitleMenu::Init()
{
	m_option.Init();

	bAlpha = false;
	bTapFlg = false;
	bStartFlg = false;
	bOptionFlg = false;

}

void C_TitleMenu::Draw()
{
	//SHADER.m_spriteShader.SetMatrix(m_menu.m_mat);
	//SHADER.m_spriteShader.DrawTex(m_menu.m_pTex, Math::Rectangle(0, 0, m_menu.SIZE.x, m_menu.SIZE.y), 1.0f);

	SHADER.m_spriteShader.SetMatrix(m_startText.m_mat);
	SHADER.m_spriteShader.DrawTex(m_startText.m_pTex, Math::Rectangle(0, 0, m_startText.SIZE.x, m_startText.SIZE.y), m_startText.m_alpha);

	SHADER.m_spriteShader.SetMatrix(m_optionText.m_mat);
	SHADER.m_spriteShader.DrawTex(m_optionText.m_pTex, Math::Rectangle(0, 0, m_optionText.SIZE.x, m_optionText.SIZE.y), m_optionText.m_alpha);

	if (!bOptionFlg)
	{
		SHADER.m_spriteShader.SetMatrix(m_select.m_mat);
		SHADER.m_spriteShader.DrawTex(m_select.m_pTex, Math::Rectangle(0, 0, m_select.SIZE.x, m_select.SIZE.y), m_select.m_alpha);
	}
	else
	{
		m_option.Draw();
	}
}

bool C_TitleMenu::Update(bool a_bSpace)
{
	if (bStartFlg)
	{
		return true;
	}



	if (!bAlpha)
	{
		AlphaChange(&m_startText);
		AlphaChange(&m_optionText);
		AlphaChange(&m_select);
		if (m_select.m_alpha >= MAX_ALPHA)
		{
			bAlpha = true;
		}
	}
	else
	{
		//スタートボタンを押したら
		if (sceneSelect == Start && !bOptionFlg)
		{
			if (!a_bSpace && GetAsyncKeyState(VK_SPACE) & 0x8000)
			{
				bStartFlg = true;
			}

		}

		UpdateOption(a_bSpace);

		if (!bOptionFlg)
		{
			SelectMenu();
		}
	}
	return NULL;
}

void C_TitleMenu::UpdateOption(bool a_bSpace)
{

	if (sceneSelect == Option && !bOptionFlg)
	{
		if (!a_bSpace && GetAsyncKeyState(VK_SPACE) & 0x8000)
		{
			bOptionFlg = true;
			a_bSpace = true;
		}
	}

	if (bOptionFlg)
	{
		if (m_option.Update(a_bSpace))
		{
			bOptionFlg = false;
		}
	}
}

void C_TitleMenu::SelectMenu()
{
	if ((GetAsyncKeyState(VK_UP) & 0x8000 || GetAsyncKeyState(VK_DOWN) & 0x8000))
	{
		if (bTapFlg)return;

		switch (sceneSelect)
		{
		case Start:
			m_select.m_pos.y = m_optionText.m_pos.y;
			m_select.m_mat = Math::Matrix::CreateTranslation(m_select.m_pos);
			sceneSelect = Option;
		
			break;
		case Option:
			m_select.m_pos.y = m_startText.m_pos.y;
			m_select.m_mat = Math::Matrix::CreateTranslation(m_select.m_pos);
			sceneSelect = Start;
			break;
		default:
			break;
		}
		bTapFlg = true;
	}
	else
	{
		bTapFlg = false;
	}
}

void C_TitleMenu::AlphaChange(BASE* a_data, bool a_bool)
{
	if (a_bool)
	{
		if (a_data->m_alpha < MAX_ALPHA)
		{
			a_data->m_alpha += CHANGE_ALPHA;
		}
		else
		{
			a_data->m_alpha = MAX_ALPHA;
		}
	}
	else
	{
		if (a_data->m_alpha > MIN_ALPHA)
		{
			a_data->m_alpha -= CHANGE_ALPHA;
		}
		else
		{
			a_data->m_alpha == MIN_ALPHA;
		}
	}
}

void C_TitleMenu::SetTex(Scene* a_pOwner)
{
	//m_menu.m_pTex = &a_pOwner->GetTitleTex()->titleStartTextTex;
	m_startText.m_pTex = &a_pOwner->GetTitleTex()->titleStartTextTex;
	m_optionText.m_pTex = &a_pOwner->GetTitleTex()->titleOptionTextTex;
	m_select.m_pTex = &a_pOwner->GetTitleTex()->titileSelectTex;
	m_option.SetTex(a_pOwner);
}
