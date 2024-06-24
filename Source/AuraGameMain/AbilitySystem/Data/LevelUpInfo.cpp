
#include "LevelUpInfo.h"

int32 ULevelUpInfo::FindLevelForXP(int32 XP) const
{
	int32 Level = 1;
	bool bSearching = true;
	while(bSearching)
	{
		//LevelUpInfomation[1] = Level 1 Infomation
		//LevelUpInfomation[2] = Level 1 Infomation
		if(LevelUpInfomation.Num() - 1 <= Level) return Level;

		if(XP >= LevelUpInfomation[Level].LevelUpRequirement)
		{
			++Level;
		}
		else
		{
			bSearching = false;
		}
		
	}
	return Level;

}
