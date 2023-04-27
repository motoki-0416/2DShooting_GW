#pragma once
#include "Application/Utility.h"
#include "Application/Scene.h"

using namespace Alpha;

class C_BaseEvent
{
public:
	C_BaseEvent() {}
	~C_BaseEvent() {}

	virtual void Init();
	virtual bool Update();
	virtual void Draw();


protected:

	BASE m_data = { {128,72,0},m_data.SIZE / 2,{0,0,0},MIN_ALPHA,{Math::Matrix::Identity},{nullptr} };

};