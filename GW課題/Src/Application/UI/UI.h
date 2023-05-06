#pragma once
using namespace std;

class C_BaseUI;
class C_SceneGame;
class Scene;

class C_UI
{
public:

	C_UI() { Init(); }
	~C_UI(){}


	void Init();
	void Update(C_SceneGame* a_pOwner);
	void Draw();

	void SetTex(Scene* a_pOwner);


private:

	vector<shared_ptr<C_BaseUI>> m_uiList;

};