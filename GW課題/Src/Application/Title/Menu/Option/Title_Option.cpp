#include "Title_Option.h"
#include "Application/Scene.h"
#include "Application/Program/selectButton/SelectButton.h"

void C_TitleOption::Init(Scene* a_pOwner)
{
	bTapFlg = false;
	sceneOption = Volume;

	m_buttonList = make_shared<C_SelectButton>();

	m_vol = make_shared<BASE>();
	m_vol->SIZE = { 300,300,0 };
	m_vol->HALF_SIZE = m_vol->SIZE / 2;
	m_vol->m_pos = { 0.0f,0.0f,0.0f };
	m_vol->m_alpha = 0.0f;
	m_vol->m_mat = {};
	m_vol->m_pTex = &a_pOwner->GetTex()->titleOptionTex;
	m_buttonList->AddButton(m_vol);

	m_back = make_shared<BASE>();
	m_back->SIZE = { 64,64,0 };
	m_back->HALF_SIZE = m_back->SIZE / 2;
	m_back->m_pos = { 0.0f,-300.0f,0.0f };
	m_back->m_alpha = 0.0f;
	m_back->m_mat = {};
	m_back->m_pTex =&a_pOwner->GetTex()->titleBackTex;
	m_buttonList->AddButton(m_back);



	m_buttonList->Init(a_pOwner, 0.0f);
	m_buttonList->SetNum(BUTTON_NUM);
	volume = 0.25;

}

void C_TitleOption::Draw()
{
	SHADER.m_spriteShader.SetMatrix(Math::Matrix::Identity);

	Math::Color color = { 0.5f,0.5f,0.5f,0.4f };
	SHADER.m_spriteShader.DrawBox(0, 0, 640, 360, &color, true);

	color = { 0.0f,0.0f,0.0f,0.5f };
	SHADER.m_spriteShader.DrawBox(0, 0, 560, 280, &color, true);

	m_buttonList->Draw();

}

bool C_TitleOption::Update(bool a_bSpace)
{
	switch (m_buttonList->Update())
	{
	case 0://volume
		VolumeChange();
		break;

	case 1:


		if (!a_bSpace && GetAsyncKeyState(VK_SPACE) & 0x8000)
		{
			return true;
		}
		break;

	default:
		break;
	}

	if (sceneOption == Volume)
	{

	}

	return NULL;
}


//âπó í≤êÆÅô
void C_TitleOption::VolumeChange()
{
	static  int delay = 0;

	if (delay <= 0)
	{
		if ((GetAsyncKeyState(VK_LEFT) & 0x8000))
		{
			volume -= 0.05;
			if (volume <= 0)
			{
				volume = 0;
			}
			delay = 2;
		}
		else if ((GetAsyncKeyState(VK_RIGHT) & 0x8000))
		{
			volume += 0.05;
			if (volume >= 0.5)
			{
				volume = 0.5;
			}
			delay = 2;
		}
	}
	else
	{
		delay--;
	}
}
