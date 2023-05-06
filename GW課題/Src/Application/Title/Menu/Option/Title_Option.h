#pragma once
#include "Application/Utility.h"
#include <DirectXTK/Inc/Keyboard.h>

class Scene;
class C_SelectButton;

using namespace std;

enum SceneOption
{
	Volume,
	Back,
};

class C_TitleOption
{
public:

	C_TitleOption() {  }
	~C_TitleOption() {  }

	void Init(Scene* a_pOwner);
	void Draw();
	bool Update(bool a_bSpace);

	void VolumeChange();


private:

	SceneOption sceneOption;

	bool bTapFlg;

	float volume;

	static const int BUTTON_NUM = 2;
	shared_ptr<BASE> m_vol;
	shared_ptr<BASE> m_back;

	shared_ptr<C_SelectButton> m_buttonList;

};