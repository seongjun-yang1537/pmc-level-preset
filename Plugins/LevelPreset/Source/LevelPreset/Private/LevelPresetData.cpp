#include "LevelPresetData.h"

bool operator==(const FLevelPresetData& lhs, const FLevelPresetData& rhs)
{
	if(lhs.Prefix != rhs.Prefix) return false;
	if(lhs.LevelPath != rhs.LevelPath) return false;
	return true;
}
