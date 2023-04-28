#include "main.h"
#include "Scene.h"
#include "Utility.h"

#include "Application/Program/Button/Program_Button.h"

#include "Application/Event/Event.h"
#include "Application/BlackOut/BlackOut.h"

#include "Application/Back/Back.h"
#include "Application/Object/Enemy/enemy.h"
#include "Application/Object/Enemy/MoveEnemy/MoveEnemy.h"
#include "Application/Object/Enemy/MiniBoss/MiniBoss.h"
#include "Application/Object/Enemy/Boss/Boss.h"
#include "Application/Particle/shine/P_Shine.h"


void Scene::Draw2D()
{
	

	switch (sceneChange)
	{
	case Title:
		DrawTitle();
		break;
	case Tutorial:
		DrawTutorial();
		break;
	case Game:
		DrawGame();
		break;
	case Result:
		break;
	default:
		break;
	}

	m_blackOut->Draw();

	//KdShaderManager::GetInstance().m_spriteShader.SetMatrix(Math::Matrix::Identity);
	//KdShaderManager::GetInstance().m_spriteShader.DrawTex(&shineTex, 0, 0,16,16);
}

void Scene::DrawTitle()
{
	//☆
	Math::Color color = { 0,0,0,1 };
	SHADER.m_spriteShader.SetMatrix(Math::Matrix::Identity);
	SHADER.m_spriteShader.DrawBox(-520, 0, 160, 360, &color, true);
	SHADER.m_spriteShader.DrawBox(520, 0, 160, 360, &color, true);
	m_title.Draw();

}

void Scene::DrawTutorial()
{
}

void Scene::DrawGame()
{
	m_back->Draw();
	for (int i = 0; i < m_enemy.size(); i++)
	{
		m_enemy[i]->Draw();
	}
	for (int i = 0; i < m_shine.size(); i++)
	{
		m_shine[i]->Draw();
	}
	m_player->Draw();
	//☆
	Math::Color color = { 0.2,0.2,0.5,0.8 };
	SHADER.m_spriteShader.SetMatrix(Math::Matrix::Identity);
	SHADER.m_spriteShader.DrawBox(-510, 0, 130, 360, &color, true);
	SHADER.m_spriteShader.DrawBox(510, 0, 130, 360, &color, true);
	m_event->Draw();
}

void Scene::Update()
{
	//☆要る？
	m_button->Update();

	switch (sceneChange)
	{
	case Title:
		UpdateTitle();
		break;
	case Tutorial:
		UpdateTutorial();
		break;
	case Game:
		UpdateGame();
		break;
	case Result:
		break;
	default:
		break;
	}
	//消す！！！！！！！！！！！！！！！！！！！！！！！！！！！
	if (GetAsyncKeyState('Q') & 0x8000)
	{
		Reset();
	}
}

void Scene::UpdateTitle()
{
	static bool bSpace = false;
	if (m_title.Update(bSpace))
	{
		//ブラックアウト
		if (m_blackOut->ChangeAlpha(true))
		{
			sceneChange = Tutorial;
		}
	}
	GetAsyncKeyState(VK_SPACE) & 0x8000 ? bSpace = true : bSpace = false;
}

void Scene::UpdateTutorial()
{
	if (GetAsyncKeyState('B') & 0x8000)
	{
		//ブラックアウト
		if (m_blackOut->ChangeAlpha(true))
		{
			sceneChange = Game;
		}
	}
	else
	{
		//ブラックイン
		m_blackOut->ChangeAlpha(false);
	}
}

void Scene::UpdateGame()
{
	//ブラックイン
	m_blackOut->ChangeAlpha(false);

	//スローモーション（お試し）
	if (!m_player->GetAlive() && slowMotion <= 0)
	{
		slowMotion = MAX_SLOW;
	}
	else if (!m_player->GetAlive() && slowMotion > 0)
	{
		slowMotion--;
		return;
	}

	//自機の処理とイベントの確認

	m_event->Update(*m_back);
	m_player->Update(m_event->GetEvent());
	m_back->Update();


	//敵の処理
	for (int i = 0; i < m_enemy.size(); i++)
	{
		m_enemy[i]->Update();
	}

	for (int i = 0; i < m_shine.size(); i++)
	{
		m_shine[i]->Update();
	}

	//当たり判定
	HitManager();
	//敵出現
	CreateManager(m_event->GetEvent());
	//削除
	DeleteManager();
}

void Scene::CreateManager(int a_eve)
{
	switch (a_eve)
	{
	case 1://スタート
		if (!bossFlg)
		{
			shared_ptr<C_Boss>tmpA = make_shared<C_Boss>();
			tmpA->Init();
			tmpA->SetPos({ 0,(float)(360 + tmpA->GetData()->HALF_SIZE.y),0 });
			tmpA->SetTex(this);
			tmpA->SetType(enemyBoss);
			m_enemy.push_back(tmpA);
			bossFlg = true;
		}
		return;
		break;

	case 2:
		if (!miniBossFlg)
		{
			shared_ptr<C_MiniBoss>tmpA = make_shared<C_MiniBoss>();
			tmpA->Init();
			tmpA->SetPos({ 0,(float)(360 + tmpA->GetData()->HALF_SIZE.y),0 });
			tmpA->SetTex(&miniBossTex, this);
			tmpA->SetType(enemyMiniBoss);
			m_enemy.push_back(tmpA);
			miniBossFlg = true;
		}
		break;

	case 3:
		if (!bossFlg)
		{
			shared_ptr<C_Boss>tmpA = make_shared<C_Boss>();
			tmpA->Init();
			tmpA->SetPos({ 0,(float)(360 + tmpA->GetData()->HALF_SIZE.y),0 });
			tmpA->SetTex(this);
			tmpA->SetType(enemyBoss);
			m_enemy.push_back(tmpA);
			bossFlg = true;
		}
		return;
	default:
		break;
	}

	return;

	static int mDelay = 0;
	if (mDelay <= 0)
	{
		float posX = rand() % 200 - 100;
		for (int i = 0; i < 3; i++)
		{
			shared_ptr<C_MoveEnemy> tmpA = make_shared<C_MoveEnemy>();
			tmpA->Init();
			tmpA->SetPos({ posX,(float)(360 + tmpA->GetData()->HALF_SIZE.y + (i * 64)),0 });
			tmpA->SetAng(-(i * 10));
			tmpA->SetType(enemyNormal);
			tmpA->SetTex(&enemyTex,this);
			m_enemy.push_back(tmpA);
		}
		mDelay = 1000;
	}
	else
	{
		mDelay--;
	}

	static int delay = 0;
	if (delay <= 0)
	{
		shared_ptr<C_Enemy> tmpA = make_shared<C_Enemy>();
		tmpA->Init();
		float posX = rand() % 600 - 300;
		tmpA->SetPos({ posX,(float)(360 + tmpA->GetData()->HALF_SIZE.y),0 });
		tmpA->SetTex(&enemyTex,this);
		tmpA->SetType(enemyNormal);
		m_enemy.push_back(tmpA);

		delay = 40;
	}
	else
	{
		delay--;
	}

	if (rand() % 10 <= 0)
	{
		shared_ptr<C_PShine>tmpA = make_shared<C_PShine>();
		tmpA->Init();
		tmpA->SetPos({ 0,0,0});
		tmpA->SetTex(&shineTex);
		m_shine.push_back(tmpA);
	}
}

void Scene::DeleteManager(bool a_bFlg)
{
	//敵
	auto en = m_enemy.begin();
	while (en != m_enemy.end())
	{
		if ((!(*en)->GetAlive() && (*en)->GetSize() <= 0) || a_bFlg)
		{
			//中ボスを倒すと
			if ((*en)->GetType() == enemyMiniBoss)
			{
				m_event->SetStopFlg(true);
			}
			en = m_enemy.erase(en);
		}
		else
		{
			en++;
		}
	}
}

void Scene::HitManager()
{
	for (int i = 0; i < m_enemy.size(); i++)
	{
		//敵と自機の当たり判定
		m_enemy[i]->PlayerCD(m_player);
		m_enemy[i]->HitCheckBullet(m_player);
	}
}

void Scene::LoadTex()
{
	//タイトル
	m_titleTex.titleNameTex.Load("Texture/Title/Title_Name.png");
	m_titleTex.titleBackGroundTex.Load("Texture/Title/Title_BackGround.png");
	m_titleTex.titleOptionTextTex.Load("Texture/Title/Title_OptionText.png");
	m_titleTex.titleStartTextTex.Load("Texture/Title/Title_StartText.png");
	m_titleTex.titileSelectTex.Load("Texture/Title/Title_Select.png");
	m_titleTex.titleOptionTex.Load("Texture/Title/Title_Option.png");
	m_titleTex.titleBackTex.Load("Texture/Title/Title_Back.png");

	//ゲーム
	miniBossTex.Load("Texture/miiniBoss.png");

	m_bossTex.bossTex.Load("Texture/Boss.png");
	m_bossTex.cannonUTex.Load("Texture/cannonU.png");
	m_bossTex.cannonDTex.Load("Texture/cannonD.png");
	m_bossTex.voltTex.Load("Texture/volt.png");
	m_bossTex.missileTex.Load("Texture/missile.png");

	m_eventTex.eventStartTex.Load("Texture/player.png");

	backTex.Load("Texture/001.bmp");
	shineTex.Load("Texture/shine.png");

	playerTex.Load("Texture/player.png");
	enemyTex.Load("Texture/enemy.png");
	m_objTex.bulletTex.Load("Texture/bullet.png");
	m_objTex.p_hitTex.Load("Texture/bullet.png");
	m_objTex.p_bomTex.Load("Texture/explosion.png");


}

void Scene::Init()
{
	m_button = make_shared<C_Button>();
	m_button->SetButton(VK_SPACE);

	//シーンの初期
	sceneChange = Game;
	srand(timeGetTime());

	//画像ロード
	LoadTex();

	m_blackOut = make_shared<C_BlackOut>();
	m_blackOut->Init();

	InitTutorial();
	InitGame();


	Reset();
}

void Scene::InitTitle()
{
	m_title.Init();
	m_title.SetTex(this);
}

void Scene::InitTutorial()
{
}

void Scene::InitGame()
{
	//メモリ確保
	m_event = make_shared<C_Event>();
	m_back = make_shared<C_Back>();
	m_back->SetTex(&backTex);
	//動的確保
	m_player = new C_Player();
	m_player->SetTex(&playerTex, this);
}

void Scene::Reset()
{
	//タイトルの初期化
	InitTitle();

	//ゲーム部分の初期化
	m_back->Init();
	slowMotion = 60;

	//自機の初期化
	m_player->Init();

	//敵の初期化
	miniBossFlg = false;
	bossFlg = false;

	//イベントの初期化
	m_event->Init();
	m_event->SetTex(this);


	DeleteManager(true);
}

void Scene::Release()
{
	//タイトル
	m_titleTex.titleNameTex.Release();
	m_titleTex.titleBackGroundTex.Release();
	m_titleTex.titleOptionTextTex.Release();
	m_titleTex.titleStartTextTex.Release();
	m_titleTex.titileSelectTex.Release();
	m_titleTex.titleOptionTex.Release();
	m_titleTex.titleBackTex.Release();

	delete m_player;

	m_bossTex.bossTex.Release();
	m_bossTex.cannonUTex.Release();
	m_bossTex.cannonDTex.Release();
	m_bossTex.voltTex.Release();
	m_bossTex.missileTex.Release();

	miniBossTex.Release();
	m_eventTex.eventStartTex.Release();
	backTex.Release();
	shineTex.Release();
	playerTex.Release();
	enemyTex.Release();
	m_objTex.bulletTex.Release();
	m_objTex.p_hitTex.Release();
	m_objTex.p_bomTex.Release();
}

void Scene::ImGuiUpdate()
{
	//return;

	ImGui::SetNextWindowPos(ImVec2(20, 20), ImGuiSetCond_Once);
	ImGui::SetNextWindowSize(ImVec2(200, 100), ImGuiSetCond_Once);

	// デバッグウィンドウ
	if (ImGui::Begin("Debug Window"))
	{
		ImGui::Text("FPS : %d", APP.m_fps);


		//ImGui::Text("a : %d", m_play);

	}
	ImGui::End();
}