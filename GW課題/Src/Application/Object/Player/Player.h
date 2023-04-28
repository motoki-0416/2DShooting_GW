#pragma once
#include "Application/Utility.h"
#include "Application/Object/Bullet/BaseBullet.h"
using namespace std;

class Scene;
class C_PBom;
class C_BaseBullet;
class C_BaseObject;

class C_Player
{
public:

	//�֐�
	C_Player();    //�R���X�g���N�^
	~C_Player();   //�f�X�g���N�^

	void Init();  //������
	void Update(int a_eve);//�X�V
	void Draw();//�`��

	//�v���C���[
	void StartEvent();
	void Key();
	void DedAnime();

	void MakeBullet();
	void DeleteManager();

	//�p�[�e�B�N���쐬
	void MakeBom(Math::Vector3 a_pos,float size = 1,Math::Vector3 a_move = { 0,0,0});

	//�Z�b�^�[
	void SetTex(KdTexture* a_pTex, Scene* a_pOwner);//������
	void SetPos(Math::Vector3 a_pos) { m_data.m_pos = a_pos; m_data.m_mat = Math::Matrix::CreateTranslation(m_data.m_pos); }
	void SetHP(int a_hp);
	void SetAlive(bool a_alive) { m_bAlive = a_alive; }
	void SetBulletAlive(bool a_alive, int i) { m_bullet[i]->SetAlive(a_alive); }

	//�Q�b�^�[
	const bool GetAlive() { return m_bAlive; }
	const OBJData* GetData() { return &m_data; }
	const OBJData* GetBulletData(int i) { return m_bullet[i]->GetData(); }
	const Math::Vector3 GetPos() { return m_data.m_pos; }
	const int GetBulletSize() { return m_bullet.size(); }

	bool CircleCD(const OBJData a_Adata, const OBJData a_Bdata);
	
private:
	OBJData m_data = { {64,64,0},m_data.SIZE / 2,{0,0,0},{0,0,0},{Math::Matrix::Identity},nullptr };
	static const int MAX_HP = 100;
	int m_hp;
	bool m_bAlive;

	//�C�x���g
	bool bStartFlg;
	
	//�Z�b�^�[�摜
	KdTexture* m_pHitTex;
	KdTexture* m_pBomTex;

	//��
	KdTexture* m_pBulletTex;
	vector<shared_ptr<C_BaseBullet>> m_bullet;
	static const int BULLET_MOVE_Y = 13;
	static const int COUNT_NUM = 1;
	int shotCount;
	bool bulletOffset;

	//���j�̃p�[�e�B�N��
	vector<shared_ptr<C_PBom>> m_bom;
	static const int BOM_MAX=10;
	static const int BOM_NUM = 4;
	static const int DLEAY_MAX = 4;
	int bomCount;
	int bomDelay;
};