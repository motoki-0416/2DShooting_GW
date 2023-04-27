//#include "../../Utility.h"
#include "P_Shine.h"

C_PShine::C_PShine()
{
	alphaFlg = false;
	m_alpha = 0.0f;
	m_data.SIZE = { 16,16 };
}

void C_PShine::Update()
{
	if (m_alpha<1.0f&&!alphaFlg)
	{
		m_alpha += 0.05;
	}
	else
	{
		m_alpha -= 0.05;
		alphaFlg = true;
	}
	if (alphaFlg <= 0.0f && alphaFlg)
	{
		m_bAlive = false;
	}


	m_data.m_pos += m_data.m_move;

	m_scaleMat=DirectX::XMMatrixScaling(m_size, m_size, 0.0f);
	m_transMat = Math::Matrix::CreateTranslation(m_data.m_pos);
	m_data.m_mat = m_scaleMat * m_transMat;
}


void C_PShine::Draw()
{
	if (!m_bAlive)return;
	SHADER.m_spriteShader.SetMatrix(m_data.m_mat);
	m_color = { 1.0f,1.0f,1.0f,1.0f};
	m_srcRect = { 0,0,16,16 };
	SHADER.m_spriteShader.DrawTex(m_data.m_pTex, 0, 0, 16, 16, &m_srcRect, &m_color);
}