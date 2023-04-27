#include "Title_Option.h"
#include "Application/Scene.h"

void C_TitleOption::Init()
{
	bTapFlg = false;
	sceneOption = Volume;

	m_option= { {128,72,0},m_option.SIZE / 2,{0,0,0},MAX_ALPHA,{Math::Matrix::CreateTranslation(m_option.m_pos)},{nullptr} };
	m_back = { {64,64,0},m_back.SIZE / 2,{0,-200,0},MAX_ALPHA,{Math::Matrix::CreateTranslation(m_back.m_pos)},{nullptr} };

	m_select = { {64,64,0},m_select.SIZE / 2,{-100,m_option.m_pos.y,0},MAX_ALPHA,{Math::Matrix::CreateTranslation(m_select.m_pos)},{nullptr} };

	volume = 0.25;
}

void C_TitleOption::Draw()
{
	SHADER.m_spriteShader.SetMatrix(Math::Matrix::Identity);

	Math::Color color = { 0.5f,0.5f,0.5f,0.4f };
	SHADER.m_spriteShader.DrawBox(0, 0, 640, 360, &color, true);

	color = { 0.0f,0.0f,0.0f,0.5f };
	SHADER.m_spriteShader.DrawBox(0, 0, 560, 280, &color, true);

	SHADER.m_spriteShader.SetMatrix(m_option.m_mat);
	SHADER.m_spriteShader.DrawTex(m_option.m_pTex, Math::Rectangle(0, 0, m_option.SIZE.x, m_option.SIZE.y), m_option.m_alpha);

	SHADER.m_spriteShader.SetMatrix(m_back.m_mat);
	SHADER.m_spriteShader.DrawTex(m_back.m_pTex, Math::Rectangle(0, 0, m_back.SIZE.x, m_back.SIZE.y), m_back.m_alpha);

	//ëIëñÓàÛ
	SHADER.m_spriteShader.SetMatrix(m_select.m_mat);
	SHADER.m_spriteShader.DrawTex(m_select.m_pTex, Math::Rectangle(0, 0, m_select.SIZE.x, m_select.SIZE.y), m_select.m_alpha);
}

bool C_TitleOption::Update(bool a_bSpace)
{
	Select();

	if (sceneOption == Volume)
	{
		VolumeChange();
	}

	if (sceneOption==Back&&!a_bSpace && GetAsyncKeyState(VK_SPACE) & 0x8000)
	{
		return true;
	}

	return NULL;
}

void C_TitleOption::SetTex(Scene* a_pOwner)
{
	m_option.m_pTex = &a_pOwner->GetTitleTex()->titleOptionTex;
	m_back.m_pTex = &a_pOwner->GetTitleTex()->titleBackTex;
	m_select.m_pTex = &a_pOwner->GetTitleTex()->titileSelectTex;
}

void C_TitleOption::Select()
{
	if ((GetAsyncKeyState(VK_UP) & 0x8000 || GetAsyncKeyState(VK_DOWN) & 0x8000))
	{

		if (bTapFlg)return;

		switch (sceneOption)
		{
		case Volume:
			m_select.m_pos.y = m_back.m_pos.y;
			m_select.m_mat = Math::Matrix::CreateTranslation(m_select.m_pos);
			sceneOption = Back;
			break;

		case Back:
			m_select.m_pos.y = m_option.m_pos.y;
			m_select.m_mat = Math::Matrix::CreateTranslation(m_select.m_pos);
			sceneOption = Volume;
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

//âπó í≤êÆÅô
void C_TitleOption::VolumeChange()
{
	static  int delay=0;

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
