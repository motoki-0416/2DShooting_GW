#pragma once

class C_WidthEnemy :public C_BaseObject
{

public:

	C_WidthEnemy() { Init(); }    //コンストラクタ
	~C_WidthEnemy() {};   //デストラクタ

	void Init()override;
	void Update()override;

	void CommitPos(Math::Vector3 a_move)override;

	//球作成-攻撃
	void MakeBullet();

	void Move();


private:

	float ang;

	static const int ENEMY_MOVE_Y = -10;
	static const int BULLET_MOVE_Y = -10;

};