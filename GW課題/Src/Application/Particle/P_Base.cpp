#include "P_Base.h"

C_BaseParticle::C_BaseParticle()
{
	m_size = 1.0f;
	m_bAlive = true;
	m_color = { 1,1,1,m_data.m_alpha };
}

void C_BaseParticle::Draw()
{
	if (!m_bAlive)return;

	SHADER.m_spriteShader.SetMatrix(m_data.m_mat);
	Math::Rectangle srcRect = { 0,0,(long)m_data.SIZE.x,(long)m_data.SIZE.x };
	SHADER.m_spriteShader.DrawTex(m_data.m_pTex, 0, 0, m_data.SIZE.x, m_data.SIZE.y, &srcRect, &m_color);
}

void C_BaseParticle::CommitPos(Math::Vector3 a_move)
{
	m_data.m_pos += m_data.m_move+a_move;

	m_scaleMat = DirectX::XMMatrixScaling(m_size, m_size, 0.0f);
	m_transMat = Math::Matrix::CreateTranslation(m_data.m_pos);
	m_data.m_mat = m_scaleMat * m_transMat;
}
