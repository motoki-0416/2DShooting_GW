#pragma once
#include "Application/Utility.h"
#include "Application/Scene.h"

class C_SelectButton;
class C_SceneResult;

class C_ReturnButton
{
public:
	C_ReturnButton(){}
	~C_ReturnButton(){}

	

	void Init(Scene* a_pOwner);
	bool Update(bool a_bSpace,C_SceneResult* a_pResScene);
	void Draw();

private:

	static const int BUTTON_NUM = 2;
	shared_ptr<BASE> m_titleBack;
	shared_ptr<BASE>m_retry;
	
	bool returnFlg;

	shared_ptr<C_SelectButton> m_buttonList;
};