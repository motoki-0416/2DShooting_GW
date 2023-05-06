#pragma once
#include "Application/Utility.h"

using namespace Alpha;
using namespace std;

class Scene;
class C_TitleOption;
class C_SelectButton;

class C_TitleMenu
{
public:

	C_TitleMenu() { }
	~C_TitleMenu() {}

	void Init(Scene* a_pOwner);
	void Draw();
	bool Update(bool a_bSpace);

private:

	bool bAlpha;
	bool bOptionFlg;
	bool bStartFlg;

	static const int BUTTON_NUM = 2;

	shared_ptr<BASE> m_startButton;
	shared_ptr<BASE> m_optionButton;

	shared_ptr<C_SelectButton> m_buttonList;

	shared_ptr<C_TitleOption> m_option;

};