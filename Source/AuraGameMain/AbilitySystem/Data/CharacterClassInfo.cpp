#include "CharacterClassInfo.h"

FCharacterClassDefaultInfo UCharacterClassInfo::GetClassDefaultInfo(ECharacterClass CharacterClass)
{

	return CharacterClassInformation.FindChecked(CharacterClass);
}
