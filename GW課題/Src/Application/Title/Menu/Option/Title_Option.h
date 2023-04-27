#pragma once
#include "Application/Utility.h"
#include <DirectXTK/Inc/Keyboard.h>

class Scene;

enum SceneOption
{
	Volume,
	Back,
};

class C_TitleOption
{
public:

	C_TitleOption() { Init(); }
	~C_TitleOption() {  }

	void Init();
	void Draw();
	bool Update(bool a_bSpace);

	void SetTex(Scene* a_pOwner);

	void Select();
	void VolumeChange();


private:

	SceneOption sceneOption;

	bool bTapFlg;

	float volume;


	BASE m_option;
	BASE m_back;
	BASE m_select;

};