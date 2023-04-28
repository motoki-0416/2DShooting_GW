#pragma once
#include "Application/Particle/P_Base.h"

class C_PVolt :public C_BaseParticle
{
public:

	C_PVolt() { Init(); }
	~C_PVolt(){}

	void Init()override;
	void Update()override;
	void Draw()override;

private:

	int m_deg;
};
