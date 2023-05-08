#include "Application/Scene/Result/Scene_Result.h"
#include "Application/Result/Number/Result_Number.h"
#include "Application/Result/Return/ReturnButton.h"
#include "Application/Scene.h"
#include "Application/BlackOut/BlackOut.h"
#include "Math.h"

void C_SceneResult::Init(Scene* a_pOwner, bool a_flg)
{
	m_pOwner = a_pOwner;

	if (!a_flg)m_game.SIZE = { 350,Y,0 }, m_game.m_pos = { 10,270,0 }, m_game.m_mat = Math::Matrix::CreateScale(1.5) * Math::Matrix::CreateTranslation(m_game.m_pos);

	gameClearFlg = a_flg;




	//スコア

	if (gameClearFlg)
	{
		scoreNum += 100000;
	}

	static const int D = 350000;
	static const int C = 500000;
	static const int B = 800000;
	static const int A = 1200000;

	if (scoreNum > A)
	{
		srcRank = 4;
		rankRGB = { 1.0f,0.0f,1.0f };
	}
	else if (scoreNum > B)
	{
		srcRank = 3;
		rankRGB = { 1.0f,0.0f,0.0f };
	}
	else if (scoreNum > C)
	{
		srcRank = 2;
		rankRGB = { 0.0f,0.0f,1.0f };
	}
	else if (score > D)
	{
		srcRank = 1;
		rankRGB = { 0.0f,1.0f,0.0f };
	}
	else
	{
		srcRank = 0;
		rankRGB = { 0.5f,0.5f,0.5f };
	}

	sizeMove = 0;
	rankDelay = 60;
	rankSize = 5.0f;
	
	//スコア番号

	static const int NUMBER_POS = 125;


	shared_ptr<C_ResultNumber> tmpA = make_shared<C_ResultNumber>();
	tmpA->SetSize();
	tmpA->Init(a_pOwner, score);
	tmpA->SetPos({ NUMBER_POS,100,0 });
	m_number.push_back(tmpA);


	shared_ptr<C_ResultNumber> tmpB = make_shared<C_ResultNumber>();
	tmpB->SetSize();
	tmpB->Init(a_pOwner, enemyDedNum);
	tmpB->SetPos({ NUMBER_POS,-20,0 });
	m_number.push_back(tmpB);


	shared_ptr<C_ResultNumber> tmpC = make_shared<C_ResultNumber>();
	tmpC->SetSize(2);
	tmpC->Init(a_pOwner, scoreNum);
	tmpC->SetPos({ 63,-160,0 });
	m_number.push_back(tmpC);

	m_button = make_shared<C_ReturnButton>();
	m_button->Init(a_pOwner);

	SetTex(a_pOwner);

}

void C_SceneResult::Update()
{
	static bool bSpace = false;

	if (m_button->Update(bSpace, this))
	{
		if (m_blackOut->ChangeAlpha(true))
		{
			sceneChange = true;
		}
	}
	else
	{
		m_blackOut->ChangeAlpha(false);
	}

	RankUpdate();

	GetAsyncKeyState(VK_SPACE) & 0x8000 ? bSpace = true : bSpace = false;
}

void C_SceneResult::Draw()
{

	//背景
	SHADER.m_spriteShader.SetMatrix(m_back.m_mat);
	SHADER.m_spriteShader.DrawTex(m_back.m_pTex, Math::Rectangle{ 0,0,(long)m_back.SIZE.x,(long)m_back.SIZE.y }, m_back.m_alpha);

	SHADER.m_spriteShader.SetMatrix(Math::Matrix::Identity);
	Math::Color color = { 0.2f,0.2f,0.2f,0.5f };
	SHADER.m_spriteShader.DrawBox(0, 0, 290, 340, &color, true);
	color = { 0.0f,0.0f,0.0f,1.0f };
	SHADER.m_spriteShader.DrawBox(0, 0, 290, 340, &color, false);

	//ゲームクリアorゲームオーバー
	if (!gameClearFlg)
	{
		Math::Color gameColor = { 1.0f,0.0f,0.0f,m_game.m_alpha };
		SHADER.m_spriteShader.SetMatrix(m_game.m_mat);
		Math::Rectangle srcRect = { 0,Y,(long)m_game.SIZE.x,(long)m_game.SIZE.y };
		SHADER.m_spriteShader.DrawTex(m_game.m_pTex, 0, 0, (long)m_game.SIZE.x, (long)m_game.SIZE.y, &srcRect, &gameColor, Math::Vector2(0.5f, 0.5f));
	}
	//クリアボーナス
	else
	{
		Math::Color gameColor = { 1.0f,1.0f,0.0f,m_game.m_alpha };
		SHADER.m_spriteShader.SetMatrix(m_game.m_mat);
		Math::Rectangle srcRect = { 0,0,(long)m_game.SIZE.x,(long)m_game.SIZE.y };
		SHADER.m_spriteShader.DrawTex(m_game.m_pTex, 0, 0, (long)m_game.SIZE.x, (long)m_game.SIZE.y, &srcRect, &gameColor, Math::Vector2(0.5f, 0.5f));

		SHADER.m_spriteShader.SetMatrix(m_bonus.m_mat);
		SHADER.m_spriteShader.DrawTex(m_bonus.m_pTex, Math::Rectangle{ 0,Y * 2,(long)m_bonus.SIZE.x,(long)m_bonus.SIZE.y }, m_bonus.m_alpha);
	}

	//スコア
	SHADER.m_spriteShader.SetMatrix(m_score.m_mat);
	SHADER.m_spriteShader.DrawTex(m_score.m_pTex, Math::Rectangle{ 0,Y * 3,(long)m_score.SIZE.x,(long)m_score.SIZE.y }, m_score.m_alpha);

	//敵
	SHADER.m_spriteShader.SetMatrix(m_ded.m_mat);
	SHADER.m_spriteShader.DrawTex(m_ded.m_pTex, Math::Rectangle{ 0,Y * 4,(long)m_ded.SIZE.x,(long)m_ded.SIZE.y }, m_ded.m_alpha);

	//ランク
	color = { rankRGB.x,rankRGB.y,rankRGB.z,m_rank.m_alpha };
	SHADER.m_spriteShader.SetMatrix(m_rank.m_mat);
	Math::Rectangle srcRect = { (long)(m_rank.SIZE.x * srcRank),0,(long)m_rank.SIZE.x,(long)m_rank.SIZE.y };
	SHADER.m_spriteShader.DrawTex(m_rank.m_pTex, 0, 0, (long)m_rank.SIZE.x, (long)m_rank.SIZE.y, &srcRect, &color, Math::Vector2(0.5f, 0.5f));

	//トータル
	color = { 0.5f,1.0f,0.5f,m_total.m_alpha };
	SHADER.m_spriteShader.SetMatrix(m_total.m_mat);
	srcRect = { 0,Y * 5,(long)m_total.SIZE.x,(long)m_total.SIZE.y };
	SHADER.m_spriteShader.DrawTex(m_total.m_pTex, 0, 0, (long)m_total.SIZE.x, (long)m_total.SIZE.y, &srcRect, &color, Math::Vector2(0.5f, 0.5f));

	//番号
	for (int i = 0; i < m_number.size(); i++)
	{
		m_number[i]->Draw();
	}

	//ボタン
	m_button->Draw();


	color = { 0,0,0,1 };
	SHADER.m_spriteShader.SetMatrix(Math::Matrix::Identity);
	SHADER.m_spriteShader.DrawBox(-480, 0, 160, 360, &color, true);
	SHADER.m_spriteShader.DrawBox(480, 0, 160, 360, &color, true);


	//ブラックアウト
	m_blackOut->Draw();

}

void C_SceneResult::SetTex(Scene* a_pOwner)
{

	m_back.m_pTex = &a_pOwner->GetTex()->result_BackTex;

	m_total.m_pTex = &a_pOwner->GetTex()->resultTex;
	m_game.m_pTex = &m_pOwner->GetTex()->resultTex;
	m_score.m_pTex = &m_pOwner->GetTex()->resultTex;
	m_bonus.m_pTex = &m_pOwner->GetTex()->resultTex;
	m_ded.m_pTex = &m_pOwner->GetTex()->resultTex;
	m_rank.m_pTex = &m_pOwner->GetTex()->resultRankTex;
}

void C_SceneResult::SetResult(int a_score, int a_enemyNum)
{
	int bonus = 0;

	score = a_score;

	enemyDedNum = a_enemyNum;

	scoreNum = score + (enemyDedNum * 1000);
}

void C_SceneResult::RankUpdate()
{
	if ( rankDelay-- > 0.0f)return;

	//ランクアルファ値
	if (m_rank.m_alpha < 1.0f)m_rank.m_alpha += 0.01;

	//サイズ変更
	if (rankSize > 2.0f)rankSize -= 0.01+sizeMove;

	sizeMove += 0.0004;
	
	rankScaleMat = Math::Matrix::CreateScale(rankSize);
	m_rank.m_mat = rankScaleMat *  Math::Matrix::CreateTranslation(m_rank.m_pos);
}

