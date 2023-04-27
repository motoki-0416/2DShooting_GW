#pragma once
using namespace std;

enum State
{
	Free,				// ���͂�����
	Press,				// �����ꂽ�u��
	Hold,	// �����Ă����
	Release,// �����ꂽ�u��
};


class C_Button
{
public:
	C_Button() {}
	~C_Button() {}

	void PreUpdate() { m_needUpdate = true; }

	void Update();

	void SetButton(int a_name) { m_name = a_name; }

	// �����I�ɓ��͖����̏�Ԃɂ���
	void NoInput() { m_state = Free; }

	/*short GetState() const { return m_state; }*/

	State GetCode() { return m_state;}

protected:
	//�g�p����{�^��
	int m_name;

	// ���͂̏��
	State m_state = Free;

	// �d�����Ă̍X�V��h��
	bool m_needUpdate = true;
};