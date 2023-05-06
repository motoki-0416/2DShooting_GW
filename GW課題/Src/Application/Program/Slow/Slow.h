#pragma once

class C_Slow
{
public:

	C_Slow() { Init(); }
	~C_Slow(){};

	void Init();
	bool Update();

	void SetSlow(int a_stop) { if (!slowFlg) { slowFlg = true, slowDelay = a_stop; } }

private:

	bool slowFlg;
	int slowDelay;
	static const int MAX_SLOW=1;

};