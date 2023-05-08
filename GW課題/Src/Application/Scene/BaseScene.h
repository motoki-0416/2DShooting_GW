#pragma once

using namespace std;

class C_BlackOut;
class Scene;

class C_BaseScene
{
public:

	enum class SceneType
	{
		null,
		scene_title,
		scene_game,
		scene_result,
	};

	enum class NowSceneSelect
	{
		select_title,
		select_game,
		select_result,
	};


	C_BaseScene();
	~C_BaseScene() {  }

	virtual void Init(Scene* a_pOwner);
	virtual void Init(Scene* a_pOwner, bool a_flg);
	virtual void Update();
	virtual void Draw();
	
	void SetType(SceneType a_type) { m_sceneType = a_type; }
	void SetBlackOutData(shared_ptr<C_BlackOut>a_data);
	virtual void SetTex(Scene* a_pOwner);
	virtual void SetResult(int a_score, int a_enemyNum){}
	void SetNowSelectScene(NowSceneSelect i) { m_select = i; }

	shared_ptr<C_BlackOut> GetBlackOutData() { return m_blackOut; }
	SceneType GetType() { return m_sceneType; }
	bool GetSceneChange() { return sceneChange; }
	bool GetAnyFlg() { return anyFlg; }

	virtual int GetScore() { return score; }
	virtual int GetEnemyDed() { return enemyDedNum; }

	NowSceneSelect GetNowSelectScene() { return m_select; }

protected:

	bool anyFlg;

	int score;
	int enemyDedNum;
	bool sceneChange;

	NowSceneSelect m_select= NowSceneSelect::select_title;

	SceneType m_sceneType = SceneType::null;

	//ブラックアウト
	shared_ptr<C_BlackOut> m_blackOut;

};