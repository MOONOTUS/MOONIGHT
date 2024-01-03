#include"MOONIGHT_Songs'List.h"
#include"MOONIGHT_Player.h"
#include"MPivot.h"

MOONIGHT_Qt* MOONIGHT_QtClass_Pivot::w = nullptr;

MOONIGHT_QtClass_Pivot::MOONIGHT_QtClass_Pivot(MOONIGHT_Qt* w)
{
	MOONIGHT_QtClass_Pivot::w = nullptr; w = w;
}

MOONIGHT_QtClass_Pivot::~MOONIGHT_QtClass_Pivot()
{}

MOONIGHT_Qt* MOONIGHT_QtClass_Pivot::MOONIGHT_QtClass_Saved()
{
	return MOONIGHT_QtClass_Pivot::w;
}

void MOONIGHT_QtClass_Pivot::MOONIGHT_QtClass_Set(MOONIGHT_Qt* w)
{
	MOONIGHT_QtClass_Pivot::w = w;
}

void MOONIGHT_Play(qint64 ID, MMainWindow* linkmain)
{
	MOONIGHT_QtClass_Pivot::MOONIGHT_QtClass_Saved()->Ui()->central = new MWidget(nullptr);
	MOONIGHT_QtClass_Pivot::MOONIGHT_QtClass_Saved()->Ui()->central->setLinkMain(linkmain);
	MOONIGHT_QtClass_Pivot::MOONIGHT_QtClass_Saved()->Ui()->central->resize(linkmain->size());
	switch (ID)
	{
	case 1000000000000:
		TestDemo_InfinityHeaven(MOONIGHT_QtClass_Pivot::MOONIGHT_QtClass_Saved());
		break;
	default:
		qDebug() << "MOONOTUSYSTEM::_Error_::There is no such song that ID = " << ID;
		break;
	}
}