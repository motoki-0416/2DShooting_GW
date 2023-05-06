
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

	C_ResultNumber() { }
	~C_ResultNumber() {}

	void Init(Scene* a_pOwner,int a_score);
	void Update();
	void Draw();

	void SetTex(Scene* a_pOwner);
	void SetPos(Math::Vector3 a_pos);

private:

	int scoreList;

	static const int NUMBER_NUM = 8;
	BASE m_number[NUMBER_NUM];

	Math::Matrix scaleMat;

	numberSrc m_src[NUMBER_NUM];

	KdTexture* m_pNumberTex;

};