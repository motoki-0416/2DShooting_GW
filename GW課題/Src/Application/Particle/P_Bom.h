#pragma once
#include "Application/Utility.h"
#include "P_Base.h"

class C_PBom :public C_BaseParticle
{
public:
	C_PBom();
	~C_PBom() {}

	void Update();
	void Draw()final;

	//セッター
	void SetSize(float a_size) { m_size = a_size; }
	
private:

	//爆破アニメ
	void Animetion();
	static const int MAX_ANIME = 4;
	static const int DLEAY_MAX = 3;
	int AniCnt;
	int delay;
	int animation;
	Math::Rectangle m_srcRect;
	
};