#include "Event_Boss.h"
#include "Application/Scene.h"
#include "Application/Scene/Game/Scene_Game.h"
#include "Application/Back/Back.h"
#include "Application/Object/Enemy/Boss/Boss.h"
void C_EventBoss::Init()
{
	
	boxFlg = false;
	boxAlpha = 0.0f;
	boxDelay = 60;
	flg = false;

	warningDelay = 60;
	
	createFlg = false;
	createDelay = 0;
}

void C_EventBoss::Draw()
{
	Math::Color color = { 0,0,0, boxAlpha };
	SHADER.m_spriteShader.SetMatrix(Math::Matrix::Identity);
	SHADER.m_spriteShader.DrawBox(0, 0, 320, 100, &color, true);

	SHADER.m_spriteShader.SetMatrix(m_warning.m_mat);
	SHADER.m_spriteShader.DrawTex(m_warning.m_pTex, Math::Rectangle{ 0,0,(long)m_warning.SIZE.x,(long)m_warning.SIZE.y }, m_warning.m_alpha);
}

void C_EventBoss::Update()
{
	//ワーニング文字の移動
	if (m_warning.m_pos.x < 600)
	{
		m_warning.m_pos.x += 10;
		if (m_warning.m_pos.x >= 0)
		{
			if (warningDelay-- > 0)
			{
				m_warning.m_pos.x = 0;
			}
		}
		m_warning.m_mat = Math::Matrix::CreateTranslation(m_warning.m_pos);
	}

	//ボックスの表示
	if (!boxFlg)
	{
		if (boxAlpha > 0.0f && flg && boxDelay-- < 0)
		{
			boxAlpha -= 0.008;
			if (boxAlpha <= 0.0f)
			{
				boxFlg = true;
			}
		}
		else if (boxAlpha < 0.5f)
		{
			boxAlpha += 0.008;
			if (boxAlpha >= 0.5f)
			{
				boxAlpha = 0.5f;
				flg = true;
			}
		}
	}

	//敵が横にはける処理
	for (int i=0;i< m_gameScene->GetEnemy().size(); i++)
	{
		if (m_gameScene->GetEnemy()[i]->GetType() != enemyBoss)
		{
			if (m_gameScene->GetEnemy()[i]->GetPos().x >= 0)
			{
				m_gameScene->GetEnemy()[i]->SetMove({ 3,-1,0 });
			
			}
			else
			{
				m_gameScene->GetEnemy()[i]->SetMove({ -3,-1,0 });
			}

			m_gameScene->GetEnemy()[i]->SetAlpha(0.03);

			m_gameScene->GetEnemy()[i]->SetCDFlg(false);
			
		}
	}

	if (createDelay++ > 120 && !createFlg)
	{
		shared_ptr<C_Boss>tmpA = make_shared<C_Boss>();
		tmpA->Init();
		tmpA->SetPos({ m_gameScene->GetBackData()->GetPos().x,(float)(360 + tmpA->GetData()->HALF_SIZE.y),0});
		tmpA->SetTex(m_pOwner);
		tmpA->SetType(enemyBoss);
		m_gameScene->AddEnemy(tmpA);
		createFlg = true;
		return;
	}


	for (int i = 0; i < m_gameScene->GetEnemy().size(); i++)
	{

		if (m_gameScene->GetEnemy()[i]->GetType() == enemyBoss)
		{

			if (!m_gameScene->GetEnemy()[i]->GetAlive())
			{

				m_bDeleteFlg = true;

			}

		}

	}

}

void C_EventBoss::SetTex(Scene* a_pOwner)
{
	m_pOwner = a_pOwner;
	m_warning.m_pTex = &a_pOwner->GetTex()->eventWarningTex;
}
