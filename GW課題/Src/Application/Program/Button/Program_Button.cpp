#include "Application/Program/Button/Program_Button.h"

void C_Button::Update()
{
	if (GetAsyncKeyState(m_name) & 0x8000)
	{
		switch (m_state)
		{
		case Free:
			m_state = Press;
			break;
		case Press:
			m_state = Hold;
			break;
		default:
			break;
		}
	}
	else
	{
		if (m_state == Hold)
		{
			m_state = Release;
		}
		else
		{
			m_state = Free;
		}

	}
}
