#pragma once
#include "Application/Event/BaseEvent.h"

class C_BaseObject;

class C_SceneGame;
class Scene;

class C_EventBoss :public C_BaseEvent
{
public:

	C_EventBoss() {}
	~C_EventBoss() {}


	void Init()override;
	void Draw()override;
	void Update()override;

	void SetTex(Scene* a_pOwner)override;
	
	

private:

	BASE m_warning = { {400,400,0},m_warning.SIZE / 2,{-600,0,0} ,1.0f,{Math::Matrix::CreateTranslation(m_warning.m_pos)},{nullptr}};
	int warningDelay;

	bool boxFlg;
	bool flg;
	float boxAlpha;
	int boxDelay;

	bool createFlg;
	int createDelay;
	int delay;

};