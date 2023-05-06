//#include "../../Utility.h"
#include "P_Hit.h"

C_PHit::C_PHit()
{
	sizeChange = 0.0f;
}

void C_PHit::Update()
{
	m_data.m_alpha *= 0.99;
	
	if (m_size > 0)
	{
		m_size -= sizeChange;
	}

	m_color = { 1,1,1,m_data.m_alpha };
	
	if (m_data.m_alpha < 0.03||m_size<0)
	{
		m_bAlive = false;
	}

}

