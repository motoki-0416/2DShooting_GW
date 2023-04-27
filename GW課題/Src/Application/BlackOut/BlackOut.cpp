#include"BlackOut.h"

void C_BlackOut::Init()
{
	blackAlpha = 0.0f;
	bAlphaFlg = false;
}

void C_BlackOut::Update()
{
}

bool C_BlackOut::ChangeAlpha(bool a_flg)
{
	if (!a_flg)
	{
		blackAlpha -= CHANGE_ALPHA;
		if (blackAlpha <= MIN_ALPHA)
		{
			blackAlpha = MIN_ALPHA;
			return true;
		}
	}
	else if(a_flg)
	{
		blackAlpha += CHANGE_ALPHA;
		if (blackAlpha >= MAX_ALPHA)
		{
			blackAlpha = MAX_ALPHA;
			return true;
	}
	}

	return NULL;
}

void C_BlackOut::Draw()
{
	SHADER.m_spriteShader.SetMatrix(Math::Matrix::Identity);
	Math::Color color = { 0.0f,0.0f,0.0f,blackAlpha };
  	SHADER.m_spriteShader.DrawBox(0, 0, HALF_WIDTH, HALF_HEIGHT, &color, true);
}
