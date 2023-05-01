#pragma once
#include "Application/Utility.h"
#include "Application/Object/Bullet/BaseBullet.h"
using namespace Screen;

class C_Homing:public C_BaseBullet
{
public:
	C_Homing() {Init(); }    //�R���X�g���N�^
	~C_Homing(){};   //�f�X�g���N�^

	void Init()override;
	void Update()override;
	
	void SetPlayerPos(Math::Vector3 a_pos);

private:
	
	Math::Vector3 playerPos;
	int homingDelay;
	float m_deg;

};