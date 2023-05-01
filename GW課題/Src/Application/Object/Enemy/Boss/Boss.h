#pragma once
#include "Application/Utility.h"
#include "Application/Object/BaseObject.h"

enum Atk
{
	Atk_Missile,
	Atk_Rotate,
	Atk_Homing,
};

class C_Boss :public C_BaseObject
{
public:

	C_Boss() {};    //コンストラクタ
	~C_Boss() {};   //デストラクタ

	void Init()override;
	void Update()override;
	void Draw()override;

	
	//球作成-攻撃
	
	void AtkSelect();
	void AtkRotate();
	void AtkMissile();
	void AtkHoming();
	
	void MakeBullet();
	void MakeMissile();
	void MakeHoming();



	void MakeBom(OBJData a_data, int num = 1);
	void MakeVolt();

	void Move();

	void PlayerCD(C_Player* a_player)override;
	void HitCheckBullet(C_Player* a_player)override;

	void SetTex(Scene* a_pOwner);

	void DeleteManager()override;

private:
	static const int MAX_HP = 300;
	static const int MAX_CANNONHP = 50;
	static const int CANNON_NUM = 4;
	static const int ENEMY_MOVE_Y = -10;
	static const int BULLET_MOVE_Y = -5;

	bool startFlg;


	Math::Vector3 playerPos;


	int damageDelay;

	Atk m_atk;
	int atkDelay;

	//大砲
	vector<shared_ptr<C_BaseObject>> m_cannonList;
	bool m_bCannonFlg;


	KdTexture* m_pVoltTex;
	KdTexture* m_pMissileTex;

};