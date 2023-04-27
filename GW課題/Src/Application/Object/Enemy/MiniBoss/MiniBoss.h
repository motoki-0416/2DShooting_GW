#pragma once
#include "Application/Utility.h"
#include "Application/Object/BaseObject.h"

class C_Player;

class C_MiniBoss :public C_BaseObject
{
public:

	C_MiniBoss() {};    //�R���X�g���N�^
	~C_MiniBoss() {};   //�f�X�g���N�^

	void Init()override;
	void Update()override;
	void Draw()override;

	//���쐬-�U��
	void MakeBullet();
	void HitCheckBullet(C_Player* a_player)override;

private:
	//static const int 
	static const int MAX_HP = 50;


	static const int ENEMY_MOVE_Y = -10;
	static const int BULLET_MOVE_Y = -10;

};