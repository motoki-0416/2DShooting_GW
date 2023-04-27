//#include "../../Utility.h"
#include "P_Hit.h"

C_PHit::C_PHit()
{
	sizeChange = 0.0f;
}

void C_PHit::Update()
{
	m_alpha *= 0.99;
	
	if (m_size > 0)
	{
		m_size -= sizeChange;
	}

	m_color = { 1,1,1,m_alpha };
	m_data.m_pos += m_data.m_move;

	m_scaleMat = DirectX::XMMatrixScaling(m_size, m_size, 0.0f);
	m_transMat = Math::Matrix::CreateTranslation(m_data.m_pos);
	m_data.m_mat = m_scaleMat * m_transMat;

	if (m_alpha < 0.03||m_size<0)
	{
		m_bAlive = false;
	}

}

