#include "ReturnButton.h"
#include "Application/Program/selectButton/SelectButton.h"
#include "Application/Scene/Result/Scene_Result.h"

void C_ReturnButton::Init(Scene* a_pOwner)
{
	returnFlg = false;

	m_buttonList = make_shared<C_SelectButton>();

	m_titleBack = make_shared<BASE>();
	m_titleBack->SIZE = { 164,82,0 };
	m_titleBack->HALF_SIZE = m_titleBack->SIZE / 2;
	m_titleBack->m_pos = { -130.0f,-200.0f,0.0f };
	m_titleBack->m_alpha = 0.0f;
	m_titleBack->m_mat = {};
	m_titleBack->m_pTex = &a_pOwner->GetTex()->result_TitleTex;
	m_buttonList->AddButton(m_titleBack);

	m_retry = make_shared<BASE>();
	m_retry->SIZE = { 157,82,0 };
	m_retry->HALF_SIZE = m_retry->SIZE / 2;
	m_retry->m_pos = { 130.0f,-200.0f,0.0f };
	m_retry->m_alpha = 0.0f;
	m_retry->m_mat = {};
	m_retry->m_pTex = &a_pOwner->GetTex()->result_RetryTex;
	m_buttonList->AddButton(m_retry);

	m_buttonList->Init(a_pOwner);
	m_buttonList->SetKey(VK_RIGHT, VK_LEFT);
	m_buttonList->SetNum(BUTTON_NUM);


}

bool C_ReturnButton::Update(bool a_bSpace, C_SceneResult* a_pResScene)
{

	switch (m_buttonList->Update())
	{
	case 0://タイトル
		if (!a_bSpace && GetAsyncKeyState(VK_SPACE) & 0x8000)
		{
			a_pResScene->SetNowSelectScene(C_SceneResult::NowSceneSelect::select_title);
			returnFlg =true;
		}
		break;

	case 1://ゲーム・リトライ
		if (!a_bSpace && GetAsyncKeyState(VK_SPACE) & 0x8000)
		{
			a_pResScene->SetNowSelectScene(C_SceneResult::NowSceneSelect::select_game);
			returnFlg =true;
		}
		break;

	default:
		break;
	}

	return  returnFlg;
}

void C_ReturnButton::Draw()
{

	m_buttonList->Draw();

}
