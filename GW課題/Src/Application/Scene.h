#pragma once

//タイトル
#include "Application/Title/Title.h"

//ゲーム
#include "Application/Object/Player/Player.h"

class C_BaseScene;


struct TexID
{
	KdTexture titleBackGroundTex;
	KdTexture titleNameTex;
	KdTexture titlePushSpace;
	KdTexture titleStartTextTex;
	KdTexture titleOptionTextTex;
	KdTexture selectTex;
	KdTexture titleOptionTex;
	KdTexture titleBackTex;

	KdTexture numberTex;

	KdTexture  eventStartTex;
	KdTexture eventWarningTex;
	KdTexture eventMissionTex;

	KdTexture bulletTex;
	KdTexture p_hitTex;
	KdTexture p_bomTex;

	KdTexture m_scoreTex;
	KdTexture m_hpTex;

	KdTexture backTex;
	KdTexture back2Tex;
	KdTexture playerTex;
	
	KdTexture enemyTex;
	KdTexture moveEnemyTex;
	KdTexture widthEnemyTex;

	KdTexture miniBossTex;
	KdTexture bossTex;
	KdTexture cannonUTex;
	KdTexture cannonDTex;
	KdTexture voltTex;
	KdTexture missileTex;
	KdTexture bossIconTex;

	KdTexture result_RetryTex;
	KdTexture result_TitleTex;
	KdTexture resultTex;
	KdTexture resultRankTex;
	
	KdTexture result_BackTex;
};


class Scene
{
private:

	TexID m_texID;
	shared_ptr<C_BaseScene> m_scene;
	
public:

	//
	TexID* GetTex() { return &m_texID; }
	
	// 初期設定
	void LoadTex();
	void Init();
	
	// 解放
	void Release();

	// 更新処理
	void Update();

	// 描画処理
	void Draw2D();

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
