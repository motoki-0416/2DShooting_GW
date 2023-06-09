#pragma once
#include "Application/Event/BaseEvent.h"

class Scene;

class C_EventStart:public C_BaseEvent
{
public:

	C_EventStart(){}
	~C_EventStart(){}

	void Init()override;
	void Update()override;
	void Draw()override;

	void SetTex(Scene* a_pOwner)override;

private:
	bool m_bFlg;
	int delay;

};