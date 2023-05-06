#include "Application/Program/Slow/Slow.h"

void C_Slow::Init()
{

	slowFlg = false;

	slowDelay = 0;

}

bool C_Slow::Update()
{

	if (!slowFlg)return NULL;


	if (slowDelay-- < 0.0f)
	{
	
		slowDelay = MAX_SLOW;

		return NULL;
	
	}

	return true;

}
