#pragma once
#include "Application/Scene/BaseScene.h"

class C_Button;
class C_BlackOut;
class C_Back;
class C_Event;
class C_Player;
class C_BaseObject;
class C_UI;
class C_Slow;


class C_SceneGame :public C_BaseScene
{
public:

	C_SceneGame() {};
	~C_SceneGame() {};

	void Init(Scene* a_pOwner)override;
	void Update()override;
	void Draw()override;

	shared_ptr<C_Player> GetPlayer() { return m_player; }

	void SetScore(int i) { score += i; }

	void SetSlow(int a_stop = 60);
	;
	shared_ptr<C_Back>GetBackData() { return m_back; }
	vector<shared_ptr<C_BaseObject>> GetEnemy() { return m_enemy; }


	void AddEnemy(shared_ptr<C_BaseObject> a_add) { m_enemy.push_back(a_add); }

private:

	Scene* m_pOwner;

	shared_ptr<C_UI> m_ui;
	shared_ptr<C_Slow>m_slow;
	shared_ptr<C_Event> m_event;

	shared_ptr<C_Player> m_player;


	bool miniBossFlg;
	bool bossFlg;

	int delayDown;
	int enemyDelay;
	int moveEnemyDelay;

	//îwåi
	shared_ptr<C_Back> m_back;

	//ìG
	vector<shared_ptr<C_BaseObject>> m_enemy;


	//ä÷êî
	void CommitPos(Math::Vector3 a_move);
	void CreateManager(int a_eve);
	void DeleteManager(bool m_bFlg = false);
	void HitManager();

};