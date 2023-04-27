#pragma once
#include "Application/Utility.h"
#include "../P_Base.h"

class C_PShine :public C_BaseParticle
{
public:
	C_PShine();
	~C_PShine() {}

	void Update();
	void Draw()final;

	//セッター
	void SetSize(float a_size) { m_size = a_size; }

private:

	bool alphaFlg;

	Math::Rectangle m_srcRect;

};