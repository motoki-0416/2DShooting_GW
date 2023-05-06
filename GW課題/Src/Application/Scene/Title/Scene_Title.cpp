#include "Scene_Title.h"
#include "Application/BlackOut/BlackOut.h"
#include "Application/Object/Player/Player.h"
#include "Application/Title/Title.h"

void C_SceneTitle::Init(Scene* a_pOwner)
{
	m_title = make_shared<C_Title>();
	m_title->Init(a_pOwner);
	m_title->SetTex(a_pOwner);

	m_player = make_shared<C_Player>();
	m_player->Init();
	m_player->SetPos({ -200, 0, 0 });
	m_player->SetTex(a_pOwner);
}

void C_SceneTitle::Update()
{

	m_player->Update(0);

	static bool bSpace = false;
	if (m_title->Update(bSpace))
	{
		//ブラックアウト
		if (m_blackOut->ChangeAlpha(true))
		{
			sceneChange = true;
		}
	}
	else
	{

		m_blackOut->ChangeAlpha(false);
	}

	GetAsyncKeyState(VK_SPACE) & 0x8000 ? bSpace = true : bSpace = false;
}

void C_SceneTitle::Draw()
{
	
	m_title->Draw();

	m_player->Draw();

	//☆
	Math::Color color = { 0,0,0,1 };
	SHADER.m_spriteShader.SetMatrix(Math::Matrix::Identity);
	SHADER.m_spriteShader.DrawBox(-480, 0, 160, 360, &color, true);
	SHADER.m_spriteShader.DrawBox(480, 0, 160, 360, &color, true);


	m_blackOut->Draw();
}

void C_SceneTitle::SetTex(Scene* a_pOwner)
{
}
