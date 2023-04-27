#pragma once
#include "Application/Utility.h"
#include "Application/Object/BaseObject.h"

class Scene;

class C_Enemy:public C_BaseObject
{
public:

	C_Enemy(){};    //�R���X�g���N�^
	~C_Enemy(){};   //�f�X�g���N�^

	void Init()override;
	void Update()override;

	//���쐬-�U��
	void MakeBullet();
	

private:
	//static const int 

	static const int ENEMY_MOVE_Y = -10;
	static const int BULLET_MOVE_Y = -10;
	
};