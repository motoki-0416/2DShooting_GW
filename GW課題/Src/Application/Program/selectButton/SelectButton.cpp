#include "SelectButton.h"
#include "Application/Utility.h"
#include "Application/Scene.h"

void C_SelectButton::Init(Scene* a_pOwner, float i)
{

	nowSelect = 0;	//èâä˙
	BUTTON_NUM = 0;

	for (int i = 0; i < m_baseList.size(); i++)
	{
		m_baseList[i]->m_mat = Math::Matrix::CreateTranslation(m_baseList[i]->m_pos);
	}

	bTapFlg = false;
	m_select = { {82, 82, 0}, m_select.SIZE / 2, { m_baseList[0]->m_pos.x - m_baseList[0]->HALF_SIZE.x - 20,m_baseList[0]->m_pos.y,0 }, i, { }, { nullptr } };
	m_select.m_mat = Math::Matrix::CreateTranslation(m_select.m_pos);

	deg = 0;

	SetTex(a_pOwner);

}

int C_SelectButton::Update()
{
	if (m_select.m_alpha < 1.0f)
	{
		const float ALPHA = 0.008;
		m_select.m_alpha += ALPHA;
		for (int i = 0; i < m_baseList.size(); i++)
		{
			m_baseList[i]->m_alpha += ALPHA;
		}

		return -1;
	}

	Select();
	AlphaChange();

	return nowSelect;
}

void C_SelectButton::Draw()
{
	SHADER.m_spriteShader.SetMatrix(m_select.m_mat);
	SHADER.m_spriteShader.DrawTex(m_select.m_pTex, Math::Rectangle(0, 0, m_select.SIZE.x, m_select.SIZE.y), m_select.m_alpha);

	for (int i = 0; i < m_baseList.size(); i++)
	{

		SHADER.m_spriteShader.SetMatrix(m_baseList[i]->m_mat);
		SHADER.m_spriteShader.DrawTex(m_baseList[i]->m_pTex, Math::Rectangle(0, 0, m_baseList[i]->SIZE.x, m_baseList[i]->SIZE.y), m_baseList[i]->m_alpha);

	}
}

void  C_SelectButton::Select()
{
	if (GetAsyncKeyState(UP) & 0x8000)
	{
		if (bTapFlg)return;

		nowSelect--;

		if (nowSelect < 0)
		{

			nowSelect += BUTTON_NUM;
		}

		bTapFlg = true;

	}
	else if (GetAsyncKeyState(DOWN) & 0x8000)
	{
		if (bTapFlg)return;

		nowSelect++;

		if (nowSelect >= BUTTON_NUM)
		{
			nowSelect -= BUTTON_NUM;
		}

		bTapFlg = true;
	}
	else
	{
		bTapFlg = false;
	}


	m_select.m_pos = { m_baseList[nowSelect]->m_pos.x - m_baseList[nowSelect]->HALF_SIZE.x - 20,m_baseList[nowSelect]->m_pos.y,m_baseList[nowSelect]->m_pos.z };
	m_select.m_mat = Math::Matrix::CreateTranslation(m_select.m_pos);

	return;
}

void C_SelectButton::AlphaChange()
{

	for (int i = 0; i < m_baseList.size(); i++)
	{
		if (i == nowSelect)
		{
			deg > 180 ? deg -= 180 : deg++;
			m_baseList[i]->m_alpha = -(sin(DirectX::XMConvertToRadians(deg)) * 0.5) + 1.0f;
		}
		else
		{
			m_baseList[i]->m_alpha = 1;
		}
	}
}

void C_SelectButton::SetTex(Scene* a_pOwner)
{
	m_select.m_pTex = &a_pOwner->GetTex()->selectTex;
}

void C_SelectButton::AddButton(shared_ptr<BASE> a_obj)
{

	m_baseList.push_back(a_obj);

}
