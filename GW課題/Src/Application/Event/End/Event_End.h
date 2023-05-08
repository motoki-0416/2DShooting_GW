
#pragma once
#include "Application/Event/BaseEvent.h"

class Scene;
class C_SceneGame;

class C_EventEnd :public C_BaseEvent
{
public:

	C_EventEnd() {}
	~C_EventEnd() {}

	void Init()override;
	void Update()override;
	void Draw()override;

private:

	KdTexture* m_tex;

	int delay;

	int alpha_Change;

	float boxAlpha;

};