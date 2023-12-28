#pragma once
#include"Mcenter.h"

class MOONIGHT_Qt;

class MOONIGHT_QtClass_Pivot
{
public:
	MOONIGHT_QtClass_Pivot(MOONIGHT_Qt* w);
	~MOONIGHT_QtClass_Pivot();

	static MOONIGHT_Qt* MOONIGHT_QtClass_Saved();
	static void MOONIGHT_QtClass_Set(MOONIGHT_Qt* w);

private:
	static MOONIGHT_Qt* w;
};

void MOONIGHT_Play(qint64 ID);