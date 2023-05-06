#pragma once
#include "../BaseUI.h"

class C_UIHP :public C_BaseUI
{

public:

	C_UIHP(){}
	~C_UIHP(){}

	void Update(C_SceneGame* a_pOwner)override;
	void Draw()override;
	
private:

	static const int MAX_HP = 100;
	float m_width;

};