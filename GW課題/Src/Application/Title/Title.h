#pragma once

#include "Application/Utility.h"
#include "Application/Title/Menu/Title_Menu.h"
#include "Application/Title/Name/Title_Name.h"

class Scene;
using namespace Screen;

enum SceneTitle
{
	Name,
	Menu,
};

class C_Title
{
public:

	C_Title(){}
	~C_Title(){}

	void Init();
	void Draw();
	void DrawTitle();

	bool Update(bool a_bSpace);

	void SetTex(Scene* a_pOwner);

private:

	BASE m_back= { {WIDTH,HEIGHT,0},m_back.SIZE / 2,{0,0,0},1.0f,{ Math::Matrix::CreateTranslation(m_back.m_pos)},{nullptr} };

	SceneTitle sceneTitle;

	C_TitleName m_name;
	C_TitleMenu m_menu;
};