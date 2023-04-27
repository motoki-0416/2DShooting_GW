#pragma once
#include "Application/Utility.h"
#include "Application/Object/BaseObject.h"

class Scene;

class C_Enemy:public C_BaseObject
{
public:

	C_Enemy(){};    //コンストラクタ
	~C_Enemy(){};   //デストラクタ

	void Init()override;
	void Update()override;

	//球作成-攻撃
	void MakeBullet();
	

private:
	//static const int 

	static const int ENEMY_MOVE_Y = -10;
	static const int BULLET_MOVE_Y = -10;
	
};