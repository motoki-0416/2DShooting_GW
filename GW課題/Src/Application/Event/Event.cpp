#include "Event.h"
#include "Application/Event/Start/Event_Start.h"
#include "Application/Event/StopEvent/Event_Stop.h"
#include "Application/Event/Boss/Event_Boss.h"
#include "Application/Event/End/Event_End.h"
#include "Application/Back/Back.h"
#include "Application/Scene.h"
#include "Application/Scene/Game/Scene_Game.h"
#include "Application/BlackOut/BlackOut.h"

void C_Event::Init()
{
	dedDelay = 0;
	startFlg = false;
	stopFlg = false;
	bossFlg = false;
	endFlg = false;
	event = Event::null;
}

void C_Event::Update(C_Back& a_back)
{

	//自機が志望した場合
	if (!m_pSceneGame->GetPlayer()->GetAlive())
	{
		if (dedDelay++ > 80)
		{
			event = Event::ded;
			return;
		}
	}


	//ゲームスタートのイベント
	if (!startFlg)
	{

		a_back.SetStopFlg(true);
		m_pSceneGame->GetBlackOutData()->ChangeAlpha(false);

		if (event == Event::null)
		{
			shared_ptr<C_EventStart> st = make_shared<C_EventStart>();
			st->SetTex(m_pOwner);
			st->SetSceneGame(m_pSceneGame);
			st->SetType(C_BaseEvent::EventType::eve_start);
			st->Init();
			m_event.push_back(st);
		}

		event = Event::start;

	}
	//中ボス
	else if (a_back.GetPos().y < 500 && !stopFlg)
	{
		if (event == Event::null)
		{
			a_back.SetMove(0);
			shared_ptr<C_EventStop> st = make_shared<C_EventStop>();
			st->SetTex(m_pOwner);
			st->SetSceneGame(m_pSceneGame);
			st->SetType(C_BaseEvent::EventType::eve_miniboss);
			st->Init();
			m_event.push_back(st);

		}

		event = Event::stop;

	}
	//ボス
	else if (a_back.GetPos().y < -a_back.GetData().HALF_SIZE.y + HALF_HEIGHT + 200 && !bossFlg)
	{

		if (event == Event::null)
		{
			a_back.SetMove(0);
			shared_ptr<C_EventBoss> bo = make_shared<C_EventBoss>();
			bo->SetTex(m_pOwner);
			bo->SetSceneGame(m_pSceneGame);
			bo->SetType(C_BaseEvent::EventType::eve_boss);
			bo->Init();
			m_event.push_back(bo);

		}

		event = Event::boss;
	}
	//終了
	else if (bossFlg && !endFlg)
	{
		if (event == Event::null)
		{
			a_back.SetMove(0);
			shared_ptr<C_EventEnd> en = make_shared<C_EventEnd>();
			en->SetTex(m_pOwner);
			en->SetSceneGame(m_pSceneGame);
			en->SetType(C_BaseEvent::EventType::eve_end);
			en->Init();
			m_event.push_back(en);

		}

		event = Event::end;

	}
	//リザルトへ
	else if (endFlg)
	{

		event = Event::result;

	}
	else
	{
		event = Event::null;
		a_back.SetMove(-1);
		a_back.SetStopFlg(false);
	}

	//イベント処理
	for (int i = 0; i < m_event.size(); i++)
	{

		m_event[i]->Update();

	}


	DeleteManager();

}

void C_Event::Draw()
{
	for (int i = 0; i < m_event.size(); i++)
	{
		m_event[i]->Draw();
	}
}

void C_Event::DeleteManager()
{
	auto ev = m_event.begin();
	while (ev != m_event.end())
	{
		if (((*ev)->GetFlg()))
		{
			switch ((*ev)->GetType())
			{
			case C_BaseEvent::EventType::eve_start:
				startFlg = true;
				break;

			case C_BaseEvent::EventType::eve_miniboss:
				stopFlg = true;
				break;

			case C_BaseEvent::EventType::eve_boss:
				bossFlg = true;
				break;

			case C_BaseEvent::EventType::eve_end:
				endFlg = true;
				break;
			default:
				break;
			}

			event = Event::null;
			ev = m_event.erase(ev);
		}
		else
		{
			ev++;
		}
	}

}

void C_Event::SetTex(Scene* a_pOwner, C_SceneGame* a_pGame)
{
	m_pOwner = a_pOwner;
	m_pSceneGame = a_pGame;
}
