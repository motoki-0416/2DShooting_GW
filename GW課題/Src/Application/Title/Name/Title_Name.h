#pragma once
#include "Application/Utility.h"

class Scene;
using namespace Alpha;

class C_TitleName
{
public:

	C_TitleName() { Init(); }
	~C_TitleName(){}

	void Init();
	void Draw();
	bool Update(bool a_bSpace);

	void SetTex(Scene* a_pOwner);


private:

	BASE m_name= { {413, 223, 0}, m_name.SIZE / 2, { 0,0,0 }, MIN_ALPHA, { Math::Matrix::Identity }, { nullptr } };
	BASE m_push= { {300, 114, 0}, m_push.SIZE / 2, { 0,-200,0 }, MIN_ALPHA, { Math::Matrix::Identity }, { nullptr } };
	const float CHANGE_ALPHA = 0.008;
	static const int MAX_DELAY = 60;


	bool m_bAlpha;

	int deg;
	bool m_bFlg;
	int delay;
};