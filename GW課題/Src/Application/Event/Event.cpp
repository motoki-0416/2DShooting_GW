#include "Event.h"
#include "Application/Event/Start/Event_Start.h"
#include "Application/Event/StopEvent/Event_Stop.h"
#include "Application/Back/Back.h"
#include "Application/Scene.h"

void C_Event::Init()
{
	startFlg = false;
	stopFlg = false;
	//m_start.reset();
	//作成
	m_start = make_shared<C_EventStart>();
	m_start->Init();
	
	m_stop = make_shared<C_EventStop>();
	m_stop->Init();
}

void C_Event::Update(C_Back& a_back)
{
	//ゲームスタートのイベント
	if (!startFlg)
	{
		event = start;
		if (m_start->Update())
		{
			a_back.SetMove({ 0,0,0 });
		}
		else
		{
			startFlg = true;
		}
	}
	else if (a_back.GetPos().y<500&&!stopFlg)
	{
		event = stop;
		if (m_stop->Update())
		{
			a_back.SetMove({ 0,0,0 });
		}
		else
		{
			stopFlg = true;
		}
	}
	else if (a_back.GetPos().y < -a_back.GetData().HALF_SIZE.y + HALF_HEIGHT)
	{
		event = boss;
		a_back.SetMove({ 0,0,0 });
	}
	else
	{		
		event = null;
		a_back.SetMove({ 0,-1,0 });
	}
}


void C_Event::Draw()
{
	//イベントの表示
	m_start->Draw();
	m_stop->Draw();
}

void C_Event::SetTex(Scene* a_pOwner)
{
	m_start->SetTex(a_pOwner);
}

