#pragma once


class C_MoveEnemy :public C_BaseObject
{

public:

	C_MoveEnemy() { Init(); }    //コンストラクタ
	~C_MoveEnemy() {};   //デストラクタ

	void Init()override;
	void Update()override;

	//動き
	void Move();

	//球作成-攻撃
	void MakeBullet();

	void SetAng(float a_ang) { ang = a_ang; }

private:
	
	float ang;

	static const int ENEMY_MOVE_Y = -10;
	static const int BULLET_MOVE_Y = -10;

};