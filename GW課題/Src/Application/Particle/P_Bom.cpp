//#include "../../Utility.h"
#include "P_Bom.h"

C_PBom::C_PBom()
{
	delay = 0;
	animation = 0;
	m_data.SIZE = { 64,64 };
	m_data.HALF_SIZE = { m_data.SIZE.x / 2,m_data.SIZE.y / 2 };
}

void C_PBom::Update()
{
	Animetion();

	//íœ
	if (animation>MAX_ANIME)
	{
		m_bAlive = false;
	}

	m_data.m_pos += m_data.m_move;

	m_scaleMat = DirectX::XMMatrixScaling(m_size, m_size, 0.0f);
	m_transMat = Math::Matrix::CreateTranslation(m_data.m_pos);
	m_data.m_mat = m_scaleMat * m_transMat;

	delay--;
}


void C_PBom::Draw()
{
	if (!m_bAlive)return;
	SHADER.m_spriteShader.SetMatrix(m_data.m_mat);
	m_srcRect = { 64 * animation ,0,64,64 };
	SHADER.m_spriteShader.DrawTex(m_data.m_pTex,0 , 0, 64, 64, &m_srcRect, &m_color);
}
void C_PBom::Animetion()
{
	if (delay > 0)return;
	delay = DLEAY_MAX;
	m_srcRect = { (int)(m_data.SIZE.x * animation),0,(int)m_data.SIZE.x,(int)m_data.SIZE.y };
	animation++;
}