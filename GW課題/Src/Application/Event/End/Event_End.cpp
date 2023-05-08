#include "Event_End.h"
#include "Application/Scene/Game/Scene_Game.h"
#include "Application/BlackOut/BlackOut.h"
#include "Application/Object/BaseObject.h"
#include "Application/Object/Enemy/MiniBoss/MiniBoss.h"

void C_EventEnd::Init()
{
	boxAlpha = 0.0f;
	delay = 0.0f;
	alpha_Change = -1;

}

void C_EventEnd::Update()
{
	delay++;

	if (delay < 120.0f)
	{

		if (delay % 30)
		{

			alpha_Change *= -1;

		}

		boxAlpha += (0.05f * alpha_Change);

	}
	else
	{

		if (boxAlpha < 1.5f)
		{

			boxAlpha += 0.01f;

		}
		else if(m_gameScene->GetBlackOutData()->ChangeAlpha(true))
		{
			m_bDeleteFlg = true;

		}


	}

}

void C_EventEnd::Draw()
{

	SHADER.m_spriteShader.SetMatrix(Math::Matrix::Identity);
	Math::Color color = { 1.0f,1.0f,1.0f, boxAlpha };
	SHADER.m_spriteShader.DrawBox(0, 0, 640, 360, &color, true);


	SHADER.m_spriteShader.SetMatrix(m_data.m_mat);
	SHADER.m_spriteShader.DrawTex(m_data.m_pTex, Math::Rectangle(0, 0, m_data.SIZE.x, m_data.SIZE.y), 1.0f);

}
