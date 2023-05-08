#include "BaseScene.h"
#include "Application/Object/BaseObject.h"
#include "Application/BlackOut/BlackOut.h"

C_BaseScene::C_BaseScene()
{
	score = 0;
	enemyDedNum = 0;

	m_blackOut = make_shared<C_BlackOut>();
	m_blackOut->Init();
	sceneChange = false;
	anyFlg = false;
}

void C_BaseScene::Init(Scene* a_pOwner)
{
	
}

void C_BaseScene::Init(Scene* a_pOwner, bool a_flg)
{
}

void C_BaseScene::Update()
{
}

void C_BaseScene::Draw()
{
}

void C_BaseScene::SetBlackOutData(shared_ptr<C_BlackOut> a_data)
{
	m_blackOut = a_data;
}

void C_BaseScene::SetTex(Scene* a_pOwner)
{
}
