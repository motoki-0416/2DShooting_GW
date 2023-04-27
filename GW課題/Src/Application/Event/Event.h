#pragma once
using namespace std;

class C_Back;
class C_EventStart;
class C_EventStop;
class Scene;

enum Event
{
	null,
	start,
	stop,
	boss,
};

class C_Event
{

public:
	C_Event(){}
	~C_Event(){}

	void Init();
	void Update(C_Back& a_back);
	void Draw();

	void SetTex( Scene* a_pOwner);
	void SetStopFlg(bool a_flg) { stopFlg = a_flg; }

	int GetEvent() { return event; }

private:
	Event event;
	shared_ptr<C_EventStart>m_start;
	shared_ptr<C_EventStop>m_stop;

	bool startFlg;
	bool stopFlg;
};