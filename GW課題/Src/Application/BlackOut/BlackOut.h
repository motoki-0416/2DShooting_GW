#pragma once
#include "Application/Utility.h"

using namespace Screen;
using namespace Alpha;

class C_BlackOut
{
public:
	C_BlackOut() { Init(); }
	~C_BlackOut(){}

	void Init();
	void Update();
	bool ChangeAlpha(bool a_flg);

	void Draw();

private:
	const float CHANGE_ALPHA=0.01;

	float blackAlpha;
	bool bAlphaFlg;

};