#pragma once
#include "Application/Utility.h"

class Scene;
class C_SceneGame;

using namespace Alpha;

class C_BaseEvent
{
public:

	enum class EventType
	{
		eve_start,
		eve_miniboss,
		eve_boss,
		eve_end,
		eve_non,
	};


	C_BaseEvent() {}
	~C_BaseEvent() {}

	virtual void Init();
	virtual void Update();
	virtual void Draw();

	void SetType(EventType a_type) { m_eveType = a_type; }
	const EventType GetType() { return m_eveType; }
	const bool GetFlg() { return m_bDeleteFlg; }
	virtual void SetTex(Scene* a_pOwner);
	virtual void SetSceneGame(C_SceneGame* a_pOwner) { m_gameScene = a_pOwner; }

protected:

	Scene* m_pOwner;
	C_SceneGame* m_gameScene;

	bool m_bDeleteFlg=false;

	EventType m_eveType = EventType::eve_non;
	BASE m_data = { {128,72,0},m_data.SIZE / 2,{0,0,0},MIN_ALPHA,{Math::Matrix::Identity},{nullptr} };

};