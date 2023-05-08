#include "main.h"
#include "Scene.h"
#include "Utility.h"

#include "Application/Scene/BaseScene.h"
#include "Application/Scene/Title/Scene_Title.h"
#include "Application/Scene/Game/Scene_Game.h"
#include "Application/Scene/Result/Scene_Result.h"

#include "Application/Program/Button/Program_Button.h"


void Scene::Draw2D()
{

	m_scene->Draw();

}

void Scene::Update()
{
	//☆要る？
	/*m_button->Update();*/

	if (m_scene->GetSceneChange())
	{
		int score = 0;
		int enemyDed = 0;
		bool m_gameFlg = false;
		shared_ptr<C_BlackOut> tmpA = m_scene->GetBlackOutData();

		switch (m_scene->GetType())
		{

		case C_BaseScene::SceneType::scene_title:
			m_scene = make_shared<C_SceneGame>();
			m_scene->SetType(C_BaseScene::SceneType::scene_game);
			m_scene->Init(this);
			m_scene->SetBlackOutData(tmpA);
			break;
		case C_BaseScene::SceneType::scene_game:
			score = m_scene->GetScore();
			enemyDed = m_scene->GetEnemyDed();
			m_gameFlg = m_scene->GetAnyFlg();

			m_scene = make_shared<C_SceneResult>();
			m_scene->SetType(C_BaseScene::SceneType::scene_result);
			m_scene->SetResult(score, enemyDed);
			m_scene->Init(this,m_gameFlg);
			m_scene->SetBlackOutData(tmpA);
			break;
		case C_BaseScene::SceneType::scene_result:
			
			switch (m_scene->GetNowSelectScene())
			{
			case C_BaseScene::NowSceneSelect::select_title:
				m_scene = make_shared<C_SceneTitle>();
				m_scene->SetType(C_BaseScene::SceneType::scene_title);
				m_scene->Init(this);
				m_scene->SetBlackOutData(tmpA);
				break;
			case C_BaseScene::NowSceneSelect::select_game:
				m_scene = make_shared<C_SceneGame>();
				m_scene->SetType(C_BaseScene::SceneType::scene_game);
				m_scene->Init(this);
				m_scene->SetBlackOutData(tmpA);
				break;
			default:
				break;
			}
			break;

		default:
			break;
		}
	}

	m_scene->Update();

	
}


void Scene::LoadTex()
{
	m_texID.selectTex.Load("Texture/select.png");

	//タイトル
	m_texID.titleNameTex.Load("Texture/Title/Title_Name.png");
	m_texID.titleBackGroundTex.Load("Texture/Title/Title_BackGround.png");
	m_texID.titleOptionTextTex.Load("Texture/Title/Title_OptionText.png");
	m_texID.titleStartTextTex.Load("Texture/Title/Title_StartText.png");
	
	m_texID.titleOptionTex.Load("Texture/Title/Title_Option.png");
	m_texID.titleBackTex.Load("Texture/Title/Title_Back.png");
	m_texID.titlePushSpace.Load("Texture/Title/Push_Space.png");

	//ゲーム
	m_texID.miniBossTex.Load("Texture/miiniBoss.png");

	m_texID.numberTex.Load("Texture/number.png");
	m_texID.m_scoreTex.Load("Texture/SCORE.png");
	m_texID.m_hpTex.Load("Texture/HP.png");

	m_texID.bossTex.Load("Texture/Boss.png");
	m_texID.cannonUTex.Load("Texture/cannonU.png");
	m_texID.cannonDTex.Load("Texture/cannonD.png");
	m_texID.voltTex.Load("Texture/volt.png");
	m_texID.missileTex.Load("Texture/missile.png");

	m_texID.eventStartTex.Load("Texture/player.png");
	m_texID.eventWarningTex.Load("Texture/warning.png");
	m_texID.eventMissionTex.Load("Texture/bossmi.png");

	m_texID.backTex.Load("Texture/001.bmp");
	

	m_texID.playerTex.Load("Texture/player.png");
	m_texID.enemyTex.Load("Texture/enemy.png");
	m_texID.moveEnemyTex.Load("Texture/moveEnemy.png");
	m_texID.widthEnemyTex.Load("Texture/enemy2.png");

	m_texID.bossIconTex.Load("Texture/bossIcon.png");

	m_texID.bulletTex.Load("Texture/bullet.png");
	m_texID.p_hitTex.Load("Texture/bullet.png");
	m_texID.p_bomTex.Load("Texture/explosion.png");

	m_texID.result_RetryTex.Load("Texture/retry.png");
	m_texID.result_TitleTex.Load("Texture/title.png");
	m_texID.resultTex.Load("Texture/Result.png");
	m_texID.resultRankTex.Load("Texture/Rank.png");

	m_texID.result_BackTex.Load("Texture/002.png");

}

void Scene::Init()
{

	//シーンの初期
	m_scene = make_shared<C_SceneTitle>();
	m_scene->SetType(C_BaseScene::SceneType::scene_title);
	m_scene->Init(this);
	m_scene->Init(this, true);

	srand(timeGetTime());

	//画像ロード
	LoadTex();


}

void Scene::Release()
{
	//タイトル
	m_texID.titleNameTex.Release();
	m_texID.titleBackGroundTex.Release();
	m_texID.titleOptionTextTex.Release();
	m_texID.titleStartTextTex.Release();
	m_texID.selectTex.Release();
	m_texID.titleOptionTex.Release();
	m_texID.titleBackTex.Release();
	m_texID.titlePushSpace.Release();

	m_texID.bossTex.Release();
	m_texID.cannonUTex.Release();
	m_texID.cannonDTex.Release();
	m_texID.voltTex.Release();
	m_texID.missileTex.Release();

	m_texID.numberTex.Release();
	m_texID.m_scoreTex.Release();
	m_texID.m_hpTex.Release();

	m_texID.miniBossTex.Release();
	m_texID.eventStartTex.Release();
	m_texID.eventWarningTex.Release();
	m_texID.eventMissionTex.Release();

	m_texID.backTex.Release();
	m_texID.playerTex.Release();

	m_texID.enemyTex.Release();
	m_texID.moveEnemyTex.Release();
	m_texID.widthEnemyTex.Release();
	m_texID.bossIconTex.Release();

	m_texID.bulletTex.Release();
	m_texID.p_hitTex.Release();
	m_texID.p_bomTex.Release();

	m_texID.result_BackTex.Release();
	m_texID.result_RetryTex.Release();
	m_texID.result_TitleTex.Release();
	m_texID.resultRankTex.Release();

}

void Scene::ImGuiUpdate()
{
	return;

	ImGui::SetNextWindowPos(ImVec2(20, 20), ImGuiSetCond_Once);
	ImGui::SetNextWindowSize(ImVec2(200, 100), ImGuiSetCond_Once);

	// デバッグウィンドウ
	if (ImGui::Begin("Debug Window"))
	{
		
		ImGui::Text("FPS : %d", APP.m_fps);

	}
	ImGui::End();
}