#pragma once
#include "Application/Event/BaseEvent.h"

class C_BaseObject;

class C_SceneGame;
class Scene;

class C_EventStop :public C_BaseEvent
{
public:

	C_EventStop() {}
	~C_EventStop() {}

	void Init()override;
	void Update()override;

	void SetTex(Scene* a_pOwner)override;

private:

	KdTexture* m_tex;


	int createDelay;
	bool createFlg;
};