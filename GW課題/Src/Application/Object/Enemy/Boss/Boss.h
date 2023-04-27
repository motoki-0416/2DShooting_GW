#pragma once
#include "Application/Utility.h"
#include "Application/Object/BaseObject.h"

enum Cannon
{
	UL,
	UR,
	DL,
	DR,
};

struct CannonData
{
	OBJData obj;
	int damageDelay;
	int cannonHP;
	bool m_bAlive;
};

class C_Boss :public C_BaseObject
{
public:

	C_Boss() {};    //�R���X�g���N�^
	~C_Boss() {};   //�f�X�g���N�^

	void Init()override;
	void Update()override;
	void Draw()override;

	void CannonAlive();	//��C�������Ă��邩

	//���쐬-�U��
	void MakeBullet();
	void MakeBom(OBJData a_data,int num=1);

	void PlayerCD(C_Player* a_player)override;
	void HitCheckBullet(C_Player* a_player)override;

	void SetTex(Scene* a_pOwner);
private:

	static const int MAX_HP = 300;
	int damageDelay;

	//��C
	static const int MAX_CANNONHP = 50;
	static const int CANNON_NUM=4;
	CannonData m_cannon[CANNON_NUM];
	bool m_bCannonFlg;

	static const int ENEMY_MOVE_Y = -10;
	static const int BULLET_MOVE_Y = -10;
};