
#pragma once
#include "Application/Utility.h"

class Scene;

struct numberSrc
{
	int numSrc;
};

class C_ResultNumber
{

public:

	C_ResultNumber() { size = 1; }
	~C_ResultNumber() {}

	void Init(Scene* a_pOwner,int a_score);
	void Draw();

	void SetTex(Scene* a_pOwner);
	void SetPos(Math::Vector3 a_pos);
	void SetSize(float i=1) { size = i; }

private:

	int scoreList;

	static const int NUMBER_NUM = 8;
	BASE m_number[NUMBER_NUM];

	numberSrc m_src[NUMBER_NUM];

	float size;
	Math::Matrix m_scaleMat;

	KdTexture* m_pNumberTex;

};