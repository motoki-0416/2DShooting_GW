#pragma once

//タイトル
#include "Application/Title/Title.h"

//ゲーム
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

	//ブラックアウト
	shared_ptr<C_BlackOut> m_blackOut;

	////////////////////////////////////////////////
	//タイトル
	////////////////////////////////////////////////
	TitleTexture m_titleTex;
	C_Title m_title;


	////////////////////////////////////////////////
	//ゲーム
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

	//背景
	shared_ptr<C_Back> m_back;
	KdTexture backTex;
	KdTexture back2Tex;
	vector<shared_ptr<C_BaseObject>> m_enemy;

	KdTexture shineTex;
	vector<shared_ptr<C_PShine>> m_shine;


	static const int MAX_SLOW=2;
	int slowMotion;


	//関数
	void CreateManager(int a_eve);
	void DeleteManager(bool m_bFlg=false);
	void HitManager();

public:

	//
	TitleTexture* GetTitleTex() { return &m_titleTex; }
	EventTexture* GetEventTex() { return &m_eventTex; }
	ObjectTexture* GetObjectTex() { return &m_objTex; }
	BossTexture* GetBossTex() { return &m_bossTex; }

	// 初期設定
	void LoadTex();
	void Init();
	
	void InitTitle();
	void InitTutorial();
	void InitGame();

	void Reset();


	// 解放
	void Release();

	// 更新処理
	void Update();

	void UpdateTitle();
	void UpdateTutorial();
	void UpdateGame();

	// 描画処理
	void Draw2D();

	void DrawTitle();
	void DrawTutorial();
	void DrawGame();


	// GUI処理
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
