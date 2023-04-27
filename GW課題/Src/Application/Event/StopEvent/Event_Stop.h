#pragma once
#include "Application/Event/BaseEvent.h"

class Scene;

class C_EventStop :public C_BaseEvent
{
public:

	C_EventStop() {}
	~C_EventStop() {}

	void Init()override;
	bool Update()override;
	void Draw()override;

private:
	bool m_bFlg;
	int delay;

};