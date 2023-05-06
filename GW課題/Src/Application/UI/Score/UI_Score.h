#pragma once
#include "../BaseUI.h"

struct numberSrc
{
	int numSrc;
};

class C_UIScore :public C_BaseUI
{

public:

	C_UIScore() { Init(); }
	~C_UIScore() {}

	void Init()override;
	void Update(C_SceneGame* a_pOwner)override;
	void Draw()override;

	void SetTex(Scene* a_pOwner)override;
private:
	static const int NUMBER_NUM = 8;
	BASE m_number[NUMBER_NUM];

	int scoreList;
	numberSrc m_src[NUMBER_NUM];

};