#pragma once
#include "Application/Utility.h"

class C_SceneGame;
class Scene;

class C_BaseUI
{
public:

	C_BaseUI() { Init(); }
	~C_BaseUI() {}

	virtual void Init();
	virtual void Update(C_SceneGame* a_pOwner);
	virtual void Draw();

	virtual void SetTex(Scene* a_pOwner){};

	protected:

	BASE m_data= { {64,64,0},m_data.SIZE / 2,{},1.0f,{Math::Matrix::Identity},nullptr };

};
