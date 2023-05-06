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
	bool ChangeAlpha(bool a_flg, float a_changeAlpha=0.01);

	void Draw();

private:

	float blackAlpha;
	bool bAlphaFlg;

};