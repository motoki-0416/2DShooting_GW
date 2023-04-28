#pragma once

//�^�C�g��
#include "Application/Title/Title.h"

//�Q�[��
#include "Application/Object/Player/Player.h"

class C_Button;
class C_BlackOut;
class C_Back;
class C_Event;
class C_Player;
class C_BaseObject;
class C_PShine;

enum SceneChange
{
	Title,
	Tutorial,
	Game,
	Result
};

struct TitleTexture
{
	KdTexture titleBackGroundTex;
	KdTexture titleNameTex;
	KdTexture titleStartTextTex;
	KdTexture titleOptionTextTex;
	KdTexture titileSelectTex;
	KdTexture titleOptionTex;
	KdTexture titleBackTex;
};

struct EventTexture
{
	KdTexture  eventStartTex;

};

struct ObjectTexture
{
	KdTexture bulletTex;
	KdTexture p_hitTex;
	KdTexture p_bomTex;
};

struct BossTexture
{
	KdTexture bossTex;
	KdTexture cannonUTex;
	KdTexture cannonDTex;
	KdTexture voltTex;
	KdTexture missileTex;

};

class Scene
{
private:
	shared_ptr<C_Button> m_button;
	SceneChange sceneChange;

	//�u���b�N�A�E�g
	shared_ptr<C_BlackOut> m_blackOut;

	////////////////////////////////////////////////
	//�^�C�g��
	////////////////////////////////////////////////
	TitleTexture m_titleTex;
	C_Title m_title;


	////////////////////////////////////////////////
	//�Q�[��
	////////////////////////////////////////////////


	shared_ptr<C_Event> m_event;
	EventTexture m_eventTex;
	ObjectTexture m_objTex;

	KdTexture playerTex;
	C_Player* m_player;

	KdTexture enemyTex;
	KdTexture miniBossTex;
	BossTexture m_bossTex;
	bool miniBossFlg;
	bool bossFlg;

	//�w�i
	shared_ptr<C_Back> m_back;
	KdTexture backTex;
	KdTexture back2Tex;
	vector<shared_ptr<C_BaseObject>> m_enemy;

	KdTexture shineTex;
	vector<shared_ptr<C_PShine>> m_shine;


	static const int MAX_SLOW=2;
	int slowMotion;


	//�֐�
	void CreateManager(int a_eve);
	void DeleteManager(bool m_bFlg=false);
	void HitManager();

public:

	//
	TitleTexture* GetTitleTex() { return &m_titleTex; }
	EventTexture* GetEventTex() { return &m_eventTex; }
	ObjectTexture* GetObjectTex() { return &m_objTex; }
	BossTexture* GetBossTex() { return &m_bossTex; }

	// �����ݒ�
	void LoadTex();
	void Init();
	
	void InitTitle();
	void InitTutorial();
	void InitGame();

	void Reset();


	// ���
	void Release();

	// �X�V����
	void Update();

	void UpdateTitle();
	void UpdateTutorial();
	void UpdateGame();

	// �`�揈��
	void Draw2D();

	void DrawTitle();
	void DrawTutorial();
	void DrawGame();


	// GUI����
	void ImGuiUpdate();


private:

	Scene() {}

public:
	static Scene& GetInstance()
	{
		static Scene instance;
		return instance;
	}
};

#define SCENE Scene::GetInstance()
