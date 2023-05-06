#include "Title_Name.h"
#include "Application/Scene.h"

void C_TitleName::Init()
{
	delay = MAX_DELAY;
	m_bAlpha = false;
	m_bFlg = false;
	deg = 0;

	m_name.m_mat = Math::Matrix::CreateTranslation(m_name.m_pos);

	m_push.m_mat = Math::Matrix::CreateTranslation(m_push.m_pos);
}

void C_TitleName::Draw()
{

	SHADER.m_spriteShader.SetMatrix(m_name.m_mat);
	SHADER.m_spriteShader.DrawTex(m_name.m_pTex, Math::Rectangle(0, 0, m_name.SIZE.x, m_name.SIZE.y), m_name.m_alpha);


	SHADER.m_spriteShader.SetMatrix(m_push.m_mat);
	SHADER.m_spriteShader.DrawTex(m_push.m_pTex, Math::Rectangle(0, 0, m_push.SIZE.x, m_push.SIZE.y), m_push.m_alpha);

}

bool C_TitleName::Update(bool a_bSpace)
{
	//アルファ値の変更
	if (m_bAlpha)
	{
		if (m_name.m_alpha <= MIN_ALPHA && m_push.m_alpha <= MIN_ALPHA)
		{
			//タイトル終了
			return true;
		}
		else
		{
			m_name.m_alpha -= CHANGE_ALPHA;
			m_push.m_alpha -= CHANGE_ALPHA;
		}
	}
	else
	{
		//タイトルアルファ値上昇
		if (m_name.m_alpha < MAX_ALPHA && delay <= MIN_ALPHA)
		{
			m_name.m_alpha += CHANGE_ALPHA;
		}
		else delay--;


		//PUSHのアルファ値
		if (m_name.m_alpha >= MAX_ALPHA && m_push.m_alpha <= MAX_ALPHA)
		{

			m_push.m_alpha += CHANGE_ALPHA;

		}

		if (m_name.m_alpha >= MAX_ALPHA && m_push.m_alpha >= MAX_ALPHA)m_bFlg = true;
		

		if (m_bFlg)
		{
			deg > 180 ? deg -= 180 : deg++;
  			m_push.m_alpha = -(sin(DirectX::XMConvertToRadians(deg))*0.5)+1.0f;
		}

	}

	//スペースを押したらアルファ値を1に/タイトルを終わる
	if (!a_bSpace && GetAsyncKeyState(VK_SPACE) & 0x8000 && !m_bAlpha)
	{
		if (!m_bFlg)
		{
			m_name.m_alpha = MAX_ALPHA;
			m_push.m_alpha = MAX_ALPHA;
			m_bFlg = true;
		}
		else
		{
			m_name.m_alpha = MAX_ALPHA;
			m_push.m_alpha = MAX_ALPHA;
			m_bAlpha = true;
		}
		a_bSpace = true;
	}



	return NULL;
}

void C_TitleName::SetTex(Scene* a_pOwner)
{
	m_name.m_pTex = &a_pOwner->GetTex()->titleNameTex;

	m_push.m_pTex = &a_pOwner->GetTex()->titlePushSpace;
}
