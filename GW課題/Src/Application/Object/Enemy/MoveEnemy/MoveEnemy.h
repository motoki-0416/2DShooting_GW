#pragma once


class C_MoveEnemy :public C_BaseObject
{

public:

	C_MoveEnemy() { Init(); }    //�R���X�g���N�^
	~C_MoveEnemy() {};   //�f�X�g���N�^

	void Init()override;
	void Update()override;

	//����
	void Move();

	//���쐬-�U��
	void MakeBullet();

	void SetAng(float a_ang) { ang = a_ang; }

private:
	
	float ang;

	static const int ENEMY_MOVE_Y = -10;
	static const int BULLET_MOVE_Y = -10;

};