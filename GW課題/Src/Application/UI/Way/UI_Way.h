#pragma once
#include "../BaseUI.h"


class C_UIWay :public C_BaseUI
{

public:

	C_UIWay() { Init(); }
	~C_UIWay() {}

	void Init()override;
	void Update(C_SceneGame* a_pOwner)override;
	void Draw()override;

	void SetTex(Scene* a_pOwner)override;

private:

	static const int WAYPOS_X = -480;

	Math::Vector3 wayPos;
};