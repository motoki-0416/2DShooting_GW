#include "Application/Scene.h"

#include "Scene_Game.h"
#include "Application/BlackOut/BlackOut.h"

#include "Application/UI/UI.h"

#include "Application/Program/Slow/Slow.h"

#include "Application/Event/Event.h"
#include "Application/BlackOut/BlackOut.h"

#include "Application/Back/Back.h"
#include "Application/Object/Enemy/enemy.h"
#include "Application/Object/Enemy/MoveEnemy/MoveEnemy.h"
#include "Application/Object/Enemy/MiniBoss/MiniBoss.h"
#include "Application/Object/Enemy/Boss/Boss.h"
#include "Application/Object/Player/Player.h"

//初期化
void C_SceneGame::Init(Scene* a_pOwner)
{
	m_pOwner = a_pOwner;

	//変数
	enemyDelay = 40;
	moveEnemyDelay = 300;
	delayDown = 0;
	//敵の初期化
	miniBossFlg = false;
	bossFlg = false;

	m_ui = make_shared<C_UI>();
	m_ui->SetTex(a_pOwner);
	m_ui->Init();

	m_slow = make_shared<C_Slow>();

	m_event = make_shared<C_Event>();
	m_back = make_shared<C_Back>();
	m_back->SetTex(a_pOwner);
	m_back->Init();

	m_player = make_shared<C_Player>();
	m_player->SetTex(a_pOwner);
	m_player->SetOwner(this);

	//ゲーム部分の初期化
	m_slow->Init();

	//自機の初期化
	m_player->Init();

	//イベントの初期化
	m_event->Init();
	m_event->SetTex(a_pOwner, this);

}


//処理
void C_SceneGame::Update()
{
	//シーンチェンジ  イベントがリザルトor自機が死亡
	if (m_event->GetEvent() == C_Event::Event::result || m_event->GetEvent() == C_Event::Event::ded)
	{
		if (GetBlackOutData()->ChangeAlpha(true))sceneChange = true;
	}

	//UI
	m_ui->Update(this);

	//スローモーション（お試し）
	if (m_slow->Update())return;

	//背景処理
	m_back->Update();

	//自機の処理
	m_player->Update((int)m_event->GetEvent());

	//敵の処理
	for (int i = 0; i < m_enemy.size(); i++)
	{
		m_enemy[i]->Update();
	}

	//イベントの処理
	m_event->Update(*m_back);

	//座標更新
	CommitPos(m_back->GetMove());
	//当たり判定
	HitManager();
	//敵出現
	CreateManager((int)m_event->GetEvent());
	//削除
	DeleteManager();
}


//描画
void C_SceneGame::Draw()
{

	m_back->Draw();

	for (int i = 0; i < m_enemy.size(); i++)
	{
		m_enemy[i]->Draw();
	}

	m_player->Draw();

	m_event->Draw();

	//☆
	Math::Color color = { 0,0,0,1 };
	SHADER.m_spriteShader.SetMatrix(Math::Matrix::Identity);
	SHADER.m_spriteShader.DrawBox(-480, 0, 160, 360, &color, true);
	SHADER.m_spriteShader.DrawBox(480, 0, 160, 360, &color, true);

	m_ui->Draw();

	m_blackOut->Draw();

}

void C_SceneGame::SetSlow(int a_stop)
{
	m_slow->SetSlow(a_stop);
}


//生成
void C_SceneGame::CreateManager(int a_eve)
{
	switch (a_eve)
	{
	case 2://中ボス
		delayDown = 10;
		
	case 1://スタート
	case 3://ボス
	case 4://ボス撃退後
	case 6://リザルト画面へ
		return;
	default:
		break;
	}

	if (moveEnemyDelay-- <= 0)
	{
		
		float posX = rand() % 200 - 100;
		
		for (int i = 0; i < 3; i++)
		{
			shared_ptr<C_MoveEnemy> tmpA = make_shared<C_MoveEnemy>();
			tmpA->Init();
			tmpA->SetPos({ posX,(float)(360 + tmpA->GetData()->HALF_SIZE.y + (i * 64)),0 });
			tmpA->SetAng(-(i * 10));
			tmpA->SetType(enemyNormal);
			tmpA->SetTex(&m_pOwner->GetTex()->moveEnemyTex, m_pOwner);
			m_enemy.push_back(tmpA);
		}
		
		moveEnemyDelay = 300;
	
	}

	if (enemyDelay-- <= 0)
	{
	
		shared_ptr<C_Enemy> tmpA = make_shared<C_Enemy>();
		tmpA->Init();
		float posX = rand() % 600 - 300;
		tmpA->SetPos({ posX,(float)(360 + tmpA->GetData()->HALF_SIZE.y),0 });
		tmpA->SetTex(&m_pOwner->GetTex()->enemyTex, m_pOwner);
		tmpA->SetType(enemyNormal);
		m_enemy.push_back(tmpA);

		enemyDelay = 40 - delayDown;
	
	}

}


//削除処理
void C_SceneGame::DeleteManager(bool a_bFlg)
{
	//敵
	auto en = m_enemy.begin();
	while (en != m_enemy.end())
	{
		if ((!(*en)->GetAlive() && (*en)->GetSize() <= 0) || a_bFlg)
		{

			en = m_enemy.erase(en);

		}
		else
		{
			en++;
		}
	}
}


//当たり判定
void C_SceneGame::HitManager()
{
	for (int i = 0; i < m_enemy.size(); i++)
	{
		//敵と自機の当たり判定
		m_enemy[i]->PlayerCD(*m_player);
		m_enemy[i]->HitCheckBullet(this);
	}
}


//座標設定
void C_SceneGame::CommitPos(Math::Vector3 a_move)
{

	for (int i = 0; i < m_enemy.size(); i++)
	{

		m_enemy[i]->CommitPos(a_move);

	}

}
