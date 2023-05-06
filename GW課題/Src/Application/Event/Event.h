#pragma once
using namespace std;

class C_Back;
class C_BaseEvent;
class Scene;
class C_SceneGame;


class C_Event
{

public:


	enum class Event
	{
		null,
		start,
		stop,
		boss,
		end,
		ded,
		result,
	};

	C_Event(){}
	~C_Event(){}

	void Init();
	void Update(C_Back& a_back);
	void Draw();

	void DeleteManager();

	void SetTex(Scene* a_pOwner,C_SceneGame* a_pGame);
	void SetStopFlg(bool a_flg) { stopFlg = a_flg; }

	Event GetEvent() { return event; }

private:

	int dedDelay;

	Event event;
	vector<shared_ptr<C_BaseEvent>> m_event;

	bool startFlg;
	bool stopFlg;
	bool bossFlg;
	bool endFlg;

	Scene* m_pOwner;
	C_SceneGame* m_pSceneGame;
};