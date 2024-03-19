#include "AttributeInfo.h"

FAuraAttributeInfo UAttributeInfo::FindAttributeInfoForTag(const FGameplayTag& AttributeTag, bool bLogNotFound) const
{
	for (const FAuraAttributeInfo &Info : AttributeInformation)
	{
		if(Info.AttributeTag == AttributeTag)
		{
			return Info;
		}
	}

	if(bLogNotFound)
	{
		UE_LOG(LogTemp,Error,TEXT("Cant find Info for Attribute Tag [%s] on Attribute Info [%s]."),
			*AttributeTag.ToString(),*GetNameSafe(this));
	}

	return FAuraAttributeInfo();
}
