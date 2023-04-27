#pragma once
#include "Application/Utility.h"
#include "P_Base.h"

class C_PHit :public C_BaseParticle
{
public:
	C_PHit();
	~C_PHit() {}

	void Update();

	//セッター
	void SetSize(float a_size, float a_sizeChange) { m_size = a_size, sizeChange = a_sizeChange; }

private:

	float sizeChange;
};