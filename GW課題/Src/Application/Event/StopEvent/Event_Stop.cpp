#include "Event_Stop.h"
#include "Application/Scene.h"
#include "Application/Back/Back.h"
#include "Application/Scene/Game/Scene_Game.h"
#include "Application/Object/BaseObject.h"
#include "Application/Object/Enemy/MiniBoss/MiniBoss.h"

void C_EventStop::Init()
{
	createDelay = 0;
	createFlg = false;
}

void C_EventStop::Update()
{
	if (createDelay++ < 100)return;

	if (!createFlg)
	{
		shared_ptr<C_MiniBoss> tmpA = make_shared<C_MiniBoss>();
		tmpA->Init();
		tmpA->SetPos({m_gameScene->GetBackData()->GetPos().x,(float)(360 + tmpA->GetData()->HALF_SIZE.y),0});
		tmpA->SetTex(m_tex, m_pOwner);
		tmpA->SetType(enemyMiniBoss);
		m_gameScene->AddEnemy(tmpA);
		createFlg = true;
	}
	
	for (int i = 0; i < m_gameScene->GetEnemy().size(); i++)
	{
		
		if (m_gameScene->GetEnemy()[i]->GetType()==enemyMiniBoss)
		{
			
			return;
		
		}

	}

	m_bDeleteFlg = true;

}

void C_EventStop::SetTex(Scene* a_pOwner)
{
	m_tex = &a_pOwner->GetTex()->miniBossTex; 
	m_pOwner = a_pOwner;
}
