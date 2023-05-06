#pragma once
#include "Application/Utility.h"

class Scene;
using namespace std;

class C_SelectButton
{
public:
	C_SelectButton(){}
	~C_SelectButton(){}

	void Init(Scene* a_pOwner,float i=1.0f);
	int Update();
	void Draw();

	void Select();

	void AlphaChange();

	void SetNum(int i) { BUTTON_NUM = i; }
	void SetKey(int a_up, int a_down) { UP = a_up, DOWN = a_down; }
	void SetTex(Scene* a_pOwner);

	void AddButton(shared_ptr<BASE> a_obj);


private:

	BASE m_select;

	vector<shared_ptr<BASE>> m_baseList;

	int BUTTON_NUM;

	int UP=VK_UP;
	int DOWN= VK_DOWN;

	bool bTapFlg;
	int nowSelect;

	int deg;
};