#pragma once
using namespace std;

enum State
{
	Free,				// 入力が無い
	Press,				// 押された瞬間
	Hold,	// 押している間
	Release,// 離された瞬間
};


class C_Button
{
public:
	C_Button() {}
	~C_Button() {}

	void PreUpdate() { m_needUpdate = true; }

	void Update();

	void SetButton(int a_name) { m_name = a_name; }

	// 強制的に入力無しの状態にする
	void NoInput() { m_state = Free; }

	/*short GetState() const { return m_state; }*/

	State GetCode() { return m_state;}

protected:
	//使用するボタン
	int m_name;

	// 入力の状態
	State m_state = Free;

	// 重複しての更新を防ぐ
	bool m_needUpdate = true;
};