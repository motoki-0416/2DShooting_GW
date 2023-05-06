#pragma once
#include "Application/Scene/BaseScene.h"

class C_Title;
class C_Player;

class C_SceneTitle:public C_BaseScene
{
public:

	C_SceneTitle(){};
	~C_SceneTitle(){};

	void Init(Scene* a_pOwner)override;
	void Update()override;
	void Draw()override;

	void SetTex(Scene* a_pOwner)override;

private:

	shared_ptr<C_Player> m_player;
	shared_ptr<C_Title> m_title;

};