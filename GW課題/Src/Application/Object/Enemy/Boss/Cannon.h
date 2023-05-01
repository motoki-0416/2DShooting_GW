#pragma once
#include "Application/Object/BaseObject.h"

class C_Cannon:public C_BaseObject
{
public:

	C_Cannon() {  }
	~C_Cannon(){}

	enum class CannonType
	{
		UL,
		UR,
		DL,
		DR,
	};

	void Init()override;
	void Draw()override;
	void Update()override;
	void SetPos(Math::Vector3 a_pos)override;
	
	void MakeBom()override;


	void SetCannonType(int a_type)	{ m_cannonType = (CannonType)a_type; }

	void HitCheckBullet(C_Player* a_player)override;

private:

	CannonType m_cannonType;

	int damageDelay;
};