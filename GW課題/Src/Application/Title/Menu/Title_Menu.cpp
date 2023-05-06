#include "Title_Menu.h"
#include "Application/Scene.h"
#include "Application/Program/selectButton/SelectButton.h"
#include "Application/Title/Menu/Option/Title_Option.h"

void C_TitleMenu::Init(Scene* a_pOwner)
{
	m_option = make_shared<C_TitleOption>();
	m_option->Init(a_pOwner);

	bAlpha = false;
	bStartFlg = false;
	bOptionFlg = false;

	m_buttonList = make_shared<C_SelectButton>();


	m_startButton = make_shared<BASE>();
	m_startButton->SIZE = { 173,82,0 };
	m_startButton->HALF_SIZE = m_startButton->SIZE / 2;
	m_startButton->m_pos = { 0,0,0 };
	m_startButton->m_alpha = 0.0f;
	m_startButton->m_mat = {};
	m_startButton->m_pTex = &a_pOwner->GetTex()->titleStartTextTex;
	m_buttonList->AddButton(m_startButton);

	m_optionButton = make_shared<BASE>();
	m_optionButton->SIZE = { 200,82,0 };
	m_optionButton->HALF_SIZE = m_optionButton->SIZE / 2;
	m_optionButton->m_pos = { 0,-100,0 };
	m_optionButton->m_alpha = 0.0f;
	m_optionButton->m_mat = {};
	m_optionButton->m_pTex = &a_pOwner->GetTex()->titleOptionTextTex;
	m_buttonList->AddButton(m_optionButton);


	m_buttonList->Init(a_pOwner, 0.0f);
	m_buttonList->SetNum(BUTTON_NUM);

}

void C_TitleMenu::Draw()
{

	if (!bOptionFlg)
	{

		m_buttonList->Draw();

	}
	else
	{

		m_option->Draw();

	}

}

bool C_TitleMenu::Update(bool a_bSpace)
{
	if (bStartFlg)
	{
		return true;
	}

	if (m_buttonList->Update() < 0)return NULL;

	if (bOptionFlg)
	{
		if (m_option->Update(a_bSpace))
		{
			bOptionFlg = false;
		}
	}
	else
	{

		switch (m_buttonList->Update())
		{
		case 0:

			if (!a_bSpace && GetAsyncKeyState(VK_SPACE) & 0x8000 && !bOptionFlg)
			{
				bStartFlg = true;
			}

			break;

		case 1:

			if (!a_bSpace && GetAsyncKeyState(VK_SPACE) & 0x8000)
			{
				bOptionFlg = true;
				a_bSpace = true;
			}

			break;

		default:
			break;
		}
	}

	return NULL;
}
