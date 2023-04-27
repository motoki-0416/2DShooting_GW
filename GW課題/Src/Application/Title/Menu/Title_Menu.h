#pragma once

#include "Application/Utility.h"
#include "Application/Title/Menu/Option/Title_Option.h"

using namespace Alpha;
class Scene;

enum SceneSlect
{
	Start,
	Option,
};

class C_TitleMenu
{
public:

	C_TitleMenu() { Init(); }
	~C_TitleMenu() {}

	void Init();
	void Draw();
	bool Update(bool a_bSpace);
	void UpdateOption(bool a_bSpace);


	void SelectMenu();
	void AlphaChange(BASE* a_data,bool a_bool=true);
	void SetTex(Scene* a_pOwner);


private:

	SceneSlect sceneSelect;
	
	const float CHANGE_ALPHA = 0.01;
	bool bAlpha;

	bool bOptionFlg;

	bool bTapFlg;
	bool bStartFlg;

	//BASE m_menu;
	BASE m_startText= { {128,72,0},m_startText.SIZE / 2,{0,0,0},0.0f,{Math::Matrix::CreateTranslation(m_startText.m_pos)},{nullptr} };
	BASE m_select= { {64,64,0},m_select.SIZE / 2,{-100,0,0},0.0f,{Math::Matrix::CreateTranslation(m_select.m_pos)},{nullptr} };
	BASE m_optionText= { {128,72,0},m_optionText.SIZE / 2,{0,-200,0},0.0f,{Math::Matrix::CreateTranslation(m_optionText.m_pos)},{nullptr} };


	C_TitleOption m_option;

};